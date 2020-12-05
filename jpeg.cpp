# include "jpeg.h"
// include <cassert> // assert
# include "error.h" // ASSERT
# include <cstdio> // printf
# include <cstring> // strlen strcat
constexpr uint16_t BIG16(const char a[2])
{
	return	static_cast<uint8_t>(a[0]) << 8
	^	static_cast<uint8_t>(a[1]);
}
constexpr uint32_t BIG32(const char a[4])
{
	return	static_cast<uint8_t>(a[0]) << 24
	^	static_cast<uint8_t>(a[1]) << 16
	^	static_cast<uint8_t>(a[2]) << 8
	^	static_cast<uint8_t>(a[3]);
}

# include <emmintrin.h> // SSE2
alignas(16) constexpr int16_t COS16_SSE2[8][8]
{
+32767, +32767, +32767, +32767, +32767, +32767, +32767, +32767,
+32138, +27245, +18204, + 6392, - 6392, -18204, -27245, -32138,
+30273, +12539, -12539, -30273, -30273, -12539, +12539, +30273,
+27245, - 6392, -32138, -18204, +18204, +32138, + 6392, -27245,
+23170, -23170, -23170, +23170, +23170, -23170, -23170, +23170,
+18204, -32138, + 6392, +27245, -27245, - 6392, +32138, -18204,
+12539, -30273, +30273, -12539, -12539, +30273, -30273, +12539,
+ 6392, -18204, +27245, -32138, +32138, -27245, +18204, - 6392,
};
void DCT(int16_t (&MCU)[8][8], const int8_t (&A)[8][8], const uint8_t (&Q)[8][8])
{
	for(int n = 0; n < 8; ++ n)
	{
		__m128i X = _mm_setzero_si128( );
		for(size_t i = 0; i < 8; ++ i)
		{
			__m128i Y = _mm_set1_epi16(COS16_SSE2[i][n]);
			for(size_t j = 0; j < 8; ++ j)
			X = _mm_add_epi16(
				X, _mm_mulhi_epi16(
					_mm_mullo_epi16(
						_mm_set1_epi16(A[i][j]), _mm_set1_epi16(Q[i][j])
					),
					_mm_mulhi_epi16(
						Y, _mm_load_si128((const __m128i *) COS16_SSE2[j])
					)
				)
			);
		}
		_mm_storeu_si128((__m128i *) MCU[n], X);
	}
}
# include <immintrin.h> // AVX2
alignas(32) constexpr int16_t COS16_AVX2[8][16]
{
	+32767, +32767, +32767, +32767, +32767, +32767, +32767, +32767, +32767, +32767, +32767, +32767, +32767, +32767, +32767, +32767,
	+32610, +31357, +28898, +25330, +20787, +15446, + 9512, + 3211, - 3211, - 9512, -15446, -20787, -25330, -28898, -31357, -32610,
	+32138, +27245, +18204, + 6392, - 6392, -18204, -27245, -32138, -32138, -27245, -18204, - 6392, + 6392, +18204, +27245, +32138,
	+31357, +20787, + 3211, -15446, -28898, -32610, -25330, - 9512, + 9512, +25330, +32610, +28898, +15446, - 3211, -20787, -31357,
	+30273, +12539, -12539, -30273, -30273, -12539, +12539, +30273, +30273, +12539, -12539, -30273, -30273, -12539, +12539, +30273,
	+28898, + 3211, -25330, -31357, - 9512, +20787, +32610, +15446, -15446, -32610, -20787, + 9512, +31357, +25329, - 3211, -28898,
	+27245, - 6392, -32138, -18204, +18204, +32138, + 6392, -27245, -27245, + 6392, +32138, +18204, -18204, -32138, - 6392, +27245,
	+25330, -15446, -31357, + 3211, +32610, + 9512, -28898, -20787, +20787, +28898, - 9512, -32610, - 3211, +31357, +15446, -25329
};
void DCT(int16_t (&MCU)[8][16], const int8_t (&A)[8][8], const uint8_t (&Q)[8][8])
{
	for(int n = 0; n < 8; ++ n)
	{
		__m256i X = _mm256_setzero_si256( );
		for(size_t i = 0; i < 8; ++ i)
		{
			__m256i Y = _mm256_set1_epi16(COS16_SSE2[i][n]);
			for(size_t j = 0; j < 8; ++ j)
			X = _mm256_add_epi16(
				X, _mm256_mulhi_epi16(
					_mm256_mullo_epi16(
						_mm256_set1_epi16(A[i][j]), _mm256_set1_epi16(Q[i][j])
					),
					_mm256_mulhi_epi16(
						Y, _mm256_load_si256((const __m256i *) COS16_AVX2[j])
					)
				)
			);
		}
		_mm256_storeu_si256((__m256i *) MCU[n], X);
	}
}
void DCT(int16_t (&MCU)[16][16], const int8_t (&A)[8][8], const uint8_t (&Q)[8][8])
{
	for(int n = 0; n < 16; ++ n)
	{
		__m256i X = _mm256_setzero_si256( );
		for(size_t i = 0; i < 8; ++ i)
		{
			__m256i Y = _mm256_set1_epi16(COS16_AVX2[i][n]);
			for(size_t j = 0; j < 8; ++ j)
			X = _mm256_add_epi16(
				X, _mm256_mulhi_epi16(
					_mm256_mullo_epi16(
						_mm256_set1_epi16(A[i][j]), _mm256_set1_epi16(Q[i][j])
					),
					_mm256_mulhi_epi16(
						Y, _mm256_load_si256((const __m256i *) COS16_AVX2[j])
					)
				)
			);
		}
		_mm256_storeu_si256((__m256i *) MCU[n], X);
	}
}
JPEG<YCbCr>::~JPEG(void)
{ }
JPEG<YCbCr>::JPEG(void): X(0), Y(0)
{ }
JPEG<YCbCr>::JPEG(RC &&rc): X(0), Y(0)
{
/*	auto IDPCM = [](int16_t diff, size_t comp)
	{
		assert(comp < 3);
		static int16_t prev[3] {0};
		return prev[comp] += diff;
	};
	auto IQ64 = [](int16_t *coef, const uint8_t *quan)
	{
		for(int i=0; i<64; ++i)	coef[i] *= quan[i];
	};
	auto IDC = [](int16_t X, size_t MSB)
	{
		return X < 1<<MSB ? X-(2<<MSB)+1 : X;
	};
	struct MCU
	{
		int16_t Y [64] {0};
		int16_t Cb[64] {0};
		int16_t Cr[64] {0};
	};*/
//	uint8_t *QT[2] {nullptr, nullptr};
	uint8_t ZZ[64]
	{
		      000,
		    001,010,
		  020,011,002,
		003,012,021,030,
	      040,031,022,013,004,
	    005,014,023,032,041,050,
	  060,051,042,033,024,015,006,
	007,016,025,034,043,052,061,070,
	  071,062,053,044,035,026,017,
	    027,036,045,054,063,072,
	      073,064,055,046,037,
		047,056,065,074,
		  075,066,057,
		    067,076,
		      077
	};
/*			     0x00,
			  0x01, 0x08,
		       0x10, 0x09, 0x02,
		    0x03, 0x0A, 0x11, 0x18,
		 0x20, 0x19, 0x12, 0x0B, 0x04,
	      0x05, 0x0C, 0x13, 0x1A, 0x21, 0x28,
	   0x30, 0x29, 0x22, 0x1B, 0x14, 0x0D, 0x06,
	0x07, 0x0E, 0x15, 0x1C, 0x23, 0x2A, 0x31, 0x38,
	   0x39, 0x32, 0x2B, 0x24, 0x1D, 0x16, 0x0F,
	      0x17, 0x1E, 0x25, 0x2C, 0x33, 0x3A,
		 0x3B, 0x34, 0x2D, 0x26, 0x1F,
		    0x27, 0x2E, 0x35, 0x3C,
		       0x3D, 0x36, 0x2F,
			  0x37, 0x3E,
			     0x3F*/
//	for(int i=0; i<64; ++i) QT[ZZ[i]];

	const char *p = static_cast<const char *>(rc.data);
	size_t n = 0;

	// DC huff -> bitcount
	// variable-size amplitude -> DC quantization
	// RLE -> ZZ -> AC huff amplitude -> AC quantization


/*	struct MSB
	{
		const char *p = nullptr;
		size_t n = 0;
		MSB(const char *data) : p(data)
		{ }
		uint16_t peek(size_t size_t)
		{
			assert(size_t <= 16);
			return *p;
		}
		void operator +=(size_t size_t)
		{
			p += (n + size_t) / 8 - size_t / 8;
			n += size_t;
		}
		uint16_t seek(size_t size_t)
		{
			assert(size_t <= 16);
			uint16_t bits = peek(size_t);
			operator +=(size_t);
			return bits;
		}
	};*/
	struct HT { uint8_t NOS[16], SYM[ ]; };
//	const *HT[8] = {nullptr};
	uint8_t const *QT[4] = {nullptr};
//	MSB stream(rc.data);

	size_t pop_i(0u);
	auto pop = [&](size_t n)
	{
		const char *p = &rc[pop_i];
		pop_i += n;
		return p;
	};
# ifndef NDEBUG
	char c_str[512] {'\0'};
# endif
	uint16_t L, M, RST = 0xFFFF;
	int16_t Z=1, W=1;
	{
		uint8_t SS;
		const HT	*DHT[8] {nullptr};
		const uint8_t	*DQT[4] {nullptr};
		do switch( M = BIG16(pop(2)) )
		{
			case 0xFFCF: // SOF15 Lossless (differential arithmetic)
			case 0xFFCE: // SOF14 Progressive (differential arithmetic)
			case 0xFFCD: // SOF13 Sequential (differential arithmetic)
			case 0xFFCB: // SOF11 Lossless (arithmetic)
			case 0xFFCA: // SOF10 Progressive (arithmetic)
			case 0xFFC9: // SOF9 Extended sequential (arithmetic)
			case 0xFFC7: // SOF7 Lossless (differential)
			case 0xFFC6: // SOF6 Progressive (differential)
			case 0xFFC5: // SOF5 Sequential (differential)
			case 0xFFC3: // SOF3 Lossless
			case 0xFFC2: // SOF2 Progressive
			case 0xFFC1: // SOF1 Extended Sequential
				printf("error: JPEG SOF%hu\n", M & 0x000F);
			case 0xFFC0: // SOF0 Baseline
			{
				uint16_t size = BIG16(pop(2));
				ASSERT(size == 17 || size == 11);
				pop(1); // This is in bits/sample, usually 8 (12 and 16 not supported by most software).
				const_cast<uint16_t &>(Y) = BIG16(pop(2));
				const_cast<uint16_t &>(X) = BIG16(pop(2));
				uint8_t NOC = *pop(1);
				ASSERT(NOC == 3 || NOC == 1);
/*
'1 1' = YCbCr4:4:4 (1 1)
'1 2' = YCbCr4:4:0 (1 2)
'1 4' = YCbCr4:4:1 (1 4)
'2 1' = YCbCr4:2:2 (2 1)
'2 2' = YCbCr4:2:0 (2 2)
'2 4' = YCbCr4:2:1 (2 4)
'4 1' = YCbCr4:1:1 (4 1)
'4 2' = YCbCr4:1:0 (4 2)*/
				for(uint8_t i=0; i<NOC; ++i)
				{
					uint8_t comp = *pop(1);
					uint8_t SS = *pop(1);
					if(comp == 1) // Y
					{
						ASSERT(!(SS & 0xCC)); // 4:1:1
//						[SS & 0x0F | SS >> 2];
					# ifndef NDEBUG
						switch(SS)
						{
							case 0x11: strcat(c_str, " 4:4:4 "); break; // 8x8
							case 0x12: strcat(c_str, " 4:4:0 "); break;
							case 0x21: strcat(c_str, " 4:2:2 "); break; // 16x8
							case 0x22: strcat(c_str, " 4:2:0 "); break; // 16x16
							case 0x41: strcat(c_str, " 4:1:1 "); break;
							default: break;
						}
					# endif
						L = (SS & 0x0F) * (SS >> 4);
						Z = (SS & 0x0F);
						W = (SS >> 4);
					}
					else
					{
						ASSERT(SS == 0x11);
					}
					DQT[*pop(1)]; // #@?!
				# ifndef NDEBUG
					if(comp > 5) comp = 0;
					const char *C[ ] {"?", "Y", "Cb", "Cr", "I", "Q"};
					strcat(c_str, C[comp]);
				# endif
				}
				continue;
			}
			case 0xFFC4: // DHT
			{
				uint16_t size = BIG16(pop(2));
				size_t NOS = 0;
				for(int j=2; j<size; j+=1+16+NOS)
				{
					uint8_t info = *pop(1);
					ASSERT((info & 0b11101100) == 0);
					DHT[info >> 2 | info & 0x00000111] = reinterpret_cast<const HT *>(pop(16));
					NOS = 0;
					for(int i=0; i<16; ++i) NOS += DHT[info >> 2 | info & 0x00000111]->NOS[i];
	//				const uint8_t *sym = (const uint8_t *)
					pop(NOS);
				}
//				for(int i=0; i<NOS; ++i)
//				assert(sym[i] == DHT[info >> 2 | info & 0x00000111]->SYM[i]);
/*				if(NOS < size - sizeof size + sizeof info + 16)
				{
					printf("warning: DHT +%i\n", size - sizeof size - sizeof info - 16 - NOS);
				}
				printf(" {%u/%u}", NOS, size - sizeof size - sizeof info - 16);
				assert(size == sizeof size + sizeof info + 16 + NOS);*/
				continue;
			}
			case 0xFFD8: // SOI
			# ifndef NDEBUG
				strcat(c_str, "JPEG");
			# endif
				continue;
			case 0xFFDA: // SOS
			{
				uint16_t size = BIG16(pop(2));
//				printf("(SOS %hu)", size);
				uint8_t comp = *pop(1);
				ASSERT(comp == 3 || comp == 1);
				if(comp == 1) ASSERT(size == 8); // Y
				if(comp == 3) ASSERT(size == 12); // YCbCr
			//	assert(p[0] == 1 && p[2] == 2 && p[4] == 3);
			/*	p[1], p[3], p[5]; // comp -> HT
				p += 9;*/
				pop(2*comp+3);
				continue;
			}
			case 0xFFDB: // DQT
			{
				uint16_t size = BIG16(pop(2));
				ASSERT(size % 65 == 67 % 65);
				for(int i=2; i<size; i+=65)
				{
					uint8_t info = *pop(1);
					ASSERT((info & 0b11111100) == 0);
					DQT[info & 0b00000011] = reinterpret_cast<const uint8_t *>(pop(64));
				}
				continue;
			}
			case 0xFFDD: // DRI
			{
			# ifndef NDEBUG
				strcat(c_str, " DRI");
			# endif
				uint16_t size = BIG16(pop(2));
				ASSERT(size == 4);
				RST = BIG16(pop(2));
				continue;
			}
			case 0xFFEF: // APP15
			case 0xFFEE: // APP14
			case 0xFFED: // APP13
			case 0xFFEC: // APP12
			case 0xFFEB: // APP11
			case 0xFFEA: // APP10
			case 0xFFE9: // APP9
			case 0xFFE8: // APP8
			case 0xFFE7: // APP7
			case 0xFFE6: // APP6
			case 0xFFE5: // APP5
			case 0xFFE4: // APP4
			case 0xFFE3: // APP3
			case 0xFFE2: // APP2
			{
				uint16_t size = BIG16(pop(2));
				printf("warning: JPEG APP%hu %s\n", M & 0x000F, pop(size - sizeof size));
				continue;
			}
			case 0xFFE1: // APP1
			{
				uint16_t size = BIG16(pop(2));
				switch(BIG32(pop(6)))
				{
					case BIG32("Exif"):
					# ifndef NDEBUG
						strcat(c_str, " Exif");
					# endif
						printf("[%i]", size - sizeof size - 6);
						pop(size - sizeof size - 6);
						continue;
					default:
						printf("warning: JPEG APP1 %s\n", pop(size - sizeof size - 6) - 6);
						continue;
				}
				continue;
			}
			case 0xFFE0: // APP0
			{
				uint16_t size = BIG16(pop(2));
				ASSERT(!memcmp(pop(5), "JFIF", 5)); // 0x4a, 0x46, 0x49, 0x46, 0x00
			# ifndef NDEBUG
				strcat(c_str, " JFIF");
			# endif
				ASSERT(BIG16(pop(2)) >= 0x10); // revision
				pop(5); // density    
				uint8_t X = *pop(1);
				uint8_t Y = *pop(1);
				if(X * Y)
				{
					printf("warning: JPEG JFIF thumbnail\n");
					pop(X * Y * 3); // RGB
				}
				ASSERT(size - 16 == X * Y * 3);
				continue;
			}
			case 0xFFFE: // COM
			{
				uint16_t size = BIG16(pop(2));
				printf("warning: JPEG %.*s\n", size - sizeof size, pop(size - sizeof size));
				continue;
			}
			default:
			{
				ASSERT((M & 0xFF00) == 0xFF00);
				printf("error: JPEG 0x%04x\n", M);
				uint16_t size = BIG16(pop(2));
				pop(size - sizeof size);
				continue;
			}
		}
		while(M != 0xFFDA); // SOS
	# ifndef NDEBUG
		printf("%s", c_str);
	# endif
	}

	if(L == 1)
	{
		int16_t MCU[8][8];
	}
	if(L == 2)
	{
		int16_t MCU[8][16];
	}
	if(L == 4)
	{
		int16_t MCU[16][16];
	}

	for(int i=0; i<L; ++i); // Y
	for(int i=0; i<1; ++i); // Cb
	for(int i=0; i<1; ++i); // Cr

	RST;
	for(int i=0; i<Y; i+=8)
	for(int j=0; j<X; j+=8)
	// for n=0 n<comp ++n
	{
		int16_t coef[64] {0};
		auto DC = [&](void){return 0;};
		auto AC = [&](void){return 0;};
		for(int k=0; k<64; ++k)
		{
			coef[ZZ[k]] = k ? AC( ) : DC( );
		}
		// DCT
	}
	do // it your own way
	{
		// DC
		// AC[63]
	} while(false);
}
JPEG<YCbCr>::JPEG(JPEG &&JPEG) noexcept: X(JPEG.X), Y(JPEG.Y)
{
/*	memcpy(this, &JPEG, sizeof JPEG);
	memset(&JPEG, 0, sizeof JPEG);*/
	rsrc = static_cast<RC &&>(JPEG.rsrc);
	memset(&JPEG, 0, sizeof JPEG);
}
void JPEG<YCbCr>::operator = (JPEG &&JPEG) noexcept
{
/*	JPEG::~JPEG( );
	memcpy(this, &JPEG, sizeof JPEG);
	memset(&JPEG, 0, sizeof JPEG);*/
	const_cast<uint16_t &>(X) = JPEG.X;
	const_cast<uint16_t &>(Y) = JPEG.Y;
	rsrc = static_cast<RC &&>(JPEG.rsrc);
	memset(&JPEG, 0, sizeof JPEG);
/*	const_cast<uint16_t &>(X) = J.X;
	const_cast<uint16_t &>(Y) = J.Y;
	rsrc = static_cast<RC &&>(J.rsrc);*/
}
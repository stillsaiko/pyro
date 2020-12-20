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
JPEG<void>::JPEG(void): X(0), Y(0)
{ }
# include <emmintrin.h> // SSE2
JPEG<void>::JPEG(RC &&rsrc, size_t Z, size_t align): X(0), Y(0), rsrc(static_cast<RC &&>(rsrc))
{
	constexpr uint8_t ZZ[64]
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
//	for(int i=0; i<64; ++i) QT[ZZ[i]];
	alignas(16) constexpr int16_t COS16[3][8][8]
	{
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32138, 27245, 18204, 6392, -6392, -18204, -27245, -32138,
		30273, 12539, -12539, -30273, -30273, -12539, 12539, 30273,
		27245, -6392, -32138, -18204, 18204, 32138, 6392, -27245,
		23170, -23170, -23170, 23170, 23170, -23170, -23170, 23170,
		18204, -32138, 6392, 27245, -27245, -6392, 32138, -18204,
		12539, -30273, 30273, -12539, -12539, 30273, -30273, 12539,
		6392, -18204, 27245, -32138, 32138, -27245, 18204, -6392,
		// COS16L
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32610, 31357, 28898, 25330, 20787, 15446, 9512, 3211,
		32138, 27245, 18204, 6392, -6392, -18204, -27245, -32138,
		31357, 20787, 3211, -15446, -28898, -32610, -25330, -9512,
		30273, 12539, -12539, -30273, -30273, -12539, 12539, 30273,
		28898, 3211, -25330, -31357, -9512, 20787, 32610, 15446,
		27245, -6392, -32138, -18204, 18204, 32138, 6392, -27245,
		25330, -15446, -31357, 3211, 32610, 9512, -28898, -20787,
		// COS16R
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		-3211, -9512, -15446, -20787, -25330, -28898, -31357, -32610,
		-32138, -27245, -18204, -6392, 6392, 18204, 27245, 32138,
		9512, 25330, 32610, 28898, 15446, -3211, -20787, -31357,
		30273, 12539, -12539, -30273, -30273, -12539, 12539, 30273,
		-15446, -32610, -20787, 9512, 31357, 25329, -3211, -28898,
		-27245, 6392, 32138, 18204, -18204, -32138, -6392, 27245,
		20787, 28898, -9512, -32610, -3211, 31357, 15446, -25329
	};


	// DC huff -> bitcount
	// variable-size amplitude -> DC quantization
	// RLE -> ZZ -> AC huff amplitude -> AC quantization
	
	struct
	{
		const uint8_t *HT[2] = { };
		const uint8_t *QT = nullptr;
		int16_t DC = 0; // DPCM
		uint8_t SS = 0;
	//	int16_t A[64];
	} CCC[3];

//	const uint8_t (*QT[3])[8] { };
//	const uint8_t (*HT[3][2]) { };

	const char *byte = &rsrc[0];
	// bytewise
# ifndef NDEBUG
	char c_str[512] {'\0'};
# endif
//	int16_t Q[2][8][8]; // YCbCr
//	uint8_t SS;
	uint16_t RST = 0xFFFF;
	uint8_t NOC;
	{
		auto pop = [&](size_t n)
		{
			return (byte += n) - n;
		};
		uint16_t M;
		const char *DQT[4];
		const char *DHT[8];
//		if(!ASSERT(BIG16(pop(2)) == 0xFFD8)) return; // SOI
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
				ASSERT(*pop(1) == 8); // 8-bit precision
				const_cast<uint16_t &>(Y) = BIG16(pop(2));
				const_cast<uint16_t &>(X) = BIG16(pop(2));
				NOC = *pop(1);
				ASSERT(NOC == 3 || NOC == 1);
				for(uint8_t i=0; i<NOC; ++i)
				{
					uint8_t comp = *pop(1);
					ASSERT(1 <= comp && comp <= 3);
				//	if(comp == 1) SS = *pop(1), ASSERT(!(SS & 0xCC)); // 4:1:1
				//	else ASSERT(*pop(1) == 0x11);
					CCC[comp - 1].SS = *pop(1);
				//	QT[comp - 1] = (uint8_t (*)[8]) DQT[*pop(1)];
					CCC[comp - 1].QT = (const uint8_t *) DQT[*pop(1)];
				# ifndef NDEBUG
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
					DHT[info >> 2 | info & 0x00000111] = pop(16);
					for(int i=0; i<16; ++i)
					NOS += (uint8_t) DHT[info >> 2 | info & 0x00000111][i];
					pop(NOS);
				}
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
				ASSERT(NOC == *pop(1));
				if(NOC == 1) ASSERT(size == 8); // Y
				if(NOC == 3) ASSERT(size == 12); // YCbCr
				for(uint8_t i=0; i<NOC; ++i)
				{
					uint8_t comp = *pop(1);
					ASSERT(1 <= comp && comp <= 3);
					uint8_t huff = *pop(1);
				//	HT[comp - 1][0] = (const uint8_t *) DHT[0 ^ huff >> 4];
					CCC[comp - 1].HT[0] = (const uint8_t *) DHT[0 ^ huff >> 4];
				//	HT[comp - 1][1] = (const uint8_t *) DHT[8 ^ huff & 15];
					CCC[comp - 1].HT[1] = (const uint8_t *) DHT[8 ^ huff & 15];
				}
				pop(3); // ignore
				continue;
			}
			case 0xFFDB: // DQT
			{
				uint16_t size = BIG16(pop(2));
				ASSERT(size % 65 == 67 % 65);
				for(int i=2; i<size; i+=65)
				{
					uint8_t info = *pop(1);
					ASSERT(!(info & 0b1100)); // 8-bit precision
					DQT[info & 0b00000011] = pop(64);
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
	//	switch(SS)
		switch(CCC[0].SS)
		{
			case 0x11: strcat(c_str, " 4:4:4 "); break; // 8x8
			case 0x12: strcat(c_str, " 4:4:0 "); break;
			case 0x21: strcat(c_str, " 4:2:2 "); break; // 16x8
			case 0x22: strcat(c_str, " 4:2:0 "); break; // 16x16
			case 0x41: strcat(c_str, " 4:1:1 "); break;
			default: break;
		}
		printf("%s", c_str);
	# endif
	}
	// bitwise
	size_t bits = 0;
	size_t size = 0;
	auto peek = [&](size_t count) -> uint16_t
	{
		while(size < count) bits <<= 8, bits |= (uint8_t) *byte++, size += 8;
		return bits >> size-count & (1 << count)-1;
	};
	auto pop = [&](size_t count) -> uint16_t
	{
		while(size < count) bits <<= 8, bits |= (uint8_t) *byte++, size += 8;
		return size -= count, bits >> size & (1 << count)-1;
	};
	auto huff = [&](const uint8_t *H) -> uint8_t
	{
		const uint8_t *sym = &H[16];
		size_t k = 1;
		size_t n = 1;
		for(int i=0; i<16; ++i)
		{
			k <<= 1;
			n <<= 1;
			uint16_t bits = peek(i + 1);
			for(int j=0; j < H[i]; ++j)
			if(bits == k - n + j) return pop(i + 1), *sym;
			else ++sym;
			n -= H[i];
		}
		return ERROR("no matching huffman code");
	};
	auto ampl = [&](uint16_t N) -> uint16_t
	{
		uint16_t X = pop(N);
		return X<<1 < 1<<N ? X-(1<<N)+1 : X; // X<<1 < 1<<N ? -((1<<N) + ~X) : X;
	};

	char *mem = static_cast<char *>(malloc(X*Y*Z));
	auto DCT = [&NOC]()
	{
		for(int k=0; k<NOC; ++k)	;
	};
	RST;
	int16_t DPCM[3] { };
	for(int y=0; y<Y; y+=(CCC[0].SS&0x0F)<<3)
	for(int x=0; x<X; x+=(CCC[0].SS&0xF0)>>1)
	{
	//	int16_t A[3][64];
		int16_t (*AAA[3])[64] { };
		for(int h=0; h<NOC; ++h) // malloc
		AAA[h] = new int16_t[(CCC[h].SS&0x0F)*(CCC[h].SS>>4)][64];

		for(int h=0; h<NOC; ++h)
		for(int i=0; i<CCC[h].SS&0x0F; i+=0x01)
		for(int j=0; j<CCC[h].SS&0xF0; j+=0x10)
		{
			int k = 0;
			int16_t *A = AAA[h][2*i+j/0x10];
			A[ZZ[k++]] = CCC[h].DC += ampl(huff(CCC[h].HT[0]));
			while(k < 64)
			if(uint16_t N = huff(CCC[h].HT[1]))
			{
				while(N & 0xF0) // RLE
				A[ZZ[k++]] = 0, N -= 0x10;
				A[ZZ[k++]] = ampl(N);
			}
			else // EOB
			{
				while(k < 64)
				A[ZZ[k++]] = 0;
			}
		}

		for(int i=0; i<CCC[0].SS&0x0F; i+=0x01)
		for(int n=0; n<8; ++n)
		for(int j=0; j<CCC[0].SS&0xF0; j+=0x10)
		{
			int16_t MCU[3][8];
			for(int h=0; h<NOC; ++h)
			{
				int16_t *A = AAA[h][CCC[h].SS/CCC[0].SS*(2*i+j/0x10)];
				const int16_t (*COS16Y)[8] = COS16[((CCC[0].SS&15)/(CCC[h].SS&15)-1)*(i/0x01+1)];
				const int16_t (*COS16X)[8] = COS16[((CCC[0].SS>>4)/(CCC[h].SS>>4)-1)*(j/0x10+1)];
				// IDCT
				__m128i xmm0 = _mm_setzero_si128( );
				for(size_t i = 0; i < 8; ++ i)
				{
					__m128i xmm1 = _mm_set1_epi16(COS16Y[i][n]);
					for(size_t j = 0; j < 8; ++ j)
					xmm0 = _mm_add_epi16(
						xmm0, _mm_mulhi_epi16(
							_mm_set1_epi16(A[8*i+j] * CCC[h].QT[8*i+j]),
							_mm_mulhi_epi16(
								xmm1, _mm_load_si128((const __m128i *) COS16X[j])
							)
						)
					);
				}
				_mm_storeu_si128((__m128i *) MCU[h], xmm0);
			}
			constexpr int16_t (*RGB[3])(int16_t Y, int16_t Cb, int16_t Cr)
			{
				[ ](int16_t Y, int16_t Cb, int16_t Cr) -> int16_t {return Y + 1.402 * (Cr - 32768);},
				[ ](int16_t Y, int16_t Cb, int16_t Cr) -> int16_t {return Y - 0.344136 * (Cb - 32768)
									- 0.714136 * (Cr - 32768);},
				[ ](int16_t Y, int16_t Cb, int16_t Cr) -> int16_t {return Y + 1.772 * (Cb - 32768);}
			};
			for(int m=0; m<8; ++m)
			if(Z == align)
			{
				// ...
			}
			else
			{
				for(int o=0; o<Z; o+=align) // 16-bit #@?!
				mem[Z*(X*y+x)+0] = RGB[o/align](MCU[0][m], MCU[1][m], MCU[2][m]);
			}
		}
		for(int h=0; h<NOC; ++h) delete[ ] AAA[h]; // free
	}
	// for n=0 n<comp ++n
	{
//		enum YCbCr {Y, Cb, Cr};
		int8_t A[8][8];
		// IDPCM
		// TODO: decode bitwise DC huffman
		int (*DC)(int16_t, size_t) = [ ](int16_t X, size_t N){return X<<1 < 1<<N ? X-(1<<N)+1 : X;}; // X<<1 < 1<<N ? -((1<<N) + ~X) : X;
		A[ZZ[0] >> 3][ZZ[0] & 7] = DPCM += DC(127, 7);
		for(int n=1; n<64; ++n)
		{
			// IRLE
			// TODO: decode bitwise RLE ZZ AC huffman
			int (*AC)(int8_t (&A)[8][8]) = [ ](int8_t (&A)[8][8]){return 0;};
			A[ZZ[n] >> 3][ZZ[n] & 7] = AC(A);
		}
		// IDCT
		// pragma warning (suppress: 6281)
		for(YCbCr comp = Y; comp <= Cr; comp = static_cast<YCbCr>(comp + 1))
		for(int S = 0; S < (SS&0x0F)*(SS>>4); ++ S)
		for(int line = 0; line < 8; ++ line)
		{
			union
			{
				__m128i si128;
				int16_t epi16[8];
			} m128i;
			[&m128i, &A, &Q, line, comp](const int16_t (*COS16X)[8], const int16_t (*COS16Y)[8])
			{
				__m128i XMM0 = _mm_setzero_si128( );
				for(size_t i = 0; i < 8; ++ i)
				{
					__m128i XMM1 = _mm_set1_epi16(COS16Y[i][line]);
					for(size_t j = 0; j < 8; ++ j)
					XMM0 = _mm_add_epi16(XMM0, _mm_mulhi_epi16(_mm_set1_epi16(A[i][j] * Q[comp][i][j]),
						_mm_mulhi_epi16(XMM1, _mm_load_si128((const __m128i *) COS16X[j]))));
				}
				_mm_storeu_si128(&m128i.si128, XMM0);
			}
			(comp&&SS&0x20? COS16_2[S%2]: COS16, comp&&SS&0x02? COS16_2[S/2]: COS16);
			switch(comp)
			{
			case Y:
				for(int i=0; i<8; ++i)
				// TODO: find address from destination bitmap
					mem[3*i+0] = m128i.epi16[i],
					mem[3*i+1] = m128i.epi16[i],
					mem[3*i+2] = m128i.epi16[i];
				break;
			case Cb:
				for(int i=0; i<8; ++i)
				// TODO: find address from destination bitmap
					mem[3*i+1] -= m128i.epi16[i] / 2,
					mem[3*i+2] += m128i.epi16[i];
				break;
			case Cr:
				for(int i=0; i<8; ++i)
				// TODO: find address from destination bitmap
					mem[3*i+0] += m128i.epi16[i],
					mem[3*i+1] -= m128i.epi16[i] / 2;
				break;
			}
		}
	}
	rsrc = RC(free, mem, size*X*Y);
}
// noexcept
JPEG<void>::~JPEG(void) noexcept
{
	rsrc = { };
}
JPEG<void>::JPEG(JPEG &&JPEG) noexcept: X(JPEG.X), Y(JPEG.Y)
{
	rsrc = static_cast<RC &&>(JPEG.rsrc);
	memset(&JPEG, 0, sizeof JPEG);
}
void JPEG<void>::operator =(JPEG &&JPEG) noexcept
{
	const_cast<uint16_t &>(X) = JPEG.X;
	const_cast<uint16_t &>(Y) = JPEG.Y;
	rsrc = static_cast<RC &&>(JPEG.rsrc);
	memset(&JPEG, 0, sizeof JPEG);
}
// const
const void *JPEG<void>::operator *(void) const
{
	return rsrc.data;
}
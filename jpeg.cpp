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
JPEG<void>::JPEG(RC &&rsrc, size_t align, size_t Z): X(0), Y(0)
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
	constexpr int16_t COS16[8][8]
	{
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32138, 27245, 18204, 6392, -6392, -18204, -27245, -32138,
		30273, 12539, -12539, -30273, -30273, -12539, 12539, 30273,
		27245, -6392, -32138, -18204, 18204, 32138, 6392, -27245,
		23170, -23170, -23170, 23170, 23170, -23170, -23170, 23170,
		18204, -32138, 6392, 27245, -27245, -6392, 32138, -18204,
		12539, -30273, 30273, -12539, -12539, 30273, -30273, 12539,
		6392, -18204, 27245, -32138, 32138, -27245, 18204, -6392,
	};
	constexpr int16_t COS16_2[2][8][8]
	{
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
	constexpr uint8_t PRECISION = 8;

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
	if(!rsrc.size || &rsrc[0] == nullptr) return; // prevent access violation
	const char *p = &rsrc[0];
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
			return (p += n) - n;
		};
		uint16_t M;
		const char *DQT[4] { };
		const char *DHT[4][2] { };
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
				WARNING("SOF%hu", M & 0x000F);
			case 0xFFC0: // SOF0 Baseline
			{
				uint16_t size = BIG16(pop(2));
				ASSERT(size == 17 || size == 11);
				ASSERT(*pop(1) == PRECISION); // 8-bit precision
				const_cast<uint16_t &>(Y) = BIG16(pop(2));
				const_cast<uint16_t &>(X) = BIG16(pop(2));
				NOC = *pop(1);
				ASSERT(NOC == 3 || NOC == 1);
			# ifndef NDEBUG
				strcat(c_str, " ");
			# endif
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
				size_t NOS;
				for(int j=2; j<size; j+=1+16+NOS)
				{
					uint8_t info = *pop(1);
					ASSERT((info & 0b11101100) == 0);
					DHT[info & 0b00000011][info >> 4] = pop(16);
					NOS = 0; // NEW
					for(int i=0; i<16; ++i)
					NOS += (uint8_t) DHT[info & 0b00000011][info >> 4][i];
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
					CCC[comp - 1].HT[0] = (const uint8_t *) DHT[huff >> 4][0];
				//	HT[comp - 1][1] = (const uint8_t *) DHT[8 ^ huff & 15];
					CCC[comp - 1].HT[1] = (const uint8_t *) DHT[huff & 15][1];
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
				WARNING("warning: JPEG APP%hu %s", M & 0x000F, pop(size - sizeof size));
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
						pop(size - sizeof size - 6);
						continue;
					default:
						WARNING("APP1 %s", pop(size - sizeof size - 6) - 6);
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
					WARNING("JFIF thumbnail");
					pop(X * Y * 3); // RGB
				}
				ASSERT(size - 16 == X * Y * 3);
				continue;
			}
			case 0xFFFE: // COM
			{
				uint16_t size = BIG16(pop(2));
				WARNING("%.*s", size - sizeof size, pop(size - sizeof size));
				continue;
			}
			default:
			{
				ASSERT((M & 0xFF00) == 0xFF00);
				WARNING("0x%04x", M);
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
		printf("%s\n", c_str);
	# endif
	}
//	CCC[0].SS = (CCC[0].SS>>4)|(CCC[0].SS<<4);
	// bitwise
	size_t bits = 0;
	size_t size = 0;
	auto pop = [&](size_t count) -> uint16_t
	{
		while(size < count)
		{
			uint8_t byte = *p++;
			if(byte == 0xFF) ASSERT(!*p++);
			bits <<= 8, bits |= byte, size += 8;
		}
		return size -= count, bits >> size & (1 << count)-1;
	};
	bool fail = false;
	auto huff = [&](const uint8_t *H) -> uint8_t
	{
		if(!ASSERT(H)) return 0;
		const uint8_t *sym = &H[16];
		size_t k = 1;
		size_t n = 1;
		uint16_t bits = 0;
		size_t K[16];
		size_t N[16];
		uint16_t BITS[16];
		for(int i=0; i<16; ++i) // H[] = {0, 1, 5}
		{
			k <<= 1;			// k = 2	// k = 4	// k = 8
			n <<= 1;			// n = 2	// n = 4	// n = 6
			bits <<= 1;
			bits |= pop(1);			// bits = 1	// bits = 2	// bits = 5
		//	bits |= pop(1) << i;
			K[i] = k;
			N[i] = n;
			BITS[i] = bits;
			for(int j=0; j < H[i]; ++j)	//		// 2 == 0	// 5 == 8 - 6 + 3
			if(bits == k - n + j) return *sym;
			else ++ sym;
			ASSERT(n -= H[i]);		// n = 2	// n = 3
		}
		fail = true;
		printf(" 0b");
		for(int i=0; i<16; ++i)
		putchar(bits>>16-i-1&1?'1':'0');
		printf("\n ");
		for(int i=0; i<16; ++i)
		printf("%c %hhu", i?',':'{', H[i]);
		puts(" }");
		for(int i=0; i<16; ++i)
		printf("k=%u, n=%u, bits=%hu H[%i]=%hhu\n", K[i], N[i], BITS[i], i, H[i]);
		return ERROR("no matching huffman code");
	};
	auto decode = [&](auto& C, short (&A)[8][8])
	{
		{
			uint8_t N = huff(C.HT[0]);
			uint16_t X = pop(N);
			C.DC += X<<1 < 1<<N ? X-(1<<N)+1 : X;
			A[ZZ[0] >> 3][ZZ[0] & 7] = C.DC * C.QT[ZZ[0]];
		}
		for(int k = 1; k < 64; ++ k)
		if(uint8_t N = huff(C.HT[1]))
		{
			k += N >> 4; // RLE (ZRL)
			N &= 0x0F;
			if(!ASSERT(k < 64)) return; // ERROR
			uint16_t X = pop(N);
			int16_t AC = X<<1 < 1<<N ? X-(1<<N)+1 : X;
			A[ZZ[k] >> 3][ZZ[k] & 7] = AC * C.QT[ZZ[k]];
		}
		else return; // EOB
	};
	char *mem = static_cast<char *>(malloc(X*Y*Z));
	this->rsrc = RC(free, mem, X*Y*Z); memset(mem, 0, X*Y*Z); // NEW
	RST;
	for(int y=0; y<Y; y+=(CCC[0].SS&0x0F)<<3)
	for(int x=0; x<X; x+=(CCC[0].SS&0xF0)>>1)
	{
		__m128i R[2][2][8];
		for(short i = 0; i < (CCC[0].SS&15); ++ i)
		for(short j = 0; j < (CCC[0].SS>>4); ++ j)
		{
			// huffman decode: luminance (Y)
			short Y[8][8] { };
			decode(CCC[0], Y);
			if(fail) // #@?!
			{
				printf("(Y) y=%i/%hu x=%i/%hu i=%hi j=%hi\n\n", y, this->Y, x, this->X, i, j);
			}
			// color accumulate: luminance (Y)
			for(int n = 0; n < 8; ++ n)
			{
				__m128i xmm0 = _mm_setzero_si128( );
				for(int i = 0; i < 8; ++ i)
				{
					__m128i xmm1 = _mm_set1_epi16(COS16[i][n]);
					for(int j = 0; j < 8; ++ j)
					 xmm0 = _mm_add_epi16(xmm0, _mm_mulhi_epi16(_mm_set1_epi16(Y[i][j]),
						_mm_mulhi_epi16(xmm1, _mm_loadu_si128((__m128i *) COS16[j])) ));
				}
	//			R[i][j][n] = xmm0;
				R[i][j][n] = _mm_add_epi16(/**/_mm_mullo_epi16(xmm0, _mm_set1_epi16(UINT8_MAX))/**/, _mm_set1_epi16(INT16_MIN));
			}
		}
		__m128i G[2][2][8];
		__m128i B[2][2][8];
		if(NOC >= 3)
		{
			// huffman decode: chrominance (Cb)
			short Cb[8][8] { };
			decode(CCC[1], Cb);
			if(fail) // #@?!
			{
				printf("(Cb) y=%i/%i x=%i/%i\n", y, this->Y, x, this->X);
			}
			// huffman decode: chrominance (Cr)
			short Cr[8][8] { };
			decode(CCC[2], Cr);
			if(fail) // #@?!
			{
				printf("(Cr) y=%i/%i x=%i/%i\n", y, this->Y, x, this->X);
			}
			// color accumulate: chrominance (Cb, Cr)
			if(Z/align > 1)
			for(int i = 0; i < (CCC[0].SS&15); ++ i)
			for(int j = 0; j < (CCC[0].SS>>4); ++ j)
			{
				const short (*COS16i)[8] = CCC[0].SS&0x02 ? COS16_2[i] : COS16;
				const short (*COS16j)[8] = CCC[0].SS&0x20 ? COS16_2[j] : COS16;
				for(int n = 0; n < 8; ++ n)
				{
					G[i][j][n] = R[i][j][n];
					B[i][j][n] = R[i][j][n];
					__m128i xmm0 = _mm_setzero_si128( );
					__m128i xmm1 = _mm_setzero_si128( );
					for(int i = 0; i < 8; ++ i)
					{
						__m128i xmm2 = _mm_set1_epi16(COS16i[i][n]);
						for(int j = 0; j < 8; ++ j)
						{
							__m128i xmm3 = _mm_mulhi_epi16(xmm2, _mm_loadu_si128((__m128i *) COS16j[j]));
							xmm0 = _mm_add_epi16(xmm0, _mm_mulhi_epi16(_mm_set1_epi16(Cb[i][j]), xmm3));
							xmm1 = _mm_add_epi16(xmm1, _mm_mulhi_epi16(_mm_set1_epi16(Cr[i][j]), xmm3));
						}
					}
					R[i][j][n] = _mm_add_epi16(R[i][j][n], /**/_mm_mullo_epi16(xmm1, _mm_set1_epi16(UINT8_MAX))/**/);
					G[i][j][n] = _mm_sub_epi16(G[i][j][n], /**/_mm_mullo_epi16(xmm1, _mm_set1_epi16(UINT8_MAX))/**/);
					G[i][j][n] = _mm_sub_epi16(G[i][j][n], /**/_mm_mullo_epi16(xmm0, _mm_set1_epi16(UINT8_MAX))/**/);
					B[i][j][n] = _mm_add_epi16(B[i][j][n], /**/_mm_mullo_epi16(xmm0, _mm_set1_epi16(UINT8_MAX))/**/);
				}
			}
		}
		// HARTER TEST HIER ///////////////////////////////
		if(fail) // #@?!
		{
			return;
		}
		// HARTER TEST ENDE ///////////////////////////////
		switch(Z/align)
		{
		case 1: // RRRRRRRR
			if(align == sizeof(char))
			for(int i = 0; i < (CCC[0].SS&0x0F); ++ i)
			for(int n = 0; n < 8; ++ n)
			{
				_mm_storeu_si128((__m128i *) &mem[Z*(X*(y+i*8+n)+x)],
				_mm_packs_epi16(_mm_srli_epi16(R[i][0][n], 8), CCC[0].SS & 0x20
					?	_mm_srli_epi16(R[i][1][n], 8)
					:	_mm_setzero_si128( ) ));
			}
			if(align == sizeof(short))
			for(int i = 0; i < (CCC[0].SS&0x0F); ++ i)
			for(int n = 0; n < 8; ++ n)
			{
				for(int j = 0; j < (CCC[0].SS>>4); ++ j)
				{
					_mm_storeu_si128((__m128i *) &mem[Z*(X*(y+i*8+n)+x+j*8)], R[i][j][n]);
				}
			}
			continue;
		case 2: // RGRGRGRG RGRGRGRG
			if(align == sizeof(char))
			for(int i = 0; i < (CCC[0].SS&0x0F); ++ i)
			for(int n = 0; n < 8; ++ n)
			{
				for(int j = 0; j < (CCC[0].SS>>4); ++ j)
				{
					_mm_storeu_si128((__m128i *) &mem[Z*(X*(y+i*8+n)+x+j*8)],
					_mm_packs_epi16(_mm_srli_epi16(_mm_unpacklo_epi16(R[i][j][n], G[i][j][n]), 8),
							_mm_srli_epi16(_mm_unpackhi_epi16(R[i][j][n], G[i][j][n]), 8)));
				}
			}
			if(align == sizeof(short))
			for(int i = 0; i < (CCC[0].SS&0x0F); ++ i)
			for(int n = 0; n < 8; ++ n)
			{
				for(int j = 0; j < (CCC[0].SS>>4); ++ j)
				{
					_mm_storeu_si128((__m128i *) &mem[Z*(X*(y+i*8+n)+x+j*8+0)], _mm_unpacklo_epi16(R[i][j][n], G[i][j][n]));
					_mm_storeu_si128((__m128i *) &mem[Z*(X*(y+i*8+n)+x+j*8+4)], _mm_unpackhi_epi16(R[i][j][n], G[i][j][n]));
				}
			}
		case 3: // !RGB
			if(align == sizeof(char))
			for(int i = 0; i < (CCC[0].SS&0x0F); ++ i)
			for(int n = 0; n < 8; ++ n)
			{
				for(int j = 0; j < (CCC[0].SS>>4); ++ j)
				{
					char RGB[3][8]; // memcpy
				}
			}
			if(align == sizeof(short));
			for(int i = 0; i < (CCC[0].SS&0x0F); ++ i)
			for(int n = 0; n < 8; ++ n)
			{
				for(int j = 0; j < (CCC[0].SS>>4); ++ j)
				{
					short RGB[3][8]; // memcpy
				}
			}
			continue;
		case 4: // RGBARGBA RGBARGBA RGBARGBA RGBARGBA
			__m128i xmm0, xmm1;
			if(align == sizeof(char))
			for(int i = 0; i < (CCC[0].SS&0x0F); ++ i)
			for(int n = 0; n < 8; ++ n)
			{
				for(int j = 0; j < (CCC[0].SS>>4); ++ j)
				{
					xmm0 = _mm_unpacklo_epi16(R[i][j][n], G[i][j][n]),
					xmm1 = _mm_unpacklo_epi16(B[i][j][n], _mm_set1_epi16(-1));
					_mm_storeu_si128((__m128i *) &mem[Z*(X*(y+i*8+n)+x+j*8+0)],
					_mm_packus_epi16(/*_mm_srli_epi16(*/_mm_unpacklo_epi32(xmm0, xmm1)/*, PRECISION - 8)*/,
							/*_mm_srli_epi16(*/_mm_unpackhi_epi32(xmm0, xmm1)/*, PRECISION - 8)*/));
					xmm0 = _mm_unpackhi_epi16(R[i][j][n], G[i][j][n]),
					xmm1 = _mm_unpackhi_epi16(B[i][j][n], _mm_set1_epi16(-1));
					_mm_storeu_si128((__m128i *) &mem[Z*(X*(y+i*8+n)+x+j*8+4)],
					_mm_packus_epi16(/*_mm_srli_epi16(*/_mm_unpacklo_epi32(xmm0, xmm1)/*, PRECISION - 8)*/,
							/*_mm_srli_epi16(*/_mm_unpackhi_epi32(xmm0, xmm1)/*, PRECISION - 8)*/));
				}
			}
			if(align == sizeof(short))
			for(int i = 0; i < (CCC[0].SS&0x0F); ++ i)
			for(int n = 0; n < 8; ++ n)
			{
				for(int j = 0; j < (CCC[0].SS>>4); ++ j)
				{
					xmm0 = _mm_unpacklo_epi16(R[i][j][n], G[i][j][n]);
					xmm1 = _mm_unpacklo_epi16(B[i][j][n], _mm_set1_epi16(-1));
					if(ASSERT(Z*(X*(y+i*8+n)+x+j*8+0) < X*Y*Z))
					_mm_storeu_si128((__m128i *) &mem[Z*(X*(y+i*8+n)+x+j*8+0)], _mm_unpacklo_epi32(xmm0, xmm1));
					if(ASSERT(Z*(X*(y+i*8+n)+x+j*8+2) < X*Y*Z))
					_mm_storeu_si128((__m128i *) &mem[Z*(X*(y+i*8+n)+x+j*8+2)], _mm_unpackhi_epi32(xmm0, xmm1));
					xmm0 = _mm_unpackhi_epi16(R[i][j][n], G[i][j][n]),
					xmm1 = _mm_unpackhi_epi16(B[i][j][n], _mm_set1_epi16(-1));
					if(ASSERT(Z*(X*(y+i*8+n)+x+j*8+4) < X*Y*Z))
					_mm_storeu_si128((__m128i *) &mem[Z*(X*(y+i*8+n)+x+j*8+4)], _mm_unpacklo_epi32(xmm0, xmm1));
					if(ASSERT(Z*(X*(y+i*8+n)+x+j*8+6) < X*Y*Z))
					_mm_storeu_si128((__m128i *) &mem[Z*(X*(y+i*8+n)+x+j*8+6)], _mm_unpackhi_epi32(xmm0, xmm1));
				}
			}
			continue;
		}
	}
	ASSERT(static_cast<uint8_t>(p[0]) == 0xFF);
	ASSERT(static_cast<uint8_t>(p[1]) == 0xC4);
	//this->rsrc = RC(free, mem, X*Y*Z);
	printf("diff %i\n", p - &rsrc[0]);
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
# include "tiff.h"
# include "error.h"
# include <cstdio>
constexpr uint64_t BIG64(const char a[8]) // DOUBLE=0x000C
{
	return	static_cast<uint64_t>(a[0]) << 56
	^	static_cast<uint64_t>(a[1]) << 48
	^	static_cast<uint64_t>(a[2]) << 40
	^	static_cast<uint64_t>(a[3]) << 32
	^	static_cast<uint64_t>(a[4]) << 24
	^	static_cast<uint64_t>(a[5]) << 16
	^	static_cast<uint64_t>(a[6]) << 8
	^	static_cast<uint64_t>(a[7]);
}
// LONG=0x0004, RATIONAL=0x0005, SLONG=0x0009, SRATIONAL=0x000A, FLOAT=0x000B
constexpr uint32_t BIG32(const char a[4])
{
	return	static_cast<uint8_t>(a[0]) << 24
	^	static_cast<uint8_t>(a[1]) << 16
	^	static_cast<uint8_t>(a[2]) << 8
	^	static_cast<uint8_t>(a[3]);
}
constexpr uint16_t BIG16(const char a[2]) // SHORT=0x0003, SSHORT=0x0008
{
	return	static_cast<uint8_t>(a[0]) << 8
	^	static_cast<uint8_t>(a[1]);
}
TIFF<void>::~TIFF(void)
{
	const_cast<uint32_t &>(X) = 0;
	const_cast<uint32_t &>(Y) = 0;
}
TIFF<void>::TIFF(void): X(0), Y(0), Z(0), N(0)
{ }
TIFF<void>::TIFF(RC &&rc): X(0), Y(0), Z(0), N(0), rsrc(static_cast<RC &&>(rc))
{
	enum TYPE
	{
		BYTE = 0x0001,
		ASCII = 0x0002,
		SHORT = 0x0003,
		LONG = 0x0004,
		RATIONAL = 0x0005,
		SBYTE = 0x0006,
		UNDEFINE = 0x0007,
		SSHORT = 0x0008,
		SLONG = 0x0009,
		SRATIONAL = 0x000A,
		FLOAT = 0x000B,
		DOUBLE   = 0x000C
	};
	struct FIELD
	{
		union
		{
			uint8_t BYTE[4]; // TYPE=0x0001
			char ASCII[4]; // TYPE=0x0002
			uint16_t SHORT[2]; // TYPE=0x0003
			uint32_t LONG[1]; // TYPE=0x0004
			uint32_t RATIONAL[ ][2]; // TYPE=0x0005
			int8_t SBYTE[4]; // TYPE=0x0006
			char UNDEFINE[ ]; // TYPE=0x0007
			int16_t SSHORT[2]; // TYPE=0x0008
			int32_t SLONG[1]; // TYPE=0x0009
			int32_t SRATIONAL[ ][2]; // TYPE=0x000A
			float FLOAT[1]; // TYPE=0x000B
			double DOUBLE[ ]; // TYPE=0x000C
		};
	};
	{
		size_t pop_i(0u);
		auto pop = [&](size_t n)
		{
			const char *p = &rsrc[pop_i];
			pop_i += n;
			return p;
		};
	/*	const FIELD *(*IFD)(uint32_t, const char *, TYPE, uint32_t);
		IFD = [ ](uint32_t X, const char *M, TYPE T, uint32_t N)
		{
			return reinterpret_cast<const FIELD *>(M + X);
		};*/

		uint16_t (*uint16)(const char *);
		uint32_t (*uint32)(const char *);
		uint64_t (*uint64)(const char *);
		switch(BIG16(pop(2)))
		{
			case BIG16("MM"):
				uint16 = [ ](const char *p) { return BIG16(p); };
				uint32 = [ ](const char *p) { return BIG32(p); };
				uint64 = [ ](const char *p) { return BIG64(p); };
				break;
			case BIG16("II"):
				uint16 = [ ](const char *p) { return *reinterpret_cast<const uint16_t *>(p); }; // strict aliasing rule undefined (behaviour)
				uint32 = [ ](const char *p) { return *reinterpret_cast<const uint32_t *>(p); }; // strict aliasing rule undefined (behaviour)
				uint64 = [ ](const char *p) { return *reinterpret_cast<const uint64_t *>(p); }; // strict aliasing rule undefined (behaviour)
				break;
			default:
				ERROR("ENDIAN");
				return;
		}
		ASSERT(uint16(pop(2)) == 42);
		uint32_t O;
		while(O = uint32(pop(4)))
		{
			pop_i = O;
			uint16_t N = uint16(pop(2));
			for(uint16_t i=0; i<N; ++i)
			{
				uint16_t M = uint16(pop(2));
				enum {	 BYTE = 0x0001, ASCII    = 0x0002,  SHORT = 0x0003,  LONG = 0x0004,  RATIONAL = 0x0005,
					SBYTE = 0x0006, UNDEFINE = 0x0007, SSHORT = 0x0008, SLONG = 0x0009, SRATIONAL = 0x000A,
					FLOAT = 0x000B, DOUBLE   = 0x000C } TYPE = static_cast<decltype(SLONG)>(uint16(pop(2)));
				uint32_t N = uint32(pop(4));
				FIELD X;
				X.LONG[0] = uint32(pop(4)); // #@?!
				switch(M)
				{
					case 0x00FE: // NewSubfileType
						ASSERT(TYPE == LONG); break;
					case 0x00FF: // NewSubfileType
						ASSERT(TYPE == SHORT); break;
					case 0x0100: // ImageWidth
						ASSERT(TYPE == SHORT || TYPE == LONG);
						const_cast<uint32_t &>(this->X) = X.LONG[0];
						break;
					case 0x0101: // ImageLength
						ASSERT(TYPE == SHORT || TYPE == LONG);
						const_cast<uint32_t &>(this->Y) = X.LONG[0];
						break;
					case 0x0102: // BitsPerSample
						ASSERT(TYPE == SHORT);
						const_cast<uint16_t &>(this->Z) = X.SHORT[0] >> 3;
						const_cast<uint16_t &>(this->N) = N;
						// ...
						break;
					case 0x0103: // Compression
						ASSERT(TYPE == SHORT);
						ASSERT(X.SHORT[0] == 1);
						break;
					case 0x0106: // PhotometricInterpretation
					case 0x0107: // Threshholding
					case 0x0108: // CellWidth
					case 0x0109: // CellLength
					case 0x010A: // FillOrder
						ASSERT(TYPE == SHORT); break;
					case 0x010E: // ImageDescription
					case 0x010F: // Make
					case 0x0110: // Model
						ASSERT(TYPE == ASCII); break;
					case 0x0111: // StripOffsets
						ASSERT(TYPE == SHORT || TYPE == LONG);
						if(TYPE == SHORT) offs = X.SHORT[0];
						if(TYPE == LONG) offs = X.LONG[0];
						break;
					case 0x0112: // Orientation
						ASSERT(TYPE == SHORT); break;
					case 0x0115: // SamplesPerPixel
						ASSERT(TYPE == SHORT);
						const_cast<uint16_t &>(this->N) = X.SHORT[0];
						break;
					case 0x0116: // RowsPerStrip
						ASSERT(TYPE == SHORT || TYPE == LONG);
						// ...
						break;
					case 0x0117: // StripByteCounts
						ASSERT(TYPE == SHORT || TYPE == LONG);
						// ...
						break;
					case 0x0118: // MinSampleValue
					case 0x0119: // MaxSampleValue
						ASSERT(TYPE == SHORT); break;
					case 0x011A: // XResolution
					case 0x011B: // YResolution
						ASSERT(TYPE == RATIONAL); break;
					case 0x011C: // PlanarConfiguration
						ASSERT(TYPE == SHORT); break;
					case 0x0120: // FreeOffsets
					case 0x0121: // FreeByteCounts
						ASSERT(TYPE == LONG); break;
					case 0x0122: // GrayResponseUnit
					case 0x0123: // GrayResponseCurve
					case 0x0128: // ResolutionUnit
						ASSERT(TYPE == SHORT); break;
					case 0x0131: // Software
					case 0x0132: // DateTime
					case 0x013B: // Artist
					case 0x013C: // HostComputer
						ASSERT(TYPE == ASCII); break;
						break;
					case 0x0140: // ColorMap
					case 0x0152: // ExtraSamples
						ASSERT(TYPE == SHORT); break;
						break;
					case 0x8298: // Copyright
						ASSERT(TYPE == ASCII); break;
						break;
					default:
						break;
				}
			}
		}
	}
/*	printf(" pop_i %u\n", pop_i);
	printf("uint16_t %hu\n", uint16(pop(2)));
	printf("uint16_t %hu\n", uint16(pop(2)));
	printf("uint16_t %hu\n", uint16(pop(2)));
	printf("uint16_t %hu\n", uint16(pop(2)));
	// TinyTIFFReader_fseek_set(tiff, tiff->nextifd_offset+2+12*ifd_count)
	offs = pop(X*Y*4);
	for(int i=4; i<8; ++i)
		printf(" %02hhx", reinterpret_cast<const char* >(offs)[i]);
	uint32_t loooong = 0xFF5B4B66;
	assert(!memcmp(offs, & loooong, 4));*/
//	memcpy(const_cast<uint8_t *&>(Z) = new uint8_t[X*Y*3], , X*Y*3);
}
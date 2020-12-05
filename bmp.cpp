# include "bmp.h"
# include <cassert>
# include <windows.h>
# include <cstdio>
BM::~BM(void)noexcept
{
	const_cast<uint32_t *&>(bmiColors) = nullptr;
}
BM::BM(void)noexcept
{ }
void BM::operator =(BM &&a)noexcept
{
	RC::operator =(std::move(a));
	const_cast<uint32_t *&>(bmiColors) = const_cast<uint32_t *>(a.bmiColors);
	const_cast<uint32_t *&>(a.bmiColors) = 0;
}
BM::BM(RC &&a): RC(std::move(a))
{
	// BITMAPFILEHEADER
	assert(RC::operator[ ](0x00) == 'B');
	assert(RC::operator[ ](0x01) == 'M');
	// BITMAPINFOHEADER
	const_cast<uint32_t *&>(bmiColors)=(uint32_t *)&RC::operator[ ](*(uint32_t *)&RC::operator[ ](0x0E) + 0x0E);
}
const BM::bmiHeader * BM::operator ->(void)
{
	return (const bmiHeader *)&RC::operator[ ](0x0E);
}
const void * BM::operator[ ](size_t n)
{
	return	& RC::operator[ ](*(uint32_t *)
		& RC::operator[ ](0x0A)	+((*this)->biWidth * operator ->( )->biBitCount + 0x1F) / 0x20 * n);
}
# ifdef _WIN32 // CreateDIBSection
BM::operator const BITMAPINFO *(void)
{
	return (const BITMAPINFO *)operator ->( );
}
# endif
BMP<void>::~BMP(void)noexcept
{
	if(bmiPixels)
	delete[ ] bmiPixels;
} // BITMAPCOREHEADER
BMP<void>::BMP(void)noexcept: X(0), Y(0)
{ }
/*
	BM Q = std::move(RC);
	// alloc bmiPixels
	bmiStride = (sizeof(T) * Q->biWidth + 3) / 4;
	bmiPixels = new uint32_t[Q->biHeight * bmiStride];
	// ............make sure bitfields are defined
	int n = Q->biBitCount != 16 ? (Q->biBitCount + 7) / 8 : 3;
	int z = Q->biBitCount / n;
	for(size_t i=0; i<Q->biHeight; ++i)
	for(size_t j=0; j<Q->biWidth;  ++j)
	{
	}
	// puff bitwise @#?!
	if constexpr(sizeof(T) == 1)
	{
		int z = bmiHeader->biBitCount == 16 ? 5
		if(bmiHeader->biBitCount == 16)
		{
				
		}
		switch(bmiHeader->biBitCount)
		{
		case 16:
			{
				BM L(bmiHeader.biWidth, bmiHeader.biWidth, 24);
				for(int32_t i=0; i<bmiHeader->biHeight; ++i)
				for(int32_t j=0; j<bmiHeader->biWidth;  ++j)
					reinterpret_cast<uint16_t *>(L[i])[j]
				Q = std::move(L);
			}
		case 24:
		case 32:
			bmiHeader->biClrUsed = 0; // make sure
			for(int32_t i=0; i<bmiHeader->biHeight; ++i)
			for(int32_t j=0; j<bmiHeader->biWidth;  ++j)
			{
				T *p = operator[ ](i)[j];
				(char *)BM[i] + ;
						
				if([this](T *p)
				{
					for(int32_t k=0; k<bmiHeader->biClrUsed; ++k)
					if(memcmp(p, bmiColors + k, sizeof(T)) == 0)
						return true;
				}(p))
				{
					assert(miHeader->biClrUsed < 256);
					memcpy(bmiColors+miHeader->biClrUsed++, p, sizeof(T));
				}
				++ p;
			}
		default:
			break
		}
			
		for(int i=0; i<bmiHeader.biHeight; ++i)
		{
			auto *p = (unsigned char *)bmiPixels + i * bmiStride;
			for(int j=0; j<bmiHeader.biWidth; ++j)
			for(int k=0; k<8; k+=bmiHeader.biBitCount)
				operator[ ](i)[j] = p[j] & bmiColors[0] << k;
		}
	}
	// ...
	if(biCompression != BI_BITFIELDS)
	switch(biBitCount)
	{
		case 1:
			bmiColors[0] = 0x1;
		case 2:
			bmiColors[0] = 0x3;
		case 4:
			bmiColors[0] = 0x0F;
		case 8:
			bmiColors[0] = 0xFF;
			break;
		case 16:
			bmiColors[0] = 0x7C00;
			bmiColors[1] = 0x03E0;
			bmiColors[2] = 0x001F;
			break;
		case 24:
			bmiColors[0] = 0xFF0000;
			bmiColors[1] = 0x00FF00;
			bmiColors[2] = 0x0000FF;
		case 32:
			bmiColors[0] = 0x00FF0000;
			bmiColors[1] = 0x0000FF00;
			bmiColors[2] = 0x000000FF;
			bmiColors[3] = 0xFF000000;
		default:
			break; // error
	}

	if(biBitCount < 8)
	{
		//int comp_in = 
	}
	// transcode

	switch(biBitCount)
	{
		case 1:
		case 2:
		case 4:
			break;
		case 8:
		case 16:
		case 24:
		case 32:
		default:
			break;
	}
*/
// ifndef BI_ALPHABITFIELDS
// define BI_ALPHABITFIELDS 6
// endif
BMP<void>::BMP(RC &&bin, BM::Z Z): X(0), Y(0)
{
	// assert bin.n > sizeof BM + 14
	const BM *Q = reinterpret_cast<const BM *>(& bin[14]);
	// BI_RGB
	assert(Q->biCompression != BI_RLE8);
	assert(Q->biCompression != BI_RLE4);
	// BI_BITFIELDS (Huffman 1D)
	assert(Q->biCompression != BI_JPEG); // (24-bit RLE)
	assert(Q->biCompression != BI_PNG);
	// BI_ALPHABITFIELDS 6
	// BI_SRCPREROTATE 0x8000 (?)
	if(Q->biCompression == BI_RGB)
	{ }
	else
	{ }
	// #@?!
	if(Q->biBitCount == 0)
	{
		const_cast<uint16_t &>(Q->biBitCount) = 24;
		printf("warning: *.bmp has biBitCount=0\n");
	}
	// auto bit depth from *.bmp
	if(Z == 0) Z = static_cast<BM::Z>(Q->biBitCount);
	// ...
	if(Z != Q->biBitCount)
	{
		// convert
	}
	// ...
	if(Z == 0)
	{
		memcpy(static_cast<BM::bmiHeader *>(this), &Q->biSize, sizeof(BM::bmiHeader));
		memcpy(bmiColors, Q.bmiColors, Q->biClrUsed ? Q->biClrUsed : biBitCount >> 3 < 2 ? 1 << biBitCount : 0);
		memcpy(buffer, Q.buffer, sizeof(uint32_t) * stride * biHeight);
		return;
	}
	else // bmiHeader
	biWidth       = Q->biWidth;
	biHeight      = Q->biHeight;
	biBitCount    = Z ? Z : Q->biBitCount;
	biCompression = BI_RGB;
	biSizeImage   = (biBitCount * biWidth + 31) / 32 * biHeight * sizeof(uint32_t);
	biClrUsed     = Z < 16 ? 1 << biBitCount : 0;
	// alloc bmiPixels
	bmiStride = (biWidth * biBitCount + 31) / 32;
	bmiPixels = new uint32_t[bmiStride * biHeight];
	// ...
	const_cast< int32_t &>(X) = Q->biWidth;
	const_cast< int32_t &>(Y) = Q->biHeight;
	const_cast<uint16_t &>(Z) = Z ? Z : Q->biBitCount;
	// ...
	if(Z > 8 && Q->biBitCount <= 8) // BitCount > 8 && ByteCount < PAL
	{
		// PAL 2 RGB
		// 2 bpp -> RGB5, RGB8, RGBA8
		// 4 bpp -> RGB5, RGB8, RGBA8
		// 8 bpp -> RGB5, RGB8, RGBA8
	}
	if(Z == 8 && Q->biBitCount > 8) // biBitCount <= 8 && ByteCount != PAL
	{
		// RGB to PAL
		// 16 bpp -> PAL
		// 24 bpp -> PAL
		// 32 bpp -> PAL
	}
	// ...
	if(biClrUsed == 0)
	switch(Z)
	{
		case 0: switch(biBitCount)
		{
			case 1:	biClrUsed = 0x0002; break;
			case 2:	biClrUsed = 0x0004; break;
			case 4:	biClrUsed = 0x0010; break;
			case 8:	biClrUsed = 0x0100; break;
			case 16:biClrUsed = 0x0003; break;
			case 24:biClrUsed = 0x0000; break;
			case 32:biClrUsed = 0x0004; break;
			default: /* format error */ break;
		}
		case 8:  biClrUsed = 0x0100; break;
		case 16: biClrUsed = 0x0003; break;
		case 24: biClrUsed = 0x0000; break;
		case 32: biClrUsed = 0x0004; break; // BI_BITFIELDS
		default: /* invalid format error */ break;
	}
	// copy bmiColors
	memcpy(bmiColors, Q.bmiColors, sizeof*bmiColors*biClrUsed);
	// alloc bmiPixels
	bmiStride = (biWidth * biBitCount + 31) / 32;
	bmiPixels = new uint32_t[bmiStride * biHeight];
	memcpy(bmiPixels, Q.bmiPixels, sizeof*bmiPixels*bmiStride*biHeight);
	// transcode
	if(Z)
	if(Z != biBitCount)
	{
		// ...
	}
}
BMP<void>::BMP(int32_t X, int32_t Y, BM::Z Z, const void *p): X(X), Y(Y), Z(Z)
{
	 const_cast<BM::Z&>(W) =
	static_cast<BM::Z>(Z + 7 >> 3);
	// ...
	biWidth = X, biHeight = Y, biBitCount = Z;
	bmiStride = (biWidth * biBitCount + 31) / 32;
	bmiPixels = new uint32_t[bmiStride * biHeight];
	if(p)for(int i=0; i<biHeight; ++i)
		memcpy(operator[ ](i), p, (X*Z >> 3)*i);
}
void * BMP<void>::operator[ ](int32_t i)
{
	return bmiPixels + i * bmiStride;
}
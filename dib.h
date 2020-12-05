# pragma once
//struct BGR { unsigned char B, G, R; };
//typedef unsigned char PAL; 
# include "wnd.h"
// DIB requires CS_BYTEALIGNCLIENT or CS_BYTEALIGNWINDOW
// case WM_CREATE:
//	unique<DIB<BGR>> = DIB(GetDC(HWND), X, Y)
// case WM_PAINT:
//	memset(unique<DIB>[0], 255, sizeof(BGR)*X*Y)
//	unique<DIB>.swap( )
// case WM_DESTROY:
//	unique<DIB> = DIB( )
template<class T> class DIB // Section
{
	HDC DC = NULL ;
	HBITMAP WBMP = NULL ;
	char * SECTION = nullptr ;
	BITMAPINFOHEADER BI {0};
public:
	RGBQUAD PAL[256] {0};
	~
	DIB(void);
	DIB(void);
	DIB(HDC, WORD X, WORD Y); // 65535 max
	void operator = (DIB&&)noexcept; // move
	T * operator[ ](WORD); // nth scanline
	T * operator * (void); // 1st scanline
	void blit(WORD = 0xFFFF, WORD = 0xFFFF);
	void stretch(WORD, WORD);
};
// dib.inl
# include <cassert>
# include <cstdio>
# include <typeinfo>
template<class T> DIB<T>::~DIB(void)noexcept
{
	if(WBMP && SECTION)
	{
		DIBSECTION DIB ;
		GetObject(WBMP, sizeof(DIBSECTION), & DIB);
		DeleteObject(WBMP);
		DeleteObject(DIB.dshSection);
		DC = NULL ;
		SECTION = nullptr ;
	}
}
template<class T> DIB<T>::DIB(void)
{ }
template<class T> DIB<T>::DIB(HDC DC, WORD X, WORD Y)
{
	// require byte align
	assert(CS & CS_BYTEALIGNCLIENT || CS & CS_BYTEALIGNWINDOW);
	/*{
		HWND WND = WindowFromDC(DC);
		assert(WND);
		char lpClassName[256];
		assert( GetClassNameA(WND, lpClassName, sizeof lpClassName) );
		WNDCLASS WC ;
		assert( GetClassInfoA(GetModuleHandle(nullptr), lpClassName, &WC) );
		assert(WC.style & CS_BYTEALIGNCLIENT
			|| WC.style & CS_BYTEALIGNWINDOW);
	}*/
	assert(X > 0);
	assert(Y > 0);
	this->DC = DC ;
	BI = {
		sizeof BI,
		(LONG)X,
		(LONG)Y,
		1, // Planes
		WORD( 8u * sizeof(T) ), // BitCount
		BI_RGB, // Compression
		X*Y*sizeof(T), // SizeImage
		0, 0, // PelsPerMeter
		256, // ClrUsed
		0 // ClrImportant
	};
	WBMP = CreateDIBSection(DC, (BITMAPINFO*)&BI, DIB_RGB_COLORS, (void**)&SECTION, NULL, 0);
}
template<class T> void DIB<T>::operator = (DIB&& a)noexcept
{
	DIB<T>::~ DIB<T>( ); // release
// move semantics
	DC = a.DC; a.DC = NULL;
	WBMP = a.WBMP; a.WBMP = NULL;
	memcpy(&BI, &a.BI, sizeof BI);	memset(&a.BI, 0, sizeof BI);
	memcpy(PAL, a.PAL, sizeof PAL);	memset(a.PAL, 0, sizeof PAL);
	SECTION = a.SECTION; a.SECTION = nullptr;
//	return *this;
}
template<class T> T * DIB<T>::operator[ ](WORD i)
{
	//                                  (T*)&SECTION[(BI.biWidth*1+3)/4*4*i]
	return SECTION && i < BI.biHeight ? (T*)&SECTION[(BI.biWidth*3+3)/4*4*i] : nullptr;
//	return SECTION && i < BI.biHeight ? (T*)&SECTION[BI.biWidth*sizeof(T)*i] : nullptr;
}
template<class T> T * DIB<T>::operator * (void)
{
	return SECTION && BI.biHeight ? (T *)SECTION : nullptr;
}
template<class T> void DIB<T>::blit(WORD Xn, WORD Yn)
{
	WORD X = min(Xn, BI.biWidth);
	WORD Y = min(Yn, BI.biHeight);
//	int i = SetDIBits(DC, WBMP, 0, Y, SECTION, (BITMAPINFO *)& BI, DIB_RGB_COLORS);
	int i = SetDIBitsToDevice(
		DC,
		0, 0, // dst			// XDest, YDest
		X, Y,				// dwWidth, dwHeight
		0, 0, // src			// XSrc, YSrc
		0, // first scan line		// uStartScan
		Y, // number of scan lines	// cScanLines
		SECTION,			// lpvBits
		(BITMAPINFO *)& BI,		// lpbmi
		DIB_RGB_COLORS			// fuColorUse
	);
//	BitBlt(DC, 0, 0, X, Y, 
	assert(i == Y);
}

template<class T> void DIB<T>::stretch(WORD Xn, WORD Yn)
{
	DWORD X = BI.biWidth;
	DWORD Y = BI.biHeight;
	int i = StretchDIBits(
		DC,
		0, 0, // dst			// XDest, YDest
		Xn, Yn,
		0, 0, // src			// XSrc, YSrc
		X, Y,
		SECTION,			// lpvBits
		(BITMAPINFO *)& BI,		// lpbmi
		DIB_RGB_COLORS,			// fuColorUse
		SRCCOPY
	);
	assert(i == Y);
}
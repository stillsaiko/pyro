# include <cassert>
# include <cstdio>
# include <typeinfo>
template<class T> DIB<T>::~DIB(void){
// release (copy #1)
	if(WBMP && SECTION){
		printf("warning: DIB<%s> (destructor)\n", typeid(T).name( ));
		DIBSECTION DIB ;
		GetObject(WBMP, sizeof(DIBSECTION), & DIB);
		DeleteObject(WBMP);
		DeleteObject(DIB.dshSection);
	}
}
template<class T> DIB<T>::DIB(void){ }
template<class T> DIB<T>::DIB(HDC DC, WORD X, WORD Y){
/*	// require byte align
	{
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
template<class T>
DIB<T>& DIB<T>::operator = (DIB&& a)noexcept {
// release (copy #2)
	if(WBMP && SECTION){
		DIBSECTION DIB ;
		GetObject(WBMP, sizeof(DIBSECTION), & DIB);
		DeleteObject(WBMP);
		DeleteObject(DIB.dshSection);
	}
// move semantics
	DC = a.DC ; a.DC = NULL ;
	WBMP = a.WBMP ; a.WBMP = NULL ;
	memcpy(&BI, &a.BI, sizeof BI);	memset(&a.BI, 0, sizeof BI);
	memcpy(PAL, a.PAL, sizeof PAL);	memset(a.PAL, 0, sizeof PAL);
	SECTION = a.SECTION ; a.SECTION = nullptr ;
	return *this ;
}
template<class T>
T * DIB<T>::operator[ ](WORD i){
	return SECTION && i < BI.biHeight ? (T*)&SECTION[(BI.biWidth*3+3)/4*4*i] : nullptr ;
}
template<class T>
void DIB<T>::swap(void){
	DWORD X = BI.biWidth ;
	DWORD Y = BI.biHeight ;
	int i = SetDIBitsToDevice(
		DC,
		0, 0, // dst				// XDest, YDest
		X, Y,						// dwWidth, dwHeight
		0, 0, // src				// XSrc, YSrc
		0, // first scan line		// uStartScan
		Y, // number of scan lines	// cScanLines
		SECTION,					// lpvBits
		(BITMAPINFO*)& BI,						// lpbmi
		DIB_RGB_COLORS				// fuColorUse
	);
	assert(i == Y);
}
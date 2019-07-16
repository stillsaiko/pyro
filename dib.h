# pragma once
# include "wnd.h"
struct BGR { unsigned char B, G, R ; };
template<class T = BGR> struct DIB {
	~
	DIB(void);
	DIB(void);
	DIB(HDC, WORD X, WORD Y); // 65535 max
	DIB& operator = (DIB&&)noexcept ;
	T * operator[ ](WORD); // scanline
	void swap(void);
private:
	HDC DC = NULL ;
	HBITMAP WBMP = NULL ;
	BITMAPINFOHEADER BI {0};
	RGBQUAD PAL[256] {0};
	char * SECTION = nullptr ;
};
# include "dib.inl"

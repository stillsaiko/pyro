# pragma once
// openGL Render Context
# include "wnd.h"
# include <gl/glew.h> // just for youser
// case WM_CREATE:
//	unique<GLRC> = GLRC(GetDC(HWND), 4, 3)
// case WM_PAINT:
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 512)
//	unique<GLRC>.swap( )
// case WM_DESTROY:
//	unique<GLRC> = GLRC( )
struct GLRC {
	~
	GLRC(void);
	GLRC(void); // ctor
	GLRC(HDC OWNDC, int MAJOR, int MINOR); // ctor
	GLRC & operator = (GLRC &&)noexcept ;
	operator HGLRC(void)const ;
	void swap(void);
private :
	HGLRC RC = nullptr ;
public: // SwapBuffers(HDC)
	HDC DC = nullptr ;
};

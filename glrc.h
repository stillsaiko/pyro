# pragma once
# include "wnd.h"
# include <gl/glew.h> // just for youser
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

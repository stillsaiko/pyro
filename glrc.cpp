# include "glrc.h"
# include <gl/wglew.h>
# include <cstdio>
# include <cassert>
// decl
/*struct GLEW {
	HGLRC RC = nullptr ;
	HDC DC = nullptr ;
public : // T
	static constexpr unsigned int CS = CS_HREDRAW | CS_VREDRAW | CS_OWNDC ;
	static long __stdcall WNDPROC(HWND, unsigned int, unsigned int, long);
	static constexpr unsigned int WS_EX = WS_EX_TOOLWINDOW ;
	static constexpr unsigned int WS = WS_OVERLAPPED ;//| WS_VISIBLE ;
};
// impl
long __stdcall GLEW ::
WNDPROC(HWND WND, unsigned int WM, unsigned int W, long L){
	return DefWindowProc(WND, WM, W, L);
}*/
GLRC :: ~
GLRC(void){
	if(DC && RC){
		printf("warning: GLRC (destructor)\n");
		assert(wglMakeCurrent(DC, NULL));
		assert(wglDeleteContext(RC));
	}
}
// ...
GLRC ::
GLRC(void){ } // ctor
// ...
/*namespace PFD {
	enum {
	// dwFlags
		DRAW_TO_WINDOW	= PFD_DRAW_TO_WINDOW,
		SUPPORT_OPENGL	= PFD_SUPPORT_OPENGL,
		DOUBLEBUFFER	= PFD_DOUBLEBUFFER,
	// iPixelType
		TYPE_RGBA		= PFD_TYPE_RGBA,
	// iLayerType
		MAIN_PLANE		= PFD_MAIN_PLANE
	};
}*/
LRESULT WINAPI WPGL(HWND H, UINT M, WPARAM W, LPARAM L){
	return DefWindowProc(H, M, W, L);
}
// ...
GLRC ::
GLRC(HDC OWNDC, int MAJOR, int MINOR){
	assert( DC = OWNDC );
	{
		WNDCLASSA WCGL {
			CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
			WPGL, 0, 0,
			GetModuleHandle(NULL),
			(HICON)NULL,
			(HCURSOR)LoadCursorA(NULL, IDC_HAND),
			(HBRUSH)GetStockObject(GRAY_BRUSH),
			(LPCSTR)nullptr,
			"GLEW"
		};
		assert(!GetClassInfoA(WCGL.hInstance, WCGL.lpszClassName, &WCGL));
		assert(RegisterClassA(&WCGL));
		HWND WGL = CreateWindowExA(
			WS_EX_TOOLWINDOW,
			WCGL.lpszClassName,
			"glew",
			WS_OVERLAPPED,//| WS_VISIBLE
			(int)CW_USEDEFAULT,
			(int)CW_USEDEFAULT,
			(int)CW_USEDEFAULT,
			(int)CW_USEDEFAULT,
			(HWND)NULL,
			(HMENU)NULL,
			WCGL.hInstance,
			nullptr
		);
		assert(WGL);
//		using namespace PFD ;
		PIXELFORMATDESCRIPTOR PFD[1] {0};
		PFD->nSize = sizeof PFD ;
		PFD->nVersion = 1u ;
		PFD->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER ;
		PFD->iPixelType = PFD_TYPE_RGBA ;
		PFD->cColorBits = 32u ;
		// ::::: :.
		PFD->cDepthBits = 24u ;
		PFD->cStencilBits = 8u ;
		// .
		PFD->iLayerType = PFD_MAIN_PLANE ;
		// ::
		HDC DC ;
		assert( DC = GetDC(WGL) );
		int format ;
		assert( format = ChoosePixelFormat(DC, PFD) );
		assert( SetPixelFormat(DC, format, PFD) );
		assert( RC = wglCreateContext(DC) );
		assert( wglMakeCurrent(DC, RC) );
		{
			GLint i[1];
			glGetIntegerv(GL_MAJOR_VERSION, i); printf("OpenGL %i.", i[0]);
			glGetIntegerv(GL_MINOR_VERSION, i); printf(       "%i ", i[0]);
			glGetIntegerv(GL_CONTEXT_PROFILE_MASK, i);
			if( i[0] == GL_CONTEXT_CORE_PROFILE_BIT )
				printf("GL_CONTEXT_CORE_PROFILE_BIT\n");
			if( i[0] == GL_CONTEXT_COMPATIBILITY_PROFILE_BIT )
				printf("GL_CONTEXT_COMPATIBILITY_PROFILE_BIT\n");
		}
		glewExperimental = GL_TRUE ;
		assert( glewInit( ) == GLEW_OK );
		ShowWindow(WGL, SW_SHOW);
		Sleep(400); // zzZZ
		assert( DestroyWindow(WGL) );
		assert( UnregisterClassA(WCGL.lpszClassName, WCGL.hInstance) );
	}
	{
		int iPixelFormat[1];
		{
			GLuint nNumFormats[1];
			GLint piAttribIList[ ]{
			/*	WGL_SAMPLE_BUFFERS_ARB,	GL_TRUE,
				WGL_SAMPLES_ARB,		8,*/
				WGL_ACCELERATION_ARB,	WGL_FULL_ACCELERATION_ARB, // GENERIC NO
				WGL_SUPPORT_OPENGL_ARB,	GL_TRUE,
				WGL_DRAW_TO_WINDOW_ARB,	GL_TRUE,
				WGL_DOUBLE_BUFFER_ARB,	GL_TRUE,
				WGL_SWAP_METHOD_ARB,	WGL_SWAP_UNDEFINED_ARB, //EXCHANGE, COPY, UNDEFINED
				WGL_PIXEL_TYPE_ARB,		WGL_TYPE_RGBA_ARB, // COLORINDEX
				WGL_COLOR_BITS_ARB,		32,
				WGL_DEPTH_BITS_ARB,		24,
				WGL_STENCIL_BITS_ARB,	8,
				0
			};
			assert( wglChoosePixelFormatARB(DC, piAttribIList, nullptr, 1, iPixelFormat, nNumFormats) );
		}
		PIXELFORMATDESCRIPTOR PFD[1] {0};
		assert( DescribePixelFormat(DC, iPixelFormat[0], sizeof PFD, PFD) );
		assert( SetPixelFormat(DC, iPixelFormat[0], PFD) );
	}
	const GLint attribList[ ]{
		WGL_CONTEXT_MAJOR_VERSION_ARB,	MAJOR,
		WGL_CONTEXT_MINOR_VERSION_ARB,	MINOR,
		WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // COMPATIBILITY_PROFILE_BIT
		WGL_CONTEXT_FLAGS_ARB,			WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,// DEBUG_BIT
		0
	};
	assert( RC = wglCreateContextAttribsARB(DC, nullptr, attribList) );
	assert( wglMakeCurrent(DC, RC) );
	/*{
		GLint num ;
		glGetIntegerv(GL_NUM_EXTENSIONS, &num);
		printf("GL_EXTENSIONS:\n");
		for(GLint i(0); i < num; ++i)
			printf(" + %s\n", glGetStringi(GL_EXTENSIONS, i));
		printf("\n");
	}*/
	{
		GLint i[1];
		glGetIntegerv(GL_SAMPLES, i); printf("GL_SAMPLES/GL_MAX_SAMPLES %i", i[0]);
		glGetIntegerv(GL_MAX_SAMPLES, i); printf("/%i\n", i[0]);
		printf(" \n");
		glGetIntegerv(GL_MAJOR_VERSION, i); printf("OpenGL %i.", i[0]);
		glGetIntegerv(GL_MINOR_VERSION, i); printf(       "%i ", i[0]);
		glGetIntegerv(GL_CONTEXT_PROFILE_MASK, i);
		if( i[0] == GL_CONTEXT_CORE_PROFILE_BIT )
			printf("GL_CONTEXT_CORE_PROFILE_BIT\n");
		if( i[0] == GL_CONTEXT_COMPATIBILITY_PROFILE_BIT )
			printf("GL_CONTEXT_COMPATIBILITY_PROFILE_BIT\n");
	}
}
GLRC& GLRC::operator = (GLRC&& a)noexcept {
	if(RC){
		if( wglGetCurrentContext( ) == RC && DC )
			wglMakeCurrent(DC, NULL);
		wglDeleteContext(RC);
	}
	RC = a.RC ; a.RC = NULL ;
	DC = a.DC ; a.DC = NULL ;
	return * this ;
}
GLRC::operator HGLRC(void)const {
	return RC ;
}
void GLRC::swap(void){
	assert(SwapBuffers(DC));
}
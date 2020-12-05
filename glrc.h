# pragma once
// openGL Render Context
# ifdef _WIN32 // windows
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <gl/gl.h>
# endif
// include "wnd.h"
// include <gl/glew.h> // just for youser
// case WM_CREATE:
//	unique<GLRC> = GLRC(GetDC(HWND), 4, 3)
// case WM_PAINT:
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 512)
//	SwapBuffers(unique<GLRC>)
// case WM_DESTROY:
//	unique<GLRC> = GLRC( )
struct GLRC
{
	~
	GLRC(void)noexcept; // dtor
	GLRC(void); // ctor
	GLRC(HDC OWNDC, int MAJOR, int MINOR); // ctor
	void operator =(GLRC &&)noexcept; // move
	operator HDC(void)const;
private:
	HGLRC HGLRC = NULL;
	HDC HDC = NULL;
};

# ifndef WGL_ARB_extensions_string
extern const char *(WINAPI*wglGetExtensionsString)(HDC);
# endif

# ifndef WGL_ARB_create_context
constexpr GLbitfield WGL_CONTEXT_DEBUG_BIT              = 0x00000001;
constexpr GLbitfield WGL_CONTEXT_FORWARD_COMPATIBLE_BIT = 0x00000002;
enum WGL_ARB_create_context : int
{
	WGL_CONTEXT_MAJOR_VERSION = 0x2091,
	WGL_CONTEXT_MINOR_VERSION = 0x2092,
	WGL_CONTEXT_LAYER_PLANE   = 0x2093,
	WGL_CONTEXT_FLAGS         = 0x2094,
	ERROR_INVALID_VERSION     = 0x2095
};
extern HGLRC (WINAPI*wglCreateContextAttribs)(HDC, HGLRC, const int *);
# endif

# ifndef WGL_ARB_create_context_profile
constexpr GLbitfield WGL_CONTEXT_CORE_PROFILE_BIT          = 0x00000001;
constexpr GLbitfield WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT = 0x00000002;
enum WGL_ARB_create_context_profile : int
{
	WGL_CONTEXT_PROFILE_MASK = 0x9126,
//	ERROR_INVALID_PROFILE    = 0x2096
};
# endif

# ifndef WGL_ARB_multisample
enum WGL_ARB_multisample : int
{
	WGL_SAMPLE_BUFFERS = 0x2041,
	WGL_SAMPLES        = 0x2042
};
# endif

# ifndef WGL_ARB_pixel_format
enum WGL_ARB_pixel_format : int
{
	WGL_NUMBER_PIXEL_FORMATS    = 0x2000,
	WGL_DRAW_TO_WINDOW          = 0x2001,
	WGL_DRAW_TO_BITMAP          = 0x2002,
	WGL_ACCELERATION            = 0x2003,
	WGL_NEED_PALETTE            = 0x2004,
	WGL_NEED_SYSTEM_PALETTE     = 0x2005,
	WGL_SWAP_LAYER_BUFFERS      = 0x2006,
	WGL_SWAP_METHOD             = 0x2007,
	WGL_NUMBER_OVERLAYS         = 0x2008,
	WGL_NUMBER_UNDERLAYS        = 0x2009,
	WGL_TRANSPARENT             = 0x200A,
	WGL_TRANSPARENT_RED_VALUE   = 0x2037,
	WGL_TRANSPARENT_GREEN_VALUE = 0x2038,
	WGL_TRANSPARENT_BLUE_VALUE  = 0x2039,
	WGL_TRANSPARENT_ALPHA_VALUE = 0x203A,
	WGL_TRANSPARENT_INDEX_VALUE = 0x203B,
	WGL_SHARE_DEPTH             = 0x200C,
	WGL_SHARE_STENCIL           = 0x200D,
	WGL_SHARE_ACCUM             = 0x200E,
	WGL_SUPPORT_GDI             = 0x200F,
	WGL_SUPPORT_OPENGL          = 0x2010,
	WGL_DOUBLE_BUFFER           = 0x2011,
	WGL_STEREO                  = 0x2012,
	WGL_PIXEL_TYPE              = 0x2013,
	WGL_COLOR_BITS              = 0x2014,
	WGL_RED_BITS                = 0x2015,
	WGL_RED_SHIFT               = 0x2016,
	WGL_GREEN_BITS              = 0x2017,
	WGL_GREEN_SHIFT             = 0x2018,
	WGL_BLUE_BITS               = 0x2019,
	WGL_BLUE_SHIFT              = 0x201A,
	WGL_ALPHA_BITS              = 0x201B,
	WGL_ALPHA_SHIFT             = 0x201C,
	WGL_ACCUM_BITS              = 0x201D,
	WGL_ACCUM_RED_BITS          = 0x201E,
	WGL_ACCUM_GREEN_BITS        = 0x201F,
	WGL_ACCUM_BLUE_BITS         = 0x2020,
	WGL_ACCUM_ALPHA_BITS        = 0x2021,
	WGL_DEPTH_BITS              = 0x2022,
	WGL_STENCIL_BITS            = 0x2023,
	WGL_AUX_BUFFERS             = 0x2024,
	WGL_NO_ACCELERATION         = 0x2025,
	WGL_GENERIC_ACCELERATION    = 0x2026,
	WGL_FULL_ACCELERATION       = 0x2027,
	WGL_SWAP_EXCHANGE           = 0x2028,
	WGL_SWAP_COPY               = 0x2029,
	WGL_SWAP_UNDEFINED          = 0x202A,
	WGL_TYPE_RGBA               = 0x202B,
	WGL_TYPE_COLORINDEX         = 0x202C
};
extern BOOL (WINAPI*wglGetPixelFormatAttribiv)(HDC, int, int, UINT, const int *, int *);
extern BOOL (WINAPI*wglGetPixelFormatAttribfv)(HDC, int, int, UINT, const int *, FLOAT *);
extern BOOL (WINAPI*wglChoosePixelFormat)(HDC, const int *, const FLOAT *, UINT, int *, UINT *);
# endif
# include "glrc.h"
# include "gl.h"
void *glGetProcAddress(const char *lpProcName)
{
# ifdef _WIN32 // WGL
	return static_cast<void *>(wglGetProcAddress(lpProcName));
# else // GLX
	return glXGetProcAddressARB((const GLubyte *) lpProcName);
# endif
}
# include "error.h"
GLRC::~ GLRC(void)noexcept
{
	constexpr decltype(HGLRC) (*glGetCurrentContext)(void) = [ ](void)
	{
	# ifdef _WIN32 // WGL
		return wglGetCurrentContext( );
	# else // GLX
		return glXGetCurrentContext( );
	# endif
	};
	if(HGLRC == NULL)return;
	if(HGLRC == glGetCurrentContext( ))
	ASSERT(wglMakeCurrent(HDC, NULL));
	ASSERT(wglDeleteContext(HGLRC));
	HGLRC = NULL;
}
GLRC::GLRC(void)
{ }
# include <cstdio> // printf
GLRC::GLRC(::HDC OWNDC, INT MAJOR, INT MINOR)
{
	{
		WNDCLASSA
		WNDCLASSA
		{
			CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
			[ ](HWND H, UINT M, WPARAM W, LPARAM L)
			{ return DefWindowProcA(H, M, W, L); },
			0, 0, GetModuleHandleA(NULL),
			(HICON)NULL,
			(HCURSOR)LoadCursorA(NULL, IDC_HAND),
			(HBRUSH)GetStockObject(GRAY_BRUSH),
			(LPCSTR)nullptr, "WGL"
		};
		ASSERT(!GetClassInfoA(WNDCLASSA.hInstance, WNDCLASSA.lpszClassName, &WNDCLASSA));
		if(!ASSERT(RegisterClassA(&WNDCLASSA))) return;
	}
	if(HWND CreateWindowExA = ::CreateWindowExA(WS_EX_TOOLWINDOW, "WGL", NULL, WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, (HWND)NULL, (HMENU)NULL, GetModuleHandleA(NULL), NULL); ASSERT(CreateWindowExA))
	{
		PIXELFORMATDESCRIPTOR
		PIXELFORMATDESCRIPTOR {0};
		PIXELFORMATDESCRIPTOR.nSize = sizeof PIXELFORMATDESCRIPTOR;
		PIXELFORMATDESCRIPTOR.nVersion = 1;
		PIXELFORMATDESCRIPTOR.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		PIXELFORMATDESCRIPTOR.iPixelType = PFD_TYPE_RGBA;
		PIXELFORMATDESCRIPTOR.cColorBits = 32;
		// ::::: :.
		PIXELFORMATDESCRIPTOR.cDepthBits = 24;
		PIXELFORMATDESCRIPTOR.cStencilBits = 8;
		// .
		PIXELFORMATDESCRIPTOR.iLayerType = PFD_MAIN_PLANE;
		// ::
		if(ASSERT(HDC = GetDC(CreateWindowExA)))
		if(int ChoosePixelFormat = ::ChoosePixelFormat(HDC, &PIXELFORMATDESCRIPTOR); ASSERT(ChoosePixelFormat))
		if(ASSERT(SetPixelFormat(HDC, ChoosePixelFormat, &PIXELFORMATDESCRIPTOR)))
		if(ASSERT(HGLRC = wglCreateContext(HDC)))
		{
			if(ASSERT(wglMakeCurrent(HDC, HGLRC)))

		# ifndef WGL_ARB_extensions_string
			wglGetExtensionsString = (decltype(wglGetExtensionsString)) glGetProcAddress("wglGetExtensionsStringARB"), ASSERT(wglGetExtensionsString),
		# endif

		# ifndef WGL_ARB_create_context
			wglCreateContextAttribs = (decltype(wglCreateContextAttribs)) glGetProcAddress("wglCreateContextAttribsARB"), ASSERT(wglCreateContextAttribs),
		# endif

		# ifndef WGL_ARB_pixel_format
			wglGetPixelFormatAttribiv = (decltype(wglGetPixelFormatAttribiv)) glGetProcAddress("wglGetPixelFormatAttribivARB"), ASSERT(wglGetPixelFormatAttribiv),
			wglGetPixelFormatAttribfv = (decltype(wglGetPixelFormatAttribfv)) glGetProcAddress("wglGetPixelFormatAttribfvARB"), ASSERT(wglGetPixelFormatAttribfv),
			wglChoosePixelFormat = (decltype(wglChoosePixelFormat)) glGetProcAddress("wglChoosePixelFormatARB"), ASSERT(wglChoosePixelFormat),
		# endif
			ASSERT(wglMakeCurrent(HDC, NULL)), HDC = NULL;
			ASSERT(wglDeleteContext(HGLRC)), HGLRC = NULL;
		}
		ASSERT(DestroyWindow(CreateWindowExA));
	}
	ASSERT(UnregisterClassA("WGL", GetModuleHandleA(NULL)));

	if(!ASSERT(HDC = OWNDC)) return;
	// WGL_ARB_create_context
	constexpr int piAttribIList[ ]
	{
	// WGL_ARB_pixel_format
	# ifdef _WIN32 // WGL
		WGL_DRAW_TO_WINDOW,	GL_TRUE,
	//	WGL_ACCELERATION,	WGL_FULL_ACCELERATION, // WGL_GENERIC_ACCELERATION, WGL_NO_ACCELERATION
	//	WGL_SWAP_METHOD,	WGL_SWAP_UNDEFINED, // WGL_SWAP_COPY, WGL_SWAP_EXCHANGE
		WGL_SUPPORT_OPENGL,	GL_TRUE,
		WGL_DOUBLE_BUFFER,	GL_TRUE,
		WGL_PIXEL_TYPE,		WGL_TYPE_RGBA, // WGL_TYPE_COLORINDEX
		WGL_COLOR_BITS,		32,
		WGL_DEPTH_BITS, 	24,
		WGL_STENCIL_BITS,	8,
	# else // GLX
		GLX_DRAWABLE_TYPE,	GLX_WINDOW_BIT,
		GLX_X_RENDERABLE,	True,
		GLX_USE_GL
		GLX_DOUBLEBUFFER,	True,
		GLX_RENDER_TYPE,	GLX_RGBA_BIT, // GLX_COLOR_INDEX_BIT
		GLX_X_VISUAL_TYPE,	GLX_TRUE_COLOR,
		GLX_DEPTH_SIZE,		24,
		GLX_STENCIL_SIZE,	8,
	# endif
	// WGL_ARB_multisample
/*	# ifdef _WIN32
		WGL_SAMPLE_BUFFERS,	GL_TRUE,
		WGL_SAMPLES,		4
	# else
		GLX_SAMPLE_BUFFERS,	GL_TRUE,
		GLX_SAMPLES,		4,
	# endif
*/		0 // null-terminated
	};
# ifdef _WIN32
	int iPixelFormat;
	UINT nNumFormats;
	PIXELFORMATDESCRIPTOR
	PIXELFORMATDESCRIPTOR {0};
	const int WGL_CONTEXT[8+1] // WGL_CONTEXT_PROFILE_MASK=WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT, WGL_CONTEXT_FLAGS=WGL_CONTEXT_DEBUG_BIT
	{
		WGL_CONTEXT_MAJOR_VERSION,	MAJOR,
		WGL_CONTEXT_MINOR_VERSION,	MINOR,
		WGL_CONTEXT_PROFILE_MASK,	WGL_CONTEXT_CORE_PROFILE_BIT,
		WGL_CONTEXT_FLAGS,		WGL_CONTEXT_FORWARD_COMPATIBLE_BIT
	};
	if(ASSERT(wglChoosePixelFormat(HDC, piAttribIList, nullptr, 1, &iPixelFormat, &nNumFormats)))
	if(int DescribePixelFormat = ::DescribePixelFormat(HDC, iPixelFormat, sizeof PIXELFORMATDESCRIPTOR, &PIXELFORMATDESCRIPTOR); ASSERT(DescribePixelFormat))
	if(BOOL SetPixelFormat = ::SetPixelFormat(HDC, iPixelFormat, &PIXELFORMATDESCRIPTOR); ASSERT(SetPixelFormat))
	if(ASSERT(HGLRC = wglCreateContextAttribs(HDC, nullptr, WGL_CONTEXT)))
	if(ASSERT(wglMakeCurrent(HDC, HGLRC)))
# else
	if(XVisualInfo *glXChooseVisual = ::glXChooseVisual(HMONITOR, XDefaultScreen(HMONITOR), piAttribIList); ASSERT(glXChooseVisual))
	if(Colormap XCreateColormap = ::XCreateColormap(HDC, RootWindow(HDC, glXChooseVisual->screen), glXChooseVisual->visual, AllocNone); ASSERT(XCreateColormap))

	
	int N;
	if(GLXFBConfig* glXChooseFBConfig = ::glXChooseFBConfig(HDC, DefaultScreen(HDC), piAttribIList, &N; ASSERT(glXChooseFBConfig))
	if(XVisualInfo *glXGetVisualFromFBConfig = ::glXGetVisualFromFBConfig(display, glXChooseFBConfig[0]); ASSERT(glXGetVisualFromFBConfig))
	if(Colormap XCreateColormap = ::XCreateColormap(HDC, RootWindow(HDC,	glXGetVisualFromFBConfig->screen),
										glXGetVisualFromFBConfig->visual, AllocNone); ASSERT(XCreateColormap))
	
	XFree(glXChooseFBConfig);
	XFree(glXGetVisualFromFBConfig);
# endif
	switch(gl_Version = MAJOR << 3 | MINOR)
	{
	# ifndef GL_VERSION_4_6
		case 046:
		glSpecializeShader = (void (__stdcall*)(GLuint, const GLchar *, GLuint, const GLuint *, const GLuint *)) glGetProcAddress("glSpecializeShader"), ASSERT(glSpecializeShader),
		glMultiDrawArraysIndirectCount = (void (__stdcall*)(GLenum, const void *, GLintptr, GLsizei, GLsizei)) glGetProcAddress("glMultiDrawArraysIndirectCount"), ASSERT(glMultiDrawArraysIndirectCount),
		glMultiDrawElementsIndirectCount = (void (__stdcall*)(GLenum, GLenum, const void *, GLintptr, GLsizei, GLsizei)) glGetProcAddress("glMultiDrawElementsIndirectCount"), ASSERT(glMultiDrawElementsIndirectCount),
		glPolygonOffsetClamp = (void (__stdcall*)(GLfloat, GLfloat, GLfloat)) glGetProcAddress("glPolygonOffsetClamp"), ASSERT(glPolygonOffsetClamp);
	# ifndef GL_VERSION_4_5
		case 045:
		glClipControl = (void (__stdcall*)(GLenum, GLenum)) glGetProcAddress("glClipControl"), ASSERT(glClipControl),
		glCreateTransformFeedbacks = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glCreateTransformFeedbacks"), ASSERT(glCreateTransformFeedbacks),
		glTransformFeedbackBufferBase = (void (__stdcall*)(GLuint, GLuint, GLuint)) glGetProcAddress("glTransformFeedbackBufferBase"), ASSERT(glTransformFeedbackBufferBase),
		glTransformFeedbackBufferRange = (void (__stdcall*)(GLuint, GLuint, GLuint, GLintptr, GLsizeiptr)) glGetProcAddress("glTransformFeedbackBufferRange"), ASSERT(glTransformFeedbackBufferRange),
		glGetTransformFeedbackiv = (void (__stdcall*)(GLuint, GLenum, GLint *)) glGetProcAddress("glGetTransformFeedbackiv"), ASSERT(glGetTransformFeedbackiv),
		glGetTransformFeedbacki_v = (void (__stdcall*)(GLuint, GLenum, GLuint, GLint *)) glGetProcAddress("glGetTransformFeedbacki_v"), ASSERT(glGetTransformFeedbacki_v),
		glGetTransformFeedbacki64_v = (void (__stdcall*)(GLuint, GLenum, GLuint, GLint64 *)) glGetProcAddress("glGetTransformFeedbacki64_v"), ASSERT(glGetTransformFeedbacki64_v),
		glCreateBuffers = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glCreateBuffers"), ASSERT(glCreateBuffers),
		glNamedBufferStorage = (void (__stdcall*)(GLuint, GLsizeiptr, const void *, GLbitfield)) glGetProcAddress("glNamedBufferStorage"), ASSERT(glNamedBufferStorage),
		glNamedBufferData = (void (__stdcall*)(GLuint, GLsizeiptr, const void *, GLenum)) glGetProcAddress("glNamedBufferData"), ASSERT(glNamedBufferData),
		glNamedBufferSubData = (void (__stdcall*)(GLuint, GLintptr, GLsizeiptr, const void *)) glGetProcAddress("glNamedBufferSubData"), ASSERT(glNamedBufferSubData),
		glCopyNamedBufferSubData = (void (__stdcall*)(GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr)) glGetProcAddress("glCopyNamedBufferSubData"), ASSERT(glCopyNamedBufferSubData),
		glClearNamedBufferData = (void (__stdcall*)(GLuint, GLenum, GLenum, GLenum, const void *)) glGetProcAddress("glClearNamedBufferData"), ASSERT(glClearNamedBufferData),
		glClearNamedBufferSubData = (void (__stdcall*)(GLuint, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *)) glGetProcAddress("glClearNamedBufferSubData"), ASSERT(glClearNamedBufferSubData),
		glMapNamedBuffer = (void *(__stdcall*)(GLuint, GLenum)) glGetProcAddress("glMapNamedBuffer"), ASSERT(glMapNamedBuffer),
		glMapNamedBufferRange = (void *(__stdcall*)(GLuint, GLintptr, GLsizeiptr, GLbitfield)) glGetProcAddress("glMapNamedBufferRange"), ASSERT(glMapNamedBufferRange),
		glUnmapNamedBuffer = (GLboolean (__stdcall*)(GLuint)) glGetProcAddress("glUnmapNamedBuffer"), ASSERT(glUnmapNamedBuffer),
		glFlushMappedNamedBufferRange = (void (__stdcall*)(GLuint, GLintptr, GLsizeiptr)) glGetProcAddress("glFlushMappedNamedBufferRange"), ASSERT(glFlushMappedNamedBufferRange),
		glGetNamedBufferParameteriv = (void (__stdcall*)(GLuint, GLenum, GLint *)) glGetProcAddress("glGetNamedBufferParameteriv"), ASSERT(glGetNamedBufferParameteriv),
		glGetNamedBufferParameteri64v = (void (__stdcall*)(GLuint, GLenum, GLint64 *)) glGetProcAddress("glGetNamedBufferParameteri64v"), ASSERT(glGetNamedBufferParameteri64v),
		glGetNamedBufferPointerv = (void (__stdcall*)(GLuint, GLenum, void **)) glGetProcAddress("glGetNamedBufferPointerv"), ASSERT(glGetNamedBufferPointerv),
		glGetNamedBufferSubData = (void (__stdcall*)(GLuint, GLintptr, GLsizeiptr, void *)) glGetProcAddress("glGetNamedBufferSubData"), ASSERT(glGetNamedBufferSubData),
		glCreateFramebuffers = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glCreateFramebuffers"), ASSERT(glCreateFramebuffers),
		glNamedFramebufferRenderbuffer = (void (__stdcall*)(GLuint, GLenum, GLenum, GLuint)) glGetProcAddress("glNamedFramebufferRenderbuffer"), ASSERT(glNamedFramebufferRenderbuffer),
		glNamedFramebufferParameteri = (void (__stdcall*)(GLuint, GLenum, GLint)) glGetProcAddress("glNamedFramebufferParameteri"), ASSERT(glNamedFramebufferParameteri),
		glNamedFramebufferTexture = (void (__stdcall*)(GLuint, GLenum, GLuint, GLint)) glGetProcAddress("glNamedFramebufferTexture"), ASSERT(glNamedFramebufferTexture),
		glNamedFramebufferTextureLayer = (void (__stdcall*)(GLuint, GLenum, GLuint, GLint, GLint)) glGetProcAddress("glNamedFramebufferTextureLayer"), ASSERT(glNamedFramebufferTextureLayer),
		glNamedFramebufferDrawBuffer = (void (__stdcall*)(GLuint, GLenum)) glGetProcAddress("glNamedFramebufferDrawBuffer"), ASSERT(glNamedFramebufferDrawBuffer),
		glNamedFramebufferDrawBuffers = (void (__stdcall*)(GLuint, GLsizei, const GLenum *)) glGetProcAddress("glNamedFramebufferDrawBuffers"), ASSERT(glNamedFramebufferDrawBuffers),
		glNamedFramebufferReadBuffer = (void (__stdcall*)(GLuint, GLenum)) glGetProcAddress("glNamedFramebufferReadBuffer"), ASSERT(glNamedFramebufferReadBuffer),
		glInvalidateNamedFramebufferData = (void (__stdcall*)(GLuint, GLsizei, const GLenum *)) glGetProcAddress("glInvalidateNamedFramebufferData"), ASSERT(glInvalidateNamedFramebufferData),
		glInvalidateNamedFramebufferSubData = (void (__stdcall*)(GLuint, GLsizei, const GLenum *, GLint x, GLint y, GLsizei, GLsizei)) glGetProcAddress("glInvalidateNamedFramebufferSubData"), ASSERT(glInvalidateNamedFramebufferSubData),
		glClearNamedFramebufferiv = (void (__stdcall*)(GLuint, GLenum, GLint, const GLint *)) glGetProcAddress("glClearNamedFramebufferiv"), ASSERT(glClearNamedFramebufferiv),
		glClearNamedFramebufferuiv = (void (__stdcall*)(GLuint, GLenum, GLint, const GLuint *)) glGetProcAddress("glClearNamedFramebufferuiv"), ASSERT(glClearNamedFramebufferuiv),
		glClearNamedFramebufferfv = (void (__stdcall*)(GLuint, GLenum, GLint, const GLfloat *)) glGetProcAddress("glClearNamedFramebufferfv"), ASSERT(glClearNamedFramebufferfv),
		glClearNamedFramebufferfi = (void (__stdcall*)(GLuint, GLenum, GLint, GLfloat, GLint)) glGetProcAddress("glClearNamedFramebufferfi"), ASSERT(glClearNamedFramebufferfi),
		glBlitNamedFramebuffer = (void (__stdcall*)(GLuint, GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum)) glGetProcAddress("glBlitNamedFramebuffer"), ASSERT(glBlitNamedFramebuffer),
		glCheckNamedFramebufferStatus = (GLenum (__stdcall*)(GLuint, GLenum)) glGetProcAddress("glCheckNamedFramebufferStatus"), ASSERT(glCheckNamedFramebufferStatus),
		glGetNamedFramebufferParameteriv = (void (__stdcall*)(GLuint, GLenum, GLint *)) glGetProcAddress("glGetNamedFramebufferParameteriv"), ASSERT(glGetNamedFramebufferParameteriv),
		glGetNamedFramebufferAttachmentParameteriv = (void (__stdcall*)(GLuint, GLenum, GLenum, GLint *)) glGetProcAddress("glGetNamedFramebufferAttachmentParameteriv"), ASSERT(glGetNamedFramebufferAttachmentParameteriv),
		glCreateRenderbuffers = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glCreateRenderbuffers"), ASSERT(glCreateRenderbuffers),
		glNamedRenderbufferStorage = (void (__stdcall*)(GLuint, GLenum, GLsizei, GLsizei)) glGetProcAddress("glNamedRenderbufferStorage"), ASSERT(glNamedRenderbufferStorage),
		glNamedRenderbufferStorageMultisample = (void (__stdcall*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei)) glGetProcAddress("glNamedRenderbufferStorageMultisample"), ASSERT(glNamedRenderbufferStorageMultisample),
		glGetNamedRenderbufferParameteriv = (void (__stdcall*)(GLuint, GLenum, GLint *)) glGetProcAddress("glGetNamedRenderbufferParameteriv"), ASSERT(glGetNamedRenderbufferParameteriv),
		glCreateTextures = (void (__stdcall*)(GLenum, GLsizei, GLuint *)) glGetProcAddress("glCreateTextures"), ASSERT(glCreateTextures),
		glTextureBuffer = (void (__stdcall*)(GLuint, GLenum, GLuint)) glGetProcAddress("glTextureBuffer"), ASSERT(glTextureBuffer),
		glTextureBufferRange = (void (__stdcall*)(GLuint, GLenum, GLuint, GLintptr, GLsizeiptr)) glGetProcAddress("glTextureBufferRange"), ASSERT(glTextureBufferRange),
		glTextureStorage1D = (void (__stdcall*)(GLuint, GLsizei, GLenum, GLsizei)) glGetProcAddress("glTextureStorage1D"), ASSERT(glTextureStorage1D),
		glTextureStorage2D = (void (__stdcall*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei)) glGetProcAddress("glTextureStorage2D"), ASSERT(glTextureStorage2D),
		glTextureStorage3D = (void (__stdcall*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei)) glGetProcAddress("glTextureStorage3D"), ASSERT(glTextureStorage3D),
		glTextureStorage2DMultisample = (void (__stdcall*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLboolean)) glGetProcAddress("glTextureStorage2DMultisample"), ASSERT(glTextureStorage2DMultisample),
		glTextureStorage3DMultisample = (void (__stdcall*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean)) glGetProcAddress("glTextureStorage3DMultisample"), ASSERT(glTextureStorage3DMultisample),
		glTextureSubImage1D = (void (__stdcall*)(GLuint, GLint, GLint, GLsizei, GLenum, GLenum, const void *)) glGetProcAddress("glTextureSubImage1D"), ASSERT(glTextureSubImage1D),
		glTextureSubImage2D = (void (__stdcall*)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *)) glGetProcAddress("glTextureSubImage2D"), ASSERT(glTextureSubImage2D),
		glTextureSubImage3D = (void (__stdcall*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *)) glGetProcAddress("glTextureSubImage3D"), ASSERT(glTextureSubImage3D),
		glCompressedTextureSubImage1D = (void (__stdcall*)(GLuint, GLint, GLint, GLsizei, GLenum, GLsizei, const void *)) glGetProcAddress("glCompressedTextureSubImage1D"), ASSERT(glCompressedTextureSubImage1D),
		glCompressedTextureSubImage2D = (void (__stdcall*)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *)) glGetProcAddress("glCompressedTextureSubImage2D"), ASSERT(glCompressedTextureSubImage2D),
		glCompressedTextureSubImage3D = (void (__stdcall*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *)) glGetProcAddress("glCompressedTextureSubImage3D"), ASSERT(glCompressedTextureSubImage3D),
		glCopyTextureSubImage1D = (void (__stdcall*)(GLuint, GLint, GLint, GLint x, GLint y, GLsizei)) glGetProcAddress("glCopyTextureSubImage1D"), ASSERT(glCopyTextureSubImage1D),
		glCopyTextureSubImage2D = (void (__stdcall*)(GLuint, GLint, GLint, GLint, GLint x, GLint y, GLsizei, GLsizei)) glGetProcAddress("glCopyTextureSubImage2D"), ASSERT(glCopyTextureSubImage2D),
		glCopyTextureSubImage3D = (void (__stdcall*)(GLuint, GLint, GLint, GLint, GLint, GLint x, GLint y, GLsizei, GLsizei)) glGetProcAddress("glCopyTextureSubImage3D"), ASSERT(glCopyTextureSubImage3D),
		glTextureParameterf = (void (__stdcall*)(GLuint, GLenum, GLfloat)) glGetProcAddress("glTextureParameterf"), ASSERT(glTextureParameterf),
		glTextureParameterfv = (void (__stdcall*)(GLuint, GLenum, const GLfloat *)) glGetProcAddress("glTextureParameterfv"), ASSERT(glTextureParameterfv),
		glTextureParameteri = (void (__stdcall*)(GLuint, GLenum, GLint)) glGetProcAddress("glTextureParameteri"), ASSERT(glTextureParameteri),
		glTextureParameterIiv = (void (__stdcall*)(GLuint, GLenum, const GLint *)) glGetProcAddress("glTextureParameterIiv"), ASSERT(glTextureParameterIiv),
		glTextureParameterIuiv = (void (__stdcall*)(GLuint, GLenum, const GLuint *)) glGetProcAddress("glTextureParameterIuiv"), ASSERT(glTextureParameterIuiv),
		glTextureParameteriv = (void (__stdcall*)(GLuint, GLenum, const GLint *)) glGetProcAddress("glTextureParameteriv"), ASSERT(glTextureParameteriv),
		glGenerateTextureMipmap = (void (__stdcall*)(GLuint)) glGetProcAddress("glGenerateTextureMipmap"), ASSERT(glGenerateTextureMipmap),
		glBindTextureUnit = (void (__stdcall*)(GLuint, GLuint)) glGetProcAddress("glBindTextureUnit"), ASSERT(glBindTextureUnit),
		glGetTextureImage = (void (__stdcall*)(GLuint, GLint, GLenum, GLenum, GLsizei, void *)) glGetProcAddress("glGetTextureImage"), ASSERT(glGetTextureImage),
		glGetCompressedTextureImage = (void (__stdcall*)(GLuint, GLint, GLsizei, void *)) glGetProcAddress("glGetCompressedTextureImage"), ASSERT(glGetCompressedTextureImage),
		glGetTextureLevelParameterfv = (void (__stdcall*)(GLuint, GLint, GLenum, GLfloat *)) glGetProcAddress("glGetTextureLevelParameterfv"), ASSERT(glGetTextureLevelParameterfv),
		glGetTextureLevelParameteriv = (void (__stdcall*)(GLuint, GLint, GLenum, GLint *)) glGetProcAddress("glGetTextureLevelParameteriv"), ASSERT(glGetTextureLevelParameteriv),
		glGetTextureParameterfv = (void (__stdcall*)(GLuint, GLenum, GLfloat *)) glGetProcAddress("glGetTextureParameterfv"), ASSERT(glGetTextureParameterfv),
		glGetTextureParameterIiv = (void (__stdcall*)(GLuint, GLenum, GLint *)) glGetProcAddress("glGetTextureParameterIiv"), ASSERT(glGetTextureParameterIiv),
		glGetTextureParameterIuiv = (void (__stdcall*)(GLuint, GLenum, GLuint *)) glGetProcAddress("glGetTextureParameterIuiv"), ASSERT(glGetTextureParameterIuiv),
		glGetTextureParameteriv = (void (__stdcall*)(GLuint, GLenum, GLint *)) glGetProcAddress("glGetTextureParameteriv"), ASSERT(glGetTextureParameteriv),
		glCreateVertexArrays = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glCreateVertexArrays"), ASSERT(glCreateVertexArrays),
		glDisableVertexArrayAttrib = (void (__stdcall*)(GLuint, GLuint)) glGetProcAddress("glDisableVertexArrayAttrib"), ASSERT(glDisableVertexArrayAttrib),
		glEnableVertexArrayAttrib = (void (__stdcall*)(GLuint, GLuint)) glGetProcAddress("glEnableVertexArrayAttrib"), ASSERT(glEnableVertexArrayAttrib),
		glVertexArrayElementBuffer = (void (__stdcall*)(GLuint, GLuint)) glGetProcAddress("glVertexArrayElementBuffer"), ASSERT(glVertexArrayElementBuffer),
		glVertexArrayVertexBuffer = (void (__stdcall*)(GLuint, GLuint, GLuint, GLintptr, GLsizei)) glGetProcAddress("glVertexArrayVertexBuffer"), ASSERT(glVertexArrayVertexBuffer),
		glVertexArrayVertexBuffers = (void (__stdcall*)(GLuint, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *)) glGetProcAddress("glVertexArrayVertexBuffers"), ASSERT(glVertexArrayVertexBuffers),
		glVertexArrayAttribBinding = (void (__stdcall*)(GLuint, GLuint, GLuint)) glGetProcAddress("glVertexArrayAttribBinding"), ASSERT(glVertexArrayAttribBinding),
		glVertexArrayAttribFormat = (void (__stdcall*)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint)) glGetProcAddress("glVertexArrayAttribFormat"), ASSERT(glVertexArrayAttribFormat),
		glVertexArrayAttribIFormat = (void (__stdcall*)(GLuint, GLuint, GLint, GLenum, GLuint)) glGetProcAddress("glVertexArrayAttribIFormat"), ASSERT(glVertexArrayAttribIFormat),
		glVertexArrayAttribLFormat = (void (__stdcall*)(GLuint, GLuint, GLint, GLenum, GLuint)) glGetProcAddress("glVertexArrayAttribLFormat"), ASSERT(glVertexArrayAttribLFormat),
		glVertexArrayBindingDivisor = (void (__stdcall*)(GLuint, GLuint, GLuint)) glGetProcAddress("glVertexArrayBindingDivisor"), ASSERT(glVertexArrayBindingDivisor),
		glGetVertexArrayiv = (void (__stdcall*)(GLuint, GLenum, GLint *)) glGetProcAddress("glGetVertexArrayiv"), ASSERT(glGetVertexArrayiv),
		glGetVertexArrayIndexediv = (void (__stdcall*)(GLuint, GLuint, GLenum, GLint *)) glGetProcAddress("glGetVertexArrayIndexediv"), ASSERT(glGetVertexArrayIndexediv),
		glGetVertexArrayIndexed64iv = (void (__stdcall*)(GLuint, GLuint, GLenum, GLint64 *)) glGetProcAddress("glGetVertexArrayIndexed64iv"), ASSERT(glGetVertexArrayIndexed64iv),
		glCreateSamplers = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glCreateSamplers"), ASSERT(glCreateSamplers),
		glCreateProgramPipelines = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glCreateProgramPipelines"), ASSERT(glCreateProgramPipelines),
		glCreateQueries = (void (__stdcall*)(GLenum, GLsizei, GLuint *)) glGetProcAddress("glCreateQueries"), ASSERT(glCreateQueries),
		glGetQueryBufferObjecti64v = (void (__stdcall*)(GLuint, GLuint, GLenum, GLintptr)) glGetProcAddress("glGetQueryBufferObjecti64v"), ASSERT(glGetQueryBufferObjecti64v),
		glGetQueryBufferObjectiv = (void (__stdcall*)(GLuint, GLuint, GLenum, GLintptr)) glGetProcAddress("glGetQueryBufferObjectiv"), ASSERT(glGetQueryBufferObjectiv),
		glGetQueryBufferObjectui64v = (void (__stdcall*)(GLuint, GLuint, GLenum, GLintptr)) glGetProcAddress("glGetQueryBufferObjectui64v"), ASSERT(glGetQueryBufferObjectui64v),
		glGetQueryBufferObjectuiv = (void (__stdcall*)(GLuint, GLuint, GLenum, GLintptr)) glGetProcAddress("glGetQueryBufferObjectuiv"), ASSERT(glGetQueryBufferObjectuiv),
		glMemoryBarrierByRegion = (void (__stdcall*)(GLbitfield)) glGetProcAddress("glMemoryBarrierByRegion"), ASSERT(glMemoryBarrierByRegion),
		glGetTextureSubImage = (void (__stdcall*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *)) glGetProcAddress("glGetTextureSubImage"), ASSERT(glGetTextureSubImage),
		glGetCompressedTextureSubImage = (void (__stdcall*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLsizei, void *)) glGetProcAddress("glGetCompressedTextureSubImage"), ASSERT(glGetCompressedTextureSubImage),
		glGetGraphicsResetStatus = (GLenum (__stdcall*)(void)) glGetProcAddress("glGetGraphicsResetStatus"), ASSERT(glGetGraphicsResetStatus),
		glGetnCompressedTexImage = (void (__stdcall*)(GLenum, GLint, GLsizei, void *)) glGetProcAddress("glGetnCompressedTexImage"), ASSERT(glGetnCompressedTexImage),
		glGetnTexImage = (void (__stdcall*)(GLenum, GLint, GLenum, GLenum, GLsizei, void *)) glGetProcAddress("glGetnTexImage"), ASSERT(glGetnTexImage),
		glGetnUniformdv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLdouble *)) glGetProcAddress("glGetnUniformdv"), ASSERT(glGetnUniformdv),
		glGetnUniformfv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLfloat *)) glGetProcAddress("glGetnUniformfv"), ASSERT(glGetnUniformfv),
		glGetnUniformiv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLint *)) glGetProcAddress("glGetnUniformiv"), ASSERT(glGetnUniformiv),
		glGetnUniformuiv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLuint *)) glGetProcAddress("glGetnUniformuiv"), ASSERT(glGetnUniformuiv),
		glReadnPixels = (void (__stdcall*)(GLint x, GLint y, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *)) glGetProcAddress("glReadnPixels"), ASSERT(glReadnPixels),
		glTextureBarrier = (void (__stdcall*)(void)) glGetProcAddress("glTextureBarrier"), ASSERT(glTextureBarrier);
	# ifndef GL_VERSION_4_4
		case 044:
		glBufferStorage = (void (__stdcall*)(GLenum, GLsizeiptr, const void *, GLbitfield)) glGetProcAddress("glBufferStorage"), ASSERT(glBufferStorage),
		glClearTexImage = (void (__stdcall*)(GLuint, GLint, GLenum, GLenum, const void *)) glGetProcAddress("glClearTexImage"), ASSERT(glClearTexImage),
		glClearTexSubImage = (void (__stdcall*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *)) glGetProcAddress("glClearTexSubImage"), ASSERT(glClearTexSubImage),
		glBindBuffersBase = (void (__stdcall*)(GLenum, GLuint, GLsizei, const GLuint *)) glGetProcAddress("glBindBuffersBase"), ASSERT(glBindBuffersBase),
		glBindBuffersRange = (void (__stdcall*)(GLenum, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizeiptr *)) glGetProcAddress("glBindBuffersRange"), ASSERT(glBindBuffersRange),
		glBindTextures = (void (__stdcall*)(GLuint, GLsizei, const GLuint *)) glGetProcAddress("glBindTextures"), ASSERT(glBindTextures),
		glBindSamplers = (void (__stdcall*)(GLuint, GLsizei, const GLuint *)) glGetProcAddress("glBindSamplers"), ASSERT(glBindSamplers),
		glBindImageTextures = (void (__stdcall*)(GLuint, GLsizei, const GLuint *)) glGetProcAddress("glBindImageTextures"), ASSERT(glBindImageTextures),
		glBindVertexBuffers = (void (__stdcall*)(GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *)) glGetProcAddress("glBindVertexBuffers"), ASSERT(glBindVertexBuffers);
	# ifndef GL_VERSION_4_3
		case 043:
		glClearBufferData = (void (__stdcall*)(GLenum, GLenum, GLenum, GLenum, const void *)) glGetProcAddress("glClearBufferData"), ASSERT(glClearBufferData),
		glClearBufferSubData = (void (__stdcall*)(GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *)) glGetProcAddress("glClearBufferSubData"), ASSERT(glClearBufferSubData),
		glDispatchCompute = (void (__stdcall*)(GLuint, GLuint, GLuint)) glGetProcAddress("glDispatchCompute"), ASSERT(glDispatchCompute),
		glDispatchComputeIndirect = (void (__stdcall*)(GLintptr)) glGetProcAddress("glDispatchComputeIndirect"), ASSERT(glDispatchComputeIndirect),
		glCopyImageSubData = (void (__stdcall*)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei)) glGetProcAddress("glCopyImageSubData"), ASSERT(glCopyImageSubData),
		glFramebufferParameteri = (void (__stdcall*)(GLenum, GLenum, GLint)) glGetProcAddress("glFramebufferParameteri"), ASSERT(glFramebufferParameteri),
		glGetFramebufferParameteriv = (void (__stdcall*)(GLenum, GLenum, GLint *)) glGetProcAddress("glGetFramebufferParameteriv"), ASSERT(glGetFramebufferParameteriv),
		glGetInternalformati64v = (void (__stdcall*)(GLenum, GLenum, GLenum, GLsizei, GLint64 *)) glGetProcAddress("glGetInternalformati64v"), ASSERT(glGetInternalformati64v),
		glInvalidateTexSubImage = (void (__stdcall*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei)) glGetProcAddress("glInvalidateTexSubImage"), ASSERT(glInvalidateTexSubImage),
		glInvalidateTexImage = (void (__stdcall*)(GLuint, GLint)) glGetProcAddress("glInvalidateTexImage"), ASSERT(glInvalidateTexImage),
		glInvalidateBufferSubData = (void (__stdcall*)(GLuint, GLintptr, GLsizeiptr)) glGetProcAddress("glInvalidateBufferSubData"), ASSERT(glInvalidateBufferSubData),
		glInvalidateBufferData = (void (__stdcall*)(GLuint)) glGetProcAddress("glInvalidateBufferData"), ASSERT(glInvalidateBufferData),
		glInvalidateFramebuffer = (void (__stdcall*)(GLenum, GLsizei, const GLenum *)) glGetProcAddress("glInvalidateFramebuffer"), ASSERT(glInvalidateFramebuffer),
		glInvalidateSubFramebuffer = (void (__stdcall*)(GLenum, GLsizei, const GLenum *, GLint x, GLint y, GLsizei, GLsizei)) glGetProcAddress("glInvalidateSubFramebuffer"), ASSERT(glInvalidateSubFramebuffer),
		glMultiDrawArraysIndirect = (void (__stdcall*)(GLenum, const void *, GLsizei, GLsizei)) glGetProcAddress("glMultiDrawArraysIndirect"), ASSERT(glMultiDrawArraysIndirect),
		glMultiDrawElementsIndirect = (void (__stdcall*)(GLenum, GLenum, const void *, GLsizei, GLsizei)) glGetProcAddress("glMultiDrawElementsIndirect"), ASSERT(glMultiDrawElementsIndirect),
		glGetProgramInterfaceiv = (void (__stdcall*)(GLuint, GLenum, GLenum, GLint *)) glGetProcAddress("glGetProgramInterfaceiv"), ASSERT(glGetProgramInterfaceiv),
		glGetProgramResourceIndex = (GLuint (__stdcall*)(GLuint, GLenum, const GLchar *)) glGetProcAddress("glGetProgramResourceIndex"), ASSERT(glGetProgramResourceIndex),
		glGetProgramResourceName = (void (__stdcall*)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *)) glGetProcAddress("glGetProgramResourceName"), ASSERT(glGetProgramResourceName),
		glGetProgramResourceiv = (void (__stdcall*)(GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLint *)) glGetProcAddress("glGetProgramResourceiv"), ASSERT(glGetProgramResourceiv),
		glGetProgramResourceLocation = (GLint (__stdcall*)(GLuint, GLenum, const GLchar *)) glGetProcAddress("glGetProgramResourceLocation"), ASSERT(glGetProgramResourceLocation),
		glGetProgramResourceLocationIndex = (GLint (__stdcall*)(GLuint, GLenum, const GLchar *)) glGetProcAddress("glGetProgramResourceLocationIndex"), ASSERT(glGetProgramResourceLocationIndex),
		glShaderStorageBlockBinding = (void (__stdcall*)(GLuint, GLuint, GLuint)) glGetProcAddress("glShaderStorageBlockBinding"), ASSERT(glShaderStorageBlockBinding),
		glTexBufferRange = (void (__stdcall*)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr)) glGetProcAddress("glTexBufferRange"), ASSERT(glTexBufferRange),
		glTexStorage2DMultisample = (void (__stdcall*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean)) glGetProcAddress("glTexStorage2DMultisample"), ASSERT(glTexStorage2DMultisample),
		glTexStorage3DMultisample = (void (__stdcall*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean)) glGetProcAddress("glTexStorage3DMultisample"), ASSERT(glTexStorage3DMultisample),
		glTextureView = (void (__stdcall*)(GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint)) glGetProcAddress("glTextureView"), ASSERT(glTextureView),
		glBindVertexBuffer = (void (__stdcall*)(GLuint, GLuint, GLintptr, GLsizei)) glGetProcAddress("glBindVertexBuffer"), ASSERT(glBindVertexBuffer),
		glVertexAttribFormat = (void (__stdcall*)(GLuint, GLint, GLenum, GLboolean, GLuint)) glGetProcAddress("glVertexAttribFormat"), ASSERT(glVertexAttribFormat),
		glVertexAttribIFormat = (void (__stdcall*)(GLuint, GLint, GLenum, GLuint)) glGetProcAddress("glVertexAttribIFormat"), ASSERT(glVertexAttribIFormat),
		glVertexAttribLFormat = (void (__stdcall*)(GLuint, GLint, GLenum, GLuint)) glGetProcAddress("glVertexAttribLFormat"), ASSERT(glVertexAttribLFormat),
		glVertexAttribBinding = (void (__stdcall*)(GLuint, GLuint)) glGetProcAddress("glVertexAttribBinding"), ASSERT(glVertexAttribBinding),
		glVertexBindingDivisor = (void (__stdcall*)(GLuint, GLuint)) glGetProcAddress("glVertexBindingDivisor"), ASSERT(glVertexBindingDivisor),
		glDebugMessageControl = (void (__stdcall*)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean)) glGetProcAddress("glDebugMessageControl"), ASSERT(glDebugMessageControl),
		glDebugMessageInsert = (void (__stdcall*)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *)) glGetProcAddress("glDebugMessageInsert"), ASSERT(glDebugMessageInsert),
		glDebugMessageCallback = (void (__stdcall*)(void (__stdcall*)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *, const void *), const void *)) glGetProcAddress("glDebugMessageCallback"), ASSERT(glDebugMessageCallback),
		glGetDebugMessageLog = (GLuint (__stdcall*)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *)) glGetProcAddress("glGetDebugMessageLog"), ASSERT(glGetDebugMessageLog),
		glPushDebugGroup = (void (__stdcall*)(GLenum, GLuint, GLsizei, const GLchar *)) glGetProcAddress("glPushDebugGroup"), ASSERT(glPushDebugGroup),
		glPopDebugGroup = (void (__stdcall*)(void)) glGetProcAddress("glPopDebugGroup"), ASSERT(glPopDebugGroup),
		glObjectLabel = (void (__stdcall*)(GLenum, GLuint, GLsizei, const GLchar *)) glGetProcAddress("glObjectLabel"), ASSERT(glObjectLabel),
		glGetObjectLabel = (void (__stdcall*)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *)) glGetProcAddress("glGetObjectLabel"), ASSERT(glGetObjectLabel),
		glObjectPtrLabel = (void (__stdcall*)(const void *, GLsizei, const GLchar *)) glGetProcAddress("glObjectPtrLabel"), ASSERT(glObjectPtrLabel),
		glGetObjectPtrLabel = (void (__stdcall*)(const void *, GLsizei, GLsizei *, GLchar *)) glGetProcAddress("glGetObjectPtrLabel"), ASSERT(glGetObjectPtrLabel);
	# ifndef GL_VERSION_4_2
		case 042:
		glDrawArraysInstancedBaseInstance = (void (__stdcall*)(GLenum, GLint, GLsizei, GLsizei, GLuint)) glGetProcAddress("glDrawArraysInstancedBaseInstance"), ASSERT(glDrawArraysInstancedBaseInstance),
		glDrawElementsInstancedBaseInstance = (void (__stdcall*)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLuint)) glGetProcAddress("glDrawElementsInstancedBaseInstance"), ASSERT(glDrawElementsInstancedBaseInstance),
		glDrawElementsInstancedBaseVertexBaseInstance = (void (__stdcall*)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint, GLuint)) glGetProcAddress("glDrawElementsInstancedBaseVertexBaseInstance"), ASSERT(glDrawElementsInstancedBaseVertexBaseInstance),
		glGetInternalformativ = (void (__stdcall*)(GLenum, GLenum, GLenum, GLsizei, GLint *)) glGetProcAddress("glGetInternalformativ"), ASSERT(glGetInternalformativ),
		glGetActiveAtomicCounterBufferiv = (void (__stdcall*)(GLuint, GLuint, GLenum, GLint *)) glGetProcAddress("glGetActiveAtomicCounterBufferiv"), ASSERT(glGetActiveAtomicCounterBufferiv),
		glBindImageTexture = (void (__stdcall*)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum)) glGetProcAddress("glBindImageTexture"), ASSERT(glBindImageTexture),
		glMemoryBarrier = (void (__stdcall*)(GLbitfield)) glGetProcAddress("glMemoryBarrier"), ASSERT(glMemoryBarrier),
		glTexStorage1D = (void (__stdcall*)(GLenum, GLsizei, GLenum, GLsizei)) glGetProcAddress("glTexStorage1D"), ASSERT(glTexStorage1D),
		glTexStorage2D = (void (__stdcall*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei)) glGetProcAddress("glTexStorage2D"), ASSERT(glTexStorage2D),
		glTexStorage3D = (void (__stdcall*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei)) glGetProcAddress("glTexStorage3D"), ASSERT(glTexStorage3D),
		glDrawTransformFeedbackInstanced = (void (__stdcall*)(GLenum, GLuint, GLsizei)) glGetProcAddress("glDrawTransformFeedbackInstanced"), ASSERT(glDrawTransformFeedbackInstanced),
		glDrawTransformFeedbackStreamInstanced = (void (__stdcall*)(GLenum, GLuint, GLuint, GLsizei)) glGetProcAddress("glDrawTransformFeedbackStreamInstanced"), ASSERT(glDrawTransformFeedbackStreamInstanced);
	# ifndef GL_VERSION_4_1
		case 041:
		glReleaseShaderCompiler = (void (__stdcall*)(void)) glGetProcAddress("glReleaseShaderCompiler"), ASSERT(glReleaseShaderCompiler),
		glShaderBinary = (void (__stdcall*)(GLsizei, const GLuint *, GLenum, const void *, GLsizei)) glGetProcAddress("glShaderBinary"), ASSERT(glShaderBinary),
		glGetShaderPrecisionFormat = (void (__stdcall*)(GLenum, GLenum, GLint *, GLint *)) glGetProcAddress("glGetShaderPrecisionFormat"), ASSERT(glGetShaderPrecisionFormat),
		glDepthRangef = (void (__stdcall*)(GLfloat, GLfloat)) glGetProcAddress("glDepthRangef"), ASSERT(glDepthRangef),
		glClearDepthf = (void (__stdcall*)(GLfloat)) glGetProcAddress("glClearDepthf"), ASSERT(glClearDepthf),
		glGetProgramBinary = (void (__stdcall*)(GLuint, GLsizei, GLsizei *, GLenum *, void *)) glGetProcAddress("glGetProgramBinary"), ASSERT(glGetProgramBinary),
		glProgramBinary = (void (__stdcall*)(GLuint, GLenum, const void *, GLsizei)) glGetProcAddress("glProgramBinary"), ASSERT(glProgramBinary),
		glProgramParameteri = (void (__stdcall*)(GLuint, GLenum, GLint)) glGetProcAddress("glProgramParameteri"), ASSERT(glProgramParameteri),
		glUseProgramStages = (void (__stdcall*)(GLuint, GLbitfield, GLuint)) glGetProcAddress("glUseProgramStages"), ASSERT(glUseProgramStages),
		glActiveShaderProgram = (void (__stdcall*)(GLuint, GLuint)) glGetProcAddress("glActiveShaderProgram"), ASSERT(glActiveShaderProgram),
		glCreateShaderProgramv = (GLuint (__stdcall*)(GLenum, GLsizei, const GLchar *const*)) glGetProcAddress("glCreateShaderProgramv"), ASSERT(glCreateShaderProgramv),
		glBindProgramPipeline = (void (__stdcall*)(GLuint)) glGetProcAddress("glBindProgramPipeline"), ASSERT(glBindProgramPipeline),
		glDeleteProgramPipelines = (void (__stdcall*)(GLsizei, const GLuint *)) glGetProcAddress("glDeleteProgramPipelines"), ASSERT(glDeleteProgramPipelines),
		glGenProgramPipelines = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glGenProgramPipelines"), ASSERT(glGenProgramPipelines),
		glIsProgramPipeline = (GLboolean (__stdcall*)(GLuint)) glGetProcAddress("glIsProgramPipeline"), ASSERT(glIsProgramPipeline),
		glGetProgramPipelineiv = (void (__stdcall*)(GLuint, GLenum, GLint *)) glGetProcAddress("glGetProgramPipelineiv"), ASSERT(glGetProgramPipelineiv),
		glProgramUniform1i = (void (__stdcall*)(GLuint, GLint, GLint)) glGetProcAddress("glProgramUniform1i"), ASSERT(glProgramUniform1i),
		glProgramUniform1iv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLint *)) glGetProcAddress("glProgramUniform1iv"), ASSERT(glProgramUniform1iv),
		glProgramUniform1f = (void (__stdcall*)(GLuint, GLint, GLfloat)) glGetProcAddress("glProgramUniform1f"), ASSERT(glProgramUniform1f),
		glProgramUniform1fv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLfloat *)) glGetProcAddress("glProgramUniform1fv"), ASSERT(glProgramUniform1fv),
		glProgramUniform1d = (void (__stdcall*)(GLuint, GLint, GLdouble)) glGetProcAddress("glProgramUniform1d"), ASSERT(glProgramUniform1d),
		glProgramUniform1dv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLdouble *)) glGetProcAddress("glProgramUniform1dv"), ASSERT(glProgramUniform1dv),
		glProgramUniform1ui = (void (__stdcall*)(GLuint, GLint, GLuint)) glGetProcAddress("glProgramUniform1ui"), ASSERT(glProgramUniform1ui),
		glProgramUniform1uiv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLuint *)) glGetProcAddress("glProgramUniform1uiv"), ASSERT(glProgramUniform1uiv),
		glProgramUniform2i = (void (__stdcall*)(GLuint, GLint, GLint, GLint)) glGetProcAddress("glProgramUniform2i"), ASSERT(glProgramUniform2i),
		glProgramUniform2iv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLint *)) glGetProcAddress("glProgramUniform2iv"), ASSERT(glProgramUniform2iv),
		glProgramUniform2f = (void (__stdcall*)(GLuint, GLint, GLfloat, GLfloat)) glGetProcAddress("glProgramUniform2f"), ASSERT(glProgramUniform2f),
		glProgramUniform2fv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLfloat *)) glGetProcAddress("glProgramUniform2fv"), ASSERT(glProgramUniform2fv),
		glProgramUniform2d = (void (__stdcall*)(GLuint, GLint, GLdouble, GLdouble)) glGetProcAddress("glProgramUniform2d"), ASSERT(glProgramUniform2d),
		glProgramUniform2dv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLdouble *)) glGetProcAddress("glProgramUniform2dv"), ASSERT(glProgramUniform2dv),
		glProgramUniform2ui = (void (__stdcall*)(GLuint, GLint, GLuint, GLuint)) glGetProcAddress("glProgramUniform2ui"), ASSERT(glProgramUniform2ui),
		glProgramUniform2uiv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLuint *)) glGetProcAddress("glProgramUniform2uiv"), ASSERT(glProgramUniform2uiv),
		glProgramUniform3i = (void (__stdcall*)(GLuint, GLint, GLint, GLint, GLint)) glGetProcAddress("glProgramUniform3i"), ASSERT(glProgramUniform3i),
		glProgramUniform3iv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLint *)) glGetProcAddress("glProgramUniform3iv"), ASSERT(glProgramUniform3iv),
		glProgramUniform3f = (void (__stdcall*)(GLuint, GLint, GLfloat, GLfloat, GLfloat)) glGetProcAddress("glProgramUniform3f"), ASSERT(glProgramUniform3f),
		glProgramUniform3fv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLfloat *)) glGetProcAddress("glProgramUniform3fv"), ASSERT(glProgramUniform3fv),
		glProgramUniform3d = (void (__stdcall*)(GLuint, GLint, GLdouble, GLdouble, GLdouble)) glGetProcAddress("glProgramUniform3d"), ASSERT(glProgramUniform3d),
		glProgramUniform3dv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLdouble *)) glGetProcAddress("glProgramUniform3dv"), ASSERT(glProgramUniform3dv),
		glProgramUniform3ui = (void (__stdcall*)(GLuint, GLint, GLuint, GLuint, GLuint)) glGetProcAddress("glProgramUniform3ui"), ASSERT(glProgramUniform3ui),
		glProgramUniform3uiv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLuint *)) glGetProcAddress("glProgramUniform3uiv"), ASSERT(glProgramUniform3uiv),
		glProgramUniform4i = (void (__stdcall*)(GLuint, GLint, GLint, GLint, GLint, GLint)) glGetProcAddress("glProgramUniform4i"), ASSERT(glProgramUniform4i),
		glProgramUniform4iv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLint *)) glGetProcAddress("glProgramUniform4iv"), ASSERT(glProgramUniform4iv),
		glProgramUniform4f = (void (__stdcall*)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat)) glGetProcAddress("glProgramUniform4f"), ASSERT(glProgramUniform4f),
		glProgramUniform4fv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLfloat *)) glGetProcAddress("glProgramUniform4fv"), ASSERT(glProgramUniform4fv),
		glProgramUniform4d = (void (__stdcall*)(GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble)) glGetProcAddress("glProgramUniform4d"), ASSERT(glProgramUniform4d),
		glProgramUniform4dv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLdouble *)) glGetProcAddress("glProgramUniform4dv"), ASSERT(glProgramUniform4dv),
		glProgramUniform4ui = (void (__stdcall*)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint)) glGetProcAddress("glProgramUniform4ui"), ASSERT(glProgramUniform4ui),
		glProgramUniform4uiv = (void (__stdcall*)(GLuint, GLint, GLsizei, const GLuint *)) glGetProcAddress("glProgramUniform4uiv"), ASSERT(glProgramUniform4uiv),
		glProgramUniformMatrix2fv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glProgramUniformMatrix2fv"), ASSERT(glProgramUniformMatrix2fv),
		glProgramUniformMatrix3fv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glProgramUniformMatrix3fv"), ASSERT(glProgramUniformMatrix3fv),
		glProgramUniformMatrix4fv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glProgramUniformMatrix4fv"), ASSERT(glProgramUniformMatrix4fv),
		glProgramUniformMatrix2dv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glProgramUniformMatrix2dv"), ASSERT(glProgramUniformMatrix2dv),
		glProgramUniformMatrix3dv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glProgramUniformMatrix3dv"), ASSERT(glProgramUniformMatrix3dv),
		glProgramUniformMatrix4dv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glProgramUniformMatrix4dv"), ASSERT(glProgramUniformMatrix4dv),
		glProgramUniformMatrix2x3fv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glProgramUniformMatrix2x3fv"), ASSERT(glProgramUniformMatrix2x3fv),
		glProgramUniformMatrix3x2fv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glProgramUniformMatrix3x2fv"), ASSERT(glProgramUniformMatrix3x2fv),
		glProgramUniformMatrix2x4fv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glProgramUniformMatrix2x4fv"), ASSERT(glProgramUniformMatrix2x4fv),
		glProgramUniformMatrix4x2fv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glProgramUniformMatrix4x2fv"), ASSERT(glProgramUniformMatrix4x2fv),
		glProgramUniformMatrix3x4fv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glProgramUniformMatrix3x4fv"), ASSERT(glProgramUniformMatrix3x4fv),
		glProgramUniformMatrix4x3fv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glProgramUniformMatrix4x3fv"), ASSERT(glProgramUniformMatrix4x3fv),
		glProgramUniformMatrix2x3dv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glProgramUniformMatrix2x3dv"), ASSERT(glProgramUniformMatrix2x3dv),
		glProgramUniformMatrix3x2dv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glProgramUniformMatrix3x2dv"), ASSERT(glProgramUniformMatrix3x2dv),
		glProgramUniformMatrix2x4dv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glProgramUniformMatrix2x4dv"), ASSERT(glProgramUniformMatrix2x4dv),
		glProgramUniformMatrix4x2dv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glProgramUniformMatrix4x2dv"), ASSERT(glProgramUniformMatrix4x2dv),
		glProgramUniformMatrix3x4dv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glProgramUniformMatrix3x4dv"), ASSERT(glProgramUniformMatrix3x4dv),
		glProgramUniformMatrix4x3dv = (void (__stdcall*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glProgramUniformMatrix4x3dv"), ASSERT(glProgramUniformMatrix4x3dv),
		glValidateProgramPipeline = (void (__stdcall*)(GLuint)) glGetProcAddress("glValidateProgramPipeline"), ASSERT(glValidateProgramPipeline),
		glGetProgramPipelineInfoLog = (void (__stdcall*)(GLuint, GLsizei, GLsizei *, GLchar *)) glGetProcAddress("glGetProgramPipelineInfoLog"), ASSERT(glGetProgramPipelineInfoLog),
		glVertexAttribL1d = (void (__stdcall*)(GLuint, GLdouble)) glGetProcAddress("glVertexAttribL1d"), ASSERT(glVertexAttribL1d),
		glVertexAttribL2d = (void (__stdcall*)(GLuint, GLdouble, GLdouble)) glGetProcAddress("glVertexAttribL2d"), ASSERT(glVertexAttribL2d),
		glVertexAttribL3d = (void (__stdcall*)(GLuint, GLdouble, GLdouble, GLdouble)) glGetProcAddress("glVertexAttribL3d"), ASSERT(glVertexAttribL3d),
		glVertexAttribL4d = (void (__stdcall*)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble)) glGetProcAddress("glVertexAttribL4d"), ASSERT(glVertexAttribL4d),
		glVertexAttribL1dv = (void (__stdcall*)(GLuint, const GLdouble *)) glGetProcAddress("glVertexAttribL1dv"), ASSERT(glVertexAttribL1dv),
		glVertexAttribL2dv = (void (__stdcall*)(GLuint, const GLdouble *)) glGetProcAddress("glVertexAttribL2dv"), ASSERT(glVertexAttribL2dv),
		glVertexAttribL3dv = (void (__stdcall*)(GLuint, const GLdouble *)) glGetProcAddress("glVertexAttribL3dv"), ASSERT(glVertexAttribL3dv),
		glVertexAttribL4dv = (void (__stdcall*)(GLuint, const GLdouble *)) glGetProcAddress("glVertexAttribL4dv"), ASSERT(glVertexAttribL4dv),
		glVertexAttribLPointer = (void (__stdcall*)(GLuint, GLint, GLenum, GLsizei, const void *)) glGetProcAddress("glVertexAttribLPointer"), ASSERT(glVertexAttribLPointer),
		glGetVertexAttribLdv = (void (__stdcall*)(GLuint, GLenum, GLdouble *)) glGetProcAddress("glGetVertexAttribLdv"), ASSERT(glGetVertexAttribLdv),
		glViewportArrayv = (void (__stdcall*)(GLuint, GLsizei, const GLfloat *)) glGetProcAddress("glViewportArrayv"), ASSERT(glViewportArrayv),
		glViewportIndexedf = (void (__stdcall*)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat)) glGetProcAddress("glViewportIndexedf"), ASSERT(glViewportIndexedf),
		glViewportIndexedfv = (void (__stdcall*)(GLuint, const GLfloat *)) glGetProcAddress("glViewportIndexedfv"), ASSERT(glViewportIndexedfv),
		glScissorArrayv = (void (__stdcall*)(GLuint, GLsizei, const GLint *)) glGetProcAddress("glScissorArrayv"), ASSERT(glScissorArrayv),
		glScissorIndexed = (void (__stdcall*)(GLuint, GLint, GLint, GLsizei, GLsizei)) glGetProcAddress("glScissorIndexed"), ASSERT(glScissorIndexed),
		glScissorIndexedv = (void (__stdcall*)(GLuint, const GLint *)) glGetProcAddress("glScissorIndexedv"), ASSERT(glScissorIndexedv),
		glDepthRangeArrayv = (void (__stdcall*)(GLuint, GLsizei, const GLdouble *)) glGetProcAddress("glDepthRangeArrayv"), ASSERT(glDepthRangeArrayv),
		glDepthRangeIndexed = (void (__stdcall*)(GLuint, GLdouble, GLdouble)) glGetProcAddress("glDepthRangeIndexed"), ASSERT(glDepthRangeIndexed),
		glGetFloati_v = (void (__stdcall*)(GLenum, GLuint, GLfloat *)) glGetProcAddress("glGetFloati_v"), ASSERT(glGetFloati_v),
		glGetDoublei_v = (void (__stdcall*)(GLenum, GLuint, GLdouble *)) glGetProcAddress("glGetDoublei_v"), ASSERT(glGetDoublei_v);
	# ifndef GL_VERSION_4_0
		case 040:
		glMinSampleShading = (void (__stdcall*)(GLfloat)) glGetProcAddress("glMinSampleShading"), ASSERT(glMinSampleShading),
		glBlendEquationi = (void (__stdcall*)(GLuint, GLenum)) glGetProcAddress("glBlendEquationi"), ASSERT(glBlendEquationi),
		glBlendEquationSeparatei = (void (__stdcall*)(GLuint, GLenum, GLenum)) glGetProcAddress("glBlendEquationSeparatei"), ASSERT(glBlendEquationSeparatei),
		glBlendFunci = (void (__stdcall*)(GLuint, GLenum, GLenum)) glGetProcAddress("glBlendFunci"), ASSERT(glBlendFunci),
		glBlendFuncSeparatei = (void (__stdcall*)(GLuint, GLenum, GLenum, GLenum, GLenum)) glGetProcAddress("glBlendFuncSeparatei"), ASSERT(glBlendFuncSeparatei),
		glDrawArraysIndirect = (void (__stdcall*)(GLenum, const void *)) glGetProcAddress("glDrawArraysIndirect"), ASSERT(glDrawArraysIndirect),
		glDrawElementsIndirect = (void (__stdcall*)(GLenum, GLenum, const void *)) glGetProcAddress("glDrawElementsIndirect"), ASSERT(glDrawElementsIndirect),
		glUniform1d = (void (__stdcall*)(GLint, GLdouble)) glGetProcAddress("glUniform1d"), ASSERT(glUniform1d),
		glUniform2d = (void (__stdcall*)(GLint, GLdouble, GLdouble)) glGetProcAddress("glUniform2d"), ASSERT(glUniform2d),
		glUniform3d = (void (__stdcall*)(GLint, GLdouble, GLdouble, GLdouble)) glGetProcAddress("glUniform3d"), ASSERT(glUniform3d),
		glUniform4d = (void (__stdcall*)(GLint, GLdouble, GLdouble, GLdouble, GLdouble)) glGetProcAddress("glUniform4d"), ASSERT(glUniform4d),
		glUniform1dv = (void (__stdcall*)(GLint, GLsizei, const GLdouble *)) glGetProcAddress("glUniform1dv"), ASSERT(glUniform1dv),
		glUniform2dv = (void (__stdcall*)(GLint, GLsizei, const GLdouble *)) glGetProcAddress("glUniform2dv"), ASSERT(glUniform2dv),
		glUniform3dv = (void (__stdcall*)(GLint, GLsizei, const GLdouble *)) glGetProcAddress("glUniform3dv"), ASSERT(glUniform3dv),
		glUniform4dv = (void (__stdcall*)(GLint, GLsizei, const GLdouble *)) glGetProcAddress("glUniform4dv"), ASSERT(glUniform4dv),
		glUniformMatrix2dv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glUniformMatrix2dv"), ASSERT(glUniformMatrix2dv),
		glUniformMatrix3dv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glUniformMatrix3dv"), ASSERT(glUniformMatrix3dv),
		glUniformMatrix4dv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glUniformMatrix4dv"), ASSERT(glUniformMatrix4dv),
		glUniformMatrix2x3dv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glUniformMatrix2x3dv"), ASSERT(glUniformMatrix2x3dv),
		glUniformMatrix2x4dv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glUniformMatrix2x4dv"), ASSERT(glUniformMatrix2x4dv),
		glUniformMatrix3x2dv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glUniformMatrix3x2dv"), ASSERT(glUniformMatrix3x2dv),
		glUniformMatrix3x4dv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glUniformMatrix3x4dv"), ASSERT(glUniformMatrix3x4dv),
		glUniformMatrix4x2dv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glUniformMatrix4x2dv"), ASSERT(glUniformMatrix4x2dv),
		glUniformMatrix4x3dv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLdouble *)) glGetProcAddress("glUniformMatrix4x3dv"), ASSERT(glUniformMatrix4x3dv),
		glGetUniformdv = (void (__stdcall*)(GLuint, GLint, GLdouble *)) glGetProcAddress("glGetUniformdv"), ASSERT(glGetUniformdv),
		glGetSubroutineUniformLocation = (GLint (__stdcall*)(GLuint, GLenum, const GLchar *)) glGetProcAddress("glGetSubroutineUniformLocation"), ASSERT(glGetSubroutineUniformLocation),
		glGetSubroutineIndex = (GLuint (__stdcall*)(GLuint, GLenum, const GLchar *)) glGetProcAddress("glGetSubroutineIndex"), ASSERT(glGetSubroutineIndex),
		glGetActiveSubroutineUniformiv = (void (__stdcall*)(GLuint, GLenum, GLuint, GLenum, GLint *)) glGetProcAddress("glGetActiveSubroutineUniformiv"), ASSERT(glGetActiveSubroutineUniformiv),
		glGetActiveSubroutineUniformName = (void (__stdcall*)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *)) glGetProcAddress("glGetActiveSubroutineUniformName"), ASSERT(glGetActiveSubroutineUniformName),
		glGetActiveSubroutineName = (void (__stdcall*)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *)) glGetProcAddress("glGetActiveSubroutineName"), ASSERT(glGetActiveSubroutineName),
		glUniformSubroutinesuiv = (void (__stdcall*)(GLenum, GLsizei, const GLuint *)) glGetProcAddress("glUniformSubroutinesuiv"), ASSERT(glUniformSubroutinesuiv),
		glGetUniformSubroutineuiv = (void (__stdcall*)(GLenum, GLint, GLuint *)) glGetProcAddress("glGetUniformSubroutineuiv"), ASSERT(glGetUniformSubroutineuiv),
		glGetProgramStageiv = (void (__stdcall*)(GLuint, GLenum, GLenum, GLint *)) glGetProcAddress("glGetProgramStageiv"), ASSERT(glGetProgramStageiv),
		glPatchParameteri = (void (__stdcall*)(GLenum, GLint)) glGetProcAddress("glPatchParameteri"), ASSERT(glPatchParameteri),
		glPatchParameterfv = (void (__stdcall*)(GLenum, const GLfloat *)) glGetProcAddress("glPatchParameterfv"), ASSERT(glPatchParameterfv),
		glBindTransformFeedback = (void (__stdcall*)(GLenum, GLuint)) glGetProcAddress("glBindTransformFeedback"), ASSERT(glBindTransformFeedback),
		glDeleteTransformFeedbacks = (void (__stdcall*)(GLsizei, const GLuint *)) glGetProcAddress("glDeleteTransformFeedbacks"), ASSERT(glDeleteTransformFeedbacks),
		glGenTransformFeedbacks = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glGenTransformFeedbacks"), ASSERT(glGenTransformFeedbacks),
		glIsTransformFeedback = (GLboolean (__stdcall*)(GLuint)) glGetProcAddress("glIsTransformFeedback"), ASSERT(glIsTransformFeedback),
		glPauseTransformFeedback = (void (__stdcall*)(void)) glGetProcAddress("glPauseTransformFeedback"), ASSERT(glPauseTransformFeedback),
		glResumeTransformFeedback = (void (__stdcall*)(void)) glGetProcAddress("glResumeTransformFeedback"), ASSERT(glResumeTransformFeedback),
		glDrawTransformFeedback = (void (__stdcall*)(GLenum, GLuint)) glGetProcAddress("glDrawTransformFeedback"), ASSERT(glDrawTransformFeedback),
		glDrawTransformFeedbackStream = (void (__stdcall*)(GLenum, GLuint, GLuint)) glGetProcAddress("glDrawTransformFeedbackStream"), ASSERT(glDrawTransformFeedbackStream),
		glBeginQueryIndexed = (void (__stdcall*)(GLenum, GLuint, GLuint)) glGetProcAddress("glBeginQueryIndexed"), ASSERT(glBeginQueryIndexed),
		glEndQueryIndexed = (void (__stdcall*)(GLenum, GLuint)) glGetProcAddress("glEndQueryIndexed"), ASSERT(glEndQueryIndexed),
		glGetQueryIndexediv = (void (__stdcall*)(GLenum, GLuint, GLenum, GLint *)) glGetProcAddress("glGetQueryIndexediv"), ASSERT(glGetQueryIndexediv);
	# ifndef GL_VERSION_3_3
		case 033:
		glBindFragDataLocationIndexed = (void (__stdcall*)(GLuint, GLuint, GLuint, const GLchar *)) glGetProcAddress("glBindFragDataLocationIndexed"), ASSERT(glBindFragDataLocationIndexed),
		glGetFragDataIndex = (GLint (__stdcall*)(GLuint, const GLchar *)) glGetProcAddress("glGetFragDataIndex"), ASSERT(glGetFragDataIndex),
		glGenSamplers = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glGenSamplers"), ASSERT(glGenSamplers),
		glDeleteSamplers = (void (__stdcall*)(GLsizei, const GLuint *)) glGetProcAddress("glDeleteSamplers"), ASSERT(glDeleteSamplers),
		glIsSampler = (GLboolean (__stdcall*)(GLuint)) glGetProcAddress("glIsSampler"), ASSERT(glIsSampler),
		glBindSampler = (void (__stdcall*)(GLuint, GLuint)) glGetProcAddress("glBindSampler"), ASSERT(glBindSampler),
		glSamplerParameteri = (void (__stdcall*)(GLuint, GLenum, GLint)) glGetProcAddress("glSamplerParameteri"), ASSERT(glSamplerParameteri),
		glSamplerParameteriv = (void (__stdcall*)(GLuint, GLenum, const GLint *)) glGetProcAddress("glSamplerParameteriv"), ASSERT(glSamplerParameteriv),
		glSamplerParameterf = (void (__stdcall*)(GLuint, GLenum, GLfloat)) glGetProcAddress("glSamplerParameterf"), ASSERT(glSamplerParameterf),
		glSamplerParameterfv = (void (__stdcall*)(GLuint, GLenum, const GLfloat *)) glGetProcAddress("glSamplerParameterfv"), ASSERT(glSamplerParameterfv),
		glSamplerParameterIiv = (void (__stdcall*)(GLuint, GLenum, const GLint *)) glGetProcAddress("glSamplerParameterIiv"), ASSERT(glSamplerParameterIiv),
		glSamplerParameterIuiv = (void (__stdcall*)(GLuint, GLenum, const GLuint *)) glGetProcAddress("glSamplerParameterIuiv"), ASSERT(glSamplerParameterIuiv),
		glGetSamplerParameteriv = (void (__stdcall*)(GLuint, GLenum, GLint *)) glGetProcAddress("glGetSamplerParameteriv"), ASSERT(glGetSamplerParameteriv),
		glGetSamplerParameterIiv = (void (__stdcall*)(GLuint, GLenum, GLint *)) glGetProcAddress("glGetSamplerParameterIiv"), ASSERT(glGetSamplerParameterIiv),
		glGetSamplerParameterfv = (void (__stdcall*)(GLuint, GLenum, GLfloat *)) glGetProcAddress("glGetSamplerParameterfv"), ASSERT(glGetSamplerParameterfv),
		glGetSamplerParameterIuiv = (void (__stdcall*)(GLuint, GLenum, GLuint *)) glGetProcAddress("glGetSamplerParameterIuiv"), ASSERT(glGetSamplerParameterIuiv),
		glQueryCounter = (void (__stdcall*)(GLuint, GLenum)) glGetProcAddress("glQueryCounter"), ASSERT(glQueryCounter),
		glGetQueryObjecti64v = (void (__stdcall*)(GLuint, GLenum, GLint64 *)) glGetProcAddress("glGetQueryObjecti64v"), ASSERT(glGetQueryObjecti64v),
		glGetQueryObjectui64v = (void (__stdcall*)(GLuint, GLenum, GLuint64 *)) glGetProcAddress("glGetQueryObjectui64v"), ASSERT(glGetQueryObjectui64v),
		glVertexAttribDivisor = (void (__stdcall*)(GLuint, GLuint)) glGetProcAddress("glVertexAttribDivisor"), ASSERT(glVertexAttribDivisor),
		glVertexAttribP1ui = (void (__stdcall*)(GLuint, GLenum, GLboolean, GLuint)) glGetProcAddress("glVertexAttribP1ui"), ASSERT(glVertexAttribP1ui),
		glVertexAttribP1uiv = (void (__stdcall*)(GLuint, GLenum, GLboolean, const GLuint *)) glGetProcAddress("glVertexAttribP1uiv"), ASSERT(glVertexAttribP1uiv),
		glVertexAttribP2ui = (void (__stdcall*)(GLuint, GLenum, GLboolean, GLuint)) glGetProcAddress("glVertexAttribP2ui"), ASSERT(glVertexAttribP2ui),
		glVertexAttribP2uiv = (void (__stdcall*)(GLuint, GLenum, GLboolean, const GLuint *)) glGetProcAddress("glVertexAttribP2uiv"), ASSERT(glVertexAttribP2uiv),
		glVertexAttribP3ui = (void (__stdcall*)(GLuint, GLenum, GLboolean, GLuint)) glGetProcAddress("glVertexAttribP3ui"), ASSERT(glVertexAttribP3ui),
		glVertexAttribP3uiv = (void (__stdcall*)(GLuint, GLenum, GLboolean, const GLuint *)) glGetProcAddress("glVertexAttribP3uiv"), ASSERT(glVertexAttribP3uiv),
		glVertexAttribP4ui = (void (__stdcall*)(GLuint, GLenum, GLboolean, GLuint)) glGetProcAddress("glVertexAttribP4ui"), ASSERT(glVertexAttribP4ui),
		glVertexAttribP4uiv = (void (__stdcall*)(GLuint, GLenum, GLboolean, const GLuint *)) glGetProcAddress("glVertexAttribP4uiv"), ASSERT(glVertexAttribP4uiv);
	# endif
	# ifndef GL_VERSION_3_2
		case 032:
		glDrawElementsBaseVertex = (void (__stdcall*)(GLenum, GLsizei, GLenum, const void *, GLint)) glGetProcAddress("glDrawElementsBaseVertex"), ASSERT(glDrawElementsBaseVertex),
		glDrawRangeElementsBaseVertex = (void (__stdcall*)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *, GLint)) glGetProcAddress("glDrawRangeElementsBaseVertex"), ASSERT(glDrawRangeElementsBaseVertex),
		glDrawElementsInstancedBaseVertex = (void (__stdcall*)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint)) glGetProcAddress("glDrawElementsInstancedBaseVertex"), ASSERT(glDrawElementsInstancedBaseVertex),
		glMultiDrawElementsBaseVertex = (void (__stdcall*)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei, const GLint *)) glGetProcAddress("glMultiDrawElementsBaseVertex"), ASSERT(glMultiDrawElementsBaseVertex),
		glProvokingVertex = (void (__stdcall*)(GLenum)) glGetProcAddress("glProvokingVertex"), ASSERT(glProvokingVertex),
		glFenceSync = (GLsync (__stdcall*)(GLenum, GLbitfield)) glGetProcAddress("glFenceSync"), ASSERT(glFenceSync),
		glIsSync = (GLboolean (__stdcall*)(GLsync)) glGetProcAddress("glIsSync"), ASSERT(glIsSync),
		glDeleteSync = (void (__stdcall*)(GLsync)) glGetProcAddress("glDeleteSync"), ASSERT(glDeleteSync),
		glClientWaitSync = (GLenum (__stdcall*)(GLsync, GLbitfield, GLuint64)) glGetProcAddress("glClientWaitSync"), ASSERT(glClientWaitSync),
		glWaitSync = (void (__stdcall*)(GLsync, GLbitfield, GLuint64)) glGetProcAddress("glWaitSync"), ASSERT(glWaitSync),
		glGetInteger64v = (void (__stdcall*)(GLenum, GLint64 *)) glGetProcAddress("glGetInteger64v"), ASSERT(glGetInteger64v),
		glGetSynciv = (void (__stdcall*)(GLsync, GLenum, GLsizei, GLsizei *, GLint *)) glGetProcAddress("glGetSynciv"), ASSERT(glGetSynciv),
		glGetInteger64i_v = (void (__stdcall*)(GLenum, GLuint, GLint64 *)) glGetProcAddress("glGetInteger64i_v"), ASSERT(glGetInteger64i_v),
		glGetBufferParameteri64v = (void (__stdcall*)(GLenum, GLenum, GLint64 *)) glGetProcAddress("glGetBufferParameteri64v"), ASSERT(glGetBufferParameteri64v),
		glFramebufferTexture = (void (__stdcall*)(GLenum, GLenum, GLuint, GLint)) glGetProcAddress("glFramebufferTexture"), ASSERT(glFramebufferTexture),
		glTexImage2DMultisample = (void (__stdcall*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean)) glGetProcAddress("glTexImage2DMultisample"), ASSERT(glTexImage2DMultisample),
		glTexImage3DMultisample = (void (__stdcall*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean)) glGetProcAddress("glTexImage3DMultisample"), ASSERT(glTexImage3DMultisample),
		glGetMultisamplefv = (void (__stdcall*)(GLenum, GLuint, GLfloat *)) glGetProcAddress("glGetMultisamplefv"), ASSERT(glGetMultisamplefv),
		glSampleMaski = (void (__stdcall*)(GLuint, GLbitfield)) glGetProcAddress("glSampleMaski"), ASSERT(glSampleMaski);
	# ifndef GL_VERSION_3_1
		case 031:
		glDrawArraysInstanced = (void (__stdcall*)(GLenum, GLint, GLsizei, GLsizei)) glGetProcAddress("glDrawArraysInstanced"), ASSERT(glDrawArraysInstanced),
		glDrawElementsInstanced = (void (__stdcall*)(GLenum, GLsizei, GLenum, const void *, GLsizei)) glGetProcAddress("glDrawElementsInstanced"), ASSERT(glDrawElementsInstanced),
		glTexBuffer = (void (__stdcall*)(GLenum, GLenum, GLuint)) glGetProcAddress("glTexBuffer"), ASSERT(glTexBuffer),
		glPrimitiveRestartIndex = (void (__stdcall*)(GLuint)) glGetProcAddress("glPrimitiveRestartIndex"), ASSERT(glPrimitiveRestartIndex),
		glCopyBufferSubData = (void (__stdcall*)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr)) glGetProcAddress("glCopyBufferSubData"), ASSERT(glCopyBufferSubData),
		glGetUniformIndices = (void (__stdcall*)(GLuint, GLsizei, const GLchar *const*, GLuint *)) glGetProcAddress("glGetUniformIndices"), ASSERT(glGetUniformIndices),
		glGetActiveUniformsiv = (void (__stdcall*)(GLuint, GLsizei, const GLuint *, GLenum, GLint *)) glGetProcAddress("glGetActiveUniformsiv"), ASSERT(glGetActiveUniformsiv),
		glGetActiveUniformName = (void (__stdcall*)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *)) glGetProcAddress("glGetActiveUniformName"), ASSERT(glGetActiveUniformName),
		glGetUniformBlockIndex = (GLuint (__stdcall*)(GLuint, const GLchar *)) glGetProcAddress("glGetUniformBlockIndex"), ASSERT(glGetUniformBlockIndex),
		glGetActiveUniformBlockiv = (void (__stdcall*)(GLuint, GLuint, GLenum, GLint *)) glGetProcAddress("glGetActiveUniformBlockiv"), ASSERT(glGetActiveUniformBlockiv),
		glGetActiveUniformBlockName = (void (__stdcall*)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *)) glGetProcAddress("glGetActiveUniformBlockName"), ASSERT(glGetActiveUniformBlockName),
		glUniformBlockBinding = (void (__stdcall*)(GLuint, GLuint, GLuint)) glGetProcAddress("glUniformBlockBinding"), ASSERT(glUniformBlockBinding);
	# ifndef GL_VERSION_3_0
		case 030:
		glColorMaski = (void (__stdcall*)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean)) glGetProcAddress("glColorMaski"), ASSERT(glColorMaski),
		glGetBooleani_v = (void (__stdcall*)(GLenum, GLuint, GLboolean *)) glGetProcAddress("glGetBooleani_v"), ASSERT(glGetBooleani_v),
		glGetIntegeri_v = (void (__stdcall*)(GLenum, GLuint, GLint *)) glGetProcAddress("glGetIntegeri_v"), ASSERT(glGetIntegeri_v),
		glEnablei = (void (__stdcall*)(GLenum, GLuint)) glGetProcAddress("glEnablei"), ASSERT(glEnablei),
		glDisablei = (void (__stdcall*)(GLenum, GLuint)) glGetProcAddress("glDisablei"), ASSERT(glDisablei),
		glIsEnabledi = (GLboolean (__stdcall*)(GLenum, GLuint)) glGetProcAddress("glIsEnabledi"), ASSERT(glIsEnabledi),
		glBeginTransformFeedback = (void (__stdcall*)(GLenum)) glGetProcAddress("glBeginTransformFeedback"), ASSERT(glBeginTransformFeedback),
		glEndTransformFeedback = (void (__stdcall*)(void)) glGetProcAddress("glEndTransformFeedback"), ASSERT(glEndTransformFeedback),
		glBindBufferRange = (void (__stdcall*)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr)) glGetProcAddress("glBindBufferRange"), ASSERT(glBindBufferRange),
		glBindBufferBase = (void (__stdcall*)(GLenum, GLuint, GLuint)) glGetProcAddress("glBindBufferBase"), ASSERT(glBindBufferBase),
		glTransformFeedbackVaryings = (void (__stdcall*)(GLuint, GLsizei, const GLchar *const*, GLenum)) glGetProcAddress("glTransformFeedbackVaryings"), ASSERT(glTransformFeedbackVaryings),
		glGetTransformFeedbackVarying = (void (__stdcall*)(GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *)) glGetProcAddress("glGetTransformFeedbackVarying"), ASSERT(glGetTransformFeedbackVarying),
		glClampColor = (void (__stdcall*)(GLenum, GLenum)) glGetProcAddress("glClampColor"), ASSERT(glClampColor),
		glBeginConditionalRender = (void (__stdcall*)(GLuint, GLenum)) glGetProcAddress("glBeginConditionalRender"), ASSERT(glBeginConditionalRender),
		glEndConditionalRender = (void (__stdcall*)(void)) glGetProcAddress("glEndConditionalRender"), ASSERT(glEndConditionalRender),
		glVertexAttribIPointer = (void (__stdcall*)(GLuint, GLint, GLenum, GLsizei, const void *)) glGetProcAddress("glVertexAttribIPointer"), ASSERT(glVertexAttribIPointer),
		glGetVertexAttribIiv = (void (__stdcall*)(GLuint, GLenum, GLint *)) glGetProcAddress("glGetVertexAttribIiv"), ASSERT(glGetVertexAttribIiv),
		glGetVertexAttribIuiv = (void (__stdcall*)(GLuint, GLenum, GLuint *)) glGetProcAddress("glGetVertexAttribIuiv"), ASSERT(glGetVertexAttribIuiv),
		glVertexAttribI1i = (void (__stdcall*)(GLuint, GLint)) glGetProcAddress("glVertexAttribI1i"), ASSERT(glVertexAttribI1i),
		glVertexAttribI2i = (void (__stdcall*)(GLuint, GLint, GLint)) glGetProcAddress("glVertexAttribI2i"), ASSERT(glVertexAttribI2i),
		glVertexAttribI3i = (void (__stdcall*)(GLuint, GLint, GLint, GLint)) glGetProcAddress("glVertexAttribI3i"), ASSERT(glVertexAttribI3i),
		glVertexAttribI4i = (void (__stdcall*)(GLuint, GLint, GLint, GLint, GLint)) glGetProcAddress("glVertexAttribI4i"), ASSERT(glVertexAttribI4i),
		glVertexAttribI1ui = (void (__stdcall*)(GLuint, GLuint)) glGetProcAddress("glVertexAttribI1ui"), ASSERT(glVertexAttribI1ui),
		glVertexAttribI2ui = (void (__stdcall*)(GLuint, GLuint, GLuint)) glGetProcAddress("glVertexAttribI2ui"), ASSERT(glVertexAttribI2ui),
		glVertexAttribI3ui = (void (__stdcall*)(GLuint, GLuint, GLuint, GLuint)) glGetProcAddress("glVertexAttribI3ui"), ASSERT(glVertexAttribI3ui),
		glVertexAttribI4ui = (void (__stdcall*)(GLuint, GLuint, GLuint, GLuint, GLuint)) glGetProcAddress("glVertexAttribI4ui"), ASSERT(glVertexAttribI4ui),
		glVertexAttribI1iv = (void (__stdcall*)(GLuint, const GLint *)) glGetProcAddress("glVertexAttribI1iv"), ASSERT(glVertexAttribI1iv),
		glVertexAttribI2iv = (void (__stdcall*)(GLuint, const GLint *)) glGetProcAddress("glVertexAttribI2iv"), ASSERT(glVertexAttribI2iv),
		glVertexAttribI3iv = (void (__stdcall*)(GLuint, const GLint *)) glGetProcAddress("glVertexAttribI3iv"), ASSERT(glVertexAttribI3iv),
		glVertexAttribI4iv = (void (__stdcall*)(GLuint, const GLint *)) glGetProcAddress("glVertexAttribI4iv"), ASSERT(glVertexAttribI4iv),
		glVertexAttribI1uiv = (void (__stdcall*)(GLuint, const GLuint *)) glGetProcAddress("glVertexAttribI1uiv"), ASSERT(glVertexAttribI1uiv),
		glVertexAttribI2uiv = (void (__stdcall*)(GLuint, const GLuint *)) glGetProcAddress("glVertexAttribI2uiv"), ASSERT(glVertexAttribI2uiv),
		glVertexAttribI3uiv = (void (__stdcall*)(GLuint, const GLuint *)) glGetProcAddress("glVertexAttribI3uiv"), ASSERT(glVertexAttribI3uiv),
		glVertexAttribI4uiv = (void (__stdcall*)(GLuint, const GLuint *)) glGetProcAddress("glVertexAttribI4uiv"), ASSERT(glVertexAttribI4uiv),
		glVertexAttribI4bv = (void (__stdcall*)(GLuint, const GLbyte *)) glGetProcAddress("glVertexAttribI4bv"), ASSERT(glVertexAttribI4bv),
		glVertexAttribI4sv = (void (__stdcall*)(GLuint, const GLshort *)) glGetProcAddress("glVertexAttribI4sv"), ASSERT(glVertexAttribI4sv),
		glVertexAttribI4ubv = (void (__stdcall*)(GLuint, const GLubyte *)) glGetProcAddress("glVertexAttribI4ubv"), ASSERT(glVertexAttribI4ubv),
		glVertexAttribI4usv = (void (__stdcall*)(GLuint, const GLushort *)) glGetProcAddress("glVertexAttribI4usv"), ASSERT(glVertexAttribI4usv),
		glGetUniformuiv = (void (__stdcall*)(GLuint, GLint, GLuint *)) glGetProcAddress("glGetUniformuiv"), ASSERT(glGetUniformuiv),
		glBindFragDataLocation = (void (__stdcall*)(GLuint, GLuint, const GLchar *)) glGetProcAddress("glBindFragDataLocation"), ASSERT(glBindFragDataLocation),
		glGetFragDataLocation = (GLint (__stdcall*)(GLuint, const GLchar *)) glGetProcAddress("glGetFragDataLocation"), ASSERT(glGetFragDataLocation),
		glUniform1ui = (void (__stdcall*)(GLint, GLuint)) glGetProcAddress("glUniform1ui"), ASSERT(glUniform1ui),
		glUniform2ui = (void (__stdcall*)(GLint, GLuint, GLuint)) glGetProcAddress("glUniform2ui"), ASSERT(glUniform2ui),
		glUniform3ui = (void (__stdcall*)(GLint, GLuint, GLuint, GLuint)) glGetProcAddress("glUniform3ui"), ASSERT(glUniform3ui),
		glUniform4ui = (void (__stdcall*)(GLint, GLuint, GLuint, GLuint, GLuint)) glGetProcAddress("glUniform4ui"), ASSERT(glUniform4ui),
		glUniform1uiv = (void (__stdcall*)(GLint, GLsizei, const GLuint *)) glGetProcAddress("glUniform1uiv"), ASSERT(glUniform1uiv),
		glUniform2uiv = (void (__stdcall*)(GLint, GLsizei, const GLuint *)) glGetProcAddress("glUniform2uiv"), ASSERT(glUniform2uiv),
		glUniform3uiv = (void (__stdcall*)(GLint, GLsizei, const GLuint *)) glGetProcAddress("glUniform3uiv"), ASSERT(glUniform3uiv),
		glUniform4uiv = (void (__stdcall*)(GLint, GLsizei, const GLuint *)) glGetProcAddress("glUniform4uiv"), ASSERT(glUniform4uiv),
		glTexParameterIiv = (void (__stdcall*)(GLenum, GLenum, const GLint *)) glGetProcAddress("glTexParameterIiv"), ASSERT(glTexParameterIiv),
		glTexParameterIuiv = (void (__stdcall*)(GLenum, GLenum, const GLuint *)) glGetProcAddress("glTexParameterIuiv"), ASSERT(glTexParameterIuiv),
		glGetTexParameterIiv = (void (__stdcall*)(GLenum, GLenum, GLint *)) glGetProcAddress("glGetTexParameterIiv"), ASSERT(glGetTexParameterIiv),
		glGetTexParameterIuiv = (void (__stdcall*)(GLenum, GLenum, GLuint *)) glGetProcAddress("glGetTexParameterIuiv"), ASSERT(glGetTexParameterIuiv),
		glClearBufferiv = (void (__stdcall*)(GLenum, GLint, const GLint *)) glGetProcAddress("glClearBufferiv"), ASSERT(glClearBufferiv),
		glClearBufferuiv = (void (__stdcall*)(GLenum, GLint, const GLuint *)) glGetProcAddress("glClearBufferuiv"), ASSERT(glClearBufferuiv),
		glClearBufferfv = (void (__stdcall*)(GLenum, GLint, const GLfloat *)) glGetProcAddress("glClearBufferfv"), ASSERT(glClearBufferfv),
		glClearBufferfi = (void (__stdcall*)(GLenum, GLint, GLfloat, GLint)) glGetProcAddress("glClearBufferfi"), ASSERT(glClearBufferfi),
		glGetStringi = (const GLubyte *(__stdcall*)(GLenum, GLuint)) glGetProcAddress("glGetStringi"), ASSERT(glGetStringi),
		glIsRenderbuffer = (GLboolean (__stdcall*)(GLuint)) glGetProcAddress("glIsRenderbuffer"), ASSERT(glIsRenderbuffer),
		glBindRenderbuffer = (void (__stdcall*)(GLenum, GLuint)) glGetProcAddress("glBindRenderbuffer"), ASSERT(glBindRenderbuffer),
		glDeleteRenderbuffers = (void (__stdcall*)(GLsizei, const GLuint *)) glGetProcAddress("glDeleteRenderbuffers"), ASSERT(glDeleteRenderbuffers),
		glGenRenderbuffers = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glGenRenderbuffers"), ASSERT(glGenRenderbuffers),
		glRenderbufferStorage = (void (__stdcall*)(GLenum, GLenum, GLsizei, GLsizei)) glGetProcAddress("glRenderbufferStorage"), ASSERT(glRenderbufferStorage),
		glGetRenderbufferParameteriv = (void (__stdcall*)(GLenum, GLenum, GLint *)) glGetProcAddress("glGetRenderbufferParameteriv"), ASSERT(glGetRenderbufferParameteriv),
		glIsFramebuffer = (GLboolean (__stdcall*)(GLuint)) glGetProcAddress("glIsFramebuffer"), ASSERT(glIsFramebuffer),
		glBindFramebuffer = (void (__stdcall*)(GLenum, GLuint)) glGetProcAddress("glBindFramebuffer"), ASSERT(glBindFramebuffer),
		glDeleteFramebuffers = (void (__stdcall*)(GLsizei, const GLuint *)) glGetProcAddress("glDeleteFramebuffers"), ASSERT(glDeleteFramebuffers),
		glGenFramebuffers = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glGenFramebuffers"), ASSERT(glGenFramebuffers),
		glCheckFramebufferStatus = (GLenum (__stdcall*)(GLenum)) glGetProcAddress("glCheckFramebufferStatus"), ASSERT(glCheckFramebufferStatus),
		glFramebufferTexture1D = (void (__stdcall*)(GLenum, GLenum, GLenum, GLuint, GLint)) glGetProcAddress("glFramebufferTexture1D"), ASSERT(glFramebufferTexture1D),
		glFramebufferTexture2D = (void (__stdcall*)(GLenum, GLenum, GLenum, GLuint, GLint)) glGetProcAddress("glFramebufferTexture2D"), ASSERT(glFramebufferTexture2D),
		glFramebufferTexture3D = (void (__stdcall*)(GLenum, GLenum, GLenum, GLuint, GLint, GLint)) glGetProcAddress("glFramebufferTexture3D"), ASSERT(glFramebufferTexture3D),
		glFramebufferRenderbuffer = (void (__stdcall*)(GLenum, GLenum, GLenum, GLuint)) glGetProcAddress("glFramebufferRenderbuffer"), ASSERT(glFramebufferRenderbuffer),
		glGetFramebufferAttachmentParameteriv = (void (__stdcall*)(GLenum, GLenum, GLenum, GLint *)) glGetProcAddress("glGetFramebufferAttachmentParameteriv"), ASSERT(glGetFramebufferAttachmentParameteriv),
		glGenerateMipmap = (void (__stdcall*)(GLenum)) glGetProcAddress("glGenerateMipmap"), ASSERT(glGenerateMipmap),
		glBlitFramebuffer = (void (__stdcall*)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum)) glGetProcAddress("glBlitFramebuffer"), ASSERT(glBlitFramebuffer),
		glRenderbufferStorageMultisample = (void (__stdcall*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei)) glGetProcAddress("glRenderbufferStorageMultisample"), ASSERT(glRenderbufferStorageMultisample),
		glFramebufferTextureLayer = (void (__stdcall*)(GLenum, GLenum, GLuint, GLint, GLint)) glGetProcAddress("glFramebufferTextureLayer"), ASSERT(glFramebufferTextureLayer),
		glMapBufferRange = (void *(__stdcall*)(GLenum, GLintptr, GLsizeiptr, GLbitfield)) glGetProcAddress("glMapBufferRange"), ASSERT(glMapBufferRange),
		glFlushMappedBufferRange = (void (__stdcall*)(GLenum, GLintptr, GLsizeiptr)) glGetProcAddress("glFlushMappedBufferRange"), ASSERT(glFlushMappedBufferRange),
		glBindVertexArray = (void (__stdcall*)(GLuint)) glGetProcAddress("glBindVertexArray"), ASSERT(glBindVertexArray),
		glDeleteVertexArrays = (void (__stdcall*)(GLsizei, const GLuint *)) glGetProcAddress("glDeleteVertexArrays"), ASSERT(glDeleteVertexArrays),
		glGenVertexArrays = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glGenVertexArrays"), ASSERT(glGenVertexArrays),
		glIsVertexArray = (GLboolean (__stdcall*)(GLuint)) glGetProcAddress("glIsVertexArray"), ASSERT(glIsVertexArray);
	# ifndef GL_VERSION_2_1
		case 021:
		glUniformMatrix2x3fv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glUniformMatrix2x3fv"), ASSERT(glUniformMatrix2x3fv),
		glUniformMatrix3x2fv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glUniformMatrix3x2fv"), ASSERT(glUniformMatrix3x2fv),
		glUniformMatrix2x4fv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glUniformMatrix2x4fv"), ASSERT(glUniformMatrix2x4fv),
		glUniformMatrix4x2fv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glUniformMatrix4x2fv"), ASSERT(glUniformMatrix4x2fv),
		glUniformMatrix3x4fv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glUniformMatrix3x4fv"), ASSERT(glUniformMatrix3x4fv),
		glUniformMatrix4x3fv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glUniformMatrix4x3fv"), ASSERT(glUniformMatrix4x3fv);
	# ifndef GL_VERSION_2_0
		case 020:
		glBlendEquationSeparate = (void (__stdcall*)(GLenum, GLenum)) glGetProcAddress("glBlendEquationSeparate"), ASSERT(glBlendEquationSeparate),
		glDrawBuffers = (void (__stdcall*)(GLsizei, const GLenum *)) glGetProcAddress("glDrawBuffers"), ASSERT(glDrawBuffers),
		glStencilOpSeparate = (void (__stdcall*)(GLenum, GLenum, GLenum, GLenum)) glGetProcAddress("glStencilOpSeparate"), ASSERT(glStencilOpSeparate),
		glStencilFuncSeparate = (void (__stdcall*)(GLenum, GLenum, GLint, GLuint)) glGetProcAddress("glStencilFuncSeparate"), ASSERT(glStencilFuncSeparate),
		glStencilMaskSeparate = (void (__stdcall*)(GLenum, GLuint)) glGetProcAddress("glStencilMaskSeparate"), ASSERT(glStencilMaskSeparate),
		glAttachShader = (void (__stdcall*)(GLuint, GLuint)) glGetProcAddress("glAttachShader"), ASSERT(glAttachShader),
		glBindAttribLocation = (void (__stdcall*)(GLuint, GLuint, const GLchar *)) glGetProcAddress("glBindAttribLocation"), ASSERT(glBindAttribLocation),
		glCompileShader = (void (__stdcall*)(GLuint)) glGetProcAddress("glCompileShader"), ASSERT(glCompileShader),
		glCreateProgram = (GLuint (__stdcall*)(void)) glGetProcAddress("glCreateProgram"), ASSERT(glCreateProgram),
		glCreateShader = (GLuint (__stdcall*)(GLenum)) glGetProcAddress("glCreateShader"), ASSERT(glCreateShader),
		glDeleteProgram = (void (__stdcall*)(GLuint)) glGetProcAddress("glDeleteProgram"), ASSERT(glDeleteProgram),
		glDeleteShader = (void (__stdcall*)(GLuint)) glGetProcAddress("glDeleteShader"), ASSERT(glDeleteShader),
		glDetachShader = (void (__stdcall*)(GLuint, GLuint)) glGetProcAddress("glDetachShader"), ASSERT(glDetachShader),
		glDisableVertexAttribArray = (void (__stdcall*)(GLuint)) glGetProcAddress("glDisableVertexAttribArray"), ASSERT(glDisableVertexAttribArray),
		glEnableVertexAttribArray = (void (__stdcall*)(GLuint)) glGetProcAddress("glEnableVertexAttribArray"), ASSERT(glEnableVertexAttribArray),
		glGetActiveAttrib = (void (__stdcall*)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *)) glGetProcAddress("glGetActiveAttrib"), ASSERT(glGetActiveAttrib),
		glGetActiveUniform = (void (__stdcall*)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *)) glGetProcAddress("glGetActiveUniform"), ASSERT(glGetActiveUniform),
		glGetAttachedShaders = (void (__stdcall*)(GLuint, GLsizei, GLsizei *, GLuint *)) glGetProcAddress("glGetAttachedShaders"), ASSERT(glGetAttachedShaders),
		glGetAttribLocation = (GLint (__stdcall*)(GLuint, const GLchar *)) glGetProcAddress("glGetAttribLocation"), ASSERT(glGetAttribLocation),
		glGetProgramiv = (void (__stdcall*)(GLuint, GLenum, GLint *)) glGetProcAddress("glGetProgramiv"), ASSERT(glGetProgramiv),
		glGetProgramInfoLog = (void (__stdcall*)(GLuint, GLsizei, GLsizei *, GLchar *)) glGetProcAddress("glGetProgramInfoLog"), ASSERT(glGetProgramInfoLog),
		glGetShaderiv = (void (__stdcall*)(GLuint, GLenum, GLint *)) glGetProcAddress("glGetShaderiv"), ASSERT(glGetShaderiv),
		glGetShaderInfoLog = (void (__stdcall*)(GLuint, GLsizei, GLsizei *, GLchar *)) glGetProcAddress("glGetShaderInfoLog"), ASSERT(glGetShaderInfoLog),
		glGetShaderSource = (void (__stdcall*)(GLuint, GLsizei, GLsizei *, GLchar *)) glGetProcAddress("glGetShaderSource"), ASSERT(glGetShaderSource),
		glGetUniformLocation = (GLint (__stdcall*)(GLuint, const GLchar *)) glGetProcAddress("glGetUniformLocation"), ASSERT(glGetUniformLocation),
		glGetUniformfv = (void (__stdcall*)(GLuint, GLint, GLfloat *)) glGetProcAddress("glGetUniformfv"), ASSERT(glGetUniformfv),
		glGetUniformiv = (void (__stdcall*)(GLuint, GLint, GLint *)) glGetProcAddress("glGetUniformiv"), ASSERT(glGetUniformiv),
		glGetVertexAttribdv = (void (__stdcall*)(GLuint, GLenum, GLdouble *)) glGetProcAddress("glGetVertexAttribdv"), ASSERT(glGetVertexAttribdv),
		glGetVertexAttribfv = (void (__stdcall*)(GLuint, GLenum, GLfloat *)) glGetProcAddress("glGetVertexAttribfv"), ASSERT(glGetVertexAttribfv),
		glGetVertexAttribiv = (void (__stdcall*)(GLuint, GLenum, GLint *)) glGetProcAddress("glGetVertexAttribiv"), ASSERT(glGetVertexAttribiv),
		glGetVertexAttribPointerv = (void (__stdcall*)(GLuint, GLenum, void **)) glGetProcAddress("glGetVertexAttribPointerv"), ASSERT(glGetVertexAttribPointerv),
		glIsProgram = (GLboolean (__stdcall*)(GLuint)) glGetProcAddress("glIsProgram"), ASSERT(glIsProgram),
		glIsShader = (GLboolean (__stdcall*)(GLuint)) glGetProcAddress("glIsShader"), ASSERT(glIsShader),
		glLinkProgram = (void (__stdcall*)(GLuint)) glGetProcAddress("glLinkProgram"), ASSERT(glLinkProgram),
		glShaderSource = (void (__stdcall*)(GLuint, GLsizei, const GLchar *const*, const GLint *)) glGetProcAddress("glShaderSource"), ASSERT(glShaderSource),
		glUseProgram = (void (__stdcall*)(GLuint)) glGetProcAddress("glUseProgram"), ASSERT(glUseProgram),
		glUniform1f = (void (__stdcall*)(GLint, GLfloat)) glGetProcAddress("glUniform1f"), ASSERT(glUniform1f),
		glUniform2f = (void (__stdcall*)(GLint, GLfloat, GLfloat)) glGetProcAddress("glUniform2f"), ASSERT(glUniform2f),
		glUniform3f = (void (__stdcall*)(GLint, GLfloat, GLfloat, GLfloat)) glGetProcAddress("glUniform3f"), ASSERT(glUniform3f),
		glUniform4f = (void (__stdcall*)(GLint, GLfloat, GLfloat, GLfloat, GLfloat)) glGetProcAddress("glUniform4f"), ASSERT(glUniform4f),
		glUniform1i = (void (__stdcall*)(GLint, GLint)) glGetProcAddress("glUniform1i"), ASSERT(glUniform1i),
		glUniform2i = (void (__stdcall*)(GLint, GLint, GLint)) glGetProcAddress("glUniform2i"), ASSERT(glUniform2i),
		glUniform3i = (void (__stdcall*)(GLint, GLint, GLint, GLint)) glGetProcAddress("glUniform3i"), ASSERT(glUniform3i),
		glUniform4i = (void (__stdcall*)(GLint, GLint, GLint, GLint, GLint)) glGetProcAddress("glUniform4i"), ASSERT(glUniform4i),
		glUniform1fv = (void (__stdcall*)(GLint, GLsizei, const GLfloat *)) glGetProcAddress("glUniform1fv"), ASSERT(glUniform1fv),
		glUniform2fv = (void (__stdcall*)(GLint, GLsizei, const GLfloat *)) glGetProcAddress("glUniform2fv"), ASSERT(glUniform2fv),
		glUniform3fv = (void (__stdcall*)(GLint, GLsizei, const GLfloat *)) glGetProcAddress("glUniform3fv"), ASSERT(glUniform3fv),
		glUniform4fv = (void (__stdcall*)(GLint, GLsizei, const GLfloat *)) glGetProcAddress("glUniform4fv"), ASSERT(glUniform4fv),
		glUniform1iv = (void (__stdcall*)(GLint, GLsizei, const GLint *)) glGetProcAddress("glUniform1iv"), ASSERT(glUniform1iv),
		glUniform2iv = (void (__stdcall*)(GLint, GLsizei, const GLint *)) glGetProcAddress("glUniform2iv"), ASSERT(glUniform2iv),
		glUniform3iv = (void (__stdcall*)(GLint, GLsizei, const GLint *)) glGetProcAddress("glUniform3iv"), ASSERT(glUniform3iv),
		glUniform4iv = (void (__stdcall*)(GLint, GLsizei, const GLint *)) glGetProcAddress("glUniform4iv"), ASSERT(glUniform4iv),
		glUniformMatrix2fv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glUniformMatrix2fv"), ASSERT(glUniformMatrix2fv),
		glUniformMatrix3fv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glUniformMatrix3fv"), ASSERT(glUniformMatrix3fv),
		glUniformMatrix4fv = (void (__stdcall*)(GLint, GLsizei, GLboolean, const GLfloat *)) glGetProcAddress("glUniformMatrix4fv"), ASSERT(glUniformMatrix4fv),
		glValidateProgram = (void (__stdcall*)(GLuint)) glGetProcAddress("glValidateProgram"), ASSERT(glValidateProgram),
		glVertexAttrib1d = (void (__stdcall*)(GLuint, GLdouble)) glGetProcAddress("glVertexAttrib1d"), ASSERT(glVertexAttrib1d),
		glVertexAttrib1dv = (void (__stdcall*)(GLuint, const GLdouble *)) glGetProcAddress("glVertexAttrib1dv"), ASSERT(glVertexAttrib1dv),
		glVertexAttrib1f = (void (__stdcall*)(GLuint, GLfloat)) glGetProcAddress("glVertexAttrib1f"), ASSERT(glVertexAttrib1f),
		glVertexAttrib1fv = (void (__stdcall*)(GLuint, const GLfloat *)) glGetProcAddress("glVertexAttrib1fv"), ASSERT(glVertexAttrib1fv),
		glVertexAttrib1s = (void (__stdcall*)(GLuint, GLshort)) glGetProcAddress("glVertexAttrib1s"), ASSERT(glVertexAttrib1s),
		glVertexAttrib1sv = (void (__stdcall*)(GLuint, const GLshort *)) glGetProcAddress("glVertexAttrib1sv"), ASSERT(glVertexAttrib1sv),
		glVertexAttrib2d = (void (__stdcall*)(GLuint, GLdouble, GLdouble)) glGetProcAddress("glVertexAttrib2d"), ASSERT(glVertexAttrib2d),
		glVertexAttrib2dv = (void (__stdcall*)(GLuint, const GLdouble *)) glGetProcAddress("glVertexAttrib2dv"), ASSERT(glVertexAttrib2dv),
		glVertexAttrib2f = (void (__stdcall*)(GLuint, GLfloat, GLfloat)) glGetProcAddress("glVertexAttrib2f"), ASSERT(glVertexAttrib2f),
		glVertexAttrib2fv = (void (__stdcall*)(GLuint, const GLfloat *)) glGetProcAddress("glVertexAttrib2fv"), ASSERT(glVertexAttrib2fv),
		glVertexAttrib2s = (void (__stdcall*)(GLuint, GLshort, GLshort)) glGetProcAddress("glVertexAttrib2s"), ASSERT(glVertexAttrib2s),
		glVertexAttrib2sv = (void (__stdcall*)(GLuint, const GLshort *)) glGetProcAddress("glVertexAttrib2sv"), ASSERT(glVertexAttrib2sv),
		glVertexAttrib3d = (void (__stdcall*)(GLuint, GLdouble, GLdouble, GLdouble)) glGetProcAddress("glVertexAttrib3d"), ASSERT(glVertexAttrib3d),
		glVertexAttrib3dv = (void (__stdcall*)(GLuint, const GLdouble *)) glGetProcAddress("glVertexAttrib3dv"), ASSERT(glVertexAttrib3dv),
		glVertexAttrib3f = (void (__stdcall*)(GLuint, GLfloat, GLfloat, GLfloat)) glGetProcAddress("glVertexAttrib3f"), ASSERT(glVertexAttrib3f),
		glVertexAttrib3fv = (void (__stdcall*)(GLuint, const GLfloat *)) glGetProcAddress("glVertexAttrib3fv"), ASSERT(glVertexAttrib3fv),
		glVertexAttrib3s = (void (__stdcall*)(GLuint, GLshort, GLshort, GLshort)) glGetProcAddress("glVertexAttrib3s"), ASSERT(glVertexAttrib3s),
		glVertexAttrib3sv = (void (__stdcall*)(GLuint, const GLshort *)) glGetProcAddress("glVertexAttrib3sv"), ASSERT(glVertexAttrib3sv),
		glVertexAttrib4Nbv = (void (__stdcall*)(GLuint, const GLbyte *)) glGetProcAddress("glVertexAttrib4Nbv"), ASSERT(glVertexAttrib4Nbv),
		glVertexAttrib4Niv = (void (__stdcall*)(GLuint, const GLint *)) glGetProcAddress("glVertexAttrib4Niv"), ASSERT(glVertexAttrib4Niv),
		glVertexAttrib4Nsv = (void (__stdcall*)(GLuint, const GLshort *)) glGetProcAddress("glVertexAttrib4Nsv"), ASSERT(glVertexAttrib4Nsv),
		glVertexAttrib4Nub = (void (__stdcall*)(GLuint, GLubyte, GLubyte, GLubyte, GLubyte)) glGetProcAddress("glVertexAttrib4Nub"), ASSERT(glVertexAttrib4Nub),
		glVertexAttrib4Nubv = (void (__stdcall*)(GLuint, const GLubyte *)) glGetProcAddress("glVertexAttrib4Nubv"), ASSERT(glVertexAttrib4Nubv),
		glVertexAttrib4Nuiv = (void (__stdcall*)(GLuint, const GLuint *)) glGetProcAddress("glVertexAttrib4Nuiv"), ASSERT(glVertexAttrib4Nuiv),
		glVertexAttrib4Nusv = (void (__stdcall*)(GLuint, const GLushort *)) glGetProcAddress("glVertexAttrib4Nusv"), ASSERT(glVertexAttrib4Nusv),
		glVertexAttrib4bv = (void (__stdcall*)(GLuint, const GLbyte *)) glGetProcAddress("glVertexAttrib4bv"), ASSERT(glVertexAttrib4bv),
		glVertexAttrib4d = (void (__stdcall*)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble)) glGetProcAddress("glVertexAttrib4d"), ASSERT(glVertexAttrib4d),
		glVertexAttrib4dv = (void (__stdcall*)(GLuint, const GLdouble *)) glGetProcAddress("glVertexAttrib4dv"), ASSERT(glVertexAttrib4dv),
		glVertexAttrib4f = (void (__stdcall*)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat)) glGetProcAddress("glVertexAttrib4f"), ASSERT(glVertexAttrib4f),
		glVertexAttrib4fv = (void (__stdcall*)(GLuint, const GLfloat *)) glGetProcAddress("glVertexAttrib4fv"), ASSERT(glVertexAttrib4fv),
		glVertexAttrib4iv = (void (__stdcall*)(GLuint, const GLint *)) glGetProcAddress("glVertexAttrib4iv"), ASSERT(glVertexAttrib4iv),
		glVertexAttrib4s = (void (__stdcall*)(GLuint, GLshort, GLshort, GLshort, GLshort)) glGetProcAddress("glVertexAttrib4s"), ASSERT(glVertexAttrib4s),
		glVertexAttrib4sv = (void (__stdcall*)(GLuint, const GLshort *)) glGetProcAddress("glVertexAttrib4sv"), ASSERT(glVertexAttrib4sv),
		glVertexAttrib4ubv = (void (__stdcall*)(GLuint, const GLubyte *)) glGetProcAddress("glVertexAttrib4ubv"), ASSERT(glVertexAttrib4ubv),
		glVertexAttrib4uiv = (void (__stdcall*)(GLuint, const GLuint *)) glGetProcAddress("glVertexAttrib4uiv"), ASSERT(glVertexAttrib4uiv),
		glVertexAttrib4usv = (void (__stdcall*)(GLuint, const GLushort *)) glGetProcAddress("glVertexAttrib4usv"), ASSERT(glVertexAttrib4usv),
		glVertexAttribPointer = (void (__stdcall*)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *)) glGetProcAddress("glVertexAttribPointer"), ASSERT(glVertexAttribPointer);
	# ifndef GL_VERSION_1_5
		case 015:
		glGenQueries = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glGenQueries"), ASSERT(glGenQueries),
		glDeleteQueries = (void (__stdcall*)(GLsizei, const GLuint *)) glGetProcAddress("glDeleteQueries"), ASSERT(glDeleteQueries),
		glIsQuery = (GLboolean (__stdcall*)(GLuint)) glGetProcAddress("glIsQuery"), ASSERT(glIsQuery),
		glBeginQuery = (void (__stdcall*)(GLenum, GLuint)) glGetProcAddress("glBeginQuery"), ASSERT(glBeginQuery),
		glEndQuery = (void (__stdcall*)(GLenum)) glGetProcAddress("glEndQuery"), ASSERT(glEndQuery),
		glGetQueryiv = (void (__stdcall*)(GLenum, GLenum, GLint *)) glGetProcAddress("glGetQueryiv"), ASSERT(glGetQueryiv),
		glGetQueryObjectiv = (void (__stdcall*)(GLuint, GLenum, GLint *)) glGetProcAddress("glGetQueryObjectiv"), ASSERT(glGetQueryObjectiv),
		glGetQueryObjectuiv = (void (__stdcall*)(GLuint, GLenum, GLuint *)) glGetProcAddress("glGetQueryObjectuiv"), ASSERT(glGetQueryObjectuiv),
		glBindBuffer = (void (__stdcall*)(GLenum, GLuint)) glGetProcAddress("glBindBuffer"), ASSERT(glBindBuffer),
		glDeleteBuffers = (void (__stdcall*)(GLsizei, const GLuint *)) glGetProcAddress("glDeleteBuffers"), ASSERT(glDeleteBuffers);
		glGenBuffers = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glGenBuffers"); ASSERT(glGenBuffers); // #@?!
		glIsBuffer = (GLboolean (__stdcall*)(GLuint)) glGetProcAddress("glIsBuffer"), ASSERT(glIsBuffer),
		glBufferData = (void (__stdcall*)(GLenum, GLsizeiptr, const void *, GLenum)) glGetProcAddress("glBufferData"), ASSERT(glBufferData),
		glBufferSubData = (void (__stdcall*)(GLenum, GLintptr, GLsizeiptr, const void *)) glGetProcAddress("glBufferSubData"), ASSERT(glBufferSubData),
		glGetBufferSubData = (void (__stdcall*)(GLenum, GLintptr, GLsizeiptr, void *)) glGetProcAddress("glGetBufferSubData"), ASSERT(glGetBufferSubData),
		glMapBuffer = (void *(__stdcall*)(GLenum, GLenum)) glGetProcAddress("glMapBuffer"), ASSERT(glMapBuffer),
		glUnmapBuffer = (GLboolean (__stdcall*)(GLenum)) glGetProcAddress("glUnmapBuffer"), ASSERT(glUnmapBuffer),
		glGetBufferParameteriv = (void (__stdcall*)(GLenum, GLenum, GLint *)) glGetProcAddress("glGetBufferParameteriv"), ASSERT(glGetBufferParameteriv),
		glGetBufferPointerv = (void (__stdcall*)(GLenum, GLenum, void **)) glGetProcAddress("glGetBufferPointerv"), ASSERT(glGetBufferPointerv);
	# ifndef GL_VERSION_1_4
		case 014:
		glBlendFuncSeparate = (void(__stdcall*)(GLenum, GLenum, GLenum, GLenum)) glGetProcAddress("glBlendFuncSeparate"), ASSERT(glBlendFuncSeparate),
		glMultiDrawArrays = (void(__stdcall*)(GLenum, const GLint *, const GLsizei *, GLsizei)) glGetProcAddress("glMultiDrawArrays"), ASSERT(glMultiDrawArrays),
		glMultiDrawElements = (void(__stdcall*)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei)) glGetProcAddress("glMultiDrawElements"), ASSERT(glMultiDrawElements),
		glPointParameterf = (void(__stdcall*)(GLenum, GLfloat)) glGetProcAddress("glPointParameterf"), ASSERT(glPointParameterf),
		glPointParameterfv = (void(__stdcall*)(GLenum, const GLfloat *)) glGetProcAddress("glPointParameterfv"), ASSERT(glPointParameterfv),
		glPointParameteri = (void(__stdcall*)(GLenum, GLint)) glGetProcAddress("glPointParameteri"), ASSERT(glPointParameteri),
		glPointParameteriv = (void(__stdcall*)(GLenum, const GLint *)) glGetProcAddress("glPointParameteriv"), ASSERT(glPointParameteriv),
		glBlendColor = (void(__stdcall*)(GLfloat, GLfloat, GLfloat, GLfloat)) glGetProcAddress("glBlendColor"), ASSERT(glBlendColor),
		glBlendEquation = (void(__stdcall*)(GLenum)) glGetProcAddress("glBlendEquation"), ASSERT(glBlendEquation);
	# ifndef GL_VERSION_1_3
		case 013:
		glActiveTexture = (void(__stdcall*)(GLenum)) glGetProcAddress("glActiveTexture"), ASSERT(glActiveTexture),
		glSampleCoverage = (void(__stdcall*)(GLfloat, GLboolean)) glGetProcAddress("glSampleCoverage"), ASSERT(glSampleCoverage),
		glCompressedTexImage3D = (void(__stdcall*)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *)) glGetProcAddress("glCompressedTexImage3D"), ASSERT(glCompressedTexImage3D),
		glCompressedTexImage2D = (void(__stdcall*)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *)) glGetProcAddress("glCompressedTexImage2D"), ASSERT(glCompressedTexImage2D),
		glCompressedTexImage1D = (void(__stdcall*)(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *)) glGetProcAddress("glCompressedTexImage1D"), ASSERT(glCompressedTexImage1D),
		glCompressedTexSubImage3D = (void(__stdcall*)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *)) glGetProcAddress("glCompressedTexSubImage3D"), ASSERT(glCompressedTexSubImage3D),
		glCompressedTexSubImage2D = (void(__stdcall*)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *)) glGetProcAddress("glCompressedTexSubImage2D"), ASSERT(glCompressedTexSubImage2D),
		glCompressedTexSubImage1D = (void(__stdcall*)(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *)) glGetProcAddress("glCompressedTexSubImage1D"), ASSERT(glCompressedTexSubImage1D),
		glGetCompressedTexImage = (void(__stdcall*)(GLenum, GLint, void *)) glGetProcAddress("glGetCompressedTexImage"), ASSERT(glGetCompressedTexImage);
	# ifndef GL_VERSION_1_2
		case 012:
		glDrawRangeElements = (void (__stdcall*)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *)) glGetProcAddress("glDrawRangeElements"), ASSERT(glDrawRangeElements),
		glTexImage3D = (void (__stdcall*)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *)) glGetProcAddress("glTexImage3D"), ASSERT(glTexImage3D),
		glTexSubImage3D = (void (__stdcall*)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *)) glGetProcAddress("glTexSubImage3D"), ASSERT(glTexSubImage3D),
		glCopyTexSubImage3D = (void (__stdcall*)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei)) glGetProcAddress("glCopyTexSubImage3D"), ASSERT(glCopyTexSubImage3D);
	# ifndef GL_VERSION_1_1
		case 011:
		glDrawArrays = (void (__stdcall*)(GLenum, GLint, GLsizei)) glGetProcAddress("glDrawArrays"), ASSERT(glDrawArrays),
		glDrawElements = (void (__stdcall*)(GLenum, GLsizei, GLenum, const void *)) glGetProcAddress("glDrawElements"), ASSERT(glDrawElements),
		glGetPointerv = (void (__stdcall*)(GLenum, void **)) glGetProcAddress("glGetPointerv"), ASSERT(glGetPointerv),
		glPolygonOffset = (void (__stdcall*)(GLfloat, GLfloat)) glGetProcAddress("glPolygonOffset"), ASSERT(glPolygonOffset),
		glCopyTexImage1D = (void (__stdcall*)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint)) glGetProcAddress("glCopyTexImage1D"), ASSERT(glCopyTexImage1D),
		glCopyTexImage2D = (void (__stdcall*)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint)) glGetProcAddress("glCopyTexImage2D"), ASSERT(glCopyTexImage2D),
		glCopyTexSubImage1D = (void (__stdcall*)(GLenum, GLint, GLint, GLint, GLint, GLsizei)) glGetProcAddress("glCopyTexSubImage1D"), ASSERT(glCopyTexSubImage1D),
		glCopyTexSubImage2D = (void (__stdcall*)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei)) glGetProcAddress("glCopyTexSubImage2D"), ASSERT(glCopyTexSubImage2D),
		glTexSubImage1D = (void (__stdcall*)(GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void *)) glGetProcAddress("glTexSubImage1D"), ASSERT(glTexSubImage1D),
		glTexSubImage2D = (void (__stdcall*)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *)) glGetProcAddress("glTexSubImage2D"), ASSERT(glTexSubImage2D),
		glBindTexture = (void (__stdcall*)(GLenum, GLuint)) glGetProcAddress("glBindTexture"), ASSERT(glBindTexture),
		glDeleteTextures = (void (__stdcall*)(GLsizei, const GLuint *)) glGetProcAddress("glDeleteTextures"), ASSERT(glDeleteTextures),
		glGenTextures = (void (__stdcall*)(GLsizei, GLuint *)) glGetProcAddress("glGenTextures"), ASSERT(glGenTextures),
		glIsTexture = (GLboolean(__stdcall*)(GLuint)) glGetProcAddress("glIsTexture"), ASSERT(glIsTexture);
	# ifndef GL_VERSION_1_0
		case 010:
		glCullFace = (void (__stdcall*)(GLenum)) glGetProcAddress("glCullFace"), ASSERT(glCullFace),
		glFrontFace = (void (__stdcall*)(GLenum)) glGetProcAddress("glFrontFace"), ASSERT(glFrontFace),
		glHint = (void (__stdcall*)(GLenum, GLenum)) glGetProcAddress("glHint"), ASSERT(glHint),
		glLineWidth = (void (__stdcall*)(GLfloat)) glGetProcAddress("glLineWidth"), ASSERT(glLineWidth),
		glPointSize = (void (__stdcall*)(GLfloat)) glGetProcAddress("glPointSize"), ASSERT(glPointSize),
		glPolygonMode = (void (__stdcall*)(GLenum, GLenum)) glGetProcAddress("glPolygonMode"), ASSERT(glPolygonMode),
		glScissor = (void (__stdcall*)(GLint, GLint, GLsizei, GLsizei)) glGetProcAddress("glScissor"), ASSERT(glScissor),
		glTexParameterf = (void (__stdcall*)(GLenum, GLenum, GLfloat)) glGetProcAddress("glTexParameterf"), ASSERT(glTexParameterf),
		glTexParameterfv = (void (__stdcall*)(GLenum, GLenum, const GLfloat *)) glGetProcAddress("glTexParameterfv"), ASSERT(glTexParameterfv),
		glTexParameteri = (void (__stdcall*)(GLenum, GLenum, GLint)) glGetProcAddress("glTexParameteri"), ASSERT(glTexParameteri),
		glTexParameteriv = (void (__stdcall*)(GLenum, GLenum, const GLint *)) glGetProcAddress("glTexParameteriv"), ASSERT(glTexParameteriv),
		glTexImage1D = (void (__stdcall*)(GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void *)) glGetProcAddress("glTexImage1D"), ASSERT(glTexImage1D),
		glTexImage2D = (void (__stdcall*)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *)) glGetProcAddress("glTexImage2D"), ASSERT(glTexImage2D),
		glDrawBuffer = (void (__stdcall*)(GLenum)) glGetProcAddress("glDrawBuffer"), ASSERT(glDrawBuffer),
		glClear = (void (__stdcall*)(GLbitfield)) glGetProcAddress("glClear"), ASSERT(glClear),
		glClearColor = (void (__stdcall*)(GLfloat, GLfloat, GLfloat, GLfloat)) glGetProcAddress("glClearColor"), ASSERT(glClearColor),
		glClearStencil = (void (__stdcall*)(GLint)) glGetProcAddress("glClearStencil"), ASSERT(glClearStencil),
		glClearDepth = (void (__stdcall*)(GLdouble)) glGetProcAddress("glClearDepth"), ASSERT(glClearDepth),
		glStencilMask = (void (__stdcall*)(GLuint)) glGetProcAddress("glStencilMask"), ASSERT(glStencilMask),
		glColorMask = (void (__stdcall*)(GLboolean, GLboolean, GLboolean, GLboolean)) glGetProcAddress("glColorMask"), ASSERT(glColorMask),
		glDepthMask = (void (__stdcall*)(GLboolean)) glGetProcAddress("glDepthMask"), ASSERT(glDepthMask),
		glDisable = (void (__stdcall*)(GLenum)) glGetProcAddress("glDisable"), ASSERT(glDisable),
		glEnable = (void (__stdcall*)(GLenum)) glGetProcAddress("glEnable"), ASSERT(glEnable),
		glFinish = (void (__stdcall*)(void)) glGetProcAddress("glFinish"), ASSERT(glFinish),
		glFlush = (void (__stdcall*)(void)) glGetProcAddress("glFlush"), ASSERT(glFlush),
		glBlendFunc = (void (__stdcall*)(GLenum, GLenum)) glGetProcAddress("glBlendFunc"), ASSERT(glBlendFunc),
		glLogicOp = (void (__stdcall*)(GLenum)) glGetProcAddress("glLogicOp"), ASSERT(glLogicOp),
		glStencilFunc = (void (__stdcall*)(GLenum, GLint, GLuint)) glGetProcAddress("glStencilFunc"), ASSERT(glStencilFunc),
		glStencilOp = (void (__stdcall*)(GLenum, GLenum, GLenum)) glGetProcAddress("glStencilOp"), ASSERT(glStencilOp),
		glDepthFunc = (void (__stdcall*)(GLenum)) glGetProcAddress("glDepthFunc"), ASSERT(glDepthFunc),
		glPixelStoref = (void (__stdcall*)(GLenum, GLfloat)) glGetProcAddress("glPixelStoref"), ASSERT(glPixelStoref),
		glPixelStorei = (void (__stdcall*)(GLenum, GLint)) glGetProcAddress("glPixelStorei"), ASSERT(glPixelStorei),
		glReadBuffer = (void (__stdcall*)(GLenum)) glGetProcAddress("glReadBuffer"), ASSERT(glReadBuffer),
		glReadPixels = (void (__stdcall*)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void *)) glGetProcAddress("glReadPixels"), ASSERT(glReadPixels),
		glGetBooleanv = (void (__stdcall*)(GLenum, GLboolean *)) glGetProcAddress("glGetBooleanv"), ASSERT(glGetBooleanv),
		glGetDoublev = (void (__stdcall*)(GLenum, GLdouble *)) glGetProcAddress("glGetDoublev"), ASSERT(glGetDoublev),
		glGetError = (GLenum (__stdcall*)(void)) glGetProcAddress("glGetError"), ASSERT(glGetError),
		glGetFloatv = (void (__stdcall*)(GLenum, GLfloat *)) glGetProcAddress("glGetFloatv"), ASSERT(glGetFloatv),
		glGetIntegerv = (void (__stdcall*)(GLenum, GLint *)) glGetProcAddress("glGetIntegerv"), ASSERT(glGetIntegerv),
		glGetString = (void (__stdcall*)(GLenum)) glGetProcAddress("glGetString"), ASSERT(glGetString),
		glGetTexImage = (void (__stdcall*)(GLenum, GLint, GLenum, GLenum, void *)) glGetProcAddress("glGetTexImage"), ASSERT(glGetTexImage),
		glGetTexParameterfv = (void (__stdcall*)(GLenum, GLenum, GLfloat *)) glGetProcAddress("glGetTexParameterfv"), ASSERT(glGetTexParameterfv),
		glGetTexParameteriv = (void (__stdcall*)(GLenum, GLenum, GLint *)) glGetProcAddress("glGetTexParameteriv"), ASSERT(glGetTexParameteriv),
		glGetTexLevelParameterfv = (void (__stdcall*)(GLenum, GLint, GLenum, GLfloat *)) glGetProcAddress("glGetTexLevelParameterfv"), ASSERT(glGetTexLevelParameterfv),
		glGetTexLevelParameteriv = (void (__stdcall*)(GLenum, GLint, GLenum, GLint *)) glGetProcAddress("glGetTexLevelParameteriv"), ASSERT(glGetTexLevelParameteriv),
		glIsEnabled = (GLboolean (__stdcall*)(GLenum)) glGetProcAddress("glIsEnabled"), ASSERT(glIsEnabled),
		glDepthRange = (void (__stdcall*)(GLdouble, GLdouble)) glGetProcAddress("glDepthRange"), ASSERT(glDepthRange),
		glViewport = (void (__stdcall*)(GLint, GLint, GLsizei, GLsizei)) glGetProcAddress("glViewport"), ASSERT(glViewport);
	# endif
	# endif
	# endif
	# endif
	# endif
	# endif
	# endif
	# endif
	# endif
	# endif
	# endif
	# endif
	# endif
	# endif
	# endif
	# endif
	# endif
	# endif
		default: return;
	}
}
void GLRC::operator = (GLRC&& a)noexcept
{
	GLRC:: ~ GLRC( );
	HGLRC = a.HGLRC, HDC = a.HDC;
	a.HGLRC = NULL, a.HDC = NULL;
}
GLRC::operator ::HDC(void)const
{
// ASSERT(wglGetCurrentDC( ) == HDC)
	return HGLRC ? HDC : NULL;
}

# ifndef WGL_ARB_extensions_string
const char *(__stdcall*wglGetExtensionsString)(HDC) = nullptr;
# endif

# ifndef WGL_ARB_create_context
HGLRC (__stdcall*wglCreateContextAttribs)(HDC, HGLRC, const int *) = nullptr;
# endif

# ifndef WGL_ARB_pixel_format
BOOL (__stdcall*wglGetPixelFormatAttribiv)(HDC, int, int, UINT, const int *, int *) = nullptr;
BOOL (__stdcall*wglGetPixelFormatAttribfv)(HDC, int, int, UINT, const int *, FLOAT *) = nullptr;
BOOL (__stdcall*wglChoosePixelFormat)(HDC, const int *, const FLOAT *, UINT, int *, UINT *) = nullptr;
# endif

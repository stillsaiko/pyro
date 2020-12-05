# pragma once
# ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# endif

# include <gl/gl.h>

extern GLenum glGetLastError(void);

# ifndef NDEBUG
# include "error.h"
extern const char *gl_Error;
# define GL_ASSERT(...) ((__VA_ARGS__), glGetLastError( ) ? ERROR(gl_Error) : true)
# else
# define GL_ASSERT(...) ((__VA_ARGS__), glGetLastError( ) == GL_NO_ERROR)
# endif

extern GLubyte gl_Version;

/*
(GL & 0xFFF8) == 0x0500
[GL & 0x0007]
extern void GL_ERROR(const char *FILE = "C:/USERS/SAIKO/GITHUB/PYRO/GL.H",
 int LINE = 0, const char *FUNCTION = "GL_ERROR", const char *ARGS = "glGetError");
# define GL_ERROR(...) GL_ERROR(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
# ifndef NDEBUG
# define GL_ASSERT(...) !(__VA_ARGS__) ? GL_ERROR(#__VA_ARGS__), false : true
# else
# define GL_ASSERT()
# endif
*/

// typedef

# ifndef GL_VERSION_4_6
# ifndef GL_VERSION_4_5
# ifndef GL_VERSION_4_4
# ifndef GL_VERSION_4_3
# ifndef GL_VERSION_4_2
# ifndef GL_VERSION_4_1
# ifndef GL_VERSION_4_0
# ifndef GL_VERSION_3_3
# ifndef GL_VERSION_3_2
typedef struct __GLsync *GLsync;
typedef unsigned long long GLuint64;
typedef long long GLint64;
# ifndef GL_VERSION_3_1
# ifndef GL_VERSION_3_0
typedef unsigned short GLhalf;
# ifndef GL_VERSION_2_1
# ifndef GL_VERSION_2_0
typedef char GLchar;
typedef short GLshort;
typedef signed char GLbyte;
typedef unsigned short GLushort;
# ifndef GL_VERSION_1_5
typedef size_t GLsizeiptr;
typedef intptr_t GLintptr;
# ifndef GL_VERSION_1_4
# ifndef GL_VERSION_1_3
# ifndef GL_VERSION_1_2
# ifndef GL_VERSION_1_1
typedef float GLclampf;
typedef double GLclampd;
# ifndef GL_VERSION_1_0
typedef void GLvoid;
typedef unsigned int GLenum;
typedef float GLfloat;
typedef int GLint;
typedef int GLsizei;
typedef unsigned int GLbitfield;
typedef double GLdouble;
typedef unsigned int GLuint;
typedef unsigned char GLubyte;
typedef unsigned char GLboolean;
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
# endif

  enum
GLbitfield_t :
GLbitfield
{
# ifndef GL_VERSION_4_6
	GL_CONTEXT_FLAG_NO_ERROR_BIT = 0x00000008,
# ifndef GL_VERSION_4_5
	GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT = 0x00000004,
# ifndef GL_VERSION_4_4
	GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT = 0x00004000,
	GL_QUERY_BUFFER_BARRIER_BIT         = 0x00008000,
	GL_MAP_PERSISTENT_BIT  = 0x0040,
	GL_MAP_COHERENT_BIT    = 0x0080,
	GL_DYNAMIC_STORAGE_BIT = 0x0100,
	GL_CLIENT_STORAGE_BIT  = 0x0200,
# ifndef GL_VERSION_4_3
	GL_CONTEXT_FLAG_DEBUG_BIT     = 0x00000002,
	GL_COMPUTE_SHADER_BIT         = 0x00000020,
	GL_SHADER_STORAGE_BARRIER_BIT = 0x00002000,
# ifndef GL_VERSION_4_2
	GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT = 0x00000001,
	GL_ELEMENT_ARRAY_BARRIER_BIT       = 0x00000002,
	GL_UNIFORM_BARRIER_BIT             = 0x00000004,
	GL_TEXTURE_FETCH_BARRIER_BIT       = 0x00000008,
	GL_SHADER_IMAGE_ACCESS_BARRIER_BIT = 0x00000020,
	GL_COMMAND_BARRIER_BIT             = 0x00000040,
	GL_PIXEL_BUFFER_BARRIER_BIT        = 0x00000080,
	GL_TEXTURE_UPDATE_BARRIER_BIT      = 0x00000100,
	GL_BUFFER_UPDATE_BARRIER_BIT       = 0x00000200,
	GL_FRAMEBUFFER_BARRIER_BIT         = 0x00000400,
	GL_TRANSFORM_FEEDBACK_BARRIER_BIT  = 0x00000800,
	GL_ATOMIC_COUNTER_BARRIER_BIT      = 0x00001000,
	GL_ALL_BARRIER_BITS                = 0xFFFFFFFF,
# ifndef GL_VERSION_4_1
	GL_VERTEX_SHADER_BIT          = 0x00000001,
	GL_FRAGMENT_SHADER_BIT        = 0x00000002,
	GL_GEOMETRY_SHADER_BIT        = 0x00000004,
	GL_TESS_CONTROL_SHADER_BIT    = 0x00000008,
	GL_TESS_EVALUATION_SHADER_BIT = 0x00000010,
	GL_ALL_SHADER_BITS            = 0xFFFFFFFF,
# ifndef GL_VERSION_4_0
# ifndef GL_VERSION_3_3
# ifndef GL_VERSION_3_2
	GL_CONTEXT_CORE_PROFILE_BIT          = 0x00000001,
	GL_CONTEXT_COMPATIBILITY_PROFILE_BIT = 0x00000002,
	GL_SYNC_FLUSH_COMMANDS_BIT = 0x00000001,
# ifndef GL_VERSION_3_1
	GL_INVALID_INDEX = 0xFFFFFFFFu,
# ifndef GL_VERSION_3_0
	GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT = 0x00000001,
	GL_MAP_READ_BIT              = 0x0001,
	GL_MAP_WRITE_BIT             = 0x0002,
	GL_MAP_INVALIDATE_RANGE_BIT  = 0x0004,
	GL_MAP_INVALIDATE_BUFFER_BIT = 0x0008,
	GL_MAP_FLUSH_EXPLICIT_BIT    = 0x0010,
	GL_MAP_UNSYNCHRONIZED_BIT    = 0x0020,
# ifndef GL_VERSION_2_1
# ifndef GL_VERSION_2_0
# ifndef GL_VERSION_1_5
# ifndef GL_VERSION_1_4
# ifndef GL_VERSION_1_3
# ifndef GL_VERSION_1_2
# ifndef GL_VERSION_1_1
# ifndef GL_VERSION_1_0
	GL_DEPTH_BUFFER_BIT   = 0x00000100,
	GL_STENCIL_BUFFER_BIT = 0x00000400,
	GL_COLOR_BUFFER_BIT   = 0x00004000
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
# endif
};

constexpr GLbitfield_t operator | (GLbitfield_t A, GLbitfield_t B)
{
	return static_cast<GLbitfield_t>(A | B);
}

# ifndef GL_VERSION_4_6
extern void (__stdcall*glSpecializeShader)(GLuint, const GLchar *, GLuint, const GLuint *, const GLuint *);
extern void (__stdcall*glMultiDrawArraysIndirectCount)(GLenum, const void *, GLintptr, GLsizei, GLsizei);
extern void (__stdcall*glMultiDrawElementsIndirectCount)(GLenum, GLenum, const void *, GLintptr, GLsizei, GLsizei);
extern void (__stdcall*glPolygonOffsetClamp)(GLfloat, GLfloat, GLfloat);
# ifndef GL_VERSION_4_5
extern void (__stdcall*glClipControl)(GLenum, GLenum);
extern void (__stdcall*glCreateTransformFeedbacks)(GLsizei, GLuint *);
extern void (__stdcall*glTransformFeedbackBufferBase)(GLuint, GLuint, GLuint);
extern void (__stdcall*glTransformFeedbackBufferRange)(GLuint, GLuint, GLuint, GLintptr, GLsizeiptr);
extern void (__stdcall*glGetTransformFeedbackiv)(GLuint, GLenum, GLint *);
extern void (__stdcall*glGetTransformFeedbacki_v)(GLuint, GLenum, GLuint, GLint *);
extern void (__stdcall*glGetTransformFeedbacki64_v)(GLuint, GLenum, GLuint, GLint64 *);
extern void (__stdcall*glCreateBuffers)(GLsizei, GLuint *);
extern void (__stdcall*glNamedBufferStorage)(GLuint, GLsizeiptr, const void *, GLbitfield);
extern void (__stdcall*glNamedBufferData)(GLuint, GLsizeiptr, const void *, GLenum);
extern void (__stdcall*glNamedBufferSubData)(GLuint, GLintptr, GLsizeiptr, const void *);
extern void (__stdcall*glCopyNamedBufferSubData)(GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr);
extern void (__stdcall*glClearNamedBufferData)(GLuint, GLenum, GLenum, GLenum, const void *);
extern void (__stdcall*glClearNamedBufferSubData)(GLuint, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *);
extern void *(__stdcall*glMapNamedBuffer)(GLuint, GLenum);
extern void *(__stdcall*glMapNamedBufferRange)(GLuint, GLintptr, GLsizeiptr, GLbitfield);
extern GLboolean (__stdcall*glUnmapNamedBuffer)(GLuint);
extern void (__stdcall*glFlushMappedNamedBufferRange)(GLuint, GLintptr, GLsizeiptr);
extern void (__stdcall*glGetNamedBufferParameteriv)(GLuint, GLenum, GLint *);
extern void (__stdcall*glGetNamedBufferParameteri64v)(GLuint, GLenum, GLint64 *);
extern void (__stdcall*glGetNamedBufferPointerv)(GLuint, GLenum, void **);
extern void (__stdcall*glGetNamedBufferSubData)(GLuint, GLintptr, GLsizeiptr, void *);
extern void (__stdcall*glCreateFramebuffers)(GLsizei, GLuint *);
extern void (__stdcall*glNamedFramebufferRenderbuffer)(GLuint, GLenum, GLenum, GLuint);
extern void (__stdcall*glNamedFramebufferParameteri)(GLuint, GLenum, GLint);
extern void (__stdcall*glNamedFramebufferTexture)(GLuint, GLenum, GLuint, GLint);
extern void (__stdcall*glNamedFramebufferTextureLayer)(GLuint, GLenum, GLuint, GLint, GLint);
extern void (__stdcall*glNamedFramebufferDrawBuffer)(GLuint, GLenum);
extern void (__stdcall*glNamedFramebufferDrawBuffers)(GLuint, GLsizei, const GLenum *);
extern void (__stdcall*glNamedFramebufferReadBuffer)(GLuint, GLenum);
extern void (__stdcall*glInvalidateNamedFramebufferData)(GLuint, GLsizei, const GLenum *);
extern void (__stdcall*glInvalidateNamedFramebufferSubData)(GLuint, GLsizei, const GLenum *, GLint x, GLint y, GLsizei, GLsizei);
extern void (__stdcall*glClearNamedFramebufferiv)(GLuint, GLenum, GLint, const GLint *);
extern void (__stdcall*glClearNamedFramebufferuiv)(GLuint, GLenum, GLint, const GLuint *);
extern void (__stdcall*glClearNamedFramebufferfv)(GLuint, GLenum, GLint, const GLfloat *);
extern void (__stdcall*glClearNamedFramebufferfi)(GLuint, GLenum, GLint, GLfloat, GLint);
extern void (__stdcall*glBlitNamedFramebuffer)(GLuint, GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
extern GLenum (__stdcall*glCheckNamedFramebufferStatus)(GLuint, GLenum);
extern void (__stdcall*glGetNamedFramebufferParameteriv)(GLuint, GLenum, GLint *);
extern void (__stdcall*glGetNamedFramebufferAttachmentParameteriv)(GLuint, GLenum, GLenum, GLint *);
extern void (__stdcall*glCreateRenderbuffers)(GLsizei, GLuint *);
extern void (__stdcall*glNamedRenderbufferStorage)(GLuint, GLenum, GLsizei, GLsizei);
extern void (__stdcall*glNamedRenderbufferStorageMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei);
extern void (__stdcall*glGetNamedRenderbufferParameteriv)(GLuint, GLenum, GLint *);
extern void (__stdcall*glCreateTextures)(GLenum, GLsizei, GLuint *);
extern void (__stdcall*glTextureBuffer)(GLuint, GLenum, GLuint);
extern void (__stdcall*glTextureBufferRange)(GLuint, GLenum, GLuint, GLintptr, GLsizeiptr);
extern void (__stdcall*glTextureStorage1D)(GLuint, GLsizei, GLenum, GLsizei);
extern void (__stdcall*glTextureStorage2D)(GLuint, GLsizei, GLenum, GLsizei, GLsizei);
extern void (__stdcall*glTextureStorage3D)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
extern void (__stdcall*glTextureStorage2DMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
extern void (__stdcall*glTextureStorage3DMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
extern void (__stdcall*glTextureSubImage1D)(GLuint, GLint, GLint, GLsizei, GLenum, GLenum, const void *);
extern void (__stdcall*glTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
extern void (__stdcall*glTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
extern void (__stdcall*glCompressedTextureSubImage1D)(GLuint, GLint, GLint, GLsizei, GLenum, GLsizei, const void *);
extern void (__stdcall*glCompressedTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
extern void (__stdcall*glCompressedTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *);
extern void (__stdcall*glCopyTextureSubImage1D)(GLuint, GLint, GLint, GLint x, GLint y, GLsizei);
extern void (__stdcall*glCopyTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLint x, GLint y, GLsizei, GLsizei);
extern void (__stdcall*glCopyTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLint x, GLint y, GLsizei, GLsizei);
extern void (__stdcall*glTextureParameterf)(GLuint, GLenum, GLfloat);
extern void (__stdcall*glTextureParameterfv)(GLuint, GLenum, const GLfloat *);
extern void (__stdcall*glTextureParameteri)(GLuint, GLenum, GLint);
extern void (__stdcall*glTextureParameterIiv)(GLuint, GLenum, const GLint *);
extern void (__stdcall*glTextureParameterIuiv)(GLuint, GLenum, const GLuint *);
extern void (__stdcall*glTextureParameteriv)(GLuint, GLenum, const GLint *);
extern void (__stdcall*glGenerateTextureMipmap)(GLuint);
extern void (__stdcall*glBindTextureUnit)(GLuint, GLuint);
extern void (__stdcall*glGetTextureImage)(GLuint, GLint, GLenum, GLenum, GLsizei, void *);
extern void (__stdcall*glGetCompressedTextureImage)(GLuint, GLint, GLsizei, void *);
extern void (__stdcall*glGetTextureLevelParameterfv)(GLuint, GLint, GLenum, GLfloat *);
extern void (__stdcall*glGetTextureLevelParameteriv)(GLuint, GLint, GLenum, GLint *);
extern void (__stdcall*glGetTextureParameterfv)(GLuint, GLenum, GLfloat *);
extern void (__stdcall*glGetTextureParameterIiv)(GLuint, GLenum, GLint *);
extern void (__stdcall*glGetTextureParameterIuiv)(GLuint, GLenum, GLuint *);
extern void (__stdcall*glGetTextureParameteriv)(GLuint, GLenum, GLint *);
extern void (__stdcall*glCreateVertexArrays)(GLsizei, GLuint *);
extern void (__stdcall*glDisableVertexArrayAttrib)(GLuint, GLuint);
extern void (__stdcall*glEnableVertexArrayAttrib)(GLuint, GLuint);
extern void (__stdcall*glVertexArrayElementBuffer)(GLuint, GLuint);
extern void (__stdcall*glVertexArrayVertexBuffer)(GLuint, GLuint, GLuint, GLintptr, GLsizei);
extern void (__stdcall*glVertexArrayVertexBuffers)(GLuint, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *);
extern void (__stdcall*glVertexArrayAttribBinding)(GLuint, GLuint, GLuint);
extern void (__stdcall*glVertexArrayAttribFormat)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint );
extern void (__stdcall*glVertexArrayAttribIFormat)(GLuint, GLuint, GLint, GLenum, GLuint );
extern void (__stdcall*glVertexArrayAttribLFormat)(GLuint, GLuint, GLint, GLenum, GLuint );
extern void (__stdcall*glVertexArrayBindingDivisor)(GLuint, GLuint, GLuint);
extern void (__stdcall*glGetVertexArrayiv)(GLuint, GLenum, GLint *);
extern void (__stdcall*glGetVertexArrayIndexediv)(GLuint, GLuint, GLenum, GLint *);
extern void (__stdcall*glGetVertexArrayIndexed64iv)(GLuint, GLuint, GLenum, GLint64 *);
extern void (__stdcall*glCreateSamplers)(GLsizei, GLuint *);
extern void (__stdcall*glCreateProgramPipelines)(GLsizei, GLuint *);
extern void (__stdcall*glCreateQueries)(GLenum, GLsizei, GLuint *);
extern void (__stdcall*glGetQueryBufferObjecti64v)(GLuint, GLuint, GLenum, GLintptr);
extern void (__stdcall*glGetQueryBufferObjectiv)(GLuint, GLuint, GLenum, GLintptr);
extern void (__stdcall*glGetQueryBufferObjectui64v)(GLuint, GLuint, GLenum, GLintptr);
extern void (__stdcall*glGetQueryBufferObjectuiv)(GLuint, GLuint, GLenum, GLintptr);
extern void (__stdcall*glMemoryBarrierByRegion)(GLbitfield);
extern void (__stdcall*glGetTextureSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
extern void (__stdcall*glGetCompressedTextureSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLsizei, void *);
extern GLenum (__stdcall*glGetGraphicsResetStatus)(void);
extern void (__stdcall*glGetnCompressedTexImage)(GLenum, GLint, GLsizei, void *);
extern void (__stdcall*glGetnTexImage)(GLenum, GLint, GLenum, GLenum, GLsizei, void *);
extern void (__stdcall*glGetnUniformdv)(GLuint, GLint, GLsizei, GLdouble *);
extern void (__stdcall*glGetnUniformfv)(GLuint, GLint, GLsizei, GLfloat *);
extern void (__stdcall*glGetnUniformiv)(GLuint, GLint, GLsizei, GLint *);
extern void (__stdcall*glGetnUniformuiv)(GLuint, GLint, GLsizei, GLuint *);
extern void (__stdcall*glReadnPixels)(GLint x, GLint y, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
extern void (__stdcall*glTextureBarrier)(void);
# ifndef GL_VERSION_4_4
extern void (__stdcall*glBufferStorage)(GLenum, GLsizeiptr, const void *, GLbitfield);
extern void (__stdcall*glClearTexImage)(GLuint, GLint, GLenum, GLenum, const void *);
extern void (__stdcall*glClearTexSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
extern void (__stdcall*glBindBuffersBase)(GLenum, GLuint, GLsizei, const GLuint *);
extern void (__stdcall*glBindBuffersRange)(GLenum, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizeiptr *);
extern void (__stdcall*glBindTextures)(GLuint, GLsizei, const GLuint *);
extern void (__stdcall*glBindSamplers)(GLuint, GLsizei, const GLuint *);
extern void (__stdcall*glBindImageTextures)(GLuint, GLsizei, const GLuint *);
extern void (__stdcall*glBindVertexBuffers)(GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *);
# ifndef GL_VERSION_4_3
extern void (__stdcall*glClearBufferData)(GLenum, GLenum, GLenum, GLenum, const void *);
extern void (__stdcall*glClearBufferSubData)(GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *);
extern void (__stdcall*glDispatchCompute)(GLuint, GLuint, GLuint);
extern void (__stdcall*glDispatchComputeIndirect)(GLintptr);
extern void (__stdcall*glCopyImageSubData)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
extern void (__stdcall*glFramebufferParameteri)(GLenum, GLenum, GLint);
extern void (__stdcall*glGetFramebufferParameteriv)(GLenum, GLenum, GLint *);
extern void (__stdcall*glGetInternalformati64v)(GLenum, GLenum, GLenum, GLsizei, GLint64 *);
extern void (__stdcall*glInvalidateTexSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
extern void (__stdcall*glInvalidateTexImage)(GLuint, GLint);
extern void (__stdcall*glInvalidateBufferSubData)(GLuint, GLintptr, GLsizeiptr);
extern void (__stdcall*glInvalidateBufferData)(GLuint);
extern void (__stdcall*glInvalidateFramebuffer)(GLenum, GLsizei, const GLenum *);
extern void (__stdcall*glInvalidateSubFramebuffer)(GLenum, GLsizei, const GLenum *, GLint x, GLint y, GLsizei, GLsizei);
extern void (__stdcall*glMultiDrawArraysIndirect)(GLenum, const void *, GLsizei, GLsizei);
extern void (__stdcall*glMultiDrawElementsIndirect)(GLenum, GLenum, const void *, GLsizei, GLsizei);
extern void (__stdcall*glGetProgramInterfaceiv)(GLuint, GLenum, GLenum, GLint *);
extern GLuint (__stdcall*glGetProgramResourceIndex)(GLuint, GLenum, const GLchar *);
extern void (__stdcall*glGetProgramResourceName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
extern void (__stdcall*glGetProgramResourceiv)(GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLint *);
extern GLint (__stdcall*glGetProgramResourceLocation)(GLuint, GLenum, const GLchar *);
extern GLint (__stdcall*glGetProgramResourceLocationIndex)(GLuint, GLenum, const GLchar *);
extern void (__stdcall*glShaderStorageBlockBinding)(GLuint, GLuint, GLuint);
extern void (__stdcall*glTexBufferRange)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr);
extern void (__stdcall*glTexStorage2DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
extern void (__stdcall*glTexStorage3DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
extern void (__stdcall*glTextureView)(GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint);
extern void (__stdcall*glBindVertexBuffer)(GLuint, GLuint, GLintptr, GLsizei);
extern void (__stdcall*glVertexAttribFormat)(GLuint, GLint, GLenum, GLboolean, GLuint );
extern void (__stdcall*glVertexAttribIFormat)(GLuint, GLint, GLenum, GLuint );
extern void (__stdcall*glVertexAttribLFormat)(GLuint, GLint, GLenum, GLuint );
extern void (__stdcall*glVertexAttribBinding)(GLuint, GLuint);
extern void (__stdcall*glVertexBindingDivisor)(GLuint, GLuint);
extern void (__stdcall*glDebugMessageControl)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean);
extern void (__stdcall*glDebugMessageInsert)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *);
extern void (__stdcall*glDebugMessageCallback)(void (__stdcall*)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *, const void *), const void *);
extern GLuint (__stdcall*glGetDebugMessageLog)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *);
extern void (__stdcall*glPushDebugGroup)(GLenum, GLuint, GLsizei, const GLchar *);
extern void (__stdcall*glPopDebugGroup)(void);
extern void (__stdcall*glObjectLabel)(GLenum, GLuint, GLsizei, const GLchar *);
extern void (__stdcall*glGetObjectLabel)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
extern void (__stdcall*glObjectPtrLabel)(const void *, GLsizei, const GLchar *);
extern void (__stdcall*glGetObjectPtrLabel)(const void *, GLsizei, GLsizei *, GLchar *);
# ifndef GL_VERSION_4_2
extern void (__stdcall*glDrawArraysInstancedBaseInstance)(GLenum, GLint, GLsizei, GLsizei, GLuint);
extern void (__stdcall*glDrawElementsInstancedBaseInstance)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLuint);
extern void (__stdcall*glDrawElementsInstancedBaseVertexBaseInstance)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint, GLuint);
extern void (__stdcall*glGetInternalformativ)(GLenum, GLenum, GLenum, GLsizei, GLint *);
extern void (__stdcall*glGetActiveAtomicCounterBufferiv)(GLuint, GLuint, GLenum, GLint *);
extern void (__stdcall*glBindImageTexture)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum);
extern void (__stdcall*glMemoryBarrier)(GLbitfield);
extern void (__stdcall*glTexStorage1D)(GLenum, GLsizei, GLenum, GLsizei);
extern void (__stdcall*glTexStorage2D)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
extern void (__stdcall*glTexStorage3D)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
extern void (__stdcall*glDrawTransformFeedbackInstanced)(GLenum, GLuint, GLsizei);
extern void (__stdcall*glDrawTransformFeedbackStreamInstanced)(GLenum, GLuint, GLuint, GLsizei);
# ifndef GL_VERSION_4_1
extern void (__stdcall*glReleaseShaderCompiler)(void);
extern void (__stdcall*glShaderBinary)(GLsizei, const GLuint *, GLenum, const void *, GLsizei);
extern void (__stdcall*glGetShaderPrecisionFormat)(GLenum, GLenum, GLint *, GLint *);
extern void (__stdcall*glDepthRangef)(GLfloat, GLfloat);
extern void (__stdcall*glClearDepthf)(GLfloat);
extern void (__stdcall*glGetProgramBinary)(GLuint, GLsizei, GLsizei *, GLenum *, void *);
extern void (__stdcall*glProgramBinary)(GLuint, GLenum, const void *, GLsizei);
extern void (__stdcall*glProgramParameteri)(GLuint, GLenum, GLint);
extern void (__stdcall*glUseProgramStages)(GLuint, GLbitfield, GLuint);
extern void (__stdcall*glActiveShaderProgram)(GLuint, GLuint);
extern GLuint (__stdcall*glCreateShaderProgramv)(GLenum, GLsizei, const GLchar *const*);
extern void (__stdcall*glBindProgramPipeline)(GLuint);
extern void (__stdcall*glDeleteProgramPipelines)(GLsizei, const GLuint *);
extern void (__stdcall*glGenProgramPipelines)(GLsizei, GLuint *);
extern GLboolean (__stdcall*glIsProgramPipeline)(GLuint);
extern void (__stdcall*glGetProgramPipelineiv)(GLuint, GLenum, GLint *);
extern void (__stdcall*glProgramUniform1i)(GLuint, GLint, GLint);
extern void (__stdcall*glProgramUniform1iv)(GLuint, GLint, GLsizei, const GLint *);
extern void (__stdcall*glProgramUniform1f)(GLuint, GLint, GLfloat);
extern void (__stdcall*glProgramUniform1fv)(GLuint, GLint, GLsizei, const GLfloat *);
extern void (__stdcall*glProgramUniform1d)(GLuint, GLint, GLdouble);
extern void (__stdcall*glProgramUniform1dv)(GLuint, GLint, GLsizei, const GLdouble *);
extern void (__stdcall*glProgramUniform1ui)(GLuint, GLint, GLuint);
extern void (__stdcall*glProgramUniform1uiv)(GLuint, GLint, GLsizei, const GLuint *);
extern void (__stdcall*glProgramUniform2i)(GLuint, GLint, GLint, GLint);
extern void (__stdcall*glProgramUniform2iv)(GLuint, GLint, GLsizei, const GLint *);
extern void (__stdcall*glProgramUniform2f)(GLuint, GLint, GLfloat, GLfloat);
extern void (__stdcall*glProgramUniform2fv)(GLuint, GLint, GLsizei, const GLfloat *);
extern void (__stdcall*glProgramUniform2d)(GLuint, GLint, GLdouble, GLdouble);
extern void (__stdcall*glProgramUniform2dv)(GLuint, GLint, GLsizei, const GLdouble *);
extern void (__stdcall*glProgramUniform2ui)(GLuint, GLint, GLuint, GLuint);
extern void (__stdcall*glProgramUniform2uiv)(GLuint, GLint, GLsizei, const GLuint *);
extern void (__stdcall*glProgramUniform3i)(GLuint, GLint, GLint, GLint, GLint);
extern void (__stdcall*glProgramUniform3iv)(GLuint, GLint, GLsizei, const GLint *);
extern void (__stdcall*glProgramUniform3f)(GLuint, GLint, GLfloat, GLfloat, GLfloat);
extern void (__stdcall*glProgramUniform3fv)(GLuint, GLint, GLsizei, const GLfloat *);
extern void (__stdcall*glProgramUniform3d)(GLuint, GLint, GLdouble, GLdouble, GLdouble);
extern void (__stdcall*glProgramUniform3dv)(GLuint, GLint, GLsizei, const GLdouble *);
extern void (__stdcall*glProgramUniform3ui)(GLuint, GLint, GLuint, GLuint, GLuint);
extern void (__stdcall*glProgramUniform3uiv)(GLuint, GLint, GLsizei, const GLuint *);
extern void (__stdcall*glProgramUniform4i)(GLuint, GLint, GLint, GLint, GLint, GLint);
extern void (__stdcall*glProgramUniform4iv)(GLuint, GLint, GLsizei, const GLint *);
extern void (__stdcall*glProgramUniform4f)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat);
extern void (__stdcall*glProgramUniform4fv)(GLuint, GLint, GLsizei, const GLfloat *);
extern void (__stdcall*glProgramUniform4d)(GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble);
extern void (__stdcall*glProgramUniform4dv)(GLuint, GLint, GLsizei, const GLdouble *);
extern void (__stdcall*glProgramUniform4ui)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint);
extern void (__stdcall*glProgramUniform4uiv)(GLuint, GLint, GLsizei, const GLuint *);
extern void (__stdcall*glProgramUniformMatrix2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glProgramUniformMatrix3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glProgramUniformMatrix4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glProgramUniformMatrix2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glProgramUniformMatrix3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glProgramUniformMatrix4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glProgramUniformMatrix2x3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glProgramUniformMatrix3x2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glProgramUniformMatrix2x4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glProgramUniformMatrix4x2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glProgramUniformMatrix3x4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glProgramUniformMatrix4x3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glProgramUniformMatrix2x3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glProgramUniformMatrix3x2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glProgramUniformMatrix2x4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glProgramUniformMatrix4x2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glProgramUniformMatrix3x4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glProgramUniformMatrix4x3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glValidateProgramPipeline)(GLuint);
extern void (__stdcall*glGetProgramPipelineInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
extern void (__stdcall*glVertexAttribL1d)(GLuint, GLdouble);
extern void (__stdcall*glVertexAttribL2d)(GLuint, GLdouble, GLdouble);
extern void (__stdcall*glVertexAttribL3d)(GLuint, GLdouble, GLdouble, GLdouble);
extern void (__stdcall*glVertexAttribL4d)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
extern void (__stdcall*glVertexAttribL1dv)(GLuint, const GLdouble *);
extern void (__stdcall*glVertexAttribL2dv)(GLuint, const GLdouble *);
extern void (__stdcall*glVertexAttribL3dv)(GLuint, const GLdouble *);
extern void (__stdcall*glVertexAttribL4dv)(GLuint, const GLdouble *);
extern void (__stdcall*glVertexAttribLPointer)(GLuint, GLint, GLenum, GLsizei, const void *);
extern void (__stdcall*glGetVertexAttribLdv)(GLuint, GLenum, GLdouble *);
extern void (__stdcall*glViewportArrayv)(GLuint, GLsizei, const GLfloat *);
extern void (__stdcall*glViewportIndexedf)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
extern void (__stdcall*glViewportIndexedfv)(GLuint, const GLfloat *);
extern void (__stdcall*glScissorArrayv)(GLuint, GLsizei, const GLint *);
extern void (__stdcall*glScissorIndexed)(GLuint, GLint, GLint, GLsizei, GLsizei);
extern void (__stdcall*glScissorIndexedv)(GLuint, const GLint *);
extern void (__stdcall*glDepthRangeArrayv)(GLuint, GLsizei, const GLdouble *);
extern void (__stdcall*glDepthRangeIndexed)(GLuint, GLdouble, GLdouble);
extern void (__stdcall*glGetFloati_v)(GLenum, GLuint, GLfloat *);
extern void (__stdcall*glGetDoublei_v)(GLenum, GLuint, GLdouble *);
# ifndef GL_VERSION_4_0
extern void (__stdcall*glMinSampleShading)(GLfloat);
extern void (__stdcall*glBlendEquationi)(GLuint, GLenum);
extern void (__stdcall*glBlendEquationSeparatei)(GLuint, GLenum, GLenum);
extern void (__stdcall*glBlendFunci)(GLuint, GLenum, GLenum);
extern void (__stdcall*glBlendFuncSeparatei)(GLuint, GLenum, GLenum, GLenum, GLenum);
extern void (__stdcall*glDrawArraysIndirect)(GLenum, const void *);
extern void (__stdcall*glDrawElementsIndirect)(GLenum, GLenum, const void *);
extern void (__stdcall*glUniform1d)(GLint, GLdouble);
extern void (__stdcall*glUniform2d)(GLint, GLdouble, GLdouble);
extern void (__stdcall*glUniform3d)(GLint, GLdouble, GLdouble, GLdouble);
extern void (__stdcall*glUniform4d)(GLint, GLdouble, GLdouble, GLdouble, GLdouble);
extern void (__stdcall*glUniform1dv)(GLint, GLsizei, const GLdouble *);
extern void (__stdcall*glUniform2dv)(GLint, GLsizei, const GLdouble *);
extern void (__stdcall*glUniform3dv)(GLint, GLsizei, const GLdouble *);
extern void (__stdcall*glUniform4dv)(GLint, GLsizei, const GLdouble *);
extern void (__stdcall*glUniformMatrix2dv)(GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glUniformMatrix3dv)(GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glUniformMatrix4dv)(GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glUniformMatrix2x3dv)(GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glUniformMatrix2x4dv)(GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glUniformMatrix3x2dv)(GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glUniformMatrix3x4dv)(GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glUniformMatrix4x2dv)(GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glUniformMatrix4x3dv)(GLint, GLsizei, GLboolean, const GLdouble *);
extern void (__stdcall*glGetUniformdv)(GLuint, GLint, GLdouble *);
extern GLint (__stdcall*glGetSubroutineUniformLocation)(GLuint, GLenum, const GLchar *);
extern GLuint (__stdcall*glGetSubroutineIndex)(GLuint, GLenum, const GLchar *);
extern void (__stdcall*glGetActiveSubroutineUniformiv)(GLuint, GLenum, GLuint, GLenum, GLint *);
extern void (__stdcall*glGetActiveSubroutineUniformName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
extern void (__stdcall*glGetActiveSubroutineName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
extern void (__stdcall*glUniformSubroutinesuiv)(GLenum, GLsizei, const GLuint *);
extern void (__stdcall*glGetUniformSubroutineuiv)(GLenum, GLint, GLuint *);
extern void (__stdcall*glGetProgramStageiv)(GLuint, GLenum, GLenum, GLint *);
extern void (__stdcall*glPatchParameteri)(GLenum, GLint);
extern void (__stdcall*glPatchParameterfv)(GLenum, const GLfloat *);
extern void (__stdcall*glBindTransformFeedback)(GLenum, GLuint);
extern void (__stdcall*glDeleteTransformFeedbacks)(GLsizei, const GLuint *);
extern void (__stdcall*glGenTransformFeedbacks)(GLsizei, GLuint *);
extern GLboolean (__stdcall*glIsTransformFeedback)(GLuint);
extern void (__stdcall*glPauseTransformFeedback)(void);
extern void (__stdcall*glResumeTransformFeedback)(void);
extern void (__stdcall*glDrawTransformFeedback)(GLenum, GLuint);
extern void (__stdcall*glDrawTransformFeedbackStream)(GLenum, GLuint, GLuint);
extern void (__stdcall*glBeginQueryIndexed)(GLenum, GLuint, GLuint);
extern void (__stdcall*glEndQueryIndexed)(GLenum, GLuint);
extern void (__stdcall*glGetQueryIndexediv)(GLenum, GLuint, GLenum, GLint *);
# ifndef GL_VERSION_3_3
extern void (__stdcall*glBindFragDataLocationIndexed)(GLuint, GLuint, GLuint, const GLchar *);
extern GLint (__stdcall*glGetFragDataIndex)(GLuint, const GLchar *);
extern void (__stdcall*glGenSamplers)(GLsizei, GLuint *);
extern void (__stdcall*glDeleteSamplers)(GLsizei, const GLuint *);
extern GLboolean (__stdcall*glIsSampler)(GLuint);
extern void (__stdcall*glBindSampler)(GLuint, GLuint);
extern void (__stdcall*glSamplerParameteri)(GLuint, GLenum, GLint);
extern void (__stdcall*glSamplerParameteriv)(GLuint, GLenum, const GLint *);
extern void (__stdcall*glSamplerParameterf)(GLuint, GLenum, GLfloat);
extern void (__stdcall*glSamplerParameterfv)(GLuint, GLenum, const GLfloat *);
extern void (__stdcall*glSamplerParameterIiv)(GLuint, GLenum, const GLint *);
extern void (__stdcall*glSamplerParameterIuiv)(GLuint, GLenum, const GLuint *);
extern void (__stdcall*glGetSamplerParameteriv)(GLuint, GLenum, GLint *);
extern void (__stdcall*glGetSamplerParameterIiv)(GLuint, GLenum, GLint *);
extern void (__stdcall*glGetSamplerParameterfv)(GLuint, GLenum, GLfloat *);
extern void (__stdcall*glGetSamplerParameterIuiv)(GLuint, GLenum, GLuint *);
extern void (__stdcall*glQueryCounter)(GLuint, GLenum);
extern void (__stdcall*glGetQueryObjecti64v)(GLuint, GLenum, GLint64 *);
extern void (__stdcall*glGetQueryObjectui64v)(GLuint, GLenum, GLuint64 *);
extern void (__stdcall*glVertexAttribDivisor)(GLuint, GLuint);
extern void (__stdcall*glVertexAttribP1ui)(GLuint, GLenum, GLboolean, GLuint);
extern void (__stdcall*glVertexAttribP1uiv)(GLuint, GLenum, GLboolean, const GLuint *);
extern void (__stdcall*glVertexAttribP2ui)(GLuint, GLenum, GLboolean, GLuint);
extern void (__stdcall*glVertexAttribP2uiv)(GLuint, GLenum, GLboolean, const GLuint *);
extern void (__stdcall*glVertexAttribP3ui)(GLuint, GLenum, GLboolean, GLuint);
extern void (__stdcall*glVertexAttribP3uiv)(GLuint, GLenum, GLboolean, const GLuint *);
extern void (__stdcall*glVertexAttribP4ui)(GLuint, GLenum, GLboolean, GLuint);
extern void (__stdcall*glVertexAttribP4uiv)(GLuint, GLenum, GLboolean, const GLuint *);
# ifndef GL_VERSION_3_2
constexpr GLuint64 GL_TIMEOUT_IGNORED = 0xFFFFFFFFFFFFFFFF;
extern void (__stdcall*glDrawElementsBaseVertex)(GLenum, GLsizei, GLenum, const void *, GLint);
extern void (__stdcall*glDrawRangeElementsBaseVertex)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *, GLint);
extern void (__stdcall*glDrawElementsInstancedBaseVertex)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint);
extern void (__stdcall*glMultiDrawElementsBaseVertex)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei, const GLint *);
extern void (__stdcall*glProvokingVertex)(GLenum);
extern GLsync (__stdcall*glFenceSync)(GLenum, GLbitfield);
extern GLboolean (__stdcall*glIsSync)(GLsync);
extern void (__stdcall*glDeleteSync)(GLsync);
extern GLenum (__stdcall*glClientWaitSync)(GLsync, GLbitfield, GLuint64);
extern void (__stdcall*glWaitSync)(GLsync, GLbitfield, GLuint64);
extern void (__stdcall*glGetInteger64v)(GLenum, GLint64 *);
extern void (__stdcall*glGetSynciv)(GLsync, GLenum, GLsizei, GLsizei *, GLint *);
extern void (__stdcall*glGetInteger64i_v)(GLenum, GLuint, GLint64 *);
extern void (__stdcall*glGetBufferParameteri64v)(GLenum, GLenum, GLint64 *);
extern void (__stdcall*glFramebufferTexture)(GLenum, GLenum, GLuint, GLint);
extern void (__stdcall*glTexImage2DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
extern void (__stdcall*glTexImage3DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
extern void (__stdcall*glGetMultisamplefv)(GLenum, GLuint, GLfloat *);
extern void (__stdcall*glSampleMaski)(GLuint, GLbitfield);
# ifndef GL_VERSION_3_1
extern void (__stdcall*glDrawArraysInstanced)(GLenum, GLint, GLsizei, GLsizei);
extern void (__stdcall*glDrawElementsInstanced)(GLenum, GLsizei, GLenum, const void *, GLsizei);
extern void (__stdcall*glTexBuffer)(GLenum, GLenum, GLuint);
extern void (__stdcall*glPrimitiveRestartIndex)(GLuint);
extern void (__stdcall*glCopyBufferSubData)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr);
extern void (__stdcall*glGetUniformIndices)(GLuint, GLsizei, const GLchar *const*, GLuint *);
extern void (__stdcall*glGetActiveUniformsiv)(GLuint, GLsizei, const GLuint *, GLenum, GLint *);
extern void (__stdcall*glGetActiveUniformName)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
extern GLuint (__stdcall*glGetUniformBlockIndex)(GLuint, const GLchar *);
extern void (__stdcall*glGetActiveUniformBlockiv)(GLuint, GLuint, GLenum, GLint *);
extern void (__stdcall*glGetActiveUniformBlockName)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
extern void (__stdcall*glUniformBlockBinding)(GLuint, GLuint, GLuint);
# ifndef GL_VERSION_3_0
extern void (__stdcall*glColorMaski)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean);
extern void (__stdcall*glGetBooleani_v)(GLenum, GLuint, GLboolean *);
extern void (__stdcall*glGetIntegeri_v)(GLenum, GLuint, GLint *);
extern void (__stdcall*glEnablei)(GLenum, GLuint);
extern void (__stdcall*glDisablei)(GLenum, GLuint);
extern GLboolean (__stdcall*glIsEnabledi)(GLenum, GLuint);
extern void (__stdcall*glBeginTransformFeedback)(GLenum);
extern void (__stdcall*glEndTransformFeedback)(void);
extern void (__stdcall*glBindBufferRange)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
extern void (__stdcall*glBindBufferBase)(GLenum, GLuint, GLuint);
extern void (__stdcall*glTransformFeedbackVaryings)(GLuint, GLsizei, const GLchar *const*, GLenum);
extern void (__stdcall*glGetTransformFeedbackVarying)(GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *);
extern void (__stdcall*glClampColor)(GLenum, GLenum);
extern void (__stdcall*glBeginConditionalRender)(GLuint, GLenum);
extern void (__stdcall*glEndConditionalRender)(void);
extern void (__stdcall*glVertexAttribIPointer)(GLuint, GLint, GLenum, GLsizei, const void *);
extern void (__stdcall*glGetVertexAttribIiv)(GLuint, GLenum, GLint *);
extern void (__stdcall*glGetVertexAttribIuiv)(GLuint, GLenum, GLuint *);
extern void (__stdcall*glVertexAttribI1i)(GLuint, GLint);
extern void (__stdcall*glVertexAttribI2i)(GLuint, GLint, GLint);
extern void (__stdcall*glVertexAttribI3i)(GLuint, GLint, GLint, GLint);
extern void (__stdcall*glVertexAttribI4i)(GLuint, GLint, GLint, GLint, GLint);
extern void (__stdcall*glVertexAttribI1ui)(GLuint, GLuint);
extern void (__stdcall*glVertexAttribI2ui)(GLuint, GLuint, GLuint);
extern void (__stdcall*glVertexAttribI3ui)(GLuint, GLuint, GLuint, GLuint);
extern void (__stdcall*glVertexAttribI4ui)(GLuint, GLuint, GLuint, GLuint, GLuint);
extern void (__stdcall*glVertexAttribI1iv)(GLuint, const GLint *);
extern void (__stdcall*glVertexAttribI2iv)(GLuint, const GLint *);
extern void (__stdcall*glVertexAttribI3iv)(GLuint, const GLint *);
extern void (__stdcall*glVertexAttribI4iv)(GLuint, const GLint *);
extern void (__stdcall*glVertexAttribI1uiv)(GLuint, const GLuint *);
extern void (__stdcall*glVertexAttribI2uiv)(GLuint, const GLuint *);
extern void (__stdcall*glVertexAttribI3uiv)(GLuint, const GLuint *);
extern void (__stdcall*glVertexAttribI4uiv)(GLuint, const GLuint *);
extern void (__stdcall*glVertexAttribI4bv)(GLuint, const GLbyte *);
extern void (__stdcall*glVertexAttribI4sv)(GLuint, const GLshort *);
extern void (__stdcall*glVertexAttribI4ubv)(GLuint, const GLubyte *);
extern void (__stdcall*glVertexAttribI4usv)(GLuint, const GLushort *);
extern void (__stdcall*glGetUniformuiv)(GLuint, GLint, GLuint *);
extern void (__stdcall*glBindFragDataLocation)(GLuint, GLuint, const GLchar *);
extern GLint (__stdcall*glGetFragDataLocation)(GLuint, const GLchar *);
extern void (__stdcall*glUniform1ui)(GLint, GLuint);
extern void (__stdcall*glUniform2ui)(GLint, GLuint, GLuint);
extern void (__stdcall*glUniform3ui)(GLint, GLuint, GLuint, GLuint);
extern void (__stdcall*glUniform4ui)(GLint, GLuint, GLuint, GLuint, GLuint);
extern void (__stdcall*glUniform1uiv)(GLint, GLsizei, const GLuint *);
extern void (__stdcall*glUniform2uiv)(GLint, GLsizei, const GLuint *);
extern void (__stdcall*glUniform3uiv)(GLint, GLsizei, const GLuint *);
extern void (__stdcall*glUniform4uiv)(GLint, GLsizei, const GLuint *);
extern void (__stdcall*glTexParameterIiv)(GLenum, GLenum, const GLint *);
extern void (__stdcall*glTexParameterIuiv)(GLenum, GLenum, const GLuint *);
extern void (__stdcall*glGetTexParameterIiv)(GLenum, GLenum, GLint *);
extern void (__stdcall*glGetTexParameterIuiv)(GLenum, GLenum, GLuint *);
extern void (__stdcall*glClearBufferiv)(GLenum, GLint, const GLint *);
extern void (__stdcall*glClearBufferuiv)(GLenum, GLint, const GLuint *);
extern void (__stdcall*glClearBufferfv)(GLenum, GLint, const GLfloat *);
extern void (__stdcall*glClearBufferfi)(GLenum, GLint, GLfloat, GLint);
extern const GLubyte *(__stdcall*glGetStringi)(GLenum, GLuint);
extern GLboolean (__stdcall*glIsRenderbuffer)(GLuint );
extern void (__stdcall*glBindRenderbuffer)(GLenum, GLuint );
extern void (__stdcall*glDeleteRenderbuffers)(GLsizei, const GLuint *);
extern void (__stdcall*glGenRenderbuffers)(GLsizei, GLuint *);
extern void (__stdcall*glRenderbufferStorage)(GLenum, GLenum, GLsizei, GLsizei);
extern void (__stdcall*glGetRenderbufferParameteriv)(GLenum, GLenum, GLint *);
extern GLboolean (__stdcall*glIsFramebuffer)(GLuint);
extern void (__stdcall*glBindFramebuffer)(GLenum, GLuint );
extern void (__stdcall*glDeleteFramebuffers)(GLsizei, const GLuint *);
extern void (__stdcall*glGenFramebuffers)(GLsizei, GLuint *);
extern GLenum (__stdcall*glCheckFramebufferStatus)(GLenum);
extern void (__stdcall*glFramebufferTexture1D)(GLenum, GLenum, GLenum, GLuint, GLint);
extern void (__stdcall*glFramebufferTexture2D)(GLenum, GLenum, GLenum, GLuint, GLint);
extern void (__stdcall*glFramebufferTexture3D)(GLenum, GLenum, GLenum, GLuint, GLint, GLint);
extern void (__stdcall*glFramebufferRenderbuffer)(GLenum, GLenum, GLenum, GLuint);
extern void (__stdcall*glGetFramebufferAttachmentParameteriv)(GLenum, GLenum, GLenum, GLint *);
extern void (__stdcall*glGenerateMipmap)(GLenum);
extern void (__stdcall*glBlitFramebuffer)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
extern void (__stdcall*glRenderbufferStorageMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
extern void (__stdcall*glFramebufferTextureLayer)(GLenum, GLenum, GLuint, GLint, GLint);
extern void *(__stdcall*glMapBufferRange)(GLenum, GLintptr, GLsizeiptr, GLbitfield);
extern void (__stdcall*glFlushMappedBufferRange)(GLenum, GLintptr, GLsizeiptr);
extern void (__stdcall*glBindVertexArray)(GLuint);
extern void (__stdcall*glDeleteVertexArrays)(GLsizei, const GLuint *);
extern void (__stdcall*glGenVertexArrays)(GLsizei, GLuint *);
extern GLboolean (__stdcall*glIsVertexArray)(GLuint);
# ifndef GL_VERSION_2_1
extern void (__stdcall*glUniformMatrix2x3fv)(GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glUniformMatrix3x2fv)(GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glUniformMatrix2x4fv)(GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glUniformMatrix4x2fv)(GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glUniformMatrix3x4fv)(GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glUniformMatrix4x3fv)(GLint, GLsizei, GLboolean, const GLfloat *);
# ifndef GL_VERSION_2_0
extern void (__stdcall*glBlendEquationSeparate)(GLenum, GLenum);
extern void (__stdcall*glDrawBuffers)(GLsizei, const GLenum *);
extern void (__stdcall*glStencilOpSeparate)(GLenum, GLenum, GLenum, GLenum);
extern void (__stdcall*glStencilFuncSeparate)(GLenum, GLenum, GLint, GLuint);
extern void (__stdcall*glStencilMaskSeparate)(GLenum, GLuint);
extern void (__stdcall*glAttachShader)(GLuint, GLuint);
extern void (__stdcall*glBindAttribLocation)(GLuint, GLuint, const GLchar *);
extern void (__stdcall*glCompileShader)(GLuint);
extern GLuint (__stdcall*glCreateProgram)(void);
extern GLuint (__stdcall*glCreateShader)(GLenum);
extern void (__stdcall*glDeleteProgram)(GLuint);
extern void (__stdcall*glDeleteShader)(GLuint);
extern void (__stdcall*glDetachShader)(GLuint, GLuint);
extern void (__stdcall*glDisableVertexAttribArray)(GLuint);
extern void (__stdcall*glEnableVertexAttribArray)(GLuint);
extern void (__stdcall*glGetActiveAttrib)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
extern void (__stdcall*glGetActiveUniform)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
extern void (__stdcall*glGetAttachedShaders)(GLuint, GLsizei, GLsizei *, GLuint *);
extern GLint (__stdcall*glGetAttribLocation)(GLuint, const GLchar *);
extern void (__stdcall*glGetProgramiv)(GLuint, GLenum, GLint *);
extern void (__stdcall*glGetProgramInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
extern void (__stdcall*glGetShaderiv)(GLuint, GLenum, GLint *);
extern void (__stdcall*glGetShaderInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
extern void (__stdcall*glGetShaderSource)(GLuint, GLsizei, GLsizei *, GLchar *);
extern GLint (__stdcall*glGetUniformLocation)(GLuint, const GLchar *);
extern void (__stdcall*glGetUniformfv)(GLuint, GLint, GLfloat *);
extern void (__stdcall*glGetUniformiv)(GLuint, GLint, GLint *);
extern void (__stdcall*glGetVertexAttribdv)(GLuint, GLenum, GLdouble *);
extern void (__stdcall*glGetVertexAttribfv)(GLuint, GLenum, GLfloat *);
extern void (__stdcall*glGetVertexAttribiv)(GLuint, GLenum, GLint *);
extern void (__stdcall*glGetVertexAttribPointerv)(GLuint, GLenum, void **);
extern GLboolean (__stdcall*glIsProgram)(GLuint);
extern GLboolean (__stdcall*glIsShader)(GLuint);
extern void (__stdcall*glLinkProgram)(GLuint);
extern void (__stdcall*glShaderSource)(GLuint, GLsizei, const GLchar *const*, const GLint *);
extern void (__stdcall*glUseProgram)(GLuint);
extern void (__stdcall*glUniform1f)(GLint, GLfloat);
extern void (__stdcall*glUniform2f)(GLint, GLfloat, GLfloat);
extern void (__stdcall*glUniform3f)(GLint, GLfloat, GLfloat, GLfloat);
extern void (__stdcall*glUniform4f)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
extern void (__stdcall*glUniform1i)(GLint, GLint);
extern void (__stdcall*glUniform2i)(GLint, GLint, GLint);
extern void (__stdcall*glUniform3i)(GLint, GLint, GLint, GLint);
extern void (__stdcall*glUniform4i)(GLint, GLint, GLint, GLint, GLint);
extern void (__stdcall*glUniform1fv)(GLint, GLsizei, const GLfloat *);
extern void (__stdcall*glUniform2fv)(GLint, GLsizei, const GLfloat *);
extern void (__stdcall*glUniform3fv)(GLint, GLsizei, const GLfloat *);
extern void (__stdcall*glUniform4fv)(GLint, GLsizei, const GLfloat *);
extern void (__stdcall*glUniform1iv)(GLint, GLsizei, const GLint *);
extern void (__stdcall*glUniform2iv)(GLint, GLsizei, const GLint *);
extern void (__stdcall*glUniform3iv)(GLint, GLsizei, const GLint *);
extern void (__stdcall*glUniform4iv)(GLint, GLsizei, const GLint *);
extern void (__stdcall*glUniformMatrix2fv)(GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glUniformMatrix3fv)(GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glUniformMatrix4fv)(GLint, GLsizei, GLboolean, const GLfloat *);
extern void (__stdcall*glValidateProgram)(GLuint);
extern void (__stdcall*glVertexAttrib1d)(GLuint, GLdouble);
extern void (__stdcall*glVertexAttrib1dv)(GLuint, const GLdouble *);
extern void (__stdcall*glVertexAttrib1f)(GLuint, GLfloat);
extern void (__stdcall*glVertexAttrib1fv)(GLuint, const GLfloat *);
extern void (__stdcall*glVertexAttrib1s)(GLuint, GLshort);
extern void (__stdcall*glVertexAttrib1sv)(GLuint, const GLshort *);
extern void (__stdcall*glVertexAttrib2d)(GLuint, GLdouble, GLdouble);
extern void (__stdcall*glVertexAttrib2dv)(GLuint, const GLdouble *);
extern void (__stdcall*glVertexAttrib2f)(GLuint, GLfloat, GLfloat);
extern void (__stdcall*glVertexAttrib2fv)(GLuint, const GLfloat *);
extern void (__stdcall*glVertexAttrib2s)(GLuint, GLshort, GLshort);
extern void (__stdcall*glVertexAttrib2sv)(GLuint, const GLshort *);
extern void (__stdcall*glVertexAttrib3d)(GLuint, GLdouble, GLdouble, GLdouble);
extern void (__stdcall*glVertexAttrib3dv)(GLuint, const GLdouble *);
extern void (__stdcall*glVertexAttrib3f)(GLuint, GLfloat, GLfloat, GLfloat);
extern void (__stdcall*glVertexAttrib3fv)(GLuint, const GLfloat *);
extern void (__stdcall*glVertexAttrib3s)(GLuint, GLshort, GLshort, GLshort);
extern void (__stdcall*glVertexAttrib3sv)(GLuint, const GLshort *);
extern void (__stdcall*glVertexAttrib4Nbv)(GLuint, const GLbyte *);
extern void (__stdcall*glVertexAttrib4Niv)(GLuint, const GLint *);
extern void (__stdcall*glVertexAttrib4Nsv)(GLuint, const GLshort *);
extern void (__stdcall*glVertexAttrib4Nub)(GLuint, GLubyte, GLubyte, GLubyte, GLubyte);
extern void (__stdcall*glVertexAttrib4Nubv)(GLuint, const GLubyte *);
extern void (__stdcall*glVertexAttrib4Nuiv)(GLuint, const GLuint *);
extern void (__stdcall*glVertexAttrib4Nusv)(GLuint, const GLushort *);
extern void (__stdcall*glVertexAttrib4bv)(GLuint, const GLbyte *);
extern void (__stdcall*glVertexAttrib4d)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
extern void (__stdcall*glVertexAttrib4dv)(GLuint, const GLdouble *);
extern void (__stdcall*glVertexAttrib4f)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
extern void (__stdcall*glVertexAttrib4fv)(GLuint, const GLfloat *);
extern void (__stdcall*glVertexAttrib4iv)(GLuint, const GLint *);
extern void (__stdcall*glVertexAttrib4s)(GLuint, GLshort, GLshort, GLshort, GLshort);
extern void (__stdcall*glVertexAttrib4sv)(GLuint, const GLshort *);
extern void (__stdcall*glVertexAttrib4ubv)(GLuint, const GLubyte *);
extern void (__stdcall*glVertexAttrib4uiv)(GLuint, const GLuint *);
extern void (__stdcall*glVertexAttrib4usv)(GLuint, const GLushort *);
extern void (__stdcall*glVertexAttribPointer)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *);
# ifndef GL_VERSION_1_5
extern void (__stdcall*glGenQueries)(GLsizei, GLuint *);
extern void (__stdcall*glDeleteQueries)(GLsizei, const GLuint *);
extern GLboolean (__stdcall*glIsQuery)(GLuint);
extern void (__stdcall*glBeginQuery)(GLenum, GLuint);
extern void (__stdcall*glEndQuery)(GLenum);
extern void (__stdcall*glGetQueryiv)(GLenum, GLenum, GLint *);
extern void (__stdcall*glGetQueryObjectiv)(GLuint, GLenum, GLint *);
extern void (__stdcall*glGetQueryObjectuiv)(GLuint, GLenum, GLuint *);
extern void (__stdcall*glBindBuffer)(GLenum, GLuint);
extern void (__stdcall*glDeleteBuffers)(GLsizei, const GLuint *);
extern void (__stdcall*glGenBuffers)(GLsizei, GLuint *);
extern GLboolean (__stdcall*glIsBuffer)(GLuint);
extern void (__stdcall*glBufferData)(GLenum, GLsizeiptr, const void *, GLenum);
extern void (__stdcall*glBufferSubData)(GLenum, GLintptr, GLsizeiptr, const void *);
extern void (__stdcall*glGetBufferSubData)(GLenum, GLintptr, GLsizeiptr, void *);
extern void *(__stdcall*glMapBuffer)(GLenum, GLenum);
extern GLboolean (__stdcall*glUnmapBuffer)(GLenum);
extern void (__stdcall*glGetBufferParameteriv)(GLenum, GLenum, GLint *);
extern void (__stdcall*glGetBufferPointerv)(GLenum, GLenum, void **);
# ifndef GL_VERSION_1_4
extern void (__stdcall*glBlendFuncSeparate)(GLenum, GLenum, GLenum, GLenum);
extern void (__stdcall*glMultiDrawArrays)(GLenum, const GLint *, const GLsizei *, GLsizei);
extern void (__stdcall*glMultiDrawElements)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei);
extern void (__stdcall*glPointParameterf)(GLenum, GLfloat);
extern void (__stdcall*glPointParameterfv)(GLenum, const GLfloat *);
extern void (__stdcall*glPointParameteri)(GLenum, GLint);
extern void (__stdcall*glPointParameteriv)(GLenum, const GLint *);
extern void (__stdcall*glBlendColor)(GLfloat, GLfloat, GLfloat, GLfloat);
extern void (__stdcall*glBlendEquation)(GLenum);
# ifndef GL_VERSION_1_3
extern void (__stdcall*glActiveTexture)(GLenum);
extern void (__stdcall*glSampleCoverage)(GLfloat, GLboolean);
extern void (__stdcall*glCompressedTexImage3D)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *);
extern void (__stdcall*glCompressedTexImage2D)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *);
extern void (__stdcall*glCompressedTexImage1D)(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *);
extern void (__stdcall*glCompressedTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *);
extern void (__stdcall*glCompressedTexSubImage2D)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
extern void (__stdcall*glCompressedTexSubImage1D)(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *);
extern void (__stdcall*glGetCompressedTexImage)(GLenum, GLint, void *);
# ifndef GL_VERSION_1_2
extern void (__stdcall*glDrawRangeElements)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *);
extern void (__stdcall*glTexImage3D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
extern void (__stdcall*glTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
extern void (__stdcall*glCopyTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
# ifndef GL_VERSION_1_1
extern void (__stdcall*glDrawArrays)(GLenum, GLint, GLsizei);
extern void (__stdcall*glDrawElements)(GLenum, GLsizei, GLenum, const void *);
extern void (__stdcall*glGetPointerv)(GLenum, void **);
extern void (__stdcall*glPolygonOffset)(GLfloat, GLfloat);
extern void (__stdcall*glCopyTexImage1D)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint);
extern void (__stdcall*glCopyTexImage2D)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
extern void (__stdcall*glCopyTexSubImage1D)(GLenum, GLint, GLint, GLint, GLint, GLsizei);
extern void (__stdcall*glCopyTexSubImage2D)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
extern void (__stdcall*glTexSubImage1D)(GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void *);
extern void (__stdcall*glTexSubImage2D)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
extern void (__stdcall*glBindTexture)(GLenum, GLuint);
extern void (__stdcall*glDeleteTextures)(GLsizei, const GLuint *);
extern void (__stdcall*glGenTextures)(GLsizei, GLuint *);
extern GLboolean(__stdcall*glIsTexture)(GLuint);
# ifndef GL_VERSION_1_0
constexpr GLboolean GL_FALSE = 0;
constexpr GLboolean GL_TRUE = 1;
extern void (__stdcall*glCullFace)(GLenum);
extern void (__stdcall*glFrontFace)(GLenum);
extern void (__stdcall*glHint)(GLenum, GLenum);
extern void (__stdcall*glLineWidth)(GLfloat);
extern void (__stdcall*glPointSize)(GLfloat);
extern void (__stdcall*glPolygonMode)(GLenum, GLenum);
extern void (__stdcall*glScissor)(GLint, GLint, GLsizei, GLsizei);
extern void (__stdcall*glTexParameterf)(GLenum, GLenum, GLfloat);
extern void (__stdcall*glTexParameterfv)(GLenum, GLenum, const GLfloat *);
extern void (__stdcall*glTexParameteri)(GLenum, GLenum, GLint);
extern void (__stdcall*glTexParameteriv)(GLenum, GLenum, const GLint *);
extern void (__stdcall*glTexImage1D)(GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void *);
extern void (__stdcall*glTexImage2D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
extern void (__stdcall*glDrawBuffer)(GLenum);
extern void (__stdcall*glClear)(GLbitfield);
extern void (__stdcall*glClearColor)(GLfloat, GLfloat, GLfloat, GLfloat);
extern void (__stdcall*glClearStencil)(GLint);
extern void (__stdcall*glClearDepth)(GLdouble);
extern void (__stdcall*glStencilMask)(GLuint);
extern void (__stdcall*glColorMask)(GLboolean, GLboolean, GLboolean, GLboolean);
extern void (__stdcall*glDepthMask)(GLboolean);
extern void (__stdcall*glDisable)(GLenum);
extern void (__stdcall*glEnable)(GLenum);
extern void (__stdcall*glFinish)(void);
extern void (__stdcall*glFlush)(void);
extern void (__stdcall*glBlendFunc)(GLenum, GLenum);
extern void (__stdcall*glLogicOp)(GLenum);
extern void (__stdcall*glStencilFunc)(GLenum, GLint, GLuint);
extern void (__stdcall*glStencilOp)(GLenum, GLenum, GLenum);
extern void (__stdcall*glDepthFunc)(GLenum);
extern void (__stdcall*glPixelStoref)(GLenum, GLfloat);
extern void (__stdcall*glPixelStorei)(GLenum, GLint);
extern void (__stdcall*glReadBuffer)(GLenum);
extern void (__stdcall*glReadPixels)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void *);
extern void (__stdcall*glGetBooleanv)(GLenum, GLboolean *);
extern void (__stdcall*glGetDoublev)(GLenum, GLdouble *);
extern GLenum (__stdcall*glGetError)(void);
extern void (__stdcall*glGetFloatv)(GLenum, GLfloat *);
extern void (__stdcall*glGetIntegerv)(GLenum, GLint *);
extern const GLubyte *(__stdcall*glGetString)(GLenum);
extern void (__stdcall*glGetTexImage)(GLenum, GLint, GLenum, GLenum, void *);
extern void (__stdcall*glGetTexParameterfv)(GLenum, GLenum, GLfloat *);
extern void (__stdcall*glGetTexParameteriv)(GLenum, GLenum, GLint *);
extern void (__stdcall*glGetTexLevelParameterfv)(GLenum, GLint, GLenum, GLfloat *);
extern void (__stdcall*glGetTexLevelParameteriv)(GLenum, GLint, GLenum, GLint *);
extern GLboolean (__stdcall*glIsEnabled)(GLenum);
extern void (__stdcall*glDepthRange)(GLdouble, GLdouble);
extern void (__stdcall*glViewport)(GLint, GLint, GLsizei, GLsizei);
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
# endif

  enum
GLenum_t :
GLenum
{
# ifndef GL_VERSION_4_6
	GL_SHADER_BINARY_FORMAT_SPIR_V = 0x9551,
	GL_SPIR_V_BINARY               = 0x9552,
	GL_PARAMETER_BUFFER         = 0x80EE,
	GL_PARAMETER_BUFFER_BINDING = 0x80EF,
	GL_VERTICES_SUBMITTED   = 0x82EE,
	GL_PRIMITIVES_SUBMITTED = 0x82EF,
	GL_VERTEX_SHADER_INVOCATIONS          = 0x82F0,
	GL_TESS_CONTROL_SHADER_PATCHES        = 0x82F1,
	GL_TESS_EVALUATION_SHADER_INVOCATIONS = 0x82F2,
	GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED = 0x82F3,
	GL_FRAGMENT_SHADER_INVOCATIONS        = 0x82F4,
	GL_COMPUTE_SHADER_INVOCATIONS         = 0x82F5,
	GL_CLIPPING_INPUT_PRIMITIVES          = 0x82F6,
	GL_CLIPPING_OUTPUT_PRIMITIVES         = 0x82F7,
	GL_POLYGON_OFFSET_CLAMP = 0x8E1B,
	GL_SPIR_V_EXTENSIONS     = 0x9553,
	GL_NUM_SPIR_V_EXTENSIONS = 0x9554,
	GL_TEXTURE_MAX_ANISOTROPY     = 0x84FE,
	GL_MAX_TEXTURE_MAX_ANISOTROPY = 0x84FF,
	GL_TRANSFORM_FEEDBACK_OVERFLOW        = 0x82EC,
	GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW = 0x82ED,
# ifndef GL_VERSION_4_5
	GL_CONTEXT_LOST = 0x0507,
	GL_CLIP_ORIGIN         = 0x935C,
	GL_CLIP_DEPTH_MODE     = 0x935D,
	GL_NEGATIVE_ONE_TO_ONE = 0x935E,
	GL_ZERO_TO_ONE         = 0x935F,
	GL_QUERY_WAIT_INVERTED           = 0x8E17,
	GL_QUERY_NO_WAIT_INVERTED        = 0x8E18,
	GL_QUERY_BY_REGION_WAIT_INVERTED = 0x8E19,
	GL_QUERY_BY_REGION_NO_WAIT_INVERTED = 0x8E1A,
	GL_MAX_CULL_DISTANCES                   = 0x82F9,
	GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES = 0x82FA,
	GL_TEXTURE_TARGET = 0x1006,
	GL_QUERY_TARGET = 0x82EA,
	GL_LOSE_CONTEXT_ON_RESET       = 0x8252,
	GL_GUILTY_CONTEXT_RESET        = 0x8253,
	GL_INNOCENT_CONTEXT_RESET      = 0x8254,
	GL_UNKNOWN_CONTEXT_RESET       = 0x8255,
	GL_RESET_NOTIFICATION_STRATEGY = 0x8256,
	GL_NO_RESET_NOTIFICATION = 0x8261,
	GL_CONTEXT_RELEASE_BEHAVIOR       = 0x82FB,
	GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH = 0x82FC,
# ifndef GL_VERSION_4_4
	GL_MAX_VERTEX_ATTRIB_STRIDE = 0x82E5,
	GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED = 0x8221,
	GL_TEXTURE_BUFFER_BINDING = 0x8C2A,
	GL_BUFFER_IMMUTABLE_STORAGE = 0x821F,
	GL_BUFFER_STORAGE_FLAGS = 0x8220,
	GL_CLEAR_TEXTURE = 0x9365,
	GL_LOCATION_COMPONENT               = 0x934A,
	GL_TRANSFORM_FEEDBACK_BUFFER_INDEX  = 0x934B,
	GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE = 0x934C,
	GL_QUERY_BUFFER = 0x9192,
	GL_QUERY_BUFFER_BINDING = 0x9193,
	GL_QUERY_RESULT_NO_WAIT = 0x9194,
	GL_MIRROR_CLAMP_TO_EDGE = 0x8743,
# ifndef GL_VERSION_4_3
	GL_NUM_SHADING_LANGUAGE_VERSIONS = 0x82E9,
	GL_VERTEX_ATTRIB_ARRAY_LONG = 0x874E,
	GL_COMPRESSED_R11_EAC                        = 0x9270,
	GL_COMPRESSED_SIGNED_R11_EAC                 = 0x9271,
	GL_COMPRESSED_RG11_EAC                       = 0x9272,
	GL_COMPRESSED_SIGNED_RG11_EAC                = 0x9273,
	GL_COMPRESSED_RGB8_ETC2                      = 0x9274,
	GL_COMPRESSED_SRGB8_ETC2                     = 0x9275,
	GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2  = 0x9276,
	GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 = 0x9277,
	GL_COMPRESSED_RGBA8_ETC2_EAC                 = 0x9278,
	GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC          = 0x9279,
	GL_PRIMITIVE_RESTART_FIXED_INDEX   = 0x8D69,
	GL_ANY_SAMPLES_PASSED_CONSERVATIVE = 0x8D6A,
	GL_MAX_ELEMENT_INDEX               = 0x8D6B,
	GL_COMPUTE_SHADER = 0x91B9,
	GL_MAX_COMPUTE_UNIFORM_BLOCKS      = 0x91BB,
	GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS = 0x91BC,
	GL_MAX_COMPUTE_IMAGE_UNIFORMS      = 0x91BD,
	GL_MAX_COMPUTE_SHARED_MEMORY_SIZE          = 0x8262,
	GL_MAX_COMPUTE_UNIFORM_COMPONENTS          = 0x8263,
	GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS      = 0x8264,
	GL_MAX_COMPUTE_ATOMIC_COUNTERS             = 0x8265,
	GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS = 0x8266,
	GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS = 0x90EB,
	GL_MAX_COMPUTE_WORK_GROUP_COUNT = 0x91BE,
	GL_MAX_COMPUTE_WORK_GROUP_SIZE  = 0x91BF,
	GL_COMPUTE_WORK_GROUP_SIZE = 0x8267,
	GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER         = 0x90EC,
	GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER = 0x90ED,
	GL_DISPATCH_INDIRECT_BUFFER                           = 0x90EE,
	GL_DISPATCH_INDIRECT_BUFFER_BINDING                   = 0x90EF,
	GL_DEBUG_OUTPUT_SYNCHRONOUS         = 0x8242,
	GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH = 0x8243,
	GL_DEBUG_CALLBACK_FUNCTION          = 0x8244,
	GL_DEBUG_CALLBACK_USER_PARAM        = 0x8245,
	GL_DEBUG_SOURCE_API                 = 0x8246,
	GL_DEBUG_SOURCE_WINDOW_SYSTEM       = 0x8247,
	GL_DEBUG_SOURCE_SHADER_COMPILER     = 0x8248,
	GL_DEBUG_SOURCE_THIRD_PARTY         = 0x8249,
	GL_DEBUG_SOURCE_APPLICATION         = 0x824A,
	GL_DEBUG_SOURCE_OTHER               = 0x824B,
	GL_DEBUG_TYPE_ERROR                 = 0x824C,
	GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR   = 0x824D,
	GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR    = 0x824E,
	GL_DEBUG_TYPE_PORTABILITY           = 0x824F,
	GL_DEBUG_TYPE_PERFORMANCE           = 0x8250,
	GL_DEBUG_TYPE_OTHER                 = 0x8251,
	GL_MAX_DEBUG_MESSAGE_LENGTH  = 0x9143,
	GL_MAX_DEBUG_LOGGED_MESSAGES = 0x9144,
	GL_DEBUG_LOGGED_MESSAGES     = 0x9145,
	GL_DEBUG_SEVERITY_HIGH       = 0x9146,
	GL_DEBUG_SEVERITY_MEDIUM     = 0x9147,
	GL_DEBUG_SEVERITY_LOW        = 0x9148,
	GL_DEBUG_TYPE_MARKER           = 0x8268,
	GL_DEBUG_TYPE_PUSH_GROUP       = 0x8269,
	GL_DEBUG_TYPE_POP_GROUP        = 0x826A,
	GL_DEBUG_SEVERITY_NOTIFICATION = 0x826B,
	GL_MAX_DEBUG_GROUP_STACK_DEPTH = 0x826C,
	GL_DEBUG_GROUP_STACK_DEPTH     = 0x826D,
	GL_BUFFER           = 0x82E0,
	GL_SHADER           = 0x82E1,
	GL_PROGRAM          = 0x82E2,
	GL_QUERY            = 0x82E3,
	GL_PROGRAM_PIPELINE = 0x82E4,
	GL_SAMPLER = 0x82E6,
	GL_MAX_LABEL_LENGTH = 0x82E8,
	GL_DEBUG_OUTPUT = 0x92E0,
	GL_MAX_UNIFORM_LOCATIONS = 0x826E,
	GL_FRAMEBUFFER_DEFAULT_WIDTH                  = 0x9310,
	GL_FRAMEBUFFER_DEFAULT_HEIGHT                 = 0x9311,
	GL_FRAMEBUFFER_DEFAULT_LAYERS                 = 0x9312,
	GL_FRAMEBUFFER_DEFAULT_SAMPLES                = 0x9313,
	GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS = 0x9314,
	GL_MAX_FRAMEBUFFER_WIDTH                      = 0x9315,
	GL_MAX_FRAMEBUFFER_HEIGHT                     = 0x9316,
	GL_MAX_FRAMEBUFFER_LAYERS                     = 0x9317,
	GL_MAX_FRAMEBUFFER_SAMPLES                    = 0x9318,
	GL_INTERNALFORMAT_SUPPORTED                   = 0x826F,
	GL_INTERNALFORMAT_PREFERRED                   = 0x8270,
	GL_INTERNALFORMAT_RED_SIZE                    = 0x8271,
	GL_INTERNALFORMAT_GREEN_SIZE                  = 0x8272,
	GL_INTERNALFORMAT_BLUE_SIZE                   = 0x8273,
	GL_INTERNALFORMAT_ALPHA_SIZE                  = 0x8274,
	GL_INTERNALFORMAT_DEPTH_SIZE                  = 0x8275,
	GL_INTERNALFORMAT_STENCIL_SIZE                = 0x8276,
	GL_INTERNALFORMAT_SHARED_SIZE                 = 0x8277,
	GL_INTERNALFORMAT_RED_TYPE                    = 0x8278,
	GL_INTERNALFORMAT_GREEN_TYPE                  = 0x8279,
	GL_INTERNALFORMAT_BLUE_TYPE                   = 0x827A,
	GL_INTERNALFORMAT_ALPHA_TYPE                  = 0x827B,
	GL_INTERNALFORMAT_DEPTH_TYPE                  = 0x827C,
	GL_INTERNALFORMAT_STENCIL_TYPE                = 0x827D,
	GL_MAX_WIDTH                                  = 0x827E,
	GL_MAX_HEIGHT                                 = 0x827F,
	GL_MAX_DEPTH                                  = 0x8280,
	GL_MAX_LAYERS                                 = 0x8281,
	GL_MAX_COMBINED_DIMENSIONS                    = 0x8282,
	GL_COLOR_COMPONENTS                           = 0x8283,
	GL_DEPTH_COMPONENTS                           = 0x8284,
	GL_STENCIL_COMPONENTS                         = 0x8285,
	GL_COLOR_RENDERABLE                           = 0x8286,
	GL_DEPTH_RENDERABLE                           = 0x8287,
	GL_STENCIL_RENDERABLE                         = 0x8288,
	GL_FRAMEBUFFER_RENDERABLE                     = 0x8289,
	GL_FRAMEBUFFER_RENDERABLE_LAYERED             = 0x828A,
	GL_FRAMEBUFFER_BLEND                          = 0x828B,
	GL_READ_PIXELS                                = 0x828C,
	GL_READ_PIXELS_FORMAT                         = 0x828D,
	GL_READ_PIXELS_TYPE                           = 0x828E,
	GL_TEXTURE_IMAGE_FORMAT                       = 0x828F,
	GL_TEXTURE_IMAGE_TYPE                         = 0x8290,
	GL_GET_TEXTURE_IMAGE_FORMAT                   = 0x8291,
	GL_GET_TEXTURE_IMAGE_TYPE                     = 0x8292,
	GL_MIPMAP                                     = 0x8293,
	GL_MANUAL_GENERATE_MIPMAP                     = 0x8294,
	GL_AUTO_GENERATE_MIPMAP                       = 0x8295,
	GL_COLOR_ENCODING                             = 0x8296,
	GL_SRGB_READ                                  = 0x8297,
	GL_SRGB_WRITE                                 = 0x8298,
	GL_FILTER                    = 0x829A,
	GL_VERTEX_TEXTURE            = 0x829B,
	GL_TESS_CONTROL_TEXTURE      = 0x829C,
	GL_TESS_EVALUATION_TEXTURE   = 0x829D,
	GL_GEOMETRY_TEXTURE          = 0x829E,
	GL_FRAGMENT_TEXTURE          = 0x829F,
	GL_COMPUTE_TEXTURE           = 0x82A0,
	GL_TEXTURE_SHADOW            = 0x82A1,
	GL_TEXTURE_GATHER            = 0x82A2,
	GL_TEXTURE_GATHER_SHADOW     = 0x82A3,
	GL_SHADER_IMAGE_LOAD         = 0x82A4,
	GL_SHADER_IMAGE_STORE        = 0x82A5,
	GL_SHADER_IMAGE_ATOMIC       = 0x82A6,
	GL_IMAGE_TEXEL_SIZE          = 0x82A7,
	GL_IMAGE_COMPATIBILITY_CLASS = 0x82A8,
	GL_IMAGE_PIXEL_FORMAT        = 0x82A9,
	GL_IMAGE_PIXEL_TYPE          = 0x82AA,
	GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST    = 0x82AC,
	GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST  = 0x82AD,
	GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE   = 0x82AE,
	GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE = 0x82AF,
	GL_TEXTURE_COMPRESSED_BLOCK_WIDTH  = 0x82B1,
	GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT = 0x82B2,
	GL_TEXTURE_COMPRESSED_BLOCK_SIZE   = 0x82B3,
	GL_CLEAR_BUFFER                    = 0x82B4,
	GL_TEXTURE_VIEW                    = 0x82B5,
	GL_VIEW_COMPATIBILITY_CLASS        = 0x82B6,
	GL_FULL_SUPPORT                    = 0x82B7,
	GL_CAVEAT_SUPPORT                  = 0x82B8,
	GL_IMAGE_CLASS_4_X_32              = 0x82B9,
	GL_IMAGE_CLASS_2_X_32              = 0x82BA,
	GL_IMAGE_CLASS_1_X_32              = 0x82BB,
	GL_IMAGE_CLASS_4_X_16              = 0x82BC,
	GL_IMAGE_CLASS_2_X_16              = 0x82BD,
	GL_IMAGE_CLASS_1_X_16              = 0x82BE,
	GL_IMAGE_CLASS_4_X_8               = 0x82BF,
	GL_IMAGE_CLASS_2_X_8               = 0x82C0,
	GL_IMAGE_CLASS_1_X_8               = 0x82C1,
	GL_IMAGE_CLASS_11_11_10            = 0x82C2,
	GL_IMAGE_CLASS_10_10_10_2          = 0x82C3,
	GL_VIEW_CLASS_128_BITS             = 0x82C4,
	GL_VIEW_CLASS_96_BITS              = 0x82C5,
	GL_VIEW_CLASS_64_BITS              = 0x82C6,
	GL_VIEW_CLASS_48_BITS              = 0x82C7,
	GL_VIEW_CLASS_32_BITS              = 0x82C8,
	GL_VIEW_CLASS_24_BITS              = 0x82C9,
	GL_VIEW_CLASS_16_BITS              = 0x82CA,
	GL_VIEW_CLASS_8_BITS               = 0x82CB,
	GL_VIEW_CLASS_S3TC_DXT1_RGB        = 0x82CC,
	GL_VIEW_CLASS_S3TC_DXT1_RGBA       = 0x82CD,
	GL_VIEW_CLASS_S3TC_DXT3_RGBA       = 0x82CE,
	GL_VIEW_CLASS_S3TC_DXT5_RGBA       = 0x82CF,
	GL_VIEW_CLASS_RGTC1_RED            = 0x82D0,
	GL_VIEW_CLASS_RGTC2_RG             = 0x82D1,
	GL_VIEW_CLASS_BPTC_UNORM           = 0x82D2,
	GL_VIEW_CLASS_BPTC_FLOAT           = 0x82D3,
	GL_UNIFORM                              = 0x92E1,
	GL_UNIFORM_BLOCK                        = 0x92E2,
	GL_PROGRAM_INPUT                        = 0x92E3,
	GL_PROGRAM_OUTPUT                       = 0x92E4,
	GL_BUFFER_VARIABLE                      = 0x92E5,
	GL_SHADER_STORAGE_BLOCK                 = 0x92E6,
	GL_VERTEX_SUBROUTINE                    = 0x92E8,
	GL_TESS_CONTROL_SUBROUTINE              = 0x92E9,
	GL_TESS_EVALUATION_SUBROUTINE           = 0x92EA,
	GL_GEOMETRY_SUBROUTINE                  = 0x92EB,
	GL_FRAGMENT_SUBROUTINE                  = 0x92EC,
	GL_COMPUTE_SUBROUTINE                   = 0x92ED,
	GL_VERTEX_SUBROUTINE_UNIFORM            = 0x92EE,
	GL_TESS_CONTROL_SUBROUTINE_UNIFORM      = 0x92EF,
	GL_TESS_EVALUATION_SUBROUTINE_UNIFORM   = 0x92F0,
	GL_GEOMETRY_SUBROUTINE_UNIFORM          = 0x92F1,
	GL_FRAGMENT_SUBROUTINE_UNIFORM          = 0x92F2,
	GL_COMPUTE_SUBROUTINE_UNIFORM           = 0x92F3,
	GL_TRANSFORM_FEEDBACK_VARYING           = 0x92F4,
	GL_ACTIVE_RESOURCES                     = 0x92F5,
	GL_MAX_NAME_LENGTH                      = 0x92F6,
	GL_MAX_NUM_ACTIVE_VARIABLES             = 0x92F7,
	GL_MAX_NUM_COMPATIBLE_SUBROUTINES       = 0x92F8,
	GL_NAME_LENGTH                          = 0x92F9,
	GL_TYPE                                 = 0x92FA,
	GL_ARRAY_SIZE                           = 0x92FB,
	GL_OFFSET                               = 0x92FC,
	GL_BLOCK_INDEX                          = 0x92FD,
	GL_ARRAY_STRIDE                         = 0x92FE,
	GL_MATRIX_STRIDE                        = 0x92FF,
	GL_IS_ROW_MAJOR                         = 0x9300,
	GL_ATOMIC_COUNTER_BUFFER_INDEX          = 0x9301,
	GL_BUFFER_BINDING                       = 0x9302,
	GL_BUFFER_DATA_SIZE                     = 0x9303,
	GL_NUM_ACTIVE_VARIABLES                 = 0x9304,
	GL_ACTIVE_VARIABLES                     = 0x9305,
	GL_REFERENCED_BY_VERTEX_SHADER          = 0x9306,
	GL_REFERENCED_BY_TESS_CONTROL_SHADER    = 0x9307,
	GL_REFERENCED_BY_TESS_EVALUATION_SHADER = 0x9308,
	GL_REFERENCED_BY_GEOMETRY_SHADER        = 0x9309,
	GL_REFERENCED_BY_FRAGMENT_SHADER        = 0x930A,
	GL_REFERENCED_BY_COMPUTE_SHADER         = 0x930B,
	GL_TOP_LEVEL_ARRAY_SIZE                 = 0x930C,
	GL_TOP_LEVEL_ARRAY_STRIDE               = 0x930D,
	GL_LOCATION                             = 0x930E,
	GL_LOCATION_INDEX                       = 0x930F,
	GL_IS_PER_PATCH = 0x92E7,
	GL_SHADER_STORAGE_BUFFER                     = 0x90D2,
	GL_SHADER_STORAGE_BUFFER_BINDING             = 0x90D3,
	GL_SHADER_STORAGE_BUFFER_START               = 0x90D4,
	GL_SHADER_STORAGE_BUFFER_SIZE                = 0x90D5,
	GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS          = 0x90D6,
	GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS        = 0x90D7,
	GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS    = 0x90D8,
	GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS = 0x90D9,
	GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS        = 0x90DA,
	GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS         = 0x90DB,
	GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS        = 0x90DC,
	GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS        = 0x90DD,
	GL_MAX_SHADER_STORAGE_BLOCK_SIZE             = 0x90DE,
	GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT    = 0x90DF,
	GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES = 0x8F39,
	GL_DEPTH_STENCIL_TEXTURE_MODE = 0x90EA,
	GL_TEXTURE_BUFFER_OFFSET           = 0x919D,
	GL_TEXTURE_BUFFER_SIZE             = 0x919E,
	GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT = 0x919F,
	GL_TEXTURE_VIEW_MIN_LEVEL   = 0x82DB,
	GL_TEXTURE_VIEW_NUM_LEVELS  = 0x82DC,
	GL_TEXTURE_VIEW_MIN_LAYER   = 0x82DD,
	GL_TEXTURE_VIEW_NUM_LAYERS  = 0x82DE,
	GL_TEXTURE_IMMUTABLE_LEVELS = 0x82DF,
	GL_VERTEX_ATTRIB_BINDING             = 0x82D4,
	GL_VERTEX_ATTRIB_RELATIVE_OFFSET     = 0x82D5,
	GL_VERTEX_BINDING_DIVISOR            = 0x82D6,
	GL_VERTEX_BINDING_OFFSET             = 0x82D7,
	GL_VERTEX_BINDING_STRIDE             = 0x82D8,
	GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET = 0x82D9,
	GL_MAX_VERTEX_ATTRIB_BINDINGS        = 0x82DA,
	GL_VERTEX_BINDING_BUFFER = 0x8F4F,
# ifndef GL_VERSION_4_2
	GL_COPY_READ_BUFFER_BINDING  = 0x8F36,
	GL_COPY_WRITE_BUFFER_BINDING = 0x8F37,
	GL_TRANSFORM_FEEDBACK_ACTIVE = 0x8E24,
	GL_TRANSFORM_FEEDBACK_PAUSED = 0x8E23,
	GL_UNPACK_COMPRESSED_BLOCK_WIDTH  = 0x9127,
	GL_UNPACK_COMPRESSED_BLOCK_HEIGHT = 0x9128,
	GL_UNPACK_COMPRESSED_BLOCK_DEPTH  = 0x9129,
	GL_UNPACK_COMPRESSED_BLOCK_SIZE   = 0x912A,
	GL_PACK_COMPRESSED_BLOCK_WIDTH    = 0x912B,
	GL_PACK_COMPRESSED_BLOCK_HEIGHT   = 0x912C,
	GL_PACK_COMPRESSED_BLOCK_DEPTH    = 0x912D,
	GL_PACK_COMPRESSED_BLOCK_SIZE     = 0x912E,
	GL_NUM_SAMPLE_COUNTS = 0x9380,
	GL_MIN_MAP_BUFFER_ALIGNMENT = 0x90BC,
	GL_ATOMIC_COUNTER_BUFFER                                      = 0x92C0,
	GL_ATOMIC_COUNTER_BUFFER_BINDING                              = 0x92C1,
	GL_ATOMIC_COUNTER_BUFFER_START                                = 0x92C2,
	GL_ATOMIC_COUNTER_BUFFER_SIZE                                 = 0x92C3,
	GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE                            = 0x92C4,
	GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS               = 0x92C5,
	GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES        = 0x92C6,
	GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER          = 0x92C7,
	GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER    = 0x92C8,
	GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER = 0x92C9,
	GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER        = 0x92CA,
	GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER        = 0x92CB,
	GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS                          = 0x92CC,
	GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS                    = 0x92CD,
	GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS                 = 0x92CE,
	GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS                        = 0x92CF,
	GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS                        = 0x92D0,
	GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS                        = 0x92D1,
	GL_MAX_VERTEX_ATOMIC_COUNTERS                                 = 0x92D2,
	GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS                           = 0x92D3,
	GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS                        = 0x92D4,
	GL_MAX_GEOMETRY_ATOMIC_COUNTERS                               = 0x92D5,
	GL_MAX_FRAGMENT_ATOMIC_COUNTERS                               = 0x92D6,
	GL_MAX_COMBINED_ATOMIC_COUNTERS                               = 0x92D7,
	GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE                             = 0x92D8,
	GL_ACTIVE_ATOMIC_COUNTER_BUFFERS       = 0x92D9,
	GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX = 0x92DA,
	GL_UNSIGNED_INT_ATOMIC_COUNTER         = 0x92DB,
	GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS  = 0x92DC,
	GL_MAX_IMAGE_UNITS                               = 0x8F38,
	GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS = 0x8F39,
	GL_IMAGE_BINDING_NAME                            = 0x8F3A,
	GL_IMAGE_BINDING_LEVEL                           = 0x8F3B,
	GL_IMAGE_BINDING_LAYERED                         = 0x8F3C,
	GL_IMAGE_BINDING_LAYER                           = 0x8F3D,
	GL_IMAGE_BINDING_ACCESS                          = 0x8F3E,
	GL_IMAGE_1D                                = 0x904C,
	GL_IMAGE_2D                                = 0x904D,
	GL_IMAGE_3D                                = 0x904E,
	GL_IMAGE_2D_RECT                           = 0x904F,
	GL_IMAGE_CUBE                              = 0x9050,
	GL_IMAGE_BUFFER                            = 0x9051,
	GL_IMAGE_1D_ARRAY                          = 0x9052,
	GL_IMAGE_2D_ARRAY                          = 0x9053,
	GL_IMAGE_CUBE_MAP_ARRAY                    = 0x9054,
	GL_IMAGE_2D_MULTISAMPLE                    = 0x9055,
	GL_IMAGE_2D_MULTISAMPLE_ARRAY              = 0x9056,
	GL_INT_IMAGE_1D                            = 0x9057,
	GL_INT_IMAGE_2D                            = 0x9058,
	GL_INT_IMAGE_3D                            = 0x9059,
	GL_INT_IMAGE_2D_RECT                       = 0x905A,
	GL_INT_IMAGE_CUBE                          = 0x905B,
	GL_INT_IMAGE_BUFFER                        = 0x905C,
	GL_INT_IMAGE_1D_ARRAY                      = 0x905D,
	GL_INT_IMAGE_2D_ARRAY                      = 0x905E,
	GL_INT_IMAGE_CUBE_MAP_ARRAY                = 0x905F,
	GL_INT_IMAGE_2D_MULTISAMPLE                = 0x9060,
	GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY          = 0x9061,
	GL_UNSIGNED_INT_IMAGE_1D                   = 0x9062,
	GL_UNSIGNED_INT_IMAGE_2D                   = 0x9063,
	GL_UNSIGNED_INT_IMAGE_3D                   = 0x9064,
	GL_UNSIGNED_INT_IMAGE_2D_RECT              = 0x9065,
	GL_UNSIGNED_INT_IMAGE_CUBE                 = 0x9066,
	GL_UNSIGNED_INT_IMAGE_BUFFER               = 0x9067,
	GL_UNSIGNED_INT_IMAGE_1D_ARRAY             = 0x9068,
	GL_UNSIGNED_INT_IMAGE_2D_ARRAY             = 0x9069,
	GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY       = 0x906A,
	GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE       = 0x906B,
	GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY = 0x906C,
	GL_MAX_IMAGE_SAMPLES                       = 0x906D,
	GL_IMAGE_BINDING_FORMAT                    = 0x906E,
	GL_IMAGE_FORMAT_COMPATIBILITY_TYPE     = 0x90C7,
	GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE  = 0x90C8,
	GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS = 0x90C9,
	GL_MAX_VERTEX_IMAGE_UNIFORMS           = 0x90CA,
	GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS     = 0x90CB,
	GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS  = 0x90CC,
	GL_MAX_GEOMETRY_IMAGE_UNIFORMS         = 0x90CD,
	GL_MAX_FRAGMENT_IMAGE_UNIFORMS         = 0x90CE,
	GL_MAX_COMBINED_IMAGE_UNIFORMS         = 0x90CF,
	GL_COMPRESSED_RGBA_BPTC_UNORM         = 0x8E8C,
	GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM   = 0x8E8D,
	GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT   = 0x8E8E,
	GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT = 0x8E8F,
	GL_TEXTURE_IMMUTABLE_FORMAT = 0x912F,
# ifndef GL_VERSION_4_1
	GL_FIXED = 0x140C,
	GL_IMPLEMENTATION_COLOR_READ_TYPE   = 0x8B9A,
	GL_IMPLEMENTATION_COLOR_READ_FORMAT = 0x8B9B,
	GL_LOW_FLOAT    = 0x8DF0,
	GL_MEDIUM_FLOAT = 0x8DF1,
	GL_HIGH_FLOAT   = 0x8DF2,
	GL_LOW_INT      = 0x8DF3,
	GL_MEDIUM_INT   = 0x8DF4,
	GL_HIGH_INT     = 0x8DF5,
	GL_SHADER_COMPILER = 0x8DFA,
	GL_SHADER_BINARY_FORMATS = 0x8DF8,
	GL_NUM_SHADER_BINARY_FORMATS = 0x8DF9,
	GL_MAX_VERTEX_UNIFORM_VECTORS   = 0x8DFB,
	GL_MAX_VARYING_VECTORS          = 0x8DFC,
	GL_MAX_FRAGMENT_UNIFORM_VECTORS = 0x8DFD,
	GL_RGB565 = 0x8D62,
	GL_PROGRAM_BINARY_RETRIEVABLE_HINT = 0x8257,
	GL_PROGRAM_BINARY_LENGTH = 0x8741,
	GL_NUM_PROGRAM_BINARY_FORMATS = 0x87FE,
	GL_PROGRAM_BINARY_FORMATS     = 0x87FF,
	GL_PROGRAM_SEPARABLE               = 0x8258,
	GL_ACTIVE_PROGRAM                  = 0x8259,
	GL_PROGRAM_PIPELINE_BINDING        = 0x825A,
	GL_MAX_VIEWPORTS                   = 0x825B,
	GL_VIEWPORT_SUBPIXEL_BITS          = 0x825C,
	GL_VIEWPORT_BOUNDS_RANGE           = 0x825D,
	GL_LAYER_PROVOKING_VERTEX          = 0x825E,
	GL_VIEWPORT_INDEX_PROVOKING_VERTEX = 0x825F,
	GL_UNDEFINED_VERTEX = 0x8260,
# ifndef GL_VERSION_4_0
	GL_SAMPLE_SHADING           = 0x8C36,
	GL_MIN_SAMPLE_SHADING_VALUE = 0x8C37,
	GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET = 0x8E5E,
	GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET = 0x8E5F,
	GL_TEXTURE_CUBE_MAP_ARRAY              = 0x9009,
	GL_TEXTURE_BINDING_CUBE_MAP_ARRAY      = 0x900A,
	GL_PROXY_TEXTURE_CUBE_MAP_ARRAY        = 0x900B,
	GL_SAMPLER_CUBE_MAP_ARRAY              = 0x900C,
	GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW       = 0x900D,
	GL_INT_SAMPLER_CUBE_MAP_ARRAY          = 0x900E,
	GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY = 0x900F,
	GL_DRAW_INDIRECT_BUFFER = 0x8F3F,
	GL_DRAW_INDIRECT_BUFFER_BINDING = 0x8F43,
	GL_GEOMETRY_SHADER_INVOCATIONS = 0x887F,
	GL_MAX_GEOMETRY_SHADER_INVOCATIONS    = 0x8E5A,
	GL_MIN_FRAGMENT_INTERPOLATION_OFFSET  = 0x8E5B,
	GL_MAX_FRAGMENT_INTERPOLATION_OFFSET  = 0x8E5C,
	GL_FRAGMENT_INTERPOLATION_OFFSET_BITS = 0x8E5D,
	GL_MAX_VERTEX_STREAMS = 0x8E71,
	GL_DOUBLE_VEC2   = 0x8FFC,
	GL_DOUBLE_VEC3   = 0x8FFD,
	GL_DOUBLE_VEC4   = 0x8FFE,
	GL_DOUBLE_MAT2   = 0x8F46,
	GL_DOUBLE_MAT3   = 0x8F47,
	GL_DOUBLE_MAT4   = 0x8F48,
	GL_DOUBLE_MAT2x3 = 0x8F49,
	GL_DOUBLE_MAT2x4 = 0x8F4A,
	GL_DOUBLE_MAT3x2 = 0x8F4B,
	GL_DOUBLE_MAT3x4 = 0x8F4C,
	GL_DOUBLE_MAT4x2 = 0x8F4D,
	GL_DOUBLE_MAT4x3 = 0x8F4E,
	GL_ACTIVE_SUBROUTINES         = 0x8DE5,
	GL_ACTIVE_SUBROUTINE_UNIFORMS = 0x8DE6,
	GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS  = 0x8E47,
	GL_ACTIVE_SUBROUTINE_MAX_LENGTH         = 0x8E48,
	GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH = 0x8E49,
	GL_MAX_SUBROUTINES                  = 0x8DE7,
	GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS = 0x8DE8,
	GL_NUM_COMPATIBLE_SUBROUTINES = 0x8E4A,
	GL_COMPATIBLE_SUBROUTINES     = 0x8E4B,
	GL_PATCHES = 0x000E,
	GL_PATCH_VERTICES                           = 0x8E72,
	GL_PATCH_DEFAULT_INNER_LEVEL                = 0x8E73,
	GL_PATCH_DEFAULT_OUTER_LEVEL                = 0x8E74,
	GL_TESS_CONTROL_OUTPUT_VERTICES             = 0x8E75,
	GL_TESS_GEN_MODE                            = 0x8E76,
	GL_TESS_GEN_SPACING                         = 0x8E77,
	GL_TESS_GEN_VERTEX_ORDER                    = 0x8E78,
	GL_TESS_GEN_POINT_MODE                      = 0x8E79,
	GL_ISOLINES                                 = 0x8E7A,
	GL_FRACTIONAL_ODD                           = 0x8E7B,
	GL_FRACTIONAL_EVEN                          = 0x8E7C,
	GL_MAX_PATCH_VERTICES                       = 0x8E7D,
	GL_MAX_TESS_GEN_LEVEL                       = 0x8E7E,
	GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS      = 0x8E7F,
	GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS   = 0x8E80,
	GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS     = 0x8E81,
	GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS  = 0x8E82,
	GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS       = 0x8E83,
	GL_MAX_TESS_PATCH_COMPONENTS                = 0x8E84,
	GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS = 0x8E85,
	GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS    = 0x8E86,
	GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS          = 0x8E89,
	GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS       = 0x8E8A,
	GL_MAX_TESS_CONTROL_INPUT_COMPONENTS    = 0x886C,
	GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS = 0x886D,
	GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS    = 0x8E1E,
	GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS = 0x8E1F,
	GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER    = 0x84F0,
	GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER = 0x84F1,
	GL_TESS_EVALUATION_SHADER = 0x8E87,
	GL_TESS_CONTROL_SHADER    = 0x8E88,
	GL_TRANSFORM_FEEDBACK               = 0x8E22,
	GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED = 0x8E23,
	GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE = 0x8E24,
	GL_TRANSFORM_FEEDBACK_BINDING       = 0x8E25,
	GL_MAX_TRANSFORM_FEEDBACK_BUFFERS = 0x8E70,
# ifndef GL_VERSION_3_3
	GL_VERTEX_ATTRIB_ARRAY_DIVISOR = 0x88FE,
	GL_SRC1_COLOR                   = 0x88F9,
	GL_ONE_MINUS_SRC1_COLOR         = 0x88FA,
	GL_ONE_MINUS_SRC1_ALPHA         = 0x88FB,
	GL_MAX_DUAL_SOURCE_DRAW_BUFFERS = 0x88FC,
	GL_ANY_SAMPLES_PASSED = 0x8C2F,
	GL_SAMPLER_BINDING = 0x8919,
	GL_RGB10_A2UI = 0x906F,
	GL_TEXTURE_SWIZZLE_R    = 0x8E42,
	GL_TEXTURE_SWIZZLE_G    = 0x8E43,
	GL_TEXTURE_SWIZZLE_B    = 0x8E44,
	GL_TEXTURE_SWIZZLE_A    = 0x8E45,
	GL_TEXTURE_SWIZZLE_RGBA = 0x8E46,
	GL_TIME_ELAPSED = 0x88BF,
	GL_TIMESTAMP = 0x8E28,
	GL_INT_2_10_10_10_REV = 0x8D9F,
# ifndef GL_VERSION_3_2
	GL_LINES_ADJACENCY          = 0x000A,
	GL_LINE_STRIP_ADJACENCY     = 0x000B,
	GL_TRIANGLES_ADJACENCY      = 0x000C,
	GL_TRIANGLE_STRIP_ADJACENCY = 0x000D,
	GL_PROGRAM_POINT_SIZE = 0x8642,
	GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS = 0x8C29,
	GL_FRAMEBUFFER_ATTACHMENT_LAYERED       = 0x8DA7,
	GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS = 0x8DA8,
	GL_GEOMETRY_SHADER = 0x8DD9,
	GL_GEOMETRY_VERTICES_OUT = 0x8916,
	GL_GEOMETRY_INPUT_TYPE   = 0x8917,
	GL_GEOMETRY_OUTPUT_TYPE  = 0x8918,
	GL_MAX_GEOMETRY_UNIFORM_COMPONENTS      = 0x8DDF,
	GL_MAX_GEOMETRY_OUTPUT_VERTICES         = 0x8DE0,
	GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS = 0x8DE1,
	GL_MAX_VERTEX_OUTPUT_COMPONENTS   = 0x9122,
	GL_MAX_GEOMETRY_INPUT_COMPONENTS  = 0x9123,
	GL_MAX_GEOMETRY_OUTPUT_COMPONENTS = 0x9124,
	GL_MAX_FRAGMENT_INPUT_COMPONENTS  = 0x9125,
	GL_CONTEXT_PROFILE_MASK           = 0x9126,
	GL_DEPTH_CLAMP = 0x864F,
	GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION = 0x8E4C,
	GL_FIRST_VERTEX_CONVENTION                  = 0x8E4D,
	GL_LAST_VERTEX_CONVENTION                   = 0x8E4E,
	GL_PROVOKING_VERTEX                         = 0x8E4F,
	GL_TEXTURE_CUBE_MAP_SEAMLESS = 0x884F,
	GL_MAX_SERVER_WAIT_TIMEOUT    = 0x9111,
	GL_OBJECT_TYPE                = 0x9112,
	GL_SYNC_CONDITION             = 0x9113,
	GL_SYNC_STATUS                = 0x9114,
	GL_SYNC_FLAGS                 = 0x9115,
	GL_SYNC_FENCE                 = 0x9116,
	GL_SYNC_GPU_COMMANDS_COMPLETE = 0x9117,
	GL_UNSIGNALED                 = 0x9118,
	GL_SIGNALED                   = 0x9119,
	GL_ALREADY_SIGNALED           = 0x911A,
	GL_TIMEOUT_EXPIRED            = 0x911B,
	GL_CONDITION_SATISFIED        = 0x911C,
	GL_WAIT_FAILED                = 0x911D,
	GL_SAMPLE_POSITION   = 0x8E50,
	GL_SAMPLE_MASK       = 0x8E51,
	GL_SAMPLE_MASK_VALUE = 0x8E52,
	GL_MAX_SAMPLE_MASK_WORDS = 0x8E59,
	GL_TEXTURE_2D_MULTISAMPLE                    = 0x9100,
	GL_PROXY_TEXTURE_2D_MULTISAMPLE              = 0x9101,
	GL_TEXTURE_2D_MULTISAMPLE_ARRAY              = 0x9102,
	GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY        = 0x9103,
	GL_TEXTURE_BINDING_2D_MULTISAMPLE            = 0x9104,
	GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY      = 0x9105,
	GL_TEXTURE_SAMPLES                           = 0x9106,
	GL_TEXTURE_FIXED_SAMPLE_LOCATIONS            = 0x9107,
	GL_SAMPLER_2D_MULTISAMPLE                    = 0x9108,
	GL_INT_SAMPLER_2D_MULTISAMPLE                = 0x9109,
	GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE       = 0x910A,
	GL_SAMPLER_2D_MULTISAMPLE_ARRAY              = 0x910B,
	GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY          = 0x910C,
	GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = 0x910D,
	GL_MAX_COLOR_TEXTURE_SAMPLES                 = 0x910E,
	GL_MAX_DEPTH_TEXTURE_SAMPLES                 = 0x910F,
	GL_MAX_INTEGER_SAMPLES                       = 0x9110,
# ifndef GL_VERSION_3_1
	GL_SAMPLER_2D_RECT        = 0x8B63,
	GL_SAMPLER_2D_RECT_SHADOW = 0x8B64,
	GL_SAMPLER_BUFFER = 0x8DC2,
	GL_INT_SAMPLER_2D_RECT = 0x8DCD,
	GL_INT_SAMPLER_BUFFER = 0x8DD0,
	GL_UNSIGNED_INT_SAMPLER_2D_RECT = 0x8DD5,
	GL_UNSIGNED_INT_SAMPLER_BUFFER = 0x8DD8,
	GL_TEXTURE_BUFFER                    = 0x8C2A,
	GL_MAX_TEXTURE_BUFFER_SIZE           = 0x8C2B,
	GL_TEXTURE_BINDING_BUFFER            = 0x8C2C,
	GL_TEXTURE_BUFFER_DATA_STORE_BINDING = 0x8C2D,
	GL_TEXTURE_RECTANGLE          = 0x84F5,
	GL_TEXTURE_BINDING_RECTANGLE  = 0x84F6,
	GL_PROXY_TEXTURE_RECTANGLE    = 0x84F7,
	GL_MAX_RECTANGLE_TEXTURE_SIZE = 0x84F8,
	GL_R8_SNORM                = 0x8F94,
	GL_RG8_SNORM               = 0x8F95,
	GL_RGB8_SNORM              = 0x8F96,
	GL_RGBA8_SNORM             = 0x8F97,
	GL_R16_SNORM               = 0x8F98,
	GL_RG16_SNORM              = 0x8F99,
	GL_RGB16_SNORM             = 0x8F9A,
	GL_RGBA16_SNORM            = 0x8F9B,
	GL_SIGNED_NORMALIZED       = 0x8F9C,
	GL_PRIMITIVE_RESTART       = 0x8F9D,
	GL_PRIMITIVE_RESTART_INDEX = 0x8F9E,
	GL_COPY_READ_BUFFER  = 0x8F36,
	GL_COPY_WRITE_BUFFER = 0x8F37,
	GL_UNIFORM_BUFFER = 0x8A11,
	GL_UNIFORM_BUFFER_BINDING = 0x8A28,
	GL_UNIFORM_BUFFER_START   = 0x8A29,
	GL_UNIFORM_BUFFER_SIZE    = 0x8A2A,
	GL_MAX_VERTEX_UNIFORM_BLOCKS                   = 0x8A2B,
	GL_MAX_GEOMETRY_UNIFORM_BLOCKS                 = 0x8A2C,
	GL_MAX_FRAGMENT_UNIFORM_BLOCKS                 = 0x8A2D,
	GL_MAX_COMBINED_UNIFORM_BLOCKS                 = 0x8A2E,
	GL_MAX_UNIFORM_BUFFER_BINDINGS                 = 0x8A2F,
	GL_MAX_UNIFORM_BLOCK_SIZE                      = 0x8A30,
	GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS      = 0x8A31,
	GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS    = 0x8A32,
	GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS    = 0x8A33,
	GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT             = 0x8A34,
	GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH        = 0x8A35,
	GL_ACTIVE_UNIFORM_BLOCKS                       = 0x8A36,
	GL_UNIFORM_TYPE                                = 0x8A37,
	GL_UNIFORM_SIZE                                = 0x8A38,
	GL_UNIFORM_NAME_LENGTH                         = 0x8A39,
	GL_UNIFORM_BLOCK_INDEX                         = 0x8A3A,
	GL_UNIFORM_OFFSET                              = 0x8A3B,
	GL_UNIFORM_ARRAY_STRIDE                        = 0x8A3C,
	GL_UNIFORM_MATRIX_STRIDE                       = 0x8A3D,
	GL_UNIFORM_IS_ROW_MAJOR                        = 0x8A3E,
	GL_UNIFORM_BLOCK_BINDING                       = 0x8A3F,
	GL_UNIFORM_BLOCK_DATA_SIZE                     = 0x8A40,
	GL_UNIFORM_BLOCK_NAME_LENGTH                   = 0x8A41,
	GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS               = 0x8A42,
	GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES        = 0x8A43,
	GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER   = 0x8A44,
	GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER = 0x8A45,
	GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER = 0x8A46,
# ifndef GL_VERSION_3_0
	GL_COMPARE_REF_TO_TEXTURE = 0x884E,
	GL_CLIP_DISTANCE0 = 0x3000,
	GL_CLIP_DISTANCE1 = 0x3001,
	GL_CLIP_DISTANCE2 = 0x3002,
	GL_CLIP_DISTANCE3 = 0x3003,
	GL_CLIP_DISTANCE4 = 0x3004,
	GL_CLIP_DISTANCE5 = 0x3005,
	GL_CLIP_DISTANCE6 = 0x3006,
	GL_CLIP_DISTANCE7 = 0x3007,
	GL_MAX_CLIP_DISTANCES = 0x0D32,
	GL_MAJOR_VERSION  = 0x821B,
	GL_MINOR_VERSION  = 0x821C,
	GL_NUM_EXTENSIONS = 0x821D,
	GL_CONTEXT_FLAGS  = 0x821E,
	GL_COMPRESSED_RED = 0x8225,
	GL_COMPRESSED_RG  = 0x8226,
	GL_RGBA32F = 0x8814,
	GL_RGB32F  = 0x8815,
	GL_RGBA16F = 0x881A,
	GL_RGB16F  = 0x881B,
	GL_VERTEX_ATTRIB_ARRAY_INTEGER = 0x88FD,
	GL_MAX_ARRAY_TEXTURE_LAYERS = 0x88FF,
	GL_MIN_PROGRAM_TEXEL_OFFSET = 0x8904,
	GL_MAX_PROGRAM_TEXEL_OFFSET = 0x8905,
	GL_CLAMP_READ_COLOR = 0x891C,
	GL_FIXED_ONLY       = 0x891D,
	GL_MAX_VARYING_COMPONENTS = 0x8B4B,
	GL_TEXTURE_1D_ARRAY         = 0x8C18,
	GL_PROXY_TEXTURE_1D_ARRAY   = 0x8C19,
	GL_TEXTURE_2D_ARRAY         = 0x8C1A,
	GL_PROXY_TEXTURE_2D_ARRAY   = 0x8C1B,
	GL_TEXTURE_BINDING_1D_ARRAY = 0x8C1C,
	GL_TEXTURE_BINDING_2D_ARRAY = 0x8C1D,
	GL_R11F_G11F_B10F               = 0x8C3A,
	GL_UNSIGNED_INT_10F_11F_11F_REV = 0x8C3B,
	GL_RGB9_E5                  = 0x8C3D,
	GL_UNSIGNED_INT_5_9_9_9_REV = 0x8C3E,
	GL_TEXTURE_SHARED_SIZE      = 0x8C3F,
	GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH = 0x8C76,
	GL_TRANSFORM_FEEDBACK_BUFFER_MODE             = 0x8C7F,
	GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS = 0x8C80,
	GL_TRANSFORM_FEEDBACK_VARYINGS     = 0x8C83,
	GL_TRANSFORM_FEEDBACK_BUFFER_START = 0x8C84,
	GL_TRANSFORM_FEEDBACK_BUFFER_SIZE  = 0x8C85,
	GL_PRIMITIVES_GENERATED                  = 0x8C87,
	GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN = 0x8C88,
	GL_RASTERIZER_DISCARD                    = 0x8C89,
	GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS = 0x8C8A,
	GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS       = 0x8C8B,
	GL_INTERLEAVED_ATTRIBS                           = 0x8C8C,
	GL_SEPARATE_ATTRIBS                              = 0x8C8D,
	GL_TRANSFORM_FEEDBACK_BUFFER                     = 0x8C8E,
	GL_TRANSFORM_FEEDBACK_BUFFER_BINDING             = 0x8C8F,
	GL_RGBA32UI = 0x8D70,
	GL_RGB32UI = 0x8D71,
	GL_RGBA16UI = 0x8D76,
	GL_RGB16UI = 0x8D77,
	GL_RGBA8UI = 0x8D7C,
	GL_RGB8UI  = 0x8D7D,
	GL_RGBA32I = 0x8D82,
	GL_RGB32I  = 0x8D83,
	GL_RGBA16I = 0x8D88,
	GL_RGB16I  = 0x8D89,
	GL_RGBA8I = 0x8D8E,
	GL_RGB8I  = 0x8D8F,
	GL_RED_INTEGER   = 0x8D94,
	GL_GREEN_INTEGER = 0x8D95,
	GL_BLUE_INTEGER  = 0x8D96,
	GL_RGB_INTEGER   = 0x8D98,
	GL_RGBA_INTEGER  = 0x8D99,
	GL_BGR_INTEGER   = 0x8D9A,
	GL_BGRA_INTEGER  = 0x8D9B,
	GL_SAMPLER_1D_ARRAY = 0x8DC0,
	GL_SAMPLER_2D_ARRAY = 0x8DC1,
	GL_SAMPLER_1D_ARRAY_SHADOW = 0x8DC3,
	GL_SAMPLER_2D_ARRAY_SHADOW = 0x8DC4,
	GL_SAMPLER_CUBE_SHADOW     = 0x8DC5,
	GL_UNSIGNED_INT_VEC2       = 0x8DC6,
	GL_UNSIGNED_INT_VEC3       = 0x8DC7,
	GL_UNSIGNED_INT_VEC4       = 0x8DC8,
	GL_INT_SAMPLER_1D          = 0x8DC9,
	GL_INT_SAMPLER_2D          = 0x8DCA,
	GL_INT_SAMPLER_3D          = 0x8DCB,
	GL_INT_SAMPLER_CUBE        = 0x8DCC,
	GL_INT_SAMPLER_1D_ARRAY = 0x8DCE,
	GL_INT_SAMPLER_2D_ARRAY = 0x8DCF,
	GL_UNSIGNED_INT_SAMPLER_1D   = 0x8DD1,
	GL_UNSIGNED_INT_SAMPLER_2D   = 0x8DD2,
	GL_UNSIGNED_INT_SAMPLER_3D   = 0x8DD3,
	GL_UNSIGNED_INT_SAMPLER_CUBE = 0x8DD4,
	GL_UNSIGNED_INT_SAMPLER_1D_ARRAY = 0x8DD6,
	GL_UNSIGNED_INT_SAMPLER_2D_ARRAY = 0x8DD7,
	GL_QUERY_WAIT              = 0x8E13,
	GL_QUERY_NO_WAIT           = 0x8E14,
	GL_QUERY_BY_REGION_WAIT    = 0x8E15,
	GL_QUERY_BY_REGION_NO_WAIT = 0x8E16,
	GL_BUFFER_ACCESS_FLAGS = 0x911F,
	GL_BUFFER_MAP_LENGTH   = 0x9120,
	GL_BUFFER_MAP_OFFSET   = 0x9121,
	GL_DEPTH_COMPONENT32F = 0x8CAC,
	GL_DEPTH32F_STENCIL8  = 0x8CAD,
	GL_FLOAT_32_UNSIGNED_INT_24_8_REV = 0x8DAD,
	GL_INVALID_FRAMEBUFFER_OPERATION = 0x0506,
	GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING = 0x8210,
	GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE = 0x8211,
	GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE       = 0x8212,
	GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE     = 0x8213,
	GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE      = 0x8214,
	GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE     = 0x8215,
	GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE     = 0x8216,
	GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE   = 0x8217,
	GL_FRAMEBUFFER_DEFAULT                   = 0x8218,
	GL_FRAMEBUFFER_UNDEFINED                 = 0x8219,
	GL_DEPTH_STENCIL_ATTACHMENT              = 0x821A,
	GL_MAX_RENDERBUFFER_SIZE = 0x84E8,
	GL_DEPTH_STENCIL     = 0x84F9,
	GL_UNSIGNED_INT_24_8 = 0x84FA,
	GL_DEPTH24_STENCIL8     = 0x88F0,
	GL_TEXTURE_STENCIL_SIZE = 0x88F1,
	GL_TEXTURE_RED_TYPE   = 0x8C10,
	GL_TEXTURE_GREEN_TYPE = 0x8C11,
	GL_TEXTURE_BLUE_TYPE  = 0x8C12,
	GL_TEXTURE_ALPHA_TYPE = 0x8C13,
	GL_TEXTURE_DEPTH_TYPE  = 0x8C16,
	GL_UNSIGNED_NORMALIZED = 0x8C17,
	GL_FRAMEBUFFER_BINDING      = 0x8CA6,
	GL_DRAW_FRAMEBUFFER_BINDING = 0x8CA6,
	GL_RENDERBUFFER_BINDING     = 0x8CA7,
	GL_READ_FRAMEBUFFER         = 0x8CA8,
	GL_DRAW_FRAMEBUFFER         = 0x8CA9,
	GL_READ_FRAMEBUFFER_BINDING = 0x8CAA,
	GL_RENDERBUFFER_SAMPLES     = 0x8CAB,
	GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE           = 0x8CD0,
	GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME           = 0x8CD1,
	GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL         = 0x8CD2,
	GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE = 0x8CD3,
	GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER         = 0x8CD4,
	GL_FRAMEBUFFER_COMPLETE                         = 0x8CD5,
	GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT            = 0x8CD6,
	GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT    = 0x8CD7,
	GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER = 0x8CDB,
	GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER = 0x8CDC,
	GL_FRAMEBUFFER_UNSUPPORTED            = 0x8CDD,
	GL_MAX_COLOR_ATTACHMENTS              = 0x8CDF,
	GL_COLOR_ATTACHMENT0  = 0x8CE0,
	GL_COLOR_ATTACHMENT1  = 0x8CE1,
	GL_COLOR_ATTACHMENT2  = 0x8CE2,
	GL_COLOR_ATTACHMENT3  = 0x8CE3,
	GL_COLOR_ATTACHMENT4  = 0x8CE4,
	GL_COLOR_ATTACHMENT5  = 0x8CE5,
	GL_COLOR_ATTACHMENT6  = 0x8CE6,
	GL_COLOR_ATTACHMENT7  = 0x8CE7,
	GL_COLOR_ATTACHMENT8  = 0x8CE8,
	GL_COLOR_ATTACHMENT9  = 0x8CE9,
	GL_COLOR_ATTACHMENT10 = 0x8CEA,
	GL_COLOR_ATTACHMENT11 = 0x8CEB,
	GL_COLOR_ATTACHMENT12 = 0x8CEC,
	GL_COLOR_ATTACHMENT13 = 0x8CED,
	GL_COLOR_ATTACHMENT14 = 0x8CEE,
	GL_COLOR_ATTACHMENT15 = 0x8CEF,
	GL_COLOR_ATTACHMENT16 = 0x8CF0,
	GL_COLOR_ATTACHMENT17 = 0x8CF1,
	GL_COLOR_ATTACHMENT18 = 0x8CF2,
	GL_COLOR_ATTACHMENT19 = 0x8CF3,
	GL_COLOR_ATTACHMENT20 = 0x8CF4,
	GL_COLOR_ATTACHMENT21 = 0x8CF5,
	GL_COLOR_ATTACHMENT22 = 0x8CF6,
	GL_COLOR_ATTACHMENT23 = 0x8CF7,
	GL_COLOR_ATTACHMENT24 = 0x8CF8,
	GL_COLOR_ATTACHMENT25 = 0x8CF9,
	GL_COLOR_ATTACHMENT26 = 0x8CFA,
	GL_COLOR_ATTACHMENT27 = 0x8CFB,
	GL_COLOR_ATTACHMENT28 = 0x8CFC,
	GL_COLOR_ATTACHMENT29 = 0x8CFD,
	GL_COLOR_ATTACHMENT30 = 0x8CFE,
	GL_COLOR_ATTACHMENT31 = 0x8CFF,
	GL_DEPTH_ATTACHMENT   = 0x8D00,
	GL_STENCIL_ATTACHMENT = 0x8D20,
	GL_FRAMEBUFFER                  = 0x8D40,
	GL_RENDERBUFFER                 = 0x8D41,
	GL_RENDERBUFFER_WIDTH           = 0x8D42,
	GL_RENDERBUFFER_HEIGHT          = 0x8D43,
	GL_RENDERBUFFER_INTERNAL_FORMAT = 0x8D44,
	GL_STENCIL_INDEX1  = 0x8D46,
	GL_STENCIL_INDEX4  = 0x8D47,
	GL_STENCIL_INDEX8  = 0x8D48,
	GL_STENCIL_INDEX16 = 0x8D49,
	GL_RENDERBUFFER_RED_SIZE              = 0x8D50,
	GL_RENDERBUFFER_GREEN_SIZE            = 0x8D51,
	GL_RENDERBUFFER_BLUE_SIZE             = 0x8D52,
	GL_RENDERBUFFER_ALPHA_SIZE            = 0x8D53,
	GL_RENDERBUFFER_DEPTH_SIZE            = 0x8D54,
	GL_RENDERBUFFER_STENCIL_SIZE          = 0x8D55,
	GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE = 0x8D56,
	GL_MAX_SAMPLES                        = 0x8D57,
	GL_FRAMEBUFFER_SRGB = 0x8DB9,
	GL_HALF_FLOAT = 0x140B,
	GL_COMPRESSED_RED_RGTC1        = 0x8DBB,
	GL_COMPRESSED_SIGNED_RED_RGTC1 = 0x8DBC,
	GL_COMPRESSED_RG_RGTC2         = 0x8DBD,
	GL_COMPRESSED_SIGNED_RG_RGTC2  = 0x8DBE,
	GL_RG         = 0x8227,
	GL_RG_INTEGER = 0x8228,
	GL_R8         = 0x8229,
	GL_R16        = 0x822A,
	GL_RG8        = 0x822B,
	GL_RG16       = 0x822C,
	GL_R16F       = 0x822D,
	GL_R32F       = 0x822E,
	GL_RG16F      = 0x822F,
	GL_RG32F      = 0x8230,
	GL_R8I        = 0x8231,
	GL_R8UI       = 0x8232,
	GL_R16I       = 0x8233,
	GL_R16UI      = 0x8234,
	GL_R32I       = 0x8235,
	GL_R32UI      = 0x8236,
	GL_RG8I       = 0x8237,
	GL_RG8UI      = 0x8238,
	GL_RG16I      = 0x8239,
	GL_RG16UI     = 0x823A,
	GL_RG32I      = 0x823B,
	GL_RG32UI     = 0x823C,
	GL_VERTEX_ARRAY_BINDING = 0x85B5,
# ifndef GL_VERSION_2_1
	GL_PIXEL_PACK_BUFFER         = 0x88EB,
	GL_PIXEL_UNPACK_BUFFER       = 0x88EC,
	GL_PIXEL_PACK_BUFFER_BINDING = 0x88ED,
	GL_PIXEL_UNPACK_BUFFER_BINDING = 0x88EF,
	GL_FLOAT_MAT2x3 = 0x8B65,
	GL_FLOAT_MAT2x4 = 0x8B66,
	GL_FLOAT_MAT3x2 = 0x8B67,
	GL_FLOAT_MAT3x4 = 0x8B68,
	GL_FLOAT_MAT4x2 = 0x8B69,
	GL_FLOAT_MAT4x3 = 0x8B6A,
	GL_SRGB         = 0x8C40,
	GL_SRGB8        = 0x8C41,
	GL_SRGB_ALPHA   = 0x8C42,
	GL_SRGB8_ALPHA8 = 0x8C43,
	GL_COMPRESSED_SRGB       = 0x8C48,
	GL_COMPRESSED_SRGB_ALPHA = 0x8C49,
# ifndef GL_VERSION_2_0
	GL_BLEND_EQUATION_RGB = 0x8009,
	GL_VERTEX_ATTRIB_ARRAY_ENABLED = 0x8622,
	GL_VERTEX_ATTRIB_ARRAY_SIZE    = 0x8623,
	GL_VERTEX_ATTRIB_ARRAY_STRIDE  = 0x8624,
	GL_VERTEX_ATTRIB_ARRAY_TYPE    = 0x8625,
	GL_CURRENT_VERTEX_ATTRIB       = 0x8626,
	GL_VERTEX_PROGRAM_POINT_SIZE   = 0x8642,
	GL_VERTEX_ATTRIB_ARRAY_POINTER = 0x8645,
	GL_STENCIL_BACK_FUNC            = 0x8800,
	GL_STENCIL_BACK_FAIL            = 0x8801,
	GL_STENCIL_BACK_PASS_DEPTH_FAIL = 0x8802,
	GL_STENCIL_BACK_PASS_DEPTH_PASS = 0x8803,
	GL_MAX_DRAW_BUFFERS = 0x8824,
	GL_DRAW_BUFFER0     = 0x8825,
	GL_DRAW_BUFFER1     = 0x8826,
	GL_DRAW_BUFFER2     = 0x8827,
	GL_DRAW_BUFFER3     = 0x8828,
	GL_DRAW_BUFFER4     = 0x8829,
	GL_DRAW_BUFFER5     = 0x882A,
	GL_DRAW_BUFFER6     = 0x882B,
	GL_DRAW_BUFFER7     = 0x882C,
	GL_DRAW_BUFFER8     = 0x882D,
	GL_DRAW_BUFFER9     = 0x882E,
	GL_DRAW_BUFFER10    = 0x882F,
	GL_DRAW_BUFFER11    = 0x8830,
	GL_DRAW_BUFFER12    = 0x8831,
	GL_DRAW_BUFFER13    = 0x8832,
	GL_DRAW_BUFFER14    = 0x8833,
	GL_DRAW_BUFFER15    = 0x8834,
	GL_BLEND_EQUATION_ALPHA = 0x883D,
	GL_MAX_VERTEX_ATTRIBS             = 0x8869,
	GL_VERTEX_ATTRIB_ARRAY_NORMALIZED = 0x886A,
	GL_MAX_TEXTURE_IMAGE_UNITS = 0x8872,
	GL_FRAGMENT_SHADER = 0x8B30,
	GL_VERTEX_SHADER   = 0x8B31,
	GL_MAX_FRAGMENT_UNIFORM_COMPONENTS  = 0x8B49,
	GL_MAX_VERTEX_UNIFORM_COMPONENTS    = 0x8B4A,
	GL_MAX_VARYING_FLOATS               = 0x8B4B,
	GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS   = 0x8B4C,
	GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS = 0x8B4D,
	GL_SHADER_TYPE       = 0x8B4F,
	GL_FLOAT_VEC2        = 0x8B50,
	GL_FLOAT_VEC3        = 0x8B51,
	GL_FLOAT_VEC4        = 0x8B52,
	GL_INT_VEC2          = 0x8B53,
	GL_INT_VEC3          = 0x8B54,
	GL_INT_VEC4          = 0x8B55,
	GL_BOOL              = 0x8B56,
	GL_BOOL_VEC2         = 0x8B57,
	GL_BOOL_VEC3         = 0x8B58,
	GL_BOOL_VEC4         = 0x8B59,
	GL_FLOAT_MAT2        = 0x8B5A,
	GL_FLOAT_MAT3        = 0x8B5B,
	GL_FLOAT_MAT4        = 0x8B5C,
	GL_SAMPLER_1D        = 0x8B5D,
	GL_SAMPLER_2D        = 0x8B5E,
	GL_SAMPLER_3D        = 0x8B5F,
	GL_SAMPLER_CUBE      = 0x8B60,
	GL_SAMPLER_1D_SHADOW = 0x8B61,
	GL_SAMPLER_2D_SHADOW = 0x8B62,
	GL_DELETE_STATUS                   = 0x8B80,
	GL_COMPILE_STATUS                  = 0x8B81,
	GL_LINK_STATUS                     = 0x8B82,
	GL_VALIDATE_STATUS                 = 0x8B83,
	GL_INFO_LOG_LENGTH                 = 0x8B84,
	GL_ATTACHED_SHADERS                = 0x8B85,
	GL_ACTIVE_UNIFORMS                 = 0x8B86,
	GL_ACTIVE_UNIFORM_MAX_LENGTH       = 0x8B87,
	GL_SHADER_SOURCE_LENGTH            = 0x8B88,
	GL_ACTIVE_ATTRIBUTES               = 0x8B89,
	GL_ACTIVE_ATTRIBUTE_MAX_LENGTH     = 0x8B8A,
	GL_FRAGMENT_SHADER_DERIVATIVE_HINT = 0x8B8B,
	GL_SHADING_LANGUAGE_VERSION        = 0x8B8C,
	GL_CURRENT_PROGRAM                 = 0x8B8D,
	GL_POINT_SPRITE_COORD_ORIGIN = 0x8CA0,
	GL_LOWER_LEFT                = 0x8CA1,
	GL_UPPER_LEFT                = 0x8CA2,
	GL_STENCIL_BACK_REF          = 0x8CA3,
	GL_STENCIL_BACK_VALUE_MASK   = 0x8CA4,
	GL_STENCIL_BACK_WRITEMASK    = 0x8CA5,
# ifndef GL_VERSION_1_5
	GL_BUFFER_SIZE  = 0x8764,
	GL_BUFFER_USAGE = 0x8765,
	GL_QUERY_COUNTER_BITS     = 0x8864,
	GL_CURRENT_QUERY          = 0x8865,
	GL_QUERY_RESULT           = 0x8866,
	GL_QUERY_RESULT_AVAILABLE = 0x8867,
	GL_ARRAY_BUFFER                 = 0x8892,
	GL_ELEMENT_ARRAY_BUFFER         = 0x8893,
	GL_ARRAY_BUFFER_BINDING         = 0x8894,
	GL_ELEMENT_ARRAY_BUFFER_BINDING = 0x8895,
	GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING = 0x889F,
	GL_READ_ONLY          = 0x88B8,
	GL_WRITE_ONLY         = 0x88B9,
	GL_READ_WRITE         = 0x88BA,
	GL_BUFFER_ACCESS      = 0x88BB,
	GL_BUFFER_MAPPED      = 0x88BC,
	GL_BUFFER_MAP_POINTER = 0x88BD,
	GL_STREAM_DRAW = 0x88E0,
	GL_STREAM_READ = 0x88E1,
	GL_STREAM_COPY = 0x88E2,
	GL_STATIC_DRAW = 0x88E4,
	GL_STATIC_READ = 0x88E5,
	GL_STATIC_COPY = 0x88E6,
	GL_DYNAMIC_DRAW = 0x88E8,
	GL_DYNAMIC_READ = 0x88E9,
	GL_DYNAMIC_COPY = 0x88EA,
	GL_SAMPLES_PASSED = 0x8914,
	GL_SRC1_ALPHA = 0x8589,
# ifndef GL_VERSION_1_4
	GL_BLEND_DST_RGB   = 0x80C8,
	GL_BLEND_SRC_RGB   = 0x80C9,
	GL_BLEND_DST_ALPHA = 0x80CA,
	GL_BLEND_SRC_ALPHA = 0x80CB,
	GL_POINT_FADE_THRESHOLD_SIZE = 0x8128,
	GL_DEPTH_COMPONENT16 = 0x81A5,
	GL_DEPTH_COMPONENT24 = 0x81A6,
	GL_DEPTH_COMPONENT32 = 0x81A7,
	GL_MIRRORED_REPEAT = 0x8370,
	GL_MAX_TEXTURE_LOD_BIAS = 0x84FD,
	GL_TEXTURE_LOD_BIAS = 0x8501,
	GL_INCR_WRAP = 0x8507,
	GL_DECR_WRAP = 0x8508,
	GL_TEXTURE_DEPTH_SIZE = 0x884A,
	GL_TEXTURE_COMPARE_MODE = 0x884C,
	GL_TEXTURE_COMPARE_FUNC = 0x884D,
	GL_BLEND_COLOR = 0x8005,
	GL_BLEND_EQUATION = 0x8009,
	GL_CONSTANT_COLOR           = 0x8001,
	GL_ONE_MINUS_CONSTANT_COLOR = 0x8002,
	GL_CONSTANT_ALPHA           = 0x8003,
	GL_ONE_MINUS_CONSTANT_ALPHA = 0x8004,
	GL_FUNC_ADD = 0x8006,
	GL_FUNC_REVERSE_SUBTRACT = 0x800B,
	GL_FUNC_SUBTRACT         = 0x800A,
	GL_MIN = 0x8007,
	GL_MAX = 0x8008,
# ifndef GL_VERSION_1_3
	GL_TEXTURE0  = 0x84C0,
	GL_TEXTURE1  = 0x84C1,
	GL_TEXTURE2  = 0x84C2,
	GL_TEXTURE3  = 0x84C3,
	GL_TEXTURE4  = 0x84C4,
	GL_TEXTURE5  = 0x84C5,
	GL_TEXTURE6  = 0x84C6,
	GL_TEXTURE7  = 0x84C7,
	GL_TEXTURE8  = 0x84C8,
	GL_TEXTURE9  = 0x84C9,
	GL_TEXTURE10 = 0x84CA,
	GL_TEXTURE11 = 0x84CB,
	GL_TEXTURE12 = 0x84CC,
	GL_TEXTURE13 = 0x84CD,
	GL_TEXTURE14 = 0x84CE,
	GL_TEXTURE15 = 0x84CF,
	GL_TEXTURE16 = 0x84D0,
	GL_TEXTURE17 = 0x84D1,
	GL_TEXTURE18 = 0x84D2,
	GL_TEXTURE19 = 0x84D3,
	GL_TEXTURE20 = 0x84D4,
	GL_TEXTURE21 = 0x84D5,
	GL_TEXTURE22 = 0x84D6,
	GL_TEXTURE23 = 0x84D7,
	GL_TEXTURE24 = 0x84D8,
	GL_TEXTURE25 = 0x84D9,
	GL_TEXTURE26 = 0x84DA,
	GL_TEXTURE27 = 0x84DB,
	GL_TEXTURE28 = 0x84DC,
	GL_TEXTURE29 = 0x84DD,
	GL_TEXTURE30 = 0x84DE,
	GL_TEXTURE31 = 0x84DF,
	GL_ACTIVE_TEXTURE = 0x84E0,
	GL_MULTISAMPLE              = 0x809D,
	GL_SAMPLE_ALPHA_TO_COVERAGE = 0x809E,
	GL_SAMPLE_ALPHA_TO_ONE      = 0x809F,
	GL_SAMPLE_COVERAGE          = 0x80A0,
	GL_SAMPLE_BUFFERS         = 0x80A8,
	GL_SAMPLES                = 0x80A9,
	GL_SAMPLE_COVERAGE_VALUE  = 0x80AA,
	GL_SAMPLE_COVERAGE_INVERT = 0x80AB,
	GL_TEXTURE_CUBE_MAP            = 0x8513,
	GL_TEXTURE_BINDING_CUBE_MAP    = 0x8514,
	GL_TEXTURE_CUBE_MAP_POSITIVE_X = 0x8515,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X = 0x8516,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y = 0x8517,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y = 0x8518,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z = 0x8519,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z = 0x851A,
	GL_PROXY_TEXTURE_CUBE_MAP      = 0x851B,
	GL_MAX_CUBE_MAP_TEXTURE_SIZE   = 0x851C,
	GL_COMPRESSED_RGB           = 0x84ED,
	GL_COMPRESSED_RGBA          = 0x84EE,
	GL_TEXTURE_COMPRESSION_HINT = 0x84EF,
	GL_TEXTURE_COMPRESSED_IMAGE_SIZE  = 0x86A0,
	GL_TEXTURE_COMPRESSED             = 0x86A1,
	GL_NUM_COMPRESSED_TEXTURE_FORMATS = 0x86A2,
	GL_COMPRESSED_TEXTURE_FORMATS     = 0x86A3,
	GL_CLAMP_TO_BORDER = 0x812D,
# ifndef GL_VERSION_1_2
	GL_UNSIGNED_BYTE_3_3_2     = 0x8032,
	GL_UNSIGNED_SHORT_4_4_4_4  = 0x8033,
	GL_UNSIGNED_SHORT_5_5_5_1  = 0x8034,
	GL_UNSIGNED_INT_8_8_8_8    = 0x8035,
	GL_UNSIGNED_INT_10_10_10_2 = 0x8036,
	GL_TEXTURE_BINDING_3D  = 0x806A,
	GL_PACK_SKIP_IMAGES    = 0x806B,
	GL_PACK_IMAGE_HEIGHT   = 0x806C,
	GL_UNPACK_SKIP_IMAGES  = 0x806D,
	GL_UNPACK_IMAGE_HEIGHT = 0x806E,
	GL_TEXTURE_3D          = 0x806F,
	GL_PROXY_TEXTURE_3D    = 0x8070,
	GL_TEXTURE_DEPTH       = 0x8071,
	GL_TEXTURE_WRAP_R      = 0x8072,
	GL_MAX_3D_TEXTURE_SIZE = 0x8073,
	GL_UNSIGNED_BYTE_2_3_3_REV     = 0x8362,
	GL_UNSIGNED_SHORT_5_6_5        = 0x8363,
	GL_UNSIGNED_SHORT_5_6_5_REV    = 0x8364,
	GL_UNSIGNED_SHORT_4_4_4_4_REV  = 0x8365,
	GL_UNSIGNED_SHORT_1_5_5_5_REV  = 0x8366,
	GL_UNSIGNED_INT_8_8_8_8_REV    = 0x8367,
	GL_UNSIGNED_INT_2_10_10_10_REV = 0x8368,
	GL_BGR  = 0x80E0,
	GL_BGRA = 0x80E1,
	GL_MAX_ELEMENTS_VERTICES = 0x80E8,
	GL_MAX_ELEMENTS_INDICES  = 0x80E9,
	GL_CLAMP_TO_EDGE = 0x812F,
	GL_TEXTURE_MIN_LOD    = 0x813A,
	GL_TEXTURE_MAX_LOD    = 0x813B,
	GL_TEXTURE_BASE_LEVEL = 0x813C,
	GL_TEXTURE_MAX_LEVEL  = 0x813D,
	GL_SMOOTH_POINT_SIZE_RANGE       = 0x0B12,
	GL_SMOOTH_POINT_SIZE_GRANULARITY = 0x0B13,
	GL_SMOOTH_LINE_WIDTH_RANGE       = 0x0B22,
	GL_SMOOTH_LINE_WIDTH_GRANULARITY = 0x0B23,
	GL_ALIASED_LINE_WIDTH_RANGE = 0x846E,
# ifndef GL_VERSION_1_1
	GL_COLOR_LOGIC_OP = 0x0BF2,
	GL_POLYGON_OFFSET_UNITS = 0x2A00,
	GL_POLYGON_OFFSET_POINT = 0x2A01,
	GL_POLYGON_OFFSET_LINE  = 0x2A02,
	GL_POLYGON_OFFSET_FILL   = 0x8037,
	GL_POLYGON_OFFSET_FACTOR = 0x8038,
	GL_TEXTURE_BINDING_1D = 0x8068,
	GL_TEXTURE_BINDING_2D = 0x8069,
	GL_TEXTURE_INTERNAL_FORMAT = 0x1003,
	GL_TEXTURE_RED_SIZE   = 0x805C,
	GL_TEXTURE_GREEN_SIZE = 0x805D,
	GL_TEXTURE_BLUE_SIZE  = 0x805E,
	GL_TEXTURE_ALPHA_SIZE = 0x805F,
	GL_DOUBLE = 0x140A,
	GL_PROXY_TEXTURE_1D = 0x8063,
	GL_PROXY_TEXTURE_2D = 0x8064,
	GL_R3_G3_B2 = 0x2A10,
	GL_RGB4 = 0x804F,
	GL_RGB5     = 0x8050,
	GL_RGB8     = 0x8051,
	GL_RGB10    = 0x8052,
	GL_RGB12    = 0x8053,
	GL_RGB16    = 0x8054,
	GL_RGBA2    = 0x8055,
	GL_RGBA4    = 0x8056,
	GL_RGB5_A1  = 0x8057,
	GL_RGBA8    = 0x8058,
	GL_RGB10_A2 = 0x8059,
	GL_RGBA12   = 0x805A,
	GL_RGBA16   = 0x805B,
	GL_VERTEX_ARRAY = 0x8074,
# ifndef GL_VERSION_1_0
	GL_POINTS         = 0x0000,
	GL_LINES          = 0x0001,
	GL_LINE_LOOP      = 0x0002,
	GL_LINE_STRIP     = 0x0003,
	GL_TRIANGLES      = 0x0004,
	GL_TRIANGLE_STRIP = 0x0005,
	GL_TRIANGLE_FAN   = 0x0006,
	GL_QUADS          = 0x0007,
	GL_NEVER    = 0x0200,
	GL_LESS     = 0x0201,
	GL_EQUAL    = 0x0202,
	GL_LEQUAL   = 0x0203,
	GL_GREATER  = 0x0204,
	GL_NOTEQUAL = 0x0205,
	GL_GEQUAL   = 0x0206,
	GL_ALWAYS   = 0x0207,
	GL_ZERO = 0,
	GL_ONE = 1,
	GL_SRC_COLOR           = 0x0300,
	GL_ONE_MINUS_SRC_COLOR = 0x0301,
	GL_SRC_ALPHA           = 0x0302,
	GL_ONE_MINUS_SRC_ALPHA = 0x0303,
	GL_DST_ALPHA           = 0x0304,
	GL_ONE_MINUS_DST_ALPHA = 0x0305,
	GL_DST_COLOR           = 0x0306,
	GL_ONE_MINUS_DST_COLOR = 0x0307,
	GL_SRC_ALPHA_SATURATE  = 0x0308,
	GL_NONE = 0,
	GL_FRONT_LEFT     = 0x0400,
	GL_FRONT_RIGHT    = 0x0401,
	GL_BACK_LEFT      = 0x0402,
	GL_BACK_RIGHT     = 0x0403,
	GL_FRONT          = 0x0404,
	GL_BACK           = 0x0405,
	GL_LEFT           = 0x0406,
	GL_RIGHT          = 0x0407,
	GL_FRONT_AND_BACK = 0x0408,
	GL_NO_ERROR = 0,
	GL_INVALID_ENUM      = 0x0500,
	GL_INVALID_VALUE     = 0x0501,
	GL_INVALID_OPERATION = 0x0502,
	GL_OUT_OF_MEMORY     = 0x0505,
	GL_CW  = 0x0900,
	GL_CCW = 0x0901,
	GL_POINT_SIZE             = 0x0B11,
	GL_POINT_SIZE_RANGE       = 0x0B12,
	GL_POINT_SIZE_GRANULARITY = 0x0B13,
	GL_LINE_SMOOTH            = 0x0B20,
	GL_LINE_WIDTH             = 0x0B21,
	GL_LINE_WIDTH_RANGE       = 0x0B22,
	GL_LINE_WIDTH_GRANULARITY = 0x0B23,
	GL_POLYGON_MODE   = 0x0B40,
	GL_POLYGON_SMOOTH = 0x0B41,
	GL_CULL_FACE      = 0x0B44,
	GL_CULL_FACE_MODE = 0x0B45,
	GL_FRONT_FACE     = 0x0B46,
	GL_DEPTH_RANGE       = 0x0B70,
	GL_DEPTH_TEST        = 0x0B71,
	GL_DEPTH_WRITEMASK   = 0x0B72,
	GL_DEPTH_CLEAR_VALUE = 0x0B73,
	GL_DEPTH_FUNC        = 0x0B74,
	GL_STENCIL_TEST            = 0x0B90,
	GL_STENCIL_CLEAR_VALUE     = 0x0B91,
	GL_STENCIL_FUNC            = 0x0B92,
	GL_STENCIL_VALUE_MASK      = 0x0B93,
	GL_STENCIL_FAIL            = 0x0B94,
	GL_STENCIL_PASS_DEPTH_FAIL = 0x0B95,
	GL_STENCIL_PASS_DEPTH_PASS = 0x0B96,
	GL_STENCIL_REF             = 0x0B97,
	GL_STENCIL_WRITEMASK       = 0x0B98,
	GL_VIEWPORT = 0x0BA2,
	GL_DITHER = 0x0BD0,
	GL_BLEND_DST = 0x0BE0,
	GL_BLEND_SRC = 0x0BE1,
	GL_BLEND     = 0x0BE2,
	GL_LOGIC_OP_MODE = 0x0BF0,
	GL_DRAW_BUFFER = 0x0C01,
	GL_READ_BUFFER = 0x0C02,
	GL_SCISSOR_BOX  = 0x0C10,
	GL_SCISSOR_TEST = 0x0C11,
	GL_COLOR_CLEAR_VALUE = 0x0C22,
	GL_COLOR_WRITEMASK   = 0x0C23,
	GL_DOUBLEBUFFER = 0x0C32,
	GL_STEREO       = 0x0C33,
	GL_LINE_SMOOTH_HINT    = 0x0C52,
	GL_POLYGON_SMOOTH_HINT = 0x0C53,
	GL_UNPACK_SWAP_BYTES  = 0x0CF0,
	GL_UNPACK_LSB_FIRST   = 0x0CF1,
	GL_UNPACK_ROW_LENGTH  = 0x0CF2,
	GL_UNPACK_SKIP_ROWS   = 0x0CF3,
	GL_UNPACK_SKIP_PIXELS = 0x0CF4,
	GL_UNPACK_ALIGNMENT   = 0x0CF5,
	GL_PACK_SWAP_BYTES  = 0x0D00,
	GL_PACK_LSB_FIRST   = 0x0D01,
	GL_PACK_ROW_LENGTH  = 0x0D02,
	GL_PACK_SKIP_ROWS   = 0x0D03,
	GL_PACK_SKIP_PIXELS = 0x0D04,
	GL_PACK_ALIGNMENT   = 0x0D05,
	GL_MAX_TEXTURE_SIZE = 0x0D33,
	GL_MAX_VIEWPORT_DIMS = 0x0D3A,
	GL_SUBPIXEL_BITS = 0x0D50,
	GL_TEXTURE_1D = 0x0DE0,
	GL_TEXTURE_2D = 0x0DE1,
	GL_TEXTURE_WIDTH  = 0x1000,
	GL_TEXTURE_HEIGHT = 0x1001,
	GL_TEXTURE_BORDER_COLOR = 0x1004,
	GL_DONT_CARE = 0x1100,
	GL_FASTEST   = 0x1101,
	GL_NICEST    = 0x1102,
	GL_BYTE           = 0x1400,
	GL_UNSIGNED_BYTE  = 0x1401,
	GL_SHORT          = 0x1402,
	GL_UNSIGNED_SHORT = 0x1403,
	GL_INT            = 0x1404,
	GL_UNSIGNED_INT   = 0x1405,
	GL_FLOAT          = 0x1406,
	GL_STACK_OVERFLOW  = 0x0503,
	GL_STACK_UNDERFLOW = 0x0504,
	GL_CLEAR         = 0x1500,
	GL_AND           = 0x1501,
	GL_AND_REVERSE   = 0x1502,
	GL_COPY          = 0x1503,
	GL_AND_INVERTED  = 0x1504,
	GL_NOOP          = 0x1505,
	GL_XOR           = 0x1506,
	GL_OR            = 0x1507,
	GL_NOR           = 0x1508,
	GL_EQUIV         = 0x1509,
	GL_INVERT        = 0x150A,
	GL_OR_REVERSE    = 0x150B,
	GL_COPY_INVERTED = 0x150C,
	GL_OR_INVERTED   = 0x150D,
	GL_NAND          = 0x150E,
	GL_SET           = 0x150F,
	GL_TEXTURE = 0x1702,
	GL_COLOR   = 0x1800,
	GL_DEPTH   = 0x1801,
	GL_STENCIL = 0x1802,
	GL_STENCIL_INDEX   = 0x1901,
	GL_DEPTH_COMPONENT = 0x1902,
	GL_RED             = 0x1903,
	GL_GREEN           = 0x1904,
	GL_BLUE            = 0x1905,
	GL_ALPHA           = 0x1906,
	GL_RGB             = 0x1907,
	GL_RGBA            = 0x1908,
	GL_POINT = 0x1B00,
	GL_LINE  = 0x1B01,
	GL_FILL  = 0x1B02,
	GL_KEEP    = 0x1E00,
	GL_REPLACE = 0x1E01,
	GL_INCR    = 0x1E02,
	GL_DECR    = 0x1E03,
	GL_VENDOR     = 0x1F00,
	GL_RENDERER   = 0x1F01,
	GL_VERSION    = 0x1F02,
	GL_EXTENSIONS = 0x1F03,
	GL_NEAREST = 0x2600,
	GL_LINEAR  = 0x2601,
	GL_NEAREST_MIPMAP_NEAREST = 0x2700,
	GL_LINEAR_MIPMAP_NEAREST  = 0x2701,
	GL_NEAREST_MIPMAP_LINEAR  = 0x2702,
	GL_LINEAR_MIPMAP_LINEAR   = 0x2703,
	GL_TEXTURE_MAG_FILTER = 0x2800,
	GL_TEXTURE_MIN_FILTER = 0x2801,
	GL_TEXTURE_WRAP_S     = 0x2802,
	GL_TEXTURE_WRAP_T     = 0x2803,
	GL_REPEAT = 0x2901,
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
# endif
};
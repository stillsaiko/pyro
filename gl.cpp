# include "gl.h"

# ifndef NDEBUG
# include "error.h"
const char *gl_Error = nullptr;
# endif

GLubyte gl_Version = 000;

GLenum glGetLastError(void)
{
	GLenum glGetError;
	GLenum
	GLenum = GL_NO_ERROR;
# ifndef NDEBUG
	constexpr const char *c_str[8]
	{
		"GL_INVALID_ENUM",
		"GL_INVALID_VALUE",
		"GL_INVALID_OPERATION",
		"GL_STACK_OVERFLOW",
		"GL_STACK_UNDERFLOW",
		"GL_OUT_OF_MEMORY"
	};
	gl_Error = nullptr;
	if(ASSERT(wglGetCurrentContext( )))
# endif
	while(glGetError = ::glGetError( ))
	{
# ifndef NDEBUG
		if(GLenum) ERROR(c_str[GLenum & 0x0007]);
		gl_Error = c_str[glGetError & 0x0007];
# endif
		if(ASSERT((glGetError & 0xFFF8) == 0x0500))
		  GLenum = glGetError;
	}
	return GLenum;
}

/*
# undef GL_ERROR
// extern
void GL_ERROR(const char *FILE, int LINE, const char *FUNCTION, const char *ARGS)
{
	GLenum error;
	const char *c_str = nullptr;
	while(error = glGetError( ))
	{
		if(c_str) ERROR(c_str);
		ASSERT((error & 0xFFF8) == 0x0500);
		ASSERT(c_str = GL_ERROR[error & 0x0007]);
	}
# undef ERROR
	ERROR(FILE, LINE, ARGS, c_str);
*/	
/*	switch(glGetError( ))
	{
		case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
		case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
		case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
		case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
		case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
		case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
		case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
		default: return nullptr;
	}
}*/



// function

# ifndef GL_VERSION_4_6
void (__stdcall*glSpecializeShader)(GLuint, const GLchar *, GLuint, const GLuint *, const GLuint *) = nullptr;
void (__stdcall*glMultiDrawArraysIndirectCount)(GLenum, const void *, GLintptr, GLsizei, GLsizei) = nullptr;
void (__stdcall*glMultiDrawElementsIndirectCount)(GLenum, GLenum, const void *, GLintptr, GLsizei, GLsizei) = nullptr;
void (__stdcall*glPolygonOffsetClamp)(GLfloat, GLfloat, GLfloat) = nullptr;
# ifndef GL_VERSION_4_5
void (__stdcall*glClipControl)(GLenum, GLenum) = nullptr;
void (__stdcall*glCreateTransformFeedbacks)(GLsizei, GLuint *) = nullptr;
void (__stdcall*glTransformFeedbackBufferBase)(GLuint, GLuint, GLuint) = nullptr;
void (__stdcall*glTransformFeedbackBufferRange)(GLuint, GLuint, GLuint, GLintptr, GLsizeiptr) = nullptr;
void (__stdcall*glGetTransformFeedbackiv)(GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetTransformFeedbacki_v)(GLuint, GLenum, GLuint, GLint *) = nullptr;
void (__stdcall*glGetTransformFeedbacki64_v)(GLuint, GLenum, GLuint, GLint64 *) = nullptr;
void (__stdcall*glCreateBuffers)(GLsizei, GLuint *) = nullptr;
void (__stdcall*glNamedBufferStorage)(GLuint, GLsizeiptr, const void *, GLbitfield) = nullptr;
void (__stdcall*glNamedBufferData)(GLuint, GLsizeiptr, const void *, GLenum) = nullptr;
void (__stdcall*glNamedBufferSubData)(GLuint, GLintptr, GLsizeiptr, const void *) = nullptr;
void (__stdcall*glCopyNamedBufferSubData)(GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr) = nullptr;
void (__stdcall*glClearNamedBufferData)(GLuint, GLenum, GLenum, GLenum, const void *) = nullptr;
void (__stdcall*glClearNamedBufferSubData)(GLuint, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *) = nullptr;
void *(__stdcall*glMapNamedBuffer)(GLuint, GLenum) = nullptr;
void *(__stdcall*glMapNamedBufferRange)(GLuint, GLintptr, GLsizeiptr, GLbitfield) = nullptr;
GLboolean (__stdcall*glUnmapNamedBuffer)(GLuint) = nullptr;
void (__stdcall*glFlushMappedNamedBufferRange)(GLuint, GLintptr, GLsizeiptr) = nullptr;
void (__stdcall*glGetNamedBufferParameteriv)(GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetNamedBufferParameteri64v)(GLuint, GLenum, GLint64 *) = nullptr;
void (__stdcall*glGetNamedBufferPointerv)(GLuint, GLenum, void **) = nullptr;
void (__stdcall*glGetNamedBufferSubData)(GLuint, GLintptr, GLsizeiptr, void *) = nullptr;
void (__stdcall*glCreateFramebuffers)(GLsizei, GLuint *) = nullptr;
void (__stdcall*glNamedFramebufferRenderbuffer)(GLuint, GLenum, GLenum, GLuint) = nullptr;
void (__stdcall*glNamedFramebufferParameteri)(GLuint, GLenum, GLint) = nullptr;
void (__stdcall*glNamedFramebufferTexture)(GLuint, GLenum, GLuint, GLint) = nullptr;
void (__stdcall*glNamedFramebufferTextureLayer)(GLuint, GLenum, GLuint, GLint, GLint) = nullptr;
void (__stdcall*glNamedFramebufferDrawBuffer)(GLuint, GLenum) = nullptr;
void (__stdcall*glNamedFramebufferDrawBuffers)(GLuint, GLsizei, const GLenum *) = nullptr;
void (__stdcall*glNamedFramebufferReadBuffer)(GLuint, GLenum) = nullptr;
void (__stdcall*glInvalidateNamedFramebufferData)(GLuint, GLsizei, const GLenum *) = nullptr;
void (__stdcall*glInvalidateNamedFramebufferSubData)(GLuint, GLsizei, const GLenum *, GLint x, GLint y, GLsizei, GLsizei) = nullptr;
void (__stdcall*glClearNamedFramebufferiv)(GLuint, GLenum, GLint, const GLint *) = nullptr;
void (__stdcall*glClearNamedFramebufferuiv)(GLuint, GLenum, GLint, const GLuint *) = nullptr;
void (__stdcall*glClearNamedFramebufferfv)(GLuint, GLenum, GLint, const GLfloat *) = nullptr;
void (__stdcall*glClearNamedFramebufferfi)(GLuint, GLenum, GLint, GLfloat, GLint) = nullptr;
void (__stdcall*glBlitNamedFramebuffer)(GLuint, GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum) = nullptr;
GLenum (__stdcall*glCheckNamedFramebufferStatus)(GLuint, GLenum) = nullptr;
void (__stdcall*glGetNamedFramebufferParameteriv)(GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetNamedFramebufferAttachmentParameteriv)(GLuint, GLenum, GLenum, GLint *) = nullptr;
void (__stdcall*glCreateRenderbuffers)(GLsizei, GLuint *) = nullptr;
void (__stdcall*glNamedRenderbufferStorage)(GLuint, GLenum, GLsizei, GLsizei) = nullptr;
void (__stdcall*glNamedRenderbufferStorageMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei) = nullptr;
void (__stdcall*glGetNamedRenderbufferParameteriv)(GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glCreateTextures)(GLenum, GLsizei, GLuint *) = nullptr;
void (__stdcall*glTextureBuffer)(GLuint, GLenum, GLuint) = nullptr;
void (__stdcall*glTextureBufferRange)(GLuint, GLenum, GLuint, GLintptr, GLsizeiptr) = nullptr;
void (__stdcall*glTextureStorage1D)(GLuint, GLsizei, GLenum, GLsizei) = nullptr;
void (__stdcall*glTextureStorage2D)(GLuint, GLsizei, GLenum, GLsizei, GLsizei) = nullptr;
void (__stdcall*glTextureStorage3D)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei) = nullptr;
void (__stdcall*glTextureStorage2DMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLboolean) = nullptr;
void (__stdcall*glTextureStorage3DMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean) = nullptr;
void (__stdcall*glTextureSubImage1D)(GLuint, GLint, GLint, GLsizei, GLenum, GLenum, const void *) = nullptr;
void (__stdcall*glTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *) = nullptr;
void (__stdcall*glTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) = nullptr;
void (__stdcall*glCompressedTextureSubImage1D)(GLuint, GLint, GLint, GLsizei, GLenum, GLsizei, const void *) = nullptr;
void (__stdcall*glCompressedTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *) = nullptr;
void (__stdcall*glCompressedTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *) = nullptr;
void (__stdcall*glCopyTextureSubImage1D)(GLuint, GLint, GLint, GLint x, GLint y, GLsizei) = nullptr;
void (__stdcall*glCopyTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLint x, GLint y, GLsizei, GLsizei) = nullptr;
void (__stdcall*glCopyTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLint x, GLint y, GLsizei, GLsizei) = nullptr;
void (__stdcall*glTextureParameterf)(GLuint, GLenum, GLfloat) = nullptr;
void (__stdcall*glTextureParameterfv)(GLuint, GLenum, const GLfloat *) = nullptr;
void (__stdcall*glTextureParameteri)(GLuint, GLenum, GLint) = nullptr;
void (__stdcall*glTextureParameterIiv)(GLuint, GLenum, const GLint *) = nullptr;
void (__stdcall*glTextureParameterIuiv)(GLuint, GLenum, const GLuint *) = nullptr;
void (__stdcall*glTextureParameteriv)(GLuint, GLenum, const GLint *) = nullptr;
void (__stdcall*glGenerateTextureMipmap)(GLuint) = nullptr;
void (__stdcall*glBindTextureUnit)(GLuint, GLuint) = nullptr;
void (__stdcall*glGetTextureImage)(GLuint, GLint, GLenum, GLenum, GLsizei, void *) = nullptr;
void (__stdcall*glGetCompressedTextureImage)(GLuint, GLint, GLsizei, void *) = nullptr;
void (__stdcall*glGetTextureLevelParameterfv)(GLuint, GLint, GLenum, GLfloat *) = nullptr;
void (__stdcall*glGetTextureLevelParameteriv)(GLuint, GLint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetTextureParameterfv)(GLuint, GLenum, GLfloat *) = nullptr;
void (__stdcall*glGetTextureParameterIiv)(GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetTextureParameterIuiv)(GLuint, GLenum, GLuint *) = nullptr;
void (__stdcall*glGetTextureParameteriv)(GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glCreateVertexArrays)(GLsizei, GLuint *) = nullptr;
void (__stdcall*glDisableVertexArrayAttrib)(GLuint, GLuint) = nullptr;
void (__stdcall*glEnableVertexArrayAttrib)(GLuint, GLuint) = nullptr;
void (__stdcall*glVertexArrayElementBuffer)(GLuint, GLuint) = nullptr;
void (__stdcall*glVertexArrayVertexBuffer)(GLuint, GLuint, GLuint, GLintptr, GLsizei) = nullptr;
void (__stdcall*glVertexArrayVertexBuffers)(GLuint, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *) = nullptr;
void (__stdcall*glVertexArrayAttribBinding)(GLuint, GLuint, GLuint) = nullptr;
void (__stdcall*glVertexArrayAttribFormat)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint ) = nullptr;
void (__stdcall*glVertexArrayAttribIFormat)(GLuint, GLuint, GLint, GLenum, GLuint ) = nullptr;
void (__stdcall*glVertexArrayAttribLFormat)(GLuint, GLuint, GLint, GLenum, GLuint ) = nullptr;
void (__stdcall*glVertexArrayBindingDivisor)(GLuint, GLuint, GLuint) = nullptr;
void (__stdcall*glGetVertexArrayiv)(GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetVertexArrayIndexediv)(GLuint, GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetVertexArrayIndexed64iv)(GLuint, GLuint, GLenum, GLint64 *) = nullptr;
void (__stdcall*glCreateSamplers)(GLsizei, GLuint *) = nullptr;
void (__stdcall*glCreateProgramPipelines)(GLsizei, GLuint *) = nullptr;
void (__stdcall*glCreateQueries)(GLenum, GLsizei, GLuint *) = nullptr;
void (__stdcall*glGetQueryBufferObjecti64v)(GLuint, GLuint, GLenum, GLintptr) = nullptr;
void (__stdcall*glGetQueryBufferObjectiv)(GLuint, GLuint, GLenum, GLintptr) = nullptr;
void (__stdcall*glGetQueryBufferObjectui64v)(GLuint, GLuint, GLenum, GLintptr) = nullptr;
void (__stdcall*glGetQueryBufferObjectuiv)(GLuint, GLuint, GLenum, GLintptr) = nullptr;
void (__stdcall*glMemoryBarrierByRegion)(GLbitfield) = nullptr;
void (__stdcall*glGetTextureSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *) = nullptr;
void (__stdcall*glGetCompressedTextureSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLsizei, void *) = nullptr;
GLenum (__stdcall*glGetGraphicsResetStatus)(void) = nullptr;
void (__stdcall*glGetnCompressedTexImage)(GLenum, GLint, GLsizei, void *) = nullptr;
void (__stdcall*glGetnTexImage)(GLenum, GLint, GLenum, GLenum, GLsizei, void *) = nullptr;
void (__stdcall*glGetnUniformdv)(GLuint, GLint, GLsizei, GLdouble *) = nullptr;
void (__stdcall*glGetnUniformfv)(GLuint, GLint, GLsizei, GLfloat *) = nullptr;
void (__stdcall*glGetnUniformiv)(GLuint, GLint, GLsizei, GLint *) = nullptr;
void (__stdcall*glGetnUniformuiv)(GLuint, GLint, GLsizei, GLuint *) = nullptr;
void (__stdcall*glReadnPixels)(GLint x, GLint y, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *) = nullptr;
void (__stdcall*glTextureBarrier)(void) = nullptr;
# ifndef GL_VERSION_4_4
void (__stdcall*glBufferStorage)(GLenum, GLsizeiptr, const void *, GLbitfield) = nullptr;
void (__stdcall*glClearTexImage)(GLuint, GLint, GLenum, GLenum, const void *) = nullptr;
void (__stdcall*glClearTexSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) = nullptr;
void (__stdcall*glBindBuffersBase)(GLenum, GLuint, GLsizei, const GLuint *) = nullptr;
void (__stdcall*glBindBuffersRange)(GLenum, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizeiptr *) = nullptr;
void (__stdcall*glBindTextures)(GLuint, GLsizei, const GLuint *) = nullptr;
void (__stdcall*glBindSamplers)(GLuint, GLsizei, const GLuint *) = nullptr;
void (__stdcall*glBindImageTextures)(GLuint, GLsizei, const GLuint *) = nullptr;
void (__stdcall*glBindVertexBuffers)(GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *) = nullptr;
# ifndef GL_VERSION_4_3
void (__stdcall*glClearBufferData)(GLenum, GLenum, GLenum, GLenum, const void *) = nullptr;
void (__stdcall*glClearBufferSubData)(GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *) = nullptr;
void (__stdcall*glDispatchCompute)(GLuint, GLuint, GLuint) = nullptr;
void (__stdcall*glDispatchComputeIndirect)(GLintptr) = nullptr;
void (__stdcall*glCopyImageSubData)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei) = nullptr;
void (__stdcall*glFramebufferParameteri)(GLenum, GLenum, GLint) = nullptr;
void (__stdcall*glGetFramebufferParameteriv)(GLenum, GLenum, GLint *) = nullptr;
void (__stdcall*glGetInternalformati64v)(GLenum, GLenum, GLenum, GLsizei, GLint64 *) = nullptr;
void (__stdcall*glInvalidateTexSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei) = nullptr;
void (__stdcall*glInvalidateTexImage)(GLuint, GLint) = nullptr;
void (__stdcall*glInvalidateBufferSubData)(GLuint, GLintptr, GLsizeiptr) = nullptr;
void (__stdcall*glInvalidateBufferData)(GLuint) = nullptr;
void (__stdcall*glInvalidateFramebuffer)(GLenum, GLsizei, const GLenum *) = nullptr;
void (__stdcall*glInvalidateSubFramebuffer)(GLenum, GLsizei, const GLenum *, GLint x, GLint y, GLsizei, GLsizei) = nullptr;
void (__stdcall*glMultiDrawArraysIndirect)(GLenum, const void *, GLsizei, GLsizei) = nullptr;
void (__stdcall*glMultiDrawElementsIndirect)(GLenum, GLenum, const void *, GLsizei, GLsizei) = nullptr;
void (__stdcall*glGetProgramInterfaceiv)(GLuint, GLenum, GLenum, GLint *) = nullptr;
GLuint (__stdcall*glGetProgramResourceIndex)(GLuint, GLenum, const GLchar *) = nullptr;
void (__stdcall*glGetProgramResourceName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
void (__stdcall*glGetProgramResourceiv)(GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLint *) = nullptr;
GLint (__stdcall*glGetProgramResourceLocation)(GLuint, GLenum, const GLchar *) = nullptr;
GLint (__stdcall*glGetProgramResourceLocationIndex)(GLuint, GLenum, const GLchar *) = nullptr;
void (__stdcall*glShaderStorageBlockBinding)(GLuint, GLuint, GLuint) = nullptr;
void (__stdcall*glTexBufferRange)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr) = nullptr;
void (__stdcall*glTexStorage2DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean) = nullptr;
void (__stdcall*glTexStorage3DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean) = nullptr;
void (__stdcall*glTextureView)(GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint) = nullptr;
void (__stdcall*glBindVertexBuffer)(GLuint, GLuint, GLintptr, GLsizei) = nullptr;
void (__stdcall*glVertexAttribFormat)(GLuint, GLint, GLenum, GLboolean, GLuint ) = nullptr;
void (__stdcall*glVertexAttribIFormat)(GLuint, GLint, GLenum, GLuint ) = nullptr;
void (__stdcall*glVertexAttribLFormat)(GLuint, GLint, GLenum, GLuint ) = nullptr;
void (__stdcall*glVertexAttribBinding)(GLuint, GLuint) = nullptr;
void (__stdcall*glVertexBindingDivisor)(GLuint, GLuint) = nullptr;
void (__stdcall*glDebugMessageControl)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean) = nullptr;
void (__stdcall*glDebugMessageInsert)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *) = nullptr;
void (__stdcall*glDebugMessageCallback)(void (__stdcall*)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *, const void *), const void *) = nullptr;
GLuint (__stdcall*glGetDebugMessageLog)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *) = nullptr;
void (__stdcall*glPushDebugGroup)(GLenum, GLuint, GLsizei, const GLchar *) = nullptr;
void (__stdcall*glPopDebugGroup)(void) = nullptr;
void (__stdcall*glObjectLabel)(GLenum, GLuint, GLsizei, const GLchar *) = nullptr;
void (__stdcall*glGetObjectLabel)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
void (__stdcall*glObjectPtrLabel)(const void *, GLsizei, const GLchar *) = nullptr;
void (__stdcall*glGetObjectPtrLabel)(const void *, GLsizei, GLsizei *, GLchar *) = nullptr;
# ifndef GL_VERSION_4_2
void (__stdcall*glDrawArraysInstancedBaseInstance)(GLenum, GLint, GLsizei, GLsizei, GLuint) = nullptr;
void (__stdcall*glDrawElementsInstancedBaseInstance)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLuint) = nullptr;
void (__stdcall*glDrawElementsInstancedBaseVertexBaseInstance)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint, GLuint) = nullptr;
void (__stdcall*glGetInternalformativ)(GLenum, GLenum, GLenum, GLsizei, GLint *) = nullptr;
void (__stdcall*glGetActiveAtomicCounterBufferiv)(GLuint, GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glBindImageTexture)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum) = nullptr;
void (__stdcall*glMemoryBarrier)(GLbitfield) = nullptr;
void (__stdcall*glTexStorage1D)(GLenum, GLsizei, GLenum, GLsizei) = nullptr;
void (__stdcall*glTexStorage2D)(GLenum, GLsizei, GLenum, GLsizei, GLsizei) = nullptr;
void (__stdcall*glTexStorage3D)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei) = nullptr;
void (__stdcall*glDrawTransformFeedbackInstanced)(GLenum, GLuint, GLsizei) = nullptr;
void (__stdcall*glDrawTransformFeedbackStreamInstanced)(GLenum, GLuint, GLuint, GLsizei) = nullptr;
# ifndef GL_VERSION_4_1
void (__stdcall*glReleaseShaderCompiler)(void) = nullptr;
void (__stdcall*glShaderBinary)(GLsizei, const GLuint *, GLenum, const void *, GLsizei) = nullptr;
void (__stdcall*glGetShaderPrecisionFormat)(GLenum, GLenum, GLint *, GLint *) = nullptr;
void (__stdcall*glDepthRangef)(GLfloat, GLfloat) = nullptr;
void (__stdcall*glClearDepthf)(GLfloat) = nullptr;
void (__stdcall*glGetProgramBinary)(GLuint, GLsizei, GLsizei *, GLenum *, void *) = nullptr;
void (__stdcall*glProgramBinary)(GLuint, GLenum, const void *, GLsizei) = nullptr;
void (__stdcall*glProgramParameteri)(GLuint, GLenum, GLint) = nullptr;
void (__stdcall*glUseProgramStages)(GLuint, GLbitfield, GLuint) = nullptr;
void (__stdcall*glActiveShaderProgram)(GLuint, GLuint) = nullptr;
GLuint (__stdcall*glCreateShaderProgramv)(GLenum, GLsizei, const GLchar *const*) = nullptr;
void (__stdcall*glBindProgramPipeline)(GLuint) = nullptr;
void (__stdcall*glDeleteProgramPipelines)(GLsizei, const GLuint *) = nullptr;
void (__stdcall*glGenProgramPipelines)(GLsizei, GLuint *) = nullptr;
GLboolean (__stdcall*glIsProgramPipeline)(GLuint) = nullptr;
void (__stdcall*glGetProgramPipelineiv)(GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glProgramUniform1i)(GLuint, GLint, GLint) = nullptr;
void (__stdcall*glProgramUniform1iv)(GLuint, GLint, GLsizei, const GLint *) = nullptr;
void (__stdcall*glProgramUniform1f)(GLuint, GLint, GLfloat) = nullptr;
void (__stdcall*glProgramUniform1fv)(GLuint, GLint, GLsizei, const GLfloat *) = nullptr;
void (__stdcall*glProgramUniform1d)(GLuint, GLint, GLdouble) = nullptr;
void (__stdcall*glProgramUniform1dv)(GLuint, GLint, GLsizei, const GLdouble *) = nullptr;
void (__stdcall*glProgramUniform1ui)(GLuint, GLint, GLuint) = nullptr;
void (__stdcall*glProgramUniform1uiv)(GLuint, GLint, GLsizei, const GLuint *) = nullptr;
void (__stdcall*glProgramUniform2i)(GLuint, GLint, GLint, GLint) = nullptr;
void (__stdcall*glProgramUniform2iv)(GLuint, GLint, GLsizei, const GLint *) = nullptr;
void (__stdcall*glProgramUniform2f)(GLuint, GLint, GLfloat, GLfloat) = nullptr;
void (__stdcall*glProgramUniform2fv)(GLuint, GLint, GLsizei, const GLfloat *) = nullptr;
void (__stdcall*glProgramUniform2d)(GLuint, GLint, GLdouble, GLdouble) = nullptr;
void (__stdcall*glProgramUniform2dv)(GLuint, GLint, GLsizei, const GLdouble *) = nullptr;
void (__stdcall*glProgramUniform2ui)(GLuint, GLint, GLuint, GLuint) = nullptr;
void (__stdcall*glProgramUniform2uiv)(GLuint, GLint, GLsizei, const GLuint *) = nullptr;
void (__stdcall*glProgramUniform3i)(GLuint, GLint, GLint, GLint, GLint) = nullptr;
void (__stdcall*glProgramUniform3iv)(GLuint, GLint, GLsizei, const GLint *) = nullptr;
void (__stdcall*glProgramUniform3f)(GLuint, GLint, GLfloat, GLfloat, GLfloat) = nullptr;
void (__stdcall*glProgramUniform3fv)(GLuint, GLint, GLsizei, const GLfloat *) = nullptr;
void (__stdcall*glProgramUniform3d)(GLuint, GLint, GLdouble, GLdouble, GLdouble) = nullptr;
void (__stdcall*glProgramUniform3dv)(GLuint, GLint, GLsizei, const GLdouble *) = nullptr;
void (__stdcall*glProgramUniform3ui)(GLuint, GLint, GLuint, GLuint, GLuint) = nullptr;
void (__stdcall*glProgramUniform3uiv)(GLuint, GLint, GLsizei, const GLuint *) = nullptr;
void (__stdcall*glProgramUniform4i)(GLuint, GLint, GLint, GLint, GLint, GLint) = nullptr;
void (__stdcall*glProgramUniform4iv)(GLuint, GLint, GLsizei, const GLint *) = nullptr;
void (__stdcall*glProgramUniform4f)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat) = nullptr;
void (__stdcall*glProgramUniform4fv)(GLuint, GLint, GLsizei, const GLfloat *) = nullptr;
void (__stdcall*glProgramUniform4d)(GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble) = nullptr;
void (__stdcall*glProgramUniform4dv)(GLuint, GLint, GLsizei, const GLdouble *) = nullptr;
void (__stdcall*glProgramUniform4ui)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint) = nullptr;
void (__stdcall*glProgramUniform4uiv)(GLuint, GLint, GLsizei, const GLuint *) = nullptr;
void (__stdcall*glProgramUniformMatrix2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glProgramUniformMatrix3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glProgramUniformMatrix4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glProgramUniformMatrix2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glProgramUniformMatrix3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glProgramUniformMatrix4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glProgramUniformMatrix2x3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glProgramUniformMatrix3x2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glProgramUniformMatrix2x4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glProgramUniformMatrix4x2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glProgramUniformMatrix3x4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glProgramUniformMatrix4x3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glProgramUniformMatrix2x3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glProgramUniformMatrix3x2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glProgramUniformMatrix2x4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glProgramUniformMatrix4x2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glProgramUniformMatrix3x4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glProgramUniformMatrix4x3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glValidateProgramPipeline)(GLuint pipeline) = nullptr;
void (__stdcall*glGetProgramPipelineInfoLog)(GLuint pipeline, GLsizei bufSize, GLsizei *, GLchar *infoLog) = nullptr;
void (__stdcall*glVertexAttribL1d)(GLuint, GLdouble x) = nullptr;
void (__stdcall*glVertexAttribL2d)(GLuint, GLdouble x, GLdouble y) = nullptr;
void (__stdcall*glVertexAttribL3d)(GLuint, GLdouble x, GLdouble y, GLdouble z) = nullptr;
void (__stdcall*glVertexAttribL4d)(GLuint, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
void (__stdcall*glVertexAttribL1dv)(GLuint, const GLdouble *v) = nullptr;
void (__stdcall*glVertexAttribL2dv)(GLuint, const GLdouble *v) = nullptr;
void (__stdcall*glVertexAttribL3dv)(GLuint, const GLdouble *v) = nullptr;
void (__stdcall*glVertexAttribL4dv)(GLuint, const GLdouble *v) = nullptr;
void (__stdcall*glVertexAttribLPointer)(GLuint, GLint, GLenum, GLsizei, const void *) = nullptr;
void (__stdcall*glGetVertexAttribLdv)(GLuint, GLenum, GLdouble *) = nullptr;
void (__stdcall*glViewportArrayv)(GLuint, GLsizei, const GLfloat *v) = nullptr;
void (__stdcall*glViewportIndexedf)(GLuint, GLfloat x, GLfloat y, GLfloat w, GLfloat h) = nullptr;
void (__stdcall*glViewportIndexedfv)(GLuint, const GLfloat *v) = nullptr;
void (__stdcall*glScissorArrayv)(GLuint, GLsizei, const GLint *v) = nullptr;
void (__stdcall*glScissorIndexed)(GLuint, GLint left, GLint bottom, GLsizei, GLsizei) = nullptr;
void (__stdcall*glScissorIndexedv)(GLuint, const GLint *v) = nullptr;
void (__stdcall*glDepthRangeArrayv)(GLuint, GLsizei, const GLdouble *v) = nullptr;
void (__stdcall*glDepthRangeIndexed)(GLuint, GLdouble, GLdouble f) = nullptr;
void (__stdcall*glGetFloati_v)(GLenum, GLuint, GLfloat *) = nullptr;
void (__stdcall*glGetDoublei_v)(GLenum, GLuint, GLdouble *) = nullptr;
# ifndef GL_VERSION_4_0
void (__stdcall*glMinSampleShading)(GLfloat) = nullptr;
void (__stdcall*glBlendEquationi)(GLuint, GLenum) = nullptr;
void (__stdcall*glBlendEquationSeparatei)(GLuint, GLenum, GLenum) = nullptr;
void (__stdcall*glBlendFunci)(GLuint, GLenum, GLenum) = nullptr;
void (__stdcall*glBlendFuncSeparatei)(GLuint, GLenum, GLenum, GLenum, GLenum) = nullptr;
void (__stdcall*glDrawArraysIndirect)(GLenum, const void *) = nullptr;
void (__stdcall*glDrawElementsIndirect)(GLenum, GLenum, const void *) = nullptr;
void (__stdcall*glUniform1d)(GLint, GLdouble) = nullptr;
void (__stdcall*glUniform2d)(GLint, GLdouble, GLdouble) = nullptr;
void (__stdcall*glUniform3d)(GLint, GLdouble, GLdouble, GLdouble) = nullptr;
void (__stdcall*glUniform4d)(GLint, GLdouble, GLdouble, GLdouble, GLdouble) = nullptr;
void (__stdcall*glUniform1dv)(GLint, GLsizei, const GLdouble *) = nullptr;
void (__stdcall*glUniform2dv)(GLint, GLsizei, const GLdouble *) = nullptr;
void (__stdcall*glUniform3dv)(GLint, GLsizei, const GLdouble *) = nullptr;
void (__stdcall*glUniform4dv)(GLint, GLsizei, const GLdouble *) = nullptr;
void (__stdcall*glUniformMatrix2dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glUniformMatrix3dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glUniformMatrix4dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glUniformMatrix2x3dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glUniformMatrix2x4dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glUniformMatrix3x2dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glUniformMatrix3x4dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glUniformMatrix4x2dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glUniformMatrix4x3dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
void (__stdcall*glGetUniformdv)(GLuint, GLint, GLdouble *) = nullptr;
GLint (__stdcall*glGetSubroutineUniformLocation)(GLuint, GLenum, const GLchar *) = nullptr;
GLuint (__stdcall*glGetSubroutineIndex)(GLuint, GLenum, const GLchar *) = nullptr;
void (__stdcall*glGetActiveSubroutineUniformiv)(GLuint, GLenum, GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetActiveSubroutineUniformName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
void (__stdcall*glGetActiveSubroutineName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
void (__stdcall*glUniformSubroutinesuiv)(GLenum, GLsizei, const GLuint *) = nullptr;
void (__stdcall*glGetUniformSubroutineuiv)(GLenum, GLint, GLuint *) = nullptr;
void (__stdcall*glGetProgramStageiv)(GLuint, GLenum, GLenum, GLint *) = nullptr;
void (__stdcall*glPatchParameteri)(GLenum, GLint) = nullptr;
void (__stdcall*glPatchParameterfv)(GLenum, const GLfloat *) = nullptr;
void (__stdcall*glBindTransformFeedback)(GLenum, GLuint) = nullptr;
void (__stdcall*glDeleteTransformFeedbacks)(GLsizei, const GLuint *) = nullptr;
void (__stdcall*glGenTransformFeedbacks)(GLsizei, GLuint *) = nullptr;
GLboolean (__stdcall*glIsTransformFeedback)(GLuint) = nullptr;
void (__stdcall*glPauseTransformFeedback)(void) = nullptr;
void (__stdcall*glResumeTransformFeedback)(void) = nullptr;
void (__stdcall*glDrawTransformFeedback)(GLenum, GLuint) = nullptr;
void (__stdcall*glDrawTransformFeedbackStream)(GLenum, GLuint, GLuint) = nullptr;
void (__stdcall*glBeginQueryIndexed)(GLenum, GLuint, GLuint) = nullptr;
void (__stdcall*glEndQueryIndexed)(GLenum, GLuint) = nullptr;
void (__stdcall*glGetQueryIndexediv)(GLenum, GLuint, GLenum, GLint *) = nullptr;
# ifndef GL_VERSION_3_3
void (__stdcall*glBindFragDataLocationIndexed)(GLuint, GLuint, GLuint, const GLchar *) = nullptr;
GLint (__stdcall*glGetFragDataIndex)(GLuint, const GLchar *) = nullptr;
void (__stdcall*glGenSamplers)(GLsizei, GLuint *) = nullptr;
void (__stdcall*glDeleteSamplers)(GLsizei, const GLuint *) = nullptr;
GLboolean (__stdcall*glIsSampler)(GLuint) = nullptr;
void (__stdcall*glBindSampler)(GLuint, GLuint) = nullptr;
void (__stdcall*glSamplerParameteri)(GLuint, GLenum, GLint) = nullptr;
void (__stdcall*glSamplerParameteriv)(GLuint, GLenum, const GLint *) = nullptr;
void (__stdcall*glSamplerParameterf)(GLuint, GLenum, GLfloat) = nullptr;
void (__stdcall*glSamplerParameterfv)(GLuint, GLenum, const GLfloat *) = nullptr;
void (__stdcall*glSamplerParameterIiv)(GLuint, GLenum, const GLint *) = nullptr;
void (__stdcall*glSamplerParameterIuiv)(GLuint, GLenum, const GLuint *) = nullptr;
void (__stdcall*glGetSamplerParameteriv)(GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetSamplerParameterIiv)(GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetSamplerParameterfv)(GLuint, GLenum, GLfloat *) = nullptr;
void (__stdcall*glGetSamplerParameterIuiv)(GLuint, GLenum, GLuint *) = nullptr;
void (__stdcall*glQueryCounter)(GLuint, GLenum) = nullptr;
void (__stdcall*glGetQueryObjecti64v)(GLuint, GLenum, GLint64 *) = nullptr;
void (__stdcall*glGetQueryObjectui64v)(GLuint, GLenum, GLuint64 *) = nullptr;
void (__stdcall*glVertexAttribDivisor)(GLuint, GLuint) = nullptr;
void (__stdcall*glVertexAttribP1ui)(GLuint, GLenum, GLboolean, GLuint) = nullptr;
void (__stdcall*glVertexAttribP1uiv)(GLuint, GLenum, GLboolean, const GLuint *) = nullptr;
void (__stdcall*glVertexAttribP2ui)(GLuint, GLenum, GLboolean, GLuint) = nullptr;
void (__stdcall*glVertexAttribP2uiv)(GLuint, GLenum, GLboolean, const GLuint *) = nullptr;
void (__stdcall*glVertexAttribP3ui)(GLuint, GLenum, GLboolean, GLuint) = nullptr;
void (__stdcall*glVertexAttribP3uiv)(GLuint, GLenum, GLboolean, const GLuint *) = nullptr;
void (__stdcall*glVertexAttribP4ui)(GLuint, GLenum, GLboolean, GLuint) = nullptr;
void (__stdcall*glVertexAttribP4uiv)(GLuint, GLenum, GLboolean, const GLuint *) = nullptr;
# ifndef GL_VERSION_3_2
void (__stdcall*glDrawElementsBaseVertex)(GLenum, GLsizei, GLenum, const void *, GLint) = nullptr;
void (__stdcall*glDrawRangeElementsBaseVertex)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *, GLint) = nullptr;
void (__stdcall*glDrawElementsInstancedBaseVertex)(GLenum, GLsizei, GLenum, const void *indices, GLsizei, GLint) = nullptr;
void (__stdcall*glMultiDrawElementsBaseVertex)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei, const GLint *) = nullptr;
void (__stdcall*glProvokingVertex)(GLenum) = nullptr;
GLsync (__stdcall*glFenceSync)(GLenum, GLbitfield) = nullptr;
GLboolean (__stdcall*glIsSync)(GLsync) = nullptr;
void (__stdcall*glDeleteSync)(GLsync) = nullptr;
GLenum (__stdcall*glClientWaitSync)(GLsync, GLbitfield, GLuint64) = nullptr;
void (__stdcall*glWaitSync)(GLsync, GLbitfield flags, GLuint64 timeout) = nullptr;
void (__stdcall*glGetInteger64v)(GLenum, GLint64 *) = nullptr;
void (__stdcall*glGetSynciv)(GLsync, GLenum, GLsizei, GLsizei *, GLint *) = nullptr;
void (__stdcall*glGetInteger64i_v)(GLenum, GLuint, GLint64 *) = nullptr;
void (__stdcall*glGetBufferParameteri64v)(GLenum, GLenum, GLint64 *) = nullptr;
void (__stdcall*glFramebufferTexture)(GLenum, GLenum, GLuint, GLint) = nullptr;
void (__stdcall*glTexImage2DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean) = nullptr;
void (__stdcall*glTexImage3DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean) = nullptr;
void (__stdcall*glGetMultisamplefv)(GLenum, GLuint, GLfloat *) = nullptr;
void (__stdcall*glSampleMaski)(GLuint, GLbitfield) = nullptr;
# ifndef GL_VERSION_3_1
void (__stdcall*glDrawArraysInstanced)(GLenum, GLint, GLsizei, GLsizei) = nullptr;
void (__stdcall*glDrawElementsInstanced)(GLenum, GLsizei, GLenum, const void *, GLsizei) = nullptr;
void (__stdcall*glTexBuffer)(GLenum, GLenum, GLuint) = nullptr;
void (__stdcall*glPrimitiveRestartIndex)(GLuint) = nullptr;
void (__stdcall*glCopyBufferSubData)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr) = nullptr;
void (__stdcall*glGetUniformIndices)(GLuint, GLsizei, const GLchar *const*, GLuint *) = nullptr;
void (__stdcall*glGetActiveUniformsiv)(GLuint, GLsizei, const GLuint *, GLenum, GLint *) = nullptr;
void (__stdcall*glGetActiveUniformName)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
GLuint (__stdcall*glGetUniformBlockIndex)(GLuint, const GLchar *) = nullptr;
void (__stdcall*glGetActiveUniformBlockiv)(GLuint, GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetActiveUniformBlockName)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
void (__stdcall*glUniformBlockBinding)(GLuint, GLuint, GLuint) = nullptr;
# ifndef GL_VERSION_3_0
void (__stdcall*glColorMaski)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean) = nullptr;
void (__stdcall*glGetBooleani_v)(GLenum, GLuint, GLboolean *) = nullptr;
void (__stdcall*glGetIntegeri_v)(GLenum, GLuint, GLint *) = nullptr;
void (__stdcall*glEnablei)(GLenum, GLuint) = nullptr;
void (__stdcall*glDisablei)(GLenum, GLuint) = nullptr;
GLboolean (__stdcall*glIsEnabledi)(GLenum, GLuint) = nullptr;
void (__stdcall*glBeginTransformFeedback)(GLenum) = nullptr;
void (__stdcall*glEndTransformFeedback)(void) = nullptr;
void (__stdcall*glBindBufferRange)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr) = nullptr;
void (__stdcall*glBindBufferBase)(GLenum, GLuint, GLuint) = nullptr;
void (__stdcall*glTransformFeedbackVaryings)(GLuint, GLsizei, const GLchar *const*, GLenum) = nullptr;
void (__stdcall*glGetTransformFeedbackVarying)(GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *) = nullptr;
void (__stdcall*glClampColor)(GLenum, GLenum) = nullptr;
void (__stdcall*glBeginConditionalRender)(GLuint, GLenum) = nullptr;
void (__stdcall*glEndConditionalRender)(void) = nullptr;
void (__stdcall*glVertexAttribIPointer)(GLuint, GLint, GLenum, GLsizei, const void *) = nullptr;
void (__stdcall*glGetVertexAttribIiv)(GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetVertexAttribIuiv)(GLuint, GLenum, GLuint *) = nullptr;
void (__stdcall*glVertexAttribI1i)(GLuint, GLint) = nullptr;
void (__stdcall*glVertexAttribI2i)(GLuint, GLint, GLint) = nullptr;
void (__stdcall*glVertexAttribI3i)(GLuint, GLint, GLint, GLint) = nullptr;
void (__stdcall*glVertexAttribI4i)(GLuint, GLint, GLint, GLint, GLint) = nullptr;
void (__stdcall*glVertexAttribI1ui)(GLuint, GLuint) = nullptr;
void (__stdcall*glVertexAttribI2ui)(GLuint, GLuint, GLuint) = nullptr;
void (__stdcall*glVertexAttribI3ui)(GLuint, GLuint, GLuint, GLuint) = nullptr;
void (__stdcall*glVertexAttribI4ui)(GLuint, GLuint, GLuint, GLuint, GLuint) = nullptr;
void (__stdcall*glVertexAttribI1iv)(GLuint, const GLint *) = nullptr;
void (__stdcall*glVertexAttribI2iv)(GLuint, const GLint *) = nullptr;
void (__stdcall*glVertexAttribI3iv)(GLuint, const GLint *) = nullptr;
void (__stdcall*glVertexAttribI4iv)(GLuint, const GLint *) = nullptr;
void (__stdcall*glVertexAttribI1uiv)(GLuint, const GLuint *) = nullptr;
void (__stdcall*glVertexAttribI2uiv)(GLuint, const GLuint *) = nullptr;
void (__stdcall*glVertexAttribI3uiv)(GLuint, const GLuint *) = nullptr;
void (__stdcall*glVertexAttribI4uiv)(GLuint, const GLuint *) = nullptr;
void (__stdcall*glVertexAttribI4bv)(GLuint, const GLbyte *) = nullptr;
void (__stdcall*glVertexAttribI4sv)(GLuint, const GLshort *) = nullptr;
void (__stdcall*glVertexAttribI4ubv)(GLuint, const GLubyte *) = nullptr;
void (__stdcall*glVertexAttribI4usv)(GLuint, const GLushort *) = nullptr;
void (__stdcall*glGetUniformuiv)(GLuint, GLint, GLuint *) = nullptr;
void (__stdcall*glBindFragDataLocation)(GLuint, GLuint, const GLchar *) = nullptr;
GLint (__stdcall*glGetFragDataLocation)(GLuint, const GLchar *) = nullptr;
void (__stdcall*glUniform1ui)(GLint, GLuint) = nullptr;
void (__stdcall*glUniform2ui)(GLint, GLuint, GLuint) = nullptr;
void (__stdcall*glUniform3ui)(GLint, GLuint, GLuint, GLuint) = nullptr;
void (__stdcall*glUniform4ui)(GLint, GLuint, GLuint, GLuint, GLuint) = nullptr;
void (__stdcall*glUniform1uiv)(GLint, GLsizei, const GLuint *) = nullptr;
void (__stdcall*glUniform2uiv)(GLint, GLsizei, const GLuint *) = nullptr;
void (__stdcall*glUniform3uiv)(GLint, GLsizei, const GLuint *) = nullptr;
void (__stdcall*glUniform4uiv)(GLint, GLsizei, const GLuint *) = nullptr;
void (__stdcall*glTexParameterIiv)(GLenum, GLenum, const GLint *) = nullptr;
void (__stdcall*glTexParameterIuiv)(GLenum, GLenum, const GLuint *) = nullptr;
void (__stdcall*glGetTexParameterIiv)(GLenum, GLenum, GLint *) = nullptr;
void (__stdcall*glGetTexParameterIuiv)(GLenum, GLenum, GLuint *) = nullptr;
void (__stdcall*glClearBufferiv)(GLenum, GLint, const GLint *) = nullptr;
void (__stdcall*glClearBufferuiv)(GLenum, GLint, const GLuint *) = nullptr;
void (__stdcall*glClearBufferfv)(GLenum, GLint, const GLfloat *) = nullptr;
void (__stdcall*glClearBufferfi)(GLenum, GLint, GLfloat, GLint) = nullptr;
const GLubyte *(__stdcall*glGetStringi)(GLenum, GLuint) = nullptr;
GLboolean (__stdcall*glIsRenderbuffer)(GLuint ) = nullptr;
void (__stdcall*glBindRenderbuffer)(GLenum, GLuint ) = nullptr;
void (__stdcall*glDeleteRenderbuffers)(GLsizei, const GLuint *) = nullptr;
void (__stdcall*glGenRenderbuffers)(GLsizei, GLuint *) = nullptr;
void (__stdcall*glRenderbufferStorage)(GLenum, GLenum, GLsizei, GLsizei) = nullptr;
void (__stdcall*glGetRenderbufferParameteriv)(GLenum, GLenum, GLint *) = nullptr;
GLboolean (__stdcall*glIsFramebuffer)(GLuint) = nullptr;
void (__stdcall*glBindFramebuffer)(GLenum, GLuint ) = nullptr;
void (__stdcall*glDeleteFramebuffers)(GLsizei, const GLuint *) = nullptr;
void (__stdcall*glGenFramebuffers)(GLsizei, GLuint *) = nullptr;
GLenum (__stdcall*glCheckFramebufferStatus)(GLenum) = nullptr;
void (__stdcall*glFramebufferTexture1D)(GLenum, GLenum, GLenum, GLuint, GLint) = nullptr;
void (__stdcall*glFramebufferTexture2D)(GLenum, GLenum, GLenum, GLuint, GLint) = nullptr;
void (__stdcall*glFramebufferTexture3D)(GLenum, GLenum, GLenum, GLuint, GLint, GLint) = nullptr;
void (__stdcall*glFramebufferRenderbuffer)(GLenum, GLenum, GLenum, GLuint) = nullptr;
void (__stdcall*glGetFramebufferAttachmentParameteriv)(GLenum, GLenum, GLenum, GLint *) = nullptr;
void (__stdcall*glGenerateMipmap)(GLenum) = nullptr;
void (__stdcall*glBlitFramebuffer)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum) = nullptr;
void (__stdcall*glRenderbufferStorageMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei) = nullptr;
void (__stdcall*glFramebufferTextureLayer)(GLenum, GLenum, GLuint, GLint, GLint) = nullptr;
void *(__stdcall*glMapBufferRange)(GLenum, GLintptr, GLsizeiptr, GLbitfield) = nullptr;
void (__stdcall*glFlushMappedBufferRange)(GLenum, GLintptr, GLsizeiptr) = nullptr;
void (__stdcall*glBindVertexArray)(GLuint) = nullptr;
void (__stdcall*glDeleteVertexArrays)(GLsizei, const GLuint *) = nullptr;
void (__stdcall*glGenVertexArrays)(GLsizei, GLuint *) = nullptr;
GLboolean (__stdcall*glIsVertexArray)(GLuint) = nullptr;
# ifndef GL_VERSION_2_1
void (__stdcall*glUniformMatrix2x3fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glUniformMatrix3x2fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glUniformMatrix2x4fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glUniformMatrix4x2fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glUniformMatrix3x4fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glUniformMatrix4x3fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
# ifndef GL_VERSION_2_0
void (__stdcall*glBlendEquationSeparate)(GLenum, GLenum) = nullptr;
void (__stdcall*glDrawBuffers)(GLsizei, const GLenum *) = nullptr;
void (__stdcall*glStencilOpSeparate)(GLenum, GLenum, GLenum, GLenum) = nullptr;
void (__stdcall*glStencilFuncSeparate)(GLenum, GLenum, GLint, GLuint) = nullptr;
void (__stdcall*glStencilMaskSeparate)(GLenum, GLuint) = nullptr;
void (__stdcall*glAttachShader)(GLuint, GLuint) = nullptr;
void (__stdcall*glBindAttribLocation)(GLuint, GLuint, const GLchar *) = nullptr;
void (__stdcall*glCompileShader)(GLuint) = nullptr;
GLuint (__stdcall*glCreateProgram)(void) = nullptr;
GLuint (__stdcall*glCreateShader)(GLenum) = nullptr;
void (__stdcall*glDeleteProgram)(GLuint) = nullptr;
void (__stdcall*glDeleteShader)(GLuint) = nullptr;
void (__stdcall*glDetachShader)(GLuint, GLuint) = nullptr;
void (__stdcall*glDisableVertexAttribArray)(GLuint) = nullptr;
void (__stdcall*glEnableVertexAttribArray)(GLuint) = nullptr;
void (__stdcall*glGetActiveAttrib)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *) = nullptr;
void (__stdcall*glGetActiveUniform)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *) = nullptr;
void (__stdcall*glGetAttachedShaders)(GLuint, GLsizei, GLsizei *, GLuint *) = nullptr;
GLint (__stdcall*glGetAttribLocation)(GLuint, const GLchar *) = nullptr;
void (__stdcall*glGetProgramiv)(GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetProgramInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
void (__stdcall*glGetShaderiv)(GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetShaderInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
void (__stdcall*glGetShaderSource)(GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
GLint (__stdcall*glGetUniformLocation)(GLuint, const GLchar *) = nullptr;
void (__stdcall*glGetUniformfv)(GLuint, GLint, GLfloat *) = nullptr;
void (__stdcall*glGetUniformiv)(GLuint, GLint, GLint *) = nullptr;
void (__stdcall*glGetVertexAttribdv)(GLuint, GLenum, GLdouble *) = nullptr;
void (__stdcall*glGetVertexAttribfv)(GLuint, GLenum, GLfloat *) = nullptr;
void (__stdcall*glGetVertexAttribiv)(GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetVertexAttribPointerv)(GLuint, GLenum, void **) = nullptr;
GLboolean (__stdcall*glIsProgram)(GLuint) = nullptr;
GLboolean (__stdcall*glIsShader)(GLuint) = nullptr;
void (__stdcall*glLinkProgram)(GLuint) = nullptr;
void (__stdcall*glShaderSource)(GLuint, GLsizei, const GLchar *const*, const GLint *) = nullptr;
void (__stdcall*glUseProgram)(GLuint) = nullptr;
void (__stdcall*glUniform1f)(GLint, GLfloat) = nullptr;
void (__stdcall*glUniform2f)(GLint, GLfloat, GLfloat) = nullptr;
void (__stdcall*glUniform3f)(GLint, GLfloat, GLfloat, GLfloat) = nullptr;
void (__stdcall*glUniform4f)(GLint, GLfloat, GLfloat, GLfloat, GLfloat) = nullptr;
void (__stdcall*glUniform1i)(GLint, GLint) = nullptr;
void (__stdcall*glUniform2i)(GLint, GLint, GLint) = nullptr;
void (__stdcall*glUniform3i)(GLint, GLint, GLint, GLint) = nullptr;
void (__stdcall*glUniform4i)(GLint, GLint, GLint, GLint, GLint) = nullptr;
void (__stdcall*glUniform1fv)(GLint, GLsizei, const GLfloat *) = nullptr;
void (__stdcall*glUniform2fv)(GLint, GLsizei, const GLfloat *) = nullptr;
void (__stdcall*glUniform3fv)(GLint, GLsizei, const GLfloat *) = nullptr;
void (__stdcall*glUniform4fv)(GLint, GLsizei, const GLfloat *) = nullptr;
void (__stdcall*glUniform1iv)(GLint, GLsizei, const GLint *) = nullptr;
void (__stdcall*glUniform2iv)(GLint, GLsizei, const GLint *) = nullptr;
void (__stdcall*glUniform3iv)(GLint, GLsizei, const GLint *) = nullptr;
void (__stdcall*glUniform4iv)(GLint, GLsizei, const GLint *) = nullptr;
void (__stdcall*glUniformMatrix2fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glUniformMatrix3fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glUniformMatrix4fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
void (__stdcall*glValidateProgram)(GLuint) = nullptr;
void (__stdcall*glVertexAttrib1d)(GLuint, GLdouble) = nullptr;
void (__stdcall*glVertexAttrib1dv)(GLuint, const GLdouble *) = nullptr;
void (__stdcall*glVertexAttrib1f)(GLuint, GLfloat) = nullptr;
void (__stdcall*glVertexAttrib1fv)(GLuint, const GLfloat *) = nullptr;
void (__stdcall*glVertexAttrib1s)(GLuint, GLshort) = nullptr;
void (__stdcall*glVertexAttrib1sv)(GLuint, const GLshort *) = nullptr;
void (__stdcall*glVertexAttrib2d)(GLuint, GLdouble, GLdouble) = nullptr;
void (__stdcall*glVertexAttrib2dv)(GLuint, const GLdouble *) = nullptr;
void (__stdcall*glVertexAttrib2f)(GLuint, GLfloat, GLfloat) = nullptr;
void (__stdcall*glVertexAttrib2fv)(GLuint, const GLfloat *) = nullptr;
void (__stdcall*glVertexAttrib2s)(GLuint, GLshort, GLshort) = nullptr;
void (__stdcall*glVertexAttrib2sv)(GLuint, const GLshort *) = nullptr;
void (__stdcall*glVertexAttrib3d)(GLuint, GLdouble, GLdouble, GLdouble) = nullptr;
void (__stdcall*glVertexAttrib3dv)(GLuint, const GLdouble *) = nullptr;
void (__stdcall*glVertexAttrib3f)(GLuint, GLfloat, GLfloat, GLfloat) = nullptr;
void (__stdcall*glVertexAttrib3fv)(GLuint, const GLfloat *) = nullptr;
void (__stdcall*glVertexAttrib3s)(GLuint, GLshort, GLshort, GLshort) = nullptr;
void (__stdcall*glVertexAttrib3sv)(GLuint, const GLshort *) = nullptr;
void (__stdcall*glVertexAttrib4Nbv)(GLuint, const GLbyte *) = nullptr;
void (__stdcall*glVertexAttrib4Niv)(GLuint, const GLint *) = nullptr;
void (__stdcall*glVertexAttrib4Nsv)(GLuint, const GLshort *) = nullptr;
void (__stdcall*glVertexAttrib4Nub)(GLuint, GLubyte, GLubyte, GLubyte, GLubyte) = nullptr;
void (__stdcall*glVertexAttrib4Nubv)(GLuint, const GLubyte *) = nullptr;
void (__stdcall*glVertexAttrib4Nuiv)(GLuint, const GLuint *) = nullptr;
void (__stdcall*glVertexAttrib4Nusv)(GLuint, const GLushort *) = nullptr;
void (__stdcall*glVertexAttrib4bv)(GLuint, const GLbyte *) = nullptr;
void (__stdcall*glVertexAttrib4d)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble) = nullptr;
void (__stdcall*glVertexAttrib4dv)(GLuint, const GLdouble *) = nullptr;
void (__stdcall*glVertexAttrib4f)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat) = nullptr;
void (__stdcall*glVertexAttrib4fv)(GLuint, const GLfloat *) = nullptr;
void (__stdcall*glVertexAttrib4iv)(GLuint, const GLint *) = nullptr;
void (__stdcall*glVertexAttrib4s)(GLuint, GLshort, GLshort, GLshort, GLshort) = nullptr;
void (__stdcall*glVertexAttrib4sv)(GLuint, const GLshort *) = nullptr;
void (__stdcall*glVertexAttrib4ubv)(GLuint, const GLubyte *) = nullptr;
void (__stdcall*glVertexAttrib4uiv)(GLuint, const GLuint *) = nullptr;
void (__stdcall*glVertexAttrib4usv)(GLuint, const GLushort *) = nullptr;
void (__stdcall*glVertexAttribPointer)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *) = nullptr;
# ifndef GL_VERSION_1_5
void (__stdcall*glGenQueries)(GLsizei, GLuint *) = nullptr;
void (__stdcall*glDeleteQueries)(GLsizei, const GLuint *) = nullptr;
GLboolean (__stdcall*glIsQuery)(GLuint) = nullptr;
void (__stdcall*glBeginQuery)(GLenum, GLuint) = nullptr;
void (__stdcall*glEndQuery)(GLenum) = nullptr;
void (__stdcall*glGetQueryiv)(GLenum, GLenum, GLint *) = nullptr;
void (__stdcall*glGetQueryObjectiv)(GLuint, GLenum, GLint *) = nullptr;
void (__stdcall*glGetQueryObjectuiv)(GLuint, GLenum, GLuint *) = nullptr;
void (__stdcall*glBindBuffer)(GLenum, GLuint) = nullptr;
void (__stdcall*glDeleteBuffers)(GLsizei, const GLuint *) = nullptr;
void (__stdcall*glGenBuffers)(GLsizei, GLuint *) = nullptr;
GLboolean (__stdcall*glIsBuffer)(GLuint) = nullptr;
void (__stdcall*glBufferData)(GLenum, GLsizeiptr, const void *, GLenum) = nullptr;
void (__stdcall*glBufferSubData)(GLenum, GLintptr, GLsizeiptr, const void *) = nullptr;
void (__stdcall*glGetBufferSubData)(GLenum, GLintptr, GLsizeiptr, void *) = nullptr;
void *(__stdcall*glMapBuffer)(GLenum, GLenum) = nullptr;
GLboolean (__stdcall*glUnmapBuffer)(GLenum) = nullptr;
void (__stdcall*glGetBufferParameteriv)(GLenum, GLenum, GLint *) = nullptr;
void (__stdcall*glGetBufferPointerv)(GLenum, GLenum, void **) = nullptr;
# ifndef GL_VERSION_1_4
void (__stdcall*glBlendFuncSeparate)(GLenum, GLenum, GLenum, GLenum) = nullptr;
void (__stdcall*glMultiDrawArrays)(GLenum, const GLint *, const GLsizei *, GLsizei) = nullptr;
void (__stdcall*glMultiDrawElements)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei) = nullptr;
void (__stdcall*glPointParameterf)(GLenum, GLfloat) = nullptr;
void (__stdcall*glPointParameterfv)(GLenum, const GLfloat *) = nullptr;
void (__stdcall*glPointParameteri)(GLenum, GLint) = nullptr;
void (__stdcall*glPointParameteriv)(GLenum, const GLint *) = nullptr;
void (__stdcall*glBlendColor)(GLfloat, GLfloat, GLfloat, GLfloat) = nullptr;
void (__stdcall*glBlendEquation)(GLenum) = nullptr;
# ifndef GL_VERSION_1_3
void (__stdcall*glActiveTexture)(GLenum) = nullptr;
void (__stdcall*glSampleCoverage)(GLfloat, GLboolean) = nullptr;
void (__stdcall*glCompressedTexImage3D)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *) = nullptr;
void (__stdcall*glCompressedTexImage2D)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *) = nullptr;
void (__stdcall*glCompressedTexImage1D)(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *) = nullptr;
void (__stdcall*glCompressedTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *) = nullptr;
void (__stdcall*glCompressedTexSubImage2D)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *) = nullptr;
void (__stdcall*glCompressedTexSubImage1D)(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *) = nullptr;
void (__stdcall*glGetCompressedTexImage)(GLenum, GLint, void *) = nullptr;
# ifndef GL_VERSION_1_2
void (__stdcall*glDrawRangeElements)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *) = nullptr;
void (__stdcall*glTexImage3D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) = nullptr;
void (__stdcall*glTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) = nullptr;
void (__stdcall*glCopyTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) = nullptr;
# ifndef GL_VERSION_1_1
void (__stdcall*glDrawArrays)(GLenum, GLint, GLsizei) = nullptr;
void (__stdcall*glDrawElements)(GLenum, GLsizei, GLenum, const void *) = nullptr;
void (__stdcall*glGetPointerv)(GLenum, void **) = nullptr;
void (__stdcall*glPolygonOffset)(GLfloat, GLfloat) = nullptr;
void (__stdcall*glCopyTexImage1D)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint) = nullptr;
void (__stdcall*glCopyTexImage2D)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint) = nullptr;
void (__stdcall*glCopyTexSubImage1D)(GLenum, GLint, GLint, GLint, GLint, GLsizei) = nullptr;
void (__stdcall*glCopyTexSubImage2D)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) = nullptr;
void (__stdcall*glTexSubImage1D)(GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void *) = nullptr;
void (__stdcall*glTexSubImage2D)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *) = nullptr;
void (__stdcall*glBindTexture)(GLenum, GLuint) = nullptr;
void (__stdcall*glDeleteTextures)(GLsizei, const GLuint *) = nullptr;
void (__stdcall*glGenTextures)(GLsizei, GLuint *) = nullptr;
GLboolean(__stdcall*glIsTexture)(GLuint) = nullptr;
# ifndef GL_VERSION_1_0
void (__stdcall*glCullFace)(GLenum) = nullptr;
void (__stdcall*glFrontFace)(GLenum) = nullptr;
void (__stdcall*glHint)(GLenum, GLenum) = nullptr;
void (__stdcall*glLineWidth)(GLfloat) = nullptr;
void (__stdcall*glPointSize)(GLfloat) = nullptr;
void (__stdcall*glPolygonMode)(GLenum, GLenum) = nullptr;
void (__stdcall*glScissor)(GLint, GLint, GLsizei, GLsizei) = nullptr;
void (__stdcall*glTexParameterf)(GLenum, GLenum, GLfloat) = nullptr;
void (__stdcall*glTexParameterfv)(GLenum, GLenum, const GLfloat *) = nullptr;
void (__stdcall*glTexParameteri)(GLenum, GLenum, GLint) = nullptr;
void (__stdcall*glTexParameteriv)(GLenum, GLenum, const GLint *) = nullptr;
void (__stdcall*glTexImage1D)(GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void *) = nullptr;
void (__stdcall*glTexImage2D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) = nullptr;
void (__stdcall*glDrawBuffer)(GLenum) = nullptr;
void (__stdcall*glClear)(GLbitfield) = nullptr;
void (__stdcall*glClearColor)(GLfloat, GLfloat, GLfloat, GLfloat) = nullptr;
void (__stdcall*glClearStencil)(GLint) = nullptr;
void (__stdcall*glClearDepth)(GLdouble) = nullptr;
void (__stdcall*glStencilMask)(GLuint) = nullptr;
void (__stdcall*glColorMask)(GLboolean, GLboolean, GLboolean, GLboolean) = nullptr;
void (__stdcall*glDepthMask)(GLboolean) = nullptr;
void (__stdcall*glDisable)(GLenum) = nullptr;
void (__stdcall*glEnable)(GLenum) = nullptr;
void (__stdcall*glFinish)(void) = nullptr;
void (__stdcall*glFlush)(void) = nullptr;
void (__stdcall*glBlendFunc)(GLenum, GLenum) = nullptr;
void (__stdcall*glLogicOp)(GLenum) = nullptr;
void (__stdcall*glStencilFunc)(GLenum, GLint, GLuint) = nullptr;
void (__stdcall*glStencilOp)(GLenum, GLenum, GLenum) = nullptr;
void (__stdcall*glDepthFunc)(GLenum) = nullptr;
void (__stdcall*glPixelStoref)(GLenum, GLfloat) = nullptr;
void (__stdcall*glPixelStorei)(GLenum, GLint) = nullptr;
void (__stdcall*glReadBuffer)(GLenum) = nullptr;
void (__stdcall*glReadPixels)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void *) = nullptr;
void (__stdcall*glGetBooleanv)(GLenum, GLboolean *) = nullptr;
void (__stdcall*glGetDoublev)(GLenum, GLdouble *) = nullptr;
GLenum (__stdcall*glGetError)(void) = nullptr;
void (__stdcall*glGetFloatv)(GLenum, GLfloat *) = nullptr;
void (__stdcall*glGetIntegerv)(GLenum, GLint *) = nullptr;
const GLubyte *(__stdcall*glGetString)(GLenum) = nullptr;
void (__stdcall*glGetTexImage)(GLenum, GLint, GLenum, GLenum, void *) = nullptr;
void (__stdcall*glGetTexParameterfv)(GLenum, GLenum, GLfloat *) = nullptr;
void (__stdcall*glGetTexParameteriv)(GLenum, GLenum, GLint *) = nullptr;
void (__stdcall*glGetTexLevelParameterfv)(GLenum, GLint, GLenum, GLfloat *) = nullptr;
void (__stdcall*glGetTexLevelParameteriv)(GLenum, GLint, GLenum, GLint *) = nullptr;
GLboolean (__stdcall*glIsEnabled)(GLenum) = nullptr;
void (__stdcall*glDepthRange)(GLdouble, GLdouble) = nullptr;
void (__stdcall*glViewport)(GLint, GLint, GLsizei, GLsizei) = nullptr;
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
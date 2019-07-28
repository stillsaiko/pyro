# pragma once
// include "rbo.h"
// include "tex.h"
# include <glsl.h>
# include <cassert>
/*enum ATTACHMENT {
	COLOR_ATTACHMENT0 = GL_COLOR_ATTACHMENT0,
	DEPTH_ATTACHMENT = GL_DEPTH_ATTACHMENT,
	DEPTH_STENCIL_ATTACHMENT = GL_DEPTH_STENCIL_ATTACHMENT
}*/
// RBO depth = RBO(...)
// TEX2D color_0 = TEX2D(...)
// TEX2D color_1 = TEX2D(...)
// FBO framebuffer = FBO(depth, color_0, color_1)
// + framebuffer // bind framebuffer
//	...
// - framebuffer // unbind framebuffer
// TEX2D color_0_new = TEX2D(...)
// framebuffer.attach(GL_COLOR_ATTACHMENT_0, color_0_new)
// framebuffer.draw(GL_COLOR_ATTACHMENT_0)
//	...
struct FBO {
	struct A {
		GLuint ID = 0u ;
		GLenum T = 0u ;
		inline operator GLuint(void)const { return ID ; }
		static constexpr GLenum format(GLenum internalformat){
			switch(internalformat){
				case GL_R8: // *_SNORM
				case GL_R16:
				case GL_R16F:
					return GL_RED ;
				case GL_R8I:
				case GL_R8UI:
				case GL_R16I:
				case GL_R16UI:
					return GL_RED_INTEGER ;
				case GL_RG8:
				case GL_RG16:
				case GL_RG16F:
					return GL_RG ;
				case GL_RG8I:
				case GL_RG8UI:
				case GL_RG16I:
				case GL_RG16UI:
					return GL_RG_INTEGER ;
				case GL_RGB8:
				case GL_RGB16:
				case GL_RGB16F:
					return GL_RGB ;
				case GL_RGB8I:
				case GL_RGB8UI:
				case GL_RGB16I:
				case GL_RGB16UI:
					return GL_RGB_INTEGER ;
				case GL_RGBA8:
				case GL_RGBA16:
				case GL_RGBA16F:
					return GL_RGBA ;
				case GL_RGBA8I:
				case GL_RGBA8UI:
				case GL_RGBA16I:
				case GL_RGBA16UI:
					return GL_RGBA_INTEGER ;
				case GL_DEPTH_COMPONENT16:
				case GL_DEPTH_COMPONENT24:
				case GL_DEPTH_COMPONENT32:
					return GL_DEPTH_COMPONENT ;
				default:
					return GL_INVALID_ENUM ; // warning
			}
		}
		static constexpr GLenum type(GLenum internalformat){
			switch(internalformat){
				case GL_RED: // *_SNORM
				case GL_R : case GL_RG : case GL_RGB : case GL_RGBA:
				case GL_R8: case GL_RG8: case GL_RGB8: case GL_RGBA8:
				case GL_R8UI:
				case GL_RG8UI:
				case GL_RGB8UI:
				case GL_RGBA8UI:
					return GL_UNSIGNED_BYTE ;
				case GL_R16:
				case GL_R16UI:
				case GL_RG16:
				case GL_RG16UI:
				case GL_RGB16:
				case GL_RGB16UI:
				case GL_RGBA16:
				case GL_RGBA16UI:
					return GL_UNSIGNED_SHORT ;
				case GL_R8I:
				case GL_RG8I:
				case GL_RGB8I:
				case GL_RGBA8I:
					return GL_BYTE ;
				case GL_R16I:
				case GL_RG16I:
				case GL_RGB16I:
				case GL_RGBA16I:
					return GL_SHORT ;
				case GL_R16F:
				case GL_RG16F:
				case GL_RGB16F:
				case GL_RGBA16F:
					return GL_HALF_FLOAT ;
				case GL_R32F:
				case GL_RG32F:
				case GL_RGB32F:
				case GL_RGBA32F:
					return GL_FLOAT ;
				case GL_DEPTH_COMPONENT16:
					return GL_UNSIGNED_SHORT ;
				case GL_DEPTH_COMPONENT24:
				case GL_DEPTH_COMPONENT32:
					return GL_UNSIGNED_INT ;
				case GL_DEPTH_COMPONENT32F:
					return GL_FLOAT ;
				case GL_DEPTH24_STENCIL8:
					return GL_UNSIGNED_INT_24_8 ;
				default:
					return GL_INVALID_ENUM ; // warning
			}
		}
	};
	A DEPTH_ATTACHMENT ;
	A COLOR_ATTACHMENT[8u];
	~
	FBO(void);
template<class...VA>
	FBO(A& Z, VA&...);
	FBO(void);
	FBO& operator = (FBO&& a)noexcept ;
//	void resize(GLsizei width, GLsizei height);
	GLint BINDING = 0;
	GLint VIEWPORT[4] = {0};
	GLint DRAW_BUFFER = GL_BACK ;
	void operator + (void);
	void operator - (void);
	operator GLuint(void)const ;
	void check(void);
	template<class...VA>
	void draw(VA...ARGS); // GL_COLOR_ATTACHMENT0
private :
	void draw(GLsizei);
	A& operator[ ](GLenum attachment);
	void attach(GLenum attachment, A&); // bind yourself before you call here
	GLuint fbo = 0u ;
};
template<class...VA> FBO::FBO(A& Z, VA&...ARGS): COLOR_ATTACHMENT{ARGS...} {
	DEPTH_ATTACHMENT.ID	= Z.ID ;
	DEPTH_ATTACHMENT.T	= Z.T ;
	{
		GLint max ;
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &max);													GL_ASSERT
		assert(sizeof...(VA) <= max);
	}
	glGenFramebuffers(1u, &fbo);
	GLint B ;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &B);															GL_ASSERT
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);																GL_ASSERT
	{
		GLint i ;
		switch(DEPTH_ATTACHMENT.T){
		case GL_RENDERBUFFER:
			glBindRenderbuffer(Z.T, Z);																	GL_ASSERT
			glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_INTERNAL_FORMAT, &i);			GL_ASSERT
			break ;
		case GL_TEXTURE_CUBE_MAP:
		case GL_TEXTURE_CUBE_MAP_ARRAY:
			glBindTexture(Z.T, Z);																		GL_ASSERT
			glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_TEXTURE_INTERNAL_FORMAT, &i);GL_ASSERT
			break ;
		default:
			glBindTexture(Z.T, Z);																		GL_ASSERT
			glGetTexLevelParameteriv(Z.T, 0, GL_TEXTURE_INTERNAL_FORMAT, &i);							GL_ASSERT
			break ;
		}
		switch(i){
		case GL_DEPTH_STENCIL: // eh...
		case GL_DEPTH24_STENCIL8:
		case GL_DEPTH32F_STENCIL8:
			attach(GL_DEPTH_STENCIL_ATTACHMENT, Z);
			break ;
		default:
			attach(GL_DEPTH_ATTACHMENT, Z);
			break ;
		}
	}
	glBindFramebuffer(GL_FRAMEBUFFER, B);																GL_ASSERT
	for(size_t i(0u); i<sizeof...(VA); ++i)
		attach(GL_COLOR_ATTACHMENT0 + i, COLOR_ATTACHMENT[i]);
	// draw buffers
	draw(sizeof...(VA));
/*	GLenum bufs[sizeof...(VA)];
	for(size_t i(0u); i<sizeof...(VA); ++i)
		bufs[i] = GL_COLOR_ATTACHMENT0 + i ;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &B);		GL_ASSERT
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);			GL_ASSERT
	glDrawBuffers(sizeof...(VA), bufs);				GL_ASSERT
	glBindFramebuffer(GL_FRAMEBUFFER, B);			GL_ASSERT*/
}
template<class...VA>
void FBO::draw(VA...ARGS){ // GL_COLOR_ATTACHMENT0
	GLint B ;
	GLenum bufs[ ]{ARGS...};
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &B);		GL_ASSERT
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);			GL_ASSERT
	glDrawBuffers(sizeof...(VA), bufs);				GL_ASSERT
	glBindFramebuffer(GL_FRAMEBUFFER, B);			GL_ASSERT
}
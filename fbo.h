# pragma once
// include "rbo.h"
// include <glsl.h>
# include "tex.h"
/*enum ATTACHMENT {
	COLOR_ATTACHMENT0 = GL_COLOR_ATTACHMENT0,
	DEPTH_ATTACHMENT = GL_DEPTH_ATTACHMENT,
	DEPTH_STENCIL_ATTACHMENT = GL_DEPTH_STENCIL_ATTACHMENT
}*/
/*struct RBO
{
	~
	RBO(void);
	RBO(void) = default;
	RBO(GLenum internalformat, GLsizei width, GLsizei height);
	operator GLuint(void)const;
private:
	GLuint ID = 0;
};
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
struct FBO
{
//	template<size_t N> FBO::bind(GLenum bufs[N]) { glBindFramebuffer(ID), glDrawBuffers(N, bufs) }
//	FBO::bind(void)                              { glBindFramebuffer(ID), glDrawBuffer(GL_NONE) }
//	static FBO::bind_default(void)               { glBindFramebuffer(0), glDrawBuffer(GL_FRONT) }
	~
	FBO(void);
	FBO(void) = default;
	template<size_t N, class...VA>
	FBO(GLenum attachment[N], const VA &...attachables)
	{
		static_assert(sizeof...(VA) == N, "#@?!");
		GLenum a = GL_COLOR_ATTACHMENT0;
		(attach(a ++, attachables), ...);
	}
	// glFramebufferRenderbuffer
	void attach(GLenum attachment, const RBO & renderbuffer);
	// glFramebufferTexture
	void attach(GLenum attachment, const TEX1D & texture, GLint level = 0);
	void attach(GLenum attachment, const TEX2D & texture, GLint level = 0);
	void attach(GLenum attachment, const TEX3D & texture, GLint level = 0);
	// glFramebufferTextureLayer
	void attach_layer(GLenum attachment, const TEX1D & texture, GLint layer, GLint level = 0);
	void attach_layer(GLenum attachment, const TEX2D & texture, GLint layer, GLint level = 0);
	void attach_layer(GLenum attachment, const TEX3D & texture, GLint layer, GLint level = 0);
private:
	GLuint ID = 0;
};*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARB_framebuffer_object 3.0
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct RBO
{
	~
	RBO(void);
	RBO(void) = default;
	RBO(RBO &&) noexcept;
	void operator = (RBO &&) noexcept;
	RBO(GLenum internalformat, GLsizei width, GLsizei height);
	// EXT_framebuffer_multisample
	RBO(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
	operator GLuint(void) const;
private:
	friend class FBO;
	GLuint renderbuffer;
	GLenum internalformat;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// glDrawBuffers(GLsizei n​, const GLenum *bufs​)
// glReadBuffer(GLenum mode​)
struct FBO
{
	struct A
	{
		const union
		{
			GLuint texture;
			GLuint renderbuffer;
		};
		const GLenum target;
		const GLint internalformat;
		A(const TEX1D &TEX): texture(TEX), target(TEX.target), internalformat(TEX.internalformat) { }
		A(const TEX2D &TEX): texture(TEX), target(TEX.target), internalformat(TEX.internalformat) { }
		A(const TEX3D &TEX): texture(TEX), target(TEX.target), internalformat(TEX.internalformat) { }
		A(const RBO &RBO): renderbuffer(RBO), target(GL_RENDERBUFFER), internalformat(RBO.internalformat) { }
	};
	~
	FBO(void);
	FBO(void);
	FBO(FBO &&) noexcept;
	void operator = (FBO &&) noexcept;

	template<class...VA>
	FBO(const TEX1D &texture, const VA &...ARGS):
	FBO(nullptr, sizeof...(VA)+1, static_cast<A>(texture), static_cast<A>(ARGS)...)
	{ }
	
	template<class...VA>
	FBO(const TEX2D &texture, const VA &...ARGS):
	FBO(nullptr, sizeof...(VA)+1, static_cast<A>(texture), static_cast<A>(ARGS)...)
	{ }

	template<class...VA>
	FBO(const TEX3D &texture, const VA &...ARGS):
	FBO(nullptr, sizeof...(VA)+1, static_cast<A>(texture), static_cast<A>(ARGS)...)
	{ }

	template<class...VA>
	FBO(const RBO &renderbuffer, const VA &...ARGS):
	FBO(nullptr, sizeof...(VA)+1, static_cast<A>(renderbuffer), static_cast<A>(ARGS)...)
	{ }

	template<class...VA>
	FBO(const GLenum (&attachment)[sizeof...(VA)], const VA &...ARGS):
	FBO(attachment, sizeof...(VA), static_cast<A>(ARGS)...)
	{ }

/*	inline void param(GLenum pname, GLint param)
	{
		GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, framebuffer)) &&
		GL_ASSERT(glFramebufferParameteri(GL_FRAMEBUFFER, pname, param));
	}*/
	
/*	// glFramebufferRenderbuffer
	void attach(GLenum attachment, const RBO &renderbuffer, GLint level = 0);
	// glFramebufferTexture
	void attach(GLenum attachment, const TEX1D &texture, GLint level = 0);
	void attach(GLenum attachment, const TEX2D &texture, GLint level = 0);
	void attach(GLenum attachment, const TEX3D &texture, GLint level = 0);
	// glFramebufferTextureLayer
	void attach(GLenum attachment, const TEX1D &texture, GLint level, GLint layer);
	void attach(GLenum attachment, const TEX2D &texture, GLint level, GLint layer);
	void attach(GLenum attachment, const TEX3D &texture, GLint level, GLint layer);
	// ARB_invalidate_subdata 4.3
	void invalidate(GLenum attachment);
	void invalidate(GLenum attachment, GLint x, GLint y, GLint width, GLint height);*/

	operator GLuint(void) const;
private:
	// private
	FBO(const GLenum *, size_t, ...);
	GLuint framebuffer;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*template<class...VA> FBO::FBO(A& Z, VA&...ARGS): COLOR_ATTACHMENT{ARGS...} {
	DEPTH_ATTACHMENT.ID	= Z.ID ;
	DEPTH_ATTACHMENT.T	= Z.T ;
	{
		GLint max ;
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &max);								GL_ASSERT
		assert(sizeof...(VA) <= max);
	}
	glGenFramebuffers(1u, &fbo);
	GLint B ;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &B);									GL_ASSERT
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);										GL_ASSERT
	{
		GLint i ;
		switch(DEPTH_ATTACHMENT.T){
		case GL_RENDERBUFFER:
			glBindRenderbuffer(Z.T, Z);									GL_ASSERT
		s	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_INTERNAL_FORMAT, &i);		GL_ASSERT
			break ;
		case GL_TEXTURE_CUBE_MAP:
		case GL_TEXTURE_CUBE_MAP_ARRAY:
			glBindTexture(Z.T, Z);										GL_ASSERT
			glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_TEXTURE_INTERNAL_FORMAT, &i);	GL_ASSERT
			break ;
		default:
			glBindTexture(Z.T, Z);										GL_ASSERT
			glGetTexLevelParameteriv(Z.T, 0, GL_TEXTURE_INTERNAL_FORMAT, &i);				GL_ASSERT
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
	glBindFramebuffer(GL_FRAMEBUFFER, B);										GL_ASSERT
	for(size_t i(0u); i<sizeof...(VA); ++i)
		attach(GL_COLOR_ATTACHMENT0 + i, COLOR_ATTACHMENT[i]);
	// draw buffers
	draw(sizeof...(VA));
//	GLenum bufs[sizeof...(VA)];
//	for(size_t i(0u); i<sizeof...(VA); ++i)
//		bufs[i] = GL_COLOR_ATTACHMENT0 + i ;
//	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &B);		GL_ASSERT
//	glBindFramebuffer(GL_FRAMEBUFFER, fbo);			GL_ASSERT
//	glDrawBuffers(sizeof...(VA), bufs);			GL_ASSERT
//	glBindFramebuffer(GL_FRAMEBUFFER, B);			GL_ASSERT
}*/




/*template<class...VA>
void FBO::draw(VA...ARGS){ // GL_COLOR_ATTACHMENT0
	GLint B ;
	GLenum bufs[ ]{ARGS...};
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &B);		GL_ASSERT
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);			GL_ASSERT
	glDrawBuffers(sizeof...(VA), bufs);			GL_ASSERT
	glBindFramebuffer(GL_FRAMEBUFFER, B);			GL_ASSERT
}*/

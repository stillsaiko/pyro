# pragma once
# include "fbo.h"
// RBO ZBuffer(GL_DEPTH_COMPONENT16, X, Y)
// glFramebufferRenderbuffer(GL_FRAMEBUFFER,
//	GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, ZBuffer)
struct RBO : public FBO::A {
/*	GLuint ID = 0u ;
	GLenum T = GL_RENDERBUFFER ;*/
	~
	RBO(void);
	RBO(void);
	RBO(GLenum internalformat, GLsizei width, GLsizei height);
	RBO& operator = (RBO&&)noexcept ;
	void resize(GLsizei, GLsizei);
	operator GLuint(void)const ;
};
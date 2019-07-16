# pragma once
# include "fbo.h"
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
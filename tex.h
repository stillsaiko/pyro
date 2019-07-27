# pragma once
# include "fbo.h"
# define GL_ASSERT assert(glGetError( ) == GL_NO_ERROR);
// NEW
struct TEX : public FBO::A {
	void bind(GLenum = GL_TEXTURE0);
	void param(GLenum, GLenum);
	void mipmap(void);
protected:
	TEX(void);
};
struct TEX1D : public TEX {
	void image(GLenum format, GLsizei width, GLvoid * pixels);
	void resize(GLsizei width);
	~
	TEX1D(void);
	TEX1D(void);
	TEX1D(GLenum target, GLenum format, GLsizei width, GLvoid * pixels = nullptr);
	TEX1D& operator = (TEX1D&&)noexcept ;
};
struct TEX2D : public TEX {
	void image(GLenum format, GLsizei width, GLsizei height, GLvoid * pixels);
	void resize(GLsizei width,
				GLsizei height);
	~
	TEX2D(void);
	TEX2D(void);
	TEX2D(GLenum target, GLenum format,	GLsizei width, 
										GLsizei height, GLvoid * pixels = nullptr);
	TEX2D& operator = (TEX2D&&)noexcept ;
};
struct TEX3D : public TEX {
	void image(GLenum format, GLsizei width, GLsizei height, GLsizei depth, GLvoid * pixels);
	void resize(GLsizei width,
				GLsizei height,
				GLsizei depth);
	~
	TEX3D(void);
	TEX3D(void);
	TEX3D(GLenum target, GLenum format,	GLsizei width,
										GLsizei height,
										GLsizei depth, GLvoid * pixels = nullptr);
	TEX3D& operator = (TEX3D&&)noexcept ;
};

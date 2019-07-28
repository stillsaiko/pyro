# pragma once
# include "fbo.h"
# define GL_ASSERT assert(glGetError( ) == GL_NO_ERROR);
// protected constructor
struct TEX : public FBO::A {
	void bind(GLenum = GL_TEXTURE0);
	void param(GLenum, GLenum);
	void mipmap(void);
protected:
	TEX(void); // secret ctor
};
// TEX1D texture(GL_RGBA, 1024, nullptr)
// TEX1D texture(GL_RGBA, 1024, new RGBA[1024])
// texture.param(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
// texture.param(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
// texture.bind(GL_TEXTURE_0)
struct TEX1D : public TEX {
	void image(GLenum format, GLsizei width, GLvoid * pixels);
	void resize(GLsizei width);
	~
	TEX1D(void);
	TEX1D(void);
	TEX1D(GLenum target, GLenum format, GLsizei width, GLvoid * pixels = nullptr);
	TEX1D& operator = (TEX1D&&)noexcept ;
};
// TEX2D texture(GL_RGBA, 256, 256, nullptr)
// TEX2D texture(GL_RGBA, 256, 256, new RGBA[65536])
// texture.param(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
// texture.param(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
// texture.bind(GL_TEXTURE_0)
struct TEX2D : public TEX {
	void image(GLenum format, GLsizei width, GLsizei height, GLvoid * pixels);
	void resize(GLsizei width,
	            GLsizei height);
	~
	TEX2D(void);
	TEX2D(void);
	TEX2D(GLenum target, GLenum format, GLsizei width, 
	                                    GLsizei height, GLvoid * pixels = nullptr);
	TEX2D& operator = (TEX2D&&)noexcept ;
};
// TEX3D texture(GL_RGBA, 48, 48, nullptr)
// TEX3D texture(GL_RGBA, 48, 48, new RGBA[110592])
// texture.param(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
// texture.param(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
// texture.bind(GL_TEXTURE_0)
struct TEX3D : public TEX {
	void image(GLenum format, GLsizei width, GLsizei height, GLsizei depth, GLvoid * pixels);
	void resize(GLsizei width,
	            GLsizei height,
	            GLsizei depth);
	~
	TEX3D(void);
	TEX3D(void);
	TEX3D(GLenum target, GLenum format, GLsizei width,
	                                    GLsizei height,
	                                    GLsizei depth, GLvoid * pixels = nullptr);
	TEX3D& operator = (TEX3D&&)noexcept ;
};

# pragma once
# include "bo.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<GLenum> auto TEX(GLsizei, GLenum, GLsizei);
template<GLenum> auto TEX(GLenum, GLsizei, const GLint *);
template<GLenum> auto TEX(GLenum, GLsizei, const GLuint *);
template<GLenum> auto TEX(GLenum, GLsizei, const GLbyte *);
template<GLenum> auto TEX(GLenum, GLsizei, const GLubyte *);
template<GLenum> auto TEX(GLenum, GLsizei, const GLshort *);
template<GLenum> auto TEX(GLenum, GLsizei, const GLushort *);
template<GLenum> auto TEX(GLenum, GLsizei, const GLfloat *);
template<GLenum> auto TEX(GLenum, const BO<GL_TEXTURE_BUFFER> &);
template<GLenum> auto TEX(GLenum, const BO<GL_TEXTURE_BUFFER> &, GLintptr, GLsizeiptr);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TEX1D
{
	~
	TEX1D(void);
	TEX1D(void) = default;
	TEX1D(TEX1D &&) noexcept;
	void operator = (TEX1D &&) noexcept;
	TEX1D(GLenum format, GLsizei width, const GLbyte *image);
	TEX1D(GLenum format, GLsizei width, const GLubyte *image);
	TEX1D(GLenum format, GLsizei width, const GLshort *image);
	TEX1D(GLenum format, GLsizei width, const GLushort *image);
	TEX1D(GLenum format, GLsizei width, const GLint *image);
	TEX1D(GLenum format, GLsizei width, const GLuint *image);
	TEX1D(GLenum format, GLsizei width, const GLfloat *image);
	// ARB_texture_storage 4.2
	TEX1D(GLsizei levels, GLenum format, GLsizei width);
	
	void param(GLenum name, GLint param);

	void mipmap(void);

	void bind(GLenum = GL_TEXTURE0);
	
	void image(GLint level, GLsizei width, const GLbyte *);
	void image(GLint level, GLsizei width, const GLubyte *);
	void image(GLint level, GLsizei width, const GLshort *);
	void image(GLint level, GLsizei width, const GLushort *);
	void image(GLint level, GLsizei width, const GLint *);
	void image(GLint level, GLsizei width, const GLuint *);
	void image(GLint level, GLsizei width, const GLfloat *);

	void sub_image(GLint level, GLint x, GLsizei width, const GLbyte *);
	void sub_image(GLint level, GLint x, GLsizei width, const GLubyte *);
	void sub_image(GLint level, GLint x, GLsizei width, const GLshort *);
	void sub_image(GLint level, GLint x, GLsizei width, const GLushort *);
	void sub_image(GLint level, GLint x, GLsizei width, const GLint *);
	void sub_image(GLint level, GLint x, GLsizei width, const GLuint *);
	void sub_image(GLint level, GLint x, GLsizei width, const GLfloat *);

	operator GLuint(void) const;
private:
	friend class FBO;
	GLuint texture = 0;
	GLenum target = 0;
	GLint internalformat = 0;
	
	friend auto TEX<GL_TEXTURE_1D>(GLsizei, GLenum, GLsizei);
	friend auto TEX<GL_TEXTURE_1D>(GLenum, GLsizei, const GLint *);
	friend auto TEX<GL_TEXTURE_1D>(GLenum, GLsizei, const GLuint *);
	friend auto TEX<GL_TEXTURE_1D>(GLenum, GLsizei, const GLbyte *);
	friend auto TEX<GL_TEXTURE_1D>(GLenum, GLsizei, const GLubyte *);
	friend auto TEX<GL_TEXTURE_1D>(GLenum, GLsizei, const GLshort *);
	friend auto TEX<GL_TEXTURE_1D>(GLenum, GLsizei, const GLushort *);
	friend auto TEX<GL_TEXTURE_1D>(GLenum, GLsizei, const GLfloat *);
	// ARB_texture_buffer_object 3.1
	friend auto TEX<GL_TEXTURE_BUFFER>(GLenum, const BO<GL_TEXTURE_BUFFER> &);
	// ARB_texture_buffer_range 4.3
	friend auto TEX<GL_TEXTURE_BUFFER>(GLenum, const BO<GL_TEXTURE_BUFFER> &, GLintptr, GLsizeiptr);
	
	TEX1D(GLenum, GLenum, GLsizei, GLenum, GLenum, const void *);
	// ARB_texture_buffer_object 3.1
	TEX1D(GLenum, const BO<GL_TEXTURE_BUFFER> &);
	// ARB_texture_buffer_range 4.3
	TEX1D(GLenum, const BO<GL_TEXTURE_BUFFER> &, GLintptr, GLsizeiptr);
	// ARB_texture_storage 4.2
	TEX1D(GLenum, GLsizei, GLenum, GLsizei);
	// GL_TEXTURE_MIN_FILTER=GL_NEAREST
	// GL_TEXTURE_MAG_FILTER=GL_NEAREST
};
// ARB_texture_storage 4.2
template<GLenum target> auto TEX(GLsizei levels, GLenum format, GLsizei width)
{
	return TEX1D(target, levels, format, width);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, const GLbyte *image)
{
	return TEX1D(target, format, width, GL_BYTE, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, const GLubyte *image)
{
	return TEX1D(target, format, width, GL_UNSIGNED_BYTE, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, const GLshort *image)
{
	return TEX1D(target, format, width, GL_SHORT, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, const GLushort *image)
{
	return TEX1D(target, format, width, GL_UNSIGNED_SHORT, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, const GLint *image)
{
	return TEX1D(target, format, width, GL_INT, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, const GLuint *image)
{
	return TEX1D(target, format, width, GL_UNSIGNED_INT, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, const GLfloat *image)
{
	return TEX1D(target, format, width, GL_FLOAT, image);
}
// ARB_texture_buffer_object 3.1
template<GLenum target> auto TEX(GLenum format, const BO<GL_TEXTURE_BUFFER> &buffer)
{
	return TEX1D(target, format, buffer);
}
// ARB_texture_buffer_range 4.3
template<GLenum target> auto TEX(GLenum format, const BO<GL_TEXTURE_BUFFER> &buffer, GLintptr offset, GLsizeiptr size)
{
	return TEX1D(target, format, buffer, offset, size);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<GLenum> auto TEX(GLsizei, GLenum, GLsizei, GLsizei);
template<GLenum> auto TEX(GLenum, GLsizei, GLsizei, const GLbyte *);
template<GLenum> auto TEX(GLenum, GLsizei, GLsizei, const GLubyte *);
template<GLenum> auto TEX(GLenum, GLsizei, GLsizei, const GLshort *);
template<GLenum> auto TEX(GLenum, GLsizei, GLsizei, const GLushort *);
template<GLenum> auto TEX(GLenum, GLsizei, GLsizei, const GLint *);
template<GLenum> auto TEX(GLenum, GLsizei, GLsizei, const GLuint *);
template<GLenum> auto TEX(GLenum, GLsizei, GLsizei, const GLfloat *);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TEX2D
{
	~
	TEX2D(void);
	TEX2D(void) = default;
	TEX2D(TEX2D &&) noexcept;
	void operator = (TEX2D &&) noexcept;
	TEX2D(GLenum format, GLsizei width, GLsizei height, const GLbyte *image);
	TEX2D(GLenum format, GLsizei width, GLsizei height, const GLubyte *image);
	TEX2D(GLenum format, GLsizei width, GLsizei height, const GLshort *image);
	TEX2D(GLenum format, GLsizei width, GLsizei height, const GLushort *image);
	TEX2D(GLenum format, GLsizei width, GLsizei height, const GLint *image);
	TEX2D(GLenum format, GLsizei width, GLsizei height, const GLuint *image);
	TEX2D(GLenum format, GLsizei width, GLsizei height, const GLfloat *image);
	// ARB_texture_storage 4.2
	TEX2D(GLsizei levels, GLenum format, GLsizei width, GLsizei height);
	
	void param(GLenum name, GLint param);

	void mipmap(void);

	void bind(GLenum = GL_TEXTURE0);
	
	void image(GLint level, GLsizei width, GLsizei height, const GLbyte *pixels);
	void image(GLint level, GLsizei width, GLsizei height, const GLubyte *pixels);
	void image(GLint level, GLsizei width, GLsizei height, const GLshort *pixels);
	void image(GLint level, GLsizei width, GLsizei height, const GLushort *pixels);
	void image(GLint level, GLsizei width, GLsizei height, const GLint *pixels);
	void image(GLint level, GLsizei width, GLsizei height, const GLuint *pixels);
	void image(GLint level, GLsizei width, GLsizei height, const GLfloat *pixels);
	
	void sub_image(GLint level, GLint x, GLint y, GLsizei width, GLsizei height, const GLbyte *);
	void sub_image(GLint level, GLint x, GLint y, GLsizei width, GLsizei height, const GLubyte *);
	void sub_image(GLint level, GLint x, GLint y, GLsizei width, GLsizei height, const GLshort *);
	void sub_image(GLint level, GLint x, GLint y, GLsizei width, GLsizei height, const GLushort *);
	void sub_image(GLint level, GLint x, GLint y, GLsizei width, GLsizei height, const GLint *);
	void sub_image(GLint level, GLint x, GLint y, GLsizei width, GLsizei height, const GLuint *);
	void sub_image(GLint level, GLint x, GLint y, GLsizei width, GLsizei height, const GLfloat *);
	
	operator GLuint(void) const;
private:
	friend class FBO;
	GLuint texture = 0;
	GLenum target = 0;
	GLint internalformat = 0;
	
	friend auto TEX<GL_TEXTURE_2D>(GLsizei, GLenum, GLsizei, GLsizei);
	friend auto TEX<GL_TEXTURE_2D>(GLenum, GLsizei, GLsizei, const GLint *);
	friend auto TEX<GL_TEXTURE_2D>(GLenum, GLsizei, GLsizei, const GLuint *);
	friend auto TEX<GL_TEXTURE_2D>(GLenum, GLsizei, GLsizei, const GLbyte *);
	friend auto TEX<GL_TEXTURE_2D>(GLenum, GLsizei, GLsizei, const GLubyte *);
	friend auto TEX<GL_TEXTURE_2D>(GLenum, GLsizei, GLsizei, const GLshort *);
	friend auto TEX<GL_TEXTURE_2D>(GLenum, GLsizei, GLsizei, const GLushort *);
	friend auto TEX<GL_TEXTURE_2D>(GLenum, GLsizei, GLsizei, const GLfloat *);
	// EXT_texture_array 3.0
	friend auto TEX<GL_TEXTURE_1D_ARRAY>(GLsizei, GLenum, GLsizei, GLsizei);
	friend auto TEX<GL_TEXTURE_1D_ARRAY>(GLenum, GLsizei, GLsizei, const GLint *);
	friend auto TEX<GL_TEXTURE_1D_ARRAY>(GLenum, GLsizei, GLsizei, const GLuint *);
	friend auto TEX<GL_TEXTURE_1D_ARRAY>(GLenum, GLsizei, GLsizei, const GLbyte *);
	friend auto TEX<GL_TEXTURE_1D_ARRAY>(GLenum, GLsizei, GLsizei, const GLubyte *);
	friend auto TEX<GL_TEXTURE_1D_ARRAY>(GLenum, GLsizei, GLsizei, const GLshort *);
	friend auto TEX<GL_TEXTURE_1D_ARRAY>(GLenum, GLsizei, GLsizei, const GLushort *);
	friend auto TEX<GL_TEXTURE_1D_ARRAY>(GLenum, GLsizei, GLsizei, const GLfloat *);
	// ARB_texture_rectangle 3.1
	friend auto TEX<GL_TEXTURE_RECTANGLE>(GLsizei, GLenum, GLsizei, GLsizei);
	friend auto TEX<GL_TEXTURE_RECTANGLE>(GLenum, GLsizei, GLsizei, const GLint *);
	friend auto TEX<GL_TEXTURE_RECTANGLE>(GLenum, GLsizei, GLsizei, const GLuint *);
	friend auto TEX<GL_TEXTURE_RECTANGLE>(GLenum, GLsizei, GLsizei, const GLbyte *);
	friend auto TEX<GL_TEXTURE_RECTANGLE>(GLenum, GLsizei, GLsizei, const GLubyte *);
	friend auto TEX<GL_TEXTURE_RECTANGLE>(GLenum, GLsizei, GLsizei, const GLshort *);
	friend auto TEX<GL_TEXTURE_RECTANGLE>(GLenum, GLsizei, GLsizei, const GLushort *);
	friend auto TEX<GL_TEXTURE_RECTANGLE>(GLenum, GLsizei, GLsizei, const GLfloat *);
	// GL_ARB_texture_multisample 3.2
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE>(GLsizei, GLenum, GLsizei, GLsizei);
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE>(GLenum, GLsizei, GLsizei, const GLint *);
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE>(GLenum, GLsizei, GLsizei, const GLuint *);
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE>(GLenum, GLsizei, GLsizei, const GLbyte *);
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE>(GLenum, GLsizei, GLsizei, const GLubyte *);
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE>(GLenum, GLsizei, GLsizei, const GLshort *);
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE>(GLenum, GLsizei, GLsizei, const GLushort *);
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE>(GLenum, GLsizei, GLsizei, const GLfloat *);

	TEX2D(GLenum, GLsizei, GLenum, GLsizei, GLsizei); // storage
	TEX2D(GLenum, GLenum, GLsizei, GLsizei, GLenum, const void *); // image
	// GL_TEXTURE_MIN_FILTER=GL_NEAREST
	// GL_TEXTURE_MAG_FILTER=GL_NEAREST
};
// ARB_texture_storage 4.2
template<GLenum target> auto TEX(GLsizei levels, GLenum format, GLsizei width, GLsizei height)
{
	return TEX2D(target, levels, format, width, height);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, GLsizei height, const GLbyte *image)
{
	return TEX2D(target, format, width, height, GL_BYTE, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, GLsizei height, const GLubyte *image)
{
	return TEX2D(target, format, width, height, GL_UNSIGNED_BYTE, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, GLsizei height, const GLshort *image)
{
	return TEX2D(target, format, width, height, GL_SHORT, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, GLsizei height, const GLushort *image)
{
	return TEX2D(target, format, width, height, GL_UNSIGNED_SHORT, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, GLsizei height, const GLint *image)
{
	return TEX2D(target, format, width, height, GL_INT, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, GLsizei height, const GLuint *image)
{
	return TEX2D(target, format, width, height, GL_UNSIGNED_INT, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, GLsizei height, const GLfloat *image)
{
	return TEX2D(target, format, width, height, GL_FLOAT, image);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARB_seamless_cube_map 3.2
// glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<GLenum> auto TEX(GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
template<GLenum> auto TEX(GLenum, GLsizei, GLsizei, GLsizei, const GLbyte *);
template<GLenum> auto TEX(GLenum, GLsizei, GLsizei, GLsizei, const GLubyte *);
template<GLenum> auto TEX(GLenum, GLsizei, GLsizei, GLsizei, const GLshort *);
template<GLenum> auto TEX(GLenum, GLsizei, GLsizei, GLsizei, const GLushort *);
template<GLenum> auto TEX(GLenum, GLsizei, GLsizei, GLsizei, const GLint *);
template<GLenum> auto TEX(GLenum, GLsizei, GLsizei, GLsizei, const GLuint *);
template<GLenum> auto TEX(GLenum, GLsizei, GLsizei, GLsizei, const GLfloat *);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TEX3D
{
	~
	TEX3D(void);
	TEX3D(void) = default;
	TEX3D(TEX3D &&) noexcept;
	void operator = (TEX3D &&) noexcept;
	TEX3D(GLenum format, GLsizei width, GLsizei height, GLsizei depth, const GLbyte *image);
	TEX3D(GLenum format, GLsizei width, GLsizei height, GLsizei depth, const GLubyte *image);
	TEX3D(GLenum format, GLsizei width, GLsizei height, GLsizei depth, const GLshort *image);
	TEX3D(GLenum format, GLsizei width, GLsizei height, GLsizei depth, const GLushort *image);
	TEX3D(GLenum format, GLsizei width, GLsizei height, GLsizei depth, const GLint *image);
	TEX3D(GLenum format, GLsizei width, GLsizei height, GLsizei depth, const GLuint *image);
	TEX3D(GLenum format, GLsizei width, GLsizei height, GLsizei depth, const GLfloat *image);
	// ARB_texture_storage 4.2
	TEX3D(GLsizei levels, GLenum format, GLsizei width, GLsizei height, GLsizei depth);
	
	void param(GLenum name, GLint param);

	void mipmap(void);

	void bind(GLenum = GL_TEXTURE0);

	void image(GLint level, GLsizei width, GLsizei height, GLsizei depth, const GLbyte *);
	void image(GLint level, GLsizei width, GLsizei height, GLsizei depth, const GLubyte *);
	void image(GLint level, GLsizei width, GLsizei height, GLsizei depth, const GLshort *);
	void image(GLint level, GLsizei width, GLsizei height, GLsizei depth, const GLushort *);
	void image(GLint level, GLsizei width, GLsizei height, GLsizei depth, const GLint *);
	void image(GLint level, GLsizei width, GLsizei height, GLsizei depth, const GLuint *);
	void image(GLint level, GLsizei width, GLsizei height, GLsizei depth, const GLfloat *);

	void sub_image(GLint level, GLint x, GLint y, GLint z, GLsizei width, GLsizei height, GLsizei depth, const GLbyte *);
	void sub_image(GLint level, GLint x, GLint y, GLint z, GLsizei width, GLsizei height, GLsizei depth, const GLubyte *);
	void sub_image(GLint level, GLint x, GLint y, GLint z, GLsizei width, GLsizei height, GLsizei depth, const GLshort *);
	void sub_image(GLint level, GLint x, GLint y, GLint z, GLsizei width, GLsizei height, GLsizei depth, const GLushort *);
	void sub_image(GLint level, GLint x, GLint y, GLint z, GLsizei width, GLsizei height, GLsizei depth, const GLint *);
	void sub_image(GLint level, GLint x, GLint y, GLint z, GLsizei width, GLsizei height, GLsizei depth, const GLuint *);
	void sub_image(GLint level, GLint x, GLint y, GLint z, GLsizei width, GLsizei height, GLsizei depth, const GLfloat *);

	operator GLuint(void) const;
private:
	friend class FBO;
	GLuint texture = 0;
	GLenum target = 0;
	GLenum internalformat = 0;
	
	friend auto TEX<GL_TEXTURE_3D>(GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
	friend auto TEX<GL_TEXTURE_3D>(GLenum, GLsizei, GLsizei, GLsizei, const GLint *);
	friend auto TEX<GL_TEXTURE_3D>(GLenum, GLsizei, GLsizei, GLsizei, const GLuint *);
	friend auto TEX<GL_TEXTURE_3D>(GLenum, GLsizei, GLsizei, GLsizei, const GLbyte *);
	friend auto TEX<GL_TEXTURE_3D>(GLenum, GLsizei, GLsizei, GLsizei, const GLubyte *);
	friend auto TEX<GL_TEXTURE_3D>(GLenum, GLsizei, GLsizei, GLsizei, const GLshort *);
	friend auto TEX<GL_TEXTURE_3D>(GLenum, GLsizei, GLsizei, GLsizei, const GLushort *);
	friend auto TEX<GL_TEXTURE_3D>(GLenum, GLsizei, GLsizei, GLsizei, const GLfloat *);
	// ARB_texture_cube_map 1.3
	friend auto TEX<GL_TEXTURE_CUBE_MAP>(GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
	friend auto TEX<GL_TEXTURE_CUBE_MAP>(GLenum, GLsizei, GLsizei, GLsizei, const GLint *);
	friend auto TEX<GL_TEXTURE_CUBE_MAP>(GLenum, GLsizei, GLsizei, GLsizei, const GLuint *);
	friend auto TEX<GL_TEXTURE_CUBE_MAP>(GLenum, GLsizei, GLsizei, GLsizei, const GLbyte *);
	friend auto TEX<GL_TEXTURE_CUBE_MAP>(GLenum, GLsizei, GLsizei, GLsizei, const GLubyte *);
	friend auto TEX<GL_TEXTURE_CUBE_MAP>(GLenum, GLsizei, GLsizei, GLsizei, const GLshort *);
	friend auto TEX<GL_TEXTURE_CUBE_MAP>(GLenum, GLsizei, GLsizei, GLsizei, const GLushort *);
	friend auto TEX<GL_TEXTURE_CUBE_MAP>(GLenum, GLsizei, GLsizei, GLsizei, const GLfloat *);
	// EXT_texture_array 3.0
	friend auto TEX<GL_TEXTURE_2D_ARRAY>(GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
	friend auto TEX<GL_TEXTURE_2D_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLint *);
	friend auto TEX<GL_TEXTURE_2D_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLuint *);
	friend auto TEX<GL_TEXTURE_2D_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLbyte *);
	friend auto TEX<GL_TEXTURE_2D_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLubyte *);
	friend auto TEX<GL_TEXTURE_2D_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLshort *);
	friend auto TEX<GL_TEXTURE_2D_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLushort *);
	friend auto TEX<GL_TEXTURE_2D_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLfloat *);
	// GL_ARB_texture_multisample 3.2
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE_ARRAY>(GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLint *);
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLuint *);
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLbyte *);
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLubyte *);
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLshort *);
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLushort *);
	friend auto TEX<GL_TEXTURE_2D_MULTISAMPLE_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLfloat *);
	// ARB_texture_cube_map_array 4.0
	friend auto TEX<GL_TEXTURE_CUBE_MAP_ARRAY>(GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
	friend auto TEX<GL_TEXTURE_CUBE_MAP_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLint *);
	friend auto TEX<GL_TEXTURE_CUBE_MAP_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLuint *);
	friend auto TEX<GL_TEXTURE_CUBE_MAP_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLbyte *);
	friend auto TEX<GL_TEXTURE_CUBE_MAP_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLubyte *);
	friend auto TEX<GL_TEXTURE_CUBE_MAP_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLshort *);
	friend auto TEX<GL_TEXTURE_CUBE_MAP_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLushort *);
	friend auto TEX<GL_TEXTURE_CUBE_MAP_ARRAY>(GLenum, GLsizei, GLsizei, GLsizei, const GLfloat *);

	TEX3D(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei); // storage
	TEX3D(GLenum, GLenum, GLsizei, GLsizei, GLsizei, GLenum, const void *); // image
	// GL_TEXTURE_MIN_FILTER=GL_NEAREST
	// GL_TEXTURE_MAG_FILTER=GL_NEAREST
};
// ARB_texture_storage 4.2
template<GLenum target> auto TEX(GLsizei levels, GLenum format, GLsizei width, GLsizei height, GLsizei depth)
{
	return TEX3D(target, levels, format, width, height, depth);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, GLsizei height, GLsizei depth, const GLbyte *image)
{
	return TEX3D(target, format, width, height, depth, GL_BYTE, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, GLsizei height, GLsizei depth, const GLubyte *image)
{
	return TEX3D(target, format, width, height, depth, GL_UNSIGNED_BYTE, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, GLsizei height, GLsizei depth, const GLshort *image)
{
	return TEX3D(target, format, width, height, depth, GL_SHORT, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, GLsizei height, GLsizei depth, const GLushort *image)
{
	return TEX3D(target, format, width, height, depth, GL_UNSIGNED_SHORT, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, GLsizei height, GLsizei depth, const GLint *image)
{
	return TEX3D(target, format, width, height, depth, GL_INT, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, GLsizei height, GLsizei depth, const GLuint *image)
{
	return TEX3D(target, format, width, height, depth, GL_UNSIGNED_INT, image);
}
template<GLenum target> auto TEX(GLenum format, GLsizei width, GLsizei height, GLsizei depth, const GLfloat *image)
{
	return TEX3D(target, format, width, height, depth, GL_FLOAT, image);
}
////////////////////////////////////////////////////////////////////////////////////////////

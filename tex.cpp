# include "tex.h"
constexpr GLenum GL_TEXTURE_BINDING(GLenum target)
{
	switch(target)
	{
		case GL_TEXTURE_1D:			return GL_TEXTURE_BINDING_1D ;
		case GL_TEXTURE_2D:			return GL_TEXTURE_BINDING_2D ;
		case GL_TEXTURE_3D:			return GL_TEXTURE_BINDING_3D ;
		case GL_TEXTURE_1D_ARRAY:		return GL_TEXTURE_BINDING_1D_ARRAY ;
		case GL_TEXTURE_2D_ARRAY:		return GL_TEXTURE_BINDING_2D_ARRAY ;
		case GL_TEXTURE_CUBE_MAP:		return GL_TEXTURE_BINDING_CUBE_MAP ;
		case GL_TEXTURE_CUBE_MAP_ARRAY:		return GL_TEXTURE_BINDING_CUBE_MAP_ARRAY ;
		case GL_TEXTURE_RECTANGLE:		return GL_TEXTURE_BINDING_RECTANGLE ;
		case GL_TEXTURE_2D_MULTISAMPLE:		return GL_TEXTURE_BINDING_2D_MULTISAMPLE ;
		case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:	return GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY ;
		case GL_TEXTURE_BUFFER:			return GL_TEXTURE_BINDING_BUFFER ;
		default:				return 0 ; // error
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
constexpr GLenum GLformat(GLenum internalformat)
{
	switch(internalformat)
	{
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
			return internalformat;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEX1D::~TEX1D(void)
{
	if(texture) GL_ASSERT(glDeleteTextures(1, &texture)), texture = 0;
}
TEX1D::TEX1D(TEX1D &&TEX) noexcept
{
	memcpy(this, &TEX, sizeof(TEX1D));
	memset(&TEX, 0, sizeof(TEX1D));
}
void TEX1D::operator = (TEX1D &&TEX) noexcept
{
	TEX1D::~TEX1D( );
	memcpy(this, &TEX, sizeof(TEX1D));
	memset(&TEX, 0, sizeof(TEX1D));
}
TEX1D::TEX1D(GLenum format, GLsizei X, const GLbyte   *image): TEX1D(GL_TEXTURE_1D, format, X, GLformat(format), GL_BYTE, image) { }
TEX1D::TEX1D(GLenum format, GLsizei X, const GLubyte  *image): TEX1D(GL_TEXTURE_1D, format, X, GLformat(format), GL_UNSIGNED_BYTE, image) { }
TEX1D::TEX1D(GLenum format, GLsizei X, const GLshort  *image): TEX1D(GL_TEXTURE_1D, format, X, GLformat(format), GL_SHORT, image) { }
TEX1D::TEX1D(GLenum format, GLsizei X, const GLushort *image): TEX1D(GL_TEXTURE_1D, format, X, GLformat(format), GL_UNSIGNED_SHORT, image) { }
TEX1D::TEX1D(GLenum format, GLsizei X, const GLint    *image): TEX1D(GL_TEXTURE_1D, format, X, GLformat(format), GL_INT, image) { }
TEX1D::TEX1D(GLenum format, GLsizei X, const GLuint   *image): TEX1D(GL_TEXTURE_1D, format, X, GLformat(format), GL_UNSIGNED_INT, image) { }
TEX1D::TEX1D(GLenum format, GLsizei X, const GLfloat  *image): TEX1D(GL_TEXTURE_1D, format, X, GLformat(format), GL_FLOAT, image) { }
// ARB_texture_storage 4.2
TEX1D::TEX1D(GLsizei levels, GLenum format, GLsizei X): TEX1D(GL_TEXTURE_1D, levels, format, X) { }
// glTexParameter
void TEX1D::param(GLenum pname, GLint param)
{
	if(ASSERT(texture))
	GL_ASSERT(glTexParameteri(target, pname, param));
}
// glGenerateMipmap
void TEX1D::mipmap(void)
{
	if(ASSERT(texture))
	if(ASSERT(target != GL_TEXTURE_BUFFER))
	GL_ASSERT(glBindTexture(target, texture)),
	GL_ASSERT(glGenerateMipmap(target));
}
// glBindTexture
void TEX1D::bind(GLenum unit)
{
	if(!ASSERT(texture)) return;
	if(gl_Version < 045)
	 GL_ASSERT(glActiveTexture(unit)),
	 GL_ASSERT(glBindTexture(target, texture));
	else // ARB_direct_state_access 4.5
	 GL_ASSERT(glBindTextureUnit(unit, texture));
}
// glTexImage1D
void TEX1D::image(GLint level, GLsizei width, const GLbyte *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexImage1D(target, level, internalformat, width, 0, GLformat(internalformat), GL_BYTE, image));
}
void TEX1D::image(GLint level, GLsizei width, const GLubyte *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexImage1D(target, level, internalformat, width, 0, GLformat(internalformat), GL_UNSIGNED_BYTE, image));
}
void TEX1D::image(GLint level, GLsizei width, const GLshort *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexImage1D(target, level, internalformat, width, 0, GLformat(internalformat), GL_SHORT, image));
}
void TEX1D::image(GLint level, GLsizei width, const GLushort *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexImage1D(target, level, internalformat, width, 0, GLformat(internalformat), GL_UNSIGNED_SHORT, image));
}
void TEX1D::image(GLint level, GLsizei width, const GLint *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexImage1D(target, level, internalformat, width, 0, GLformat(internalformat), GL_INT, image));
}
void TEX1D::image(GLint level, GLsizei width, const GLuint *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexImage1D(target, level, internalformat, width, 0, GLformat(internalformat), GL_UNSIGNED_INT, image));
}
void TEX1D::image(GLint level, GLsizei width, const GLfloat *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexImage1D(target, level, internalformat, width, 0, GLformat(internalformat), GL_FLOAT, image));
}
// glTexSubImage1D
void TEX1D::sub_image(GLint level, GLint x, GLsizei width, const GLbyte *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexSubImage1D(target, level, x, width, GLformat(internalformat), GL_BYTE, image));
}
void TEX1D::sub_image(GLint level, GLint x, GLsizei width, const GLubyte *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexSubImage1D(target, level, x, width, GLformat(internalformat), GL_UNSIGNED_BYTE, image));
}
void TEX1D::sub_image(GLint level, GLint x, GLsizei width, const GLshort *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexSubImage1D(target, level, x, width, GLformat(internalformat), GL_SHORT, image));
}
void TEX1D::sub_image(GLint level, GLint x, GLsizei width, const GLushort *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexSubImage1D(target, level, x, width, GLformat(internalformat), GL_UNSIGNED_SHORT, image));
}
void TEX1D::sub_image(GLint level, GLint x, GLsizei width, const GLint *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexSubImage1D(target, level, x, width, GLformat(internalformat), GL_INT, image));
}
void TEX1D::sub_image(GLint level, GLint x, GLsizei width, const GLuint *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexSubImage1D(target, level, x, width, GLformat(internalformat), GL_UNSIGNED_INT, image));
}
void TEX1D::sub_image(GLint level, GLint x, GLsizei width, const GLfloat *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexSubImage1D(target, level, x, width, GLformat(internalformat), GL_FLOAT, image));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEX1D::TEX1D(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void *image): target(target), internalformat(internalformat)
{
	if(GL_ASSERT(glGenTextures(1, &texture)))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexImage1D(target, 0, internalformat, width, 0, format, type, image));
}
// ARB_texture_buffer_object 3.1
TEX1D::TEX1D(GLenum internalformat, const BO<GL_TEXTURE_BUFFER> &buffer): target(GL_TEXTURE_BUFFER), internalformat(internalformat)
{
	if(GL_ASSERT(glGenTextures(1, &texture)))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexBuffer(target, internalformat, buffer));
}
// ARB_texture_buffer_range 4.3
TEX1D::TEX1D(GLenum internalformat, const BO<GL_TEXTURE_BUFFER> &buffer, GLintptr offset, GLsizeiptr size): target(GL_TEXTURE_BUFFER), internalformat(internalformat)
{
	if(GL_ASSERT(glGenTextures(1, &texture)))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(GL_ASSERT(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST)))
	if(GL_ASSERT(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST)))
	   GL_ASSERT(glTexBufferRange(target, internalformat, buffer, offset, size));
}
// ARB_texture_storage 4.2
TEX1D::TEX1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width): target(target), internalformat(internalformat)
{
	if(GL_ASSERT(glGenTextures(1, &texture)))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(GL_ASSERT(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST)))
	if(GL_ASSERT(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST)))
	   GL_ASSERT(glTexStorage1D(target, levels, internalformat, width));
}
TEX1D::operator GLuint(void) const
{
	return texture;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEX2D::~TEX2D(void)
{
	if(texture) GL_ASSERT(glDeleteTextures(1, &texture)), texture = 0;
}
TEX2D::TEX2D(TEX2D &&TEX) noexcept
{
	memcpy(this, &TEX, sizeof(TEX2D));
	memset(&TEX, 0, sizeof(TEX2D));
}
void TEX2D::operator = (TEX2D &&TEX) noexcept
{
	TEX2D::~TEX2D( );
	memcpy(this, &TEX, sizeof(TEX2D));
	memset(&TEX, 0, sizeof(TEX2D));
}
TEX2D::TEX2D(GLenum internalformat, GLsizei X, GLsizei Y, const GLbyte *image): TEX2D(GL_TEXTURE_2D, internalformat, X, Y, GL_BYTE, image) { }
TEX2D::TEX2D(GLenum internalformat, GLsizei X, GLsizei Y, const GLubyte *image): TEX2D(GL_TEXTURE_2D, internalformat, X, Y, GL_UNSIGNED_BYTE, image) { }
TEX2D::TEX2D(GLenum internalformat, GLsizei X, GLsizei Y, const GLshort *image): TEX2D(GL_TEXTURE_2D, internalformat, X, Y, GL_SHORT, image) { }
TEX2D::TEX2D(GLenum internalformat, GLsizei X, GLsizei Y, const GLushort *image): TEX2D(GL_TEXTURE_2D, internalformat, X, Y, GL_UNSIGNED_SHORT, image) { }
TEX2D::TEX2D(GLenum internalformat, GLsizei X, GLsizei Y, const GLint *image): TEX2D(GL_TEXTURE_2D, internalformat, X, Y, GL_INT, image) { }
TEX2D::TEX2D(GLenum internalformat, GLsizei X, GLsizei Y, const GLuint *image): TEX2D(GL_TEXTURE_2D, internalformat, X, Y, GL_UNSIGNED_INT, image) { }
TEX2D::TEX2D(GLenum internalformat, GLsizei X, GLsizei Y, const GLfloat *image): TEX2D(GL_TEXTURE_2D, internalformat, X, Y, GL_FLOAT, image) { }
// ARB_texture_storage 4.2
TEX2D::TEX2D(GLsizei levels, GLenum format, GLsizei X, GLsizei Y): TEX2D(GL_TEXTURE_2D, levels, internalformat, X, Y) { }
// glTexParameter
void TEX2D::param(GLenum pname, GLint param)
{
	if(ASSERT(texture))
	GL_ASSERT(glTexParameteri(target, pname, param));
}
// glGenerateMipmap
void TEX2D::mipmap(void)
{
	if(ASSERT(texture))
	if(ASSERT(target != GL_TEXTURE_RECTANGLE))
	if(ASSERT(target != GL_TEXTURE_2D_MULTISAMPLE))
	GL_ASSERT(glBindTexture(target, texture)),
	GL_ASSERT(glGenerateMipmap(target));
}
// glBindTexture
void TEX2D::bind(GLenum unit)
{
	if(!ASSERT(texture)) return;
	if(gl_Version < 045)
	 GL_ASSERT(glActiveTexture(unit)),
	 GL_ASSERT(glBindTexture(target, texture));
	else // ARB_direct_state_access 4.5
	 GL_ASSERT(glBindTextureUnit(unit, texture));
}
// glTexImage2D
void TEX2D::image(GLint level, GLsizei width, GLsizei height, const GLbyte *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexImage2D(target, level, internalformat, width, height, 0, GLformat(internalformat), GL_BYTE, image));
}
void TEX2D::image(GLint level, GLsizei width, GLsizei height, const GLubyte *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexImage2D(target, level, internalformat, width, height, 0, GLformat(internalformat), GL_UNSIGNED_BYTE, image));
}
void TEX2D::image(GLint level, GLsizei width, GLsizei height, const GLshort *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexImage2D(target, level, internalformat, width, height, 0, GLformat(internalformat), GL_SHORT, image));
}
void TEX2D::image(GLint level, GLsizei width, GLsizei height, const GLushort *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexImage2D(target, level, internalformat, width, height, 0, GLformat(internalformat), GL_UNSIGNED_SHORT, image));
}
void TEX2D::image(GLint level, GLsizei width, GLsizei height, const GLint *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexImage2D(target, level, internalformat, width, height, 0, GLformat(internalformat), GL_INT, image));
}
void TEX2D::image(GLint level, GLsizei width, GLsizei height, const GLuint *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexImage2D(target, level, internalformat, width, height, 0, GLformat(internalformat), GL_UNSIGNED_INT, image));
}
void TEX2D::image(GLint level, GLsizei width, GLsizei height, const GLfloat *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexImage2D(target, level, internalformat, width, height, 0, GLformat(internalformat), GL_FLOAT, image));
}
// glTexSubImage2D
void TEX2D::sub_image(GLint level, GLint x, GLint y, GLsizei width, GLsizei height, const GLbyte *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexSubImage2D(target, level, x, y, width, height, GLformat(internalformat), GL_BYTE, image));
}
void TEX2D::sub_image(GLint level, GLint x, GLint y, GLsizei width, GLsizei height, const GLubyte *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexSubImage2D(target, level, x, y, width, height, GLformat(internalformat), GL_UNSIGNED_BYTE, image));
}
void TEX2D::sub_image(GLint level, GLint x, GLint y, GLsizei width, GLsizei height, const GLshort *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexSubImage2D(target, level, x, y, width, height, GLformat(internalformat), GL_SHORT, image));
}
void TEX2D::sub_image(GLint level, GLint x, GLint y, GLsizei width, GLsizei height, const GLushort *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexSubImage2D(target, level, x, y, width, height, GLformat(internalformat), GL_UNSIGNED_SHORT, image));
}
void TEX2D::sub_image(GLint level, GLint x, GLint y, GLsizei width, GLsizei height, const GLfloat *image)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	   GL_ASSERT(glTexSubImage2D(target, level, x, y, width, height, GLformat(internalformat), GL_FLOAT, image));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ARB_texture_storage 4.2
TEX2D::TEX2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height): target(target), internalformat(internalformat)
{
	if(GL_ASSERT(glGenTextures(1, &texture)))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(GL_ASSERT(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST)))
	if(GL_ASSERT(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST)))
	   GL_ASSERT(glTexStorage2D(target, levels, internalformat, width, height));
}
TEX2D::TEX2D(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum type, const void *pixels): target(target), internalformat(internalformat)
{
	if(GL_ASSERT(glGenTextures(1, &texture)))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(GL_ASSERT(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST)))
	if(GL_ASSERT(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST)))
	   GL_ASSERT(glTexImage2D(target, 0, internalformat, width, height, 0, GLformat(internalformat), type, pixels));
}
TEX2D::operator GLuint(void) const
{
	return texture;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEX3D::~TEX3D(void)
{
	if(texture) GL_ASSERT(glDeleteTextures(1, &texture)), texture = 0;
}
TEX3D::TEX3D(TEX3D &&TEX) noexcept
{
	memcpy(this, &TEX, sizeof(TEX3D));
	memset(&TEX, 0, sizeof(TEX3D));
}
void TEX3D::operator = (TEX3D &&TEX) noexcept
{
	TEX3D::~TEX3D( );
	memcpy(this, &TEX, sizeof(TEX3D));
	memset(&TEX, 0, sizeof(TEX3D));
}
TEX3D::TEX3D(GLenum format, GLsizei X, GLsizei Y, GLsizei Z, const GLbyte   *image): TEX3D(GL_TEXTURE_3D, format, X, Y, Z, GL_BYTE, image) { }
TEX3D::TEX3D(GLenum format, GLsizei X, GLsizei Y, GLsizei Z, const GLubyte  *image): TEX3D(GL_TEXTURE_3D, format, X, Y, Z, GL_UNSIGNED_BYTE, image) { }
TEX3D::TEX3D(GLenum format, GLsizei X, GLsizei Y, GLsizei Z, const GLshort  *image): TEX3D(GL_TEXTURE_3D, format, X, Y, Z, GL_SHORT, image) { }
TEX3D::TEX3D(GLenum format, GLsizei X, GLsizei Y, GLsizei Z, const GLushort *image): TEX3D(GL_TEXTURE_3D, format, X, Y, Z, GL_UNSIGNED_SHORT, image) { }
TEX3D::TEX3D(GLenum format, GLsizei X, GLsizei Y, GLsizei Z, const GLint    *image): TEX3D(GL_TEXTURE_3D, format, X, Y, Z, GL_INT, image) { }
TEX3D::TEX3D(GLenum format, GLsizei X, GLsizei Y, GLsizei Z, const GLuint   *image): TEX3D(GL_TEXTURE_3D, format, X, Y, Z, GL_UNSIGNED_INT, image) { }
TEX3D::TEX3D(GLenum format, GLsizei X, GLsizei Y, GLsizei Z, const GLfloat  *image): TEX3D(GL_TEXTURE_3D, format, X, Y, Z, GL_FLOAT, image) { }
// ARB_texture_storage 4.2
TEX3D::TEX3D(GLsizei levels, GLenum format, GLsizei X, GLsizei Y, GLsizei Z): TEX3D(GL_TEXTURE_3D, levels, format, X, Y, Z) { }
// glTexParameter
void TEX3D::param(GLenum pname, GLint param)
{
	if(ASSERT(texture))
	GL_ASSERT(glTexParameteri(target, pname, param));
}
// glGenerateMipmap
void TEX3D::mipmap(void)
{
	if(ASSERT(texture))
	if(ASSERT(target != GL_TEXTURE_2D_MULTISAMPLE_ARRAY))
	GL_ASSERT(glBindTexture(target, texture)),
	GL_ASSERT(glGenerateMipmap(target));
}
// glBindTexture
void TEX3D::bind(GLenum unit)
{
	if(!ASSERT(texture)) return;
	if(gl_Version < 045)
	 GL_ASSERT(glActiveTexture(unit)),
	 GL_ASSERT(glBindTexture(target, texture));
	else // ARB_direct_state_access 4.5
	 GL_ASSERT(glBindTextureUnit(unit, texture));
}
// glTexImage3D
void TEX3D::image(GLint level, GLsizei X, GLsizei Y, GLsizei Z, const GLbyte *pixels)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(target == GL_TEXTURE_CUBE_MAP && ASSERT(Z == 6))
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, internalformat, X, Y, 0, GLformat(internalformat), GL_BYTE, pixels + X * Y * 0)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, internalformat, X, Y, 0, GLformat(internalformat), GL_BYTE, pixels + X * Y * 1)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, internalformat, X, Y, 0, GLformat(internalformat), GL_BYTE, pixels + X * Y * 2)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, internalformat, X, Y, 0, GLformat(internalformat), GL_BYTE, pixels + X * Y * 3)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, internalformat, X, Y, 0, GLformat(internalformat), GL_BYTE, pixels + X * Y * 4)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, internalformat, X, Y, 0, GLformat(internalformat), GL_BYTE, pixels + X * Y * 5));
	else
	   GL_ASSERT(glTexImage3D(target, level, internalformat, X, Y, Z, 0, GLformat(internalformat), GL_BYTE, pixels));
}
void TEX3D::image(GLint level, GLsizei X, GLsizei Y, GLsizei Z, const GLubyte *pixels)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(target == GL_TEXTURE_CUBE_MAP && ASSERT(Z == 6))
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_BYTE, pixels + X * Y * 0)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_BYTE, pixels + X * Y * 1)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_BYTE, pixels + X * Y * 2)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_BYTE, pixels + X * Y * 3)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_BYTE, pixels + X * Y * 4)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_BYTE, pixels + X * Y * 5));
	else
	   GL_ASSERT(glTexImage3D(target, level, internalformat, X, Y, Z, 0, GLformat(internalformat), GL_UNSIGNED_BYTE, pixels));
}
void TEX3D::image(GLint level, GLsizei X, GLsizei Y, GLsizei Z, const GLshort *pixels)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(target == GL_TEXTURE_CUBE_MAP && ASSERT(Z == 6))
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, internalformat, X, Y, 0, GLformat(internalformat), GL_SHORT, pixels + X * Y * 0)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, internalformat, X, Y, 0, GLformat(internalformat), GL_SHORT, pixels + X * Y * 1)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, internalformat, X, Y, 0, GLformat(internalformat), GL_SHORT, pixels + X * Y * 2)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, internalformat, X, Y, 0, GLformat(internalformat), GL_SHORT, pixels + X * Y * 3)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, internalformat, X, Y, 0, GLformat(internalformat), GL_SHORT, pixels + X * Y * 4)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, internalformat, X, Y, 0, GLformat(internalformat), GL_SHORT, pixels + X * Y * 5));
	else
	   GL_ASSERT(glTexImage3D(target, level, internalformat, X, Y, Z, 0, GLformat(internalformat), GL_SHORT, pixels));
}
void TEX3D::image(GLint level, GLsizei X, GLsizei Y, GLsizei Z, const GLushort *pixels)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(target == GL_TEXTURE_CUBE_MAP && ASSERT(Z == 6))
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_SHORT, pixels + X * Y * 0)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_SHORT, pixels + X * Y * 1)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_SHORT, pixels + X * Y * 2)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_SHORT, pixels + X * Y * 3)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_SHORT, pixels + X * Y * 4)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_SHORT, pixels + X * Y * 5));
	else
	   GL_ASSERT(glTexImage3D(target, level, internalformat, X, Y, Z, 0, GLformat(internalformat), GL_UNSIGNED_SHORT, pixels));
}
void TEX3D::image(GLint level, GLsizei X, GLsizei Y, GLsizei Z, const GLint *pixels)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(target == GL_TEXTURE_CUBE_MAP && ASSERT(Z == 6))
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, internalformat, X, Y, 0, GLformat(internalformat), GL_INT, pixels + X * Y * 0)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, internalformat, X, Y, 0, GLformat(internalformat), GL_INT, pixels + X * Y * 1)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, internalformat, X, Y, 0, GLformat(internalformat), GL_INT, pixels + X * Y * 2)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, internalformat, X, Y, 0, GLformat(internalformat), GL_INT, pixels + X * Y * 3)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, internalformat, X, Y, 0, GLformat(internalformat), GL_INT, pixels + X * Y * 4)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, internalformat, X, Y, 0, GLformat(internalformat), GL_INT, pixels + X * Y * 5));
	else
	   GL_ASSERT(glTexImage3D(target, level, internalformat, X, Y, Z, 0, GLformat(internalformat), GL_INT, pixels));
}
void TEX3D::image(GLint level, GLsizei X, GLsizei Y, GLsizei Z, const GLuint *pixels)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(target == GL_TEXTURE_CUBE_MAP && ASSERT(Z == 6))
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_INT, pixels + X * Y * 0)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_INT, pixels + X * Y * 1)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_INT, pixels + X * Y * 2)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_INT, pixels + X * Y * 3)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_INT, pixels + X * Y * 4)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, internalformat, X, Y, 0, GLformat(internalformat), GL_UNSIGNED_INT, pixels + X * Y * 5));
	else
	   GL_ASSERT(glTexImage3D(target, level, internalformat, X, Y, Z, 0, GLformat(internalformat), GL_UNSIGNED_INT, pixels));
}
void TEX3D::image(GLint level, GLsizei X, GLsizei Y, GLsizei Z, const GLfloat *pixels)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(target == GL_TEXTURE_CUBE_MAP && ASSERT(Z == 6))
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, internalformat, X, Y, 0, GLformat(internalformat), GL_FLOAT, pixels + X * Y * 0)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, internalformat, X, Y, 0, GLformat(internalformat), GL_FLOAT, pixels + X * Y * 1)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, internalformat, X, Y, 0, GLformat(internalformat), GL_FLOAT, pixels + X * Y * 2)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, internalformat, X, Y, 0, GLformat(internalformat), GL_FLOAT, pixels + X * Y * 3)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, internalformat, X, Y, 0, GLformat(internalformat), GL_FLOAT, pixels + X * Y * 4)) &&
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, internalformat, X, Y, 0, GLformat(internalformat), GL_FLOAT, pixels + X * Y * 5));
	else
	   GL_ASSERT(glTexImage3D(target, level, internalformat, X, Y, Z, 0, GLformat(internalformat), GL_FLOAT, pixels));
}
// glTexSubImage3D
void TEX3D::sub_image(GLint level, GLint x, GLint y, GLint z, GLsizei X, GLsizei Y, GLsizei Z, const GLbyte *pixels)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(target == GL_TEXTURE_CUBE_MAP && ASSERT(Z == 6) && gl_Version < 045)
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, x, y, X, Y, GLformat(internalformat), GL_BYTE, pixels + X * Y * 0)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, x, y, X, Y, GLformat(internalformat), GL_BYTE, pixels + X * Y * 1)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, x, y, X, Y, GLformat(internalformat), GL_BYTE, pixels + X * Y * 2)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, x, y, X, Y, GLformat(internalformat), GL_BYTE, pixels + X * Y * 3)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, x, y, X, Y, GLformat(internalformat), GL_BYTE, pixels + X * Y * 4)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, x, y, X, Y, GLformat(internalformat), GL_BYTE, pixels + X * Y * 5));
	else // case GL_TEXTURE_CUBE_MAP: ARB_direct_state_access 4.5
	   GL_ASSERT(glTexSubImage3D(target, level, x, y, z, X, Y, Z, GLformat(internalformat), GL_BYTE, pixels));
}
void TEX3D::sub_image(GLint level, GLint x, GLint y, GLint z, GLsizei X, GLsizei Y, GLsizei Z, const GLubyte *pixels)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(target == GL_TEXTURE_CUBE_MAP && ASSERT(Z == 6) && gl_Version < 045)
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_BYTE, pixels + X * Y * 0)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_BYTE, pixels + X * Y * 1)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_BYTE, pixels + X * Y * 2)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_BYTE, pixels + X * Y * 3)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_BYTE, pixels + X * Y * 4)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_BYTE, pixels + X * Y * 5));
	else // case GL_TEXTURE_CUBE_MAP: ARB_direct_state_access 4.5
	   GL_ASSERT(glTexSubImage3D(target, level, x, y, z, X, Y, Z, GLformat(internalformat), GL_UNSIGNED_BYTE, pixels));
}
void TEX3D::sub_image(GLint level, GLint x, GLint y, GLint z, GLsizei X, GLsizei Y, GLsizei Z, const GLshort *pixels)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(target == GL_TEXTURE_CUBE_MAP && ASSERT(Z == 6) && gl_Version < 045)
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, x, y, X, Y, GLformat(internalformat), GL_SHORT, pixels + X * Y * 0)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, x, y, X, Y, GLformat(internalformat), GL_SHORT, pixels + X * Y * 1)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, x, y, X, Y, GLformat(internalformat), GL_SHORT, pixels + X * Y * 2)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, x, y, X, Y, GLformat(internalformat), GL_SHORT, pixels + X * Y * 3)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, x, y, X, Y, GLformat(internalformat), GL_SHORT, pixels + X * Y * 4)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, x, y, X, Y, GLformat(internalformat), GL_SHORT, pixels + X * Y * 5));
	else // case GL_TEXTURE_CUBE_MAP: ARB_direct_state_access 4.5
	   GL_ASSERT(glTexSubImage3D(target, level, x, y, z, X, Y, Z, GLformat(internalformat), GL_SHORT, pixels));
}
void TEX3D::sub_image(GLint level, GLint x, GLint y, GLint z, GLsizei X, GLsizei Y, GLsizei Z, const GLushort *pixels)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(target == GL_TEXTURE_CUBE_MAP && ASSERT(Z == 6) && gl_Version < 045)
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_SHORT, pixels + X * Y * 0)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_SHORT, pixels + X * Y * 1)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_SHORT, pixels + X * Y * 2)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_SHORT, pixels + X * Y * 3)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_SHORT, pixels + X * Y * 4)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_SHORT, pixels + X * Y * 5));
	else // case GL_TEXTURE_CUBE_MAP: ARB_direct_state_access 4.5
	   GL_ASSERT(glTexSubImage3D(target, level, x, y, z, X, Y, Z, GLformat(internalformat), GL_UNSIGNED_SHORT, pixels));
}
void TEX3D::sub_image(GLint level, GLint x, GLint y, GLint z, GLsizei X, GLsizei Y, GLsizei Z, const GLint *pixels)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(target == GL_TEXTURE_CUBE_MAP && ASSERT(Z == 6) && gl_Version < 045)
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, x, y, X, Y, GLformat(internalformat), GL_INT, pixels + X * Y * 0)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, x, y, X, Y, GLformat(internalformat), GL_INT, pixels + X * Y * 1)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, x, y, X, Y, GLformat(internalformat), GL_INT, pixels + X * Y * 2)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, x, y, X, Y, GLformat(internalformat), GL_INT, pixels + X * Y * 3)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, x, y, X, Y, GLformat(internalformat), GL_INT, pixels + X * Y * 4)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, x, y, X, Y, GLformat(internalformat), GL_INT, pixels + X * Y * 5));
	else // case GL_TEXTURE_CUBE_MAP: ARB_direct_state_access 4.5
	   GL_ASSERT(glTexSubImage3D(target, level, x, y, z, X, Y, Z, GLformat(internalformat), GL_INT, pixels));
}
void TEX3D::sub_image(GLint level, GLint x, GLint y, GLint z, GLsizei X, GLsizei Y, GLsizei Z, const GLuint *pixels)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(target == GL_TEXTURE_CUBE_MAP && ASSERT(Z == 6) && gl_Version < 045)
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_INT, pixels + X * Y * 0)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_INT, pixels + X * Y * 1)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_INT, pixels + X * Y * 2)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_INT, pixels + X * Y * 3)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_INT, pixels + X * Y * 4)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, x, y, X, Y, GLformat(internalformat), GL_UNSIGNED_INT, pixels + X * Y * 5));
	else // case GL_TEXTURE_CUBE_MAP: ARB_direct_state_access 4.5
	   GL_ASSERT(glTexSubImage3D(target, level, x, y, z, X, Y, Z, GLformat(internalformat), GL_UNSIGNED_INT, pixels));
}
void TEX3D::sub_image(GLint level, GLint x, GLint y, GLint z, GLsizei X, GLsizei Y, GLsizei Z, const GLfloat *pixels)
{
	if(ASSERT(texture) && ASSERT(internalformat))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(target == GL_TEXTURE_CUBE_MAP && ASSERT(Z == 6) && gl_Version < 045)
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, x, y, X, Y, GLformat(internalformat), GL_FLOAT, pixels + X * Y * 0)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, x, y, X, Y, GLformat(internalformat), GL_FLOAT, pixels + X * Y * 1)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, x, y, X, Y, GLformat(internalformat), GL_FLOAT, pixels + X * Y * 2)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, x, y, X, Y, GLformat(internalformat), GL_FLOAT, pixels + X * Y * 3)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, x, y, X, Y, GLformat(internalformat), GL_FLOAT, pixels + X * Y * 4)) &&
	   GL_ASSERT(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, x, y, X, Y, GLformat(internalformat), GL_FLOAT, pixels + X * Y * 5));
	else // case GL_TEXTURE_CUBE_MAP: ARB_direct_state_access 4.5
	   GL_ASSERT(glTexSubImage3D(target, level, x, y, z, X, Y, Z, GLformat(internalformat), GL_FLOAT, pixels));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ARB_texture_storage 4.2
TEX3D::TEX3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth): target(target), internalformat(internalformat)
{
	if(GL_ASSERT(glGenTextures(1, &texture)))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(GL_ASSERT(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST)))
	if(GL_ASSERT(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST)))
	   GL_ASSERT(glTexStorage3D(target, levels, internalformat, width, height, depth));
}
TEX3D::TEX3D(GLenum target, GLenum internalformat, GLsizei X, GLsizei Y, GLsizei Z, GLenum type, const void *pixels): target(target), internalformat(internalformat)
{
	GLenum format = GLformat(internalformat);
	constexpr auto GLsize = [ ](GLenum type) -> GLsizeiptr
	{
		switch(type)
		{
			case GL_BYTE:		return sizeof(GLbyte);
			case GL_UNSIGNED_BYTE:	return sizeof(GLubyte);
			case GL_SHORT:		return sizeof(GLshort);
			case GL_UNSIGNED_SHORT:	return sizeof(GLushort);
			case GL_INT:		return sizeof(GLint);
			case GL_UNSIGNED_INT:	return sizeof(GLuint);
			case GL_FLOAT:		return sizeof(GLfloat);
			default:		return 0;
		}
	};
	if(GL_ASSERT(glGenTextures(1, &texture)))
	if(GL_ASSERT(glBindTexture(target, texture)))
	if(GL_ASSERT(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST)))
	if(GL_ASSERT(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST)))
	if(target == GL_TEXTURE_CUBE_MAP && ASSERT(Z == 6))
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, internalformat, X, Y, 0, format, type, static_cast<const char *>(pixels) + GLsize(type) * X * Y * 0)),
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, internalformat, X, Y, 0, format, type, static_cast<const char *>(pixels) + GLsize(type) * X * Y * 1)),
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, internalformat, X, Y, 0, format, type, static_cast<const char *>(pixels) + GLsize(type) * X * Y * 2)),
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, internalformat, X, Y, 0, format, type, static_cast<const char *>(pixels) + GLsize(type) * X * Y * 3)),
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, internalformat, X, Y, 0, format, type, static_cast<const char *>(pixels) + GLsize(type) * X * Y * 4)),
	   GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, internalformat, X, Y, 0, format, type, static_cast<const char *>(pixels) + GLsize(type) * X * Y * 5));
	else
	   GL_ASSERT(glTexImage3D(target, 0, internalformat, X, Y, Z, 0, format, type, pixels));
}
TEX3D::operator GLuint(void) const
{
	return texture;
}
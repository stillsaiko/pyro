# include "tex.h"
# include <cassert>
# define GL_ASSERT assert(glGetError( ) == GL_NO_ERROR);
// ...
constexpr GLenum TEXBINDING(GLenum target){ // TEXTARGET
	switch(target){
		case GL_TEXTURE_1D					: return GL_TEXTURE_BINDING_1D ;
		case GL_TEXTURE_2D					: return GL_TEXTURE_BINDING_2D ;
		case GL_TEXTURE_3D					: return GL_TEXTURE_BINDING_3D ;
		case GL_TEXTURE_1D_ARRAY			: return GL_TEXTURE_BINDING_1D_ARRAY ;
		case GL_TEXTURE_2D_ARRAY			: return GL_TEXTURE_BINDING_2D_ARRAY ;
		case GL_TEXTURE_CUBE_MAP			: return GL_TEXTURE_BINDING_CUBE_MAP ;
		case GL_TEXTURE_CUBE_MAP_ARRAY		: return GL_TEXTURE_BINDING_CUBE_MAP_ARRAY ;
		case GL_TEXTURE_RECTANGLE			: return GL_TEXTURE_BINDING_RECTANGLE ;
		case GL_TEXTURE_2D_MULTISAMPLE		: return GL_TEXTURE_BINDING_2D_MULTISAMPLE ;
		case GL_TEXTURE_2D_MULTISAMPLE_ARRAY: return GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY ;
		case GL_TEXTURE_BUFFER				: return GL_TEXTURE_BINDING_BUFFER ;
		default: return 0u ; // error
	}
}
// n-dimensional ______________________________________________________________________
// ____________________________________________________________________________________
void TEX::bind(GLenum slot){
	assert(ID);
	glActiveTexture(slot);									GL_ASSERT
	glBindTexture(T, ID);									GL_ASSERT
}
void TEX::param(GLenum a, GLenum x){
	assert(ID);
	GLint B ;
	glGetIntegerv(TEXBINDING(T), &B);						GL_ASSERT
	glBindTexture(T, ID);									GL_ASSERT
	glTexParameteriv(T, a, &(GLint&)x);						GL_ASSERT
	glBindTexture(T, B);									GL_ASSERT
}
void TEX::mipmap(void){
	assert(ID);
	GLint B ;
	glGetIntegerv(TEXBINDING(T), &B);						GL_ASSERT
	glBindTexture(T, ID);									GL_ASSERT
	glGenerateMipmap(T);									GL_ASSERT
	glBindTexture(T, B);									GL_ASSERT
}
// protected
TEX::TEX(void){ }
// 1-dimensional ______________________________________________________________________
// ____________________________________________________________________________________
void TEX1D::image(GLenum i, GLsizei X, GLvoid * PX){
	GLint B ;
	glGetIntegerv(TEXBINDING(T), &B);								GL_ASSERT
	glBindTexture(T, ID);											GL_ASSERT
	glTexImage1D(T, 0, i, X, 0, format(i), type(i), PX);			GL_ASSERT
	glBindTexture(T, B);											GL_ASSERT
}
void TEX1D::resize(GLsizei X){
	assert(ID);
	GLint LOD = 0 ; // ?
	GLint i ;
	glBindTexture(T, ID);											GL_ASSERT
	glGetTexLevelParameteriv(T, 0, GL_TEXTURE_INTERNAL_FORMAT, &i);	GL_ASSERT
	glTexImage1D(T, LOD, i, X, 0, format(i), type(i), nullptr);		GL_ASSERT
}
TEX1D::~TEX1D(void){
	if(ID) glDeleteTextures(1u, &ID);
}
TEX1D::TEX1D(void){ }
TEX1D::TEX1D(GLenum T, GLenum i, GLsizei X, GLvoid * PX){
	this->T = T ;
	glGenTextures(1u, &ID);											GL_ASSERT
	image(i, X, PX);
}
TEX1D& TEX1D::operator = (TEX1D&& a)noexcept {
	ID = a.ID; T = a.T; a.ID = 0; a.T = 0;	return *this ;
}
// 2-dimensional ______________________________________________________________________
// ____________________________________________________________________________________
void TEX2D::image(GLenum i, GLsizei X, GLsizei Y, GLvoid * PX){
	GLint B ;
	glGetIntegerv(TEXBINDING(T), &B);								GL_ASSERT
	glBindTexture(T, ID);											GL_ASSERT
	glTexImage2D(T, 0, i, X, Y, 0, format(i), type(i), PX);			GL_ASSERT
	glBindTexture(T, B);											GL_ASSERT
}
void TEX2D::resize(GLsizei X, GLsizei Y){
	assert(ID);
	GLint LOD = 0 ; // ?
	GLint i ;
	GLint B ;
	glGetIntegerv(TEXBINDING(T), &B);								GL_ASSERT
	glBindTexture(T, ID);											GL_ASSERT
	glGetTexLevelParameteriv(T, 0, GL_TEXTURE_INTERNAL_FORMAT, &i);	GL_ASSERT
	glTexImage2D(T, LOD, i, X, Y, 0, format(i), type(i), nullptr);	GL_ASSERT
	glBindTexture(T, B);											GL_ASSERT
}
TEX2D::~TEX2D(void){
	if(ID) glDeleteTextures(1u, &ID);
}
TEX2D::TEX2D(void){ }
TEX2D::TEX2D(GLenum T, GLenum i, GLsizei X, GLsizei Y, GLvoid * PX){
	this->T = T ;													GL_ASSERT
	glGenTextures(1u, &ID);											GL_ASSERT
	image(i, X, Y, PX); //	AO = ::TEX<2D>(GL_DEPTH_COMPONENT16, 720, 720);
}
TEX2D& TEX2D::operator = (TEX2D&& a)noexcept {
	ID = a.ID; T = a.T; a.ID = 0; a.T = 0;	return *this ;
}
// 3-dimensional ______________________________________________________________________
// ____________________________________________________________________________________
void TEX3D::image(GLenum i, GLsizei X, GLsizei Y, GLsizei Z, GLvoid * PX){
	GLint B ;
	glGetIntegerv(TEXBINDING(T), &B);								GL_ASSERT
	glBindTexture(T, ID);											GL_ASSERT
	glTexImage3D(T, 0, i, X, Y, Z, 0, format(i), type(i), PX);		GL_ASSERT
	glBindTexture(T, B);											GL_ASSERT
}
void TEX3D::resize(GLsizei X, GLsizei Y, GLsizei Z){
	assert(ID);
	GLint LOD = 0 ; // ?
	GLint i ;
	GLint B ;
	glGetIntegerv(TEXBINDING(T), &B);								GL_ASSERT
	glBindTexture(T, ID);											GL_ASSERT
	glGetTexLevelParameteriv(T, 0, GL_TEXTURE_INTERNAL_FORMAT, &i);	GL_ASSERT
	glTexImage3D(T, LOD, i, X, Y, Z, 0, format(i), type(i), nullptr);GL_ASSERT
	glBindTexture(T, B);											GL_ASSERT
}
TEX3D::~TEX3D(void){
	if(ID) glDeleteTextures(1u, &ID);
}
TEX3D::TEX3D(void){ }
TEX3D::TEX3D(GLenum T, GLenum i, GLsizei X, GLsizei Y, GLsizei Z, GLvoid * PX){
	this->T = T ;
	glGenTextures(1u, &ID);											GL_ASSERT
	image(i, X, Y, Z, PX);
}
TEX3D& TEX3D::operator = (TEX3D&& a)noexcept {
	ID = a.ID; T = a.T; a.ID = 0; a.T = 0;	return *this ;
}

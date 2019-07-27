# include "tex.h"
# include <cassert>
# define GL_ASSERT assert(glGetError( ) == GL_NO_ERROR);
// NEW
template<TEXTARGET> struct TEXDIM ;
template<> struct TEXDIM<1D>					{ typedef TEX1D type ; };

template<> struct TEXDIM<2D>					{ typedef TEX2D type ; };
template<> struct TEXDIM<1D_ARRAY>				{ typedef TEX2D type ; };
template<> struct TEXDIM<2D_MULTISAMPLE>		{ typedef TEX2D type ; };

template<> struct TEXDIM<3D>					{ typedef TEX3D type ; };
template<> struct TEXDIM<2D_ARRAY>				{ typedef TEX3D type ; };
template<> struct TEXDIM<CUBE_MAP>				{ typedef TEX3D type ; };
template<> struct TEXDIM<CUBE_MAP_ARRAY>		{ typedef TEX3D type ; };
template<> struct TEXDIM<2D_MULTISAMPLE_ARRAY>	{ typedef TEX3D type ; };

template<TEXTARGET T> struct foo : TEXDIM<T>::type {
};
foo<CUBE_MAP> xxxxxx ;
struct TEX2D_MUTLISAMPLE_ARRAY {
	
};
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
// protected
TEX1D::~TEX1D(void){
	if(ID) glDeleteTextures(1u, &ID);
}
TEX1D::TEX1D(void){ }
TEX1D::TEX1D(TEXTARGET T, GLenum i, GLsizei X, GLvoid * PX){
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
// protected
TEX2D::~TEX2D(void){
	if(ID) glDeleteTextures(1u, &ID);
}
TEX2D::TEX2D(void){ }
TEX2D::TEX2D(TEXTARGET T, GLenum i, GLsizei X, GLsizei Y, GLvoid * PX){
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
// protected
TEX3D::~TEX3D(void){
	if(ID) glDeleteTextures(1u, &ID);
}
TEX3D::TEX3D(void){ }
TEX3D::TEX3D(TEXTARGET T, GLenum i, GLsizei X, GLsizei Y, GLsizei Z, GLvoid * PX){
	this->T = T ;
	glGenTextures(1u, &ID);											GL_ASSERT
	image(i, X, Y, Z, PX);
}
TEX3D& TEX3D::operator = (TEX3D&& a)noexcept {
	ID = a.ID; T = a.T; a.ID = 0; a.T = 0;	return *this ;
}
/*
// template specialization __________________________________________________
// n-dimensional ______________________________________________________
TEX<1D>::TEX(GLenum F, GLsizei X, GLvoid* P): TEX1D(1D, F, X, P){ }
TEX<1D>::TEX(void){ }
TEX<1D>& TEX<1D>::operator = (TEX<1D>&& a)noexcept { ID = a.ID; T = a.T; a.ID = 0; a.T = 0; return *this ; }
TEX<2D>::TEX(GLenum F, GLsizei X, GLsizei Y, GLvoid* P): TEX2D(2D, F, X, Y, P){ }
TEX<2D>::TEX(void){ }
TEX<2D>&
TEX<2D>::operator = (TEX<2D>&& a)noexcept { ID = a.ID; T = a.T; a.ID = 0; a.T = 0; return *this ; }
TEX<3D>::TEX(GLenum F, GLsizei X, GLsizei Y, GLsizei Z, GLvoid* P): TEX3D(3D, F, X, Y, Z, P){ }
TEX<3D>::TEX(void){ }
TEX<3D>&
TEX<3D>::operator = (TEX<3D>&& a)noexcept { ID = a.ID; T = a.T; a.ID = 0; a.T = 0; return *this ; }
// array ________________________________________________________
TEX<1D_ARRAY>::TEX(GLenum F, GLsizei X, GLsizei Y, GLvoid* P): TEX2D(1D_ARRAY, F, X, Y, P){ }
TEX<1D_ARRAY>::TEX(void){ }
TEX<1D_ARRAY>&
TEX<1D_ARRAY>::operator = (TEX<1D_ARRAY>&& a)noexcept { ID = a.ID; T = a.T; a.ID = 0; a.T = 0; return *this ; }
TEX<2D_ARRAY>::TEX(GLenum F, GLsizei X, GLsizei Y, GLsizei Z, GLvoid* P): TEX3D(2D_ARRAY, F, X, Y, Z, P){ }
TEX<2D_ARRAY>::TEX(void){ }
TEX<2D_ARRAY>&
TEX<2D_ARRAY>::operator = (TEX<2D_ARRAY>&& a)noexcept { ID = a.ID; T = a.T; a.ID = 0; a.T = 0; return *this ; }
// rect ____________________________________________________________________________
// ________________________________ R E C T A N G L E ______________________________
// _________________________________________________________________________________
TEX<RECTANGLE>::TEX(GLenum F, GLsizei X, GLsizei Y, GLvoid* P): TEX2D(RECTANGLE, F, X, Y, P){ }
TEX<RECTANGLE>::TEX(void){ }
TEX<RECTANGLE>&
TEX<RECTANGLE>::operator = (TEX<RECTANGLE>&& a)noexcept { ID = a.ID; T = a.T; a.ID = 0; a.T = 0; return *this ; }
// cube ____________________________________________________________________________
// _________________________________ C U B E _ M A P _______________________________
// _________________________________________________________________________________
TEX<CUBE_MAP>::TEX(GLenum F, GLsizei X, GLsizei Y, GLvoid* P): TEX2D(CUBE_MAP, F, X, Y, P){ }
TEX<CUBE_MAP>::TEX(void){ }
TEX<CUBE_MAP>&
TEX<CUBE_MAP>::operator = (TEX<CUBE_MAP>&& a)noexcept { ID = a.ID; T = a.T; a.ID = 0; a.T = 0; return *this ; }
// array ________________________________________________________
TEX<CUBE_MAP_ARRAY>::TEX(GLenum F, GLsizei X, GLsizei Y, GLsizei Z, GLvoid* P): TEX3D(CUBE_MAP_ARRAY, F, X, Y, Z, P){ }
TEX<CUBE_MAP_ARRAY>::TEX(void){ }
TEX<CUBE_MAP_ARRAY>&
TEX<CUBE_MAP_ARRAY>::operator = (TEX<CUBE_MAP_ARRAY>&& a)noexcept { ID = a.ID; T = a.T; a.ID = 0; a.T = 0; return *this ; }
// multisample _____________________________________________________________________
// _______________________________ M U L T I S A M P L E ___________________________
// _________________________________________________________________________________
TEX<2D_MULTISAMPLE>::TEX(GLenum F, GLsizei X, GLsizei Y, GLvoid* P): TEX2D(2D_MULTISAMPLE, F, X, Y, P){ }
TEX<2D_MULTISAMPLE>::TEX(void){ }
TEX<2D_MULTISAMPLE>&
TEX<2D_MULTISAMPLE>::operator = (TEX<2D_MULTISAMPLE>&& a)noexcept { ID = a.ID; T = a.T; a.ID = 0; a.T = 0; return *this ; }
TEX<2D_MULTISAMPLE_ARRAY>::TEX(GLenum F, GLsizei X, GLsizei Y, GLsizei Z, GLvoid* P): TEX3D(2D_MULTISAMPLE_ARRAY, F, X, Y, Z, P){ }
TEX<2D_MULTISAMPLE_ARRAY>::TEX(void){ }
TEX<2D_MULTISAMPLE_ARRAY>&
TEX<2D_MULTISAMPLE_ARRAY>::operator = (TEX<2D_MULTISAMPLE_ARRAY>&& a)noexcept { ID = a.ID; T = a.T; a.ID = 0; a.T = 0; return *this ; }
// buffer __________________________________________________________________________
// ___________________________________ B U F F E R _________________________________
// _________________________________________________________________________________
TEX<BUFFER>::TEX(void){ assert(false); }
TEX<BUFFER>::TEX(GLenum internalformat, GLuint buffer){ assert(false); }*/
# pragma once
# include "fbo.h"
# define GL_ASSERT assert(glGetError( ) == GL_NO_ERROR);
// GLenum target ________________________________________________
enum TEXTARGET : GLenum {
	RECTANGLE		= GL_TEXTURE_RECTANGLE,
	CUBE_MAP		= GL_TEXTURE_CUBE_MAP,
	CUBE_MAP_ARRAY	= GL_TEXTURE_CUBE_MAP_ARRAY,
	BUFFER			= GL_TEXTURE_BUFFER
};
// illegal literals (warning C4455)
# pragma warning(suppress: 4455)
constexpr TEXTARGET operator "" D(unsigned long long n){
	if( n == 1 )return (TEXTARGET) GL_TEXTURE_1D ;
	if( n == 2 )return (TEXTARGET) GL_TEXTURE_2D ;
	if( n == 3 )return (TEXTARGET) GL_TEXTURE_3D ;
	return (TEXTARGET) -1 ; // error
}
# pragma warning(suppress: 4455)
constexpr TEXTARGET operator "" D_ARRAY(unsigned long long n){
	if( n == 1 )return (TEXTARGET) GL_TEXTURE_1D_ARRAY ;
	if( n == 2 )return (TEXTARGET) GL_TEXTURE_2D_ARRAY ;
	return (TEXTARGET) -1 ; // error
}
# pragma warning(suppress: 4455)
constexpr TEXTARGET operator "" D_MULTISAMPLE(unsigned long long n){
	if( n == 2 )return (TEXTARGET) GL_TEXTURE_2D_MULTISAMPLE ;
	return (TEXTARGET) -1 ; // error
}
# pragma warning(suppress: 4455)
constexpr TEXTARGET operator "" D_MULTISAMPLE_ARRAY(unsigned long long n){
	if( n == 2 )return (TEXTARGET) GL_TEXTURE_2D_MULTISAMPLE_ARRAY ;
	return (TEXTARGET) -1 ; // error
}
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
//protected:
	~
	TEX1D(void);
	TEX1D(void);
	TEX1D(TEXTARGET, GLenum, GLsizei, GLvoid*);
	TEX1D& operator = (TEX1D&&)noexcept ;
};
struct TEX2D : public TEX {
	void image(GLenum format, GLsizei width, GLsizei height, GLvoid * pixels);
	void resize(GLsizei width, GLsizei height);
//protected:
	~
	TEX2D(void);
	TEX2D(void);
	TEX2D(TEXTARGET, GLenum, GLsizei, GLsizei, GLvoid*);
	TEX2D& operator = (TEX2D&&)noexcept ;
};
struct TEX3D : public TEX {
	void image(GLenum format, GLsizei width, GLsizei height, GLsizei depth, GLvoid* pixels);
	void resize(GLsizei width, GLsizei height, GLsizei depth);
//protected:
	~
	TEX3D(void);
	TEX3D(void);
	TEX3D(TEXTARGET, GLenum, GLsizei, GLsizei, GLsizei, GLvoid*);
	TEX3D& operator = (TEX3D&&)noexcept ;
};
/*
// template prototype __________________________________________________
template<TEXTARGET>struct TEX ;
// n-dimensional ______________________________________________________
template<> struct TEX<1D> : public TEX1D {
	TEX(void);
	TEX(GLenum format, GLsizei width, GLvoid* pixels=nullptr);
	TEX<1D>& operator = (TEX<1D>&& a)noexcept ;
};
template<> struct TEX<2D> : public TEX2D {
	TEX(void);
	TEX(GLenum format, GLsizei width, GLsizei height, GLvoid* pixels=nullptr);
	TEX<2D>& operator = (TEX<2D>&& a)noexcept ;
};
template<> struct TEX<3D> : public TEX3D {
	TEX(void);
	TEX(GLenum format, GLsizei width, GLsizei height, GLsizei depth, GLvoid* pixels=nullptr);
	TEX<3D>& operator = (TEX<3D>&& a)noexcept ;
};
// array ________________________________________________________
template<> struct TEX<1D_ARRAY> : public TEX2D {
	TEX(void);
	TEX(GLenum format, GLsizei width, GLsizei height, GLvoid* pixels=nullptr);
	TEX<1D_ARRAY>& operator = (TEX<1D_ARRAY>&& a)noexcept ;
};
template<> struct TEX<2D_ARRAY> : public TEX3D {
	TEX(void);
	TEX(GLenum format, GLsizei width, GLsizei height, GLsizei depth, GLvoid* pixels=nullptr);
	TEX<2D_ARRAY>& operator = (TEX<2D_ARRAY>&& a)noexcept ;
};
// rect ____________________________________________________________________________
// ________________________________ R E C T A N G L E ______________________________
// _________________________________________________________________________________
template<> struct TEX<RECTANGLE> : public TEX2D {
	TEX(void);
	TEX(GLenum format, GLsizei width, GLsizei height, GLvoid* pixels=nullptr);
	TEX<RECTANGLE>& operator = (TEX<RECTANGLE>&& a)noexcept ;
};
// cube ____________________________________________________________________________
// _________________________________ C U B E _ M A P _______________________________
// _________________________________________________________________________________
template<> struct TEX<CUBE_MAP> : public TEX2D {
	TEX(void);
	TEX(GLenum format, GLsizei width, GLsizei height, GLvoid* pixels=nullptr);
	TEX<CUBE_MAP>& operator = (TEX<CUBE_MAP>&& a)noexcept ;
};
// array ________________________________________________________
template<> struct TEX<CUBE_MAP_ARRAY> : public TEX3D {
	TEX(void);
	TEX(GLenum format, GLsizei width, GLsizei height, GLsizei depth, GLvoid* pixels=nullptr);
	TEX<CUBE_MAP_ARRAY>& operator = (TEX<CUBE_MAP_ARRAY>&& a)noexcept ;
};
// multisample _____________________________________________________________________
// _______________________________ M U L T I S A M P L E ___________________________
// _________________________________________________________________________________
template<> struct TEX<2D_MULTISAMPLE> : public TEX2D {
	TEX(void);
	TEX(GLenum format, GLsizei width, GLsizei height, GLvoid* pixels=nullptr);
	TEX<2D_MULTISAMPLE>& operator = (TEX<2D_MULTISAMPLE>&& a)noexcept ;
};
template <> struct TEX<2D_MULTISAMPLE_ARRAY> : public TEX3D {
	TEX(void);
	TEX(GLenum format, GLsizei width, GLsizei height, GLsizei depth, GLvoid* pixels=nullptr);
	TEX<2D_MULTISAMPLE_ARRAY>& operator = (TEX<2D_MULTISAMPLE_ARRAY>&& a)noexcept ;
};
// buffer __________________________________________________________________________
// ___________________________________ B U F F E R _________________________________
// _________________________________________________________________________________
template<> struct TEX<BUFFER> : public TEXBASE {
	TEX(void);
	TEX(GLenum internalformat, GLuint buffer);
};*/
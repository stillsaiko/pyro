# pragma once
# include "glsl.h"
template<class...VA> struct VAO {
	GLuint vao = 0u ;
	GLuint vbo = 0u ;
	~
	VAO(void);
	VAO(void);
	VAO(const void * vertices, size_t count);
	VAO<VA...>& operator = (VAO<VA...>&&);
	void operator( )(const void *, size_t);
	void sub(size_t, const void *, size_t);
	operator GLuint(void)const { return vao ; }
};
# include "vao.inl"
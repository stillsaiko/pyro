# pragma once
// include "gl/glew.h"
# include "glsl.h"
// vertex attrib
struct VA { // warning: VA hidden by macro (seek to end)
	const GLvoid * offset ; // offsetof
	const GLsizei size ; // 1, 2, 3, 4
	const GLenum type ; // GL_FLOAT
};
/////////////////////////////////////////
// vertex array object
# include <initializer_list>
template<class T> class VAO {
	GLuint vao = 0u ;
	GLuint vbo = 0u ;
public:
	~
	VAO(void);
	VAO(void);
	VAO(std::initializer_list<VA>, size_t = 0UL, const T * = nullptr);
	VAO& operator = (VAO&&)noexcept ;
	void operator( )(size_t, const T *); // glBufferData
	void operator( )(size_t, const T *, size_t); // glBufferSubData
	operator GLuint(void)const { return vao ; }
};
# include "vao.inl"
// size_t n ... ;
// V3VN3 * vert = new ... ;
// VAO<V3VN3> vao({	VA<offsetof(V3VN3, V),	decltype(V3VN3::V)>,
//					VA<offsetof(V3VN3, VN),	decltype(V3VN3::VN)> }, ...);
# define VA(T, A) VA {				\
	(GLvoid *)offsetof(T, A),		\
	GLattrib<decltype(T::A)>::size,	\
	GLattrib<decltype(T::A)>::type }
// size_t n ... ;
// V3VN3 * vert = new ... ;
// VAO<V3VN3> vao({	VA(V3VN3, V),
//					VA(V3VN3, VN) }, vert, n);
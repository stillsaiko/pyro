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
// vao.inl
template<class> constexpr GLenum GLtype(void);
template<> constexpr GLenum GLtype<GLint>(void){return GL_INT;}
template<> constexpr GLenum GLtype<GLshort>(void){return GL_SHORT;}
template<> constexpr GLenum GLtype<GLbyte>(void){return GL_BYTE;}
template<> constexpr GLenum GLtype<GLuint>(void){return GL_UNSIGNED_INT;}
template<> constexpr GLenum GLtype<GLushort>(void){return GL_UNSIGNED_SHORT;}
template<> constexpr GLenum GLtype<GLubyte>(void){return GL_UNSIGNED_BYTE;}
template<> constexpr GLenum GLtype<GLfloat>(void){return GL_FLOAT;}
template<> constexpr GLenum GLtype<GLdouble>(void){return GL_DOUBLE;}
template<class> struct GL ;
template<class T, int N> struct GL<T[N]> {
	static constexpr GLenum type = GLtype<T>( );
	static constexpr GLsizei size = N ;
};
/*template<class T> struct GL<T> {
	static constexpr GLenum type = GLtype<T>( );
	static constexpr GLsizei size = 1u ;
};*/
// helper shizzle above
template<class...VA> VAO<VA...>::~VAO(void){
	if( vao )glDeleteVertexArrays(1, &vao);
	if( vbo )glDeleteBuffers(1, &vbo);
}
template<class...VA> VAO<VA...>::VAO(void){ }
# include <tuple>
template<class...VA> VAO<VA...>::VAO(const void * vertices, size_t count){
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLenum types[sizeof...(VA)]{ GL<VA>::type... };
	GLenum sizes[sizeof...(VA)]{ GL<VA>::size... };
	GLsizei stride = sizeof(std::tuple<VA...>);
	size_t offset(0u);
	for(GLuint i(0u); i<sizeof...(VA); ++i){
		switch(types[i]){
		case GL_FLOAT:
		case GL_DOUBLE:
			glVertexAttribPointer(i, sizes[i], types[i], GL_FALSE, stride, (void*)offset);
			break ;
		default:
			glVertexAttribIPointer(i, sizes[i], types[i], stride, (void*)offset);
			break ;
		}
		glEnableVertexAttribArray(i);
		switch(types[i]){
			case GL_DOUBLE:
				printf("GL_DOUBLE\n");
				offset += 8u * sizes[i];
				continue ;
			case GL_FLOAT:
			case GL_INT:
			case GL_UNSIGNED_INT:
				printf("GL_FLOAT GL_INT GL_UNSIGNED_INT\n");
				offset += 4u * sizes[i];
				continue ;
			case GL_SHORT:
			case GL_UNSIGNED_SHORT:
				printf("GL_SHORT GL_UNSIGNED_SHORT\n");
				offset += 2u * sizes[i];
				continue ;
			case GL_BYTE:
			case GL_UNSIGNED_BYTE:
				printf("GL_BYTE GL_UNSIGNED_BYTE\n");
				offset += 1u * sizes[i];
				continue ;
			default: // (invalid enum)
				printf("GL_* %u\n", types[i]);
				continue ;
		}
	}
	printf("offset = %u\n ... stride = %u\n", offset, stride);
	assert(offset == stride);
	glBindBuffer(GL_ARRAY_BUFFER, 0u); // okay?
	glBindVertexArray(0u); // okay?
	operator( )(vertices, count);
}
template<class...VA>
VAO<VA...>&
VAO<VA...>::operator = (VAO<VA...>&& a){
	if( vao ){
		GLint prev ;									GL_ASSERT
		glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &prev);	GL_ASSERT
		if(prev == vao){
			glBindVertexArray(0u);						GL_ASSERT
		}
		glDeleteVertexArrays(1, &vao);					GL_ASSERT
	}
	if( vbo )glDeleteBuffers(1, &vbo);
	vao = a ; a.vao = 0u ;
	vbo = a ; a.vbo = 0u ;
	return *this ;
}
template<class...VA> void VAO<VA...>::operator( )(const void * data, size_t size){
	assert(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(std::tuple<VA...>) * size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
}
template<class...VA> void VAO<VA...>::sub(size_t offset, const void * data, size_t size){
	assert(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(std::tuple<VA...>) * offset,
									 sizeof(std::tuple<VA...>) * size, data); // GL_STATIC_DRAW
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
}

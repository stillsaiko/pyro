template<class> constexpr GLenum GLtype(void);
template<> constexpr GLenum GLtype<GLint>(void){return GL_INT;}
template<> constexpr GLenum GLtype<GLshort>(void){return GL_SHORT;}
template<> constexpr GLenum GLtype<GLbyte>(void){return GL_BYTE;}
template<> constexpr GLenum GLtype<GLuint>(void){return GL_UNSIGNED_INT;}
template<> constexpr GLenum GLtype<GLushort>(void){return GL_UNSIGNED_SHORT;}
template<> constexpr GLenum GLtype<GLubyte>(void){return GL_UNSIGNED_BYTE;}
template<> constexpr GLenum GLtype<GLfloat>(void){return GL_FLOAT;}
template<> constexpr GLenum GLtype<GLdouble>(void){return GL_DOUBLE;}
template<class T> struct GLattrib {
	static constexpr GLenum type = GLtype<T>( );
	static constexpr GLsizei size = 1UL;
};
template<class T, size_t N> struct GLattrib<T[N]> {
	static constexpr GLenum type = GLtype<T>( );
	static constexpr GLsizei size = N;
};
constexpr size_t GLsize(GLenum type){
	switch(type){
		case GL_DOUBLE:
			return 8UL;
		case GL_FLOAT:
		case GL_INT:
		case GL_UNSIGNED_INT:
			return 4UL;
		case GL_SHORT:
		case GL_UNSIGNED_SHORT:
			return 2UL;
		case GL_BYTE:
		case GL_UNSIGNED_BYTE:
			return 1UL;
		default: // (invalid enum)
			return 0UL; // error
	}
}
// helper shizzle above
template<class T> VAO<T>::~VAO(void){
	if( vao )glDeleteVertexArrays(1, &vao);
	if( vbo )glDeleteBuffers(1, &vbo);
}
template<class T> VAO<T>::VAO(void){ }
# include <tuple>
// VAO<V3>({GL(x,y,z)}, )
template<class T> VAO<T>::VAO(std::initializer_list<VA> layout, size_t count, const T * vertices){
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	size_t offset(0u);
	GLuint index(0u);
	for(const VA & a : layout){
		if(a.type==GL_FLOAT||a.type==GL_DOUBLE){
			 glVertexAttribPointer(index, a.size, a.type, GL_FALSE, sizeof(T), a.offset);
		} else {
			glVertexAttribIPointer(index, a.size, a.type, sizeof(T), a.offset);
		}
		glEnableVertexAttribArray(index++);
		if( size_t n = GLsize(a.type) ){
			offset += n * a.size;
		} else {
			printf("GL_* %u\n", a.type);
		}
	}
	assert(offset == sizeof(T));
	glBindBuffer(GL_ARRAY_BUFFER, 0u); // okay?
	glBindVertexArray(0u); // okay?
	if(count > 0UL)operator( )(count, vertices); // glBufferData
}
template<class T> VAO<T>& VAO<T>::operator = (VAO&& a)noexcept {
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
template<class T> void VAO<T>::operator( )(size_t count, const T * vert){
	assert(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(T) * count, vert, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
}
template<class T> void VAO<T>::operator( )(size_t count, const T * vert, size_t offset){
	assert(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(T) * offset,
									 sizeof(T) * count, vert); // GL_STATIC_DRAW
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
}
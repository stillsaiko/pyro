# pragma once
// openGL Shader Language
# include <gl.h>
// include "gl/glew.h"
# include <cstdio> // please *.cpp
# include <cstring> // strlen
# include "rc.h"
// include "vao.h"
// include <cassert>
// define GL_ASSERT assert(glGetError( ) == GL_NO_ERROR);
// GLSL shader_program = GLSL(RC(".vert"), RC(".frag"))
// glUseProgram(shader_program)
// glUniform1i(shader_program["sampler"], 0)
# include <initializer_list>
struct GLSL  {
	template<size_t N, class T> struct U {
		GLint location = -1 ;
		U(void){ }
		U(const U<N,T> & a){ location = a.location ; } // MinGw
		U(GLint L){ location = L ; }
		U& operator = (U&& a)noexcept { location = a.location ; a.location = -1 ; return *this ; }
		template<class...VA>
		void operator( )(VA...ARGS){
			static_assert( sizeof...(VA) == N, "noob" );
			u(ARGS...);
		}
		void u(int x)					{ ASSERT(glUniform1i(location, x)); }
		void u(int x, int y)				{ ASSERT(glUniform2i(location, x, y)); }
		void u(int x, int y, int z)			{ ASSERT(glUniform3i(location, x, y, z)); }
		void u(int x, int y, int z, int w)		{ ASSERT(glUniform4i(location, x, y, z, w)); }
		void u(float x)					{ ASSERT(glUniform1f(location, x)); }
		void u(float x, float y)			{ ASSERT(glUniform2f(location, x, y)); }
		void u(float x, float y, float z)		{ ASSERT(glUniform3f(location, x, y, z)); }
		void u(float x, float y, float z, float w)	{ ASSERT(glUniform4f(location, x, y, z, w)); }
	};
	~
	GLSL(void)noexcept ; // ~
	GLSL(void);
	GLSL(RC&&comp);
	GLSL(RC&&vert,                           RC&&frag);
	GLSL(RC&&vert,                  RC&&geom,RC&&frag);
	GLSL(RC&&vert,RC&&tesc,RC&&tese,         RC&&frag);
	GLSL(RC&&vert,RC&&tesc,RC&&tese,RC&&geom,RC&&frag);
//	GLSL(const GLSL &);
	void operator = (GLSL &&)noexcept ; // move
	GLint operator[ ](const char *);
/*	template<class...T> void operator( )(U<T>...uniform){
		glUseProgram(program);
		uniform.update( )... ;
	}*/
	template<size_t N, class T> U<N,T> uniform(const char * name){
		if(!ASSERT(program)) return { };
	/*	GLint B ;
		glGetIntegerv(GL_CURRENT_PROGRAM, &B);
		glUseProgram(program);					GL_ASSERT*/
		GLint location = glGetUniformLocation(program, name);//	GL_ASSERT
	//	glUseProgram(B);					GL_ASSERT
		return U<N,T>(location);
	}
	operator GLuint(void)const ;
private :
	GLuint PROGRAM = 0;
	static GLuint __GLSLcompile(GLenum, RC&);
	static GLuint __GLSLlink(std::initializer_list<GLuint>);
};

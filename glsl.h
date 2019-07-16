# pragma once
# include "gl/glew.h"
# include <cstdio> // please *.cpp
# include <cstring> // strlen
# include "rc.h"
// include "vao.h"
# include <cassert>
# define GL_ASSERT assert(glGetError( ) == GL_NO_ERROR);
struct GLSL {
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
		void u(int x)						{ glUniform1i(location, x);			GL_ASSERT }
		void u(int x, int y)				{ glUniform2i(location, x, y);		GL_ASSERT }
		void u(int x, int y, int z)			{ glUniform3i(location, x, y, z);	GL_ASSERT }
		void u(int x, int y, int z, int w)	{ glUniform4i(location, x, y, z, w);GL_ASSERT }
		void u(float x)								{ glUniform1f(location, x);			GL_ASSERT }
		void u(float x, float y)					{ glUniform2f(location, x, y);		GL_ASSERT }
		void u(float x, float y, float z)			{ glUniform3f(location, x, y, z);	GL_ASSERT }
		void u(float x, float y, float z, float w)	{ glUniform4f(location, x, y, z, w);GL_ASSERT }
	};
	~
	GLSL(void);
	GLSL(void);
	GLSL(RC&&comp);
	GLSL(RC&&vert,                           RC&&frag);
	GLSL(RC&&vert,                  RC&&geom,RC&&frag);
	GLSL(RC&&vert,RC&&tesc,RC&&tese,         RC&&frag);
	GLSL(RC&&vert,RC&&tesc,RC&&tese,RC&&geom,RC&&frag);
//	GLSL(const GLSL &);
	GLSL & operator = (GLSL &&)noexcept ;
	GLint operator[ ](const char *);
/*	template<class...T> void operator( )(U<T>...uniform){
		glUseProgram(program);
		uniform.update( )... ;
	}*/
	template<size_t N, class T> U<N,T> uniform(const char * name){
		assert(program);
	/*	GLint B ;
		glGetIntegerv(GL_CURRENT_PROGRAM, &B);
		glUseProgram(program);									GL_ASSERT*/
		GLint location = glGetUniformLocation(program, name);	GL_ASSERT
	//	glUseProgram(B);										GL_ASSERT
		return U<N,T>(location);
	}
	operator GLuint(void)const ;
private :
	GLuint program = 0u ;
};

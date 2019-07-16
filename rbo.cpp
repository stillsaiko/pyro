# include "rbo.h"
RBO::~RBO(void){
// delete (copy #1)
	if(ID && T == GL_RENDERBUFFER){
		printf("warning: RBO (destructor)\n");
		glDeleteRenderbuffers(1u, &ID);
	}
}
RBO::RBO(void){ }
RBO::RBO(GLenum internalformat, GLsizei width, GLsizei height){
	glGenRenderbuffers(1u, &ID);								GL_ASSERT
	glBindRenderbuffer(T = GL_RENDERBUFFER, ID);				GL_ASSERT
	glRenderbufferStorage(T, internalformat, width, height);	GL_ASSERT
}
RBO& RBO::operator = (RBO&& a)noexcept {
// delete (copy #2)
	if(ID && T == GL_RENDERBUFFER){
		glDeleteRenderbuffers(1u, &ID);							GL_ASSERT
	}
// move
	ID = a.ID ; a.ID = 0u ;
	T = a.T ; a.T = 0u ;
	return *this ;
}
void RBO::resize(GLsizei X, GLsizei Y){
	GLint LOD = 0 ;
	// assert(type != GL_RENDERBUFFER);
	GLint i ;
	GLint Z ;
	switch(T){
	case GL_RENDERBUFFER:
		glGetRenderbufferParameteriv(GL_RENDERBUFFER,
							GL_RENDERBUFFER_INTERNAL_FORMAT, &i);		GL_ASSERT
		glRenderbufferStorage(GL_RENDERBUFFER, i, X, Y);				GL_ASSERT
		return ;
	case GL_TEXTURE_1D:
	case GL_TEXTURE_2D:
	case GL_TEXTURE_2D_MULTISAMPLE:
	case GL_TEXTURE_RECTANGLE:
	case GL_TEXTURE_CUBE_MAP:
		glGetTexLevelParameteriv(T, 0, GL_TEXTURE_INTERNAL_FORMAT, &i);	GL_ASSERT
		glTexImage2D(T, LOD, i, X, Y, 0, format(i), type(i), nullptr);	GL_ASSERT
		return ;
	case GL_TEXTURE_1D_ARRAY:
	case GL_TEXTURE_2D_ARRAY:
	case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
	case GL_TEXTURE_3D:
	case GL_TEXTURE_CUBE_MAP_ARRAY:
		glGetTexLevelParameteriv(T,0,GL_TEXTURE_INTERNAL_FORMAT,&i);	GL_ASSERT
		glGetTexLevelParameteriv(T, 0, GL_TEXTURE_DEPTH, &Z);			GL_ASSERT
		glTexImage3D(T, LOD, i, X, Y, Z, 0,	format(i), type(i), 0u);	GL_ASSERT
		return ;
	default :
		return ; // error
	}
}
RBO::operator GLuint(void)const {
	return ID ;
}
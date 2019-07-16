# include "fbo.h"
# include <memory>
// ...
FBO::~FBO(void){ /*if(fbo)operator = (FBO( ));*/ 
	if( fbo ){ // (copy #1)
		printf("warning: FBO (destructor)\n");
		GLint prev ;
		glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prev);	GL_ASSERT
		if( prev == fbo ){
			glBindFramebuffer(GL_FRAMEBUFFER, 0u);			GL_ASSERT
		}
		glDeleteFramebuffers(1, &fbo);						GL_ASSERT
	}
} // ...?
FBO::FBO(void){ }
FBO&
FBO::operator = (FBO&& a)noexcept {
	if( fbo ){ // (copy #2)
		GLint prev ;										GL_ASSERT
		glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prev);	GL_ASSERT
		if( prev == fbo ){
			glBindFramebuffer(GL_FRAMEBUFFER, 0u);			GL_ASSERT
		}
		glDeleteFramebuffers(1, &fbo);						GL_ASSERT
	}
	fbo = a.fbo ; a.fbo = 0u ;
	for(size_t i(0u); i<8u; ++i)
	COLOR_ATTACHMENT[i]	= std::move(a.COLOR_ATTACHMENT[i]);
	DEPTH_ATTACHMENT	= std::move(a.DEPTH_ATTACHMENT) ;
	return *this ;
}
/*void FBO::resize(GLsizei X, GLsizei Y){
	if( DEPTH_ATTACHMENT )
		DEPTH_ATTACHMENT.resize(X, Y);
	for(int i(0u); i<8; ++i)
		if( COLOR_ATTACHMENT[i] )
			COLOR_ATTACHMENT[i].resize(X, Y);
}*/
void FBO::operator + (void){
	assert(fbo);
	assert(DEPTH_ATTACHMENT);
	A & a = DEPTH_ATTACHMENT ;
	GLint X, Y ;
	if(a.T == GL_RENDERBUFFER){
		glBindRenderbuffer(a.T, a.ID);							GL_ASSERT
		glGetRenderbufferParameteriv(GL_RENDERBUFFER,
									GL_RENDERBUFFER_WIDTH, &X);	GL_ASSERT
		glGetRenderbufferParameteriv(GL_RENDERBUFFER,
									GL_RENDERBUFFER_HEIGHT, &Y);GL_ASSERT
	} else {
		// gay TEXUTRE_*_BINDING.......
		glBindTexture(a.T, a.ID);								GL_ASSERT
		glGetTexLevelParameteriv(a.T,0,GL_TEXTURE_WIDTH,&X);	GL_ASSERT
		glGetTexLevelParameteriv(a.T,0,GL_TEXTURE_HEIGHT,&Y);	GL_ASSERT
	}
	glGetIntegerv(GL_VIEWPORT, VIEWPORT);						GL_ASSERT
	glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &BINDING);		GL_ASSERT
	glGetIntegerv(GL_DRAW_BUFFER, &DRAW_BUFFER);				GL_ASSERT
	glViewport(0, 0, X, Y);										GL_ASSERT
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);						GL_ASSERT
	// only for non color attachment styles !! FIX THIS MAN!!!!!!!
	glDrawBuffer(GL_NONE);										GL_ASSERT
}
void FBO::operator - (void){
	assert(fbo);
glViewport(VIEWPORT[0],VIEWPORT[1],VIEWPORT[2],VIEWPORT[3]);GL_ASSERT
	glBindFramebuffer(GL_FRAMEBUFFER, BINDING);				GL_ASSERT
	glDrawBuffer(DRAW_BUFFER);								GL_ASSERT
# ifndef NDEBUG
	BINDING = 0; // (not necessary)
	VIEWPORT[0] = 0; // (not necessary)
	VIEWPORT[1] = 0; // (not necessary)
	VIEWPORT[2] = 0; // (not necessary)
	VIEWPORT[3] = 0; // (not necessary)
	DRAW_BUFFER = GL_BACK ; // (not necessary)
# endif
}
FBO::operator GLuint(void)const { return fbo ; }
void FBO::check(void){
	GLint B ;
	glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &B);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	auto S = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	assert(S!=GL_FRAMEBUFFER_UNDEFINED);
	assert(S!=GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT);
	assert(S!=GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT);
	assert(S!=GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER);
	assert(S!=GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER);
	assert(S!=GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);
	assert(S!=GL_FRAMEBUFFER_UNSUPPORTED);
	assert(S!=GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE);
	assert(S!=GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS);
	assert(S==GL_FRAMEBUFFER_COMPLETE);
	glBindFramebuffer(GL_FRAMEBUFFER, B);
}
// private
void FBO::draw(GLsizei n){
	GLenum * bufs = new GLenum[n];
	for(GLsizei i(0u); i < n ; ++i)
		bufs[i] = GL_COLOR_ATTACHMENT0 + i ;
	GLint B ;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &B);		GL_ASSERT
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);			GL_ASSERT
	glDrawBuffers(n, bufs);							GL_ASSERT
	glBindFramebuffer(GL_FRAMEBUFFER, B);			GL_ASSERT
	delete[ ] bufs ;
}
FBO::A&
FBO::operator[ ](GLenum a){
	if(a == GL_DEPTH_ATTACHMENT)		return DEPTH_ATTACHMENT ;
	if(a == GL_DEPTH_STENCIL_ATTACHMENT)return DEPTH_ATTACHMENT ;
	assert(GL_COLOR_ATTACHMENT0 <= a && a <= GL_COLOR_ATTACHMENT15);
	return COLOR_ATTACHMENT[a-GL_COLOR_ATTACHMENT0];
}
void FBO::attach(GLenum A, FBO::A& move){
	GLint LOD = 0;
	GLint layer = 0;
// ...
	FBO::A& a = operator[ ](A);// = std::move(move);
	assert( a.ID = move.ID );
	assert(( a.T = move.T )==GL_TEXTURE_2D);
	GLint B ;																GL_ASSERT
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &B);								GL_ASSERT
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);									GL_ASSERT
	switch( a.T ){
		case GL_RENDERBUFFER:
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, A, a.T, a.ID);		GL_ASSERT
			break ;
		case GL_TEXTURE_1D:
		case GL_TEXTURE_2D:
		case GL_TEXTURE_RECTANGLE:
			glFramebufferTexture(GL_FRAMEBUFFER, A, a.ID, LOD);				GL_ASSERT
			break ;
		case GL_TEXTURE_3D:
		case GL_TEXTURE_1D_ARRAY:
		case GL_TEXTURE_2D_ARRAY:
		case GL_TEXTURE_CUBE_MAP:
		case GL_TEXTURE_CUBE_MAP_ARRAY:
			glFramebufferTextureLayer(GL_FRAMEBUFFER, A, a.ID, LOD, layer);	GL_ASSERT
			break ;
		default:
			break ; // error
	}
	glBindFramebuffer(GL_FRAMEBUFFER, B);									GL_ASSERT
}
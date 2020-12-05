# include "vao.h"
/*
void glDrawArrays                                 (GLenum mode​, GLint first​,              GLsizei count​);
void glDrawElements                               (GLenum mode​,                           GLsizei count​, GLenum type​, void *indices​);
void glDrawRangeElements                          (GLenum mode​, GLuint start​, GLuint end​, GLsizei count​, GLenum type​, void *indices​);
// multi
void glMultiDrawArrays                            (GLenum mode​, GLint *first​, GLsizei *count​,                              GLsizei primcount​);
void glMultiDrawElements                          (GLenum mode​,               GLsizei *count​, GLenum type​, void **indices​, GLsizei primcount);
// instanced
void glDrawArraysInstanced                        (GLenum mode​, GLint first​, GLsizei count​,                      GLsizei instancecount​);
void glDrawElementsInstanced                      (GLenum mode​, GLsizei count​, GLenum type​, const void *indices​, GLsizei instancecount​);
void glDrawTransformFeedbackInstanced             (GLenum mode​, GLuint id​,                                       GLsizei instancecount​);
// instanced base instance
void glDrawArraysInstancedBaseInstance            (GLenum mode​, GLint first​, GLsizei count​,                                   GLsizei instancecount​, GLuint baseinstance​​);
void glDrawElementsInstancedBaseInstance          (GLenum mode​,              GLsizei count​, GLenum type​, const void *indices​, GLsizei instancecount​, GLuint baseinstance​​);
// indirect
void glDrawArraysIndirect                         (GLenum mode​,              const void *indirect​);
void glDrawElementsIndirect                       (GLenum mode​, GLenum type​, const void *indirect​);
// multi indirect
void glMultiDrawArraysIndirect                    (GLenum mode​,              const void *indirect​, GLsizei drawcount​, GLsizei stride​);
void glMultiDrawElementsIndirect                  (GLenum mode​, GLenum type​, const void *indirect​, GLsizei drawcount​, GLsizei stride​);

void glDrawElementsBaseVertex                     (GLenum mode​, GLsizei  count​, GLenum type​, void  *indices​,                    GLint  basevertex​);
void glMultiDrawElementsBaseVertex                (GLenum mode​, GLsizei *count​, GLenum type​, void **indices​, GLsizei primcount​, GLint *basevertex​);
void glDrawRangeElementsBaseVertex                (GLenum mode​, GLuint start​, GLuint end​, GLsizei count​, GLenum type​, void *indices​,    GLint basevertex​);
void glDrawElementsInstancedBaseVertex            (GLenum mode​, GLsizei count​, GLenum type​, const void *indices​, GLsizei instancecount​, GLint basevertex​);
void glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode​, GLsizei count​, GLenum type​, const void *indices​, GLsizei instancecount​, GLint basevertex​, GLuint baseinstance​);
// transform feedback
void glDrawTransformFeedback                      (GLenum mode​, GLuint id​);
void glDrawTransformFeedbackStream                (GLenum mode​, GLuint id​, GLuint stream​);
void glDrawTransformFeedbackStreamInstanced       (GLenum mode​, GLuint id​, GLuint stream​, GLsizei instancecount​);*/

VBO::~VBO(void)
{
	if(layout) delete[ ] layout, layout = nullptr;
}
VBO::VBO(VBO &&VBO) noexcept: BO<GL_ARRAY_BUFFER>(static_cast<BO<GL_ARRAY_BUFFER> &&>(VBO)), layout(VBO.layout), stride(VBO.stride), count(VBO.count)
{ }
void VBO::operator = (VBO &&VBO) noexcept
{
	VBO::~VBO( );
	memcpy(this, &VBO, sizeof VBO);
	memset(&VBO, 0, sizeof VBO);
}

IBO::IBO(BO<GL_ELEMENT_ARRAY_BUFFER> &&IBO, GLenum type):
 BO<GL_ELEMENT_ARRAY_BUFFER>(static_cast<BO<GL_ELEMENT_ARRAY_BUFFER> &&>(IBO)), type(type)
{ }
/*
VAO::VAO(const BO<GL_ARRAY_BUFFER> &buffer, GLsizei stride, GLuint sizeof_VA, va_list ap)
{
	if(GL_ASSERT(glGenVertexArrays(1, &array)))
	if(GL_ASSERT(glBindVertexArray(array)))
	{
		if(GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, buffer)))
		for(GLuint index=0; index < sizeof_VA; ++index)
		{
			VBO::A A = va_arg(ap, VBO::A);
			GL_ASSERT(glVertexAttribPointer(index, A.size, A.type, GL_FALSE, stride, A.mp));
			GL_ASSERT(glEnableVertexAttribArray(index));
		}
	}
}
VAO::VAO(const BO<GL_ARRAY_BUFFER> &buffer, GLsizei stride, GLuint sizeof_VA, ...)
{
	if(GL_ASSERT(glGenVertexArrays(1, &array)))
	if(GL_ASSERT(glBindVertexArray(array)))
	{
		va_list ap;
		va_start(ap, sizeof_VA);
		
		va_end(ap);
	}
}

VAO::VAO(const BO<GL_ELEMENT_ARRAY_BUFFER> &buffer, const BO<GL_ARRAY_BUFFER> &vbo, GLsizei sizeof_T, GLuint sizeof_VA, ...): VAO(vbo, sizeof_T, sizeof_VA, ...)
{
	GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer));
}*/
VAO::A::A(const VBO &VBO): buffer(VBO), layout(VBO.layout), stride(VBO.stride), count(VBO.count)
{ }
VAO::~VAO(void)
{
	if(array) GL_ASSERT(glDeleteVertexArrays(1, &array)), array = 0;
}
# pragma warning (suppress: 26495)
VAO::VAO(VAO &&VAO) noexcept
{
	memcpy(this, &VAO, sizeof VAO);
	memset(&VAO, 0, sizeof VAO);
}
void VAO::operator = (VAO &&VAO) noexcept
{
	VAO::~VAO( );
	memcpy(this, &VAO, sizeof VAO);
	memset(&VAO, 0, sizeof VAO);
}
# include <cstdarg>
VAO::VAO(const BO<GL_ARRAY_BUFFER> &VBO, GLsizei stride, size_t attribs, ...)
{
	if(GL_ASSERT(glGenVertexArrays(1, &array)))
	if(GL_ASSERT(glBindVertexArray(array)))
	if(GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, VBO)))
	{
		va_list ap;
		va_start(ap, attribs);
		for(size_t index=0; index<attribs; ++index)
		{
			VBO::A A = va_arg(ap, VBO::A);
			GL_ASSERT(glVertexAttribPointer(index, A.size, A.type, GL_FALSE, stride, A.mp));
			GL_ASSERT(glEnableVertexAttribArray(index));
		}
		va_end(ap);
	}
}
VAO::VAO(size_t buffers, ...)
{
	GLuint index = 0;
	if(GL_ASSERT(glGenVertexArrays(1, &array)))
	if(GL_ASSERT(glBindVertexArray(array)))
	{
		va_list ap;
		va_start(ap, buffers);
		for(size_t i=0; i<buffers; ++i)
		{
			VAO::A A = va_arg(ap, VAO::A);
			glBindBuffer(GL_ARRAY_BUFFER, A.buffer);
			for(size_t j=0; j<A.count; ++j)
			{
				GL_ASSERT(glVertexAttribPointer(index, A.layout[j].size, A.layout[j].type, GL_FALSE, A.stride, A.layout[j].mp));
				GL_ASSERT(glEnableVertexAttribArray(index));
				++ index;
			}
		}
		va_end(ap);
	}
}
/*
void VAO::draw(GLenum mode, GLint first, GLsizei count)
{
	if(ASSERT(array) && GL_ASSERT(glBindVertexArray(array))) switch(type)
	{
		case GL_UNSIGNED_BYTE:
		case GL_UNSIGNED_SHORT:
		case GL_UNSIGNED_INT:
		{
			GL_ASSERT(glDrawElements(mode, count, type, static_cast<char *>(nullptr) + first));
			return;
		}
		default:
			if(ASSERT(!type))
			GL_ASSERT(glDrawArrays(mode, first, count));
			return;
	}
}

void VAO::draw(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
{
	if(ASSERT(array) && GL_ASSERT(glBindVertexArray(array))) switch(type)
	{
		case GL_UNSIGNED_BYTE:
		case GL_UNSIGNED_SHORT:
		case GL_UNSIGNED_INT:
		{
			GL_ASSERT(glDrawElementsInstanced(mode, count, type, static_cast<char *>(nullptr) + first, instancecount));
			return;
		}
		default:
			if(ASSERT(!type))
			GL_ASSERT(glDrawArraysInstanced(mode, first, count, instancecount));
			return;
	}
}*/
VAO::operator GLuint(void) const
{
	return array;
}





/*
# define DATA_USAGE GL_STATIC_DRAW
/////////////////////////////////////////////////////////////////////////////////
VBO<void>::~VBO(void) { if(ID) GL_ASSERT(glDeleteBuffers(1, &ID)); }
VBO<void>::VBO(void) { ID = 0; }
VBO<void>::VBO(const void *p, size_t n)
{
	GL_ASSERT(glGenBuffers(1, &ID));
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, ID));
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, n, p, DATA_USAGE));
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO<void>::operator =(VBO &&a)noexcept
{
	this -> ~ VBO( );
	ID = a.ID;
	a.ID = 0;
}
VBO<void>::operator GLuint(void)const
{
	return ID;
}
/////////////////////////////////////////////////////////////////////////////////
IBO::~IBO(void) { if(ID) GL_ASSERT(glDeleteBuffers(1, &ID)); }
IBO::IBO(void) { ID = 0; }
# define initialize(p, n)				\
glGenBuffers(1, &ID);					\
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);		\
glBufferData(GL_ELEMENT_ARRAY_BUFFER, n, p, DATA_USAGE);
IBO::IBO(const GLubyte *p, size_t n){ initialize(p, n) }
IBO::IBO(const GLushort *p, size_t n){ initialize(p, n) }
IBO::IBO(const GLuint *p, size_t n){ initialize(p, n) }
# undef initialize
void IBO::operator =(IBO &&a)noexcept
{
	this -> ~ IBO( );
	ID = a.ID;
	a.ID = 0;
}
IBO::operator GLuint(void)const
{
	return ID;
}
/////////////////////////////////////////////////////////////////////////////////
VAO::~VAO(void)
{
	if(ID) GL_ASSERT(glDeleteVertexArrays(1, &ID));
}
VAO::VAO(GLenum)
{
	GL_ASSERT(glGenVertexArrays(1, &ID));
	GL_ASSERT(glBindVertexArray(ID));
}
void VAO::clear(void)
{
	if(ID) GL_ASSERT(glBindVertexArray(ID));
	while(ID && N) GL_ASSERT(glDisableVertexAttribArray(--N));
}
VAO::operator GLuint(void)const
{
	return ID;
}*/
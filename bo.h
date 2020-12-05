# pragma once
# include "gl.h"
/////////////////////////////////////////////////////////////////////////////////
template<GLenum T> struct BO
{
	
	constexpr GLenum GL_BUFFER_BINDING(GLenum target)
	{
		switch(target)
		{
		// GL_VERSION_1_5
			case GL_ARRAY_BUFFER: return GL_ARRAY_BUFFER_BINDING;
			case GL_ELEMENT_ARRAY_BUFFER: return GL_ELEMENT_ARRAY_BUFFER_BINDING;
		// GL_VERSION_2_1
			case GL_PIXEL_PACK_BUFFER: return GL_PIXEL_PACK_BUFFER_BINDING;
			case GL_PIXEL_UNPACK_BUFFER: return GL_PIXEL_UNPACK_BUFFER_BINDING;
		// GL_VERSION_3_0
			case GL_TRANSFORM_FEEDBACK_BUFFER: return GL_TRANSFORM_FEEDBACK_BUFFER_BINDING;
		// GL_VERSION_3_1
			case GL_UNIFORM_BUFFER: return GL_UNIFORM_BUFFER_BINDING;
			case GL_TEXTURE_BUFFER: return GL_TEXTURE_BUFFER_BINDING;
			case GL_COPY_READ_BUFFER: return GL_COPY_READ_BUFFER_BINDING;
			case GL_COPY_WRITE_BUFFER: return GL_COPY_WRITE_BUFFER_BINDING;
		// GL_VERSION_4_0
			case GL_DRAW_INDIRECT_BUFFER: return GL_DRAW_INDIRECT_BUFFER_BINDING;
		// GL_VERSION_4_2
			case GL_ATOMIC_COUNTER_BUFFER: return GL_ATOMIC_COUNTER_BUFFER_BINDING;
		// GL_VERSION_4_3
			case GL_DISPATCH_INDIRECT_BUFFER: return GL_DISPATCH_INDIRECT_BUFFER_BINDING;
			case GL_SHADER_STORAGE_BUFFER: return GL_SHADER_STORAGE_BUFFER_BINDING;
		// GL_VERSION_4_4
			case GL_QUERY_BUFFER: return GL_QUERY_BUFFER_BINDING;
		// GL_VERSION_4_6
			case GL_PARAMETER_BUFFER: return GL_PARAMETER_BUFFER_BINDING;
			default: return 0; // GL_INVALID_ENUM
		}
	}
	~
	BO(void)
	{
		if(ID) GL_ASSERT(glDeleteBuffers(1, &ID)), const_cast<GLuint &>(ID) = 0;
	}
	BO(void): ID(0)
	{ }
	BO(BO<T> &&BO) noexcept: ID(BO.ID)
	{
		const_cast<GLuint &>(BO.ID) = 0;
	}
	void operator = (BO<T> &&BO) noexcept
	{
		BO::~BO( );
		const_cast<GLuint &>(ID) = BO.ID;
		const_cast<GLuint &>(BO.ID) = 0;
	}
	// GL_STREAM_DRAW
	// GL_STREAM_READ
	// GL_STREAM_COPY
	// GL_STATIC_DRAW
	// GL_STATIC_READ
	// GL_STATIC_COPY
	// GL_DYNAMIC_DRAW
	// GL_DYNAMIC_READ
	// GL_DYNAMIC_COPY
	BO(GLsizeiptr size, const void *data, GLenum_t usage)
	{
		GL_ASSERT(glGenBuffers(1, &const_cast<GLuint &>(ID))) &&
		GL_ASSERT(glBindBuffer(T, ID)) &&
		GL_ASSERT(glBufferData(T, size, data, usage));
	}
	// GL_MAP_READ_BIT
	// GL_MAP_WRITE_BIT
	// GL_MAP_PERSISTENT_BIT
	// GL_MAP_COHERENT_BIT
	// GL_DYNAMIC_STORAGE_BIT
	// GL_CLIENT_STORAGE_BIT
	BO(GLsizeiptr size, const void *data, GLbitfield_t flags)
	{
		GL_ASSERT(glGenBuffers(1, &const_cast<GLuint &>(ID))) &&
		GL_ASSERT(glBindBuffer(T, ID)) &&
		GL_ASSERT(glBufferStorage(T, size, data, flags));
	}
	// GL_READ_ONLY
	// GL_WRITE_ONLY
	// GL_READ_WRITE
	void *map(GLenum access)
	{
		if(ASSERT(ID) && GL_ASSERT(glBindBuffer(T, ID)))
		if(void *glMapBuffer = ::glMapBuffer(T, access);
		  ASSERT(glMapBuffer) && GL_ASSERT(glMapBuffer))
		return glMapBuffer;
		return nullptr;
	}
	void unmap(void *)
	{
		if(ASSERT(ID) && GL_ASSERT(glBindBuffer(T, ID)))
		if(GLboolean glUnmapBuffer = ::glUnmapBuffer(T);
		  ASSERT(glUnmapBuffer) && GL_ASSERT(glUnmapBuffer));
	}
	operator GLuint(void)const
	{
		return ID;
	}
private:
	const GLuint ID = 0;
};
////////////////////////////////////////////////////////
/*
template<class T> struct VBO : public BO<GL_ARRAY_BUFFER>
{
	VBO(void) = default;
//	template<class...VA> VBO(VA T:: *...SS) assert
	VBO(const T *p, size_t n) : BO<GL_ARRAY_BUFFER>(p, n * sizeof(T)) { }
};
template<class T> struct IBO : public BO<GL_ELEMENT_ARRAY_BUFFER>
{
	IBO(void) = default;
	IBO(const T *p, GLsizeiptr n):
	 BO<GL_ELEMENT_ARRAY_BUFFER>(p, n)
	{ }
};
template<class T>
struct SSBO : public BO<GL_SHADER_STORAGE_BUFFER>
{
	template<class M> SSBO(M T:: *variadic) { }
};
*/

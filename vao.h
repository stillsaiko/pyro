# pragma once
# include <gl.h>
# include "bo.h"
template<class T> struct GLpointer
{
	union
	{
		const void   *mp;
		GLbyte   T:: *hhi;
		GLubyte  T:: *hhu;
		GLshort  T:: *hi;
		GLushort T:: *hu;
		GLint    T:: *i;
		GLuint   T:: *u;
		GLfloat  T:: *f;
		GLdouble T:: *lf;
	};
	GLpointer(GLint    T:: *mp): i(mp) { }
	GLpointer(GLshort  T:: *mp): hi(mp) { }
	GLpointer(GLbyte   T:: *mp): hhi(mp) { }
	GLpointer(GLuint   T:: *mp): u(mp) { }
	GLpointer(GLushort T:: *mp): hu(mp) { }
	GLpointer(GLubyte  T:: *mp): hhu(mp) { }
	GLpointer(GLfloat  T:: *mp): f(mp) { }
	GLpointer(GLdouble T:: *mp): lf(mp) { }
	constexpr operator const void *(void)
	{
		return mp;
	}
};
template<class T> constexpr GLenum GLtype(GLint T:: *){return GL_INT;}
template<class T> constexpr GLenum GLtype(GLshort T:: *){return GL_SHORT;}
template<class T> constexpr GLenum GLtype(GLbyte T:: *){return GL_BYTE;}
template<class T> constexpr GLenum GLtype(GLuint T:: *){return GL_UNSIGNED_INT;}
template<class T> constexpr GLenum GLtype(GLushort T:: *){return GL_UNSIGNED_SHORT;}
template<class T> constexpr GLenum GLtype(GLubyte T:: *){return GL_UNSIGNED_BYTE;}
template<class T> constexpr GLenum GLtype(GLfloat T:: *){return GL_FLOAT;}
template<class T> constexpr GLenum GLtype(GLdouble T:: *){return GL_DOUBLE;}
/*
template<class T, class U> constexpr GLint GLsize(U T:: *) { return 1; }
template<class T, class U, GLint N> constexpr GLint GLsize(U (T:: *)[N]) { return N; }
*/
struct VBO : public BO<GL_ARRAY_BUFFER>
{
	~
	VBO(void);
	VBO(void) = default;
	VBO(VBO &&) noexcept;
	void operator = (VBO &&) noexcept;

	template<class T, class...VA>
	VBO(BO<GL_ARRAY_BUFFER> &&VBO, VA T:: *...ARGS):
	 BO<GL_ARRAY_BUFFER>(static_cast<BO<GL_ARRAY_BUFFER> &&>(VBO)),
	 layout(new A[sizeof...(VA)]{ARGS...}), stride(sizeof(T)), count(sizeof...(VA))
	{ }

	template<size_t N, class T, class...VA>
	VBO(const T (&vertices)[N], VA T:: *...ARGS):
	 BO<GL_ARRAY_BUFFER>(sizeof vertices, vertices, GL_STATIC_DRAW),
	 layout(new A[sizeof...(VA)]{ARGS...}), stride(sizeof(T)), count(sizeof...(VA))
	{ }

private:
	friend class VAO;
	struct A
	{
		GLint size = 0;
		GLenum type = 0;
		const void *mp = nullptr;
		A(void) = default;
		template<class T> A(GLint    T:: *mp): size(1), type(GL_INT), mp((GLint *&) mp) { }
		template<class T> A(GLshort  T:: *mp): size(1), type(GL_SHORT), mp((GLshort *&) mp) { }
		template<class T> A(GLbyte   T:: *mp): size(1), type(GL_BYTE), mp((GLbyte *&) mp) { }
		template<class T> A(GLuint   T:: *mp): size(1), type(GL_UNSIGNED_INT), mp((GLuint  *&) mp) { }
		template<class T> A(GLushort T:: *mp): size(1), type(GL_UNSIGNED_SHORT), mp((GLushort *&) mp) { }
		template<class T> A(GLubyte  T:: *mp): size(1), type(GL_UNSIGNED_BYTE), mp((GLubyte *&) mp) { }
		template<class T> A(GLfloat  T:: *mp): size(1), type(GL_FLOAT), mp((GLfloat *&) mp) { }
		template<class T> A(GLdouble T:: *mp): size(1), type(GL_DOUBLE), mp((GLdouble *&) mp) { }
		template<class T, size_t N> A(GLint   (T:: *mp)[N]): size(N), type(GL_INT), mp((GLint *&) mp) { }
		template<class T, size_t N> A(GLshort (T:: *mp)[N]): size(N), type(GL_SHORT), mp((GLshort *&) mp) { }
		template<class T, size_t N> A(GLbyte  (T:: *mp)[N]): size(N), type(GL_BYTE), mp((GLbyte *&) mp) { }
		template<class T, size_t N> A(GLuint  (T:: *mp)[N]): size(N), type(GL_UNSIGNED_INT), mp((GLuint *&) mp) { }
		template<class T, size_t N> A(GLushort(T:: *mp)[N]): size(N), type(GL_UNSIGNED_SHORT), mp((GLushort *&) mp) { }
		template<class T, size_t N> A(GLubyte (T:: *mp)[N]): size(N), type(GL_UNSIGNED_BYTE), mp((GLubyte *&) mp) { }
		template<class T, size_t N> A(GLfloat (T:: *mp)[N]): size(N), type(GL_FLOAT), mp((GLfloat *&) mp) { }
		template<class T, size_t N> A(GLdouble(T:: *mp)[N]): size(N), type(GL_DOUBLE), mp((GLdouble *&) mp) { }
	} *layout = nullptr;
	GLsizei stride = 0;
	size_t count = 0;
};
/*
struct IBO : public BO<GL_ELEMENT_ARRAY_BUFFER>
{
	const GLenum type;

	IBO(GLsizei count, const GLuint *indices, GLenum_1_5 usage = GL_STATIC_DRAW);
	IBO(GLsizei count, const GLuint *indices, GLbitfield flags =  GL_MAP_READ_BIT|GL_MAP_WRITE_BIT|
								GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);
	IBO(GLsizei count, const GLubyte *indices, GLenum_1_5 usage = GL_STATIC_DRAW);
	IBO(GLsizei count, const GLubyte *indices, GLbitfield flags = GL_MAP_READ_BIT|GL_MAP_WRITE_BIT|
								GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);
	IBO(GLsizei count, const GLushort *indices, GLenum_1_5 usage = GL_STATIC_DRAW);
	IBO(GLsizei count, const GLushort *indices, GLbitfield flags = GL_MAP_READ_BIT|GL_MAP_WRITE_BIT
								|GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);
}; // GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT
*/
struct IBO : public BO<GL_ELEMENT_ARRAY_BUFFER>
{
	IBO(void) = default;
	IBO(BO<GL_ELEMENT_ARRAY_BUFFER> &&IBO, GLenum type);

	template<size_t N>
	IBO(const GLuint (&indices)[N]):
	 BO<GL_ELEMENT_ARRAY_BUFFER>(sizeof indices, indices, GL_STATIC_DRAW),
	 type(GL_UNSIGNED_INT)
	{ }

	template<size_t N>
	IBO(const GLushort (&indices)[N]):
	 BO<GL_ELEMENT_ARRAY_BUFFER>(sizeof indices, indices, GL_STATIC_DRAW),
	 type(GL_UNSIGNED_SHORT)
	{ }

	template<size_t N>
	IBO(const GLubyte (&indices)[N]):
	 BO<GL_ELEMENT_ARRAY_BUFFER>(sizeof indices, indices, GL_STATIC_DRAW),
	 type(GL_UNSIGNED_BYTE)
	{ }
private:
	friend class VAO;
	GLenum type = 0;
};
// ARB_vertex_array_object 3.0
struct VAO
{
	~
	VAO(void);
	VAO(void) = default;
	VAO(VAO &&) noexcept;
	void operator = (VAO &&) noexcept;

	template<class T, class...VA>
	VAO(const BO<GL_ARRAY_BUFFER> &VBO, VA T:: *...ARGS):
	VAO(VBO, sizeof(T), sizeof...(VA), VBO::A(ARGS)...)
	{ }
	
	template<class T, class...VA>
	VAO(const BO<GL_ELEMENT_ARRAY_BUFFER> &IBO, const BO<GL_ARRAY_BUFFER> &VBO, VA T:: *...ARGS):
	VAO(VBO, sizeof(T), sizeof...(VA), VBO::A(ARGS)...)
	{
		GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
	}
	
	template<class...VA>
	VAO(const VBO &VBO, VA...ARGS):
	VAO(sizeof...(VA)+1, static_cast<A>(VBO), static_cast<A>(ARGS)...)
	{ }

	template<class...VA>
	VAO(const BO<GL_ELEMENT_ARRAY_BUFFER> &IBO, const VBO &VBO, VA...ARGS):
	VAO(sizeof...(VA)+1, static_cast<A>(VBO), static_cast<A>(ARGS)...)
	{
		GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
	}

//	void draw(GLenum mode, GLint first, GLsizei count);
//	void draw(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);

	operator GLuint(void) const;
private:
	VAO(const BO<GL_ARRAY_BUFFER> &, GLsizei, size_t, ...);
	VAO(size_t, ...);
	struct A
	{
		GLuint buffer;
		VBO::A *layout;
		GLsizei stride;
		size_t count;
		A(const VBO &);
	};
/*	VAO(const BO<GL_ARRAY_BUFFER> &, GLsizei, GLuint, va_list);
	VAO(const BO<GL_ARRAY_BUFFER> &, GLsizei, GLuint, ...);
	VAO(const BO<GL_ELEMENT_ARRAY_BUFFER> &, const BO<GL_ARRAY_BUFFER> &, GLsizei, GLuint, ...);*/
	GLuint array;
};
/*struct IBO : public BO<GL_ELEMENT_ARRAY_BUFFER>
{
	const GLenum T;
	const GLsizei N;
	IBO(const GLubyte *indices, GLsizei count);
	IBO(const GLushort *indices, GLsizei count);
	IBO(const GLuint *indices, GLsizei count);
};
IBO::IBO(const GLubyte  *indices, GLsizei count): BO<GL_ELEMENT_ARRAY_BUFFER>(count * sizeof *indices, indices), T(GL_UNSIGNED_BYTE),  N(count) { }
IBO::IBO(const GLushort *indices, GLsizei count): BO<GL_ELEMENT_ARRAY_BUFFER>(count * sizeof *indices, indices), T(GL_UNSIGNED_SHORT), N(count) { }
IBO::IBO(const GLuint   *indices, GLsizei count): BO<GL_ELEMENT_ARRAY_BUFFER>(count * sizeof *indices, indices), T(GL_UNSIGNED_INT),   N(count) { }
struct VAO
{
	template<class T, class...VA> VAO(const BO<GL_ELEMENT_ARRAY_BUFFER> &IBO,
	                                  const BO<GL_ARRAY_BUFFER> &VBO, VA T:: *...ARGS) { }
	template<class T, class...VA> VAO(const BO<GL_ARRAY_BUFFER> &VBO, VA T:: *...ARGS) { }
	template<class...VA> VAO(const IBO &IBO, const VBO<VA> &...ARGS) { }
	template<class...VA> VAO(const VBO<VA> &...ARGS) { }
};*/
/////////////////////////////////////////////////////////////////////////////////
/*
template<class> constexpr GLenum GLtype(void);
template<> constexpr GLenum GLtype<GLint>   (void){return GL_INT;}
template<> constexpr GLenum GLtype<GLshort> (void){return GL_SHORT;}
template<> constexpr GLenum GLtype<GLbyte>  (void){return GL_BYTE;}
template<> constexpr GLenum GLtype<GLuint>  (void){return GL_UNSIGNED_INT;}
template<> constexpr GLenum GLtype<GLushort>(void){return GL_UNSIGNED_SHORT;}
template<> constexpr GLenum GLtype<GLubyte> (void){return GL_UNSIGNED_BYTE;}
template<> constexpr GLenum GLtype<GLfloat> (void){return GL_FLOAT;}
template<> constexpr GLenum GLtype<GLdouble>(void){return GL_DOUBLE;}
template<class T> constexpr GLenum GLtype<T *>    (void){return GLtype<T>( );}*/
//template<class T> constexpr GLenum GLtype<const T>(void){return GLtype<T>( );}
/////////////////////////////////////////////////////////////////////////////////
/*
# include <typeinfo>
struct VA
{
	const GLint size;
	const GLenum type;
	const GLsizei stride;
	const void *pointer;
	const size_t st_hash_code;
	template<class st, class m> VA(m st:: *p):
		size(sizeof(m) / alignof(m)),
		type(GLtype<m>( )),
		stride(sizeof(st)),
		pointer(reinterpret_cast<void *&>(p)),
		st_hash_code(typeid(st).hash_code( ))
	{ }
};
/////////////////////////////////////////////////////////////////////////////////
template<class> struct VBO;
/////////////////////////////////////////////////////////////////////////////////
template<> struct VBO<void>
{
	virtual ~ // #@?!
	VBO(void);
	VBO(void);
	VBO(const void *, size_t);
//	void operator( )(const void *, size_t);
	void operator = (VBO<void> &&)noexcept;
	operator GLuint(void)const;
protected:
	GLuint ID;
};
/////////////////////////////////////////////////////////////////////////////////
template<class T> struct VBO : public VBO<void>
{
	VBO(void) = default;
	VBO(const T *p, size_t n): VBO<void>(p, n*sizeof(T)) { }
//	void operator( )(const T *p, size_t n) { VBO<void>::operator( )(p, n*sizeof(T)); }
};
/////////////////////////////////////////////////////////////////////////////////
struct IBO
{
	~
	IBO(void);
	IBO(void);
	IBO(const GLubyte *, size_t); // GL_UNSIGNED_BYTE
	IBO(const GLushort *, size_t); // GL_UNSIGNED_SHORT
	IBO(const GLuint *, size_t); // GL_UNSIGNED_INT
	void operator = (IBO &&)noexcept;
	operator GLuint(void)const;
protected:
	GLuint ID;
};
/////////////////////////////////////////////////////////////////////////////////
# include <cstdio>
// include <initializer_list>
class VAO
{
	GLuint ID = 0;
	int N = 0;
	template<int...> struct I { };
	template<int N, int...VA> struct II : public II<N-1, N-1, VA...> { };
	template<       int...VA> struct II<0, VA...> { typedef I<VA...> T; };
	template<int = 0> struct A
	{
		int i=0, n=1, s=0;
		void **p=nullptr;
		template<class T> constexpr operator T(void) // struct as vector-attrib
		{
			// __is_enum
			// __is_class
			if constexpr(__is_pod(T)) return {A {i, sizeof(T) / alignof(T), s, p}};
			auto &ref = reinterpret_cast<T *&>(*p);
			glVertexAttribPointer(i, n, GLtype<T>( ), GL_FALSE, s, ref);
			glEnableVertexAttribArray(i);
			ref += n;
			return { };
		}
	};
	template<class T, int I, int...VA> decltype(T {A<I> { }, A<VA> { }...}) enable(const VBO<T> &VBO, VAO::I<I, VA...>)
	{
		printf("warning: implicit %s:: *...attribs\n", typeid(T).name( ));
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		void *p = nullptr;
		return {A<I> {N++, 1, sizeof(T), &p}, A<VA> {N++, 1, sizeof(T), &p}...};
	}
	template<class T, int...VA> void enable(const VBO<T> &B, I<VA...>)
	{
		enable<T>(B, typename II<sizeof...(VA)-1>::T { });
	}
public:
	~
	VAO(void); // dtor
	VAO(void) = default;
	VAO(GLenum);
	template<class T, class...VA> VAO(const VBO<T> &B0, const VBO<VA> &...BB): VAO(GL_VERTEX_ARRAY)
	{
		(enable<T> (B0, typename II<sizeof(T)>::T { }));
		if constexpr(sizeof...(VA))
		(enable<VA>(BB, typename II<sizeof(VA)>::T { }), ...);
	}
	template<class T, class M, class...VA> VAO(const VBO<T> &B, M T:: *A0, VA T:: *...AA): VAO(GL_VERTEX_ARRAY)
	{
		enable(B, A0, AA...);
	}
	template<class T, class...VA> void enable(const VBO<T> &B, VA T:: *...AA)
	{
		glBindBuffer(GL_ARRAY_BUFFER, B);
		(A<> {N++, sizeof(VA)/alignof(VA), sizeof(T), &reinterpret_cast<void *&>(AA)}.operator VA( ), ...);
	}
	void clear(void); // NEW
	operator GLuint(void)const;
//////////////////////////////////////////////////
/*	template<size_t N, class...T> VAO(const VA(&VAs)[N], const VBO<T> &...VBOs)
	{
		GLuint bufs[sizeof...(T)] {VBOs...};
		size_t hash_code[sizeof...(T)] {typeid(T).hash_code( )...};
		for(size_t k=0; k<sizeof...(T); ++k)
		{
			glBindBuffer(GL_ARRAY_BUFFER, bufs[k]);
			for(size_t i=0; i<N; ++i)
			if(VAs[i].st_hash_code == hash_code[k]) // #@?!
			{
				glVertexAttribPointer(i, VAs[i].size, VAs[i].type, GL_FALSE, VAs[i].stride, VAs[i].pointer)
				glEnableVertexAttribArray(i);
			}
		}
	}
	GLuint ID;
	template<class...T> VAO(std::initializer_list<VA> il, const VBO<T> &...VBOs)
	{
		GLuint ID[sizeof...T] { VBOs... };
		size_t hash_code[sizeof...T] { typeid(T).hash_code( )... };
		std::initializer_list<VA>::iterator i = il.begin( );
		for(size_t k(0); k < sizeof...T; ++ k)
		{
			glBindBuffer(GL_ARRAY_BUFFER, ID[k]);
			for(il)
			glVertexAttribPointer(i - il.begin( ), ...);
		}


		size_t hash_code[sizeof...T] { typeid(T).hash_code( )... };
		GLuint ID[sizeof...T] { VBOs... };
		for(size_t k(0); k < sizeof...T; ++ k)
		{
			while(hash_code[k] == i->hash_code)
			{
				glVertexAttribPointer(n, i->size, i->type, GL_FALSE, i->stride, i->pointer);
			}
		}

		GLuint array_buffer_binding;
		glGetIntegerv(GL_ARRAY_BUFER_BINDING, &array_buffer_binding);
		for(size_t k = 0; k < sizeof...T; ++ k)
		{
			if(array_buffer_binding != ID[k])
			glBindBuffer(GL_ARRAY_BUFFER, ID[k]);
			for(auto & a : il) if(hash_code[k] == a.hash_code)
			{
				glVertexAttribPointer(i, a.size, a.type, GL_FALSE, a.stride, a.pointer);
				glEnableVertexAttribArray(i ++);
			}
		}
	}
	template<class T, class...VA>
	VAO(VBO<T>, VA T::*...args)
	{
		glGenVertexArrays(1, &ID);
		glBindVertexArray(ID);
		GLint size[sizeof...args] { sizeof(VA)/alignof(VA)... };
		GLenum type[sizeof...args] { GLtype<VA>( )... };
		GLsizei stride[sizeof...args] { sizeof(T) };
		for(GLuint i=0; i<sizeof...args; ++i)
		{
			glVertexAttribPointer(i, size[i], type[i], GL_FALSE, stride, offs);
			glEnableVertexAttribArray(i);
		}
	}
};*/
/////////////////////////////////////////////////////////////////////////////////
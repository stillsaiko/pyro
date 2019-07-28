# pragma once
# include <initializer_list>
# include <cstring>
# include "rc.h"
# include <cstdarg>
// struct foo { ... }
// using pyro::shared
// LEX expr_list({"[\a]\r\n", "\a=\a\r\n", ";\a\r\n"}, RC(".ini"))
// for( LEX::X & expr : expr_list )
//	if( expr == 1 ) // 2nd syntax from initializer_list
//	 shared<foo>[B40LL(expr.A[0])] = foo((const char *)expr.A[1])
struct LEX {
	struct G { // syntax tree
		unsigned grammar = 0u ; // (-1) // enum (grammar-index)
		const char * keyword = nullptr ; // const string
	//	std::vector<G> fork ; // null-terminated delimit array
		G * fork = nullptr ;
		unsigned n = 0u ;
	} root ; // root.keyword = null
	struct A { // \a (varying argument)
		A(const char *, size_t);
		const char * trim(const char * charset = " \t\r");
		double as_double(void);
		long as_long(void);
		bool equals(const char * c_str);
	// const sugar
		operator const char * (void)const { return raw ; }
		const char & operator[ ](size_t i)const { return (raw)[i]; }
	private:
		char * raw = nullptr ; // non-const
		char * __trim = nullptr ; // private
	};
	struct X { // expr
		unsigned G = 0xffffffff ; // syntax enum // enum (grammar-index)
		LEX::A * A = nullptr ; // '\a', '\a', '\a', ... // arguments
		char * ascii = nullptr ; // buffer !!!!!!!!!!
	// sugar
		inline operator unsigned(void){ return G ; }
		inline decltype(*A)operator[ ](size_t i){ return A[i]; }
	} * Xs = nullptr ; // expr list
	unsigned Xn = 0u ; // expr count
// const sugar
	inline const X * begin(void)const{ return Xs ; }
	inline const X * end(void)const{ return Xs + Xn ; }
	inline const X & operator[ ](size_t i)const{ return Xs[i]; }
// ...
	~
	LEX(void);
	LEX(void);
	LEX(std::initializer_list<const char*> Gs, RC&&);
	unsigned insert(intptr_t, const char * fmt, ...); // one expr
	unsigned remove(intptr_t); // one expr
	size_t save(const char * filename);
	void append(const char * fmt, ...);
	void insert(unsigned index, unsigned G, va_list);
// sugar
	inline void insert(unsigned index, unsigned G, ...){
		va_list va ;
		va_start(va, G);
		insert(index, G, va);
		va_end(va);
	}
	inline void append(unsigned G, ...){
		va_list va ;
		va_start(va, G);
		insert(Xn, G, va);
		va_end(va);
	}
private:
	size_t parse(const char * a, const size_t n, X * out);
};

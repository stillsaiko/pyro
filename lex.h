# pragma once
# include <initializer_list>
# include <cstring>
/*template<class G = unsigned, class S = double> struct LEX {
	struct T {
		G G ; // enum (grammar-index)
		void ** A ; // arguments
		S & as_v(size_t n = 0u);
		char & as_a(size_t n = 0u);
	};
	LEX(std::initializer_list<const char *> g, const char * a, size_t n = 0u);
	const T * begin(void)const ;
	const T * end(void)const ;
private:
//	const char * a ;
//	size_t n ;
//	char delimiter ;
	size_t a(const char*str, size_t len, char*val, unsigned mul, char til);
	size_t v(const char*str, size_t len, S*val, unsigned mul, char del);
	T * tok = nullptr ;
	size_t len = 0u ;
};*/
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
		unsigned grammar = 0u ; // (-1)
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
		unsigned G = 0xffffffff ; // syntax enum
		LEX::A * A = nullptr ; // '\a', '\a', '\a', ...
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
//	size_t parse(const char * a, size_t n, X * out, G * node);
};
/*template<class T = unsigned> struct LEX {
	struct L {
		T syntax ;
		unsigned argc ;
		const char ** args ;
	};
	~
	LEX(void);
	LEX(void);
	LEX(std::initializer_list<char const*>, RC&&);
	void operator = (LEX<T>&&)noexcept ;
	L& operator[ ](size_t);
private:
	L * array = nullptr ;
	size_t length = 0u ;
	unsigned long long flag[4] {0}; // 256 bits
};*/
//# include "lex.inl"

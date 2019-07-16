# include "lex.h"
# include <vector>
# include <cassert>
// A
LEX::A::A(const char * a, size_t n){
	raw = (char *)memcpy(new char[n+1], a, n);
	raw[n] = '\0';
	__trim = nullptr ;
}
const char * LEX::A::trim(const char * trim){
	if( __trim )delete[ ]
		__trim ;
	char const * p = raw ;
	while([&](char x){
		const char * t = trim ;
		while(*t)if( *t++ == x )
		return true ; // haha
		return false ;
 	}(*p)) ++ p ;
	size_t n = strlen(p);
	while([&](char x){
		const char * t = trim ;
		while(*t)if( *t++ == x )return true ;
		return false ;
 	}( p[n-1] )) -- n ;
	__trim = new char[n+1]; // RELEASE IT PLEASE !!!!!!!!!!!1
	memcpy(__trim, p, n);
	__trim[n] = '\0';
	return __trim ;
}
double LEX::A::as_double(void){
	return 0.0;
}
long LEX::A::as_long(void){
	char const * p = raw ;
	long val = 0L ;
	while( *p ){
		if( *p >= '0' && *p <= '9' ){
			val *= 10 ;
			val += *p - '0' ;
		}
		++ p ;
	}
	return val ;
}
bool LEX::A::equals(const char * cstr){
	const char * p = raw ;
	if(cstr && p)while(*p){
		if(*p != *cstr)switch(*p){
			case ' ':
			case '\t':
			case '\r':
				++ p ;
				continue ;
			default:
				return false ;
		}
		return!strncmp(cstr, p, strlen(cstr));
	}
	return false ;
}
/*# include <type_traits> // remove_reference
double std::remove_reference<decltype(*LEX::X::A)>::type::as_double(void){
	return 0.0;
}
long std::remove_reference<decltype(*LEX::X::A)>::type::as_long(void){
	char const * p = ptr ;
	long val = 0L ;
	while( *p ){
		if( *p >= '0' && *p <= '9' ){
			val *= 10 ;
			val += *p - '0' ;
		}
		++ p ;
	}
	return val ;
}*/
// LEX
LEX::~LEX(void){
	// dtor
}
LEX::LEX(void){
	// default ctor
}
# include <functional>
LEX::LEX(std::initializer_list<char const*> il, RC&& a){
	{
		bool a(false);
		for(const char * g : il){
			assert(g);
			assert(strlen(g));
			assert(g[strlen(g)-1] != '\a');
			if( g[0] == '\a' ) a = true ;  // once  begins \a
			if( a ) assert(g[0] == '\a'); // always begins \a
		}
	}
	size_t Gn(0u); // size of grammar string
	for(const char * g : il) Gn += strlen(g) + 1u ;
	char * Gm = new char[Gn]; // alloc writable
	{
		char * p = Gm ;
		unsigned grammar(0u);
		for(const char * g : il){
			strcpy(p, g);
		// ...
			G * node = & root ;
			if( p[0] == '\a' ){
			// fork new branche
				node->fork = (G *)realloc(node->fork, ++node->n*sizeof(G));
				node = node->fork + node->n - 1u ; // root -> '\a' -> ...
				memset(node, 0, sizeof(G)); // NEW
				node->keyword = nullptr;//"";
			}
//			if( p[0] > '\0' )
			if( const char * tok = strtok(p, "\a") )
			do node = [ ](G * node, const char * tok){
				assert(node); // NEW
				if( node->fork ) // NEW
				for( unsigned i(0u); i < node->n ; ++i )
					if( !node->fork[i].keyword || // NEW
						!strcmp(node->fork[i].keyword, tok) )
						return node->fork + i ;
			// fork new branche
				node->fork = (G *)realloc(node->fork, ++node->n*sizeof(G));
				node = node->fork + node->n - 1u ; // root -> ... -> leaf
				new(node)G ;
			//	memset(node, 0, sizeof(G));
				node->keyword = tok ;
				return node ;
			}(node, tok);
			while( tok = strtok(nullptr, "\a") );
		// ...
			node->grammar = ++ grammar ; // grammar ++
			p += strlen(g) + 1u ;
		}
		assert(p == Gm + Gn);
	}
	// ...
/*	std::function<void(G*,unsigned)> lambda ;
	lambda = [&](G * node, unsigned tab){
		if( node->keyword ){
			for(unsigned i=0u;i<tab;++i)
				printf("\t");
			printf("\"");
			for(int i=0;node->keyword[i];++i)
			switch(node->keyword[i]){
			case '\a':	printf("\\a");					break;
			case '\b':	printf("\\b");					break;
			case '\f':	printf("\\f");					break;
			case '\t':	printf("\\t");					break;
			case '\v':	printf("\\v");					break;
			case '\r':	printf("\\r");					break;
			case '\n':	printf("\\n");					break;
			default:	printf("%c", node->keyword[i]);	break;
			}
			printf("\"");
			printf("\n");
		}
		for(unsigned i=0u; i<node->n; ++i)
			lambda(node->fork + i, tab + 1u);
	};
	lambda(&root, -1);*/
	// ...
	const char * p = &a[0];
	size_t n = a.n ;
	while( n ){
		Xs = (X *)realloc(Xs, ++Xn*sizeof(X));
		new(Xs+Xn-1)X;
	//	memset(Xs+Xn-1, 0, sizeof(X));
		size_t o = parse(p, n, Xs + Xn - 1u);
		if( o == 0u )break ;
		n -= o ;
		p += o ;
	}
}
unsigned LEX::insert(intptr_t i, const char * fmt, ...){
	char buf[512]; // lol?
	va_list va ;
	va_start(va, fmt);
	vsprintf(buf, fmt, va);
	va_end(va);
	// ...
	Xs = (X *)realloc(Xs, ++Xn*sizeof(X));
	memmove(Xs+i+1, Xs+i, (Xn-i-1)*sizeof(X));
	memset(Xs+i, 0, sizeof(X));
	size_t offset = parse(buf, strlen(buf), Xs+i);
	// ...
	return Xs[i].G ; // return grammar-index
}
unsigned LEX::remove(intptr_t i){
	assert(Xs && Xn);
	unsigned G = Xs[i].G ;
	memmove(Xs+i, Xs+i+1, (Xn-i-1)*sizeof(X));
	Xs = (X *)realloc(Xs, --Xn*sizeof(X));
	return G ;
}
# include <deque>
size_t LEX::save(char const * filename){
	std::deque<const char *> stack ;
	std::function<bool(G *, unsigned, bool)> lambda = [&](G * node, unsigned G, bool initial){
		// break on `Xs[i].G == node->grammar-1'
		if( ! node->n ){
			if( node->grammar-1 == G )
				stack.push_back(node->keyword);
			return node->grammar-1 == G ;
		}
		// going through whole syntax tree
		for(size_t n(0u); n < node->n ; ++n){
			// push & pop keywords
			if(!initial)stack.push_back(node->keyword);
			if( lambda(node->fork + n, G, false) )
				return true ;
			if(!initial)stack.pop_back( );
		}
		return false ;
	};
//	decltype(X::A) A ;
	FILE * f = fopen(filename, "wb");
	size_t written(0u);
	for(size_t i(0u); i<Xn; ++i){
		if( lambda(&root, Xs[i].G, true) ){
			// fold `stack' keywords with `X[i].A'
			if( const char * keyw = stack.front( ) ){ // 1
				written += fwrite(keyw, 1, strlen(keyw), f); // 1
			}
			stack.pop_front( ); // 1
			size_t offset(0u);
			while( !stack.empty( ) ){
				const char * ptr = Xs[i].A[offset++] ;
				written += fwrite(ptr, 1, strlen(ptr), f);
				if( const char * keyw = stack.front( ) ){ // 2
					written += fwrite(keyw, 1, strlen(keyw), f); // 2
				}
				stack.pop_front( ); // 2
			}
		}
//		stack.clear( );
	}
	fclose(f);
	return written ;
}
// private
size_t LEX::parse(char const * a, const size_t n, X * out){
	unsigned An(0u);
	struct A {
		const char * p ;
		unsigned n ;
	} * As(nullptr);
	char const * p(a);
	auto alarm_until = [this](const char * a, size_t n, G * node){
		const char * p = a ;
		while( p - a < n ){
			for(unsigned i(0u); i < node->n; ++i)
			 if( auto * key = node->fork[i].keyword ){
				size_t len = strlen(key);
				if(len > n + a - p){
					printf("%i...", len - n + p - a);
					continue ;
				}
				if( !strncmp(p, key, len) ){
					// store alarm string
					return p - a ;
				} else {
					continue ;
				}
			 } else {
				assert(false); // !!!!!!!!!!!!
			}
			++ p ;
		}
		return 0;
		return p - a ;
	};
	if( G * super = &root ; G * node = super->fork )do {
		if( node->keyword ){
			size_t len = strlen(node->keyword);
			if( p + len > a + n || strncmp(p, node->keyword, len) ){
				++ node ;
				continue ;
			}
			out->G = node->grammar - 1 ; // NEW
			p += len ;
		}
		size_t o = alarm_until(p, n + a - p, node);

			As = (A *) realloc(As, ++An*sizeof(A));
			new(As+An-1)A{p,o};
		//	As[An-1].p = p ; As[An-1].n = o ;
			p += o ;

		if( node->fork ) // NEW
			node = ( super = node )->fork ;
	} while( node - super->fork < super->n );
 // copy............
	assert(out);
	assert(out->A == nullptr);
	out->A = (LEX::A *)malloc(sizeof(LEX::A)*An);
	//new std::remove_reference<decltype(*out->A)>::type[An];
	for(unsigned n(0u); n < An; ++n){
//		A & a = As[n];
	//	printf("As[%u].p`%s' As[%n].n`%u'\n", n, As[n].p, n, As[n].n);
		new (out->A + n) LEX::A (As[n].p, As[n].n);
//		out->A[n].raw = (char*)memcpy(new char[a.n+1], a.p, a.n); // RELEASE IT PLEASE !!!!!!!!!
//		const_cast<char*&>(out->A[n].raw)[a.n] = '\0';
	}
	free(As);
	return p - a ;
}
/*size_t LEX::a(const char*str, size_t len, char*val, unsigned mul, char til){
	assert(str);
	assert(val);
	const char * ptr = str ;
	while(ptr - str < len && ptr - str < mul){
		if( * ptr == til )break ;
		val[ptr - str] = * ptr ;
		++ ptr ;
	}
	return ptr - str ;
}
# include <cmath> // NAN
size_t LEX::v(const char*str, size_t len, double*val, unsigned mul, char del){
	assert(str);
	assert(val);
	const char * ptr = str ;
	while(ptr - str < len){
		if( * ptr == del ){
			++ val ;
			-- mul ;
			++ ptr ;
			continue ;
		}
		if( * ptr >= '0' && * ptr <= '9' ){
			* val = * ptr - '0';
			++ ptr ;
			continue ;
		}
		if( * ptr == ' ' || * ptr == '\t' || * ptr == '\r' ){
			++ ptr ;
			continue ;
		}
		while( mul ){
			-- mul ;
			* val ++ = NAN ;
		}
		break ;
	}
	return ptr - str ;
}*/

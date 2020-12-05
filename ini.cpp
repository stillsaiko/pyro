# include "ini.h"
INI::K::K(B40LL&& L, const LEX::A & R): B40LL(L), LEX::A(R) { }
// ...
INI::S::~S(void)noexcept {
	for(size_t n=0UL; n<Ln; ++n)
		L[n].~K( );
	if(L)
		free(L);
	L = nullptr;
	Ln = 0UL;
}
INI::S::S(B40LL&& S): B40LL(S){ }
# include <memory> // std::move
void INI::S::insert(intptr_t i, B40LL&& x, const LEX::A & y){
	if( i > Ln )
		i = Ln ;
# pragma warning(suppress: 6308)
	L = (K *)realloc(L, ++ Ln * sizeof(K));
	memmove(L + i + 1, L + i, Ln - i - 1); // * sizeof(K) ???
# pragma warning(suppress: 28182)
	L[i] = K(std::move(x), y);
}

INI::K * INI::S::operator[ ](unsigned long long K){
	for(auto p(L); (p < L + Ln); ++p)
		if( *p == K )return p ;
	return nullptr ;
}
INI::K * INI::S::begin(void){ return L; }
INI::K * INI::S::end(void){ return L + Ln; }
INI::~INI(void)noexcept {
	for(size_t n=0UL; n<Ln; ++n)
		L[n].~S( );
	if(L)
		free(L);
	L = nullptr;
	Ln = 0UL;
} 
INI::INI(void){ }
# include <cstdio> // printf
INI::INI(RC&& a){
	LEX Xs(std::move(a), {"[\a]\a\n", ";\a\n", "\a=\a\n"});
	// prepare section labels
	for(const LEX::X & X : Xs)switch(X.G){
		case 0: // section
# pragma warning(suppress: 6308)
			L = (S *)realloc(L, ++ Ln * sizeof(S));
			new (L+Ln-1) S( B40LL(X.A[0].trim(" \t\r")) );
			break ;
		case 1: // comment
			printf("warning: *.ini ;%s\n", (const char *)X.A[0]);
			break ;
		case 2: // key (property)
			if( Ln == 0u ){
# pragma warning(suppress: 6308)
				L = (S *)realloc(L, ++ Ln * sizeof(S));
				new (L+Ln-1) S( B40LL(nullptr) ); // nullptr
			}
			L[Ln-1].insert(
				L[Ln-1].end( ) - L[Ln-1].begin( ),
				B40LL( X.A[0].trim(" \t\r") ), X.A[1]
			);
//			{ // first time testing `c_str'
//				char buf[13U];
//				L[Ln-1].end( )[-1].c_str(buf);
//				printf(" %s = %s\n", buf, L[Ln-1].end( )[-1].trim(" \t\r"));
//			}
			break ;
		default:
			// error expr
			break ;
	}
}
INI::INI(INI&& a)noexcept {
	L = a.L; a.L = nullptr;
	Ln = a.Ln; a.Ln = 0UL;
}
void INI::operator = (INI&& a)noexcept {
	this->~INI( ); // ~
	L = a.L; a.L = nullptr;
	Ln = a.Ln; a.Ln = 0UL;
}
INI::S & INI::operator[ ](unsigned long long K){
	for(auto p(L); (p < L + Ln); ++p)
		if( *p == K )return *p ;
	return *(S *)nullptr ; // error
}
INI::S * INI::begin(void){ return L; }
INI::S * INI::end(void){ return L + Ln; }
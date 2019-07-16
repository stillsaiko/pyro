# pragma once
# include <new> // new (placement) int( )
# include <cstring> // memmove
# include "rc.h"
template<class T> struct shared_t {
	unsigned long long * U = nullptr ;
	T * A = nullptr ;
	size_t n = 0UL ;
	~ shared_t(void){
		if( n ){ // another dtor missing here (malloc/free)
			if( U )delete[ ] U ; // release
			if( A )delete[ ] A ; // release
		}
	}
	T & operator[ ](unsigned long long ULL){
		for(size_t i(0UL); (i < n); ++i) // o(n)
			if( U[i] == ULL )return A[i];
	// realloc
		A = (T *)realloc(A, ++ n * sizeof(T)); // alloc
		U = (unsigned long long *)realloc(U, n // alloc
	* sizeof(unsigned long long));
		U[n-1] = ULL ;
		return * new (A + n - 1) T ( ); // default ctor(void)
	}
	bool remove(unsigned long long ULL){ // dtor missing in here
		for(size_t i(0UL); (i < n); ++i) // o(n)
			if( U[i] == ULL ){
				memmove(U+i, U+i+1, (n-i-1)*sizeof(unsigned long long));
				memmove(A+i, A+i+1, (n-i-1)*sizeof(T));
				A = (T *)realloc(A, -- n * sizeof(T)); // alloc
				U = (unsigned long long *)realloc(U, n // alloc
			* sizeof(unsigned long long));
				return true ;
			}
		return false ;
	}
	T * begin(void){
		return A ? A : nullptr ;
	}
	T * end(void){
		return A ? A + n : nullptr ;
			// !A != !n ? nullptr : A + n
	}
};
template<class T> static inline shared_t<T> shared ;
// RAM<monster_t>[B40LL("kurum")].upgrade_power(+2);
// RAM<INI>[B40LL("wnd")]->operator[ ](0ULL)[B40LL("width")]->as_long( )
// RAM<INI>[B40LL("wnd")][0ULL][B40LL("width")]->as_long( )
// RAM<INI>.emplace(...)
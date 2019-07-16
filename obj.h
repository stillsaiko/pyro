# pragma once
# include "rc.h"
struct V3 { float V[3]; };
struct V3VT2 { float V[3]; float VT[2]; };
struct V3VN3 { float V[3]; float VN[3]; };
struct V3VT2VN3 { float V[3]; float VT[2]; float VN[3]; };
# include <type_traits> // std::conditional
# include "lex.h" // no thanks
template<class T> struct OBJ {
	const unsigned n = 0u ;
	T * a = nullptr ;
	enum : unsigned {
		V3			= 3u,
		V3VT2		= 5u, // isVT2 -> sizeof(T)/alignof(T)%V3==2
		V3VN3		= 6u, // isVN3 -> sizeof(T)/alignof(T)/V3==3
		V3VT2VN3	= 8u
	};
/*	enum G {
		VT,
		VN,
		V,
		F,
		G_LEN
	};*/
	static_assert(
		alignof(T) == sizeof(double) ||
		alignof(T) == sizeof(float), "axiom mismatch");
	static_assert(
		sizeof(T)/alignof(T)==V3	||
		sizeof(T)/alignof(T)==V3VT2	||
		sizeof(T)/alignof(T)==V3VN3	||
		sizeof(T)/alignof(T)==V3VT2VN3, "axiom mismatch");
	typedef std::conditional<alignof(T)/sizeof(double), double, float> S ;
// decl
	inline OBJ(RC&& a);
	inline size_t f(size_t offset, LEX::A * A, S * Vs, S * VTs, S * VNs);
};
# include "lex.h"
# include "obj.inl"
# pragma once
/*
# include <cstdint>
# define register(typename)	\
 operator int8_t   (void);	\
 operator int16_t  (void);	\
 operator int32_t  (void);	\
 operator int64_t  (void);	\
 operator int128_t (void);	\
 operator int256_t (void);	\
 operator uint8_t  (void);	\
 operator uint16_t (void);	\
 operator uint32_t (void);	\
 operator uint64_t (void);	\
 operator uint128_t(void);	\
 operator uint256_t(void);
 struct alignas(32)  int256_t; // NEW
 struct alignas(32) uint256_t; // NEW
 struct alignas(16)  int128_t;
 struct alignas(16) uint128_t
 {
	register(uint128_t)
	uint128_t(bool);
	uint128_t(uint8_t);	uint128_t(int8_t);
	uint128_t(uint16_t);	uint128_t(int16_t);
	uint128_t(uint32_t);	uint128_t(int32_t);
	uint128_t(uint64_t);	uint128_t(int64_t);
				uint128_t(int128_t);
	uint128_t operator + (void);
	uint128_t operator ++ (int);
	uint128_t operator - (void);
	uint128_t operator -- (int);
	uint128_t operator ~ (void);
	bool      operator ! (void);
protected:
	uint128_t(uint64_t, uint64_t);
 };
 struct alignas(32)  int256_t;
 struct alignas(32) uint256_t
 {
	uint256_t(bool);
	uint256_t(uint8_t);
	uint256_t(uint16_t);
	uint256_t(uint32_t);
	uint256_t(uint64_t);
	uint256_t(uint128_t);
	uint256_t(int256_t);
	uint256_t(int128_t);
	uint256_t(int64_t);
	uint256_t(int32_t);
	uint256_t(int16_t);
	uint256_t(int8_t);
	uint256_t operator + (void);
	uint256_t operator ++ (int);
	uint256_t operator - (void);
	uint256_t operator -- (int);
	uint256_t operator ~ (void);
	bool      operator ! (void);
protected:
	uint256_t(uint128_t, uint128_t);
 };
 struct alignas(16) int128_t
 {
	int128_t(bool);
	int128_t(int8_t);
	int128_t(int16_t);
	int128_t(int32_t);
	int128_t(int64_t);
	int128_t(uint128_t);
	int128_t(uint64_t);
	int128_t(uint32_t);
	int128_t(uint16_t);
	int128_t(uint8_t);
	int128_t operator + (void);
	int128_t operator ++ (int);
	int128_t operator - (void);
	int128_t operator -- (int);
	int128_t operator ~ (void);
	bool     operator ! (void);
 };
 struct alignas(32) int256_t
 {
	int256_t(bool);
	int256_t(int8_t);
	int256_t(int16_t);
	int256_t(int32_t);
	int256_t(int64_t);
	int256_t(int128_t);
	int256_t(uint256_t);
	int256_t(uint128_t);
	int256_t(uint64_t);
	int256_t(uint32_t);
	int256_t(uint16_t);
	int256_t(uint8_t);
	int256_t operator + (void);
	int256_t operator ++ (int);
	int256_t operator - (void);
	int256_t operator -- (int);
	int256_t operator ~ (void);
	bool     operator ! (void);
 };
// einfach mal zwischen durch -- o gott ey
namespace pyro
{
	template<size_t> struct i { typedef void T; };
	template<> struct i<0x01> { typedef int8_t T; };
	template<> struct i<0x02> { typedef int16_t T; };
	template<> struct i<0x04> { typedef int32_t T; };
	template<> struct i<0x08> { typedef int64_t T; };
	template<> struct i<0x10> { typedef int128_t T; };
	template<> struct i<0x20> { typedef int256_t T; };
	template<class T> auto align_i(T *ptr)
	{
		return reinterpret_cast<typename i<alignof(T)>::T *>(ptr);
	}
	template<class T> auto align_i(T& ref)
	{
		return reinterpret_cast<typename i<alignof(T)>::T &>(ref);
	}
	template<size_t> struct u { typedef void T; };
	template<> struct u<0x01> { typedef uint8_t T; };
	template<> struct u<0x02> { typedef uint16_t T; };
	template<> struct u<0x04> { typedef uint32_t T; };
	template<> struct u<0x08> { typedef uint64_t T; };
	template<> struct u<0x10> { typedef uint128_t T; };
	template<> struct u<0x20> { typedef uint256_t T; };
	template<class T> auto align_u(T *ptr)
	{
		return reinterpret_cast<typename u<alignof(T)>::T *>(ptr);
	}
	template<class T> auto align_u(T& ref)
	{
		return reinterpret_cast<typename u<alignof(T)>::T &>(ref);
	}
	template<size_t> struct f { typedef void T; };
	template<> struct f<0x04> { typedef float T; };
	template<> struct f<0x08> { typedef double T; };
	template<class T> auto align_f(T *ptr)
	{
		return reinterpret_cast<typename f<alignof(T)>::T *>(ptr);
	}
	template<class T> auto align_f(T& ref)
	{
		return reinterpret_cast<typename f<alignof(T)>::T &>(ref);
	}
	template<class T> struct align
	{
		typedef typename i<alignof(T)>::T i;
		typedef typename u<alignof(T)>::T u;
		typedef typename f<alignof(T)>::T f;
	};
}
# define volatile(operator)							\
 // unsigned unsigned 128							\
 auto operator (uint8_t a, uint128_t u) { return operator (uint128_t(a), u); }	\
 auto operator (uint16_t a, uint128_t u){ return operator (uint128_t(a), u); }	\
 auto operator (uint32_t a, uint128_t u){ return operator (uint128_t(a), u); }	\
 auto operator (uint64_t a, uint128_t u){ return operator (uint128_t(a), u); }	\
 auto operator (uint128_t u, uint64_t a){ return operator (u, uint128_t(a)); }	\
 auto operator (uint128_t u, uint32_t a){ return operator (u, uint128_t(a)); }	\
 auto operator (uint128_t u, uint16_t a){ return operator (u, uint128_t(a)); }	\
 auto operator (uint128_t u, uint8_t a) { return operator (u, uint128_t(a)); }	\
 // unsigned unsigned 256							\
 auto operator (uint8_t a, uint256_t u) { return operator (uint256_t(a), u); }	\
 auto operator (uint16_t a, uint256_t u){ return operator (uint256_t(a), u); }	\
 auto operator (uint32_t a, uint256_t u){ return operator (uint256_t(a), u); }	\
 auto operator (uint64_t a, uint256_t u){ return operator (uint256_t(a), u); }	\
 auto operator (uint128_t a,uint256_t u){ return operator (uint256_t(a), u); }	\
 auto operator (uint256_t u,uint128_t a){ return operator (u, uint256_t(a)); }	\
 auto operator (uint256_t u, uint64_t a){ return operator (u, uint256_t(a)); }	\
 auto operator (uint256_t u, uint32_t a){ return operator (u, uint256_t(a)); }	\
 auto operator (uint256_t u, uint16_t a){ return operator (u, uint256_t(a)); }	\
 auto operator (uint256_t u, uint8_t a) { return operator (u, uint256_t(a)); }	\
 // signed signed 128								\
 auto operator (int8_t a, int128_t i)   { return operator (int128_t(a), i); }	\
 auto operator (int16_t a, int128_t i)  { return operator (int128_t(a), i); }	\
 auto operator (int32_t a, int128_t i)  { return operator (int128_t(a), i); }	\
 auto operator (int64_t a, int128_t i)  { return operator (int128_t(a), i); }	\
 auto operator (int128_t i, int64_t a)  { return operator (i, int128_t(a)); }	\
 auto operator (int128_t i, int32_t a)  { return operator (i, int128_t(a)); }	\
 auto operator (int128_t i, int16_t a)  { return operator (i, int128_t(a)); }	\
 auto operator (int128_t i, int8_t a)   { return operator (i, int128_t(a)); }	\
 // signed signed 256								\
 auto operator (int8_t a, int256_t i)   { return operator (int256_t(a), i); }	\
 auto operator (int16_t a, int256_t i)  { return operator (int256_t(a), i); }	\
 auto operator (int32_t a, int256_t i)  { return operator (int256_t(a), i); }	\
 auto operator (int64_t a, int256_t i)  { return operator (int256_t(a), i); }	\
 auto operator (int128_t a, int256_t i) { return operator (int256_t(a), i); }	\
 auto operator (int256_t i, int128_t a) { return operator (i, int256_t(a)); }	\
 auto operator (int256_t i, int64_t a)  { return operator (i, int256_t(a)); }	\
 auto operator (int256_t i, int32_t a)  { return operator (i, int256_t(a)); }	\
 auto operator (int256_t i, int16_t a)  { return operator (i, int256_t(a)); }	\
 auto operator (int256_t i, int8_t a)   { return operator (i, int256_t(a)); }	\
 // unsigned signed 128								\
 auto operator (uint8_t a, int128_t i)  { return operator (int128_t(a), i); }	\
 auto operator (uint16_t a, int128_t i) { return operator (int128_t(a), i); }	\
 auto operator (uint32_t a, int128_t i) { return operator (int128_t(a), i); }	\
 auto operator (uint64_t a, int128_t i) { return operator (int128_t(a), i); }	\
 auto operator (uint128_t u, int128_t i){ return operator (u, uint128_t(i)); }	\
 auto operator (uint128_t u, int64_t a) { return operator (u, int128_t(a)); }	\
 auto operator (uint128_t u, int32_t a) { return operator (u, int128_t(a)); }	\
 auto operator (uint128_t u, int16_t a) { return operator (u, int128_t(a)); }	\
 auto operator (uint128_t u, int8_t a)  { return operator (u, int128_t(a)); }	\
 // unsigned signed 256								\
 auto operator (uint8_t a, int256_t i)  { return operator (int256_t(a), i); }	\
 auto operator (uint16_t a, int256_t i) { return operator (int256_t(a), i); }	\
 auto operator (uint32_t a, int256_t i) { return operator (int256_t(a), i); }	\
 auto operator (uint64_t a, int256_t i) { return operator (int256_t(a), i); }	\
 auto operator (uint128_t a, int256_t i){ return operator (int256_t(a), i); }	\
 auto operator (uint256_t u, int256_t i){ return operator (u, uint256_t(i)); }	\
 auto operator (uint256_t u, int128_t a){ return operator (u, int256_t(a)); }	\
 auto operator (uint256_t u, int64_t a) { return operator (u, int256_t(a)); }	\
 auto operator (uint256_t u, int32_t a) { return operator (u, int256_t(a)); }	\
 auto operator (uint256_t u, int16_t a) { return operator (u, int256_t(a)); }	\
 auto operator (uint256_t u, int8_t a)  { return operator (u, int256_t(a)); }	\
 // signed unsigned 128								\
 auto operator (int128_t i, uint8_t a)  { return operator (i, int128_t(a)); }	\
 auto operator (int128_t i, uint16_t a) { return operator (i, int128_t(a)); }	\
 auto operator (int128_t i, uint32_t a) { return operator (i, int128_t(a)); }	\
 auto operator (int128_t i, uint64_t a) { return operator (i, int128_t(a)); }	\
 auto operator (int128_t i, uint128_t u){ return operator (uint128_t(i), u); }	\
 auto operator (int64_t a, uint128_t u) { return operator (int128_t(a), u); }	\
 auto operator (int32_t a, uint128_t u) { return operator (int128_t(a), u); }	\
 auto operator (int16_t a, uint128_t u) { return operator (int128_t(a), u); }	\
 auto operator (int8_t a, uint128_t u)  { return operator (int128_t(a), u); }	\
 // signed unsigned 256								\
 auto operator (int256_t i, uint8_t a)  { return operator (i, int256_t(a)); }	\
 auto operator (int256_t i, uint16_t a) { return operator (i, int256_t(a)); }	\
 auto operator (int256_t i, uint32_t a) { return operator (i, int256_t(a)); }	\
 auto operator (int256_t i, uint64_t a) { return operator (i, int256_t(a)); }	\
 auto operator (int256_t i, uint128_t a){ return operator (i, int256_t(a)); }	\
 auto operator (int256_t i, uint256_t u){ return operator (uint256_t(i), u); }	\
 auto operator (int128_t a, uint256_t u){ return operator (int256_t(a), u); }	\
 auto operator (int64_t a, uint256_t u) { return operator (int256_t(a), u); }	\
 auto operator (int32_t a, uint256_t u) { return operator (int256_t(a), u); }	\
 auto operator (int16_t a, uint256_t u) { return operator (int256_t(a), u); }	\
 auto operator (int8_t a, uint256_t u)  { return operator (int256_t(a), u); }

# define mutable(operator)							\
 inline auto operator##=(uint128_t u, uint128_t a){return u = operator(u, a);}	\
 inline auto operator##=(uint256_t u, uint256_t a){return u = operator(u, a);}	\
 inline auto operator##=(int128_t i, int128_t a)  {return i = operator(i, a);}	\
 inline auto operator##=(int256_t i, int256_t a)  {return i = operator(i, a);}
 // add
 extern uint128_t operator + (uint128_t, uint128_t);
 extern uint256_t operator + (uint256_t, uint256_t);
 extern int128_t operator + (int128_t, int128_t);
 extern int256_t operator + (int256_t, int256_t);
 volatile(operator +) // add
 mutable(operator +)
 // sub
 inline uint128_t operator - (uint128_t u, uint128_t v){ return u + (-v); }
 inline uint256_t operator - (uint256_t u, uint256_t v){ return u + (-v); }
 inline int128_t operator - (int128_t i, int128_t j){ return i + (-j); }
 inline int256_t operator - (int256_t i, int256_t j){ return i + (-j); }
 volatile(operator -) // sub
 mutable(operator -)
 // mul
 extern uint128_t operator * (uint128_t, uint128_t);
 extern uint256_t operator * (uint256_t, uint256_t);
 extern int128_t operator * (int128_t, int128_t);
 extern int256_t operator * (int256_t, int256_t);
 volatile(operator *) // mul
 mutable(operator *)
 // div
 extern uint128_t operator / (uint128_t, uint128_t);
 extern uint256_t operator / (uint256_t, uint256_t);
 extern int128_t operator / (int128_t, int128_t);
 extern int256_t operator / (int256_t, int256_t);
 volatile(operator /) // div
 mutable(operator /)
 // mod
 extern uint128_t operator % (uint128_t, uint128_t);
 extern uint256_t operator % (uint256_t, uint256_t);
 extern int128_t operator % (int128_t, int128_t);
 extern int256_t operator % (int256_t, int256_t);
 volatile(operator %) // mod
 mutable(operator %)
 // cmp
 extern bool operator != (uint128_t, uint128_t);
 extern bool operator != (uint256_t, uint256_t);
 extern bool operator != (int128_t, int128_t);
 extern bool operator != (int256_t, int256_t);
 volatile(operator !=)
 // <=>
 extern bool operator < (uint128_t, uint128_t);
 extern bool operator > (uint128_t, uint128_t);
 extern bool operator < (uint256_t, uint256_t);
 extern bool operator > (uint256_t, uint256_t);
 extern bool operator < (int128_t, int128_t);
 extern bool operator > (int128_t, int128_t);
 extern bool operator < (int256_t, int256_t);
 extern bool operator > (int256_t, int256_t);
 volatile(operator <)
 volatile(operator >)
 inline bool operator == (uint128_t u, uint128_t v){return!(u != v);}
 inline bool operator == (uint256_t u, uint256_t v){return!(u != v);}
 inline bool operator == (int128_t u, int128_t v)  {return!(u != v);}
 inline bool operator == (int256_t u, int256_t v)  {return!(u != v);}
 volatile(operator ==)
 inline bool operator <= (uint128_t u, uint128_t v){return!(u > v);}
 inline bool operator <= (uint256_t u, uint256_t v){return!(u > v);}
 inline bool operator <= (int128_t u, int128_t v)  {return!(u > v);}
 inline bool operator <= (int256_t u, int256_t v)  {return!(u > v);}
 volatile(operator <=)
 inline bool operator >= (uint128_t u, uint128_t v){return!(u < v);}
 inline bool operator >= (uint256_t u, uint256_t v){return!(u < v);}
 inline bool operator >= (int128_t u, int128_t v)  {return!(u < v);}
 inline bool operator >= (int256_t u, int256_t v)  {return!(u < v);}
 volatile(operator >=)
 // shift
 extern uint128_t operator << (uint128_t, uint128_t);
 extern uint128_t operator >> (uint128_t, uint128_t);
 extern uint256_t operator << (uint256_t, uint256_t);
 extern uint256_t operator >> (uint256_t, uint256_t);
 extern int128_t operator << (int128_t, int128_t);
 extern int128_t operator >> (int128_t, int128_t);
 extern int256_t operator << (int256_t, int256_t);
 extern int256_t operator >> (int256_t, int256_t);
 volatile(operator <<)
 volatile(operator >>)
 mutable(operator <<)
 mutable(operator >>)
 // and
 extern uint128_t operator & (uint128_t, uint128_t);
 extern uint256_t operator & (uint256_t, uint256_t);
 extern int128_t operator & (int128_t, int128_t);
 extern int256_t operator & (int256_t, int256_t);
 volatile(operator &) // and
 mutable(operator &)
 // xor
 extern uint128_t operator ^ (uint128_t, uint128_t);
 extern uint256_t operator ^ (uint256_t, uint256_t);
 extern int128_t operator ^ (int128_t, int128_t);
 extern int256_t operator ^ (int256_t, int256_t);
 volatile(operator ^) // xor
 mutable(operator ^)
 // or
 extern uint128_t operator | (uint128_t, uint128_t);
 extern uint256_t operator | (uint256_t, uint256_t);
 extern int128_t operator | (int128_t, int128_t);
 extern int256_t operator | (int256_t, int256_t);
 volatile(operator |) // or
 mutable(operator |)
# undef mutable
# undef volatile
*/
namespace pyro
{
	template<int N, class T = unsigned> struct uvec { T array[N]; };
	template<int N, class T = signed> struct ivec { T array[N]; };
	template<int N, class T = float> struct fvec { T array[N]; };
	template<class T> auto align_u(T &value)
	{
		if constexpr(sizeof(T) == 1)return reinterpret_cast<unsigned char      &>(value);
		if constexpr(sizeof(T) == 2)return reinterpret_cast<unsigned short     &>(value);
		if constexpr(sizeof(T) == 4)return reinterpret_cast<unsigned int       &>(value);
		if constexpr(sizeof(T) == 8)return reinterpret_cast<unsigned long long &>(value);
	}
	template<class T> auto align_uvec(T &value)
	{
		if constexpr(alignof(T) == 1)return reinterpret_cast<uvec<sizeof(T) >> 0, unsigned char>      &>(value);
		if constexpr(alignof(T) == 2)return reinterpret_cast<uvec<sizeof(T) >> 1, unsigned short>     &>(value);
		if constexpr(alignof(T) == 4)return reinterpret_cast<uvec<sizeof(T) >> 2, unsigned int>       &>(value);
		if constexpr(alignof(T) == 8)return reinterpret_cast<uvec<sizeof(T) >> 3, unsigned long long> &>(value);
	}
	template<class T> auto align_i(T &value)
	{
		if constexpr(sizeof(T) == 1)return reinterpret_cast<signed char      &>(value);
		if constexpr(sizeof(T) == 2)return reinterpret_cast<signed short     &>(value);
		if constexpr(sizeof(T) == 4)return reinterpret_cast<signed int       &>(value);
		if constexpr(sizeof(T) == 8)return reinterpret_cast<signed long long &>(value);
	}
	template<class T> auto align_ivec(T &value)
	{
		if constexpr(alignof(T) == 1)return reinterpret_cast<ivec<sizeof(T) >> 0, signed char>      &>(value);
		if constexpr(alignof(T) == 2)return reinterpret_cast<ivec<sizeof(T) >> 1, signed short>     &>(value);
		if constexpr(alignof(T) == 4)return reinterpret_cast<ivec<sizeof(T) >> 2, signed int>       &>(value);
		if constexpr(alignof(T) == 8)return reinterpret_cast<ivec<sizeof(T) >> 3, signed long long> &>(value);
	}
	template<class T> auto align_f(T &value)
	{
		if constexpr(sizeof(T) == 4)return reinterpret_cast<float  &>(value);
		if constexpr(sizeof(T) == 8)return reinterpret_cast<double &>(value);
	}
	template<class T> auto align_fvec(T &value)
	{
		if constexpr(alignof(T) == 4)return reinterpret_cast<fvec<sizeof(T) >> 2, float>  &>(value);
		if constexpr(alignof(T) == 8)return reinterpret_cast<fvec<sizeof(T) >> 3, double> &>(value);
	}
}
/*# pragma once
# include <type_traits>
/////////////////////////////////////////////////////////////////////
struct alignas(16) int128_t
{
	template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
	operator T(void){ return*reinterpret_cast<T*>(this); }
	template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
	int128_t(T a){ }
	int128_t operator << (unsigned);
	int128_t operator >> (unsigned);
	bool     operator ! (void);
	int128_t operator ~ (void);
	int128_t operator + (void);
	int128_t operator - (void);
};
// add
extern int128_t operator + (int128_t, int128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator + (int128_t u, T a){ return u + int128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator + (T a, int128_t u){ return int128_t(a) + u; }
// sub
extern int128_t operator - (int128_t, int128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator - (int128_t u, T a){ return u - int128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator - (T a, int128_t u){ return int128_t(a) - u; }
// imul
extern int128_t operator * (int128_t, int128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator * (int128_t u, T a){ return u * int128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator * (T a, int128_t u){ return int128_t(a) * u; }
// idiv
extern int128_t operator / (int128_t, int128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator / (int128_t u, T a){ return u / int128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator / (T a, int128_t u){ return int128_t(a) / u; }
// imod
extern int128_t operator % (int128_t, int128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator % (int128_t u, T a){ return u % int128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator % (T a, int128_t u){ return int128_t(a) % u; }
// and
extern int128_t operator & (int128_t, int128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator & (int128_t u, T a){ return u & int128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator & (T a, int128_t u){ return int128_t(a) & u; }
// xor
extern int128_t operator ^ (int128_t, int128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator ^ (int128_t u, T a){ return u ^ int128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator ^ (T a, int128_t u){ return int128_t(a) ^ u; }
// or
extern int128_t operator | (int128_t, int128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator | (int128_t u, T a){ return u | int128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator | (T a, int128_t u){ return int128_t(a) | u; }
/////////////////////////////////////////////////////////////////////
struct alignas(16) uint128_t
{
	template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
	uint128_t(T a){ }
	uint128_t operator << (unsigned);
	uint128_t operator >> (unsigned);
	bool      operator ! (void);
	uint128_t operator ~ (void);
	uint128_t operator + (void);
	uint128_t operator - (void);
};
// add
extern uint128_t operator + (uint128_t, uint128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator + (uint128_t u, T a){ return u + uint128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator + (T a, uint128_t u){ return uint128_t(a) + u; }
// sub
extern uint128_t operator - (uint128_t, uint128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator - (uint128_t u, T a){ return u - uint128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator - (T a, uint128_t u){ return uint128_t(a) - u; }
// mul
extern uint128_t operator * (uint128_t, uint128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator * (uint128_t u, T a){ return u * uint128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator * (T a, uint128_t u){ return uint128_t(a) * u; }
// div
extern uint128_t operator / (uint128_t, uint128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator / (uint128_t u, T a){ return u / uint128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator / (T a, uint128_t u){ return uint128_t(a) / u; }
// mod
extern uint128_t operator % (uint128_t, uint128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator % (uint128_t u, T a){ return u % uint128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator % (T a, uint128_t u){ return uint128_t(a) % u; }
// and
extern uint128_t operator & (uint128_t, uint128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator & (uint128_t u, T a){ return u & uint128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator & (T a, uint128_t u){ return uint128_t(a) & u; }
// xor
extern uint128_t operator ^ (uint128_t, uint128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator ^ (uint128_t u, T a){ return u ^ uint128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator ^ (T a, uint128_t u){ return uint128_t(a) ^ u; }
// or
extern uint128_t operator | (uint128_t, uint128_t); // align.cpp
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator | (uint128_t u, T a){ return u | uint128_t(a); }
template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline auto operator | (T a, uint128_t u){ return uint128_t(a) | u; }
/////////////////////////////////////////////////////////////////////
# include <cstdint>
namespace pyro
{
	template<class T> struct align
	{
		typedef
		std::conditional_t<alignof(T)==0x01, int8_t,
		std::conditional_t<alignof(T)==0x02, int16_t,
		std::conditional_t<alignof(T)==0x04, int32_t,
		std::conditional_t<alignof(T)==0x08, int64_t,
		std::conditional_t<alignof(T)==0x10, int128_t, void>>>>> i;
		typedef
		std::conditional_t<alignof(T)==0x01, uint8_t,
		std::conditional_t<alignof(T)==0x02, uint16_t,
		std::conditional_t<alignof(T)==0x04, uint32_t,
		std::conditional_t<alignof(T)==0x08, uint64_t,
		std::conditional_t<alignof(T)==0x10, uint128_t, void>>>>> u;
		typedef
		std::conditional_t<alignof(T)==0x04, float,
		std::conditional_t<alignof(T)==0x08, double, void>> f;
	};
	template<class T> auto align_i(T *ptr)
	{
		return reinterpret_cast<typename align<T>::i*>(ptr);
	}
	template<class T> auto align_i(T& ref)
	{
		return reinterpret_cast<typename align<T>::i&>(ref);
	}
	template<class T> auto align_u(T *ptr)
	{
		return reinterpret_cast<typename align<T>::u*>(ptr);
	}
	template<class T> auto align_u(T& ref)
	{
		return reinterpret_cast<typename align<T>::u&>(ref);
	}
	template<class T> auto align_f(T *ptr)
	{
		return reinterpret_cast<typename align<T>::f*>(ptr);
	}
	template<class T> auto align_f(T& ref)
	{
		return reinterpret_cast<typename align<T>::f&>(ref);
	}
}
*/
/*template<size_t> struct m64;
template<> struct m64<0>
{
	const __m64 mm;
	operator __m64(void){ return mm; }
	m64(__m64 a): mm(a){ }
	m64<0> operator &(m64<0> a){ return _mm_and_si64(mm, a); }
	m64<0> operator ^(m64<0> a){ return _mm_xor_si64(mm, a); }
	m64<0> operator |(m64<0> a){ return _mm_or_si64(mm, a); }
};
template<> struct m64<1> : public m64<0>
{
	m64(__m64 a): m64<0>(a){ }
public:
	m64(char a): m64(_mm_set1_pi8(a)) { }
	m64(char a, char b, char c, char d, char e, char f, char g, char h): m64(_mm_set_pi8(a, b, c, d, e, f, g, h)) { }
	m64<1> operator +(m64<1> a){ return _mm_add_pi8(mm, a); }
	m64<1> operator -(m64<1> a){ return _mm_sub_pi8(mm, a); }
	m64<1> operator *(m64<1> a)
	{
		return m64<1> (	operator[ ](0) * a[0],
				operator[ ](1) * a[1],
				operator[ ](2) * a[2],
				operator[ ](3) * a[3],
				operator[ ](4) * a[4],
				operator[ ](5) * a[5],
				operator[ ](6) * a[6],
				operator[ ](7) * a[7] );
	}
	m64<1> operator /(m64<1> a)
	{
		return m64<1> (	operator[ ](0) / a[0],
				operator[ ](1) / a[1],
				operator[ ](2) / a[2],
				operator[ ](3) / a[3],
				operator[ ](4) / a[4],
				operator[ ](5) / a[5],
				operator[ ](6) / a[6],
				operator[ ](7) / a[7] );
	}
	char operator[ ](size_t i){ return reinterpret_cast<const char *>(& mm)[i]; }
};
template<> struct m64<2> : public m64<0>
{
	m64(__m64 a): m64<0>(a){ }
public:
	m64(short a, short b, short c, short d): m64(_mm_set_pi16(a, b, c, d)) { }
	m64<2> operator +(m64<2> a){ return _mm_add_pi16(mm, a); }
	m64<2> operator -(m64<2> a){ return _mm_sub_pi16(mm, a); }
	m64<2> operator *(m64<2> a)
	{
		return m64<2>(	operator[ ](0) * a[0],
				operator[ ](1) * a[1],
				operator[ ](2) * a[2],
				operator[ ](3) * a[3] );
	}
	m64<2> operator /(m64<2> a)
	{
		return m64<2>(	operator[ ](0) / a[0],
				operator[ ](1) / a[1],
				operator[ ](2) / a[2],
				operator[ ](3) / a[3] );
	}
	short operator[ ](size_t i){ return reinterpret_cast<const short *>(& mm)[i]; }
};
template<> struct m64<4> : public m64<0>
{
	m64(__m64 a): m64<0>(a){ }
public:
	m64(int a, int b): m64<0>(_mm_set_pi32(a, b)) { }
	m64<4> operator +(m64<4> a){ return _mm_add_pi32(mm, a); }
	m64<4> operator +(m64<4> a){ return _mm_sub_pi32(mm, a); }
	m64<4> operator *(m64<4> a){ return _mm_mul_su32(mm, a); }
	m64<4> operator /(m64<4> a)
	{
		return m64<4>(	operator[ ](0) / a[0],
				operator[ ](1) / a[1]	
		);
	}
	int operator[ ](size_t i){ return reinterpret_cast<const int *>(& mm)[i]; }
};*/
/////////////////////////////////////////////////////////////////////
/*typedef __m128i m128i8;
typedef __m128i m128i16;
typedef __m128i m128i32;
typedef __m128i m128i64;
m128i8 m128(char a, char b, char c, char d, char e, char f, char g, char h, char i, char j, char k, char l, char m, char n, char o, char p)
{
	return _mm_set_epi8(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);
}
m128i16 m128(short a, short b, short c, short d, short e, short f, short g, short h)
{
	return _mm_set_epi16(a, b, c, d, e, f, g, h);
}
m128i32 m128(int a, int b, int c, int d)
{
	return _mm_set_epi32(a, b, c, d);
}
m128i64 m128(__m64 a, __m64 b)
{
	return _mm_set_epi64(a, b);
}
m128i8  operator +(m128i8  A, m128i8  B){ return _mm_add_epi8 (A, B); }
m128i16 operator +(m128i16 A, m128i16 B){ return _mm_add_epi16(A, B); }
m128i32 operator +(m128i32 A, m128i32 B){ return _mm_add_epi32(A, B); }
m128i64 operator +(m128i64 A, m128i64 B){ return _mm_add_epi64(A, B); }
typedef __m64 m64i8;
typedef __m64 m64i16;
typedef __m64 m64i32;
m64i8 m64(char a, char b, char c, char d, char e, char f, char g, char h)
{
	return _mm_set_pi8(a, b, c, d, e, f, g, h);
}
m64i16 m64(short a, short b, short c, short d)
{
	return _mm_set_pi16(a, b, c, d);
}
m64i32 m64(int a, int b)
{
	return _mm_set_pi32(a, b);
}
__m128 m128(void){ return _mm_setzero_ps( ); } // _mm_undefined_ps
__m128 m128(const float *A){ return _mm_loadu_ps(A); } // _mm_loadr_ps, _mm_load1_ps, _mm_load_ps1
__m128 m128(float A){ return _mm_set_ps1(A); }
__m128 m128(float A, float B, float C, float D){ return _mm_set_ps(A, B, C, D); }
__m128 m128(__m128i A){ return _mm_cvtepi32_ps(A); }
__m128 m128(__m128d A){ return _mm_cvtpd_ps(A); }
__m128 m128(__m64 A){ return _mm_cvtpi8_ps(A), _mm_cvtpi16_ps(A), _mm_cvtpu8_ps(A), _mm_cvtpu16_ps(A); }
__m128 m128(__m128 A, __m64 B){ return _mm_cvt_pi2ps(A, B); }
//__m128 m128(__m64 A, __m64 B){ return _mm_cvtpi32x2_ps(A, B); }
__m64 m64(__m128 A){ return _mm_cvtt_ps2pi(A); }
# include <immintrin.h>
__m128 m128(__m128i A){ return _mm_cvtph_ps(A); }
__m128 operator +(__m128 A, __m128 B){ return _mm_add_ps(A, B), _mm_hadd_ps(A, B); }
__m128 operator -(__m128 A, __m128 B){ return _mm_sub_ps(A, B), _mm_hsub_ps(A, B); }
__m128 operator *(__m128 A, __m128 B){ return _mm_mul_ps(A, B); }
__m128 operator /(__m128 A, __m128 B){ return _mm_div_ps(A, B); }
__m128 operator &(__m128 A, __m128 B){ return _mm_and_ps(A, B); }
__m128 operator |(__m128 A, __m128 B){ return _mm_or_ps(A, B); }
__m128 operator ^(__m128 A, __m128 B){ return _mm_xor_ps(A, B); }
__m128 operator ==(__m128 A, __m128 B){ return _mm_cmpeq_ps(A, B); }
__m128 operator >=(__m128 A, __m128 B){ return _mm_cmpge_ps(A, B); }
__m128 operator >(__m128 A, __m128 B){ return _mm_cmpgt_ps(A, B); }
__m128 operator <=(__m128 A, __m128 B){ return _mm_cmple_ps(A, B); }
__m128 operator <(__m128 A, __m128 B){ return _mm_cmplt_ps(A, B); }
__m128 operator !=(__m128 A, __m128 B){ return _mm_cmpneq_ps(A, B); }
__m128 __max__(__m128 A, __m128 B){ return _mm_max_ps(A, B); }
__m128 __min__(__m128 A, __m128 B){ return _mm_min_ps(A, B); }
__m128 __inv__(__m128 A){ return _mm_rcp_ps(A); }
__m128 __sqrt__(__m128 A){ return _mm_sqrt_ps(A); }
// _mm_store_ps
// _MM_TRANSPOSE4_PS 
void transpose(__m128& row0, __m128& row1, __m128& row2, __m128& row3)
{
        __m128 _Tmp3, _Tmp2, _Tmp1, _Tmp0;
        _Tmp0   = _mm_shuffle_ps((row0), (row1), 0x44);
        _Tmp2   = _mm_shuffle_ps((row0), (row1), 0xEE);
        _Tmp1   = _mm_shuffle_ps((row2), (row3), 0x44);
        _Tmp3   = _mm_shuffle_ps((row2), (row3), 0xEE);
        (row0) = _mm_shuffle_ps(_Tmp0, _Tmp1, 0x88);
        (row1) = _mm_shuffle_ps(_Tmp0, _Tmp1, 0xDD);
        (row2) = _mm_shuffle_ps(_Tmp2, _Tmp3, 0x88);
        (row3) = _mm_shuffle_ps(_Tmp2, _Tmp3, 0xDD);
}*/
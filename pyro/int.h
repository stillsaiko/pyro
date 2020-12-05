# pragma once
# include <cstdint>
namespace pyro
{
	// unsigned
	typedef uint8_t  uint8;
	typedef uint16_t uint16;
	typedef uint32_t uint32;
	typedef uint64_t uint64;
	typedef struct   uint128
	{
		uint128(void);
		uint128(uint64 lo, uint64 hi = 0);
		// ...
		operator uint64(void);
		// private
		uint64 const lo;
		uint64 const hi;
	};
	# define inline(operator, T)\
	inline T operator (T a, uint8  u){ return operator (a, static_cast<T>(u)); }\
	inline T operator (T a, uint16 u){ return operator (a, static_cast<T>(u)); }\
	inline T operator (T a, uint32 u){ return operator (a, static_cast<T>(u)); }\
	inline T operator (T a, uint64 u){ return operator (a, static_cast<T>(u)); }\
	inline T operator (uint8  u, T a){ return operator (static_cast<T>(u), a); }\
	inline T operator (uint16 u, T a){ return operator (static_cast<T>(u), a); }\
	inline T operator (uint32 u, T a){ return operator (static_cast<T>(u), a); }\
	inline T operator (uint64 u, T a){ return operator (static_cast<T>(u), a); }
	extern uint128 operator &(uint128, uint128); inline(operator &, uint128)
	extern uint128 operator ^(uint128, uint128); inline(operator ^, uint128)
	extern uint128 operator |(uint128, uint128); inline(operator |, uint128)
	extern uint128 operator +(uint128, uint128); inline(operator +, uint128)
	extern uint128 operator -(uint128, uint128); inline(operator -, uint128)
	extern uint128 operator *(uint128, uint128); inline(operator *, uint128)
	extern uint128 operator /(uint128, uint128); inline(operator /, uint128)
	extern uint128 operator %(uint128, uint128); inline(operator %, uint128)
	# undef inline
	// signed
	typedef int8_t  int8;
	typedef int16_t int16;
	typedef int32_t int32;
	typedef int64_t int64;
	typedef struct  int128
	{
		int128(void);
		int128(int64 lo, int64 hi = 0);
		// ...
		operator int64(void);
		// private
		int64 const lo;
		int64 const hi;
	};
	# define inline(operator, T)\
	inline T operator (T a, int8  i){ return operator (a, static_cast<T>(i)); }\
	inline T operator (T a, int16 i){ return operator (a, static_cast<T>(i)); }\
	inline T operator (T a, int32 i){ return operator (a, static_cast<T>(i)); }\
	inline T operator (T a, int64 i){ return operator (a, static_cast<T>(i)); }\
	inline T operator (int8  i, T a){ return operator (static_cast<T>(i), a); }\
	inline T operator (int16 i, T a){ return operator (static_cast<T>(i), a); }\
	inline T operator (int32 i, T a){ return operator (static_cast<T>(i), a); }\
	inline T operator (int64 i, T a){ return operator (static_cast<T>(i), a); }
	extern int128 operator &(int128, int128); inline(operator &, int128)
	extern int128 operator ^(int128, int128); inline(operator ^, int128)
	extern int128 operator |(int128, int128); inline(operator |, int128)
	extern int128 operator +(int128, int128); inline(operator +, int128)
	extern int128 operator -(int128, int128); inline(operator -, int128)
	extern int128 operator *(int128, int128); inline(operator *, int128)
	extern int128 operator /(int128, int128); inline(operator /, int128)
	extern int128 operator %(int128, int128); inline(operator %, int128)
	# undef inline
	template<class T>
	struct uvec :
	public T
	{
		uvec(void): T( ) { }
		uvec(T  a): T(a) { }
		operator auto(void) { return align_u(static_cast<T *>(this)); }
		auto operator[ ](size_t i) { return operator typename align<T>::u( )[i]; }
	};
	template<class T> uvec<T> operator *(uvec<T> A, uvec<T> B)
	{
		if constexpr( sizeof(T) / alignof(T) == 4 && alignof(T) == 4 )
		{
			SSE<unsigned>(A[0], A[1], A[2], A[3]) *
			SSE<unsigned>(B[0], B[1], B[2], B[3]);
		}
		uvec<T> C;
		for(size_t i = 0; i < sizeof(T) / alignof(T); ++ i)
			C[i] = A[i] * B[i];
		return C;
	}
}
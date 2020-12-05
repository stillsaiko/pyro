# pragma once
// Z : ⧖ sawtooth
// S : 8 sinus
// L : H square
// C : O abs(sin)
// < : X triangle
namespace pyro
{
	typedef signed char		int8;
	typedef signed short		int16;
	typedef signed int		int32;
	typedef signed long long	int64;
	struct				int128 { };
	struct				int256 { };

	template<class T> constexpr auto int_align(T *ptr)
	{
		if constexpr(alignof(T) ==  1) return reinterpret_cast<int8   *>(ptr);
		if constexpr(alignof(T) ==  2) return reinterpret_cast<int16  *>(ptr);
		if constexpr(alignof(T) ==  4) return reinterpret_cast<int32  *>(ptr);
		if constexpr(alignof(T) ==  8) return reinterpret_cast<int64  *>(ptr);
		if constexpr(alignof(T) == 16) return reinterpret_cast<int128 *>(ptr);
		if constexpr(alignof(T) == 32) return reinterpret_cast<int256 *>(ptr);
	}

	typedef unsigned char		uint8;
	typedef unsigned short		uint16;
	typedef unsigned int		uint32;
	typedef unsigned long long	uint64;
	struct				uint128 { };
	struct				uint256 { };

	template<class T> constexpr auto uint_align(T *ptr)
	{
		if constexpr(alignof(T) ==  1) return reinterpret_cast<uint8   *>(ptr);
		if constexpr(alignof(T) ==  2) return reinterpret_cast<uint16  *>(ptr);
		if constexpr(alignof(T) ==  4) return reinterpret_cast<uint32  *>(ptr);
		if constexpr(alignof(T) ==  8) return reinterpret_cast<uint64  *>(ptr);
		if constexpr(alignof(T) == 16) return reinterpret_cast<uint128 *>(ptr);
		if constexpr(alignof(T) == 32) return reinterpret_cast<uint256 *>(ptr);
	}

	struct				float16 { };
	typedef float			float32;
	typedef double			float64;

	template<class T> constexpr auto float_align(T *ptr)
	{
		if constexpr(alignof(T) == 2) return reinterpret_cast<float16 *>(ptr);
		if constexpr(alignof(T) == 4) return reinterpret_cast<float32 *>(ptr);
		if constexpr(alignof(T) == 8) return reinterpret_cast<float64 *>(ptr);
	}
}
// vector.h
namespace pyro
{
	template<unsigned> struct ivec
	{
		template<class T> ivec(T a)
		{
			int_align(a);
		}
	};
}
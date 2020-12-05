# pragma once
// include "rc.h"
# include <cstdio> // fopen
# include <cstdlib> // malloc
// include <cassert> // assert
# include <cstdint> // uint8_t
// image/jpeg
template<class> struct JPEG;
struct YCbCr
{
	int16_t Y, Cb, Cr;
};
# include "rc.h"
template<> struct JPEG<YCbCr>
{
	const uint16_t X;
	const uint16_t Y;
	~
	JPEG(void);
	JPEG(void);
	JPEG(RC &&);
	JPEG(JPEG<YCbCr> &&) noexcept;
	void operator = (JPEG<YCbCr> &&)noexcept;
	const YCbCr *operator *(void) const;
	const YCbCr *operator[ ](size_t) const;
protected:
	RC rsrc;
/*	struct C
	{
		enum { Y = 1, Cb = 2, Cr = 3, I = 4, Q = 5 } comp;
		const uint8_t *QT = nullptr;
		const uint8_t
	};*/
};
// include <cstdint>
template<class T> struct JPEG final : JPEG<YCbCr>
{
	JPEG(void) = default;
	static_assert(alignof(T) <= 2, "max 16-bit");
	static_assert(sizeof(T) <= alignof(T) << 2, "max RGBA");
	JPEG(JPEG<T> &&JPEG) noexcept
	// : JPEG<YCbCr>(static_cast<JPEG<YCbCr>&&>(JPEG))
	{
		memcpy(this, &JPEG, sizeof JPEG);
		memset(&JPEG, sizeof JPEG);
	}
	void operator = (JPEG<T> &&JPEG) noexcept
	{
	//	JPEG<YCbCr>::operator = (static_cast<JPEG<YCbCr>&&>(JPEG));
		JPEG<T>::~JPEG( );
		memcpy(this, &JPEG, sizeof JPEG);
		memset(&JPEG, sizeof JPEG);
	}
	JPEG(RC &&resource):
	JPEG<YCbCr>(static_cast<RC &&>(resource))
	{
		// YCbCr -> RGB
		if(ASSERT(X * Y) && ASSERT(rsrc.size == 3*X*Y))
		{
			if constexpr(sizeof(T) == alignof(T) << 2)
			WARNING("convert YCbCr to RGBA%zu", alignof(T) << 3);
			T *pixels = static_cast<T *>(malloc(sizeof(T)*X*Y));
			// fragments
			for(uint16_t i=0; i<Y; ++i)
			for(uint16_t j=0; j<X; ++j)
			{
				YCbCr YCbCr = JPEG<::YCbCr>::operator[ ](i)[j];
				
				constexpr float Kb = 0.114;
				constexpr float Kr = 0.299;
				constexpr float Kg = 1.000 - Kb - Kr;
				
				constexpr int16_t (*RGB[3])(YCbCr)
				{
					[ ](YCbCr YCbCr) -> int16_t { return YCbCr.Y + 1.402 * (YCbCr.Cr - 32768); },
					[ ](YCbCr YCbCr) -> int16_t { return YCbCr.Y - 0.344136 * (YCbCr.Cb - 32768)
					                                            - 0.714136 * (YCbCr.Cr - 32768); },
					[ ](YCbCr YCbCr) -> int16_t { return YCbCr.Y + 1.772 * (YCbCr.Cb - 32768); }
				};
				// components
				for(unsigned n(0u); n<sizeof(T)/alignof(T); ++n)
				{
					if constexpr(alignof(T) == sizeof(char))
						reinterpret_cast<char *&>(pixels[X*i+j]) = RGB[n](YCbCr) >> 8;
					else	reinterpret_cast<short *&>(pixels[X*i+j]) = RGB[n](YCbCr);

					uint16_t Q = n * alignof(YCbCr) < sizeof(YCbCr)
							? RGB[n](YCbCr) >> 16-8*alignof(T) : 65535;
					// bytes
					for(unsigned k(0u); k<alignof(T); ++k) mem[L+n*alignof(T)+k] = Q >> 8*k;
				}
			/*	{
					float R = Cr * (2 - 2*Kr) + Y;
					float B = Cb * (2 - 2*Kb) + Y;
					float G = (Y - Kb * B - Kr * R) / Kg;
				}

				pixels[X*i+j] = T {
					RGB[0](YCbCr) >> 16-8*alignof(T),
					RGB[1](YCbCr) >> 16-8*alignof(T),
					RGB[2](YCbCr) >> 16-8*alignof(T) };*/
			}
			rsrc = RC(free, mem, sizeof(T)*X*Y);
		}
	}
	const T *operator *(void) const
	{
		return &reinterpret_cast<const T *>(&rsrc[0])[0];
	}
	const T *operator[ ](size_t n) const
	{
		return &reinterpret_cast<const T *>(&rsrc[0])[X * n];
	}
};
/*template<class T> struct JPEG : public JPEG<void>
{
	~
	JPEG(void);
	JPEG(void) = default;
	JPEG(RC &&file):
	JPEG<void>(static_cast<RC &&>(file), sizeof(T) / alignof(T))
	{ }
};*/
# pragma once
// struct RGBA { unsigned char R, G, B, A }
template<class> struct PNG;
# include <rc.h>
template<> struct PNG<void>
{
	const unsigned X; // width
	const unsigned Y; // height
	const unsigned Z; // bit depth
	const unsigned N; // color type
	~
	PNG(void)noexcept ;
	PNG(void);
	PNG(RC&&);
	void operator = (PNG<void>&&)noexcept; // move
	const void * operator * (void);
protected:
	RC rsrc;
};
// include <cstdio>
// include <typeinfo>
# include <error.h>
// struct RGB { uint8_t R, G, B }
// PNG<RGB> image = PNG<RGB>(RC(".png"))
// for(size_t Y=0UL; Y < image.Y; ++Y)
// for(size_t X=0UL; X < image.X; ++X)
//	image[Y][X].R = ...
//	image[Y][X].G = ...
//	image[Y][X].B = ...
template<class T> struct PNG : public PNG<void>
{
	PNG(void) = default;
	static_assert(alignof(T) <= 2, "max 16-bit");
	static_assert(sizeof(T) <= alignof(T) << 2, "max RGBA");
	PNG(RC &&resource):
	PNG<void>(static_cast<RC&&>(resource))
	{
		if(rsrc && X*Y && Z*N)
		if(sizeof(T) != alignof(T)*N || alignof(T) != Z)
		{
			WARNING("convert %.*s%zu to %.*s%zu", N, "RGBA", Z << 3,
				sizeof(T) / alignof(T), "RGBA", alignof(T) << 3);
		//	printf("warning: convert %ubit to %ubit %s\n", 8*N*Z, 8*sizeof(T), typeid(T).name( ));
			char * mem = (char*)malloc(sizeof(T)*X*Y);
			unsigned L(0u);
			unsigned R(0u);
			for(unsigned i(0u); i<Y; ++i)
			for(unsigned j(0u); j<X; ++j)
			{
				for(unsigned n(0u); n<sizeof(T)/alignof(T); ++n)
				for(unsigned k(0u); k<alignof(T); ++k)
				{
			//	mem[sizeof(T)*(X*i+j)+n*alignof(T)+k] = n<N?memory[Z*N*(X*i+j)+n*Z+k%Z+Z/alignof(T)/2]:255;
					# pragma warning (suppress: 6011)
					# pragma warning (suppress: 6386)
					mem[L+n*alignof(T)+k] = n<N?rsrc[R+n*Z+k%Z+Z/alignof(T)/2]:255;
				}
				L += sizeof(T);
				R += N*Z ;
			}
			rsrc = RC(free, mem, sizeof(T)*X*Y);
		}
	}
	const T * operator * (void)const
	{
		return &reinterpret_cast<const T *>(&rsrc[0])[0];
	}
	const T * operator[ ](size_t n)const
	{
		return &reinterpret_cast<const T *>(&rsrc[0])[X * n];
	}
};

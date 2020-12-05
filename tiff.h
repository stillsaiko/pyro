# pragma once
# include <cstdlib> // malloc
# include <cstdint> // uint8_t
# include "rc.h"
template<class T> struct TIFF;
template<> struct TIFF<void>
{	
	~
	TIFF(void);
	TIFF(void);
	TIFF(RC&&);
	void operator = (TIFF<void> &&T)noexcept
	{
		const_cast<uint32_t &>(X) = T.X;
		const_cast<uint32_t &>(Y) = T.Y;
		const_cast<uint16_t &>(Z) = T.Z;
		const_cast<uint16_t &>(N) = T.N;
		const_cast<uint32_t &>(T.X) = 0;
		const_cast<uint32_t &>(T.Y) = 0;
		const_cast<uint16_t &>(T.Z) = 0;
		const_cast<uint16_t &>(T.N) = 0;
		rsrc = static_cast<RC &&>(T.rsrc);
	}
// attrib
	const uint32_t X; // width
	const uint32_t Y; // height
	const uint16_t Z; // bit depth
	const uint16_t N; // color type
private:
//	const uint8_t *p;
	RC rsrc;
	size_t offs = 0;
};
# include <typeinfo>
# include <cstdio>
template<class T> struct TIFF : public TIFF<void>
{
	TIFF(void) = default;
static_assert(alignof(T)<3, "max depth of 16 bit (either 1 or 2)");
	TIFF(RC &&rsrc):
	TIFF<void>(static_cast<RC &&>(rsrc))
	{
		if(rsrc && X*Y && Z*N)
		if(sizeof(T) != alignof(T)*N || alignof(T) != Z){
			printf("warning: convert %ubit to %ubit %s\n", 8*N*Z, 8*sizeof(T), typeid(T).name( ));
			
			unsigned char *mem = static_cast<unsigned char *>(malloc(sizeof(T)*X*Y));
			unsigned L(0u);
			unsigned R(0u);
			for(unsigned i(0u); i<Y; ++i)
			for(unsigned j(0u); j<X; ++j){
				for(unsigned n(0u); n<sizeof(T)/alignof(T); ++n)
				for(unsigned k(0u); k<alignof(T); ++k){
			//	mem[sizeof(T)*(X*i+j)+n*alignof(T)+k] = n<N?memory[Z*N*(X*i+j)+n*Z+k%Z+Z/alignof(T)/2]:255;
					mem[L+n*alignof(T)+k] = n<N?rsrc[R+n*Z+k%Z+Z/alignof(T)/2]:255;
				}
				L += sizeof(T);
				R += N*Z;
			}
			rsrc = RC(free, mem, sizeof(T)*X*Y);
		}
	}
//	T *operator
};
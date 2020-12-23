# pragma once
// image/jpeg
template<class> struct JPEG;
// struct RGB { char R, G, B }
// JPEG<RGB> image = JPEG<RGB>("#@?!.jpeg")
// for i=0 i<image.Y ++i
// for j=0 j<image.X ++j
//	image[i][j].R
//	image[i][j].G
//	image[i][j].B
# include <rc.h>
template<> struct JPEG<void>
{
	const uint16_t X;
	const uint16_t Y;
protected:
	RC rsrc;
	// protected
	JPEG(void);
	JPEG(RC &&, size_t, size_t);
	~
	JPEG(void)			noexcept;
	JPEG(JPEG<void> &&)		noexcept;
	void operator =(JPEG<void> &&)	noexcept;
	const void *operator *(void)	const;
};
template<class T> struct JPEG : public JPEG<void>
{
	JPEG(void) = default;
	JPEG(RC &&resource);

	const T *operator *(void)	const;
	const T *operator[ ](size_t n)	const
	{
		return operator *( ) + X * n;
	}
	static_assert(alignof(T) <= 2, "max 16-bit");
	static_assert(sizeof(T) <= alignof(T) << 2, "max RGBA");
};
template<class T> JPEG<T>::JPEG(RC &&rsrc):
JPEG<void>(static_cast<RC &&>(rsrc), alignof(T), sizeof(T)) { }
template<class T> const T *JPEG<T>::operator *(void) const
{
	return static_cast<const T *>(JPEG<void>::operator *( ));
}
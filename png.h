# pragma once
// image/png
template<class> struct PNG;
// struct RGB { char R, G, B }
// PNG<RGB> image = PNG<RGB>("#@?!.png")
// for i=0 i<image.Y ++i
// for j=0 j<image.X ++j
//	image[i][j].R
//	image[i][j].G
//	image[i][j].B
# include <rc.h>
template<> struct PNG<void>
{
	const uint32_t X; // width
	const uint32_t Y; // height
	const uint16_t Z; // bit depth
	const uint16_t N; // color type
protected:
	RC rsrc;
	// protected
	PNG(void);
	PNG(RC &&);
	PNG(RC &&, size_t, size_t);
	~
	PNG(void)			noexcept;
	PNG(PNG<void> &&)		noexcept;
	void operator =(PNG<void> &&)	noexcept;
	const void *operator *(void)	const;
};
template<class T> struct PNG : public PNG<void>
{
	PNG(void) = default;
	PNG(RC &&resource);
	~
	PNG(void)			noexcept = default;
	PNG(PNG<T> &&)			noexcept = default;
	PNG<T>  &operator =(PNG<T> &&)	noexcept = default;
	const T *operator *(void)	const;
	const T *operator[](size_t n)	const
	{
		return operator *( ) + X * n;
	}
	static_assert(alignof(T) <= 2, "max 16-bit");
	static_assert(sizeof(T) <= alignof(T) << 2, "max RGBA");
};
template<class T> PNG<T>::PNG(RC &&rsrc):
PNG<void>(static_cast<RC &&>(rsrc), alignof(T), sizeof(T)) { }
template<class T> const T *PNG<T>::operator *(void) const
{
	return static_cast<const T *>(PNG<void>::operator *( ));
}

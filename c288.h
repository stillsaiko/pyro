# pragma once
# include "rc.h"
template<class T> class C288
{
	static_assert(sizeof(T) % 3 == 0, "#@?!");
	RC data; // *.c288
public:
	C288(void) = default;
	C288(RC &&resource): data(reinterpret_cast<RC &&>(resource))
	{ }
/*	C288(T height_vertices[288/sizeof(T)*48], bool even_odd[288]): data(
	{
		
	}*/
	bool bit(unsigned short index)const
	{
		return 1<<(index & 7) & data[index/8];
	}
	const T *operator[ ](unsigned char)const
	{
		return reinterpret_cast<const T *>(& data[0] + 288);
	}
private:
};
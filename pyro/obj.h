# pragma once
# include <cstdint> // size_t
namespace pyro
{
	template<class T> struct obj
	{
		virtual size_t flush(size_t n, T *p) = 0;
		virtual size_t ahead(size_t n = 0)const;
	};
	template<class T>
	size_t obj<T>::ahead(size_t)const
	{
		return 0;
	}
}
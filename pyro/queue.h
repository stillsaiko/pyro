# pragma once
namespace pyro
{
	template<class T> struct queue
	{
		const size_t size = 0;
	private:
		T * data = nullptr;
	public:
		T * push(size_t); // <<
		T * pop(size_t); // >>
		T & operator[ ](size_t);
		T * begin(void); // &[0]
		T * end(void); // &[size]
	};
	// push
	template<class T> T * queue<T>::push(size_t n)
	{
		const_cast<size_t &>(size) = size + n;
		data = (T *)realloc(data, sizeof(T)*size);
		return data + size - n;
	}
	// pop
	template<class T> T * queue<T>::pop(size_t n)
	{
		n = min(n, size);
		const_cast<size_t &>(size) = size - n;
		memmove(data, data+n, sizeof(T)*size);
		return data = (T *)realloc(sizeof(T)*size);
	}
	// ...
	template<class T> T & queue<T>::operator[ ](size_t i)
	{
		return pop(0)[i];
	}
	template<class T> T * queue<T>::begin(void)
	{
		return pop(0);
	}
	template<class T> T * queue<T>::end(void)
	{
		return pop(0) + size;
	}
}
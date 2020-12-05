# pragma once
# include <cstdlib> // realloc, free
# include <cstdint> // size_t
namespace pyro
{
	template<class T> class stack
	{
		T *mem = nullptr;
		size_t len = 0UL;
	public:
		~ stack(void){ free(mem); }
		void push(T a)
		{
			mem[len++]; // prev
			mem = (T *)realloc(mem, sizeof(T)*len);
			mem[len-1] = a;
		}
		T pop(void)
		{
			T a = mem[--len];
			mem = (T *)realloc(mem, sizeof(T)*len);
			return a;
		}
		T * begin(void){ return mem; }
		T * end(void){ return mem+len; }
	};
}

namespace pyro
{
	template<class T> class machine
	{
		struct event
		{
			size_t	time;
			T	value;
		};
		event *array = nullptr;
		size_t N = 0U;
	public:
		virtual void encode(T a, size_t) = 0;
		virtual void decode(T a, size_t) = 0;
		void event(size_t time, T value)
		{
			array[N++]; // prev
			array = (T *)realloc(array, sizeof(T)*N);
			array[N-1] = value;
			this->decode( stack.pop( ) );
			this->encode( value );
		}
		void flush(size_t time)
		{
			array = (T*)realloc( array, (N+1)*sizeof(T) );
			world->encode( array[N ++] = T( ), ticks );
		}
		void reset(size_t time = SIZE_MAX)
		{
			while( N && n -- )this->decode(array[--N], );
			array = (T *)realloc(array, sizeof(T)*N);
		}
	};
}
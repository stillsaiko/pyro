# pragma once
namespace pyro
{
	struct LR { short L, R; };
	template<class T> class codec
	{
		T *stack = nullptr;
		size_t count = 0U;
	public:
		virtual ~ codec(void)
		{
			free(stack);
		}
		size_t event(T value)
		{
			stack = (T *)realloc(stack, sizeof(T)*++count);
			return this->encode( stack[count-1] = value );
		}
		size_t reset(size_t n)
		{
			size_t a = 0;
			if(n > count)
			   n = count;
			for(size_t i=0; i<n; ++i)
			{
				a += this->decode(stack[--count]);
				stack[count].~T( );
			}
			stack = (T *)realloc(stack, sizeof(T)*count);
			return a;
		}
		virtual size_t flush(size_t) = 0;
		virtual size_t encode(T) = 0;
		virtual size_t decode(T) = 0;
	};
	template<class T>
	struct audio : public codec<T*>
	{
		size_t flush(size_t)override
		{
		}
		size_t encode(T *buffer)override
		{
			
		}
		size_t decode(T *buffer)override
		{
			delete[ ] buffer;
		}
	};
}
# include <b40.h>
# include <pyro/stack.h>
namespace Game
{
	size_t time(void);
	using namespace pyro;
	struct event
	{
		B40LL	name;
		size_t	time;
	};
	pyro::
	stack<event>	stack;
	codec<event> *	world;
	void input(event event)
	{
		world->decode( stack.pop( ) );
		world->encode( event );
		stack.push( event );
	}
	void flush(size_t n)
	{
		event event {B40LL( ), n};
		world->encode( event );
		stack.push( event );
	}
}
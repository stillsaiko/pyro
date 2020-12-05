# pragma once
# include <cassert>
# include <utility>
namespace pyro
{
	template<class T> struct track
	{
		T             *queue = nullptr;
		size_t         count = 0;
		size_t         delay = 0;
		size_t (const *event)(const T &);
		track( size_t (*func)(const T &) ): event(func) { }

		void push(T &&refref)
		{
			queue = (T *)realloc(queue, sizeof(T)+sizeof(T)*count);
			queue[count ++] = std::move(refref);
		}

		void flush(size_t ticks)
		{
			assert(event);
			assert(index < length);
			while(delay <= ticks)
			{
				ticks -= delay;
				delay = event(queue[index]);
				index = ++ index % length;
			}
			delay -= ticks;
		}

		void reset(void)
		{
			index = 0;
		}
	};
	struct event { };
	void foo(void)
	{
		track<event> track = static_cast<size_t (*)(const event &)>(
							[ ](const event &) { return 0u; });
		track.push(event { });
		track.push(event { });
		track.push(event { });
		track.flush(1337);
	}
}
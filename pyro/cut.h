# pragma once
# include "obj.h"
namespace pyro
{
	template<class T>
	struct cut :
	public obj<T>
	{
		bool	inv = false;
		size_t	off = 0ULL;
		int64_t	avg[2][sizeof(T)/alignof(T)]; 
		size_t flush(size_t n, T *p)override
		{
			long long acc = cut * 4294967296LL;
			for(T*q=p; q<n+ahead(n); ++q)
			{
				for(size_t k=0; k<2; ++k)
				{
					align_i( avg[1] )[k] += align*q * acc;
				}
				acc = acc  * (65535U - off) / 65535LL;
			}

			for(T*q=p+n+ahead(n); q>p; --q)
			{
				avg[0][0] += *q * acc;
				acc = acc * (65535U - off) / 65535LL;
				accum[k] = cut * 4294967296LL * pow((65535U - cut) / 65535.0, i+1UL);
			}
			return n;
		}
		size_t ahead(size_t n)override
		{
			return off;
		}
	};
}
# include <initializer_list>
namespace pyro
{
	template<class T>
	struct que :
	public obj<T>
	{
		obj<T> * p = nullptr;
		size_t N = 0ULL;
		que(std::initializer_list<obj<T>*> il)
		{
			p = malloc( il.size( ) * sizeof(obj<T>*) );
			for(obj<T> *q : il) p[N++] = q;
		}
		~que(void) // virtual?
		{
			free(p); // `if(p)' not necessary
		}
		void push(T *q)
		{
			p = (obj<T>*)realloc(p, ++N*sizeof(obj<T>*));
			p[N-1] = q;
		}
		T *pop(void)
		{
			memmove(p, p+1, sizeof(obj<T>*)*--N);
			T *q = p[N];
			p = (obj<T>*)realloc(p, N*sizeof(obj<T>*)); // not necessary
			return q;
		}
		size_t flush(size_t n, T *p)override
		{
			for(size_t k=0ULL; k<N; ++k)
				n = p[k].flush(n, p);
			return n;
		}
		size_t ahead(size_t n)override
		{
			size_t a = 0ULL;
			for(size_t k=0ULL; k<N; ++k)
				a += p[k].ahead(n);
			return a;
		}
		T *begin(void){ return p; }
		T *end(void){ return p+N; }
	};
}
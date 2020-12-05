# pragma once
namespace pyro {
	template<class T> struct wave {
		enum { saw, abs, arc };
		const decltype(saw) type;
		const unsigned Hz;
		const unsigned volume;
		size_t index = 0UL;
		wave(decltype(saw), unsigned=440U, unsigned=4096U);
		size_t flush(size_t, T *);
	};
}
// wave.cpp
# include "wave.h"
namespace pyro {
	template<class T> wave<T>::wave(decltype(saw) T, unsigned Hz, unsigned vol):
		type(T), Hz(44100/Hz), volume(vol)
	{ }
	template<class T> size_t wave<T>::flush(size_t n, T * p){
		constexpr float pi = 3.1415926535897932384626433832795 ;
		for(size_t k=0UL; k < n; ++k){
			switch(type){
				case saw:
					p->L = p->R = 0;
					for(size_t i=1UL; i<=17UL; ++i)
						p->L += volume * sin(pi*Hz/22050 * (index+k) * i) / i,
						p->R += volume * sin(pi*Hz/22050 * (index+k) * i) / i;
					break;
				case abs:
					p->L = p->R = 0;
					for(size_t i=1UL; i<=17UL; ++i)
						p->L += volume * cos(pi*Hz/22050 * (index+k) * i) / i,
						p->R += volume * cos(pi*Hz/22050 * (index+k) * i) / i;
					break;
				case arc:
					p->L = p->R = 0;
					for(size_t i=1UL; i<=17UL; ++i)
						p->L += volume * cos(pi*Hz/22050 * (index+k) * (i*2-1)) / i,
						p->R += volume * cos(pi*Hz/22050 * (index+k) * (i*2-1)) / i;
					break;
				default: // error
					break;
			}
			++ p ;
		}
		index = ( index + n ) % Hz ;
		return n ;
	}
}
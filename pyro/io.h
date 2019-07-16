# pragma once
/*namespace pyro {
	template<class T> struct in { virtual void invoke(const T *, size_t = 1u) = 0; };
	template<class T> struct out { virtual size_t flush(T * = nullptr, size_t = 1u) = 0; };
// std=c++17
	template<class T> static inline in<T> * in_ptr = nullptr ;
	template<class T> static inline out<T> * out_ptr = nullptr ;
}*/
# include "unique.h"
namespace pyro {
	template<class T> struct addr {
		unsigned long long ULL = 0ULL ;
		addr(unsigned long long ULL): ULL(ULL) { }
		T * operator -> (void){
			return & unique<T>[ULL];
		}
		T & operator * (void){
			return unique<T>[ULL];
		}
	};
}
// PTR<video_t>->flush( )
// PTR<audio_t>->flush(44100)
template<class T> static inline pyro::addr<T> PTR ;
// pyro::ptr<video_t>->flush( )
// pyro::ptr<audio_t>->flush(44100)
namespace pyro
{
	///////////////////////////////////////////
	template<class T> struct io
	{
		virtual T * flush(size_t = 1UL, T * = nullptr) = 0;
		///////////////////////////////////////////
	};
// std=c++17
//	template<class T> static inline pyro::io_t<T> * io = nullptr ;
}
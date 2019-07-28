# pragma once
# include <cstdlib> // size_t (MinGW)
namespace pyro {
	template<class T> struct audio {
		// WAVEOUT
		/*virtual*/ size_t flush(T *, size_t)/* = 0*/;
	};
}

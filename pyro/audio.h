# pragma once
namespace pyro {
	template<class T> struct audio {
		// WAVEOUT
		/*virtual*/ size_t flush(T *, size_t)/* = 0*/;
	};
}
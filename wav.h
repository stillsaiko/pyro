# pragma once
// RIFF WAVE
# include "rc.h"
//struct LR { short L, R; };
// struct LR { short L, R }
// WAV<LR> sample = WAV<LR>(RC(".wav"))
// for(size_t i=0UL; i<sample.length; ++i)
//	( sample[i].L + sample[i].R ) / 2 ...
template<class T/* = LR*/> struct WAV {
	~
	WAV(void);
	WAV(void);
	WAV(RC&&);
	WAV& operator = (WAV&&)noexcept ;
	T& operator[ ](size_t);
private:
	RC rc ; // RIFF WAVE
public:
	const size_t length;
	/*inline size_t length(void){
		return rc.n > 44UL ? rc.n - 44UL : 0UL;
	}*/
	inline T* begin(void){
		return rc.size > 44UL ? reinterpret_cast<T*>(&rc[0] + 44UL) : nullptr;
	}
	inline T* end(void){
		return rc.size > 44UL ? reinterpret_cast<T*>(&rc[0] + rc.size) : nullptr;
	}
};
// wav.inl
# define WIN32_MEAN_AND_LEAN
# include <windows.h>
# include <mmsystem.h> // WAVEFORMAT
# include <type_traits> // std::move
# include <cassert>
# include <memory> // std::move MinGW
template<class T> WAV<T>::~WAV(void){ }
template<class T> WAV<T>::WAV(void){ }
template<class T> WAV<T>::WAV(RC&& rc):length(rc.size > 44UL ? rc.size - 44UL : 0UL){
	this->rc = std::move(rc);
}
template<class T> WAV<T>& WAV<T>::operator = (WAV&& a)noexcept {
	if( rc = std::move(a.rc) ){
		WAVEFORMAT & RIFF = (WAVEFORMAT&)rc[20];
		assert(RIFF.wFormatTag == WAVE_FORMAT_PCM);
		assert(RIFF.nChannels == sizeof(T) > 3 ? 2 : 1);
		assert(RIFF.nSamplesPerSec == 44100u); // ...
		assert(RIFF.nAvgBytesPerSec == 176400u); // ...
		assert(RIFF.nBlockAlign == 4u);
	//	assert(RIFF.wBitsPerSample == sizeof(T) * 8u);
		const_cast<size_t&>(length) = a.length;
		const_cast<size_t&>(a.length) = 0UL;
	}
	return *this ;
}
template<class T> T& WAV<T>::operator[ ](size_t n){
	assert(rc);
	assert(n + 44 < rc.n);
	return ((T *)&rc[44])[n];
}

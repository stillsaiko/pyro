# define WIN32_MEAN_AND_LEAN
# include <windows.h>
# include <mmsystem.h> // WAVEFORMAT
# include <type_traits> // std::move
# include <cassert>
# include <memory> // std::move MinGW
template<class T> WAV<T>::~WAV(void){ }
template<class T> WAV<T>::WAV(void){ }
template<class T> WAV<T>::WAV(RC&& rc){
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
	}
	return *this ;
}
template<class T> T& WAV<T>::operator[ ](size_t n){
	assert(rc);
	assert(n + 44 < rc.n);
	return ((T *)&rc[44])[n];
}

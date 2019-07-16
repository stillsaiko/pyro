# pragma once
# define WIN32_MEAN_AND_LEAN
# include <windows.h>
# include <mmsystem.h>
// docs.google.com/document/d/1x1gQ91aYWOecjh43q1ueLk-vXo_ASXoJPgoD5GEjAYk
# include <cassert>
# include <cstdio>
// include <vector>
template<class T, size_t N = 2u> struct WAVEOUT {
	~
	WAVEOUT(void);
	WAVEOUT(void);
	WAVEOUT(HWND window, size_t rate = 44100u);
	WAVEOUT& operator = (WAVEOUT&&)noexcept ;
	T * operator( )(T * samples, size_t length);
	void resize(size_t samples);
private:
	WAVEHDR HDRs[N] = {0};
	size_t current = 0u ;
public: // ...
	HWAVEOUT H = NULL ;
};//https://www.youtube.com/watch?v=ypknY6nIDe0
// waveout.inl
template<class T, size_t N>
WAVEOUT<T,N>::~WAVEOUT(void){
	if(H) printf("warning: WAVEOUT (destructor)\n");
	if(H) Sleep(1000); // magix
	if(H) assert(waveOutClose(H) == MMSYSERR_NOERROR);
}
template<class T, size_t N>
WAVEOUT<T,N>::WAVEOUT(void){ }
// ...
template<class T, size_t N>
WAVEOUT<T,N>::WAVEOUT(HWND window, size_t rate){
	WAVEFORMATEX WFX {
		( WORD )WAVE_FORMAT_PCM, // format type
		( WORD )(sizeof(T) > 3 ? 2 : 1), // number of channels (i.e. mono, stereo...)
		(DWORD )rate, // sample rate
		(DWORD )(sizeof(T) * rate), // for buffer estimation
		( WORD ) sizeof(T), // block size of data
		( WORD )(sizeof(T) > 3 ? sizeof(T) * 4 : sizeof(T) * 8), // number of bits per sample of mono data
		0 // the count in bytes of the size of extra information (after cbSize)
	};
	switch(waveOutOpen(&H, WAVE_MAPPER, &WFX, (DWORD_PTR)window, 0, CALLBACK_WINDOW)){
		case MMSYSERR_ALLOCATED :
			printf("Specified resource is already allocated.\n");
			return;
		case MMSYSERR_BADDEVICEID :
			printf("Specified device identifier is out of range.\n");
			return;
		case MMSYSERR_NODRIVER :
			printf("No device driver is present.\n");
			return;
		case MMSYSERR_NOMEM :
			printf("Unable to allocate or lock memory.\n");
			return;
		case WAVERR_BADFORMAT :
			printf("Attempted to open with an unsupported waveform-audio format.\n");
			return;
		case WAVERR_SYNC :
			printf("The device is synchronous but waveOutOpen was called without using the WAVE_ALLOWSYNC flag.\n");
			return;
		case MMSYSERR_NOERROR:
			break;
		default:
			printf("warning: waveOutOpen\n");
			break ;
	}
	assert(H);
}
template<class T, size_t N>
WAVEOUT<T,N> &
WAVEOUT<T,N>::operator = (WAVEOUT<T,N>&& a)noexcept {
	if(H) Sleep(1000); // magix
	if(H) assert(waveOutClose(H) == MMSYSERR_NOERROR);
	H = a.H ; a.H = NULL ;
	memcpy(HDRs, a.HDRs, sizeof HDRs);
	memset(a.HDRs, 0, sizeof HDRs);
	current = a.current ; a.current = 0u ;
	return *this ;
}
template<class T, size_t N>
T * WAVEOUT<T,N>::operator( )(T * samples, size_t n){
	assert(HDRs[current].lpData == nullptr);
	assert(HDRs[current].dwBufferLength == 0u);
	assert(HDRs[current].dwBufferLength == 0u);
	assert(HDRs[current].dwUser == 0u);
//	assert(HDRs[current].dwFlags == 0u);
	assert(HDRs[current].dwLoops == 0u);
	HDRs[current].lpData = reinterpret_cast<LPSTR>(samples); // pointer to locked data buffer
	HDRs[current].dwBufferLength = n * sizeof(T); // length of data buffer
	HDRs[current].dwBytesRecorded = (DWORD)0; // used for input only
	HDRs[current].dwUser = (DWORD_PTR)current ; // for client's use
	HDRs[current].dwFlags = (DWORD)0; // assorted flags (see defines)
	HDRs[current].dwLoops = (DWORD)0; // loop control counter
	switch(waveOutPrepareHeader(H, &HDRs[current], sizeof HDRs[current]) ){
		case MMSYSERR_INVALHANDLE:
			printf("MMSYSERR_INVALHANDLE: Specified device handle is invalid.\n");
			break ;
		case MMSYSERR_NODRIVER:
			printf("MMSYSERR_NODRIVER: No device driver is present.\n");
			break ;
		case MMSYSERR_NOMEM:
			printf("MMSYSERR_NOMEM: Unable to allocate or lock memory.\n");
			break ;
		case MMSYSERR_NOERROR:
			break;
		default:
			printf("warning: waveOutPrepareHeader\n");
			break ;
	}
	switch( waveOutWrite(H, &HDRs[current], sizeof HDRs[current]) ){
	case MMSYSERR_INVALHANDLE:
		printf("Specified device handle is invalid.\n");
		break ;
	case MMSYSERR_NOMEM:
		printf("Unable to allocate or lock memory.\n");
		break ;
	case WAVERR_UNPREPARED:
		printf("The data block pointed to by the pwh parameter hasn't been prepared.\n");
		break ;
	case MMSYSERR_NOERROR:
		break;
	default:
		printf("warning: waveOutWrite\n");
		break ;
	}
	current = ( current + 1 ) % N ;
	// prepare next buffer
	T * previous = reinterpret_cast<T *>( HDRs[current].lpData );
	HDRs[current].lpData = nullptr ; // pointer to locked data buffer
	HDRs[current].dwBufferLength = (DWORD)0; // length of data buffer
	HDRs[current].dwBytesRecorded = (DWORD)0; // used for input only
	HDRs[current].dwUser = (DWORD_PTR)0; // for client's use
//	HDRs[current].dwFlags = (DWORD)0; // assorted flags (see defines)
	HDRs[current].dwLoops = (DWORD)0; // loop control counter
	return previous ;
}
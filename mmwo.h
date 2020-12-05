# pragma once
// [deprecated] try <audclnt.h> instead.
# ifdef _WIN32
# ifndef WIN32_MEAN_AND_LEAN
# define WIN32_MEAN_AND_LEAN
# include <windows.h>
# endif
# include <mmsystem.h>
# else
# error winmm.lib
# endif
// docs.google.com/document/d/1x1gQ91aYWOecjh43q1ueLk-vXo_ASXoJPgoD5GEjAYk
# include <cassert>
# include <cstdio>
// struct LR { short L, R }
// static MMWO<LR> WO
// case WM_CREATE:
//	WO = MMWO<LR>(HWND, 44100)
// case WM_DESTROY:
//	WO = MMWO<LR>( ) // release
// case MM_WOM_OPEN:
//	WO.push(8820UL, new LR[8820]) // queue 200 ms
//	WO.push(8820UL, new LR[8820]) // queue 200 ms
// case MM_WOM_DONE:
//	delete[ ] WO.pop(WPARAM, LPARAM)
//	WO.push(8820UL, new LR[8820]) // queue 200 ms
template<class T> struct MMWO {
	~
	MMWO(void);
	MMWO(void);
	MMWO(HWND window, DWORD rate = 44100);
	MMWO& operator = (MMWO&&)noexcept ;
	void push(size_t length, T * samples);
	T * pop(WPARAM, LPARAM); // -> samples
//	void resize(size_t samples);
private:
	LPWAVEHDR *	HDRs = nullptr; // array
	size_t		HDRn = 0UL; // multi-buffer / queue-length
public: // ...
	HWAVEOUT H = NULL ;
};//https://www.youtube.com/watch?v=ypknY6nIDe0
// waveout.inl
template<class T>
MMWO<T>::~MMWO(void){
	if(H) printf("warning: WAVEOUT (destructor)\n");
	if(H) Sleep(1000); // magix
	if(H) waveOutClose(H); // assert == MMSYSERR_NOERROR
	// copy #1
	if(HDRs)
	{
		for(size_t i=0UL; i<HDRn; ++i)
		delete HDRs[i];
		delete[ ] HDRs;
	}
}
template<class T>
MMWO<T>::MMWO(void){ }
// ...
template<class T>
MMWO<T>::MMWO(HWND window, DWORD rate){
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
template<class T>
MMWO<T> &
MMWO<T>::operator = (MMWO<T>&& a)noexcept {
	if(H) Sleep(1000); // magix
	if(H) waveOutClose(H); // assert == MMSYSERR_NOERROR
	// copy #2
	if(HDRs)
	{
		for(size_t i=0UL; i<HDRn; ++i)
		delete HDRs[i];
		delete[ ] HDRs;
	}
	memcpy(this, &a, sizeof a);
	memset(&a,    0, sizeof a);
	return *this ;
}
template<class T>
void MMWO<T>::push(size_t n, T * samples){
	HDRs = (WAVEHDR**)realloc(HDRs, (HDRn+1UL)*sizeof(LPWAVEHDR));
	HDRs[HDRn] = new WAVEHDR {0};
	HDRs[HDRn]->lpData = reinterpret_cast<LPSTR>(samples); // pointer to locked data buffer
	HDRs[HDRn]->dwBufferLength = n * sizeof(T); // length of data buffer
	HDRs[HDRn]->dwBytesRecorded = (DWORD)0; // used for input only
	HDRs[HDRn]->dwUser = (DWORD_PTR)HDRn ; // for client's use
	HDRs[HDRn]->dwFlags = (DWORD)0; // assorted flags (see defines)
	HDRs[HDRn]->dwLoops = (DWORD)0; // loop control counter
	switch( waveOutPrepareHeader(H, HDRs[HDRn], sizeof(WAVEHDR)) ){
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
	switch( waveOutWrite(H, HDRs[HDRn], sizeof(WAVEHDR)) ){
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
	++ HDRn;
}
template<class T>
T * MMWO<T>::pop(WPARAM W, LPARAM L){
	assert((HWAVEOUT)W == H);
	for(size_t i=0UL; i<HDRn; ++i)
	if((LPWAVEHDR)L == HDRs[i]) // i == HDRs[i]->dwUser
	{
		LPSTR lpData = HDRs[i]->lpData;
		delete HDRs[i];
		-- HDRn;
		memmove(HDRs+i, HDRs+i+1, (HDRn-i)*sizeof(LPWAVEHDR));
		HDRs = (LPWAVEHDR*)realloc(HDRs, (HDRn)*sizeof(LPWAVEHDR));
		return reinterpret_cast<T *>(lpData);
	 }
	return nullptr; // error
}
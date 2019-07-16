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
# include "waveout.inl"
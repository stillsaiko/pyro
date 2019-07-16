# pragma once
# include "rc.h"
// class T = struct LR { unsigned short L, R }
template<class T> struct WAV {
	~
	WAV(void);
	WAV(void);
	WAV(RC&&);
	WAV& operator = (WAV&&)noexcept ;
	T& operator[ ](size_t);
private:
	RC rc ; // RIFF WAVE
};
# include "wav.inl"
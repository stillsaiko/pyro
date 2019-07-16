# include "note.h"
# include <cassert>
# include <cmath> // sin cos MinGW
namespace pyro {
	note::~note(void){ }
	note::note(void){ }
	note::note(char key, size_t n){
		if(key > ' ' && key <= '~'){
			pitch = key - '!';
			this->n = n;
			decay = new float[n];
			for(size_t i=0u; i<n; ++i)
				decay[i] = 1.f;
		} else {
			printf("warning: note(%c, %u)\n", key, n);
		}
	}
	note& note::operator = (note&& a)noexcept {
		pitch = a.pitch ; a.pitch = 0u ;
		n = a.n ; a.n = 0u ;
		if( decay )delete[ ] decay ;
		decay = a.decay ; a.decay = nullptr ;
		iter = a.iter ; a.iter = 0u ;
		return *this ;
	}
	void note::flush(LR * ptr, size_t size){
		while(size){
			for(size_t i=0u; i<n; ++i){
				ptr[0].L = decay[i] * sin((i+iter) * pitch / 2048.f) * 32767;
				ptr[0].R = decay[i] * cos((i+iter) * pitch / 2048.f) * 32767;
			}
			-- size ;
			++ ptr ;
			++ iter ;
		}
		for(size_t i=0u; i<n; ++i)
			decay[i] *= 1.f - i*.3f/n ;
	}
}

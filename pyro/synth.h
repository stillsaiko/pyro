# pragma once
# include <vector>
# include <wav.h>
namespace pyro {
	template<class T> struct tone {
		unsigned key;
	};
	template<class T> struct synth {
		tone<T>& insert(intptr_t, tone<T>&&);
	private:
		size_t size = 0UL;
		tone<T> * tune = nullptr;
		intptr_t * time = nullptr;
	};
/*	struct synth {
		void blit(const LR * data, size_t size, int offset = 0);
		void reset(void);
// const
		operator size_t(void)const ;
	private:
		std::vector<LR> buffer ;
	};*/
}
namespace pyro {
	template<class T> tone<T>& synth<T>::insert(intptr_t t, tone<T>&& a){
		size_t i=0UL;
		while(time[i] < t && i < size) ++ i;
		time = (intptr_t*)realloc(time, ++size*sizeof(intptr_t));
		tune = (tone<T>*)realloc(tune, size*sizeof(tone<T>));
		memmove(time+i+1UL, time+i, sizeof(intptr_t));
		memmove(tune+i+1UL, tune+i, sizeof(tone<T>));
		time[i] = t;
		return tune[i] = std::move(a);
	}
/*	void track::blit(const LR * data, size_t size, int offset){
		if(offset + size > buffer.size( ))	buffer.resize(offset + size);
		for(size_t i(0u); i<size; ++i)		buffer[offset+i].L += data[i].L,
											buffer[offset+i].R += data[i].R ;
	}
	void track::reset(void){
		buffer.clear( );
	}
// const
	track::operator size_t(void)const {
		return buffer.size( );
	}*/
}
# pragma once
# include <vector>
# include <wav.h>
namespace pyro {
	struct synth {
		void blit(const LR * data, size_t size, int offset = 0);
		void reset(void);
// const
		operator size_t(void)const ;
	private:
		std::vector<LR> buffer ;
	};
}
namespace pyro {
	void track::blit(const LR * data, size_t size, int offset){
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
	}
}
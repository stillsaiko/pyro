# include "mid.h"
constexpr unsigned BIG32(const char a[4]){
	return	static_cast<unsigned char>(a[0]) << 24u
		^	static_cast<unsigned char>(a[1]) << 16u
		^	static_cast<unsigned char>(a[2]) << 8u
		^	static_cast<unsigned char>(a[3]) << 0u ;
}
constexpr unsigned BIG16(const char a[2]){
	return	static_cast<unsigned char>(a[0]) << 8u
		^	static_cast<unsigned char>(a[1]) << 0u ;
}
MID::~MID(void)noexcept {
	// release......................
}
MID::MID(void){ }
# include <cassert>
# include <cstdio>
MID::MID(RC&& a){
	size_t pop_i(0u);
	auto pop = [&](size_t n){
		const char * p = &a[pop_i];
		pop_i += n ;
		return p ;
	};
	unsigned format ;
	unsigned tracks ;
	unsigned delta ;
	while(pop_i < a.size){
		unsigned type = BIG32(pop(4u));
		unsigned n = BIG32(pop(4u));
		switch(type){
			case BIG32("MThd"):
				printf("MThd\n");
				assert(n == 6u);
				format = BIG16(pop(2u));
				tracks = BIG16(pop(2u));
				delta = BIG16(pop(2u));
				break ;
			case BIG32("MTrk"):{
				printf("MTrk\n");
				unsigned pop_n = pop_i + n ;
				while(pop_i < pop_n){
					unsigned long long delta(0ULL);
			/*	unsigned why = 0;
				if(unsigned char byte = *pop(1u))do {
					printf("unsigned byte %u (delta)\n", (unsigned)byte);
					delta *= 128;
					byte = *pop(1u);
					delta += byte & 0b01111111 ;
				} while(byte & 0b10000000 && ++why<4);*/
					unsigned char c ;
					if((delta = (unsigned char)*pop(1u)) & 0x80){
						delta &= 0x7f;
						do {
							delta = (delta << 7) + ((c = *pop(1u)) & 0x7f);
						} while (c & 0x80);
					}
					// sleep delta here
					printf("sleep %u\n", (unsigned)delta);
					unsigned char byte = *pop(1u);
				//	printf("unsigned byte %u\n", (unsigned)byte);
					switch(byte >> 4u){
						case 0b1000:{
							unsigned char nn = *pop(1u);
							unsigned char vv = *pop(1u);
							printf("x=%u nn=%u vv=%u release\n", byte&0b1111, nn, vv);
							break ;
						}
						case 0b1001:{
							unsigned char nn = *pop(1u);
							unsigned char vv = *pop(1u);
							printf("x=%u nn=%u vv=%u trigger\n", byte&0b1111, nn, vv);
							break ;
						}
						case 0b1010:{
							unsigned char nn = *pop(1u);
							unsigned char vv = *pop(1u);
							printf("x=%u nn=%u vv=%u decay\n", byte&0b1111, nn, vv);
							break ;
						}
						case 0b1011:{
							unsigned char cc = *pop(1u);
							unsigned char vv = *pop(1u);
							printf("x=%u cc=%u vv=%u control\n", byte&0b1111, cc, vv);
							break ;
						}
						case 0b1101:{
							unsigned char cc = *pop(1u);
							printf("x=%u cc=%u channel decay\n", byte&0b1111, cc);
							break ;
						}
						case 0b1110:{
							unsigned char bb = *pop(1u);
							unsigned char tt = *pop(1u);
							printf("x=%u bb=%u tt=%u pitch\n", byte&0b1111, bb, tt);
							break ;
						}
						default:{
							printf(".");
							if(byte == 255){
								pop(1u);
								unsigned char len = *pop(1u);
								pop(len);
							} else {
								unsigned char nn = *pop(1u);
								pop(nn);
							}
							break ;
						}
					}
				}
				break ;
			}
			default:
				break ;
		}
	}
}
void MID::operator = (MID&&)noexcept {
	this->~MID( ); // ~
	// move......................
}
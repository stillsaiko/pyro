# pragma once
# include <rc.h>
template<class T> struct PNG ;
# include <memory> // std::move (MinGW)
template<> struct PNG<void> {
	~
	PNG(void);
	PNG(void);
	PNG(RC&&);
	PNG<void>&
	operator = (PNG<void>&&)noexcept ;
	void * operator * (void);
// attrib
	const unsigned X ; // width
	const unsigned Y ; // height
	const unsigned Z ; // bit depth
	const unsigned N ; // color type
public:
	void decode(const char*); // compression & filter
	void endian(void);
//	unsigned char	colour ;
	char * memory = nullptr ;
};
# include <cassert>
// either 1 or 2
// T**
# include <typeinfo>
// struct RGB { uint8_t R, G, B }
// PNG<RGB> image = PNG<RGB>(RC(".png"))
// for(size_t Y=0UL; Y < image.Y; ++Y)
// for(size_t X=0UL; X < image.X; ++X)
//	image[Y][X].R = ...
//	image[Y][X].G = ...
//	image[Y][X].B = ...
template<class T> struct PNG : public PNG<void> {
	static_assert(alignof(T)<3, "max depth of 16 bit (either 1 or 2)");
	PNG(RC&& file): PNG<void>( std::move(file) ){
		if(memory && X*Y && Z*N)
		if(sizeof(T) != alignof(T)*N || alignof(T) != Z){
			printf("warning: convert %ubit to %ubit %s\n", 8*N*Z, 8*sizeof(T), typeid(T).name( ));
			char * mem = (char*)malloc(sizeof(T)*X*Y);
			unsigned L(0u);
			unsigned R(0u);
			for(unsigned i(0u); i<Y; ++i)
			for(unsigned j(0u); j<X; ++j){
				for(unsigned n(0u); n<sizeof(T)/alignof(T); ++n)
				for(unsigned k(0u); k<alignof(T); ++k){
			//	mem[sizeof(T)*(X*i+j)+n*alignof(T)+k] = n<N?memory[Z*N*(X*i+j)+n*Z+k%Z+Z/alignof(T)/2]:255;
					mem[L+n*alignof(T)+k] = n<N?memory[R+n*Z+k%Z+Z/alignof(T)/2]:255;
				}
				L += sizeof(T);
				R += N*Z ;
			}
			free(memory);
			memory = mem ;
		}
	/*	if(alignof(T) < Z){
			for(unsigned i(0u); i<Y; ++i)
			for(unsigned j(0u); j<X; ++j)
			for(unsigned k(0u); k<Z; ++k)
			for(unsigned n(0u); n<N; ++n)

			// TODO: convert 16 -> 8 bit here
		}
		if(alignof(T) > Z){
			// TODO: convert 8 -> 16 bit here
		}*/
/*		// after dynamic DEFLATE decoding here
		if(sizeof(T) == Z*N)return ;
		if(sizeof(T) > Z*N){ // extend 255
			printf("warning: PNG<%s> color expand %u byte(s) 0xFF\n", typeid(T).name( ), sizeof(T) - Z*N);
			// e.g. convert RGB.PNG into PNG<RGBA> alias append alpha component
			memory = (char*)realloc(memory, sizeof(T)*X*Y);
			for(unsigned i(0u); i<Y; ++i)
			for(unsigned j(0u); j<X; ++j)
# define i (Y-i-1)
# define j (X-j-1)
//				memmove(memory+sizeof(T)*(X*i+j), memory+N*(X*i+j), N),
//				memset(memory+sizeof(T)*(X*i+j)+N, 255, sizeof(T) - N);
				memmove(		operator[ ](i)+j, memory+Z*N*(X*i+j), Z*N),
				memset((char *)(operator[ ](i)+j)+Z*N, 255, sizeof(T)-Z*N);
//						(char*)(operator[ ](i)+j)+0 ;
//						(char*)(operator[ ](i)+j)+N ;
# undef i
# undef j
			return ;
		}
		if(sizeof(T) < Z*N){ // reduce
			printf("warning: PNG<%s> color reduce %u byte(s)\n", typeid(T).name( ), Z*N - sizeof(T));
			// e.g. convert RGBA.PNG into PNG<RGB> alias ignore alpha component
			for(unsigned i(0u); i<Y; ++i)
			for(unsigned j(0u); j<X; ++j)
				memmove(operator[ ](i)+j, memory+Z*N*(X*i+j), sizeof(T));
			return ;
		}*/
	}
	T * operator * (void){
		return &reinterpret_cast<T*>(memory)[0];
	}
	T * operator[ ](size_t n){
		return &reinterpret_cast<T*>(memory)[X * n];
	}
};
/*template<class T> struct PNG {
	unsigned width ;
	unsigned height ;
	unsigned char depth ;
	unsigned char color ;
	T * image = nullptr ;
	~
	PNG(void){ }
	PNG(void){ }
	PNG(RC&& a){
		size_t pop_i(0u);
		auto pop = [&](size_t n){
			const char * p = &a[pop_i];
			pop_i += n ;
			return p ;
		};
		assert(!memcmp(pop(8u), "\x89PNG\r\n\x1A\n", 8u));
		while(pop_i < a.n){
			if(unsigned long n = BIG32(pop(4u)))
			switch( BIG32(pop(4u)) ){
			case BIG32("IHDR"):
				assert(n == 13u);
				// discretization
				width = BIG32(pop(4));
				height = BIG32(pop(4));
				assert(width * height > 0u);
				// quantization
				depth = *(unsigned char*)pop(1u);
				color = *(unsigned char*)pop(1u);
				assert(sizeof(T) == depth/8u*(color/6u+3u));
				// ...
				assert(*pop(1u) == '\0'); // compression
				assert(*pop(1u) == '\0'); // filter
				assert(*pop(1u) == '\0'); // interlace
				break ;
			case BIG32("IDAT"):
				printf("zlib compression method/flags code %u\n", (unsigned)*(const unsigned char*)pop(1u));
				printf("Additional flags/check bits %u\n", (unsigned)*(const unsigned char*)pop(1u));
				n -= 2 ;
				// Compressed data blocks
				{
					unsigned long size = (1u + depth/8u*(color/6u+3u)*width) * height ;
					unsigned char * temp = new unsigned char[sizeof(T)*width*height + height]; // allocate memory
					if( int error = puff((unsigned char*)temp, &size, (const unsigned char*)pop(n), &n) ){
						printf("error: %s", puff_error[error + 11]);
					} else {
						printf("%s", puff_error[11]); // successful inflate
						// filter method 0
						image = new T[width*height]; // allocate memory
						for(unsigned i(0u); i<height; ++i)
						for(unsigned j(0u); j<width; ++j)
						for(unsigned k(0u); k<sizeof(T); ++k){
							unsigned char c = '\0', b = '\0';
							unsigned char a = '\0', x = temp[1u+i+sizeof(T)*(j + i*width) + k];
							unsigned char type        = temp[0u+i+sizeof(T)*(0 + i*width) + 0];
							if(i*j>0u) c = reinterpret_cast<char*>(&image[j-1 + (i-1)*width])[k];
							if(i > 0u) b = reinterpret_cast<char*>(&image[j-0 + (i-1)*width])[k];
							if(j > 0u) a = reinterpret_cast<char*>(&image[j-1 + (i-0)*width])[k];
							switch(type){
							case 0: // None
								reinterpret_cast<unsigned char*>(image+j+i*width)[k] = x ;
								break ;
							case 1: // Sub
								reinterpret_cast<unsigned char*>(image+j+i*width)[k] = x + a ;
								break ;
							case 2: // Up
								reinterpret_cast<unsigned char*>(image+j+i*width)[k] = x + b ;
								break ;
							case 3: // Average
								reinterpret_cast<unsigned char*>(image+j+i*width)[k] = x + (a + b) / 2;
								break ;
							case 4: // Paeth
								reinterpret_cast<unsigned char*>(image+j+i*width)[k] = [&](void){
									int PR ;
									int p = a + b - (int)c ;
									int PA = abs(p - a);
									int PB = abs(p - b);
									int PC = abs(p - c);
									if( PA <= PB && PA <= PC ) PR = a ;
									else if( PB <= PC ) PR = b ;
									else PR = c ;
									return x + PR ;
								}( );
								break ;
							default:
								assert(false);
								break ;
							}
						}
					} // finally
					delete[ ] temp ; // release memory
				}
				break ;
			case BIG32("IEND"):
				assert(n == 0u);
				break ;
			default:
				pop(n);
				break ;
			}
			pop(4u); // CRC
		}
	}
	void operator = (PNG&& a)noexcept {
		width = a.width ;
		height = a.height ;
		depth = a.depth ;
		if( image )delete[ ] image ;
		image = a.image ;
		a.image = nullptr ;
	}
	T * operator[ ](unsigned i){
		assert(image);
		return image + width*i ;
	}
};*/

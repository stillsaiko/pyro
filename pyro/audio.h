# pragma once
# include "codec.h"
# include <ini.h>
namespace pyro
{
	struct audio_event
	{
		enum { trigger, release } type;
		long Hz;
	};
	template<class T> class audio : public codec<audio_event>
	{
		// FXs
	public:
		audio(const INI & ini)
		{
			for(const INI::S & section : ini)
			switch(section)
			{
			case B40LL("cut"):
				// push_back new FX
				for(const INI::K & key : section)
				switch(key)
				{
				case B40LL("Hz"):
					key.as_long(); // ...
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		size_t flush(size_t n)override
		{
			return n;
		}
		size_t encode(audio_event a)override
		{
			switch(a.type)
			{
			case audio_event::trigger:
				break;
			case audio_event::release:
				break;
			default:
				break;
			}
			return 0;
		}
		size_t decode(audio_event a)override
		{
			switch(a.type)
			{
			case audio_event::trigger:
				break;
			case audio_event::release:
				break;
			default:
				break;
			}
			return 0;
		}
	};
}
# define NOMINMAX
# include "align.h"
# include <cmath> // log
# include <cstdio> // printf
# include <algorithm> // std::min
/*struct uint64
{
	typedef unsigned long long T;
	unsigned long long integral = 0LL;
	uint64(unsigned long long u): integral(u){ }
	uint128 divmul(unsigned long long div, unsigned long long mul)
	{
		integral = integral / div		// ^64 = ^64 / ^64
			 + integral % div * mul / div;	//     + ^64 % ^64 * ^64 / ^64
	}
	operator unsigned long long(void)const
	{
		return integral;
	}
};
struct uint128
{
	unsigned long long hi = 0LL;
	unsigned long long lo = 0LL;
	uint128(unsigned long long most, unsigned long long least): hi(most), lo(least){ }
//	uint128 operator * (unsigned long long
	uint128 operator / (unsigned long long div)
	{
		unsigned long long Z = 18446744073709551615ULL;
		unsigned long long W = 18446744073709551615ULL;
		if(  div > 1ULL  )
		Z /= div - 1ULL;
		W /= Z;
		return uint128(hi / div, lo / div + hi % div * Z / div * W);
	}
	unsigned long long operator % (unsigned long long mod) // return operator - (operator / (mod));
	{
		return ((hi % mod) * ((unsigned long long)-mod % mod) + (lo % mod)) % mod;

		unsigned long long Z = 18446744073709551615ULL;
		unsigned long long W = 18446744073709551615ULL;
		if(  mod > 1ULL  )
		Z /= mod - 1ULL;
		W /= Z;
		return uint128(
			hi - hi / mod - (lo - (lo / mod + hi % mod * Z / mod * W) > lo ? 1 : 0),
			lo - lo / mod + hi % mod * Z / mod * W
		)
		-> uint128(
			hi / mod,
			lo / mod + hi % mod * Z / mod * W
		);
		return operator - ( uint128(hi / mod, lo / mod + hi % mod * Z / mod * W) * mod );
	}
	uint128 operator + (unsigned long long add)
	{
		return uint128(lo > lo + add ? hi : hi + 1ULL, lo + add);
	}
	uint128 operator - (unsigned long long sub)
	{
		return uint128(hi - (lo < lo - sub ? 1 : 0), lo - sub);
	}

	uint128 divmul(unsigned long long div, unsigned long long mul)
	{
		value	= operator / (div) // ^64 = ^64 / ^16 * ^16
			+ operator % (div) * 65535LL / (65535U - cut);
	}
};*/
namespace pyro
{
	template<class T> struct __audio
	{
		virtual size_t flush(size_t, T *) = 0;
		struct lowpass;
	};
	template<class T>
	struct __audio<T>::lowpass :
	public __audio<T>
	{
	//	double cut = 0.01; // ] 0.0, 1.0 [
		unsigned short cut = 655U; // ^16 ] 0U, 65535U [
		double avg_0[align<T>::N] = {0};
		long long avg_1[align<T>::N] = {0};
	//	align<T>::li avg_2[align<T>::N];
		size_t flush(size_t n, T *p)override
		{
		/*	for(size_t k=0UL; k < align<T>::N; ++ k)
			{
				avg[k][1] = 0.0;
				double accum(cut);
				for(size_t i=0UL; i<n; ++i)
				{
					avg[k][1] += align_i(p+i)[k] * accum;
					accum *= 1.0 - cut;
				}
			}*/
	//		ptrdiff_t n36 = (log(cut) + log(68719476736.0)) / log(1.0/(1.0-cut));
	//		ptrdiff_t n52 = (log(cut) + log(4503599627370496.0)) / log(1.0/(1.0-cut));
			
		//	ptrdiff_t n24 = (log(cut) + log(16777216.0)) / log(1.0/((65535U-cut)/65535.0));
			ptrdiff_t n24 = (log(cut) + log(268435456.0)) / log(1.0/((65535U-cut)/65535.0)); // n28
		//	ptrdiff_t n24 = (log(cut) + log(4294967296.0)) / log(1.0/((65535U-cut)/65535.0)); // n32
		//	ptrdiff_t n24 = (log(cut) + log(65536)) / log(1.0/((65535U-cut)/65535.0)); // n16

			ptrdiff_t n48 = (log(cut) + log(281474976710656.0)) / log(1.0/((65535U-cut)/65535.0));
		//	ptrdiff_t n64 = (log(cut) + log(18446744073709551616.0)) / log(1.0/(1.0-cut));
			ptrdiff_t n64 = (log(cut) + 44.3614195558364998) / log(1.0/((65535U-cut)/65535.0));
	//		printf("n36=%u n52=%u\n", n36, n52);
			printf("n24=%u n48=%u n64=%u\n", n24, n48, n64);
			T * const pn(p + n);
	//		long long avg_2[align<T>::N] {0};
	//		double avg_2_fmod[align<T>::N] {0};
	// ...........................................
			long long accum[align<T>::N]; // ^48 factor
		//	if( pn - p >= n48 )
			for(size_t k=0UL; k < align<T>::N; ++ k)
			{
				accum[k] = cut * 4294967296LL;//65536LL // ^48 = ^16 * ^32
			//	avg[k][1] *= 0.00000001;
		//		avg[k][1] = 0.0;
		//		avg_2_fmod[k] = 0.0;
				avg_1[k] = 0LL;
				for(size_t i=0UL; i < (std::min)(pn - p, n24); ++i)
				{
			//		avg[k][1] += align_i(p+i)[k] * accum[k];
					avg_1[k] += /*i%2==0?*/	align_i(p+i)[k] * accum[k] /* 281474976710656:*/; // ^64 += ^16 * ^48
					//	/* round( */	align_i(p+i)[k] * accum[k] /* 281474976710656	)*/;
					accum[k] = /*round(*/accum[k] * (65535U - cut) / 65535LL; // ^48 = ^48 * ^16 / ^16
					accum[k] = cut * 4294967296LL * pow((65535U - cut) / 65535.0, i+1UL);
				}
				if(k == 0UL) printf("%lli\n", accum[k]);
//				accum[k] /= (1.0 - cut);
//				accum[k] = cut * 4294967296LL * pow((65535U - cut) / 65535.0, (std::min)(pn - p, n24)-1);
			}
			do
			{

//				for(size_t i(0UL); i < (std::min)(pn - p, n24); ++ i)
//				{
				for(size_t k=0UL; k < align<T>::N; ++ k)
				{
	//				avg_0[k] *= 1.0 - cut;
	//				avg_0[k] += align_i(p)[k] * cut;

				//	avg_1[k] = /*round(*/(avg_1[k] - align_i(p)[k] * cut * 281474976710656) / (1.0 - cut);
					avg_1[k] -= /*65536LL*/4294967296LL * align_i(p)[k] * /*static_cast<long long>(*/cut; // ^64 -= ^32 * ^16 * ^16
//					avg_1[k] = /*round(*/avg_1[k] * 256LL / (65535U - cut) * 256LL; // ^64 = ^64 * ^8 / ^16 * ^8
				//	long long mod = avg_1[k] % (65535U - cut) * 65535LL / (65535U - cut);
	//				avg_1[k] = /*round(*/avg_1[k] * 65535U / (65535U - cut); // ^48 = ^48 * ^16 / ^16
					avg_1[k] = /*round(*/avg_1[k] / (65535U - cut) * 65535LL // ^64 = ^64 / ^16 * ^16
							   + avg_1[k] % (65535U - cut) * 65535LL / (65535U - cut);
					if(pn - p > n24)
						avg_1[k] += /*round(avg_1[k] +*/ align_i(p+n24)[k] * accum[k]; // ^64 += ^16 * ^48
			//		avg_2[k] -= align_i(p)[k] * cut * 281474976710656;
				//	avg_2[k] /= 1.0 - cut;
			//		double new_avg_2_fmod = fmod(avg_2[k] + avg_2_fmod[k], 1.0 - cut);
			//		avg_2[k] = (avg_2[k] + avg_2_fmod[k]) / (1.0 - cut);
			//		avg_2_fmod[k] = new_avg_2_fmod;

		//			align_i(p)[k] = (avg_0[k] + avg_1[k]/281474976710656) / 2.0;
					align_i(p)[k] = avg_1[k] / 281474976710656LL;//4294967296LL;
				//	align_i(p)[k] = avg[k][1];
			//		align_i(p)[k] = (avg[k][0] + avg[k][1]) / 2.0;
				}
				++ p;
//				}
			} while(p < pn);
			
		/*	for(T * const pn(p + n); bool(p < pn); ++ p)
			{
				for(size_t k=0UL; k < align<T>::N; ++ k)
				{
					if(k % log_n == 0)
					{
						avg[k][1] = 0.0;
						double accum(cut);
						for(T * pi(p); pi<pn && pi<p+log_n; ++pi)
						{
							avg[k][1] += align_i(pi)[k] * accum;
							accum *= 1.0 - cut;
						}
					}
					avg[k][0] *= 1.0 - cut;
					avg[k][0] += align_i(p)[k] * cut;

					avg[k][1] -= align_i(p)[k] * cut;
					avg[k][1] /= 1.0 - cut;

					align_i(p)[k] = avg[k][0] + avg[k][1];
				}
			}*/
			// prev impl ........
		/*	for(size_t k=0UL; i<n; ++i)
			{
			//	avg[k][1] = 0.0;
			//	for(size_t i=0UL; i<n; ++i)
			//	{
			//		avg[k][0] *= 1.0 - cut;
			//		avg[k][0] += p[n-i-1UL] * cut;
			//	}
				avg[k][1] = 0.0;
				{
					double weight(cut);
					for(size_t i=0UL; i<n; ++i)
					{
						avg[k][1] += p[i] * weight;
						weight *= 1.0 - cut;
					}
				}
				// calculate avg[1]
				T *pn = p + n;
				while(p < pn)
				{
				//	avg[0] = avg[0] * (1.0 - cut) + *p * cut;
				//
				//	avg[0] += (*p - avg[0]) * cut;
				//	avg[1] = (avg[1] - *p * cut) / cut;
				
					avg[k][0] *= 1.0 - cut;
					avg[k][0] += *p * cut;

					avg[k][1] -= *p * cut;
					avg[k][1] /= 1.0 - cut;

				//	*p = avg[0] = avg[0] * (1.0 - cut) + *p * cut;
					*p = avg[k][0] + avg[k][1];
					++ p;
				}
			}*/
			return n;
		}
	};
}
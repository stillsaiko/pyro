# include "int.h"
// unsigned
using pyro::uint128;
uint128 pyro::operator &(uint128 A, uint128 B){ return uint128(A.lo & B.lo, A.hi & B.hi); }
uint128 pyro::operator ^(uint128 A, uint128 B){ return uint128(A.lo ^ B.lo, A.hi ^ B.hi); }
uint128 pyro::operator |(uint128 A, uint128 B){ return uint128(A.lo | B.lo, A.hi | B.hi); }
uint128 pyro::operator +(uint128 A, uint128 B){ return uint128(A.lo + B.lo, (A.lo > UINT64_MAX - B.lo ? 1 : 0) + A.hi + B.hi); }
uint128 pyro::operator -(uint128 A, uint128 B){ }
# include "simd.h"
uint128 pyro::operator *(uint128 A, uint128 B)
{
# ifdef _M_IX86_FP
	uint64 lo[2] =
	SSE<uint32>(A.lo & 0xFFFFFFFF, A.lo >> 32 & 0xFFFFFFFF) *
	SSE<uint32>(B.lo & 0xFFFFFFFF, B.lo >> 32 & 0xFFFFFFFF);

	uint64 hi[2] =
	SSE<uint32>(A.hi & 0xFFFFFFFF, A.hi >> 32 & 0xFFFFFFFF) *
	SSE<uint32>(B.hi & 0xFFFFFFFF, B.hi >> 32 & 0xFFFFFFFF);
# else
# endif
}
uint128 pyro::operator /(uint128 A, uint128 B){ }
uint128 pyro::operator %(uint128 A, uint128 B){ }
// signed
using pyro::int128;
int128 pyro::operator &(int128 A, int128 B){ return int128(A.lo & B.lo, A.hi & B.hi); }
int128 pyro::operator ^(int128 A, int128 B){ return int128(A.lo ^ B.lo, A.hi ^ B.hi); }
int128 pyro::operator |(int128 A, int128 B){ return int128(A.lo | B.lo, A.hi | B.hi); }
int128 pyro::operator +(int128 A, int128 B){ }
int128 pyro::operator -(int128 A, int128 B){ }
int128 pyro::operator *(int128 A, int128 B){ }
int128 pyro::operator /(int128 A, int128 B){ }
int128 pyro::operator %(int128 A, int128 B){ }
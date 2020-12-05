# include "align.h"

// :: unsigned 128
uint128_t::uint128_t(bool     lo): uint128_t(lo, 0){ }
uint128_t::uint128_t(uint8_t  lo): uint128_t(lo, 0){ }
uint128_t::uint128_t(uint16_t lo): uint128_t(lo, 0){ }
uint128_t::uint128_t(uint32_t lo): uint128_t(lo, 0){ }
uint128_t::uint128_t(uint64_t lo): uint128_t(lo, 0){ }
uint128_t::uint128_t(int128_t  a): uint128_t(a.lo, a.hi){ }
uint128_t::uint128_t(int64_t  lo): uint128_t(lo, lo<0?-1:0){ }
uint128_t::uint128_t(int32_t  lo): uint128_t(lo, lo<0?-1:0){ }
uint128_t::uint128_t(int16_t  lo): uint128_t(lo, lo<0?-1:0){ }
uint128_t::uint128_t(int8_t   lo): uint128_t(lo, lo<0?-1:0){ }
uint128_t uint128_t::operator + (void){ return*this; }
uint128_t uint128_t::operator ++ (int){ return*this+1; }
uint128_t uint128_t::operator - (void){ return 1+~*this; }
uint128_t uint128_t::operator -- (int){ return*this-1; }
uint128_t uint128_t::operator ~ (void){ }
bool uint128_t::operator ! (void){ return*this!=0; }
// :: unsigned 256
uint256_t::uint256_t(bool     lo): uint256_t(lo, 0){ }
uint256_t::uint256_t(uint8_t  lo): uint256_t(lo, 0){ }
uint256_t::uint256_t(uint16_t lo): uint256_t(lo, 0){ }
uint256_t::uint256_t(uint32_t lo): uint256_t(lo, 0){ }
uint256_t::uint256_t(uint64_t lo): uint256_t(lo, 0){ }
uint256_t::uint256_t(uint128_t lo): uint256_t(lo, 0){ }
uint256_t::uint256_t(int256_t  a): uint256_t(a.lo, a.hi){ }
uint256_t::uint256_t(int128_t  lo): uint256_t(lo, lo<0?-1:0){ }
uint256_t::uint256_t(int64_t  lo): uint256_t(lo, lo<0?-1:0){ }
uint256_t::uint256_t(int32_t  lo): uint256_t(lo, lo<0?-1:0){ }
uint256_t::uint256_t(int16_t  lo): uint256_t(lo, lo<0?-1:0){ }
uint256_t::uint256_t(int8_t   lo): uint256_t(lo, lo<0?-1:0){ }
uint256_t uint256_t::operator + (void){ return*this; }
uint256_t uint256_t::operator ++ (int){ return*this+1; }
uint256_t uint256_t::operator - (void){ return 1+~*this; }
uint256_t uint256_t::operator -- (int){ return*this-1; }
uint256_t uint256_t::operator ~ (void){ }
bool uint256_t::operator ! (void){ return*this!=0; }
// :: signed 128
int128_t::int128_t(bool one): lo(one?1:0), hi(0){ }
int128_t::int128_t(int8_t a): lo(a), hi(a<0?-1:0){ }
int128_t::int128_t(int16_t a): lo(a), hi(a<0?-1:0){ }
int128_t::int128_t(int32_t a): lo(a), hi(a<0?-1:0){ }
int128_t::int128_t(int64_t a): lo(a), hi(a<0?-1:0){ }
int128_t::int128_t(uint128_t a): lo(a.lo), hi(a.hi){ }
int128_t::int128_t(uint64_t a): lo(a), hi(0){ }
int128_t::int128_t(uint32_t a): lo(a), hi(0){ }
int128_t::int128_t(uint16_t a): lo(a), hi(0){ }
int128_t::int128_t(uint8_t a): lo(a), hi(0){ }
int128_t int128_t::operator + (void){ return*this; }
int128_t int128_t::operator ++ (int){ return*this+1; }
int128_t int128_t::operator - (void){ return 1+~*this; }
int128_t int128_t::operator -- (int){ return*this-1; }
int128_t int128_t::operator ~ (void){ }
bool int128_t::operator ! (void){ return*this!=0; }
// :: signed 256
int256_t::int256_t(bool one): lo(one?1:0), hi(0){ }
int256_t::int256_t(int8_t a): lo(a), hi(a<0?-1:0){ }
int256_t::int256_t(int16_t a): lo(a), hi(a<0?-1:0){ }
int256_t::int256_t(int32_t a): lo(a), hi(a<0?-1:0){ }
int256_t::int256_t(int64_t a): lo(a), hi(a<0?-1:0){ }
int256_t::int256_t(int128_t a): lo(a), hi(a<0?-1:0){ }
int256_t::int256_t(uint256_t a): lo(a.lo), hi(a.hi){ }
int256_t::int256_t(uint128_t a): lo(a), hi(0){ }
int256_t::int256_t(uint64_t a): lo(a), hi(0){ }
int256_t::int256_t(uint32_t a): lo(a), hi(0){ }
int256_t::int256_t(uint16_t a): lo(a), hi(0){ }
int256_t::int256_t(uint8_t a): lo(a), hi(0){ }
int256_t int256_t::operator + (void){ return*this; }
int256_t int256_t::operator ++ (int){ return*this+1; }
int256_t int256_t::operator - (void){ return 1+~*this; }
int256_t int256_t::operator -- (int){ return*this-1; }
int256_t int256_t::operator ~ (void){ }
bool int256_t::operator ! (void){ return*this!=0; }
// extern
 // add
 uint128_t operator + (uint128_t u, uint128_t v)
 {
	reinterpret_cast<uint64_t*>(&u)[0] + reinterpret_cast<uint64_t*>(&v)[0];
	reinterpret_cast<uint64_t*>(&u)[1] + reinterpret_cast<uint64_t*>(&v)[1];
 }
 uint256_t operator + (uint256_t u, uint256_t v)
 {
	reinterpret_cast<uint64_t*>(&u)[0] + reinterpret_cast<uint64_t*>(&v)[0];
	reinterpret_cast<uint64_t*>(&u)[1] + reinterpret_cast<uint64_t*>(&v)[1];
 }
 int128_t operator + (int128_t u, int128_t v)
 {
	reinterpret_cast<uint64_t*>(&u)[0] + reinterpret_cast<uint64_t*>(&v)[0];
	reinterpret_cast<uint64_t*>(&u)[1] + reinterpret_cast<uint64_t*>(&v)[1];
 }
 int256_t operator + (int256_t u, int256_t v)
 {
	reinterpret_cast<uint64_t*>(&u)[0] + reinterpret_cast<uint64_t*>(&v)[0];
	reinterpret_cast<uint64_t*>(&u)[1] + reinterpret_cast<uint64_t*>(&v)[1];
 }
 // mul
 uint128_t operator * (uint128_t u, uint128_t v)
 {
	uint128_t a(0);
	a = a + (uint64_t)reinterpret_cast<uint32_t*>(&u)[3] * reinterpret_cast<uint32_t*>(&v)[3] << 32;
	a = a + (uint64_t)reinterpret_cast<uint32_t*>(&u)[2] * reinterpret_cast<uint32_t*>(&v)[2] << 32;
	a = a + (uint64_t)reinterpret_cast<uint32_t*>(&u)[1] * reinterpret_cast<uint32_t*>(&v)[1] << 32;
	return  (uint64_t)reinterpret_cast<uint32_t*>(&u)[0] * reinterpret_cast<uint32_t*>(&v)[0];
 }
 uint256_t operator * (uint256_t u, uint256_t v)
 {
	uint256_t a(0);
	a = a + (uint128_t)reinterpret_cast<uint64_t*>(&u)[3] * reinterpret_cast<uint64_t*>(&v)[3] << 32;
	a = a + (uint128_t)reinterpret_cast<uint64_t*>(&u)[2] * reinterpret_cast<uint64_t*>(&v)[2] << 32;
	a = a + (uint128_t)reinterpret_cast<uint64_t*>(&u)[1] * reinterpret_cast<uint64_t*>(&v)[1] << 32;
	return  (uint128_t)reinterpret_cast<uint64_t*>(&u)[0] * reinterpret_cast<uint64_t*>(&v)[0];
 }
 int128_t operator * (int128_t, int128_t){ }
 int256_t operator * (int256_t, int256_t){ }
 // div
 uint128_t operator / (uint128_t, uint128_t){ }
 uint256_t operator / (uint256_t, uint256_t){ }
 int128_t operator / (int128_t, int128_t){ }
 int256_t operator / (int256_t, int256_t){ }
 // mod
 uint128_t operator % (uint128_t, uint128_t){ }
 uint256_t operator % (uint256_t, uint256_t){ }
 int128_t operator % (int128_t, int128_t){ }
 int256_t operator % (int256_t, int256_t){ }
 // cmp
 bool operator != (uint128_t, uint128_t){ }
 bool operator != (uint256_t, uint256_t){ }
 bool operator != (int128_t, int128_t){ }
 bool operator != (int256_t, int256_t){ }
 // <=>
 bool operator < (uint128_t u, uint128_t v)
 {
	return	reinterpret_cast<uint64_t*>(&u)[1] <= reinterpret_cast<uint64_t*>(&v)[1]
	&&	reinterpret_cast<uint64_t*>(&u)[0] <  reinterpret_cast<uint64_t*>(&v)[0];
 }
 bool operator > (uint128_t u, uint128_t v)
 {
	return	reinterpret_cast<uint64_t*>(&u)[1] >= reinterpret_cast<uint64_t*>(&v)[1]
	&&	reinterpret_cast<uint64_t*>(&u)[0] >  reinterpret_cast<uint64_t*>(&v)[0];
 }
 bool operator < (uint256_t, uint256_t){ }
 bool operator > (uint256_t, uint256_t){ }
 bool operator < (int128_t, int128_t){ }
 bool operator > (int128_t, int128_t){ }
 bool operator < (int256_t, int256_t){ }
 bool operator > (int256_t, int256_t){ }
 // shift
 uint128_t operator << (uint128_t, uint128_t){ }
 uint128_t operator >> (uint128_t, uint128_t){ }
 uint256_t operator << (uint256_t, uint256_t){ }
 uint256_t operator >> (uint256_t, uint256_t){ }
 int128_t operator << (int128_t, int128_t){ }
 int128_t operator >> (int128_t, int128_t){ }
 int256_t operator << (int256_t, int256_t){ }
 int256_t operator >> (int256_t, int256_t){ }
 // and
 uint128_t operator & (uint128_t u, uint128_t v)
 {
	reinterpret_cast<uint64_t*>(&u)[0] = reinterpret_cast<uint64_t*>(&u)[0] & reinterpret_cast<uint64_t*>(&v)[0];
	reinterpret_cast<uint64_t*>(&u)[1] = reinterpret_cast<uint64_t*>(&u)[1] & reinterpret_cast<uint64_t*>(&v)[1];
	return u;
 }
 uint256_t operator & (uint256_t u, uint256_t v)
 {
	reinterpret_cast<uint128_t*>(&u)[0] = reinterpret_cast<uint128_t*>(&u)[0] & reinterpret_cast<uint128_t*>(&v)[0];
	reinterpret_cast<uint128_t*>(&u)[1] = reinterpret_cast<uint128_t*>(&u)[1] & reinterpret_cast<uint128_t*>(&v)[1];
	return u;
 }
 int128_t operator & (int128_t, int128_t){ }
 int256_t operator & (int256_t, int256_t){ }
 // xor
 uint128_t operator ^ (uint128_t, uint128_t){ }
 uint256_t operator ^ (uint256_t, uint256_t){ }
 int128_t operator ^ (int128_t, int128_t){ }
 int256_t operator ^ (int256_t, int256_t){ }
 // or
 uint128_t operator | (uint128_t, uint128_t){ }
 uint256_t operator | (uint256_t, uint256_t){ }
 int128_t operator | (int128_t, int128_t){ }
 int256_t operator | (int256_t, int256_t){ }
/*
///////////////////////////////////////////////////////////////////////
int128_t int128_t::operator << (unsigned){ }
int128_t int128_t::operator >> (unsigned){ }
bool int128_t::operator ! (void){ }
int128_t int128_t::operator ~ (void){ }
int128_t int128_t::operator + (void){ }
int128_t int128_t::operator - (void){ }
// add
extern int128_t operator + (int128_t, int128_t){ }
// sub
extern int128_t operator - (int128_t, int128_t){ }
// imul
extern int128_t operator * (int128_t, int128_t){ }
// idiv
extern int128_t operator / (int128_t, int128_t){ }
// imod
extern int128_t operator % (int128_t, int128_t){ }
// and
extern int128_t operator & (int128_t, int128_t){ }
// xor
extern int128_t operator ^ (int128_t, int128_t){ }
// or
extern int128_t operator | (int128_t, int128_t){ }
/////////////////////////////////////////////////////////////////////
uint128_t uint128_t::operator << (unsigned){ }
uint128_t uint128_t::operator >> (unsigned){ }
bool uint128_t::operator ! (void){ }
uint128_t uint128_t::operator ~ (void){ }
uint128_t uint128_t::operator + (void){ }
uint128_t uint128_t::operator - (void){ }
// add
extern uint128_t operator + (uint128_t, uint128_t){ }
// sub
extern uint128_t operator - (uint128_t, uint128_t){ }
// imul
extern uint128_t operator * (uint128_t, uint128_t){ }
// idiv
extern uint128_t operator / (uint128_t, uint128_t){ }
// imod
extern uint128_t operator % (uint128_t, uint128_t){ }
// and
extern uint128_t operator & (uint128_t, uint128_t){ }
// xor
extern uint128_t operator ^ (uint128_t, uint128_t){ }
// or
extern uint128_t operator | (uint128_t, uint128_t){ }
/////////////////////////////////////////////////////////////////////*/
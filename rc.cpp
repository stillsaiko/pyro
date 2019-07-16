# include "rc.h"
# include <cstdio>
# include <cassert>
# include <cstdlib>
// windows
# ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# endif
RC::~RC(void){
	// clean up
	if( release&&rawdata )
		release( rawdata );
}
RC::RC(void){ }
RC::RC(const char * lpName){
# ifdef _WIN32
	if(HMODULE hModule = GetModuleHandle(NULL))
	if(HRSRC hResInfo = FindResource(hModule, lpName, RT_RCDATA)){
		HGLOBAL hResData ;
		assert( hResData = LoadResource(hModule, hResInfo) );
		assert( const_cast<char*&>(rawdata) = (char*)LockResource(hResData) );
		assert( const_cast<size_t&>(n) = SizeofResource(hModule, hResInfo) );
		return ;
	}
# endif
	if( FILE * f = fopen(lpName, "rb") ){
		assert( fseek(f, 0, SEEK_END) == NO_ERROR );
		const_cast<size_t&>(n) = ftell(f);
		const_cast<char*&>(rawdata) = (char*)malloc(n);
		const_cast<void(*&)(void*)>(release) = free ;
		assert( fseek(f, 0, SEEK_SET) == NO_ERROR );
		assert( fread(rawdata, sizeof(char), n, f) == n );
		assert( fclose(f) == NO_ERROR );
		printf("warning: RC::ctor %s (from file)\n", lpName);
		return ;
	}
	printf("error: RC::ctor %s (not exist)\n", lpName);
}
RC::RC(const void * data, size_t size){
	assert(data);
	const_cast<size_t&>(n) = size ? size : strlen((const char*)data);
	const_cast<char*&>(rawdata) = (char*)const_cast<void*&>(data);
	const_cast<void(*&)(void*)>(release) = nullptr ;
}
RC::RC(void * data, size_t size, void(*__free)(void*)){
	assert(data);
	assert(size);
	const_cast<size_t&>(n) = size ;
	const_cast<char*&>(rawdata) = (char*)data ;
	const_cast<void(*&)(void*)>(release) = __free ;
}
RC& RC::operator = (RC&& x)noexcept {
	// clean up
	if( release&&rawdata )
		release( rawdata );
	// ...
	const_cast<size_t&>(n) = x.n,
	const_cast<size_t&>(x.n) = 0u,
	const_cast<void(*&)(void*)>(release) = x.release,
	const_cast<void(*&)(void*)>(x.release) = nullptr,
	const_cast<char*&>(rawdata) = x.rawdata,
	const_cast<char*&>(x.rawdata) = nullptr ;
	return * this ;
}
// const
const char & RC ::
operator[ ](size_t index)const {
	return rawdata[index];
}
RC :: operator bool(void)const {
	return rawdata ;
}

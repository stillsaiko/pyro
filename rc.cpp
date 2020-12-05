# include "rc.h"
# include "error.h"
# include <cstdio> // fopen, fseek, fread, fclose
# include <cstdio> // printf
# include <cstdlib> // malloc, free
# ifdef _WIN32 // windows
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
// GetModuleHandleA
// FindResource, LoadResource
// LockResource, SizeofResource
# endif
RC::~RC(void)noexcept
{
	if(!ASSERT(this)) return;
	if(data && free)
		free(data),
		memset(this, 0, sizeof(RC));
}
RC::RC(void)noexcept: free(nullptr)
{ }
RC::RC(const char *lpName): free(nullptr)
{
	if(!ASSERT(this)) return;
# ifdef _WIN32 // windows
	if(HMODULE hModule  = GetModuleHandleA(NULL)                    )
	if(HRSRC   hResInfo = FindResourceA(hModule, lpName, RT_RCDATA) )
	if(HGLOBAL hResData = LoadResource(hModule, hResInfo)           )
	if(const_cast<void *&>(data) = (void*)LockResource(hResData)    )
	if(const_cast<size_t&>(size) = SizeofResource(hModule, hResInfo))
		return;
# endif
	if(FILE *file = fopen(lpName, "rb"))
	{
		ASSERT(!fseek(file, 0, SEEK_END));
		const_cast<size_t&>(size) = ftell(file);
		const_cast<void *&>(data) = malloc(size);
		const_cast<void(*&)(void *)>(free) = ::free;
		ASSERT(!fseek(file, 0, SEEK_SET));
		ASSERT(fread(data, sizeof(char), size, file) == size);
		ASSERT(!fclose(file));
//		printf("warning: RC::ctor %s (from file)\n", lpName); // #@?!
		return;
	}
//	printf("error: RC::ctor %s (not exist)\n", lpName);
	ERROR(lpName);
}
RC::RC(void(*q)(void*), const void *p, size_t n): free(p ? q : nullptr)
{
	if(!ASSERT(this)) return;
	const_cast<void *&>(data) = (void *)p;
	const_cast<size_t&>(size) = p ? n : 0;
	if(data && size == SIZE_MAX) // c_str
	if(ASSERT(data != (void *) 0xFFFFFFFF))
	const_cast<size_t&>(size) = strlen(static_cast<char *>(data));
}
RC::RC(RC&& ref)noexcept: free(nullptr)
{
	if(!ASSERT(this)) return;
	memcpy(this, &ref, sizeof(RC));
	memset(&ref,    0, sizeof(RC));
}
void RC::operator = (RC&& ref)noexcept
{
	if(!ASSERT(this)) return;
	this->~ RC( ); // release
	memcpy(this, &ref, sizeof(RC));
	memset(&ref,    0, sizeof(RC));
}
const char & RC::operator[ ](size_t i)const
{
	return static_cast<const char *>(data)[i];
}
// NEW
/*# include <cassert>
const void *RC::operator + (size_t offs)const
{
	assert(offs < size && data);
	return data + offs;
}*/
RC::operator const void *(void)const
{
	return ASSERT(this) ? data : nullptr;
}
// ...
const char * RC::begin(void)const
{
	if(!ASSERT(this)) return nullptr;
	return static_cast<const char *>(data);
}
const char * RC::end(void)const
{
	if(!ASSERT(this)) return nullptr;
	return static_cast<const char *>(data) + size;
}
// NEW
# ifdef _WIN32
/*HICON ICO(const char *lpIconName)
{
	return LoadIconA(GetModuleHandleA(NULL), lpIconName);
}
HBITMAP BMP(const char *lpBitmapName)
{
	return LoadBitmapA(GetModuleHandleA(NULL), lpBitmapName);
}*/
# endif
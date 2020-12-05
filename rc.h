# pragma once
# ifdef __cplusplus
# include <cstdint>
struct RC // file or resource
{
	void(* const free)(void *);
	void * const data = nullptr;
	size_t const size = 0;
	~
	RC(void)noexcept;
	RC(void)noexcept; // default
	RC(const char *file); // c_str
	RC(void(*)(void *), const void *, size_t=SIZE_MAX);
	RC(RC &&)noexcept; // move semantics
	void		operator = (RC &&)noexcept;
//	const void *	operator + (size_t)const; // NEW
	const char &	operator[ ](size_t)const;
			operator const void *(void)const; // NEW
	// ...
	const char * begin(void)const;
	const char * end  (void)const;
};
# endif
// resource compiler
# ifdef RC_INVOKED
# define RC(file)  file RCDATA #file
# define ICO(file) file ICON   #file
# define BMP(file) file BITMAP #file
// define FNT(file) file FONT #file
# endif
// NEW
# ifdef _WIN32
# define WIN32_MEAN_AND_LEAN
# include <windows.h>
//extern HICON ICO(const char *lpIconName);
//extern HBITMAP BMP(const char *lpBitmapName);
# endif

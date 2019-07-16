# pragma once
# ifdef RC_INVOKED
# define RC(file) file RCDATA #file
# define ICO(file) file ICON #file
# define BMP(file) file BITMAP #file
# else
# include <cstdlib>
struct RC { // file or resource
	~
	RC(void);
	RC(void);
	RC(const char * file);
	RC(const void *, size_t n);
	RC(void *, size_t n, void(*free)(void*));
	RC& operator = (RC&&)noexcept ;
// const
	const char &
	operator[ ](size_t)const ;
	operator bool(void)const ;
				size_t const n = 0u ;
private :
	void(* const release)(void *) = nullptr;
	char * const rawdata = nullptr ;
};
# endif

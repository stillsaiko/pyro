# pragma once
struct EXT {
	~
	EXT(void);
	EXT(char const * file, const char * ext);
 // const
	operator const char * (void)const ;
	const char & operator[ ](size_t)const ;
private:
	char * c_str = nullptr ;
};
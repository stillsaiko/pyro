# pragma once
# include <cstddef> // size_t (MinGW)
// {
//	EXT filename("file_1412", "txt");
//	fopen(filename, "rb");
//	...
// }
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

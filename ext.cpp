# include "ext.h"
# include <cstdlib>
# include <cassert>
EXT::~EXT(void){
	assert(c_str);
	free(c_str);
}
# include <cstring> // strlen
# include <cstdio> // printf
EXT::EXT(char const * file, char const * ext){
	assert(file);
	assert(ext);
	if(*ext == '.'){
		printf("warning: EXT(\"%s\", \"%s\")\n", file, ext);
		printf("      -> EXT(\"%s\", \"%s\")\n", file, ext+1);
		++ ext;
	}
	c_str = (char *)malloc(strlen(file) + strlen(ext) + 1UL);
	strcpy(c_str, file);
	strcat(c_str, ".");
	strcat(c_str, ext);
}
// const
EXT::operator const char * (void)const {
	return c_str ;
}
const char & EXT::operator[ ](size_t index)const {
	return c_str[index];
}

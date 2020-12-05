# include "error.h"
# include <cstring> // strrchr
# include <cstdio> // printf
# include <b40.h>
# undef ERROR
bool ERROR(const char *FILE, int LINE, char const *FUNCTION, const char *ARGS)
{
	if(const char *rchr = strrchr(FILE, '\\')) FILE = rchr + 1;
	if(const char *rchr = strrchr(FILE, '/')) FILE = rchr + 1;
	if(const char *rchr = strrchr(FUNCTION, ':')) FUNCTION = rchr + 1;
	unsigned long long err = B40LL(FILE) ^ LINE ^ B40LL(FUNCTION) ^ B40LL(ARGS);
	constexpr size_t SIZE = 32;
	static unsigned long long ERR[SIZE] {0};
	size_t index = SIZE>>1;
	for(size_t stride=SIZE>>2; stride; stride>>=1)
		if(err < ERR[index]) index += stride;
	else	if(err > ERR[index]) index -= stride;
	else return false;
	if(index+1 < SIZE)
	memmove(&ERR[index+1], &ERR[index], (SIZE-index-1)*sizeof ERR[0]);
	ERR[index] = err;
	printf("ERROR %s:%i %s %s\n", FILE, LINE, FUNCTION, ARGS);
	return false;
}
# undef WARNING
int WARNING(const char *FUNCTION, const char *FORMAT, ...)
{
	if(const char *rchr = strrchr(FUNCTION, ':')) FUNCTION = rchr + 1;
	printf("WARNING: %s ", FUNCTION);
	va_list ap;
	va_start(ap, FORMAT);
	int printf = vprintf(FORMAT, ap);
	va_end(ap);
	puts("\n");
	return printf;
}
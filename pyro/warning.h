# pragma once
# include <cstring>
# include <cstdarg>
# include <cstdio>
namespace pyro
{
//	extern void warning(const char *func, const char *fmt, ...);
	template<int N, class...T>
	void warning(const char *func, const char fmt[N], T...args)
	{
		printf("warning: %s (", func);
		printf(fmt, args...);
		printf(")\n");
	}
}
// include "warning.h"
# include <cstring>
# include <cstdarg>
# include <cstdio>
/*templatevoid pyro::warning(const char *func, const char *fmt[], ...)
{
	char buf[sizeof("warning: ") + strlen(fmt)];
	va_list va;
	va_start(va, fmt);
	vprintf(strcat(buf, fmt), va);
	va_end(va);
}*/
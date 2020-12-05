# pragma once
# include "wnd.h"

# ifdef ERROR // wingdi.h
# undef ERROR
# endif

extern bool ERROR(const char *FILE = "C:/USERS/SAIKO/GITHUB/PYRO/ERROR.H",
 int LINE = 0, const char *FUNCTION = "ERROR", const char *ARGS = "#@?!");
# define ERROR(...) ERROR(__FILE__, __LINE__, __FUNCTION__, (__VA_ARGS__))
# ifndef NDEBUG
# define ASSERT(...) (!(__VA_ARGS__) ? ERROR(#__VA_ARGS__) : true)
# else
# define ASSERT(...) !!(__VA_ARGS__)
# endif

extern int WARNING(const char *FUNCTION, const char *FORMAT = "%%", ...);
# define WARNING(...) WARNING(__FUNCTION__, __VA_ARGS__)
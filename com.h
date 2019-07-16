# pragma once
# define WIN32_MEAN_AND_LEAN
# include <windows.h>
struct COM {
	~
	COM(void);
	COM(void);
	COM(const char *);
	COM& operator = (COM&&)noexcept ;
	operator bool(void);
private:
	STARTUPINFO SI {0};
	PROCESS_INFORMATION PI {0};
};

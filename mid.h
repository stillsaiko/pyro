# pragma once
# include "rc.h"
struct MID {
	~
	MID(void)noexcept ;
	MID(void);
	MID(RC&&);
	void operator = (MID&&)noexcept ;
};
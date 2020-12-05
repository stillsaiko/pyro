# pragma once
// config file
# include "rc.h"
# include "lex.h"
# include "b40.h"
// if( INI config = INI(RC(".ini")) )
// for(INI::S & section : config)
//  switch(section)
//	case B40LL("user_section"):
//		for(INI::K & key : section)
//		 switch(key)
//		 case B40LL("property_int"):
//			if( key.equals("undefined") ) ...
//			else key.as_long( ) ...
//		 case B40LL("property_str"):
//			if( key.equals("sample text") ) ...
//			else (const char *) key ...
//			key.trim(" \t\r") -> const char *
struct INI {
	enum { SECTION, COMMENT, KEY };
	struct K :
	public B40LL,
	public LEX::A {
		K(B40LL&&, const LEX::A &);
	};
	struct S : public B40LL {
		~
		S(void)noexcept ;
		S(B40LL&&);
		void insert(intptr_t, B40LL&&, const LEX::A &);
		K * operator[ ](unsigned long long);
		K * begin(void);
		K * end(void);
	private:
		K * L = nullptr ;
		size_t Ln = 0UL ;
	};
	S * L = nullptr ;
	size_t Ln = 0UL ;
	~
	INI(void)noexcept ;
	INI(void);
	INI(RC&&);
	INI(INI&&)noexcept ;
	void operator = (INI&&)noexcept ; // move
	S & operator[ ](unsigned long long K); // ambiguous first section
	S * begin(void);
	S * end(void);
	inline operator bool(void)const { return L && Ln; }
};

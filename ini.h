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
	class S : public B40LL {
		K * L = nullptr ;
		size_t Ln = 0UL ;
	public:
		S(B40LL&&);
		void insert(intptr_t, B40LL&&, const LEX::A &);
		K * operator[ ](unsigned long long);
		K * begin(void);
		K * end(void);
	};
	S * L = nullptr ;
	size_t Ln = 0UL ;
	S * from = nullptr ;
	S * to = nullptr ;
	S & operator[ ](unsigned long long K);
	S * begin(void);
	S * end(void);
	~
	INI(void);
	INI(void);
	INI(RC&&);
	inline operator bool(void)const { return L && Ln; }
};

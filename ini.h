# pragma once

# include "rc.h"
# include "lex.h"
# include "b40.h"
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
/*	B40<unsigned long long> val ;
	struct X {
		bool is_section ;
	};
	LEX::X * begin(void);
	LEX::X * end(void);*/
};

constexpr unsigned char A2B40[128] {
0,	0,	0,	0,	0,	0,	0,	0,	// NUL SOH STX ETX EOT ENQ ACK BEL
0,	0,	0,	0,	0,	0,	0,	0,	//	BS	HT	LF	VT	FF	CR	SO	SI
0,	0,	0,	0,	0,	0,	0,	0,	// DLE DC1 DC2 DC3 DC4 NAK SYN ETB
0,	0,	0,	0,	0,	0,	0,	0,	// CAN	EM SUB ESC	FS	GS	RS	US
0,	39, 39, 39, 39, 39, 39, 39,	//	SP	!	"	#	$	%	&	'
39, 39, 39, 39, 39, 39, 38, 39,	//	(	)	*	+	,	-	.	/
1,	2,	3,	4,	5,	6,	7,	8,	//	0	1	2	3	4	5	6	7
9,	10, 39, 39, 39, 39, 39, 39, //	8	9	:	;	<	=	>	?
39, 11, 12, 13, 14, 15, 16, 17,	//	@	A	B	C	D	E	F	G
18, 19, 20, 21, 22, 23, 24, 25,	//	H	I	J	K	L	M	N	O
26, 27, 28, 29, 30, 31, 32, 33,	//	P	Q	R	S	T	U	V	W
34, 35, 36, 39, 39, 39, 37, 39,	//	X	Y	Z	[	\	]	^	_
39, 11, 12, 13, 14, 15, 16, 17,	//	`	a	b	c	d	e	f	g
18, 19, 20, 21, 22, 23, 24, 25,	//	h	i	j	k	l	m	n	o
26, 27, 28, 29, 30, 31, 32, 33,	//	p	q	r	s	t	u	v	w
34, 35, 36, 39, 39, 39, 39, 0	//	x	y	z	{	|	}	~  DEL
};
constexpr char B402A[40]{
'\0', '0', '1', '2', '3',	//	0 ... 4
 '4', '5', '6', '7', '8',	//	5 ... 9
 '9', 'a', 'b', 'c', 'd',	// 10 ... 14
 'e', 'f', 'g', 'h', 'i',	// 15 ... 19
 'j', 'k', 'l', 'm', 'n',	// 20 ... 24
 'o', 'p', 'q', 'r', 's',	// 25 ... 29
 't', 'u', 'v', 'w', 'x',	// 30 ... 34
 'y', 'z', '_', '.', '?'	// 35 ... 39
};
# include <cstdint> // uint16_t uint32_t uint64_t
# include <cstdlib> // malloc
class B40 {
    uint16_t U ;
public:
    constexpr operator decltype(U)(void){ return U; }
    constexpr B40(void): U(0U) { }
    constexpr B40(decltype(U) U): U(U) { }
    constexpr B40(const char A[ ]): U( // 3U
		 A    ? 0x0001 * A2B40[ A[0] & 0x7F ] +
		(A[0] ? 0x0028 * A2B40[ A[1] & 0x7F ] +
		(A[1] ? 0x0640 * A2B40[ A[2] & 0x7F ] : 0) : 0) : 0
    ){ }
    constexpr char operator[ ](unsigned i){
        return
    	i<1U ? B402A[ U / 0x0001 - U / 0x0028 * 0x0028 ]:
    	i<2U ? B402A[ U / 0x0028 - U / 0x0640 * 0x0028 ]:
    	i<3U ? B402A[ U / 0x0640 ]: '\0'; // error
    }
	inline void c_str(char A[4U]){
		A[0U] = operator[ ](0U);
		A[1U] = operator[ ](1U);
		A[2U] = operator[ ](2U);
		A[3U] = '\0';
    }
};
struct B40L {
	uint32_t UL ;
public:
	constexpr operator decltype(UL)(void){ return UL; }
	constexpr B40L(void): UL(0UL) { }
	constexpr B40L(decltype(UL) U): UL(U) { }
	constexpr B40L(const char A[ ]): // 6U
		UL(	B40(A) / 0x0640
		?	B40(A) + ((decltype(UL)) B40(A+3U) << 16U)
		:	B40(A) + 0UL )
    { }
	constexpr char operator[ ](unsigned i){
		return i<6U ? ((B40*)&UL)[i/3U][i%3U]: '\0';
	}
	inline void c_str(char A[7U]){
		reinterpret_cast<B40*>(&UL)[0].c_str(A+0U);
		reinterpret_cast<B40*>(&UL)[1].c_str(A+3U);
	}
};
struct B40LL {
	uint64_t ULL ;
public:
	constexpr operator decltype(ULL)(void){ return ULL; }
	constexpr B40LL(void): ULL(0ULL) { }
	constexpr B40LL(decltype(ULL) U): ULL(U) { }
	constexpr B40LL(const char A[ ]): // 12U
		ULL( B40L(A) / 0x06400000
		?	 B40L(A) + ((decltype(ULL)) B40L(A+6U) << 32U)
		:	 B40L(A) + 0ULL )
    { }
	constexpr char operator[ ](unsigned i){
		return i<12U ? ((B40*)&ULL)[i/3U][i%3U]: '\0';
	}
	inline void c_str(char A[13U]){
		reinterpret_cast<B40L*>(&ULL)[0].c_str(A+0U);
		reinterpret_cast<B40L*>(&ULL)[1].c_str(A+6U);
	}
};
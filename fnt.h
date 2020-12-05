# pragma once
# include <rc.h>
# include <wnd.h>
/*template<class T> struct FNT; // *.fon
template<>*/ struct FNT/*<void>*/
{
	FNT(void);
	FNT(RC &&);
	void operator = (FNT &&)noexcept;
	const char * operator[ ](char);
private:
	RC rc;
};
/*template<class T> struct FNT : public FNT<void>
{
	PNG<T> operator[ ](char)
	{
		PNG<T>();
	}
};*/
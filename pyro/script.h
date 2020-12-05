# pragma once
# include <ini.h>
# include <pyro/codec.h>
namespace pyro
{
	struct script :
	public codec<size_t>
	{
		script(INI&&);
		size_t encode(size_t)override;
		size_t decode(size_t)override;
		INI::K& operator[ ](size_t);
		size_t length(void);
	private:
		INI ini;
	};
	
}
// script.cpp
# include "script.h"
# include <cstdio> // printf
# include <memory> // std::move
namespace pyro
{
	script::script(INI&& a): ini(std::move(a))
	{ }
	size_t script::encode(size_t index)
	{
		INI::K *ptr = &operator[ ](index);
		char key[13] {0};
		ptr->c_str(key);
		printf("encode %s = %s\n", key, ptr->trim( ));
	}
	size_t script::decode(size_t index)
	{
		INI::K *ptr = &operator[ ](index);
		char key[13] {0};
		ptr->c_str(key);
		printf("decode %s = %s\n", key, ptr->trim( ));
	}
	INI::K& script::operator[ ](size_t index)
	{
		for(INI::S & section : ini)
		{
			size_t length = section.end( ) - section.begin( );
			if(index < length)break; // ...
			else index -= length; // +1
		}
	}
	size_t script::length( )
	{
		size_t length = 0;
		for(INI::S & section : ini)
		{
			length += section.end( ) - section.begin( ) + 1;
		}
		return length;
	}
}
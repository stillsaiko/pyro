# include "ascii.h"
# include <pyro/unique.h>
# include <b40.h>
# include <png.h>
// private static
size_t pyro::ascii::find(char key)
{
	if(key < '!')return 0;
	if(key > '~')return 0;
	return map[key - '!'];
}
bool pyro::ascii::is_zero(size_t i)
{
	char * column = unique<PNG<char>>[i];
	for(size_t j=0; j<unique<PNG<char>>.X; ++j)
	{
		if(column[j])return false;
	}
	return true;
};
uint16_t pyro::ascii::map[94] {0};
// ...
pyro::ascii::ascii(char key)
{
	if(unique<PNG<char>>.X * unique<PNG<char>>.Y * unique<PNG<char>>.Z == 0)
	{
		unique<PNG<char>> = PNG<char>(RC("ascii.png"));
		size_t index = 0;
		assert(is_zero(0));
		size_t offset = 0 + 1;
		for(size_t i=1; i<unique<PNG<char>>.Y; ++i)
		{
			assert(index < 94);
			if(is_zero(i))
			{
				map[index ++] = offset;
				offset = i + 1;
			}
		}
	}
	Y = unique<PNG<char>>.Y;
	offset = find(key) * Y;
	    X =	find(key) ?
		find(key) / Y - offset - 1 :
	  unique<PNG<char>>.X - offset / Y - 1;
}
char * pyro::ascii::begin(void)
{
	return unique<PNG<char>>[offset];
}
char * pyro::ascii::end(void)
{
	return unique<PNG<char>>[offset+Y*X];
}
char * pyro::ascii::operator[ ](size_t i)
{
	if(is_zero(i))return nullptr;
	return unique<PNG<char>>[i];
}
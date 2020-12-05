# pragma once
# include <cstdint>
namespace pyro
{
	template<bool vertical = false>
	class ascii
	{
		static size_t find(char);
		static bool is_zero(size_t);
		static uint16_t map[94];
		unsigned char X, Y;
		size_t offset;
	public:
		ascii(char);
		char * begin(void); // 1st column
		char * end(void);
		char * operator[ ](size_t); // column
	};
}

# pragma once
# if __has_include("config.h")
# include "config.h"
# else
# define PYRO_WORLD_SIZE_X 48
# define PYRO_WORLD_SIZE_Y 32
# endif
namespace pyro
{
	struct world { };
	enum {super, terrain, aqueous};
	template<auto = super> struct chunk
	{
		virtual void mechanics(int) = 0;
		virtual void draw(void) = 0;
	};
	template<>
	struct chunk<terrain> :
	public chunk<>
	{
		void mechanics(int)override;
		void draw(void)override;
	};
	template<>
	struct chunk<aqueous> :
	public chunk<>
	{
		void mechanics(int)override;
		void draw(void)override;
	};
}
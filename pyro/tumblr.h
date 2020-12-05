# pragma once
# include <glsl.h>
# include "shared.h"
# include <b40.h>
namespace pyro
{
	struct tumblr // height-/tile-map
	{
		struct tile
		{
			enum { flat, ramp, isom } type = flat;
			unsigned short height = 0;
			unsigned char texture = 0;
		} ** chunk_array = nullptr;
		tumblr(void)
		{
			{
				GLSL& tmp = shared<GLSL>[B40LL("tumblr")];
				if(!tmp) tmp = GLSL(RC("tumblr.vert"), RC("tumblr.frag"));
			}
		}
	};
}
# pragma once
# if __has_include("config.h")
# include "config.h"
# endif
# include <vao.h>
namespace pyro
{
	struct tile
	{
		enum : GLubyte { quad = 0, tris = 64, flip = 128 };
		struct vertex
		{
			GLubyte Z[3] = {0};
			GLubyte TexID = quad;
		};
		tile(GLubyte v1, GLubyte v2, GLubyte v3, GLubyte t){}
		vertex vertices[2];
	/*	enum MSLR { M, S, L, R }; // 2 bit
		unsigned char height [3]; // 24 bit
		unsigned char texture[2]; // 12 bit
		enum clamp { A, X, Y }; // 2 bit*/
	};
	template<size_t PX> class tilemap
	{
		tile * buffer = nullptr;
		size_t stride = 0U;
	//	size_t height = 0U;
	//	size_t width = 0U;
	public:
		template<size_t A> tilemap(tilemap<A>&& a)
		{
			buffer = a.buffer;
			         a.buffer = nullptr;
			stride = a.stride;
			         a.stride = 0U;
		}
		// make sure you include a GLSL header `project' within
		tile * operator[ ](size_t x)
		{
			return buffer + x * stride;
		}
	};
}
// A = vertex.a & 0b10000000 (B = !A)
// L = vertex.a & 0b01000000 (R = !L)
// --------------- upper neighbor known version ---------------
// lo: vec3( L, 1, H[0]), vec3(!L, 1, H[1]), vec3( L,  A, H[2])
// hi: vec3(!L, 1, H[0]), vec3( L, 0, H[1]), vec3(!L, !A, H[2])
// --------------- lower neighbor known version ---------------
// hi: vec3(!L, 0, H[0]), vec3( L, 0, H[1]), vec3(!L, !A, H[2])
// lo: vec3( L, 0, H[0]), vec3(!L, 1, H[1]), vec3( L,  A, H[2])


// 1 bit sign of slope + 7 bit height
// 4 bit slope         + 6 bit clamp
// 2x 6 bit texture    + 2 bit clamp-type

// MSLR   4 (2 bit)
// H8   128 (7 bit)
// clamp 128 (7 bit)
// clampT 2 (1 bit)
// slope 32 (5 bit)
// TEX_0 32 (5 bit)
// TEX_1 32 (5 bit)
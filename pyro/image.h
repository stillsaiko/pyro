# pragma once
# include <vao.h>
# include <glsl.h>
# include "queue.h"
# include <png.h>
namespace pyro
{
	struct RGBA
	{
		unsigned char R, G, B, A;
	};
	class image
	{
		struct vertex
		{
			unsigned short coord[2];
			unsigned char colour[3];
		};
		VBO vbo;
		VAO vao;
		GLsizei count = 0;
		GLSL glsl;
	public:
		image(const PNG<RGBA> & PNG)
		{
			queue<vertex> pixels;
			// buffer vertices
			for(size_t i=0; i<PNG.Y; ++i)
			for(size_t j=0; j<PNG.X; ++j)
			if( PNG[i][j].A )
			{
				*pixels.push(1) = vertex {j, i, PNG[i][j].R, PNG[i][j].G, PNG[i][j].B};
			}
			// OpenGL vertices
			vbo = VBO(pixels.pop(0), pixels.size);
			vao = VAO({VA(vertex, coord), VA(vertex, colour)}, vbo);
			count = pixels.size;
			// OpenGL shader program
			glsl = GLSL(RC("image.vert"), RC("image.geom"), RC("image.frag"));
		}
		void render(void)
		{
			glBindVertexArray(vao);
			glUseProgram(glsl);
			glDrawArrays(GL_ARRAY_BUFFER, vao, count);
			glUseProgram(0);
			glBindVertexArray(0);
		}
	};
}
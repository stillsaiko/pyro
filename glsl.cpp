# include "glsl.h"
# include "error.h"
# include <cstring>
# include "wnd.h"
# include "ini.h"
/*const char * __GLSLversion(void){
	static char core_version[ ] = "# version \a\a0 core\r\n";
	if( core_version[10] != '\a' ) // maj
	if( core_version[11] != '\a' ) // min
		return core_version ;
	// ...
}
RC& __GLSLinclude(void){
	static RC header_include ;
}*/
GLuint GLSL::__GLSLcompile(GLenum T, RC&source){
	if( !source.size || !source )return 0u ;
	if(GLuint glCreateShader = ::glCreateShader(T); GL_ASSERT(glCreateShader))
	{
		GLint strlen = source.size; // strlen(source)
		size_t magic_offset = 0u;
		char core_version[ ] = "# version \a\a0 core\r\n";
# ifndef _MAX_PATH
# define _MAX_PATH 120
# endif // _MAX_PATH
//		char header_name[_MAX_PATH] = "config.h";//{0};
		{
		//	if(auto * a = __ini["include"])assert(sscanf(a, "%s", header_name));
		//	if(auto * a = __ini["version"])assert(sscanf(a, "%i", &maj)),min=maj/10%10,maj/=100;
			GLint params[1];
			// magic core version
			GL_ASSERT(glGetIntegerv(GL_MAJOR_VERSION, params)), core_version[10] = params[0] + '0';
			GL_ASSERT(glGetIntegerv(GL_MINOR_VERSION, params)), core_version[11] = params[0] + '0';
			// ...
			++ magic_offset ; // \r\n
		}
		const char * p = &source[0];
		GLint params[1] {0};
//		assert(strlen(header_name));
		{
			// magic code injection
//			RC header(header_name);
			RC header("config.h");
			if(header)
			{
				for(size_t i=0u; i<header.size; ++i)
					if(header[i] == '\n')
						++ magic_offset; // \r\n
				char * mem = static_cast<char *>(malloc(strlen = ::strlen(core_version) + header.size + source.size));
				# pragma warning(suppress: 6387)
				memcpy(mem, core_version, ::strlen(core_version));
				memcpy(mem+::strlen(core_version), header, header.size);
				memcpy(mem+::strlen(core_version)+header.size, source, source.size);
				GL_ASSERT(glShaderSource(glCreateShader, 1, &mem, &strlen));
				GL_ASSERT(glCompileShader(glCreateShader));
				GL_ASSERT(glGetShaderiv(glCreateShader, GL_COMPILE_STATUS, params));
				free(mem);
			} else {
				printf("-------- %s not found --------\n", "config.h"); // header_name
				//...
			}
		}
		//glShaderSource(shader, 1, &p, &GL);
		//glCompileShader(shader);
		//glGetShaderiv(shader, GL_COMPILE_STATUS, &GL);
		if(params[0])
		{
			// fine
			return glCreateShader;
		}
		else
		{
			GL_ASSERT(glGetShaderiv(glCreateShader, GL_INFO_LOG_LENGTH, params));
			char * ascii = static_cast<char *>(malloc(params[0]));
			GL_ASSERT(glGetShaderInfoLog(glCreateShader, params[0], params, ascii));
			{
				// magic line correction
				bool inner = false ;
				int line = 0;
				char * ptr = nullptr ;
				for(GLint k(0); k<params[0]; ++k)
				if( inner ){
					inner = ascii[k] >= '0' &&
							ascii[k] <= '9';
					if( inner ){
						line = 10*line + ascii[k]-'0';
						if(!ptr)
							ptr = ascii + k ;

					} else if( ptr ){
						if( ascii + k - ptr && ascii[k] == ':' ){
							memset(ptr, '\a', ascii + k - ptr);
							line -= magic_offset ;
							for(size_t i(0); i < ascii + k - ptr && line; ++i)
								ptr[ascii + k - ptr - 1 - i] = line % 10 + '0', line /= 10 ;
							//sprintf(ptr, "%*i", ascii + k - ptr, line),
							ascii[k] = ':';
						}
						line = 0;
						ptr = nullptr ;
					}
				} else {
					inner = ascii[k] == ':';
				}
			}
			printf("%*s", params[0], ascii);
			free(ascii);
			GL_ASSERT(glDeleteShader(glCreateShader));
		}
	}
	return 0u ;
}
GLuint GLSL::__GLSLlink(std::initializer_list<GLuint> il)
{
	if(GLuint glCreateProgram = ::glCreateProgram( ); GL_ASSERT(glCreateProgram) )
	{
		for(GLuint glCreateShader : il) if(glCreateShader)
		GL_ASSERT(glAttachShader(glCreateProgram, glCreateShader));
		GL_ASSERT(glLinkProgram(glCreateProgram));
		GLint GL = GL_TRUE;
		GL_ASSERT(glGetProgramiv(glCreateProgram, GL_LINK_STATUS, &GL));
		if(GL == GL_FALSE)
		{
			GL_ASSERT(glGetProgramiv(glCreateProgram, GL_INFO_LOG_LENGTH, &GL));
			char * ascii = static_cast<char *>(malloc(GL));
			GL_ASSERT(glGetProgramInfoLog(glCreateProgram, GL, &GL, ascii));
			printf("%*s", GL, ascii);
			free(ascii);
			GL_ASSERT(glDeleteProgram(glCreateProgram));
			return 0u ;
		}
		for(GLuint glCreateShader : il) if(glCreateShader)
		GL_ASSERT(glDetachShader(glCreateProgram, glCreateShader));
		return glCreateProgram;
	}
	return 0;
}
// helper above
GLSL::~GLSL(void)noexcept
{
	if(PROGRAM)
	if(ASSERT(wglGetCurrentContext( )))
		GL_ASSERT(glDeleteProgram(PROGRAM)),
		PROGRAM = 0;
	// shader cleanup ?
/*	for(int i(0); i<6; ++i)
		shader[i] =
		refref.shader[i],
		refref.shader[i] = 0u ;*/
	// ...
}
GLSL::GLSL(void)
{ }
GLSL::GLSL(RC&&comp)
{
	PROGRAM =
	__GLSLlink({
	__GLSLcompile(GL_COMPUTE_SHADER, comp) });
}
GLSL::GLSL(RC&&vert, RC&&frag)
{
	PROGRAM =
	__GLSLlink({
	__GLSLcompile(GL_VERTEX_SHADER, vert),
	__GLSLcompile(GL_FRAGMENT_SHADER, frag) });
}
GLSL::GLSL(RC&&vert, RC&&geom, RC&&frag)
{
	PROGRAM =
	__GLSLlink({
	__GLSLcompile(GL_VERTEX_SHADER, vert),
	__GLSLcompile(GL_GEOMETRY_SHADER, geom),
	__GLSLcompile(GL_FRAGMENT_SHADER, frag) });
}
GLSL::GLSL(RC&&vert, RC&&tesc, RC&&tese, RC&&frag)
{
	PROGRAM =
	__GLSLlink({
	__GLSLcompile(GL_VERTEX_SHADER, vert),
	__GLSLcompile(GL_TESS_CONTROL_SHADER, tesc),
	__GLSLcompile(GL_TESS_EVALUATION_SHADER, tese),
	__GLSLcompile(GL_FRAGMENT_SHADER, frag) });
}
GLSL::GLSL(RC&&vert, RC&&tesc, RC&&tese, RC&&geom, RC&&frag)
{
	PROGRAM =
	__GLSLlink({
	__GLSLcompile(GL_VERTEX_SHADER, vert),
	__GLSLcompile(GL_TESS_CONTROL_SHADER, tesc),
	__GLSLcompile(GL_TESS_EVALUATION_SHADER, tese),
	__GLSLcompile(GL_GEOMETRY_SHADER, geom),
	__GLSLcompile(GL_FRAGMENT_SHADER, frag) });
}
void GLSL::operator = (GLSL &&a)noexcept
{
	this->~GLSL( ); // dtor
	// ...
	PROGRAM = a.PROGRAM, a.PROGRAM = 0;
}
GLint GLSL::operator[ ](const char * uniform)
{
	GLint glGetUniformLocation(-1);
	if(ASSERT(PROGRAM))
		glGetUniformLocation = ::glGetUniformLocation(PROGRAM, uniform), GL_ASSERT(glGetUniformLocation);
	return glGetUniformLocation;
}
GLSL::operator GLuint(void)const
{
	return PROGRAM;
}

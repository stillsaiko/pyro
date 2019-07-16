# include "glsl.h"
# include <cassert>
# include <cstring>
# include <initializer_list>
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
GLuint __GLSLcompile(GLenum T, RC&source){
	if( !source.n || !source )return 0u ;
	if( GLuint shader = glCreateShader(T) ){
		GLint size = source.n ; // strlen(source)
		size_t magic_offset = 0u;
		char core_version[ ] = "# version \a\a0 core\r\n";
# ifndef _MAX_PATH
# define _MAX_PATH 120
# endif // _MAX_PATH
		char header_name[_MAX_PATH] = {0};
		{
			GLint maj, min ;
			glGetIntegerv(GL_MAJOR_VERSION, &maj);
			glGetIntegerv(GL_MINOR_VERSION, &min);
			// dynamic *.ini shizzle			
			INI __ini( RC("glsl.ini") );
		//	ini __ini( RC("glsl.ini") );
			for(INI::S & sect : __ini){
				for(INI::K & expr : sect){
					switch(expr){
						case B40LL("include"):
							strcpy(header_name, expr.trim(" \t\r"));
							break ;
						case B40LL("version"):
							maj = expr.as_long( ),
							min = maj/10%10,
							maj /= 100 ;
							break ;
						default:
							break ;
					}
				}
			}
		//	if(auto * a = __ini["include"])assert(sscanf(a, "%s", header_name));
		//	if(auto * a = __ini["version"])assert(sscanf(a, "%i", &maj)),min=maj/10%10,maj/=100;
			// magic core version
			core_version[10] = maj + '0';
			core_version[11] = min + '0';
			// ...
			++ magic_offset ; // \r\n
		}
		const char * p = &source[0];
		assert(strlen(header_name));
		{
			// magic code injection
			RC header(header_name);
			// RC header("config.h");
			if(header){
				for(size_t i=0u; i<header.n; ++i)
					if(header[i] == '\n')
						++ magic_offset ; // \r\n
				char * mem = new char[ size = strlen(core_version) + header.n + source.n ];
				memcpy(mem, core_version, strlen(core_version));
				memcpy(mem+strlen(core_version), &header[0], header.n);
				memcpy(mem+strlen(core_version)+header.n, &source[0], source.n);
				glShaderSource(shader, 1, &mem, &size);
				glCompileShader(shader);
				glGetShaderiv(shader, GL_COMPILE_STATUS, &size);
				delete[ ] mem ;
			} else {
				printf("-------- %s not found --------\n", header_name);
				//...
			}
		}
		//glShaderSource(shader, 1, &p, &GL);
		//glCompileShader(shader);
		//glGetShaderiv(shader, GL_COMPILE_STATUS, &GL);
		if( size ){
			// fine
			return shader ;
		} else {
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
			char * ascii = new char[size];
			glGetShaderInfoLog(shader, size, &size, ascii);
			{
				// magic line correction
				bool inner = false ;
				int line = 0;
				char * ptr = nullptr ;
				for(GLint k(0); k<size; ++k)
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
			printf("`%*s'", size, ascii);
			delete[ ] ascii ;
			glDeleteShader(shader);
		}
	}
	return 0u ;
}
GLuint __GLSLlink(std::initializer_list<GLuint> il){
	if( GLuint program = glCreateProgram( ) ){
		for(GLuint x : il)if( x )
		glAttachShader(program, x);
		glLinkProgram(program);
		GLint GL ;
		glGetProgramiv(program, GL_LINK_STATUS, &GL);
		if( GL );//break
		else {
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &GL);
			char * ascii = new char[GL];
			glGetProgramInfoLog(program, GL, &GL, ascii);
			printf("%*s", GL, ascii);
			delete[ ] ascii ;
			glDeleteProgram(program);
			return 0u ;
		}
		for(GLuint x : il)if( x )
		glDetachShader(program, x);
		return program ;
	}
	return 0u ;
}
// helper above
GLSL :: ~
GLSL(void){
	if( program )printf("warning: GLSL (destructor)\n");
	if( program )assert(wglGetCurrentContext( ));
	if( program )glDeleteProgram(program);
		program = 0u ;
	// shader cleanup ?
}
GLSL ::
GLSL(void){ }
GLSL ::
GLSL(RC&&comp){
	program =
	__GLSLlink({
	__GLSLcompile(GL_COMPUTE_SHADER, comp) });
}
GLSL ::
GLSL(RC&&vert, RC&&frag){
	program =
	__GLSLlink({
	__GLSLcompile(GL_VERTEX_SHADER, vert),
	__GLSLcompile(GL_FRAGMENT_SHADER, frag) });
}
GLSL ::
GLSL(RC&&vert, RC&&geom, RC&&frag){
	program =
	__GLSLlink({
	__GLSLcompile(GL_VERTEX_SHADER, vert),
	__GLSLcompile(GL_GEOMETRY_SHADER, geom),
	__GLSLcompile(GL_FRAGMENT_SHADER, frag) });
}
GLSL ::
GLSL(RC&&vert, RC&&tesc, RC&&tese, RC&&frag){
	program =
	__GLSLlink({
	__GLSLcompile(GL_VERTEX_SHADER, vert),
	__GLSLcompile(GL_TESS_CONTROL_SHADER, tesc),
	__GLSLcompile(GL_TESS_EVALUATION_SHADER, tese),
	__GLSLcompile(GL_FRAGMENT_SHADER, frag) });
}
GLSL ::
GLSL(RC&&vert, RC&&tesc, RC&&tese, RC&&geom, RC&&frag){
	program =
	__GLSLlink({
	__GLSLcompile(GL_VERTEX_SHADER, vert),
	__GLSLcompile(GL_TESS_CONTROL_SHADER, tesc),
	__GLSLcompile(GL_TESS_EVALUATION_SHADER, tese),
	__GLSLcompile(GL_GEOMETRY_SHADER, geom),
	__GLSLcompile(GL_FRAGMENT_SHADER, frag) });
}
GLSL &
GLSL ::
operator = (GLSL && refref) noexcept {
	// cleanup ?
	// ...
	program =
	refref.program,
	refref.program = 0u ;
	// ...
/*	for(int i(0); i<6; ++i)
		shader[i] =
		refref.shader[i],
		refref.shader[i] = 0u ;*/
	// ...
	return *this ;
}
GLint GLSL ::
operator[ ](const char * uniform){
	return program ? glGetUniformLocation(program, uniform) : -1 ;
}
GLSL ::
operator GLuint(void)const {
	if( program )return
		program ;
	// ...
	return 0u ;
}

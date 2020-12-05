# include "fbo.h"

constexpr GLenum GLformat(GLenum internalformat)
{
	switch(internalformat)
	{
		case GL_R8:
		case GL_R8_SNORM:
		case GL_R16:
		case GL_R16_SNORM:
		case GL_R16F:
		case GL_R32F:
			return GL_RED;
		case GL_R8I:
		case GL_R8UI:
		case GL_R16I:
		case GL_R16UI:
		case GL_R32I:
		case GL_R32UI:
			return GL_RED_INTEGER;
		case GL_RG8:
		case GL_RG8_SNORM:
		case GL_RG16:
		case GL_RG16_SNORM:
		case GL_RG16F:
		case GL_RG32F:
			return GL_RG;
		case GL_RG8I:
		case GL_RG8UI:
		case GL_RG16I:
		case GL_RG16UI:
		case GL_RG32I:
		case GL_RG32UI:
			return GL_RG_INTEGER;
		case GL_R3_G3_B2:
		case GL_RGB4:
		case GL_RGB5:
		case GL_RGB8: 
		case GL_RGB8_SNORM:
		case GL_RGB10:
		case GL_RGB12:
		case GL_RGB16_SNORM:
		case GL_SRGB8:
		case GL_RGB16F:
		case GL_RGB32F:
		case GL_R11F_G11F_B10F:
		case GL_RGB9_E5:
			return GL_RGB;
		case GL_RGB8I:
		case GL_RGB8UI:
		case GL_RGB16I:
		case GL_RGB16UI:
		case GL_RGB32I:
		case GL_RGB32UI:
			return GL_RGB_INTEGER;
		case GL_RGBA2:
		case GL_RGBA4:
		case GL_RGB5_A1:
		case GL_RGBA8:
		case GL_RGBA8_SNORM:
		case GL_RGB10_A2:
		case GL_RGBA12:
		case GL_RGBA16:
		case GL_SRGB8_ALPHA8:
		case GL_RGBA16F:
		case GL_RGBA32F:
			return GL_RGBA;
		case GL_RGBA8I:
		case GL_RGBA8UI:
		case GL_RGB10_A2UI:
		case GL_RGBA16I:
		case GL_RGBA16UI:
		case GL_RGBA32I:
		case GL_RGBA32UI:
			return GL_RGBA_INTEGER;
		case GL_DEPTH_COMPONENT16:
		case GL_DEPTH_COMPONENT24:
		case GL_DEPTH_COMPONENT32:
		case GL_DEPTH_COMPONENT32F:
			return GL_DEPTH_COMPONENT;
		// GL_ARB_stencil_texturing 4.3
		case GL_DEPTH24_STENCIL8:
		case GL_DEPTH32F_STENCIL8:
			return GL_DEPTH_STENCIL;
		// ARB_texture_stencil8 4.4
		case GL_STENCIL_INDEX1:
		case GL_STENCIL_INDEX4:
		case GL_STENCIL_INDEX8:
		case GL_STENCIL_INDEX16:
			return GL_STENCIL_INDEX;
		default:
			return internalformat;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
constexpr GLenum GLattachment(GLenum internalformat)
{
	switch(GLformat(internalformat))
	{
		case GL_RED:
		case GL_RED_INTEGER:
		case GL_RG:
		case GL_RG_INTEGER:
		case GL_RGB:
		case GL_RGB_INTEGER:
		case GL_RGBA:
		case GL_RGBA_INTEGER:
			return GL_COLOR_ATTACHMENT0;
		case GL_DEPTH_COMPONENT:
			return GL_DEPTH_ATTACHMENT;
		// GL_ARB_stencil_texturing 4.3
		case GL_DEPTH_STENCIL:
			return GL_DEPTH_STENCIL_ATTACHMENT;
		// ARB_texture_stencil8 4.4
		case GL_STENCIL_INDEX:
			return GL_STENCIL_ATTACHMENT;
		default:
			return GL_COLOR_ATTACHMENT0; // #@?!
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RBO::~RBO(void)
{
	if(renderbuffer)
# ifndef NDEBUG
	if(GLint binding; GL_ASSERT(glGetIntegerv(GL_RENDERBUFFER_BINDING, &binding)))
	if(!ASSERT(binding != renderbuffer) && GL_ASSERT(glBindRenderbuffer(GL_RENDERBUFFER_BINDING, 0)))
# endif
	GL_ASSERT(glDeleteRenderbuffers(1, &renderbuffer)), renderbuffer = 0;
}
# pragma warning (suppress: 26495)
RBO::RBO(RBO &&RBO) noexcept
{
	memcpy(this, &RBO, sizeof RBO);
	memset(&RBO, 0, sizeof RBO);
}
void RBO::operator = (RBO &&RBO) noexcept
{
	RBO::~RBO( );
	memcpy(this, &RBO, sizeof RBO);
	memset(&RBO, 0, sizeof RBO);
}
RBO::RBO(GLenum internalformat, GLsizei width, GLsizei height): internalformat(internalformat)
{
	GL_ASSERT(glGenRenderbuffers(1, &renderbuffer)) &&
	GL_ASSERT(glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer)) &&
	GL_ASSERT(glRenderbufferStorage(GL_RENDERBUFFER, internalformat, width, height));
}
RBO::operator GLuint(void) const
{
	return renderbuffer;
}
// EXT_framebuffer_multisample
RBO::RBO(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height): internalformat(internalformat)
{
	GL_ASSERT(glGenRenderbuffers(1, &renderbuffer)) &&
	GL_ASSERT(glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer)) &&
	GL_ASSERT(glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalformat, width, height));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FBO::~FBO(void)
{
	if(framebuffer) GL_ASSERT(glDeleteFramebuffers(1, &framebuffer)), framebuffer = 0;
}
# pragma warning (suppress: 26495)
FBO::FBO(void)
{
	memset(this, 0, sizeof(FBO));
}
# pragma warning (suppress: 26495)
FBO::FBO(FBO &&FBO) noexcept
{
	memcpy(this, &FBO, sizeof FBO);
	memset(&FBO, 0, sizeof FBO);
}
void FBO::operator = (FBO &&FBO) noexcept
{
	FBO::~FBO( );
	memcpy(this, &FBO, sizeof FBO);
	memset(&FBO, 0, sizeof FBO);
}
/*
// glFramebufferRenderbuffer
void FBO::attach(GLenum attachment, const RBO &renderbuffer, GLint level)
{
	if(ASSERT(framebuffer))
	GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, framebuffer)) &&
	GL_ASSERT(glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderbuffer));
}
// glFramebufferTexture
void FBO::attach(GLenum attachment, const TEX1D &texture, GLint level)
{
	if(ASSERT(framebuffer) && GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, framebuffer)))

	GL_ASSERT(glFramebufferTexture(GL_FRAMEBUFFER, attachment, texture, level));
}
void FBO::attach(GLenum attachment, const TEX2D &texture, GLint level){}
void FBO::attach(GLenum attachment, const TEX3D &texture, GLint level){}
// glFramebufferTextureLayer
void FBO::attach(GLenum attachment, const TEX1D &texture, GLint level, GLint layer){}
void FBO::attach(GLenum attachment, const TEX2D &texture, GLint level, GLint layer){}
void FBO::attach(GLenum attachment, const TEX3D &texture, GLint level, GLint layer){}
*/
FBO::operator GLuint(void) const
{
	return framebuffer;
}
// private
# include <cstdarg>
# include <cstdlib>
FBO::FBO(const GLenum *attachments, size_t sizeof_VA, ...)
{
	GLenum *color_attachments = nullptr;
	size_t N = 0;
	if(GL_ASSERT(glGenFramebuffers(1, &framebuffer)))
	if(GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, framebuffer)))
	{
		va_list ap;
		va_start(ap, sizeof_VA);
		for(size_t index=0; index<sizeof_VA; ++index)
		{
			A A = va_arg(ap, FBO::A);
			// GL_*_ATTACHMENT
			GLenum attachment = GLattachment(A.internalformat);
			if(attachments) attachment = attachments[index];
			else if(attachment == GL_COLOR_ATTACHMENT0) attachment += N;
			if(attachment >= GL_COLOR_ATTACHMENT0 && attachment < GL_DEPTH_ATTACHMENT)
			{
				# pragma warning(suppress: 6308)
				color_attachments = static_cast<GLenum *>(realloc(color_attachments, sizeof(GLenum) *++ N));
				# pragma warning(suppress: 28182)
				color_attachments[N - 1] = attachment;
			}
			else ASSERT(attachment == GLattachment(A.internalformat));
			A.target == GL_RENDERBUFFER
			? GL_ASSERT(glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, A.renderbuffer))
			: GL_ASSERT(glFramebufferTexture(GL_FRAMEBUFFER, attachment, A.texture, 0));
		}
		va_end(ap);
		GL_ASSERT(glDrawBuffers(N, color_attachments));
		if(color_attachments) free(color_attachments);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
// glDeleteFramebuffers
FBO::~FBO(void)
{
	if(ID) GL_ASSERT(glDeleteFramebuffers(1, &ID));
	const_cast<GLuint &>(ID) = 0;
}
// glFramebufferRenderbuffer
void FBO::attach(GLenum attachment, const RBO & renderbuffer)
{
	if(ID == 0) glGenFramebuffers(1, &ID);
	GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, ID));
	GL_ASSERT(glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderbuffer));
}
// glFramebufferTexture
void FBO::attach(GLenum attachment, const TEX1D & texture, GLint level)
{
	if(ID == 0) GL_ASSERT(glGenFramebuffers(1, &ID));
	GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, ID));
	GL_ASSERT(glFramebufferTexture(GL_FRAMEBUFFER, attachment, texture, level));
}
void FBO::attach(GLenum attachment, const TEX2D & texture, GLint level)
{
	if(ID == 0) GL_ASSERT(glGenFramebuffers(1, &ID));
	GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, ID));
	GL_ASSERT(glFramebufferTexture(GL_FRAMEBUFFER, attachment, texture, level));
}
void FBO::attach(GLenum attachment, const TEX3D & texture, GLint level)
{
	if(ID == 0) GL_ASSERT(glGenFramebuffers(1, &ID));
	GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, ID));
	GL_ASSERT(glFramebufferTexture(GL_FRAMEBUFFER, attachment, texture, level));
}
// glFramebufferTextureLayer
void FBO::attach_layer(GLenum attachment, const TEX1D & texture, GLint layer, GLint level)
{
	if(ID == 0) GL_ASSERT(glGenFramebuffers(1, &ID));
	GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, ID));
	GL_ASSERT(glFramebufferTextureLayer(GL_FRAMEBUFFER, attachment, texture, level, layer));
}
void FBO::attach_layer(GLenum attachment, const TEX2D & texture, GLint layer, GLint level)
{
	if(ID == 0) GL_ASSERT(glGenFramebuffers(1, &ID));
	GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, ID));
	GL_ASSERT(glFramebufferTextureLayer(GL_FRAMEBUFFER, attachment, texture, level, layer));
}
void FBO::attach_layer(GLenum attachment, const TEX3D & texture, GLint layer, GLint level)
{
	if(ID == 0) GL_ASSERT(glGenFramebuffers(1, &ID));
	GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, ID));
	GL_ASSERT(glFramebufferTextureLayer(GL_FRAMEBUFFER, attachment, texture, level, layer));
}*/
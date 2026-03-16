#include "TextureMultisample.h"

#include "../Framebuffer/Attachement/FramebufferAttachement.h"
#include "../../Debugging/Debugging.h"
#include "../Dependencies/OpenGL.h"
#include "../../Editor/TypesToEditor/TextureToEditor.h"

namespace ae
{

	TextureMultisample::TextureMultisample( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format, Uint32 _SamplesCount )
	{
		Set( _Width, _Height, _Format, _SamplesCount );
		SetName( std::string( "Texture2DMultisample_" ) + std::to_string( GetResourceID() ) );
	}

	TextureMultisample::TextureMultisample( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _FramebufferAttachement ) 
	{
		Set( _Width, _Height, _FramebufferAttachement );
		SetName( std::string( "Texture2DMultisample_" ) + std::to_string( GetResourceID() ) );
	}

	void TextureMultisample::Set( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format, Uint32 _SamplesCount )
	{
		m_Dimension = TextureDimension::Texture2DMultiSample;
		m_Width = _Width;
		m_Height = _Height;
		m_Format = _Format;
		m_SampleCount = _SamplesCount;

		SetupEmpty();		
	}

	void TextureMultisample::Set( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format )
	{
		m_Dimension = TextureDimension::Texture2DMultiSample;
		m_Width = _Width;
		m_Height = _Height;
		m_Format = _Format;
		m_SampleCount = 1;

		SetupEmpty();
	}

	void TextureMultisample::Set( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _FramebufferAttachement )
	{
		m_Dimension = TextureDimension::Texture2DMultiSample;
		m_Width = _Width;
		m_Height = _Height;
		m_Format = _FramebufferAttachement.GetFormat();
		m_Filter = _FramebufferAttachement.GetFilter();
		m_SampleCount = _FramebufferAttachement.GetSamplesCount();

		SetupEmpty();
	}

	void TextureMultisample::SetSamplesCount( Uint32 _SamplesCount )
	{
		if( m_SampleCount == _SamplesCount )
			return;

		m_SampleCount = _SamplesCount;

		// Apply the multi sampling setting.
		SetupEmpty();
	}

	Uint32 TextureMultisample::GetSamplesCount() const
	{
		return m_SampleCount;
	}

	void TextureMultisample::AttachToFramebuffer( const FramebufferAttachement& _Attachement ) const
	{
		glFramebufferTexture2D( GL_FRAMEBUFFER,
								_Attachement.GetGLAttachement(),
								Cast( GLenum, GetDimension() ),
								GetTextureID(),
								0 );
		AE_ErrorCheckOpenGLError();
	}

	void TextureMultisample::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::TextureToEditorBegin();
		priv::ui::TextureMultisampleToEditor( *this );
		priv::ui::TextureToEditorEnd();
	}

	void TextureMultisample::SetupEmpty()
	{
		Bind();

		// Texture settings :  repeat ? - pixel interpolation ( smoothing ) ?.
		glTexParameteri( GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();

		glTexImage2DMultisample( GL_TEXTURE_2D_MULTISAMPLE, m_SampleCount, ToGLInternalFormat( m_Format ), m_Width, m_Height, GL_TRUE );
		AE_ErrorCheckOpenGLError();

		Unbind();
	}

} // ae

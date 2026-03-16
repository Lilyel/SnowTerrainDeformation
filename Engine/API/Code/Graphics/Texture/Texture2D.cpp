#include "Texture2D.h"

#include "../Framebuffer/Attachement/FramebufferAttachement.h"
#include "../../Debugging/Debugging.h"
#include "../Dependencies/OpenGL.h"
#include "../../Editor/TypesToEditor/TextureToEditor.h"

namespace ae
{

	Texture2D::Texture2D( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format )
	{
		Set( _Width, _Height, _Format );
		SetName( std::string( "Texture2D_" ) + std::to_string( GetResourceID() ) );
	}

	Texture2D::Texture2D( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _FramebufferAttachement )
	{
		Set( _Width, _Height, _FramebufferAttachement );
		SetName( std::string( "Texture2D_" ) + std::to_string( GetResourceID() ) );
	}

	void Texture2D::Set( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format )
	{
		m_Dimension = TextureDimension::Texture2D;
		m_Width = _Width;
		m_Height = _Height;
		m_Format = _Format;

		SetupEmpty();		
	}

	void Texture2D::Set( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _FramebufferAttachement )
	{
		m_Dimension = TextureDimension::Texture2D;
		m_Width = _Width;
		m_Height = _Height;
		m_Format = _FramebufferAttachement.GetFormat();
		m_Filter = _FramebufferAttachement.GetFilter();

		SetupEmpty();
	}

	void Texture2D::Resize( Uint32 _Width, Uint32 _Height )
	{
		if( m_Width == _Width && m_Height == _Height )
			return;

		m_Width = _Width;
		m_Height = _Height;

		SetupEmpty();
	}

	Uint32 Texture2D::GetWidth() const
	{
		return m_Width;
	}

	Uint32 Texture2D::GetHeight() const
	{
		return m_Height;
	}

	void Texture2D::AttachToFramebuffer( const FramebufferAttachement& _Attachement ) const
	{
		glFramebufferTexture2D( GL_FRAMEBUFFER,
								_Attachement.GetGLAttachement(),
								Cast( GLenum, GetDimension() ),
								GetTextureID(),
								0 );
		AE_ErrorCheckOpenGLError();
	}


	Image Texture2D::ToImage() const
	{
		Uint8 ChannelsCount = GetChannelsCount( m_Format );

		std::vector<Uint8> Pixels( Cast( size_t, GetWidth() ) * Cast( size_t,  GetHeight() ) * Cast( size_t, ChannelsCount ), 0 );

		glGetTexImage( Cast( GLenum, GetDimension() ), 0, ToGLFormat( m_Format ), GL_UNSIGNED_BYTE, Pixels.data() );
		AE_ErrorCheckOpenGLError();

		Image ImageData;
		ImageData.LoadFromMemory( Pixels.data(), GetWidth(), GetHeight(), Cast( ImageFormat, ChannelsCount ) );

		return ImageData;
	}


	void Texture2D::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::TextureToEditorBegin();
		priv::ui::Texture2DToEditor( *this );
		priv::ui::Texture2DToEditorPreview( *this );
		priv::ui::TextureToEditorEnd();
	}

	Texture2D::Texture2D()
	{
	}

	void Texture2D::SetupEmpty()
	{
		Bind();

		// Texture settings :  repeat ? - pixel interpolation ( smoothing ) ?.
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();

		glTexImage2D( GL_TEXTURE_2D, 0, ToGLInternalFormat( m_Format ), m_Width, m_Height, 0, ToGLFormat( m_Format ), ToGLType( m_Format ), nullptr ); 
		AE_ErrorCheckOpenGLError();

		Unbind();
	}

}

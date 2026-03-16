#include "Texture1D.h"

#include "../Framebuffer/Attachement/FramebufferAttachement.h"
#include "../../Debugging/Debugging.h"
#include "../Dependencies/OpenGL.h"
#include "../../Editor/TypesToEditor/TextureToEditor.h"

namespace ae
{

	Texture1D::Texture1D( Uint32 _Width, TexturePixelFormat _Format )
	{
		Set( _Width, _Format );
		SetName( std::string( "Texture1D_" ) + std::to_string( GetResourceID() ) );
	}

	Texture1D::Texture1D( Uint32 _Width, const FramebufferAttachement& _FramebufferAttachement )
	{
		Set( _Width, _FramebufferAttachement );
	}

	void Texture1D::Set( Uint32 _Width, TexturePixelFormat _Format )
	{
		m_Dimension = TextureDimension::Texture1D;
		m_Width = _Width;
		m_Format = _Format;

		SetupEmpty();		
	}

	void Texture1D::Set( Uint32 _Width, const FramebufferAttachement& _FramebufferAttachement )
	{
		m_Dimension = TextureDimension::Texture1D;
		m_Width = _Width;
		m_Format = _FramebufferAttachement.GetFormat();
		m_Filter = _FramebufferAttachement.GetFilter();

		SetupEmpty();
	}

	void Texture1D::Resize( Uint32 _Width )
	{
		if( m_Width == _Width )
			return;

		m_Width = _Width;

		SetupEmpty();
	}

	Uint32 Texture1D::GetWidth() const
	{
		return m_Width;
	}

	void Texture1D::AttachToFramebuffer( const FramebufferAttachement& _Attachement ) const
	{
		glFramebufferTexture1D( GL_FRAMEBUFFER,
								_Attachement.GetGLAttachement(),
								Cast( GLenum, GetDimension() ),
								GetTextureID(),
								0 );
		AE_ErrorCheckOpenGLError();
	}

	void Texture1D::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::TextureToEditorBegin();
		priv::ui::Texture1DToEditor( *this );
		priv::ui::TextureToEditorEnd();
	}

	void Texture1D::SetupEmpty()
	{
		Bind();

		// Texture settings :  repeat ? - pixel interpolation ( smoothing ) ?.
		glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();

		glTexImage1D( GL_TEXTURE_1D, 0, ToGLInternalFormat( m_Format ), m_Width, 0, ToGLFormat( m_Format ), ToGLType( m_Format ), nullptr );
		AE_ErrorCheckOpenGLError();

		Unbind();
	}


} // ae

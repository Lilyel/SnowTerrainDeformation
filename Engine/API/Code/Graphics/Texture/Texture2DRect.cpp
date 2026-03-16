#include "Texture2DRect.h"

#include "../Framebuffer/Attachement/FramebufferAttachement.h"
#include "../../Debugging/Debugging.h"
#include "../Dependencies/OpenGL.h"
#include "../../Editor/TypesToEditor/TextureToEditor.h"

namespace ae
{

	Texture2DRect::Texture2DRect( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format )
	{
		Set( _Width, _Height, _Format );
		SetName( std::string( "Texture2DRect_" ) + std::to_string( GetResourceID() ) );
	}

	Texture2DRect::Texture2DRect( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _FramebufferAttachement )
	{
		Set( _Width, _Height, _FramebufferAttachement );
		SetName( std::string( "Texture2DRect_" ) + std::to_string( GetResourceID() ) );
	}

	void Texture2DRect::Set( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format )
	{
		m_Dimension = TextureDimension::Texture2DRect;
		m_Width = _Width;
		m_Height = _Height;
		m_Format = _Format;

		SetupEmpty();		
	}

	void Texture2DRect::Set( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _FramebufferAttachement )
	{
		m_Dimension = TextureDimension::Texture2DRect;
		m_Width = _Width;
		m_Height = _Height;
		m_Format = _FramebufferAttachement.GetFormat();
		m_Filter = _FramebufferAttachement.GetFilter();

		SetupEmpty();
	}

	void Texture2DRect::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::TextureToEditorBegin();
		priv::ui::Texture2DRectToEditor( *this );
		priv::ui::TextureToEditorEnd();
	}

	void Texture2DRect::SetupEmpty()
	{
		Bind();

		// Texture settings :  repeat ? - pixel interpolation ( smoothing ) ?.
		glTexParameteri( GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();

		glTexImage2D( GL_TEXTURE_RECTANGLE, 0, ToGLInternalFormat( m_Format ), m_Width, m_Height, 0, ToGLFormat( m_Format ), ToGLType( m_Format ), nullptr );
		AE_ErrorCheckOpenGLError();

		Unbind();
	}

	void Texture2DRect::AttachToFramebuffer( const FramebufferAttachement& ) const
	{
		throw std::exception( "Impossible to set a texture rectangle as framebuffer attachement." );
	}

}
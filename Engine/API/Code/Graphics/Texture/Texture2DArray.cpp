#include "Texture2DArray.h"

#include "../Framebuffer/Attachement/FramebufferAttachement.h"
#include "../../Debugging/Debugging.h"
#include "../Dependencies/OpenGL.h"
#include "../../Editor/TypesToEditor/TextureToEditor.h"

namespace ae
{

	Texture2DArray::Texture2DArray( Uint32 _Width, Uint32 _Height, Uint32 _Depth, TexturePixelFormat _Format )
	{
		Set( _Width, _Height, _Depth, _Format );
		SetName( std::string( "Texture2DArray_" ) + std::to_string( GetResourceID() ) );
	}

	Texture2DArray::Texture2DArray( Uint32 _Width, Uint32 _Height, Uint32 _Depth, const FramebufferAttachement& _FramebufferAttachement )
	{
		Set( _Width, _Height, _Depth, _FramebufferAttachement );
		SetName( std::string( "Texture2DArray_" ) + std::to_string( GetResourceID() ) );
	}

	void Texture2DArray::Set( Uint32 _Width, Uint32 _Height, Uint32 _Depth, TexturePixelFormat _Format )
	{
		m_Dimension = TextureDimension::Texture2DArray;
		m_Width = _Width;
		m_Height = _Height;
		m_Depth = _Depth;
		m_Format = _Format;

		SetupEmpty();		
	}

	void Texture2DArray::Set( Uint32 _Width, Uint32 _Height, Uint32 _Depth, const FramebufferAttachement& _FramebufferAttachement )
	{
		m_Dimension = TextureDimension::Texture2DArray;
		m_Width = _Width;
		m_Height = _Height;
		m_Depth = _Depth;
		m_Format = _FramebufferAttachement.GetFormat();
		m_Filter = _FramebufferAttachement.GetFilter();

		SetupEmpty();
	}

	void Texture2DArray::Resize( Uint32 _Width, Uint32 _Height, Uint32 _Depth )
	{
		if( m_Width == _Width && m_Height == _Height && m_Depth == _Depth )
			return;

		m_Width = _Width;
		m_Height = _Height;
		m_Depth = _Depth;

		SetupEmpty();
	}

	Uint32 Texture2DArray::GetWidth() const
	{
		return m_Width;
	}

	Uint32 Texture2DArray::GetHeight() const
	{
		return m_Height;
	}

	Uint32 Texture2DArray::GetDepth() const
	{
		return m_Depth;
	}

	void Texture2DArray::AttachToFramebuffer( const FramebufferAttachement& _Attachement ) const
	{
		glFramebufferTexture3D( GL_FRAMEBUFFER,
								_Attachement.GetGLAttachement(),
								Cast( GLenum, GetDimension() ),
								GetTextureID(),
								0, 0 );
		AE_ErrorCheckOpenGLError();
	}

	void Texture2DArray::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::TextureToEditorBegin();
		priv::ui::Texture2DArrayToEditor( *this );
		priv::ui::TextureToEditorEnd();
	}

	void Texture2DArray::SetupEmpty()
	{
		Bind();

		// Texture settings :  repeat ? - pixel interpolation ( smoothing ) ?.
		glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();

		glTexImage3D( GL_TEXTURE_2D_ARRAY, 0, ToGLInternalFormat( m_Format ), m_Width, m_Height, m_Depth, 0, ToGLFormat( m_Format ), ToGLType( m_Format ), nullptr );
		AE_ErrorCheckOpenGLError();

		Unbind();
	}

}

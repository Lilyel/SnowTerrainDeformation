#include "Texture1DArray.h"

#include "../Framebuffer/Attachement/FramebufferAttachement.h"
#include "../../Debugging/Debugging.h"
#include "../Dependencies/OpenGL.h"
#include "../../Editor/TypesToEditor/TextureToEditor.h"

namespace ae
{

	Texture1DArray::Texture1DArray( Uint32 _Width, Uint32 _Depth, TexturePixelFormat _Format )
	{
		Set( _Width, _Depth, _Format );
		SetName( std::string( "Texture1DArray_" ) + std::to_string( GetResourceID() ) );
	}

	Texture1DArray::Texture1DArray( Uint32 _Width, Uint32 _Depth, const FramebufferAttachement& _FramebufferAttachement )
	{
		Set( _Width, _Depth, _FramebufferAttachement );
		SetName( std::string( "Texture1DArray_" ) + std::to_string( GetResourceID() ) );
	}

	void Texture1DArray::Set( Uint32 _Width, Uint32 _Depth, TexturePixelFormat _Format )
	{
		m_Dimension = TextureDimension::Texture1DArray;
		m_Width = _Width;
		m_Depth = _Depth;
		m_Format = _Format;

		SetupEmpty();		
	}

	void Texture1DArray::Set( Uint32 _Width, Uint32 _Depth, const FramebufferAttachement& _FramebufferAttachement )
	{
		m_Dimension = TextureDimension::Texture1DArray;
		m_Width = _Width;
		m_Depth = _Depth;
		m_Format = _FramebufferAttachement.GetFormat();
		m_Filter = _FramebufferAttachement.GetFilter();

		SetupEmpty();
	}

	void Texture1DArray::Resize( Uint32 _Width, Uint32 _Depth )
	{
		if( m_Width == _Width && m_Depth == _Depth )
			return;

		m_Width = _Width;
		m_Depth = _Depth;

		SetupEmpty();
	}

	Uint32 Texture1DArray::GetWidth() const
	{
		return m_Width;
	}

	Uint32 Texture1DArray::GetDepth() const
	{
		return m_Depth;
	}

	void Texture1DArray::AttachToFramebuffer( const FramebufferAttachement& _Attachement ) const
	{
		glFramebufferTexture2D( GL_FRAMEBUFFER,
								_Attachement.GetGLAttachement(),
								Cast( GLenum, GetDimension() ),
								GetTextureID(),
								0 );
		AE_ErrorCheckOpenGLError();
	}

	void Texture1DArray::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::TextureToEditorBegin();
		priv::ui::Texture1DArrayToEditor( *this );
		priv::ui::TextureToEditorEnd();
	}

	void Texture1DArray::SetupEmpty()
	{
		Bind();

		// Texture settings :  repeat ? - pixel interpolation ( smoothing ) ?.
		glTexParameteri( GL_TEXTURE_1D_ARRAY, GL_TEXTURE_WRAP_S, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_1D_ARRAY, GL_TEXTURE_WRAP_T, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MIN_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MAG_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();

		glTexImage2D( GL_TEXTURE_1D_ARRAY, 0, ToGLInternalFormat( m_Format ), m_Width, m_Depth, 0, ToGLFormat( m_Format ), ToGLType( m_Format ), nullptr );
		AE_ErrorCheckOpenGLError();

		Unbind();
	}

}

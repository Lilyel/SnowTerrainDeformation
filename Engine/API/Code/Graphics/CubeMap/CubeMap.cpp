#include "CubeMap.h"

#include "../Framebuffer/Attachement/FramebufferAttachement.h"
#include "../../Debugging/Debugging.h"
#include "../Dependencies/OpenGL.h"
#include "../../Aero/Aero.h"
#include "../../Editor/TypesToEditor/CubeMapToEditor.h"

namespace ae
{

	CubeMap::CubeMap( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format )
	{
		m_Wrap = TextureWrapMode::ClampToEdge;
		Set( _Width, _Height, _Format );
	}

	CubeMap::CubeMap( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _FramebufferAttachement )
	{
		m_Wrap = TextureWrapMode::ClampToEdge;
		Set( _Width, _Height, _FramebufferAttachement );
	}

	void CubeMap::Set( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format )
	{
		m_Dimension = TextureDimension::CubeMap;
		SetWidths( _Width );
		SetHeights( _Height );
		m_Format = _Format;

		SetupEmpty();

		SetName( std::string( "CubeMap_" ) + std::to_string( GetResourceID() ) );
	}

	void CubeMap::Set( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _FramebufferAttachement )
	{
		m_Dimension = TextureDimension::CubeMap;
		SetWidths( _Width );
		SetHeights( _Height );
		m_Format = _FramebufferAttachement.GetFormat();
		m_Filter = _FramebufferAttachement.GetFilter();

		SetupEmpty();

		SetName( std::string( "CubeMap_FBA_" ) + std::to_string( GetResourceID() ) );
	}


	void CubeMap::SetWrapMode( TextureWrapMode _Mode )
	{
		m_Wrap = _Mode;

		if( !Aero.CheckContext() )
			return;

		// Bind it to apply the next settings to it.
		Bind();

		// Apply the new wrap mode.
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();

		// Once we have finished, we unbind the texture from OpenGL.
		Unbind();

		if( m_Wrap == TextureWrapMode::ClampToBorder )
			SetBorderColor( m_BorderColor );
	}


	Uint32 CubeMap::GetWidth( Uint32 _Index ) const
	{
		if( _Index >= 6 )
		{
			AE_LogError( "Try to access to a cube map's width superior to 5, returing 0. (Cube map textures indexes must be in [0-5])" );
			return 0;
		}

		return m_Widths[_Index];
	}

	Uint32 CubeMap::GetHeight( Uint32 _Index ) const
	{
		if( _Index >= 6 )
		{
			AE_LogError( "Try to access to a cube map's height superior to 5, returing 0. (Cube map textures indexes must be in [0-5])" );
			return 0;
		}

		return m_Heights[_Index];
	}

	void CubeMap::AttachToFramebuffer( const FramebufferAttachement& _Attachement ) const
	{
		glFramebufferTexture( GL_FRAMEBUFFER, _Attachement.GetGLAttachement(), GetTextureID(), 0 );
		AE_ErrorCheckOpenGLError();
	}

	void CubeMap::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::CubeMapToEditorBegin();
		priv::ui::CubeMapToEditor( *this );
		priv::ui::TextureToEditorEnd();
	}

	CubeMap::CubeMap()
	{
		SetWidths( 0 );
		SetHeights( 0 );
	}

	void CubeMap::SetupEmpty()
	{
		Bind();

		// Texture settings :  repeat ? - pixel interpolation ( smoothing ) ?.
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();

		for( size_t i = 0; i < 6; i++ )
		{
			glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + Cast( GLenum, i ),
						  0,
						  ToGLInternalFormat( m_Format ),
						  m_Widths[i], m_Heights[i],
						  0,
						  ToGLFormat( m_Format ),
						  ToGLType( m_Format ),
						  nullptr );
			AE_ErrorCheckOpenGLError();
		}

		Unbind();
	}

	void CubeMap::SetWidths( Uint32 _Width )
	{
		m_Widths[0] = _Width;
		m_Widths[1] = _Width;
		m_Widths[2] = _Width;
		m_Widths[3] = _Width;
		m_Widths[4] = _Width;
		m_Widths[5] = _Width;
	}

	void CubeMap::SetHeights( Uint32 _Height )
	{
		m_Heights[0] = _Height;
		m_Heights[1] = _Height;
		m_Heights[2] = _Height;
		m_Heights[3] = _Height;
		m_Heights[4] = _Height;
		m_Heights[5] = _Height;
	}

} // ae

#include "Texture.h"

#include "../../Debugging/Debugging.h"
#include "../../Editor/TypesToEditor/TextureToEditor.h"
#include "../../Maths/Functions/MathsFunctions.h"
#include "../Image/Image.h"

#include "../../Aero/Aero.h"

#include "../Dependencies/OpenGL.h"

namespace ae
{
	Texture::Texture() :
		m_TextureID( 0 ),
		m_Filter( TextureFilterMode::Linear ),
		m_Wrap( TextureWrapMode::ClampToEdge ),
		m_Format( TexturePixelFormat::Red_U8 ),
		m_Dimension( TextureDimension::Texture2D ),
		m_IsBoundAsImage( False )
	{
		CreateResource();
		SetName( std::string( "Texture_" ) + std::to_string( GetResourceID() ) );
	}

	Texture::~Texture()
	{
		FreeResource();
	}

	void Texture::SetFilterMode( TextureFilterMode _Mode )
	{
		if( m_Filter == _Mode )
			return;

		m_Filter = _Mode;

		if( !Aero.CheckContext() )
			return;

		// Bind it to apply the next settings to it.
		Bind();

		// Apply the new filter mode.
		glTexParameteri( Cast( GLenum, m_Dimension ), GL_TEXTURE_MIN_FILTER, Cast( GLint, m_Filter ) );
		AE_ErrorCheckOpenGLError();
		glTexParameteri( Cast( GLenum, m_Dimension ), GL_TEXTURE_MAG_FILTER, Cast( GLint, m_Filter ) );
		AE_ErrorCheckOpenGLError();

		// Once we have finished, we unbind the texture from OpenGL.
		Unbind();
	}

	TextureFilterMode Texture::GetFilterMode() const
	{
		return m_Filter;
	}


	void Texture::SetWrapMode( TextureWrapMode _Mode )
	{
		if( m_Wrap == _Mode )
			return;

		m_Wrap = _Mode;

		if( !Aero.CheckContext() )
			return;

		// Bind it to apply the next settings to it.
		Bind();

		// Apply the new wrap mode.
		glTexParameteri( Cast( GLenum, m_Dimension ), GL_TEXTURE_WRAP_S, Cast( GLint, m_Wrap ) );
		AE_ErrorCheckOpenGLError();
		glTexParameteri( Cast( GLenum, m_Dimension ), GL_TEXTURE_WRAP_T, Cast( GLint, m_Wrap ) );
		AE_ErrorCheckOpenGLError();

		// Once we have finished, we unbind the texture from OpenGL.
		Unbind();

		if( m_Wrap == TextureWrapMode::ClampToBorder )
			SetBorderColor( m_BorderColor );
	}

	TextureWrapMode Texture::GetWrapMode() const
	{
		return m_Wrap;
	}

	TexturePixelFormat Texture::GetFormat() const
	{
		return m_Format;
	}

	TextureDimension Texture::GetDimension() const
	{
		return m_Dimension;
	}


	void Texture::SetBorderColor( const Color& _Color )
	{
		if( m_BorderColor == _Color )
			return;

		m_BorderColor = _Color;

		if( !Aero.CheckContext() )
			return;

		// Bind it to apply the next settings to it.
		Bind();

		// Apply the new color for the border.
		const GLfloat Color[4] = { m_BorderColor.R(), m_BorderColor.G(), m_BorderColor.B(), m_BorderColor.A() };
		glTexParameterfv( Cast( GLenum, m_Dimension ), GL_TEXTURE_BORDER_COLOR, Color );

		// Once we have finished, we unbind the texture from OpenGL.
		Unbind();
	}

	const Color& Texture::GetBorderColor() const
	{
		return m_BorderColor;
	}

	void Texture::GenerateMipMap() const
	{
		if( !Aero.CheckContext() )
			return;

		// Bind it to apply the next settings to it.
		Bind();

		glGenerateMipmap( Cast( GLenum, m_Dimension ) );

		// Once we have finished, we unbind the texture from OpenGL.
		Unbind();
	}

	void Texture::Bind() const
	{
		glBindTexture( Cast( GLenum, m_Dimension ), m_TextureID );
		AE_ErrorCheckOpenGLError();
	}

	void Texture::Unbind() const
	{
		glBindTexture( Cast( GLenum, m_Dimension ), 0 );
		AE_ErrorCheckOpenGLError();
	}

	void Texture::BindAsImage( Uint32 _ImageUnit, TextureImageBindMode _AccessMode, Bool _IsLayered, Uint32 _Layer ) const
	{
		glBindImageTexture( _ImageUnit, m_TextureID, 0, _IsLayered, _Layer, Cast( GLenum, _AccessMode ), ToGLImageFormat( m_Format ) );
		AE_ErrorCheckOpenGLError();
	}

	void Texture::UnbindAsImage() const
	{
		glBindImageTexture( 0, 0, 0, False, 0, GL_READ_WRITE, ToGLImageFormat( m_Format ) );
		AE_ErrorCheckOpenGLError();
	}

	void Texture::SetName( const std::string& _NewName )
	{
		Resource::SetName( _NewName );

		const std::string& Name = GetName();

		glObjectLabel( GL_TEXTURE, m_TextureID, Cast( GLsizei, Name.size() ), Name.c_str() );
	}

	Uint32 Texture::GetTextureID() const
	{
		return m_TextureID;
	}

	Bool Texture::IsBoundAsImage() const
	{
		return m_IsBoundAsImage;
	}

	void Texture::SetIsBoundAsImage( Bool _IsBoundAsImage )
	{
		m_IsBoundAsImage = _IsBoundAsImage;
	}


	void Texture::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::TextureToEditorBegin();
		priv::ui::TextureToEditor( *this );
		priv::ui::TextureToEditorEnd();
	}

	void Texture::CreateResource()
	{
		if( !Aero.CheckContext() )
			return;

		// Generate the OpenGL texture.
		glGenTextures( 1, &m_TextureID ); AE_ErrorCheckOpenGLError();
	}

	void Texture::FreeResource()
	{
		if( m_TextureID && Aero.CheckContext() )
		{
			glDeleteTextures( 1, &m_TextureID ); AE_ErrorCheckOpenGLError();
			m_TextureID = 0;
		}
	}
} // ae
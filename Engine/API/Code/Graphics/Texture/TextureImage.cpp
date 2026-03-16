#include "TextureImage.h"

#include "../Framebuffer/Attachement/FramebufferAttachement.h"
#include "../Image/Image.h"
#include "../Image/ImageHDR.h"
#include "../../Debugging/Debugging.h"
#include "../Dependencies/OpenGL.h"
#include "../../Editor/TypesToEditor/TextureToEditor.h"

namespace ae
{
	TextureImage::TextureImage( const std::string& _FilePath, const IntRect& _SubRect )
	{
		Set( _FilePath, _SubRect );
		SetName( std::string( "TextureImage_" ) + std::to_string( GetResourceID() ) );
	}

	TextureImage::TextureImage( const Image& _ImageSource, const IntRect& _SubRect )
	{
		Set( _ImageSource, _SubRect );
		SetName( std::string( "TextureImage_" ) + std::to_string( GetResourceID() ) );
	}

	TextureImage::TextureImage( const ImageHDR& _ImageSource, const IntRect& _SubRect )
	{
		Set( _ImageSource, _SubRect );
		SetName( std::string( "TextureImage_" ) + std::to_string( GetResourceID() ) );
	}

	void TextureImage::Set( const std::string& _FilePath, const IntRect& _SubRect )
	{
		const Image ImageSource( _FilePath );

		m_Dimension = TextureDimension::Texture2D;
		m_Width = ImageSource.GetWidth();
		m_Height = ImageSource.GetHeight();
		m_Format = ImageSource.GetTexturePixelFormat();

		UpdateDataFromImage( ImageSource, _SubRect );		
	}

	void TextureImage::Set( const Image& _ImageSource, const IntRect& _SubRect )
	{
		m_Dimension = TextureDimension::Texture2D;
		m_Width = _ImageSource.GetWidth();
		m_Height = _ImageSource.GetHeight();
		m_Format = _ImageSource.GetTexturePixelFormat();
		
		UpdateDataFromImage( _ImageSource, _SubRect );
	}

	void TextureImage::Set( const ImageHDR& _ImageSource, const IntRect& _SubRect )
	{
		m_Dimension = TextureDimension::Texture2D;
		m_Width = _ImageSource.GetWidth();
		m_Height = _ImageSource.GetHeight();
		m_Format = _ImageSource.GetTexturePixelFormat();

		UpdateDataFromImage( _ImageSource, _SubRect );
	}

	const std::string& TextureImage::GetFilePath() const
	{
		return m_FilePath;
	}

	void TextureImage::AttachToFramebuffer( const FramebufferAttachement& _Attachement ) const
	{
		glFramebufferTexture2D( GL_FRAMEBUFFER,
								_Attachement.GetGLAttachement(),
								Cast( GLenum, GetDimension() ),
								GetTextureID(),
								0 );
		AE_ErrorCheckOpenGLError();
	}

	void TextureImage::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::TextureToEditorBegin();
		priv::ui::TextureImageToEditor( *this );
		priv::ui::Texture2DToEditorPreview( *this );
		priv::ui::TextureToEditorEnd();
	}

	void TextureImage::UpdateDataFromImage( const Image& _ImageSource, const IntRect& _SubRect )
	{
		// If the rect is not user defined, chose the image size.
		if( _SubRect.Left == 0 && _SubRect.Right == 0 && _SubRect.Top == 0 && _SubRect.Bottom == 0 )
		{
			m_Width = _ImageSource.GetWidth();
			m_Height = _ImageSource.GetHeight();
		}
		else
		{
			m_Width = Math::Abs( _SubRect.Right - _SubRect.Left );
			m_Height = Math::Abs( _SubRect.Bottom - _SubRect.Top );
		}

		Texture2D::SetupEmpty();

		Bind();

		// Send to OpenGL the part of the image we want.
		glTexSubImage2D( GL_TEXTURE_2D, 0, _SubRect.Left, _SubRect.Top, m_Width, m_Height, ToGLFormat( m_Format ), ToGLType( m_Format ), _ImageSource.GetData() );
		AE_ErrorCheckOpenGLError();

		Unbind();
	}

	void TextureImage::UpdateDataFromImage( const ImageHDR& _ImageSource, const IntRect& _SubRect )
	{
		// If the rect is not user defined, chose the image size.
		if( _SubRect.Left == 0 && _SubRect.Right == 0 && _SubRect.Top == 0 && _SubRect.Bottom == 0 )
		{
			m_Width = _ImageSource.GetWidth();
			m_Height = _ImageSource.GetHeight();
		}
		else
		{
			m_Width = Math::Abs( _SubRect.Right - _SubRect.Left );
			m_Height = Math::Abs( _SubRect.Bottom - _SubRect.Top );
		}

		Texture2D::SetupEmpty();

		Bind();

		// Send to OpenGL the part of the image we want.
		glTexSubImage2D( GL_TEXTURE_2D, 0, _SubRect.Left, _SubRect.Top, m_Width, m_Height, ToGLFormat( m_Format ), ToGLType( m_Format ), _ImageSource.GetData() );
		AE_ErrorCheckOpenGLError();

		Unbind();
	}

} // ae

#include "ImageBase.h"

namespace ae
{
	ImageBase::ImageBase() : 
		m_Width( 0 ),
		m_Height( 0 ),
		m_ChannelsCount( 0 )
	{
	}
	Uint32 ImageBase::GetWidth() const
	{
		return m_Width;
	}

	Uint32 ImageBase::GetHeight() const
	{
		return m_Height;
	}

	ImageFormat ImageBase::GetFormat() const
	{
		return Cast( ImageFormat, m_ChannelsCount );
	}

	GLenum ImageBase::GetFormatOpenGL() const
	{
		switch( m_ChannelsCount )
		{
		case 1:
			return GL_LUMINANCE;

		case 2:
			return GL_LUMINANCE_ALPHA;

		case 3:
			return GL_RGB;

		case 4:
			return GL_RGBA;

		default:
			AE_LogError( "Invalid image format" );
			return GL_INVALID_ENUM;
		}
	}

	Uint32 ImageBase::GetChannelsCount() const
	{
		return m_ChannelsCount;
	}

	const std::string& ImageBase::GetFilePath() const
	{
		return m_FilePath;
	}

	Color ImageBase::GetPixel( const Uint32 _X, const Uint32 _Y ) const
	{
		if( _X >= m_Width || _Y >= m_Height )
		{
			AE_LogError( "Index out of range" );
			return Color::White;
		}

		return GetPixelConverted( _Y * m_Width + _X );
	}

	Color ImageBase::GetPixel( const Uint32 _Index ) const
	{
		if( _Index >= Cast( Uint32, m_Width ) * Cast( Uint32, m_Height ) )
		{
			AE_LogError( "Index out of range" );
			return Color::White;
		}

		return GetPixelConverted( _Index );
	}

	void ImageBase::SetPixel( const Uint32 _X, const Uint32 _Y, const Color& _Color )
	{
		if( _X >= m_Width || _Y >= m_Height )
		{
			AE_LogError( "Index out of range" );
			return;
		}

		SetPixelConverted( _Y * m_Width + _X, _Color );
	}

	void ImageBase::SetPixel( const Uint32 _Index, const Color& _Color )
	{
		if( _Index >= Cast( Uint32, m_Width ) * Cast( Uint32, m_Height ) )
		{
			AE_LogError( "Index out of range" );
			return;
		}

		SetPixelConverted( _Index, _Color );
	}

}
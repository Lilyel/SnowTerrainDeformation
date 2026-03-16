#include "ImageHDR.h"

#include "../../Debugging/Debugging.h"
#include "../../Maths/Functions/MathsFunctions.h"
#include "../../Editor/TypesToEditor/ImageToEditor.h"

#include "../STBImageHelper/STBImageHelper.h"

namespace ae
{
	ImageHDR::ImageHDR() :
		ImageBase()
	{
	}

	ImageHDR::ImageHDR( const Uint32 _Width, const Uint32 _Height, const ImageFormat _Format ) :
		ImageHDR()
	{
		// Reserve the memory for the picture.
		AllocatePixelsArray( _Width, _Height, Cast( Uint32, _Format ) );
	}

	ImageHDR::ImageHDR( const std::string& _FileName ) :
		ImageHDR()
	{
		LoadFromFile( _FileName );
	}

	ImageHDR::ImageHDR( const ImageHDR& _Copy )
	{
		// Reserve the memory for the picture.
		AllocatePixelsArray( _Copy.m_Width, _Copy.m_Height, Cast( Uint32, _Copy.m_ChannelsCount ) );

		CopyPixels( _Copy.GetData() );
	}

	ImageHDR::~ImageHDR()
	{
		DestroyPixelsArray();
	}

	ImageHDR& ImageHDR::operator=( const ImageHDR& _Copy )
	{
		// Reserve the memory for the picture.
		AllocatePixelsArray( _Copy.m_Width, _Copy.m_Height, Cast( Uint32, _Copy.m_ChannelsCount ) );

		CopyPixels( _Copy.GetData() );

		return *this;
	}

	Bool ImageHDR::LoadFromFile( const std::string& _FileName )
	{
		Int32 Width;
		Int32 Height;
		Int32 ChannelsCount;

		// Load raw data from file.
		float* Pixels = priv::STBLoadFileFloat( Width, Height, ChannelsCount, _FileName );

		if( !Pixels || !Width || !Height )
		{
			AE_LogError( std::string( "Failed to load " ) + _FileName + std::string( " Reason : " ) + priv::STBGetFailureReason() );
			return False;
		}

		if( Width > 4096 || Height > 4096 )
		{
			// If fail, don't forget to free raw pixels.
			priv::STBFreeImage( Pixels );
			AE_LogError( "Failed to load " + _FileName + " Reason : Picture' size bigger than 4096" );
			return False;
		}

		// Reserve the memory for the picture.
		AllocatePixelsArray( Cast( Uint32, Width ), Cast( Uint32, Height ), Cast( Uint32, ChannelsCount ) );


		// Copy the raw data to the pixels array.
		CopyPixels( Pixels );

		// Once the copy is done, free the raw data.
		priv::STBFreeImage( Pixels );

		m_FilePath = _FileName;

		return True;
	}

	Bool ImageHDR::LoadFromMemory( const float* _Data, const Uint32 _Width, const Uint32 _Height, const ImageFormat _Format )
	{
		if( _Data == nullptr )
		{
			AE_LogError( "Cannot create image from null data." );
			return False;
		}
		if( _Width > 4096 || _Height > 4096 )
		{
			AE_LogError( "Cannot create image bigger than 4096*4096." );
			return False;
		}

		// Reserve the memory for the picture.
		AllocatePixelsArray( _Width, _Height, Cast( Int32, _Format ) );

		CopyPixels( _Data );

		m_FilePath = "";

		return True;
	}


	void ImageHDR::AllocatePixelsArray( const Uint32 _Width, const Uint32 _Height, const Uint32 _ChannelsCount )
	{
		if( _Width == 0 || _Height == 0 )
		{
			AE_LogError( "Size of an image must be at least 1x1." );
			return;
		}

		if( _Width == m_Width && _Height == m_Height )
			return;

		m_Pixels.resize( Cast( size_t, _Width ) * Cast( size_t, _Height ) * Cast( size_t, _ChannelsCount ) );
		if( m_Pixels.empty() )
		{
			AE_LogError( "Failed to allocate pixel array." );
			return;
		}

		m_Width = _Width;
		m_Height = _Height;
		m_ChannelsCount = _ChannelsCount;
	}

	void ImageHDR::DestroyPixelsArray()
	{
		m_Width = 0;
		m_Height = 0;
		m_ChannelsCount = 0;

		m_Pixels.clear();
	}

	void ImageHDR::CopyPixels( const float* _Pixels )
	{
		std::memcpy( m_Pixels.data(), _Pixels, m_Pixels.size() * sizeof( float ) );
	}

	Color ImageHDR::GetPixelConverted( const Uint32 _Index ) const
	{
		// Get back the pixel fom array.
		const float* PixelPtr = &m_Pixels[Cast( size_t, _Index ) * Cast( size_t, m_ChannelsCount )];

		switch( m_ChannelsCount )
		{
			// GreyScale
		case 1:
			return Color{ PixelPtr[0], PixelPtr[0], PixelPtr[0], 0 };

			// GreyScale + Alpha
		case 2:
			return Color{ PixelPtr[0], PixelPtr[0], PixelPtr[0], PixelPtr[1] };

			// RGB
		case 3:
			return Color{ PixelPtr[0], PixelPtr[1], PixelPtr[2], 0 };

			// RGB + Alpha
		case 4:
			return Color{ PixelPtr[0], PixelPtr[1], PixelPtr[2], PixelPtr[3] };

		default:
			AE_LogError( "Invalid count of channels on the image" );
			return Color::White;
		}
	}

	void ImageHDR::SetPixelConverted( const Uint32 _Index, const Color& _Color )
	{
		// Get back the pixel fom array.
		float* PixelPtr = &m_Pixels[Cast( size_t, _Index ) * Cast( size_t, m_ChannelsCount )];

		Uint8 R = Cast( Uint8, Math::Clamp01( _Color.R() ) * 255.0f );
		Uint8 G = Cast( Uint8, Math::Clamp01( _Color.G() ) * 255.0f );
		Uint8 B = Cast( Uint8, Math::Clamp01( _Color.B() ) * 255.0f );
		Uint8 A = Cast( Uint8, Math::Clamp01( _Color.A() ) * 255.0f );

		switch( m_ChannelsCount )
		{
			// GreyScale
		case 1:
			PixelPtr[0] = Math::Max( R, Math::Max( G, B ) );
			break;

			// GreyScale + Alpha
		case 2:
			PixelPtr[0] = Math::Max( R, Math::Max( G, B ) );
			PixelPtr[1] = A;
			break;

			// RGB
		case 3:
			PixelPtr[0] = R;
			PixelPtr[1] = G;
			PixelPtr[2] = B;
			break;

			// RGB + Alpha
		case 4:
			PixelPtr[0] = R;
			PixelPtr[1] = G;
			PixelPtr[2] = B;
			PixelPtr[3] = A;
			break;

		default:
			AE_LogError( "Invalid count of channels on the image" );
			break;
		}
	}




	const float* ImageHDR::GetData() const
	{
		return m_Pixels.data();
	}


	TexturePixelFormat ImageHDR::GetTexturePixelFormat() const
	{
		switch( m_ChannelsCount )
		{
		case 1:
			return TexturePixelFormat::Red_F32;

		case 2:
			return TexturePixelFormat::RedGreen_F32;

		case 3:
			return TexturePixelFormat::RGB_F32;

		case 4:
			return TexturePixelFormat::RGBA_F32;

		default:
			AE_LogError( "Invalid image format" );
			return TexturePixelFormat::Unknown;
		}
	}


	Bool ImageHDR::SaveToFile( const std::string& _FileName ) const
	{
		Bool Error = priv::STBWriteToHDRFloat( _FileName, *this );

		if( Error )
		{
			AE_LogError( "Failed to save " + _FileName + " Reason : " + priv::STBGetFailureReason() );
			return False;
		}

		return True;
	}


	Bool ImageHDR::Resize( const Uint32 _NewWidth, const Uint32 _NewHeight )
	{
		float* Resized = Cast( float*, malloc( sizeof( float ) * _NewWidth * _NewHeight * m_ChannelsCount ) );

		if( Resized == nullptr )
		{
			AE_LogError( "Failed to allocate memory for the copy." );
			return False;
		}

		Bool Error = priv::STBResize( Resized, _NewWidth, _NewHeight, *this );
		if( Error )
		{
			AE_LogError( std::string( "Failed to resize. Reason : " ) + priv::STBGetFailureReason() );
			return False;
		}

		LoadFromMemory( Resized, _NewWidth, _NewHeight, Cast( ImageFormat, m_ChannelsCount ) );

		free( Resized );

		return True;
	}


	void ImageHDR::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::ImageToEditor( *this );
	}

} // ae
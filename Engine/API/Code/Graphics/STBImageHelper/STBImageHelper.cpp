#include "STBImageHelper.h"

#include "../Image/Image.h"
#include "../Image/ImageHDR.h"

#pragma warning( push )
#pragma warning( disable : 5054 )
#pragma warning( disable : 26812 )
#pragma warning( disable : 6386 )
#pragma warning( disable : 26451 )
#pragma warning( disable : 26453 )
#pragma warning( disable : 6001 )
#pragma warning( disable : 6385 )
#pragma warning( disable : 6011 )
#pragma warning( disable : 6262 )

#define STB_IMAGE_IMPLEMENTATION
#include "../../../../Libraries/STB_Image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../../../Libraries/STB_Image/stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../../../../Libraries/STB_Image/stb_image_resize.h"

#pragma warning( pop )

namespace ae
{
	namespace priv
	{
		Uint8* STBLoadFileUint8( AE_Out Int32& _Width, AE_Out Int32& _Height, AE_Out Int32& _ChannelsCount, const std::string& _FileName )
		{
			return stbi_load( _FileName.c_str(), &_Width, &_Height, &_ChannelsCount, STBI_default );
		}

		float* STBLoadFileFloat( AE_Out Int32& _Width, AE_Out Int32& _Height, AE_Out Int32& _ChannelsCount, const std::string& _FileName )
		{
			return stbi_loadf( _FileName.c_str(), &_Width, &_Height, &_ChannelsCount, STBI_default );
		}


		void STBFreeImage( AE_InOut Uint8*& _Pixels )
		{
			stbi_image_free( _Pixels );
			_Pixels = nullptr;
		}

		void STBFreeImage( AE_InOut float*& _Pixels )
		{
			stbi_image_free( _Pixels );
			_Pixels = nullptr;
		}



		std::string STBGetFailureReason()
		{
			return stbi_failure_reason();
		}


		Bool STBWriteToPngUint8( const std::string& _FileName, const Image& _Image )
		{
			const int Stride = _Image.GetWidth() * _Image.GetChannelsCount() * sizeof( Uint8 );
			return stbi_write_png( _FileName.c_str(), _Image.GetWidth(), _Image.GetHeight(), _Image.GetChannelsCount(), _Image.GetData(), Stride ) == 0;
		}

		Bool STBWriteToHDRFloat( const std::string& _FileName, const ImageHDR& _Image )
		{
			const int Stride = _Image.GetWidth() * _Image.GetChannelsCount() * sizeof( float );
			return stbi_write_hdr( _FileName.c_str(), _Image.GetWidth(), _Image.GetHeight(), _Image.GetChannelsCount(), _Image.GetData() ) == 0;
		}



		Bool STBResize( AE_InOut Uint8* _Resized, Uint32 _NewWidth, Uint32 _NewHeight, const Image& _Image )
		{
			const int Stride = _Image.GetWidth() * _Image.GetChannelsCount() * sizeof( Uint8 );
			const int NewStride = _NewWidth * _Image.GetChannelsCount() * sizeof( Uint8 );

			return stbir_resize_uint8( _Image.GetData(), _Image.GetWidth(), _Image.GetHeight(), Stride, _Resized, _NewWidth, _NewHeight, NewStride, _Image.GetChannelsCount() ) == 0;
		}

		Bool STBResize( AE_InOut float* _Resized, Uint32 _NewWidth, Uint32 _NewHeight, const ImageHDR& _Image )
		{
			const int Stride = _Image.GetWidth() * _Image.GetChannelsCount() * sizeof( float );
			const int NewStride = _NewWidth * _Image.GetChannelsCount() * sizeof( float );

			return stbir_resize_float( _Image.GetData(), _Image.GetWidth(), _Image.GetHeight(), Stride, _Resized, _NewWidth, _NewHeight, NewStride, _Image.GetChannelsCount() ) == 0;
		}
	}

} // ae
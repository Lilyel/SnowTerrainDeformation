#pragma once

#include "../../Toolbox/Toolbox.h"

#include <string>

namespace ae
{
	class Image;
	class ImageHDR;

	namespace priv
	{
		/// <summary>Load an image file with the STB library.</summary>
		/// <param name="_Width">Filled with the image width.</param>
		/// <param name="_Height">Filled with the image heit.</param>
		/// <param name="_ChannelsCount">Filled with the image count of channels.</param>
		/// <param name="_FileName">File to load.</param>
		/// <returns>The pixels loaded. Must be manualy freed.</returns>
		Uint8* STBLoadFileUint8( AE_Out Int32& _Width, AE_Out Int32& _Height, AE_Out Int32& _ChannelsCount, const std::string& _FileName );

		/// <summary>Load an image file with the STB library.</summary>
		/// <param name="_Width">Filled with the image width.</param>
		/// <param name="_Height">Filled with the image heit.</param>
		/// <param name="_ChannelsCount">Filled with the image count of channels.</param>
		/// <param name="_FileName">File to load.</param>
		/// <returns>The pixels loaded. Must be manualy freed.</returns>
		float* STBLoadFileFloat( AE_Out Int32& _Width, AE_Out Int32& _Height, AE_Out Int32& _ChannelsCount, const std::string& _FileName );

		/// <summary>Free the memory taken by the load functions.</summary>
		/// <param name="_Pixels">The memory to free.</param>
		void STBFreeImage( AE_InOut Uint8*& _Pixels );

		/// <summary>Free the memory taken by the load functions.</summary>
		/// <param name="_Pixels">The memory to free.</param>
		void STBFreeImage( AE_InOut float*& _Pixels );

		/// <summary>Retrieve the last error and convert it to a string.</summary>
		/// <returns>The error as string.</returns>
		std::string STBGetFailureReason();


		/// <summary>Save an image to a file.</summary>
		/// <param name="_FileName">The file to save the image into.</param>
		/// <param name="_Image">The image to save.</param>
		/// <returns>True if saved successfully, False otherwise.</returns>
		Bool STBWriteToPngUint8( const std::string& _FileName, const Image& _Image );

		/// <summary>Save an image to a file.</summary>
		/// <param name="_FileName">The file to save the image into.</param>
		/// <param name="_Image">The image to save.</param>
		/// <returns>True if saved successfully, False otherwise.</returns>
		Bool STBWriteToHDRFloat( const std::string& _FileName, const ImageHDR& _Image );

		/// <summary>Resize an image. The <paramref name="_Resized"/> must already been allocated.</summary>
		/// <param name="_Resized">The pixel array resized to fill.</param>
		/// <param name="_NewWidth">The resized width.</param>
		/// <param name="_NewHeight">The resized height.</param>
		/// <param name="_Image">The image to resize.</param>
		/// <returns>True if resized successfully, False otherwise.</returns>
		Bool STBResize( AE_InOut Uint8* _Resized, Uint32 _NewWidth, Uint32 _NewHeight, const Image& _Image );

		/// <summary>Resize an image. The <paramref name="_Resized"/> must already been allocated.</summary>
		/// <param name="_Resized">The pixel array resized to fill.</param>
		/// <param name="_NewWidth">The resized width.</param>
		/// <param name="_NewHeight">The resized height.</param>
		/// <param name="_Image">The image to resize.</param>
		/// <returns>True if resized successfully, False otherwise.</returns>
		Bool STBResize( AE_InOut float* _Resized, Uint32 _NewWidth, Uint32 _NewHeight, const ImageHDR& _Image );

	} // priv

} // ae

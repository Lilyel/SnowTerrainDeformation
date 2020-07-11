#pragma once

#include "../Color/Color.h"
#include "../Texture/TexturePixelFormat.h"
#include "ImageBase.h"
#include "ImageFormat.h"
#include "ImageResizeFilter.h"

#include "../Dependencies/OpenGL.h"

#include <string>
#include <vector>

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Store an array of pixels loaded from an HDR image file.<para/>
	/// </summary>
	/// <seealso cref="Color"/>
	class AERO_CORE_EXPORT ImageHDR : public ImageBase
	{
	public:
		/// <summary>
		/// Create an empty (invalid) image.
		/// </summary>
		ImageHDR();


		/// <summary>
		/// Create a black image.
		/// </summary>
		/// <param name="_Width">The width of the image.</param>
		/// <param name="_Height">The height of the image.</param>
		/// <param name="_Format">The format of the image.</param>
		explicit ImageHDR( const Uint32 _Width, const Uint32 _Height, const ImageFormat _Format );

		/// <summary>Load an image file and store the pixels.</summary>
		/// <param name="_FileName">Name of the image file.</param>
		explicit ImageHDR( const std::string& _FileName );

		/// <summary>Copy constructor.</summary>
		/// <param name="_Copy">The image to copy.</param>
		ImageHDR( const ImageHDR& _Copy );

		/// <summary>If there is an image loaded, free the pixels.</summary>
		virtual ~ImageHDR();

		/// <summary>Copy operator</summary>
		/// <param name="_Copy">The image to copy.</param>
		/// <returns>The calling image with the data of <paramref name="_Copy">.</returns>
		ImageHDR& operator=( const ImageHDR& _Copy );

		/// <summary>Load an image file and store the pixels.</summary>
		/// <param name="_FileName">Name of the image file.</param>
		/// <returns>True if the loaded is completed, False if a problem happened.</returns>
		Bool LoadFromFile( const std::string& _FileName ) override;

		/// <summary>Copy pixels from memory.</summary>
		/// <param name="_Data">The data containing the pixels to copy.</param>
		/// <param name="_Width">The width of the image.</param>
		/// <param name="_Height">The height of the image.</param>
		/// <param name="_Format">The format f the image.</param>
		/// <returns>True if successfully loaded, False otherwise.</returns>
		Bool LoadFromMemory( const float* _Data, const Uint32 _Width, const Uint32 _Height, const ImageFormat _Format );


		/// <summary>Get the raw pixels array.</summary>
		/// <returns>Pixels as an raw array.</returns>
		const float* GetData() const;

		/// <summary>Get the pixel format for setting the textures.</summary>
		/// <returns>Pixel format of the image</returns>
		TexturePixelFormat GetTexturePixelFormat() const override;


		/// <summary>Saves the image to a file.</summary>
		/// <param name="_FileName">Name of the file.</param>
		/// <returns>True if sucessfully saved, False otherwise.</returns>
		Bool SaveToFile( const std::string& _FileName ) const override;

		/// <summary>Resize the image to a new size.</summary>
		/// <param name="_NewWidth">The new width.</param>
		/// <param name="_NewHeight">The new height.</param>
		/// <returns>True if successfully resized, False otherwise.</returns>
		Bool Resize( const Uint32 _NewWidth, const Uint32 _NewHeight ) override;


		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor();

	protected:
		/// <summary>Reserve an array of pixel.</summary>
		/// <param name="_Width">The width of the array to reserve.</param>
		/// <param name="_Height">The height of the array to reserve.</param>
		/// <param name="_ChannelsCount">The number of channels per pixel.</param>
		void AllocatePixelsArray( const Uint32 _Width, const Uint32 _Height, const Uint32 _ChannelsCount );

		/// <summary>If the array is allocated, free it.</summary>
		void DestroyPixelsArray();

		/// <summary>Copies from memory to the image buffer.</summary>
		/// <param name="_Pixels">The pixels to copy.</param>
		void CopyPixels( const float* _Pixels );

		/// <summary>Get the pixel converted from image format (Greyscale, RGB, ... ) to RGBA pixel.</summary>
		/// <param name="_Index">The index of the pixel.</param>
		/// <returns>The pixel as RGBA.</returns>
		Color GetPixelConverted( const Uint32 _Index ) const override;

		/// <summary>Set the pixel of the image format (Greyscale, RGB, ... ) from a RGBA pixel.</summary>
		/// <param name="_Index">The index of the pixel.</param>
		/// <param name="_Color">The color of the pixel to apply as RGBA.</param>
		void SetPixelConverted( const Uint32 _Index, const Color& _Color ) override;

	protected:
		/// <summary>Array of pixels of the image.</summary>
		std::vector<float> m_Pixels;
	};

}; // ae

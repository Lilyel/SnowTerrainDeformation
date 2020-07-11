#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../../Resources/Resource/Resource.h"
#include "../Color/Color.h"
#include "../Texture/TexturePixelFormat.h"
#include "ImageFormat.h"
#include "ImageResizeFilter.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Image basics functionnality that are common to Image and ImageHDR.
	/// </summary>
	/// <seealso cref="Color"/>
	class AERO_CORE_EXPORT ImageBase : public Resource
	{
	public:
		/// <summary>Default constructor.</summary>
		ImageBase();

		/// <summary>Tag destructor for inherited classes.</summary>
		virtual ~ImageBase() = default;


		/// <summary>Load an image file and store the pixels.</summary>
		/// <param name="_FileName">Name of the image file.</param>
		/// <returns>True if the loaded is completed, False if a problem happened.</returns>
		virtual Bool LoadFromFile( const std::string& _FileName ) AE_IsVirtualPure;

		/// <summary>Gets the a particular pixel from the image loaded.</summary>
		/// <param name="_X">The index x of the pixel.</param>
		/// <param name="_Y">The index y of the pixel.</param>
		/// <returns>Color of the pixel at [<paramref name="_X"/>,<paramref name="_Y"/>] coordinates.</returns>
		Color GetPixel( const Uint32 _X, const Uint32 _Y ) const;

		/// <summary>Gets the a particular pixel from the image loaded.</summary>
		/// <param name="_Index">The index of the pixel.</param>
		/// <returns>Color of the pixel at <paramref name="_Index"/>.</returns>
		Color GetPixel( const Uint32 _Index ) const;

		/// <summary>Set the color of a pixel.</summary>
		/// <param name="_X">The index x of the pixel.</param>
		/// <param name="_Y">The index y of the pixel.</param>
		/// <param name="_Color">The new color of the pixel.</param>
		void SetPixel( const Uint32 _X, const Uint32 _Y, const Color& _Color );

		/// <summary>Set the color of a pixel.</summary>
		/// <param name="_Index">The index of the pixel.</param>
		/// <param name="_Color">The new color of the pixel.</param>
		void SetPixel( const Uint32 _Index, const Color& _Color );

		/// <summary>Get the width of the image.</summary>
		/// <returns>Width of the image.</returns>
		Uint32 GetWidth() const;

		/// <summary>Get the height of the image.</summary>
		/// <returns>Height of the image.</returns>
		Uint32 GetHeight() const;

		/// <summary>Get the format of the image ( Greyscale, Greyscale + Alpha, RGB, RGBA )</summary>
		/// <returns>Format of the image</returns>
		ImageFormat GetFormat() const;

		/// <summary>Get the pixel format for setting the textures.</summary>
		/// <returns>Pixel format of the image</returns>
		virtual TexturePixelFormat GetTexturePixelFormat() const AE_IsVirtualPure;

		/// <summary>Get the format of the image for OpenGL ( Greyscale, Greyscale + Alpha, RGB, RGBA )</summary>
		/// <returns>Format of the image for OpenGL.</returns>
		GLenum GetFormatOpenGL() const;

		/// <summary>
		/// Get the image channel count.
		/// 1 for greyscale, 2 for greyscale + alpha,
		/// 3 for RGB and 4 for RGBA.
		/// </summary>
		/// <returns>Image channel count.</returns>
		Uint32 GetChannelsCount() const;

		/// <summary>Saves the image to a file.</summary>
		/// <param name="_FileName">Name of the file.</param>
		/// <returns>True if sucessfully saved, False otherwise.</returns>
		virtual Bool SaveToFile( const std::string& _FileName ) const AE_IsVirtualPure;

		/// <summary>Resize the image to a new size.</summary>
		/// <param name="_NewWidth">The new width.</param>
		/// <param name="_NewHeight">The new height.</param>
		/// <returns>True if successfully resized, False otherwise.</returns>
		virtual Bool Resize( const Uint32 _NewWidth, const Uint32 _NewHeight ) AE_IsVirtualPure;

		/// <summary>
		/// Path to the loaded image.<para/>
		/// Can be empty if image created from memory.
		/// </summary>
		/// <returns></returns>
		const std::string& GetFilePath() const;


	protected:
		/// <summary>Get the pixel converted from image format (Greyscale, RGB, ... ) to RGBA pixel.</summary>
		/// <param name="_Index">The index of the pixel.</param>
		/// <returns>The pixel as RGBA.</returns>
		virtual Color GetPixelConverted( const Uint32 _Index ) const AE_IsVirtualPure;

		/// <summary>Set the pixel of the image format (Greyscale, RGB, ... ) from a RGBA pixel.</summary>
		/// <param name="_Index">The index of the pixel.</param>
		/// <param name="_Color">The color of the pixel to apply as RGBA.</param>
		virtual void SetPixelConverted( const Uint32 _Index, const Color& _Color ) AE_IsVirtualPure;

	protected:
		/// <summary>The width of the image.</summary>
		Uint32 m_Width;
		/// <summary>The height of the image.</summary>
		Uint32 m_Height;

		/// <summary>
		/// Image channels count.
		/// 1 for greyscale, 2 for greyscale + alpha,
		/// 3 for RGB and 4 for RGBA.
		/// </summary>
		Int32 m_ChannelsCount;

		/// <summary>
		/// Path to the loaded file.<para/>
		/// Empty if image created from memory.
		/// </summary>
		std::string m_FilePath;
	};
}
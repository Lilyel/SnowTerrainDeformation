#pragma once

#include "../../Toolbox/Toolbox.h"
#include "Texture2D.h"
#include "../../Maths/Primitives/TRect.h"

namespace ae
{
	class Image;
	class ImageHDR;

	/// \ingroup graphics
	/// <summary>
	/// 2D image that can be link to a shader to be rendered.
	/// </summary>
	/// <seealso cref="Image"/>
	class AERO_CORE_EXPORT TextureImage : public Texture2D
	{
	public:
		/// <summary>Create a texture from a image file.</summary>
		/// <param name="_FilePath">The image file path.</param>
		/// <param name="_SubRect">The area if you want to select only a part of the image.</param>
		TextureImage( const std::string& _FilePath, const IntRect& _SubRect = IntRect() );

		/// <summary>Create a texture from an image.</summary>
		/// <param name="_ImageSource">The image source.</param>
		/// <param name="_SubRect">The area if you want to select only a part of the image.</param>
		TextureImage( const Image& _ImageSource, const IntRect& _SubRect = IntRect() );

		/// <summary>Create a texture from an HDR image.</summary>
		/// <param name="_ImageSource">The image source.</param>
		/// <param name="_SubRect">The area if you want to select only a part of the image.</param>
		TextureImage( const ImageHDR& _ImageSource, const IntRect& _SubRect = IntRect() );


		/// <summary>Create a texture from an image.</summary>
		/// <param name="_FilePath">The path to the image file to load.</param>
		/// <param name="_SubRect">The area if you want to select only a part of the image.</param>
		void Set( const std::string& _FilePath, const IntRect& _SubRect = IntRect() );

		/// <summary>Create a texture from an image.</summary>
		/// <param name="_ImageSource">The image source.</param>
		/// <param name="_SubRect">The area if you want to select only a part of the image.</param>
		void Set( const Image& _ImageSource, const IntRect& _SubRect = IntRect() );

		/// <summary>Create a texture from an HDR image.</summary>
		/// <param name="_ImageSource">The image source.</param>
		/// <param name="_SubRect">The area if you want to select only a part of the image.</param>
		void Set( const ImageHDR& _ImageSource, const IntRect& _SubRect = IntRect() );

		/// <summary>
		/// Path to the loaded image.<para/>
		/// Can be empty if image created from memory.
		/// </summary>
		/// <returns>The file path to the loaded texture.</returns>
		const std::string& GetFilePath() const;


		/// <summary>Called by the framebuffer to attach the texture to it.</summary>
		void AttachToFramebuffer( const FramebufferAttachement& _Attachement ) const override;


		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor();

	private:
		/// <summary>Hide set method of Texture2D.</summary>
		using Texture2D::Set;

		/// <summary>Hide set method of Texture2D.</summary>
		using Texture2D::Resize;

		/// <summary>Update the OpenGL texture data from an image data.</summary>
		/// <param name="_ImageSource">The image source.</param>
		/// <param name="_SubRect">The area to select in the image.</param>
		void UpdateDataFromImage( const Image& _ImageSource, const IntRect& _SubRect );

		/// <summary>Update the OpenGL texture data from an image data.</summary>
		/// <param name="_ImageSource">The image source.</param>
		/// <param name="_SubRect">The area to select in the image.</param>
		void UpdateDataFromImage( const ImageHDR& _ImageSource, const IntRect& _SubRect );


	protected:
		/// <summary>
		/// Path to loaded image.<para/>
		/// Can be a path to an image into the resource manager.
		/// </summary>
		std::string m_FilePath;
	};

} // ae

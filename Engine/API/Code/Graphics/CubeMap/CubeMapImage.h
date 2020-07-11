#pragma once


#include "../../Toolbox/Toolbox.h"
#include "CubeMap.h"
#include "../Image/Image.h"
#include "../Image/ImageHDR.h"

#include <string>
#include <array>
#include <functional>

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// A texture that make a cube (6 sides).<para>
	/// Can be send to shader to process refraction or reflection.<para/>
	/// Can also be used to make a skybox.<para/>
	/// The cubemap is composed of 6 textures, each one attached to a cube face.<para/>
	/// Order : Right, Left, Top, Bottom, Front, Back.
	/// </summary>
	/// <seealso cref="Image"/>
	class AERO_CORE_EXPORT CubeMapImage : public CubeMap
	{
	public:
		/// <summary>
		/// Create a cube from 6 image files.<para/>
		/// If there is one or more nullptr path, the function fail.<para/>
		/// Order : Right, Left, Top, Bottom, Front, Back.
		/// </summary>
		/// <param name="_FilePaths">The images file path.</param>
		/// <param name="_AreHDR">Are the files HDR images ?</param>
		explicit CubeMapImage( const std::array<const std::string*, 6>& _FilePaths, Bool _AreHDR = False );

		/// <summary>
		/// Create a cube from 6 image files.<para/>
		/// Order : Right, Left, Top, Bottom, Front, Back.
		/// </summary>
		/// <param name="_FilePaths">The images file path.</param>
		/// <param name="_AreHDR">Are the files HDR images ?</param>
		explicit CubeMapImage( const std::array<const std::string, 6>& _FilePaths, Bool _AreHDR = False );

		/// <summary>
		/// Create a cube from one image file.<para/>
		/// The texture will be attached to every side of the cube.
		/// </summary>
		/// <param name="_FilePath">The image file path.</param>
		/// <param name="_AreHDR">Are the files HDR images ?</param>
		explicit CubeMapImage( const std::string& _FilePath, Bool _AreHDR = False );


		/// <summary>
		/// Create a texture from 6 images.<para/>
		/// If there is one or more nullptr image, the function fail.<para/>
		/// Order : Right, Left, Top, Bottom, Front, Back.
		/// </summary>
		/// <param name="_ImageSources">The image sources.</param>
		explicit CubeMapImage( const std::array<const Image*, 6>& _ImageSources );

		/// <summary>
		/// Create a texture from 6 images.<para/>
		/// Order : Right, Left, Top, Bottom, Front, Back.
		/// </summary>
		/// <param name="_ImageSources">The image sources.</param>
		explicit CubeMapImage( const std::array<const Image, 6>& _ImageSources );

		/// <summary>
		/// Create a cube from one image.<para/>
		/// The texture will be attached to every side of the cube.
		/// </summary>
		/// <param name="_ImageSource">The image source.</param>
		explicit CubeMapImage( const Image& _ImageSource );


		/// <summary>
		/// Create a texture from 6 images.<para/>
		/// If there is one or more nullptr image, the function fail.<para/>
		/// Order : Right, Left, Top, Bottom, Front, Back.
		/// </summary>
		/// <param name="_ImageSources">The image sources.</param>
		explicit CubeMapImage( const std::array<const ImageHDR*, 6>& _ImageSources );

		/// <summary>
		/// Create a texture from 6 images.<para/>
		/// Order : Right, Left, Top, Bottom, Front, Back.
		/// </summary>
		/// <param name="_ImageSources">The image sources.</param>
		explicit CubeMapImage( const std::array<const ImageHDR, 6>& _ImageSources );

		/// <summary>
		/// Create a cube from one image.<para/>
		/// The texture will be attached to every side of the cube.
		/// </summary>
		/// <param name="_ImageSource">The image source.</param>
		explicit CubeMapImage( const ImageHDR& _ImageSource );


		/// <summary>
		/// Path to the loaded image.<para/>
		/// Can be empty if image created from memory.
		/// </summary>
		/// <param name="_Index">Index of the texture to get the path of.</param>
		/// <returns>The file path to the loaded texture.</returns>
		const std::string& GetFilePath( Uint32 _Index ) const;

		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		void ToEditor() override;

	private:
		using CubeMap::Set;

		/// <summary>Setup the cubemap with 6 images.</summary>
		/// <param name="_ImageSources">The image to attach to each side of the cube.</param>
		void UpdateDataFromImages( std::reference_wrapper<const Image> _ImageSources[6] );

		/// <summary>Setup the cubemap with 6 images.</summary>
		/// <param name="_ImageSources">The image to attach to each side of the cube.</param>
		void UpdateDataFromImages( std::reference_wrapper<const ImageHDR> _ImageSources[6] );


	private:
		/// <summary>
		/// Paths to loaded images.<para/>
		/// Can be a path to images into the resource manager.<para/>
		/// There is path per cube side.
		/// </summary>
		std::string m_FilePath[6];
	};

} // ae

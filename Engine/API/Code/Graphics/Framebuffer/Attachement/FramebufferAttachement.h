#pragma once

#include "../../../Toolbox/Toolbox.h"
#include "../../Dependencies/OpenGL.h"
#include "../../Texture/TexturePixelFormat.h"
#include "../../Texture/TextureFilterMode.h"
#include "../../Texture/TextureDimension.h"

#include <string>
#include <limits>

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Setting for framebuffer attachement (color, depth, stencil, ...).<para/>
	/// Note that if you send several attachement of the same type only the first will be taken.<para/>
	/// Depth and DepthStencil are not stackable either.
	/// </summary>
	class AERO_CORE_EXPORT FramebufferAttachement
	{
	public:
		/// <summary>
		/// Possible types of attachement.
		/// </summary>
		enum class Type : Uint32
		{
			Color_0 = GL_COLOR_ATTACHMENT0,
			Color_1 = GL_COLOR_ATTACHMENT1,
			Color_2 = GL_COLOR_ATTACHMENT2,
			Color_3 = GL_COLOR_ATTACHMENT3,
			Color_4 = GL_COLOR_ATTACHMENT4,
			Color_5 = GL_COLOR_ATTACHMENT5,
			Color_6 = GL_COLOR_ATTACHMENT6,
			Color_7 = GL_COLOR_ATTACHMENT7,
			Color_8 = GL_COLOR_ATTACHMENT8,
			Color_9 = GL_COLOR_ATTACHMENT9,
			Color_10 = GL_COLOR_ATTACHMENT10,
			Color_11 = GL_COLOR_ATTACHMENT11,
			Color_12 = GL_COLOR_ATTACHMENT12,
			Color_13 = GL_COLOR_ATTACHMENT13,
			Color_14 = GL_COLOR_ATTACHMENT14,
			Color_15 = GL_COLOR_ATTACHMENT15,

			Depth = GL_DEPTH_ATTACHMENT,
			DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT,

			None = std::numeric_limits<Uint32>::max()
		};

	public:
		/// <summary>Store 2D attachement settings to be given to a framebuffer later.</summary>
		/// <param name="_Type">Type of the attachement.</param>
		/// <param name="_Format">Format of the pixels (channel, types, ...) for attachements.</param>
		/// <param name="_Filter">Filter for the attachements.</param>
		/// <param name="_Dimension">Dimension for the attachements.</param>
		FramebufferAttachement( Type _Type,
								TexturePixelFormat _Format = TexturePixelFormat::DefaultTexture,
								TextureFilterMode _Filter = TextureFilterMode::Linear,
								TextureDimension _Dimension = TextureDimension::Texture2D );

		/// <summary>
		/// Store 2D attachement settings to be given to a framebuffer later.<para/>
		/// Special case for multi sample : the attachement will be a 2D texture.<para/>
		/// If the samples count is 0 or 1, the texture will not be multi sample but will still be a 2D texture.
		/// </summary>
		/// <param name="_Type">Type of the attachement.</param>
		/// <param name="_SamplesCount">Number of sample for multi sample texture. 0 or 1 mean no multi sampling.</param>
		/// <param name="_Format">Format of the pixels (channel, types, ...) for attachements.</param>
		/// <param name="_Filter">Filter for the attachements.</param>
		explicit FramebufferAttachement( Type _Type,
										 Uint32 _SamplesCount,
										 TexturePixelFormat _Format = TexturePixelFormat::DefaultTexture,
										 TextureFilterMode _Filter = TextureFilterMode::Linear );

		/// <summary>Get the color format for "internal format" parameter in OpenGL calls.</summary>
		/// <returns>The OpenGL value that correspond to the color format of the attachement.</returns>
		GLint GetGLInternalFormat() const;

		/// <summary>Get the color format for "format" parameter in OpenGL calls.</summary>
		/// <returns>The OpenGL value that correspond to the color format of the attachement.</returns>
		GLenum GetGLFormat() const;

		/// <summary>Get the type format for "type" parameter in OpenGL calls.</summary>
		/// <returns>The OpenGL value that correspond to the type format of the attachement.</returns>
		GLenum GetGLType() const;

		/// <summary>Get the color filter for "param" parameter in OpenGL calls.</summary>
		/// <returns>The OpenGL value that correspond to the filter of the attachement.</returns>
		GLint GetGLFilter() const;

		/// <summary>Get the attachement for "attachement" parameter in OpenGL calls.</summary>
		/// <returns>The OpenGL value that correspond to the attachement type.</returns>
		GLenum GetGLAttachement() const;

		/// <summary>Set the current format of the attachement.</summary>
		/// <param name="_Format">The format to apply.</param>
		void SetFormat( TexturePixelFormat _Format );

		/// <summary>Retrieve the pixel format of the attachement.</summary>
		/// <returns>The attachement format.</returns>
		TexturePixelFormat GetFormat() const;

		/// <summary>Set the current filter of the attachement.</summary>
		/// <param name="_FilterMode">The filter to apply.</param>
		void SetFilter( TextureFilterMode _FilterMode );

		/// <summary>Retrieve the filter for the attachement.</summary>
		/// <returns>The filter.</returns>
		TextureFilterMode GetFilter() const;
		
		/// <summary>Set the dimension for the attachement</summary>
		/// <param name="_Dimension">The dimension to apply.</param>
		void SetDimension( TextureDimension _Dimension );

		/// <summary>Retrieve the dimension of the attachement.</summary>
		/// <returns>The dimension of the attachement.</returns>
		TextureDimension GetDimension() const;

		/// <summary>Set the number of samples in case of 2D mutli sample texture.</summary>
		/// <param name="_SamplesCount">The count of samples to apply.</param>
		void SetSamplesCount( Uint32 _SamplesCount );

		/// <summary>The number of samples for the texture in case of 2D mutli sample texture.</summary>
		/// <returns>The number of samples for multi sample texture.</returns>
		Uint32 GetSamplesCount() const;

		/// <summary>Retrieve the type of the attachement.</summary>
		/// <returns>The type of the attachement.</returns>
		Type GetType() const;

		/// <summary>Is the attachement is a color attachement ?</summary>
		/// <returns>True if it is a color attachement, False otherwise.</returns>
		Bool IsColorAttachement() const;

		/// <summary>Is the attachement is a depth or depth/stencil attachement ?</summary>
		/// <returns>True if it is a depth or depth/stencil attachement, False otherwise.</returns>
		Bool IsDepthAttachement() const;

		/// <summary>Is the attachement is a valid attachement ?</summary>
		/// <returns>True if it is valid attachement, False otherwise.</returns>
		Bool IsInvalidAttachement() const;

		/// <summary>Is the attachement is a color attachement ?</summary>
		/// <param name="_Type">Type of attachement to check.</param>
		/// <returns>True if it is a color attachement, False otherwise.</returns>
		static Bool IsColorAttachement( Type _Type );

		/// <summary>Is the attachement is a depth or depth/stencil attachement ?</summary>
		/// <param name="_Type">Type of attachement to check.</param>
		/// <returns>True if it is a depth or depth/stencil attachement, False otherwise.</returns>
		static Bool IsDepthAttachement( Type _Type );

		/// <summary>Is the attachement is a valid attachement ?</summary>
		/// <param name="_Type">Type of attachement to check.</param>
		/// <returns>True if it is valid attachement, False otherwise.</returns>
		static Bool IsInvalidAttachement( Type _Type );

		/// <summary>Convert the type to a string. Mostly editor purpose.</summary>
		/// <returns>The type as string.</returns>
		std::string TypeToString() const;

	private:
		/// <summary>Type of the attachement.</summary>
		Type m_Type;

		/// <summary>Type of the datas.</summary>
		TexturePixelFormat m_Format;

		/// <summary>Filter for the attachements.</summary>
		TextureFilterMode m_Filter;

		/// <summary>Dimension of the attachement.</summary>
		TextureDimension m_Dimension;

		/// <summary>Count of samples in case of multi samples 2D texture.</summary>
		Uint32 m_SamplesCount;
	};

	/// <summary>Convert the type to a string. Mostly editor purpose.</summary>
	/// <param name="_Type">The attachement type to convert.</param>
	/// <returns>The type as string.</returns>
	AERO_CORE_EXPORT inline std::string ToString( FramebufferAttachement::Type _Type );

} // ae

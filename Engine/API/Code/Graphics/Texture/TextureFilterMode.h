#pragma once

#include "../../Toolbox/Types.h"
#include "../Dependencies/OpenGL.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>When the texture will be sampled, determine how to chose the pixel color.</summary>
	/// <remarks>https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexParameter.xhtml</remarks>
	enum class TextureFilterMode : Int32
	{
		/// <summary>Nearest pixel ( Manhattan distance ).</summary>
		Nearest = GL_NEAREST,

		/// <summary>Average of the four neighboor ( more smooth ).</summary>
		Linear = GL_LINEAR,

		/// <summary>Chooses the mipmap that most closely matches the size of the pixel being textured and uses the GL_NEAREST criterion.</summary>
		Nearest_MipMap_Nearest = GL_NEAREST_MIPMAP_NEAREST,

		/// <summary>Chooses the two mipmaps that most closely match the size of the pixel being textured and uses the GL_NEAREST criterion.</summary>
		Nearest_MipMap_Linear = GL_NEAREST_MIPMAP_LINEAR,

		/// <summary>Chooses the mipmap that most closely matches the size of the pixel being textured and uses the GL_LINEAR criterion.</summary>
		Linear_MipMap_Nearest = GL_LINEAR_MIPMAP_NEAREST,

		/// <summary>Chooses the two mipmaps that most closely match the size of the pixel being textured and uses the GL_LINEAR criterion.</summary>
		Linear_MipMap_Linear = GL_LINEAR_MIPMAP_LINEAR
	};
}

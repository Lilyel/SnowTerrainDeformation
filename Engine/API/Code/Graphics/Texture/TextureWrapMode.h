#pragma once

#include "../../Toolbox/Types.h"
#include "../Dependencies/OpenGL.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>Determine how the texture coordinates will be processed when they are outside of [0, 1].</summary>
	/// <remarks>https://learnopengl.com/#!Getting-started/Textures</remarks>
	enum class TextureWrapMode : Int32
	{
		/// <summary>Repeats the texture image.</summary>
		Repeat = GL_REPEAT,

		/// <summary>Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.</summary>
		ClampToEdge = GL_CLAMP_TO_EDGE,

		/// <summary>Coordinates outside the range are now given a user-specified border color.</summary>
		ClampToBorder = GL_CLAMP_TO_BORDER,

		/// <summary>Same as Repeat but mirrors the image with each repeat.</summary>
		MirroredRepeat = GL_MIRRORED_REPEAT,

		/// <summary>Same as MirroredRepeat but for one time.</summary>
		MirroredClampToEdge = GL_MIRROR_CLAMP_TO_EDGE
	};
} 

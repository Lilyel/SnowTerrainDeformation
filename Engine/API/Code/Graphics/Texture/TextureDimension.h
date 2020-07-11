#pragma once

#include "../../Toolbox/Types.h"
#include "../Dependencies/OpenGL.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>Dimension of the texture 1D (simple array), 2D (image), 3D (volume, layered image).</summary>
	enum class TextureDimension : Int32
	{
		/// <summary>1D texture.</summary>
		Texture1D = GL_TEXTURE_1D,

		/// <summary>1D texture array.</summary>
		Texture1DArray = GL_TEXTURE_1D_ARRAY,

		/// <summary>2D texture.</summary>
		Texture2D = GL_TEXTURE_2D,

		/// <summary>2D multi sample texture.</summary>
		Texture2DMultiSample = GL_TEXTURE_2D_MULTISAMPLE,

		/// <summary>2D texture rectangle.</summary>
		Texture2DRect = GL_TEXTURE_RECTANGLE,

		/// <summary>2D texture array.</summary>
		Texture2DArray = GL_TEXTURE_2D_ARRAY,

		/// <summary>3D texture.</summary>
		Texture3D = GL_TEXTURE_3D,
		
		/// <summary>Cube map texture.</summary>
		CubeMap = GL_TEXTURE_CUBE_MAP
	};
}

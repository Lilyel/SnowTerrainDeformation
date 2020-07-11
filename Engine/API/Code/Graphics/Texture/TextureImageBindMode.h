#pragma once

#include "../../Toolbox/Types.h"
#include "../Dependencies/OpenGL.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>Determine the access mode of texture bound as image.</summary>
	enum class TextureImageBindMode : GLenum
	{
		/// <summary>Read only access.</summary>
		ReadOnly = GL_READ_ONLY,

		/// <summary>Write only access.</summary>
		WriteOnly = GL_WRITE_ONLY,

		/// <summary>Read and write access.</summary>
		ReadWrite = GL_READ_WRITE
	};
}

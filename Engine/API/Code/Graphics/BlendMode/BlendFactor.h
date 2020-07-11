#pragma once

#include "../Dependencies/OpenGL.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Factors for blending mode. 
	/// 's' is for source and 'd' for destination.
	/// 'R' is for red, 'G' for greeen, 'B' for blue and 'A' for alpha.
	/// </summary>
	enum class BlendFactor : GLenum
	{
		/// <summary>(0,0,0,0)</summary>
		Zero = GL_ZERO,

		/// <summary>(1,1,1,1)</summary>
		One = GL_ONE,


		/// <summary>(Rs, Gs, Bs, As)</summary>
		SourceColor = GL_SRC_COLOR,

		/// <summary>(1,1,1,1) - (Rs, Gs, Bs, As) </summary>
		OneMinusSourceColor = GL_ONE_MINUS_SRC_COLOR,

		/// <summary>(Rd, Gd, Bd, Ad)</summary>
		DestinationColor = GL_DST_COLOR,

		/// <summary>(1,1,1,1) - (Rd, Gd, Bd, Ad)</summary>
		OneMinusDestinationColor = GL_ONE_MINUS_DST_COLOR,


		/// <summary>(As, As, As, As)</summary>
		SourceAlpha = GL_SRC_ALPHA,

		/// <summary>(1,1,1,1) - (As, As, As, As)</summary>
		OneMinusSourceAlpha = GL_ONE_MINUS_SRC_ALPHA,

		/// <summary>(Ad, Ad, Ad, Ad)</summary>
		DestinationAlpha = GL_DST_ALPHA,

		/// <summary>(1,1,1,1) - (Ad, Ad, Ad, Ad)</summary>
		OneMinusDestinationAlpha = GL_ONE_MINUS_DST_ALPHA,

		/// <summary>(Ad, Ad, Ad, 1)</summary>
		SourceAlphaSaturate = GL_SRC_ALPHA_SATURATE
	};
} // ae

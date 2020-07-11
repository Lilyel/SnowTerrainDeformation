#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Dependencies/OpenGL.h"


namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Depth mode to apply to renderers (Less, Less or equal, no depth test, ...).
	/// </summary>
	enum class DepthMode : GLenum
	{
		/// <summary>Disable depth test.</summary>
		NoDepthTest = 0,

		/// <summary>Never passes.</summary>
		Never = GL_NEVER,

		/// <summary>Passes if the incoming z value is less than the stored z value.</summary>
		Less = GL_LESS,

		/// <summary>Passes if the incoming z value is less than or equal to the stored z value.</summary>
		LessEqual = GL_LEQUAL,

		/// <summary>Passes if the incoming z value is equal to the stored z value.</summary>
		Equal = GL_EQUAL,

		/// <summary>Passes if the incoming z value is not equal to the stored z value.</summary>
		NotEqual = GL_NOTEQUAL,

		/// <summary>Passes if the incoming z value is greater than or equal to the stored z value.</summary>
		GreaterEqual = GL_GEQUAL,

		/// <summary>Passes if the incoming z value is greater than the stored z value.</summary>
		Greater = GL_GREATER,

		/// <summary>Always passes.</summary>
		Always = GL_ALWAYS,

		/// <summary>Default DepthMode value for renderer.</summary>
		Default = LessEqual,


		/// <summary>Invalid depth mode. For internal use only.</summary>
		Unknown

	};
}

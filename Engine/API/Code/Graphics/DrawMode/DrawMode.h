#pragma once


#include "../../Toolbox/Toolbox.h"
#include "../Dependencies/OpenGL.h"


namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Draw mode to apply to renderers (wireframe, filled, ...).
	/// </summary>
	enum class DrawMode : GLenum
	{
		/// <summary>
		/// Default draw mode, faces will be filled.
		/// </summary>
		Filled,

		/// <summary>
		/// Wireframe draw mode, faces will not be filled, only the edges will be visible.
		/// </summary>
		Wireframe,

		/// <summary>
		/// Points draw mode, faces and edges will not be filled, only the points will be visible.
		/// </summary>
		Points,


		/// <summary>Invalid draw mode. For internal use only.</summary>
		Unknown
	};

	/// <summary>Convert a draw mode enum value to a string.</summary>
	/// <param name="_Mode">The draw mode value to convert.</param>
	/// <returns>Draw mode as a C++ string.</returns>
	AERO_CORE_EXPORT inline std::string ToString( DrawMode _Mode )
	{
		switch( _Mode )
		{
		case ae::DrawMode::Filled:
			return "Filled";

		case ae::DrawMode::Wireframe:
			return "Wireframe";

		case ae::DrawMode::Points:
			return "Points";

		default:
			return "Unknown DrawMode";
		}
	}
}
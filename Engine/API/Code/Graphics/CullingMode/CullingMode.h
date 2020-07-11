#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Dependencies/OpenGL.h"


namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Culling mode to apply to renderers (cull back faces, front faces, ...).
	/// </summary>
	enum class CullingMode : GLenum
	{
		/// <summary>
		/// No face culling.
		/// </summary>
		NoCulling,

		/// <summary>
		/// Default value. <para/>
		/// The faces that don't face the camera will not be drawn.
		/// </summary>
		BackFaces,

		/// <summary>
		/// The faces that face the camera will not be drawn.
		/// </summary>
		FrontFaces,

		/// <summary>
		/// The faces that face and don't face the camera will not be drawn.
		/// </summary>
		BackAndFrontFaces,


		/// <summary>Invalid culling mode. For internal use only.</summary>
		Unknown
	};

	/// <summary>Convert a culling mode enum value to a string.</summary>
	/// <param name="_Mode">The culling mode value to convert.</param>
	/// <returns>Culling mode as a C++ string.</returns>
	AERO_CORE_EXPORT inline std::string ToString( CullingMode _Mode )
	{
		switch( _Mode )
		{
		case CullingMode::NoCulling:
			return "No Culling";

		case CullingMode::BackFaces:
			return "Back Faces";

		case CullingMode::FrontFaces:
			return "Front Faces";

		case CullingMode::BackAndFrontFaces:
			return "Back And Front Faces";

		case CullingMode::Unknown:
		default:
			return "Unknown CullingMode";
		}
	}
}

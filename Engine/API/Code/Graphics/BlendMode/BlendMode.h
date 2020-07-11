#ifndef _BLENDMODE_AERO_H_
#define _BLENDMODE_AERO_H_

#include "../../Toolbox/Toolbox.h"
#include "../Dependencies/OpenGL.h"
#include "BlendFactor.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Blending mode for rendering.
	/// Determine how the draw pixels while be processed with the existing ones.
	/// </summary>
	class AERO_CORE_EXPORT BlendMode
	{
	public:
		/// <summary>Create a blend mode with the corresponding factor.</summary>
		/// <param name="_SourceFactor">The source blending factor.</param>
		/// <param name="_DestinationFactor">The destination blending factor.</param>
		BlendMode( BlendFactor _SourceFactor, BlendFactor _DestinationFactor );

		/// <summary>The source for the pixel blending.</summary>
		BlendFactor SourceFactor;
		/// <summary>The destination for the pixel blending.</summary>
		BlendFactor DestinationFactor;


	public:
		/// <summary>Classic alpha blending. Allow to handle transprancy.</summary>
		static const BlendMode BlendAlpha;
		/// <summary>The new pixel will be add to the hold one.</summary>
		static const BlendMode BlendAdd;
		/// <summary>The new pixel will be multiplied to the hold one.</summary>
		static const BlendMode BlendMultiply;
		/// <summary>No blending, it will be the new pixel that will be drawn (override).</summary>
		static const BlendMode BlendNone;
        /// <summary>The new pixel will be substracted to the hold one.</summary>
        static const BlendMode BlendSubstract;
	};

} // ae

#endif // _BLENDMODE_AERO_H_
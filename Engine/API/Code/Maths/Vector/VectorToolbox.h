#pragma once

#include "../../Toolbox/Toolbox.h"

namespace ae
{
	/// \ingroup math
	/// <summary>Allow to specify in which range the Angle functions need to return the angle.</summary>
	enum class VectorAngleRange : Uint8
	{
        /// <summary>Angle will be in [0, PI] and [-PI, 0] range.</summary>
		Signed_0_PI,

        /// <summary>Angle will be in [0, PI] range.</summary>
		Unsigned_0_PI,

        /// <summary>Angle will be in [0, 2 * PI] range.</summary>
		Unsigned_0_2PI
	};

    /// \ingroup math
    /// <summary>
    /// Allow to specify a specific algorithm to process the length of a vector.
    /// </summary>
    /// <remarks>https://en.wikipedia.org/wiki/Distance https://en.wikipedia.org/wiki/Minkowski_distance </remarks>
    enum class VectorLength : Uint8
    {
        /// <summary> 
        /// Also called L1 norm, Taxicab norm or Manhattan distance.
        /// </summary>
        /// <remarks>\f$ \sum{\lvert x_i - y_i \rvert} \f$</remarks>
        Norm_1, 

        /// <summary> 
        /// Also called L2 norm or Euclidean distance. 
        /// </summary>
        /// <remarks>\f$\sqrt{\sum{\lvert x_i - y_i \rvert ^{2} } }\f$ or \f$(\sum{\lvert x_i - y_i \rvert ^{2}})^{1/2}\f$</remarks>
        Norm_2,

        /// <summary>
        /// Also called Lp norm. 
        /// </summary>
        /// <remarks>\f$(\sum{\lvert x_i - y_i \rvert ^{2}})^{1/p} \f$</remarks>
        Norm_p,

        /// <summary>
        /// Also called Chebyshev distance.
        /// </summary>
        /// <remarks>\f$ \max{\lvert x_i - y_i \rvert} \f$</remarks>
        Norm_infinite
    };

	namespace priv
	{
		namespace VectorToolbox
		{
			/// <summary>Convert and angle in radians to the wanted format.</summary>
			/// <param name="_Angle">(Input and output of the function) Angle to convert.</param>
			/// <param name="_AngleRange">Format to apply to <paramref name="_Angle"/>.</param>
			AERO_CORE_EXPORT inline void ProcessAngleRange( AE_InOut float& _Angle, const VectorAngleRange _AngleRange );

		} // VectorToolbox

	} // priv

} // ae


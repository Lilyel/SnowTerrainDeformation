#include "VectorToolbox.h"

#include "../Functions/MathsFunctions.h"


namespace ae
{
	namespace priv
	{
		namespace VectorToolbox
		{
			void ProcessAngleRange( AE_InOut float& _Angle, const VectorAngleRange _AngleRange )
			{
				// Angle range is supposed to be Signed_0_PI by default.

				if( _AngleRange == VectorAngleRange::Unsigned_0_PI )
					_Angle = Math::Abs( _Angle );

				else if( _AngleRange == VectorAngleRange::Unsigned_0_2PI && _Angle < 0.0f )
					_Angle += Math::PiMulBy2();
			}

		} // VectorToolbox

	} // priv

} // ae
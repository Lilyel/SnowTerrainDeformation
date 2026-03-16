#include "BlendMode.h"

namespace ae
{
	const BlendMode BlendMode::BlendAlpha = BlendMode( BlendFactor::SourceAlpha, BlendFactor::OneMinusSourceAlpha );
	const BlendMode BlendMode::BlendAdd = BlendMode( BlendFactor::SourceAlpha, BlendFactor::One );
	const BlendMode BlendMode::BlendMultiply = BlendMode( BlendFactor::DestinationColor, BlendFactor::Zero );
	const BlendMode BlendMode::BlendNone = BlendMode( BlendFactor::One, BlendFactor::Zero );
    const BlendMode BlendMode::BlendSubstract = BlendMode( BlendFactor::OneMinusDestinationColor, BlendFactor::OneMinusSourceColor);

	BlendMode::BlendMode( BlendFactor _SourceFactor, BlendFactor _DestinationFactor ) :
		SourceFactor( _SourceFactor ),
		DestinationFactor( _DestinationFactor )
	{
	}

} // ae
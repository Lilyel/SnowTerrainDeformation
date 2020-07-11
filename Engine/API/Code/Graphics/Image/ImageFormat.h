#pragma once

#include "../../Toolbox/Toolbox.h"

namespace ae
{

	/// <summary>Color format of the picture.</summary>
	enum class ImageFormat : Uint8
	{
		/// <summary>Only one channel representing gray intensity.</summary>
		GeyScale = 1,
		/// <summary>Two channel representing gray intensity and alpha (transparency).</summary>
		GreyScale_Alpha = 2,
		/// <summary>Three channel representing red, blue and green intensity.</summary>
		RGB = 3,
		/// <summary>Four channel representing red, blue and green intensity and alpha (transparency).</summary>
		RGB_Alpha = 4
	};

}
#pragma once

#include "../../Toolbox/Toolbox.h"

namespace ae
{

	/// <summary>Algorithm used when resizing the image.</summary>
	enum class ImageResizeFilter : Uint8
	{
		/// <summary>Default algorithm (Catmull Rom or Mitchell depending if we upscaling or downscaling).</summary>
		Default = 0,

		/// <summary>"Box filter" : takes the same color as the neighbors.</summary>
		NearestNeighbour = 1,

		/// <summary>Billinear interpolation.</summary>
		Bilinear = 2,

		/// <summary>Cubic B-Spline interpolation. ("aka Mitchell-Netrevalli with B=1,C=0")</summary>
		CubicSpline = 3,

		/// <summary>Cubic B-Spline interpolation. ("aka Mitchell-Netrevalli with B=1,C=0")</summary>
		CatmullRom = 4,

		/// <summary>Mitchell interpolation. ("Mitchell-Netrevalli filter with B=1/3, C=1/3")</summary>
		Mitchell = 5
	};

}
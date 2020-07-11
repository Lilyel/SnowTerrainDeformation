#pragma once

#pragma once

#include "../../Graphics/PostProcess/GammaCorrection.h"
#include "../../Maths/Functions/MathsFunctions.h"
#include "../../UI/Dependencies/IncludeImGui.h"


namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void GammaCorrectionToEditor( GammaCorrection& _GammaCorrection )
			{
				ImGui::Text( "Gamma Correction" );

				float Exposure = _GammaCorrection.GetExposure();
				if( ImGui::DragFloat( "Exposure", &Exposure, 0.1f ) )
					_GammaCorrection.SetExposure( Exposure );

				float Gamma = _GammaCorrection.GetGamma();
				if( ImGui::DragFloat( "Gamma", &Gamma, 0.1f, Math::Epsilon(), Math::Max<float>() ) )
					_GammaCorrection.SetGamma( Gamma );

				ImGui::Separator();
			}
		}

	} // priv

} // ae

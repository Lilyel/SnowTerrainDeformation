#pragma once

#include "../../Graphics/Light/SpotLight/SpotLight.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void SpotLightToEditor( SpotLight& _SpotLight )
            {
                float InnerAngle = _SpotLight.GetInnerAngle();
                ImGui::SliderAngle( "Inner Angle", &InnerAngle, 0.0f, 89.0f );
                _SpotLight.SetInnerAngle( InnerAngle );

                float OuterAngle = _SpotLight.GetOuterAngle();
                ImGui::SliderAngle( "Outer Angle", &OuterAngle, 1.0f, 89.0f );
                _SpotLight.SetOuterAngle( OuterAngle );

                float Range = _SpotLight.GetRange();
                ImGui::DragFloat( "Range", &Range, 1.0f, 0.0f, std::numeric_limits<float>::max() );
                _SpotLight.SetRange( Range );
            }
        }

    } // priv

} // ae

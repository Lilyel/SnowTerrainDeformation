#pragma once

#pragma once

#include "../../Graphics/Light/PointLight/PointLight.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void PointLightToEditor( PointLight& _PointLight )
            {
                float Radius = _PointLight.GetRadius();
                ImGui::DragFloat( "Radius", &Radius, 1.0f, Math::Epsilon(), std::numeric_limits<float>::max() );
                _PointLight.SetRadius( Radius );
            }
        }

    } // priv

} // ae


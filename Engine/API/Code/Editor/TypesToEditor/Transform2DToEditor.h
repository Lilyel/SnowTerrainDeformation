#pragma once

#pragma once

#include "../../Maths/Functions/MathsFunctions.h"
#include "../../Maths/Transform/Transform2D.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void TransformToEditor( Transform2D& _Object )
            {
                ImGui::Text( "Transform" );

                Vector2 Position = _Object.GetPosition();
                ImGui::DragFloat2( "Position", &Position.X );
                _Object.SetPosition( Position );

                float Rotation = _Object.GetRotation();
                Rotation = Math::RadToDeg( Rotation );
                ImGui::DragFloat( "Rotation", &Rotation );
                _Object.SetRotation( Math::DegToRad( Rotation ) );

                Vector2 Scale = _Object.GetScale();
                ImGui::DragFloat2( "Scale", &Scale.X );
                _Object.SetScale( Scale );

                Vector2 Origin = _Object.GetOrigin();
                ImGui::DragFloat2( "Origin", &Origin.X );
                _Object.SetOrigin( Origin );

                ImGui::Separator();
            }
        }

    } // priv

} // ae


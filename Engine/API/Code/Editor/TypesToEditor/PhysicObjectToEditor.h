#pragma once

#include "../../Physics/PhysicObject/PhysicObject.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void PhysicObjectToEditor( PhysicObject& _PhysicObject )
            {
                ImGui::Text( "Physic Object" );

                bool ApplyPhysics = _PhysicObject.DoApplyPhysics();
                ImGui::Checkbox( "Apply Physics", &ApplyPhysics );
                _PhysicObject.SetApplyPhysics( ApplyPhysics );

                bool ApplyGravity = _PhysicObject.DoApplyGravity();
                ImGui::Checkbox( "Apply Gravity", &ApplyGravity );
                _PhysicObject.SetApplyGravity( ApplyGravity );

                bool ApplyAirResistance = _PhysicObject.DoApplyAirResistance();
                ImGui::Checkbox( "Apply Air Resistance", &ApplyAirResistance );
                _PhysicObject.SetApplyAirResistance( ApplyAirResistance );

                bool ApplyGlobalWind = _PhysicObject.DoApplyGlobalWind();
                ImGui::Checkbox( "Apply Global Wind", &ApplyGlobalWind );
                _PhysicObject.SetApplyGlobalWind( ApplyGlobalWind );

                float Mass = _PhysicObject.GetMass();
                ImGui::DragFloat( "Mass", &Mass, 1.0f, Math::Epsilon(), std::numeric_limits<float>::max() );
                _PhysicObject.SetMass( Mass );

                float AirResistance = _PhysicObject.GetAirResistance();
                ImGui::DragFloat( "Air Resistance", &AirResistance, 1.0f, 0.0f, std::numeric_limits<float>::max() );
                _PhysicObject.SetAirResistance( AirResistance );

                Vector3 Velocity = _PhysicObject.GetVelocity();
                ImGui::InputFloat3( "Velocity", &Velocity.X, 3, ImGuiInputTextFlags_ReadOnly );

                Vector3 Acceleration = _PhysicObject.GetAcceleration();
                ImGui::InputFloat3( "Acceleration", &Acceleration.X, 3, ImGuiInputTextFlags_ReadOnly );

                Vector3 Forces = _PhysicObject.GetForces();
                ImGui::InputFloat3( "Forces", &Forces.X, 3, ImGuiInputTextFlags_ReadOnly );

                ImGui::Separator();
            }
        }

    } // priv

} // ae

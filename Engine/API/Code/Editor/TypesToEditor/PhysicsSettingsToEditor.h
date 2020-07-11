#pragma once


#include "../../Physics/Settings/PhysicsSettings.h"
#include "../../Maths/Functions/MathsFunctions.h"
#include "../../Aero/Aero.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void PhysicsSettingsToEditor( PhysicsSettings& _PhysicsSettings )
            {
                ImGui::Text( "Physics Settings" );


                std::string Integrators[3] = { "Euler", "Euler Ending Velocity", "Euler Average Velocity" };
                Uint8 Integrator = ae::Math::Clamp( Cast( Uint8, 0 ), Cast( Uint8, 3 ), Cast( Uint8, _PhysicsSettings.Integrator ) );

                if( ImGui::BeginCombo( "Integration Method", Integrators[Integrator].c_str() ) )
                {
                    Bool IsSelected = False;
                    for( Uint8 p = 0; p < 3; p++ )
                    {
                        IsSelected = p == Integrator;
                        if( ImGui::Selectable( Integrators[p].c_str(), &IsSelected ) )
                            Integrator = p;

                        if( IsSelected )
                            ImGui::SetItemDefaultFocus();
                    }

                    ImGui::EndCombo();
                }

                _PhysicsSettings.Integrator = Cast( PhysicsSettings::IntegrationMethod, Integrator );

                ImGui::DragFloat3( "Gravity", &_PhysicsSettings.Gravity.X );

                ImGui::DragFloat3( "Global Wind", &_PhysicsSettings.GlobalWind.X );

                int FixedFrameRate = Cast( int, _PhysicsSettings.FixedFrameRate );
                ImGui::SliderInt( "Fixed Frame Rate", &FixedFrameRate, 1, 100 );
                _PhysicsSettings.FixedFrameRate = Cast( Uint32, FixedFrameRate );

                ImGui::Separator();
            }
        }

    } // priv

} // ae

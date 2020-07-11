#pragma once

#include "../../Graphics/Camera/Camera.h"
#include "../../Graphics/Camera/CameraOrthographic.h"
#include "../../Graphics/Camera/CameraPerspective.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void CameraToEditor( Camera& _Camera )
            {
                // Control

                std::string ControlTypes[3] = { "Free", "FPS", "Orbit" };
                Uint8 ControlType = Math::Clamp( Cast( Uint8, 0 ), Cast( Uint8, 3 ), Cast( Uint8, _Camera.GetControlType() ) );

                if( ImGui::BeginCombo( "Control", ControlTypes[ControlType].c_str() ) )
                {
                    Bool IsSelected = False;
                    for( Uint8 c = 0; c < 3; c++ )
                    {
                        IsSelected = c == ControlType;
                        if( ImGui::Selectable( ControlTypes[c].c_str(), &IsSelected ) )
                            ControlType = c;

                        if( IsSelected )
                            ImGui::SetItemDefaultFocus();
                    }

                    ImGui::EndCombo();
                }

                if( ControlType != Cast( Uint8, _Camera.GetControlType() ) )
                {
                    switch( ControlType )
                    {
                    case 0: _Camera.SetControlToFree(); break;
                    case 1: _Camera.SetControlToFPS(); break;
                    case 2:  _Camera.SetControlToOrbit( Vector3::Zero ); break;
                    default: _Camera.SetControlToFree(); break;
                    }
                }


                float Near = _Camera.GetNear();
                if( ImGui::DragFloat( "Near", &Near, 1.0f, Math::Epsilon(), std::numeric_limits<float>::max() ) )
                _Camera.SetNear( Near );

                float Far = _Camera.GetFar();
                if( ImGui::DragFloat( "Far", &Far, 1.0f, Math::Epsilon(), std::numeric_limits<float>::max() ) )
                _Camera.SetFar( Far );


                float OrbitDistance = _Camera.GetOrbitDistance();
                if( ImGui::DragFloat( "Orbit Distance", &OrbitDistance, 1.0f, Math::Epsilon(), std::numeric_limits<float>::max() ) )
                _Camera.SetOrbitDistance( OrbitDistance );

            }

            inline void CameraPerspectiveToEditor( CameraPerspective& _Camera )
            {
                ImGui::Text( "Camera Perspective" );

                CameraToEditor( _Camera );


                float FOV = _Camera.GetFieldOfView();
                if( ImGui::SliderAngle( "Field Of View", &FOV, Math::Epsilon(), 179.0f ) )
                _Camera.SetFieldOfView( FOV );

                float Aspect = _Camera.GetAspect();
                if( ImGui::DragFloat( "Aspect Ratio", &Aspect, Math::Epsilon(), Math::Max<float>() ) )
                _Camera.SetAspect( Aspect );
            }

            inline void CameraOrthographicToEditor( CameraOrthographic& _Camera )
            {
                ImGui::Text( "Camera Orthographic" );

                CameraToEditor( _Camera );

                Bool ViewportChanged = False;
                FloatRect Viewport = _Camera.GetViewport();

                ViewportChanged = ImGui::InputFloat( "Viewport Left", &Viewport.Left );
                ViewportChanged = ViewportChanged || ImGui::InputFloat( "Viewport Top", &Viewport.Top );
                ViewportChanged = ViewportChanged || ImGui::InputFloat( "Viewport Right", &Viewport.Right );
                ViewportChanged = ViewportChanged || ImGui::InputFloat( "Viewport Bottom", &Viewport.Bottom );
            }
        }

    } // priv

} // ae
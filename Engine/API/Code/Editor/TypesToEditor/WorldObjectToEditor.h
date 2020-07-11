#pragma once

#include "../../World/WorldObject/WorldObject.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void WorldObjectToEditor( WorldObject& _Object )
            {
                ImGui::Text( "World Object" );

                std::string IDString = std::to_string( _Object.GetObjectID() );
                ImGui::InputText( "ID", &IDString, ImGuiInputTextFlags_ReadOnly );

                std::string ObjectName = _Object.GetName();
                ImGui::InputText( "Name", &ObjectName );
                _Object.SetName( ObjectName );

                bool IsEnabled = _Object.IsEnabled();
                ImGui::Checkbox( "Is Enabled", &IsEnabled );
                _Object.SetEnabled( IsEnabled );

                ImGui::Separator();
            }
        }

    } // priv

} // ae

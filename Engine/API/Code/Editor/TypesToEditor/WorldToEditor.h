#pragma once

#include "../../World/World.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void WorldToEditor( World& )
            {
                ImGui::Text( "World Settings" );



                ImGui::Separator();
            }
        }

    } // priv

} // ae

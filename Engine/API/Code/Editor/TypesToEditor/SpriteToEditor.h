#pragma once

#include "../../Graphics/Sprite/Sprite.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void SpriteToEditor( Sprite& _Sprite )
            {
                ImGui::Text( "Sprite" );

                const Texture* CurrentTexture = _Sprite.GetTexture();

                std::string CurrentTextureName = CurrentTexture == nullptr ? "None" : CurrentTexture->GetName();
                ImGui::InputText( "Texture Name", &CurrentTextureName, ImGuiInputTextFlags_ReadOnly );

                std::string CurrentTextureID = CurrentTexture == nullptr ? "Invalid ID" : std::to_string( CurrentTexture->GetResourceID() );
                ImGui::InputText( "Texture ID", &CurrentTextureID, ImGuiInputTextFlags_ReadOnly );

                ImGui::Separator();
            }
        }

    } // priv

} // ae

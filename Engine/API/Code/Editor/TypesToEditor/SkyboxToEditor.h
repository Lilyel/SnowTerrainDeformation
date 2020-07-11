#pragma once

#pragma once

#include "../../Graphics/Skybox/Skybox.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void SkyboxToEditor( ae::Skybox& _Skybox )
			{
				ImGui::Text( "Skybox" );

				const CubeMap* CurrentCubeMap = _Skybox.GetCubeMap();

				std::string CurrentCubeMapName = CurrentCubeMap == nullptr ? "None" : CurrentCubeMap->GetName();
				ImGui::InputText( "Cube Map Name", &CurrentCubeMapName, ImGuiInputTextFlags_ReadOnly );

				std::string CurrentCubeMapID = CurrentCubeMap == nullptr ? "Invalid ID" : std::to_string( CurrentCubeMap->GetResourceID() );
				ImGui::InputText( "Cube Map ID", &CurrentCubeMapID, ImGuiInputTextFlags_ReadOnly );

				ImGui::Separator();
			}
		}

	} // priv

} // 
#pragma once

#include "../../Graphics/Material/Material.h"
#include "../../Graphics/ShadowMap/ShadowMap.h"
#include "../../Graphics/Shader/ShaderParameter/ShaderParameter.h"
#include "../../UI/Dependencies/IncludeImGui.h"
#include "../../Maths/Functions/MathsFunctions.h"

#include <array>

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void MaterialToEditor( Material& _Material )
			{
				ImGui::Text( "Material" );


				if( _Material.GetShader() != nullptr )
				{
					std::string ShaderName = _Material.GetShader()->GetName();
					ImGui::InputText( "Shader", &ShaderName, ImGuiInputTextFlags_ReadOnly );

					if( ImGui::Button( "Reload Shader" ) )
					{
						_Material.GetShader()->Compile();
						_Material.DiscardSavedUniformsLocation();
					}
				}

				ImGui::SameLine();
				if( ImGui::Button( "Save Uniforms Locations" ) )
					_Material.SaveUniformsLocation();

				for( std::pair<const std::string, ShaderParameter*>& ShaderParamIt : _Material )
				{
					if( ShaderParamIt.second->IsEditable() )
						ShaderParamIt.second->ToEditor();
				}

				if( _Material.HasShadowMap() )
				{
					std::string ShadowMapName = _Material.GetShadowMap()->GetName();
					ImGui::InputText( "Shadow Map", &ShadowMapName, ImGuiInputTextFlags_ReadOnly );
				}

				ImGui::Separator();
			}
		}

	} // priv

} // ae
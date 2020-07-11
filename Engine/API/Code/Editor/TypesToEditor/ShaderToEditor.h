#pragma once

#include "../../Graphics/Shader/Shader.h"
#include "../../UI/Dependencies/IncludeImGui.h"

#include <array>

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void ShaderToEditor( Shader& _Shader )
			{
				ImGui::Text( "Shader" );

				std::string ShaderFileName = _Shader.GetVertexFile();
				ImGui::InputText( "Vertex File", &ShaderFileName, ImGuiInputTextFlags_ReadOnly );

				ShaderFileName = _Shader.GetFragmentFile();
				ImGui::InputText( "Fragment File", &ShaderFileName, ImGuiInputTextFlags_ReadOnly );

				ShaderFileName = _Shader.GetGeometryFile();
				ImGui::InputText( "Geometry File", &ShaderFileName, ImGuiInputTextFlags_ReadOnly );

				ShaderFileName = _Shader.GetComputeFile();
				ImGui::InputText( "Compute File", &ShaderFileName, ImGuiInputTextFlags_ReadOnly );

				ShaderFileName = _Shader.GetTesselationControlFile();
				ImGui::InputText( "Tesselation Control File", &ShaderFileName, ImGuiInputTextFlags_ReadOnly );

				ShaderFileName = _Shader.GetTesselationEvaluationFile();
				ImGui::InputText( "Tesselation Evaluation File", &ShaderFileName, ImGuiInputTextFlags_ReadOnly );

				if( ImGui::Button( "Reload Shader" ) )
					_Shader.Compile();


				const Shader::LocationsMap& CachedLocations = _Shader.GetCachedLocations();
				const std::string CachedHeaderName = std::string( "Cached Parameters (" ) + std::to_string( CachedLocations.size() ) + ")";

				if( ImGui::CollapsingHeader( CachedHeaderName.c_str() ) )
				{
					ImGui::Indent();

					std::string CachedLocationStr;

					for( const std::pair<std::string, Int32>& CachedLocation : CachedLocations )
					{
						CachedLocationStr = CachedLocation.first + " : " + std::to_string( CachedLocation.second );
						ImGui::Text( CachedLocationStr.c_str() );
					}

					ImGui::Unindent();
				}

				ImGui::Separator();
			}
		}

	} // priv

} // ae
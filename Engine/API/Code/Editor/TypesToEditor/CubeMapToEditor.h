#pragma once

#include "../../Graphics/CubeMap/CubeMap.h"
#include "../../Graphics/CubeMap/CubeMapImage.h"
#include "TextureToEditor.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void CubeMapToEditorBegin()
			{
				ImGui::Text( "CubeMap" );
			}

			inline void CubeMapToEditorEnd()
			{
				ImGui::Separator();
			}

			inline void CubeMapToEditor( CubeMap& _CubeMap )
			{
				TextureToEditor( _CubeMap );

				std::array<std::string, 6> SideNames =
				{
					"Side( +X )", "Side( -X )",
					"Side( +Y )", "Side( -Y )",
					"Side( +Z )", "Side( -Z )"
				};

				for( Uint32 s = 0; s < 6u; s++ )
				{
					if( !ImGui::CollapsingHeader( SideNames[s].c_str() ) )
						continue;

					// Size
					float Width = Cast( float, _CubeMap.GetWidth( s ) );
					ImGui::InputFloat( "Width", &Width, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );

					float Height = Cast( float, _CubeMap.GetHeight( s ) );
					ImGui::InputFloat( "Height", &Height, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );
				}
			}

			inline void CubeMapImageToEditor( CubeMapImage& _CubeMap )
			{
				TextureToEditor( _CubeMap );

				std::array<std::string, 6> SideNames =
				{
					"Side( +X )", "Side( -X )",
					"Side( +Y )", "Side( -Y )",
					"Side( +Z )", "Side( -Z )"
				};

				for( Uint32 s = 0; s < 6u; s++ )
				{
					if( !ImGui::CollapsingHeader( SideNames[s].c_str() ) )
						continue;

					// Size
					float Width = Cast( float, _CubeMap.GetWidth( s ) );
					ImGui::InputFloat( "Width", &Width, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );

					float Height = Cast( float, _CubeMap.GetHeight( s ) );
					ImGui::InputFloat( "Height", &Height, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );

					std::string Path = _CubeMap.GetFilePath( s );
					ImGui::InputText( "Path", &Path, ImGuiInputTextFlags_ReadOnly );
				}
			}
		}

	} // priv

} // ae

#pragma once

#include "../../Graphics/ShadowMap/ShadowMap.h"
#include "../../UI/Dependencies/IncludeImGui.h"
#include "../../Maths/Functions/MathsFunctions.h"
#include "TextureToEditor.h"

#include <array>

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void ShadowMapToEditor( ShadowMap& _ShadowMap )
			{
				ImGui::Text( "Shadow Map" );

				float Width = Cast( float, _ShadowMap.GetWidth() );
				float Height = Cast( float, _ShadowMap.GetHeight() );


				std::string ShaderName = _ShadowMap.GetShader()->GetName();
				ImGui::InputText( "Shader", &ShaderName, ImGuiInputTextFlags_ReadOnly );

				// Is a cube map ?
				Bool IsOmni = _ShadowMap.IsOmnidirectional();
				ImGui::Checkbox( "Is Omnidirectional", &IsOmni );

				// Size
				ImGui::InputFloat( "Width", &Width, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );
				ImGui::InputFloat( "Height", &Height, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );

				// Light reference.
				std::string LightName = _ShadowMap.GetLight().GetName();
				ImGui::InputText( "Light", &LightName, ImGuiInputTextFlags_ReadOnly );

				// Projection settings.
				float Near = _ShadowMap.GetNear();
				if( ImGui::DragFloat( "Near", &Near, 0.1f, Math::Epsilon(), std::numeric_limits<float>::max() ) )
					_ShadowMap.SetNear( Near );

				float Far = _ShadowMap.GetFar();
				if( ImGui::DragFloat( "Far", &Far, 0.1f, Math::Epsilon(), std::numeric_limits<float>::max() ) )
					_ShadowMap.SetFar( Far );

				Vector2 Coverage = _ShadowMap.GetOrthographicCoverage();
				if( ImGui::DragFloat2( "Orthographic Coverage", &Coverage.X, 0.1f, 0.0f ) )
					_ShadowMap.SetOrthographicCoverage( Coverage );

				// Shading process.

				Bool UsePCF = _ShadowMap.IsUsingPCF();
				if( ImGui::Checkbox( "Use Percentage-Closer Filtering", &UsePCF ) )
					_ShadowMap.SetUsePCF( UsePCF );

				if( UsePCF && _ShadowMap.IsOmnidirectional() )
				{
					float OmniPCFRadius = _ShadowMap.GetOmniPCFRadius();
					if( ImGui::DragFloat( "PCF Radius", &OmniPCFRadius, 0.001f, 0.0f, 1.0f ) )
						_ShadowMap.SetOmniPCFRadius( OmniPCFRadius );
				}

				float Bias = _ShadowMap.GetBias();
				if( ImGui::DragFloat( "Bias", &Bias, 0.001f, 0.0f, 1.0f ) )
					_ShadowMap.SetBias( Bias );

				// Preview
				if( !_ShadowMap.IsOmnidirectional() )
				{
					const Texture2D* ShadowMapTexture = dynamic_cast<const Texture2D*>( _ShadowMap.GetShadowMap() );
					if( ShadowMapTexture != nullptr )
						Texture2DToEditorPreview( *ShadowMapTexture );
				}

				ImGui::Separator();
			}
		}

	} // priv

} // ae
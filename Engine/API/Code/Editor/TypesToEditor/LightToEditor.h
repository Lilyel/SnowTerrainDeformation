#pragma once

#include "../../Graphics/Light/Light.h"
#include "../../UI/Dependencies/IncludeImGui.h"
#include "ColorToEditor.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void LightToEditor( Light& _Light )
			{
				std::string LightType;
				switch( _Light.GetLightType() )
				{
				case ae::Light::LightType::Point: LightType = "Point Light"; break;
				case ae::Light::LightType::Spot: LightType = "Spot Light"; break;
				case ae::Light::LightType::Directional: LightType = "Directional Light"; break;
				case ae::Light::LightType::Unknown: LightType = "Unknown"; break;
				default:
					break;
				}

				ImGui::Text( LightType.c_str() );

				float Intensity = _Light.GetIntensity();
				ImGui::DragFloat( "Intensity", &Intensity, 1.0f, Math::Epsilon(), std::numeric_limits<float>::max() );
				_Light.SetIntensity( Intensity );

				Color LightColor = _Light.GetColor();
				if( ColorToEditor( "Color", LightColor ) )
					_Light.SetColor( LightColor );
			}
		}

	} // priv

} // ae
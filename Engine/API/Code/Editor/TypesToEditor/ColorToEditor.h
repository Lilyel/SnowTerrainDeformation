#pragma once

#include "../../UI/Dependencies/IncludeImGui.h"
#include "../../Graphics/Color/Color.h"

#include <string>

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline bool ColorToEditor( const std::string& _Name, Color& _Color )
			{
				float ColorRaw[4] = { _Color.R(), _Color.G(), _Color.B(), _Color.A() };
				if( ImGui::ColorEdit4( _Name.c_str(), ColorRaw, ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR ) )
				{
					_Color.Set( ColorRaw[0], ColorRaw[1], ColorRaw[2], ColorRaw[3] );
					return True;
				}
				return false;
			}

			inline bool ColorNoAlphaToEditor( const std::string& _Name, Color& _Color )
			{
				float ColorRaw[3] = { _Color.R(), _Color.G(), _Color.B() };
				if( ImGui::ColorEdit4( _Name.c_str(), ColorRaw, ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_NoAlpha ) )
				{
					_Color.Set( ColorRaw[0], ColorRaw[1], ColorRaw[2] );
					return True;
				}
				return false;
			}
		} // ui		
	} // priv
} // ae

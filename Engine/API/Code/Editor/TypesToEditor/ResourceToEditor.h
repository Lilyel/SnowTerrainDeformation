#pragma once

#pragma once

#include "../../Resources/Resource/Resource.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void ResourceToEditor( Resource& _Resource )
			{
				ImGui::Text( "Resource" );

				std::string IDString = std::to_string( _Resource.GetResourceID() );
				ImGui::InputText( "ID", &IDString, ImGuiInputTextFlags_ReadOnly );

				std::string ObjectName = _Resource.GetName();
				if( ImGui::InputText( "Name", &ObjectName ) )
					_Resource.SetName( ObjectName );

				ImGui::Separator();
			}
		}

	} // priv

} // ae

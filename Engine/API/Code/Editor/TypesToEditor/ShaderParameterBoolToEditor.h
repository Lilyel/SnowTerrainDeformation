#pragma once

#include "../../Graphics/Shader/ShaderParameter/ShaderParameterBool.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void ShaderParameterBoolToEditor( ShaderParameterBool& _ShaderParameterBool )
			{
				Bool Value = _ShaderParameterBool.GetValue();

				if( ImGui::Checkbox( _ShaderParameterBool.GetName().c_str(), &Value ) )
					_ShaderParameterBool.SetValue( Value );
			}
		} // ui		
	} // priv
} // ae
#pragma once

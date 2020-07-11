#pragma once

#include "../../Graphics/Shader/ShaderParameter/ShaderParameterFloat.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void ShaderParameterFloatToEditor( ShaderParameterFloat& _ShaderParameterFloat )
			{
				float Value = _ShaderParameterFloat.GetValue();

				if( ImGui::DragFloat( _ShaderParameterFloat.GetName().c_str(), &Value, Cast( float, _ShaderParameterFloat.GetStep() ), _ShaderParameterFloat.GetMin(), _ShaderParameterFloat.GetMax() ) )
					_ShaderParameterFloat.SetValue( Value );
			}
		} // ui		
	} // priv
} // ae

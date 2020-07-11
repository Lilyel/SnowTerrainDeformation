#pragma once

#include "../../Graphics/Shader/ShaderParameter/ShaderParameterInt.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void ShaderParameterIntToEditor( ShaderParameterInt& _ShaderParameterInt )
			{
				Int32 Value = _ShaderParameterInt.GetValue();

				if( ImGui::DragInt( _ShaderParameterInt.GetName().c_str(), &Value, Cast( float, _ShaderParameterInt.GetStep() ), _ShaderParameterInt.GetMin(), _ShaderParameterInt.GetMax() ) )
					_ShaderParameterInt.SetValue( Value );
			}
		} // ui		
	} // priv
} // ae

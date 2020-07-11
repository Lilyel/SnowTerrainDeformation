#pragma once

#include "../../Graphics/Shader/ShaderParameter/ShaderParameterVector2.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void ShaderParameterVector2ToEditor( ShaderParameterVector2& _ShaderParameterVector2 )
			{
				Vector2 Value = _ShaderParameterVector2.GetValue();

				float ValueRaw[2] = { Value.X, Value.Y };

				if( ImGui::DragFloat2( _ShaderParameterVector2.GetName().c_str(), ValueRaw, Cast( float, _ShaderParameterVector2.GetStep() ), _ShaderParameterVector2.GetMin(), _ShaderParameterVector2.GetMax() ) )
					_ShaderParameterVector2.SetValue( Vector2( ValueRaw[0], ValueRaw[1] ) );
			}
		} // ui		
	} // priv
} // ae

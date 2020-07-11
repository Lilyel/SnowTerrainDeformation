#pragma once

#include "../../Graphics/Shader/ShaderParameter/ShaderParameterVector3.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void ShaderParameterVector3ToEditor( ShaderParameterVector3& _ShaderParameterVector3 )
			{
				Vector3 Value = _ShaderParameterVector3.GetValue();

				float ValueRaw[3] = { Value.X, Value.Y,Value.Z };

				if( ImGui::DragFloat3( _ShaderParameterVector3.GetName().c_str(), ValueRaw, Cast( float, _ShaderParameterVector3.GetStep() ), _ShaderParameterVector3.GetMin(), _ShaderParameterVector3.GetMax() ) )
					_ShaderParameterVector3.SetValue( Vector3( ValueRaw[0], ValueRaw[1], ValueRaw[2] ) );
			}
		} // ui		
	} // priv
} // ae

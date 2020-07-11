#pragma once

#include "../../Graphics/Shader/ShaderParameter/ShaderParameterColor.h"
#include "../../UI/Dependencies/IncludeImGui.h"
#include "ColorToEditor.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void ShaderParameterColorToEditor( ShaderParameterColor& _ShaderParameterColor )
			{
				Color ParameterColor = _ShaderParameterColor.GetValue();
				if( ColorToEditor( _ShaderParameterColor.GetName(), ParameterColor ) )
					_ShaderParameterColor.SetValue( ParameterColor );
			}
		} // ui		
	} // priv
} // ae

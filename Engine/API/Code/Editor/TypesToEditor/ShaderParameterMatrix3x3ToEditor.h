#pragma once

#include "../../Graphics/Shader/ShaderParameter/ShaderParameterMatrix3x3.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void ShaderParameterMatrix3x3ToEditor( ShaderParameterMatrix3x3& _ShaderParameterMatrix3x3 )
			{
				Matrix3x3 Matrix = _ShaderParameterMatrix3x3.GetValue();
				
				float PerRows[3][3] =
				{
					{ Matrix( 0, 0 ), Matrix( 0, 1 ), Matrix( 0, 2 ) },
					{ Matrix( 1, 0 ), Matrix( 1, 1 ), Matrix( 1, 2 ) },
					{ Matrix( 2, 0 ), Matrix( 2, 1 ), Matrix( 2, 2 ) }
				};

				Bool HasRow0Changed = ImGui::DragFloat3( _ShaderParameterMatrix3x3.GetName().c_str(), PerRows[0] );
				Bool HasRow1Changed = ImGui::DragFloat3( "##ShaderParamMat3_Row1", PerRows[1] );
				Bool HasRow2Changed = ImGui::DragFloat3( "##ShaderParamMat3_Row2", PerRows[2] );

				if( HasRow0Changed || HasRow1Changed || HasRow2Changed )
				{
					Matrix( 0, 0 ) = PerRows[0][0]; Matrix( 0, 1 ) = PerRows[0][1]; Matrix( 0, 2 ) = PerRows[0][2];
					Matrix( 1, 0 ) = PerRows[1][0]; Matrix( 1, 1 ) = PerRows[1][1]; Matrix( 1, 2 ) = PerRows[1][2];
					Matrix( 2, 0 ) = PerRows[2][0]; Matrix( 2, 1 ) = PerRows[2][1]; Matrix( 2, 2 ) = PerRows[2][2];

					_ShaderParameterMatrix3x3.SetValue( Matrix );
				}
			}
		} // ui		
	} // priv
} // ae

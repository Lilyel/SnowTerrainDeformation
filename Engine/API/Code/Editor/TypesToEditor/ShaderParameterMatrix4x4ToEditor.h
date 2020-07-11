#pragma once

#include "../../Graphics/Shader/ShaderParameter/ShaderParameterMatrix4x4.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void ShaderParameterMatrix4x4ToEditor( ShaderParameterMatrix4x4& _ShaderParameterMatrix4x4 )
			{
				Matrix4x4 Matrix = _ShaderParameterMatrix4x4.GetValue();

				float PerRows[4][4] =
				{
					{ Matrix( 0, 0 ), Matrix( 0, 1 ), Matrix( 0, 2 ), Matrix( 0, 3 ) },
					{ Matrix( 1, 0 ), Matrix( 1, 1 ), Matrix( 1, 2 ), Matrix( 1, 3 ) },
					{ Matrix( 2, 0 ), Matrix( 2, 1 ), Matrix( 2, 2 ), Matrix( 2, 3 ) },
					{ Matrix( 3, 0 ), Matrix( 3, 1 ), Matrix( 3, 2 ), Matrix( 3, 3 ) }
				};

				Bool HasRow0Changed = ImGui::DragFloat4( _ShaderParameterMatrix4x4.GetName().c_str(), PerRows[0] );
				Bool HasRow1Changed = ImGui::DragFloat4( "##ShaderParamMat4_Row1", PerRows[1] );
				Bool HasRow2Changed = ImGui::DragFloat4( "##ShaderParamMat4_Row2", PerRows[2] );
				Bool HasRow3Changed = ImGui::DragFloat4( "##ShaderParamMat4_Row3", PerRows[3] );

				if( HasRow0Changed || HasRow1Changed || HasRow2Changed || HasRow3Changed )
				{
					Matrix( 0, 0 ) = PerRows[0][0]; Matrix( 0, 1 ) = PerRows[0][1]; Matrix( 0, 2 ) = PerRows[0][2];	Matrix( 0, 3 ) = PerRows[0][3];
					Matrix( 1, 0 ) = PerRows[1][0]; Matrix( 1, 1 ) = PerRows[1][1]; Matrix( 1, 2 ) = PerRows[1][2];	Matrix( 1, 3 ) = PerRows[1][3];
					Matrix( 2, 0 ) = PerRows[2][0]; Matrix( 2, 1 ) = PerRows[2][1]; Matrix( 2, 2 ) = PerRows[2][2];	Matrix( 2, 3 ) = PerRows[2][3];
					Matrix( 3, 0 ) = PerRows[3][0]; Matrix( 3, 1 ) = PerRows[3][1]; Matrix( 3, 2 ) = PerRows[3][2];	Matrix( 3, 3 ) = PerRows[3][3];

					_ShaderParameterMatrix4x4.SetValue( Matrix );
				}
			}
		} // ui		
	} // priv
} // ae

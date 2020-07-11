#pragma once

#include "../../UI/Dependencies/IncludeImGui.h"
#include "../../Graphics/Mesh/3D/CurveMesh.h"
#include "../CurveEditor/CurveEditor.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void CurveMeshToEditor( CurveMesh& _CurveMesh )
			{
				ImGui::Text( "Curve Mesh" );

				std::string InterpolationTypeName = ToString( _CurveMesh.GetCurve().GetType() );
				ImGui::InputText( "Interpolation", &InterpolationTypeName, ImGuiInputTextFlags_ReadOnly );

				int PointCount = Cast( int, _CurveMesh.GetPointCount() );
				if( ImGui::DragInt( "Point Count", &PointCount, 1.0f, 2, Math::Max<int>() ) )
					_CurveMesh.SetPointCount( Cast( Uint32, PointCount ) );


				Bool DrawControlCurve = _CurveMesh.IsControlCurveDrawn();
				if( ImGui::Checkbox( "Draw Control Curve", &DrawControlCurve ) )
					_CurveMesh.SetDrawControlCurve( DrawControlCurve );


				Bool DrawCurve = _CurveMesh.IsCurveDrawn();
				if( ImGui::Checkbox( "Draw Curve", &DrawCurve ) )
					_CurveMesh.SetDrawCurve( DrawCurve );



				if( ImGui::Button( "Edit" ) )
					IsCurveEditorOpen = True;

				if( IsCurveEditorOpen )
				{
					Curve& CurrentCurve = const_cast<Curve&>( _CurveMesh.GetCurve() );

					if( CurveEditor( CurrentCurve ) )
						_CurveMesh.Update();
				}
				ImGui::Separator();
			}
		} // ui		
	} // priv
} // ae

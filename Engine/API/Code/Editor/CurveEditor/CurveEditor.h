#pragma once

#include "../../UI/Dependencies/IncludeImGui.h"
#include "../../Maths/Curve/Curve.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			static Bool IsCurveEditorOpen = false;

			inline Bool CurveEditor( Curve& _Curve )
			{
				Bool UpdateMesh = False;

				if( IsCurveEditorOpen )
				{
					ImGui::Begin( "Curve Editor", &IsCurveEditorOpen );

					const Uint32 ControlPointCount = _Curve.GetControlPointsCount();
					
					Uint32 PropertiesCount = _Curve.EditorGetPropertiesCount();

					ImGui::Columns( Cast( int, PropertiesCount + 1 ), "ControlPoints" );

					// Headers.
					ImGui::Separator();

					ImGui::Text( "ID" ); ImGui::NextColumn();

					for( Uint32 p = 0; p < PropertiesCount; p++ )
					{
						ImGui::Text( _Curve.EditorGetPropertyName( p ).c_str() );
						ImGui::NextColumn();
					}
					
					ImGui::Separator();


					// Control points.
					for( Uint32 cp = 0; cp < ControlPointCount; cp++ )
					{
						// ID
						ImGui::PushItemWidth( -1 );

						ImGui::Text( "%d", cp );

						ImGui::PopItemWidth();
						ImGui::NextColumn();


						// Curve specific properties.
						for( Uint32 p = 0; p < PropertiesCount; p++ )
						{
							ImGui::PushItemWidth( -1 );

							const std::string Label = std::string( "##" ) + _Curve.EditorGetPropertyName( p ) + "#" + std::to_string( cp );

							if( _Curve.EditorEditProperty( Label, cp, p ) )
								UpdateMesh = True;

							ImGui::PopItemWidth();
							ImGui::NextColumn();
						}

						ImGui::Separator();
					}

					ImGui::Columns( 1 );
					ImGui::Separator();

					ImGui::End();
				}

				return UpdateMesh;
			}
		}
	}
}
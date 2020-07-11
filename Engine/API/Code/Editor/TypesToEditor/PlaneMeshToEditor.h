#pragma once

#include "../../Graphics/Mesh/3D/PlaneMesh.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void PlaneMeshToEditor( ae::PlaneMesh& _PlaneStatic )
            {
                ImGui::Text( "Plane Mesh" );

                float Size = _PlaneStatic.GetSize();
                if( ImGui::DragFloat( "Size", &Size, 1.0f, Math::Epsilon(), std::numeric_limits<float>::max() ) )
                {
                    _PlaneStatic.SetSize( Size );
                    _PlaneStatic.ApplyChanges();
                }

                
                int SubdivisionWidth = Cast( int, _PlaneStatic.GetSubdivisionWidth() );
                if( ImGui::DragInt( "Subdivision Width", &SubdivisionWidth, 1.0f, 1, Math::Max<int>() ) )
                    _PlaneStatic.SetSubdivisionWidth( Cast( Uint32, SubdivisionWidth ) );

                int SubdivisionHeight = Cast( int, _PlaneStatic.GetSubdivisionHeight() );
                if( ImGui::DragInt( "Subdivision Height", &SubdivisionHeight, 1.0f, 1, Math::Max<int>() ) )
                    _PlaneStatic.SetSubdivisionHeight( Cast( Uint32, SubdivisionHeight ) );


                ImGui::Separator();
            }
        }

    } // priv

} // ae
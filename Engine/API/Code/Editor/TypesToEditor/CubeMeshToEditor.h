#pragma once

#include "../../Graphics/Mesh/3D/CubeMesh.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void CubeMeshToEditor( ae::CubeMesh& _CubeStatic )
            {
                ImGui::Text( "Cube Mesh" );

                float Size = _CubeStatic.GetSize();
                if( ImGui::DragFloat( "Size", &Size, 1.0f, Math::Epsilon(), std::numeric_limits<float>::max() ) )
                {
                    _CubeStatic.SetSize( Size );
                    _CubeStatic.ApplyChanges();
                }


                int SubdivisionWidth = Cast( int, _CubeStatic.GetSubdivisionWidth() );
                if( ImGui::DragInt( "Subdivision Width", &SubdivisionWidth, 1.0f, 1, Math::Max<int>() ) )
                    _CubeStatic.SetSubdivisionWidth( Cast( Uint32, SubdivisionWidth ) );

                int SubdivisionHeight = Cast( int, _CubeStatic.GetSubdivisionHeight() );
                if( ImGui::DragInt( "Subdivision Height", &SubdivisionHeight, 1.0f, 1, Math::Max<int>() ) )
                    _CubeStatic.SetSubdivisionHeight( Cast( Uint32, SubdivisionHeight ) );

                int SubdivisionDepth = Cast( int, _CubeStatic.GetSubdivisionDepth() );
                if( ImGui::DragInt( "Subdivision Depth", &SubdivisionDepth, 1.0f, 1, Math::Max<int>() ) )
                    _CubeStatic.SetSubdivisionDepth( Cast( Uint32, SubdivisionDepth ) );

                ImGui::Separator();
            }
        }

    } // priv

} // ae
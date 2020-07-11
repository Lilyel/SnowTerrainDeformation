#pragma once

#pragma once

#include "../../Graphics/Mesh/3D/SphereMesh.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void SphereMeshToEditor( ae::SphereMesh& _SphereStatic )
            {
                ImGui::Text( "Sphere Mesh" );


                float Radius = _SphereStatic.GetRadius();
                if( ImGui::DragFloat( "Radius", &Radius, 1.0f, Math::Epsilon(), std::numeric_limits<float>::max() ) )
                {
                    _SphereStatic.SetRadius( Radius );
                    _SphereStatic.ApplyChanges();
                }

				int RingCount = static_cast<int>( _SphereStatic.GetRingCount() );
				if( ImGui::DragInt( "Ring Count", &RingCount, 1.0f, 3, std::numeric_limits<int>::max() ) )
					_SphereStatic.SetRingCount( static_cast<Uint32>( RingCount ) );

				int SegmentCount = static_cast<int>( _SphereStatic.GetSegmentCount() );
				if( ImGui::DragInt( "Segment Count", &SegmentCount, 1.0f, 3, std::numeric_limits<int>::max() ) )
					_SphereStatic.SetSegmentCount( static_cast<Uint32>( SegmentCount ) );

                ImGui::Separator();
            }
        }

    } // priv

} // ae
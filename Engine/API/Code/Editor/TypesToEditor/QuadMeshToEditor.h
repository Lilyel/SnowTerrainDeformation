#pragma once

#include "../../Graphics/Mesh/2D/QuadMesh.h"
#include "../../UI/Dependencies/IncludeImGui.h"
#include "ColorToEditor.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void QuadMeshToEditor( QuadMesh& _QuadStatic )
            {
                ImGui::Text( "Quad Static" );

                Vector2 Size = _QuadStatic.GetSize();
                if( ImGui::DragFloat2( "Size", &Size.X, 1.0f, Math::Epsilon(), std::numeric_limits<float>::max() ) )
                {
                    _QuadStatic.SetSize( Size.X, Size.Y );
                    _QuadStatic.ApplyChanges();
                }
                
                ImGui::Separator();
            }
        }

    } // priv

} // ae

#pragma once


#include "../../../Toolbox/Toolbox.h"
#include "../../Drawable/Drawable.h"

#include <functional>

namespace ae
{
    /// \ingroup graphics
    /// <summary>
    /// 2D quad that covers the entire screen. Setup to be used directly in normalized device coordinates.
    /// </summary>
    class AERO_CORE_EXPORT FullscreenQuadMesh : public Drawable
    {
    public:
        /// <summary>Initialize the full-screen quad mesh.</summary>
        /// <param name="_NewMaterialInstance">
		/// Must create a new material instance for this sprite ?<para/>
		/// If set to False, the default 2D material is taken and will be shared with all others sprite and 2D shapes with the default material.
		/// </param>
        FullscreenQuadMesh( Bool _NewMaterialInstance = True );

    private:
        /// <summary>Vertices to render that hold the texture.</summary>
        Vertex2DArray m_QuadVertices;

        /// <summary>Indices of the triangles made with the vertices.</summary>
        IndexArray m_QuadIndices;
    };

} // ae

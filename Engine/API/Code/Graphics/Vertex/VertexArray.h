#ifndef _VERTEXARRAY_AERO_H_
#define _VERTEXARRAY_AERO_H_

#include "../../Toolbox/Toolbox.h"
#include "Vertex3D.h"
#include "Vertex2D.h"

#include <vector>

template class AERO_CORE_EXPORT std::vector<ae::Vertex3D>;
template class AERO_CORE_EXPORT std::vector<ae::Vertex2D>;

namespace ae
{
    /// \ingroup graphics
    /// <summary>
    /// Array of 3D vertex that can be drawn.
    /// </summary>
    /// <seealso cref="Vertex3D"/>
    using Vertex3DArray = std::vector<Vertex3D>;

    /// \ingroup graphics
    /// <summary>
    /// Array of 2D vertex that can be drawn.
    /// </summary>
    /// <seealso cref="Vertex2D"/>
    using Vertex2DArray = std::vector<Vertex2D>;

} // ae


#endif // _VERTEXARRAY_AERO_H_
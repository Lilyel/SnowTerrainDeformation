#ifndef _PRIMITIVES_TYPE_AERO_H_
#define _PRIMITIVES_TYPE_AERO_H_

#include "../Dependencies/OpenGL.h"


namespace ae
{
    /// \ingroup graphics
    /// <summary>
    /// Determine how the primitive will be drawn.
    /// </summary>
    enum class PrimitiveType : GLenum
    {
        /// <summary>
        /// Treats each vertex as a single point. 
        /// Vertex n defines point n. 
        /// N points are drawn.
        /// </summary>
        Points = GL_POINTS,

        /// <summary>
        /// Treats each pair of vertices as an independent line segment. 
        /// Vertices 2n - 1 and 2n define line n. 
        /// N/2 lines are drawn.
        /// </summary>
        Lines = GL_LINES,

        /// <summary>
        /// Draws a connected group of line segments from the first vertex to the last. 
        /// Vertices n and n+1 define line n. 
        /// N - 1 lines are drawn.
        /// </summary>
        LineStrip = GL_LINE_STRIP,

        /// <summary>
        /// Draws a connected group of line segments from the first vertex to the last, then back to the first. 
        /// Vertices n and n + 1 define line n. 
        /// The last line, however, is defined by vertices N and 1. 
        /// N lines are drawn.
        /// </summary>
        LineLoop = GL_LINE_LOOP,

        /// <summary>
        /// Treats each triplet of vertices as an independent triangle. 
        /// Vertices 3n - 2, 3n - 1, and 3n define triangle n. 
        /// N/3 triangles are drawn.
        /// </summary>
        Triangles = GL_TRIANGLES,

        /// <summary>
        /// Draws a connected group of triangles. 
        /// One triangle is defined for each vertex presented after the first two vertices. 
        /// For odd n, vertices n, n + 1, and n + 2 define triangle n. 
        /// For even n, vertices n + 1, n, and n + 2 define triangle n. 
        /// N - 2 triangles are drawn.
        /// </summary>
        TriangleStrip = GL_TRIANGLE_STRIP,

        /// <summary>
        /// Draws a connected group of triangles. 
        /// One triangle is defined for each vertex presented after the first two vertices. 
        /// Vertices 1, n + 1, n + 2 define triangle n. 
        /// N - 2 triangles are drawn.
        /// </summary>
        TriangleFan = GL_TRIANGLE_FAN,

        /// <summary>
        /// Treats each group of four vertices as an independent quadrilateral. 
        /// Vertices 4n - 3, 4n - 2, 4n - 1, and 4n define quadrilateral n. 
        /// N/4 quadrilaterals are drawn. 
        /// </summary>
        Quads = GL_QUADS,

        /// <summary>
        /// Draws a connected group of quadrilaterals. 
        /// One quadrilateral is defined for each pair of vertices presented after the first pair. 
        /// Vertices 2n - 1, 2n, 2n + 2, and 2n + 1 define quadrilateral n. 
        /// N/2 - 1 quadrilaterals are drawn. 
        /// Note that the order in which vertices are used to construct a quadrilateral from strip data is different from that used with independent data.
        /// </summary>
        QuadStip = GL_QUAD_STRIP,

        /// <summary>
        /// Draws a single, convex polygon.
        /// Vertices 1 through N define this polygon.
        /// </summary>
        Polygon = GL_POLYGON,

        /// <summary>
        /// Primitive type for tesselation shaders.<para/>
        /// The number of vertices for the patches must be defined in the tesselation control shader 
        /// or with the glPatchParameteri(GL_PATCH_VERTICES, CountPerPatch) function.
        /// </summary>
        Patches = GL_PATCHES
    };
} // ae

#endif
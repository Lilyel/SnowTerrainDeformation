#ifndef _VERTEX2D_AERO_H_
#define _VERTEX2D_AERO_H_

#include "../../Toolbox/Toolbox.h"
#include "../Color/Color.h"
#include "../../Maths/Vector/Vector2.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Represent a 2D point that can be rendered.
	/// Contains a position, a color and texture coordinates.
	/// </summary>
	class AERO_CORE_EXPORT Vertex2D
	{
	public:
		/// <summary>
		/// Default construtor.
		/// </summary>
		Vertex2D();

		/// <summary>
		/// Build a vertex from a position.
		/// The color will be White and the UV (0, 0).
		/// </summary>
		/// <param name="_Position">3D Position to build the vertex from.</param>
		Vertex2D( const Vector2& _Position );

		/// <summary>
		/// Build a vertex from a position and a color.
		/// The UV will be (0, 0).
		/// </summary>
		/// <param name="_Position">3D Position to build the vertex from.</param>
		/// <param name="_Color">Color of the vertex.</param>
		Vertex2D( const Vector2& _Position, const Color& _Color );

		/// <summary>
		/// Build a vertex from a position, a color and texture coordinates (UV).
		/// </summary>
		/// <param name="_Position">2D Position to build the vertex from.</param>
		/// <param name="_Color">Color of the vertex.</param>
		/// <param name="_UV">Texture coordinates of the vertex.</param>
		Vertex2D( const Vector2& _Position, const Color& _Color, const Vector2& _UV );

		/// <summary>Compare two vertices.</summary>
		/// <param name="_VertexB">Array to compare with.</param>
		/// <returns>True if vertex are the same, False otherwise.</returns>
		inline Bool operator==( const Vertex2D& _VertexB ) const;


		/// <summary>Compare two vertices.</summary>
		/// <param name="_VertexB">Vertex to compare with.</param>
		/// <returns>True if vertex are different, False otherwise.</returns>
		inline Bool operator!=( const Vertex2D& _VertexB ) const;

	public:
		/// <summary>3D position of the vertex.</summary>
		Vector2 Position;
		/// <summary>Color of the vertex. </summary>
		Color Color;
		/// <summary>Texture coordinates of the vertex.</summary>
		Vector2 UV;
	};

    /// <summary>
    /// Convert a vertex 2D to a string.
    /// </summary>
    /// <param name="_Color">Vertex 2D to convert.</param>
    /// <returns>Vertex 2D as a C++ string. ( Order : Position, Color, UV ).</returns>
    AERO_CORE_EXPORT inline std::string ToString( const Vertex2D& _Vertex );

} // ae

/// <summary>
/// Convert a vertex 2D to a string and push it in the out stream.
/// </summary>
/// <param name="_Color">Vertex 2D to convert and push to the out stream.</param>
/// <returns>Out stream.</returns>
AERO_CORE_EXPORT std::ostream& operator<<( std::ostream& os, const ae::Vertex2D& _Vertex );

#endif // _VERTEX2D_AERO_H_
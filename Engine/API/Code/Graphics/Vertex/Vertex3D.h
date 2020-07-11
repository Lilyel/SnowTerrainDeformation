#ifndef _VERTEX3D_AERO_H_
#define _VERTEX3D_AERO_H_

#include "../../Toolbox/Toolbox.h"
#include "../Color/Color.h"
#include "../../Maths/Vector/Vector2.h"
#include "../../Maths/Vector/Vector3.h"

#include <string>
#include <iostream>

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Represent a 3D point that can be rendered.
	/// Contains a position, a color and texture coordinates.
	/// </summary>
	class AERO_CORE_EXPORT Vertex3D
	{
	public:
		/// <summary>
		/// Default construtor.
		/// </summary>
		Vertex3D();

		/// <summary>
		/// Build a vertex from a position.
		/// The color will be White and the UV (0, 0).
		/// </summary>
		/// <param name="_Position">3D Position to build the vertex from.</param>
		Vertex3D( const Vector3& _Position );

		/// <summary>
		/// Build a vertex from a position and a color.
		/// The UV will be (0, 0).
		/// </summary>
		/// <param name="_Position">3D Position to build the vertex from.</param>
		/// <param name="_Color">Color of the vertex.</param>
		Vertex3D( const Vector3& _Position, const Color& _Color );

		/// <summary>
		/// Build a vertex from a position, a color and texture coordinates (UV).
		/// </summary>
		/// <param name="_Position">3D Position to build the vertex from.</param>
		/// <param name="_Color">Color of the vertex.</param>
		/// <param name="_UV">Texture coordinates of the vertex.</param>
		Vertex3D( const Vector3& _Position, const Color& _Color, const Vector2& _UV );

		/// <summary>
		/// Build a vertex from a position, a color and texture coordinates (UV).
		/// </summary>
		/// <param name="_Position">3D Position to build the vertex from.</param>
		/// <param name="_Color">Color of the vertex.</param>
		/// <param name="_UV">Texture coordinates of the vertex.</param>
		/// <param name="_Normal">Normal of the vertex.</param>
		Vertex3D( const Vector3& _Position, const Color& _Color, const Vector2& _UV, const Vector3& _Normal );

		/// <summary>Compare two vertices.</summary>
		/// <param name="_VertexB">Array to compare with.</param>
		/// <returns>True if vertex are the same, False otherwise.</returns>
		inline Bool operator==( const Vertex3D& _VertexB ) const;


		/// <summary>Compare two vertices.</summary>
		/// <param name="_VertexB">Vertex to compare with.</param>
		/// <returns>True if vertex are different, False otherwise.</returns>
		inline Bool operator!=( const Vertex3D& _VertexB ) const;

	public:
		/// <summary>3D position of the vertex.</summary>
		Vector3 Position;

		/// <summary>Color of the vertex. </summary>
		Color Color;

		/// <summary>Texture coordinates of the vertex.</summary>
		Vector2 UV;

		/// <summary>3D normal vector of the vertex.</summary>
		Vector3 Normal;
	};


    /// <summary>
    /// Convert a vertex 3D to a string.
    /// </summary>
    /// <param name="_Color">Vertex 3D to convert.</param>
    /// <returns>Vertex 3D as a C++ string. ( Order : Position, Color, Normal, UV ).</returns>
    AERO_CORE_EXPORT inline std::string ToString( const Vertex3D& _Vertex );


} // ae

/// <summary>
/// Convert a vertex 3D to a string and push it in the out stream.
/// </summary>
/// <param name="_Color">Vertex 3D to convert and push to the out stream.</param>
/// <returns>Out stream.</returns>
AERO_CORE_EXPORT std::ostream& operator<<( std::ostream& os, const ae::Vertex3D& _Vertex );

#endif
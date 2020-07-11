#pragma once

#include "../../../Toolbox/Toolbox.h"
#include "../../Color/Color.h"
#include "../../Vertex/Vertex2D.h"
#include "../../Drawable/TransformableDrawable2D.h"

#include <array>

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Represent a 2D models in the scene.<para/>
	/// By default, the material is initialized with the parameters for the 2D shader shipped with the engine.
	/// </summary>
	/// <seealso cref="Transform2D" />
	/// <seealso cref="Drawable" />
	class AERO_CORE_EXPORT Mesh2D : public TransformableDrawable2D
	{
	public:
		/// <summary>Cannot create an empty mesh.</summary>
		Mesh2D() = delete;

		/// <summary>Build an empty mesh but reserve vertices and indices.</summary>
		/// <param name="_VerticesCount">Count of vertices to reserve.</param>
		/// <param name="_IndicesCount">Count of indices to reserve.</param>
		explicit Mesh2D( const Uint32 _VerticesCount, const Uint32 _IndicesCount );

		/// <summary>Build a mesh with vertices and indices.</summary>
		/// <param name="_Vertices">Vertices of the mesh.</param>
		/// <param name="_Indices">Indices of vertices of each triangles.</param>
		explicit Mesh2D( const Vertex2DArray& _Vertices, const IndexArray& _Indices );


		/// <summary>Build an empty mesh but reserve vertices and indices.</summary>
		/// <param name="_VerticesCount">Count of vertices to reserve.</param>
		/// <param name="_IndicesCount">Count of indices to reserve.</param>
		void Setup( const Uint32 _VerticesCount, const Uint32 _IndicesCount );

		/// <summary>Build a mesh with vertices and indices.</summary>
		/// <param name="_Vertices">Vertices of the mesh.</param>
		/// <param name="_Indices">Indices of vertices of each triangles.</param>
		void Setup( const Vertex2DArray& _Vertices, const IndexArray& _Indices );

		/// <summary>
		/// Build a mesh with vertices and indices.<para/>
		/// Vertices and indices provided become invalid after this call.
		/// </summary>
		/// <param name="_Vertices">Vertices of the mesh.</param>
		/// <param name="_Indices">Indices of vertices of each triangles.</param>
		void Setup( Vertex2DArray&& _Vertices, IndexArray&& _Indices );


		/// <summary>Retrieve one vertex. Read Only.</summary>
		/// <param name="_Index">Index of the vertex to retrieve.</param>
		/// <returns>Vertex at the specified index. Read Only.</returns>
		const Vertex2D& operator[]( const Uint32 _Index ) const;

		/// <summary>Retrieve one vertex.</summary>
		/// <param name="_Index">Index of the vertex to retrieve.</param>
		/// <returns>Vertex at the specified index.</returns>
		Vertex2D& operator[]( const Uint32 _Index );


		/// <summary>Set a vertex at a specified index.</summary>
		/// <param name="_Index">Index of the vertex to modify.</param>
		/// <param name="_Vertex">New properties of the vertex.</param>
		void SetVertex( const Uint32 _Index, const Vertex2D& _Vertex );

		/// <summary>Retrieve one vertex. Read Only.</summary>
		/// <param name="_Index">Index of the vertex to retrieve.</param>
		/// <returns>Vertex at the specified index. Read Only.</returns>
		const Vertex2D& GetVertex( const Uint32 _Index ) const;


		/// <summary>Set a triangle index.</summary>
		/// <param name="_Index">Index to set.</param>
		/// <param name="_Value">New value for the index.</param>
		void SetIndice( const Uint32 _Index, const Uint32 _Value );

		/// <summary>Setup a triangle.</summary>
		/// <param name="_TriangleIndex">Triangle index to modify.</param>
		/// <param name="_Values">New indices for the triangle.</param>
		void SetTriangleIndices( const Uint32 _TriangleIndex, const Uint32 _Values[3] );

		/// <summary>Setup a quad.</summary>
		/// <param name="_QuadIndex">Quad index to modify.</param>
		/// <param name="_Values">New indices for the quad.</param>
		void SetQuadIndices( const Uint32 _QuadIndex, const Uint32 _Values[4] );

		/// <summary>Get a triangle index value.</summary>
		/// <param name="_Index">Triangle index to get the value.</param>
		/// <returns>Value of the triangle index.</returns>
		Uint32 GetIndice( const Uint32 _Index ) const;




		/// <summary>Apply modifications done to the vertices and indices.</summary>
		void ApplyChanges();


		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor() override;


	protected:

		/// <summary>Vertices of the mesh.</summary>
		Vertex2DArray m_Vertices;

		/// <summary>Triangles indices.</summary>
		IndexArray m_Indices;
	};

} // ae
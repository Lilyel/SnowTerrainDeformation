#pragma once

#include "../../../Toolbox/Toolbox.h"
#include "Mesh3D.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Simple 3D colored cube.
	/// </summary>
	/// <seealso cref="Mesh3D" />
	/// <seealso cref="Drawable" />
	class AERO_CORE_EXPORT CubeMesh : public Mesh3D
	{
	public:
		/// <summary>Create a colored cube with a side size.</summary>
		/// <param name="_Size">The size of cube side size.</param>
		/// <param name="_SubdivisionWidth">Number of face along the width of the cube.</param>
		/// <param name="_SubdivisionHeight">Number of face along the height of the cube.</param>
		/// <param name="_SubdivisionDepth">Number of face along the depth of the cube.</param>
		CubeMesh( const float _Size = 1.0f, Uint32 _SubdivisionWidth = 1, Uint32 _SubdivisionHeight = 1, Uint32 _SubdivisionDepth = 1 );


		/// <summary>Set the side size of the cube.</summary>
		/// <param name="_Size">The new size to apply.</param>
		void SetSize( const float _Size );

		/// <summary>Retrieve the size of the cube.</summary>
		/// <returns>The size of the cube.</returns>
		float GetSize() const;


		/// <summary>Retrieve the number of the face along the width of the cube.</summary>
		/// <returns>The number of face along the width of the cube.</returns>
		Uint32 GetSubdivisionWidth() const;

		/// <summary>Set the number of the face along the width of the cube.</summary>
		/// <param name="_Subdvision">The new number of face along the width of the cube.</param>
		void SetSubdivisionWidth( Uint32 _Subdvision );

		/// <summary>Retrieve the number of the face along the height of the cube.</summary>
		/// <returns>The number of face along the height of the cube.</returns>
		Uint32 GetSubdivisionHeight() const;

		/// <summary>Set the number of the face along the height of the cube.</summary>
		/// <param name="_Subdvision">The new number of face along the height of the cube.</param>
		void SetSubdivisionHeight( Uint32 _Subdvision );

		/// <summary>Retrieve the number of the face along the height of the cube.</summary>
		/// <returns>The number of face along the height of the cube.</returns>
		Uint32 GetSubdivisionDepth() const;

		/// <summary>Set the number of the face along the height of the cube.</summary>
		/// <param name="_Subdvision">The new number of face along the height of the cube.</param>
		void SetSubdivisionDepth( Uint32 _Subdvision );


		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor() override;

	private:
		/// <summary>Create the cube mesh according to the stored parameters.</summary>
		void GenerateCubeMesh();

		/// <summary>Create the cube mesh according to the stored parameters.</summary>
		/// <param name="_Vertices">Allocated vertices array to setup.</param>
		/// <param name="_Indices">Allocated indices array to setup.</param>
		void SetupVerticesAndIndices( AE_InOut Vertex3DArray& _Vertices, AE_InOut IndexArray& _Indices );

		/// <summary>Generate the a plane mesh for a cube side.</summary>
		/// <param name="_Vertices">The vertices array containing the cube mesh to modify.</param>
		/// <param name="_Indices">The indices array containing the faces to modify.</param>
		/// <param name="_iTri">The index of the first free face index.</param>
		/// <param name="_iVertex">The index of the free vertex.</param>
		/// <param name="_ExtremePoints">The extreme points of the side plane.</param>
		/// <param name="_Normal">The normal of the side.</param>
		/// <param name="_WidthVerticesCount">The number of points along the width of the plane.</param>
		/// <param name="_HeightVerticesCount">The number of points along the height of the plane.</param>
		void SetupVerticesAndIndicesSide( AE_InOut Vertex3DArray& _Vertices, AE_InOut IndexArray& _Indices,
										  AE_InOut size_t& _iTri, AE_InOut size_t& _iVertex,
										  const Vector3 _ExtremePoints[4], const Vector3& _Normal,
										  size_t _WidthVerticesCount, size_t _HeightVerticesCount );

	private:
		/// <summary>Size of the cube.</summary>
		float m_Size;

		/// <summary>Number of face along the width of the cube.</summary>
		Uint32 m_SubdivisionWidth;

		/// <summary>Number of face along the height of the cube.</summary>
		Uint32 m_SubdivisionHeight;

		/// <summary>Number of face along the depth of the cube.</summary>
		Uint32 m_SubdivisionDepth;
	};
} // ae

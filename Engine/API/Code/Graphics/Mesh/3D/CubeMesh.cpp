#include "CubeMesh.h"

#include "../../../Editor/TypesToEditor/CubeMeshToEditor.h"

namespace ae
{
	CubeMesh::CubeMesh( const float _Size, Uint32 _SubdivisionWidth, Uint32 _SubdivisionHeight, Uint32 _SubdivisionDepth ) :
		Mesh3D( 0, 0 ),
		m_Size( _Size ),
		m_SubdivisionWidth( Math::Max( _SubdivisionWidth, 1u ) ),
		m_SubdivisionHeight( Math::Max( _SubdivisionHeight, 1u ) ),
		m_SubdivisionDepth( Math::Max( _SubdivisionDepth, 1u ) )
	{
		GenerateCubeMesh();

		SetName( std::string( "StaticCube_" ) + std::to_string( GetObjectID() ) );
	}


	void CubeMesh::SetSize( const float _Size )
	{
		m_Size = _Size;

		SetupVerticesAndIndices( m_Vertices, m_Indices );
	}

	float CubeMesh::GetSize() const
	{
		return m_Size;
	}

	Uint32 CubeMesh::GetSubdivisionWidth() const
	{
		return m_SubdivisionWidth;
	}

	void CubeMesh::SetSubdivisionWidth( Uint32 _Subdvision )
	{
		m_SubdivisionWidth = Math::Max( _Subdvision, 1u );

		GenerateCubeMesh();
	}

	Uint32 CubeMesh::GetSubdivisionHeight() const
	{
		return m_SubdivisionHeight;
	}

	void CubeMesh::SetSubdivisionHeight( Uint32 _Subdvision )
	{
		m_SubdivisionHeight = Math::Max( _Subdvision, 1u );

		GenerateCubeMesh();
	}

	Uint32 CubeMesh::GetSubdivisionDepth() const
	{
		return m_SubdivisionDepth;
	}

	void CubeMesh::SetSubdivisionDepth( Uint32 _Subdvision )
	{
		m_SubdivisionDepth = Math::Max( _Subdvision, 1u );

		GenerateCubeMesh();
	}

	void CubeMesh::ToEditor()
	{
		Mesh3D::ToEditor();
		priv::ui::CubeMeshToEditor( *this );
	}

	void CubeMesh::GenerateCubeMesh()
	{
		// Allocate the mesh memory.

		const size_t WidthVerticesCount = Cast( size_t, m_SubdivisionWidth ) + 1;
		const size_t HeightVerticesCount = Cast( size_t, m_SubdivisionHeight ) + 1;
		const size_t DepthVerticesCount = Cast( size_t, m_SubdivisionDepth ) + 1;

		size_t CountVertices = WidthVerticesCount * HeightVerticesCount * 2;
		CountVertices += WidthVerticesCount * DepthVerticesCount * 2;
		CountVertices += HeightVerticesCount * DepthVerticesCount * 2;

		size_t CountIndices = 6 * Cast( size_t, m_SubdivisionWidth ) * Cast( size_t, m_SubdivisionHeight ) * 2;
		CountIndices += 6 * Cast( size_t, m_SubdivisionWidth ) * Cast( size_t, m_SubdivisionDepth ) * 2;
		CountIndices += 6 * Cast( size_t, m_SubdivisionHeight ) * Cast( size_t, m_SubdivisionDepth ) * 2;

		Vertex3DArray Vertices( CountVertices );
		IndexArray Indices( CountIndices );

		SetupVerticesAndIndices( Vertices, Indices );

		Setup( std::move( Vertices ), std::move( Indices ) );
	}

	void CubeMesh::SetupVerticesAndIndices( AE_InOut Vertex3DArray& _Vertices, AE_InOut IndexArray& _Indices )
	{
		const size_t WidthVerticesCount = Cast( size_t, m_SubdivisionWidth ) + 1;
		const size_t HeightVerticesCount = Cast( size_t, m_SubdivisionHeight ) + 1;
		const size_t DepthVerticesCount = Cast( size_t, m_SubdivisionDepth ) + 1;

		// Setup the mesh vertices and faces.


		const float HalfSize = m_Size * 0.5f;
		size_t iTri = 0;
		size_t iVertex = 0;

		// Front.
		const Vector3 FrontExtremes[4] =
		{
			Vector3( -HalfSize, -HalfSize, HalfSize ),
			Vector3( HalfSize, -HalfSize, HalfSize ),
			Vector3( HalfSize, HalfSize, HalfSize ),
			Vector3( -HalfSize, HalfSize, HalfSize )
		};
		SetupVerticesAndIndicesSide( _Vertices, _Indices, iTri, iVertex, FrontExtremes, Vector3::AxeZ, WidthVerticesCount, HeightVerticesCount );


		// Top.
		const Vector3 TopExtremes[4] =
		{
			Vector3( -HalfSize, HalfSize, -HalfSize ),
			Vector3( -HalfSize, HalfSize, HalfSize ),
			Vector3( HalfSize, HalfSize, HalfSize ),
			Vector3( HalfSize, HalfSize, -HalfSize )
		};
		SetupVerticesAndIndicesSide( _Vertices, _Indices, iTri, iVertex, TopExtremes, Vector3::AxeY, DepthVerticesCount, WidthVerticesCount );


		// Back.
		const Vector3 BackExtremes[4] =
		{
			Vector3( -HalfSize, -HalfSize, -HalfSize ),
			Vector3( -HalfSize, HalfSize, -HalfSize ),
			Vector3( HalfSize, HalfSize, -HalfSize ),
			Vector3( HalfSize, -HalfSize, -HalfSize )
		};
		SetupVerticesAndIndicesSide( _Vertices, _Indices, iTri, iVertex, BackExtremes, -Vector3::AxeZ, HeightVerticesCount, WidthVerticesCount );


		// Left.
		const Vector3 LeftExtremes[4] =
		{
			Vector3( -HalfSize, -HalfSize, -HalfSize ),
			Vector3( -HalfSize, -HalfSize, HalfSize ),
			Vector3( -HalfSize, HalfSize, HalfSize ),
			Vector3( -HalfSize, HalfSize, -HalfSize )
		};
		SetupVerticesAndIndicesSide( _Vertices, _Indices, iTri, iVertex, LeftExtremes, -Vector3::AxeX, DepthVerticesCount, HeightVerticesCount );


		// Bottom.
		const Vector3 BottomExtremes[4] =
		{
			Vector3( -HalfSize, -HalfSize, -HalfSize ),
			Vector3( HalfSize, -HalfSize, -HalfSize ),
			Vector3( HalfSize, -HalfSize, HalfSize ),
			Vector3( -HalfSize, -HalfSize, HalfSize )
		};
		SetupVerticesAndIndicesSide( _Vertices, _Indices, iTri, iVertex, BottomExtremes, -Vector3::AxeY, WidthVerticesCount, DepthVerticesCount );


		// Right.
		const Vector3 RightExtremes[4] =
		{
			Vector3( HalfSize, -HalfSize, -HalfSize ),
			Vector3( HalfSize, HalfSize, -HalfSize ),
			Vector3( HalfSize, HalfSize, HalfSize ),
			Vector3( HalfSize, -HalfSize, HalfSize )
		};
		SetupVerticesAndIndicesSide( _Vertices, _Indices, iTri, iVertex, RightExtremes, Vector3::AxeX, HeightVerticesCount, DepthVerticesCount );
	}

	void CubeMesh::SetupVerticesAndIndicesSide( AE_InOut Vertex3DArray& _Vertices, AE_InOut IndexArray& _Indices,
												  AE_InOut size_t& _iTri, AE_InOut size_t& _iVertex,
												  const Vector3 _ExtremePoints[4], const Vector3& _Normal,
												  size_t _WidthVerticesCount, size_t _HeightVerticesCount )
	{
		const size_t VertexOffset = _iVertex;

		for( size_t h = 0; h < _HeightVerticesCount; h++ )
		{
			const float TimeH = Cast( float, h ) / Cast( float, _HeightVerticesCount - 1 );

			for( size_t w = 0; w < _WidthVerticesCount; w++ )
			{
				const float TimeW = Cast( float, w ) / Cast( float, _WidthVerticesCount - 1 );


				Vertex3D& Vertex = _Vertices[_iVertex];
				Vertex.Position = Math::BiLerp( _ExtremePoints[0], _ExtremePoints[1], _ExtremePoints[2], _ExtremePoints[3], TimeW, TimeH );
				Vertex.Normal = _Normal;
				Vertex.UV.Set( TimeW, TimeH );
				_iVertex++;

				// If we are not on the last line or column, add the 2 triangles of the current quad.
				if( w < _WidthVerticesCount - 1 && h < _HeightVerticesCount - 1 )
				{
					const Uint32 A = Cast( Uint32, VertexOffset + h * _WidthVerticesCount + w );
					const Uint32 B = Cast( Uint32, VertexOffset + h * _WidthVerticesCount + w + 1 );
					const Uint32 C = Cast( Uint32, VertexOffset + ( h + 1 ) * _WidthVerticesCount + w + 1 );
					const Uint32 D = Cast( Uint32, VertexOffset + ( h + 1 ) * _WidthVerticesCount + w );

					_Indices[_iTri] = A;
					_Indices[_iTri + 1] = B;
					_Indices[_iTri + 2] = C;

					_iTri += 3;

					_Indices[_iTri] = A;
					_Indices[_iTri + 1] = C;
					_Indices[_iTri + 2] = D;

					_iTri += 3;
				}
			}
		}
	}

} // ae
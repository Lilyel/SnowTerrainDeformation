#include "PlaneMesh.h"

#include "../../../Editor/TypesToEditor/PlaneMeshToEditor.h"

namespace ae
{
	PlaneMesh::PlaneMesh( const float _Size, Uint32 _SubdivisionWidth, Uint32 _SubdivisionHeight ) :
		Mesh3D( 0, 0 ),
		m_Size( _Size ),
		m_SubdivisionWidth( Math::Max( _SubdivisionWidth, 1u ) ),
		m_SubdivisionHeight( Math::Max( _SubdivisionHeight, 1u ) )
	{
		GeneratePlaneMesh();

		SetName( std::string( "PlaneMesh_" ) + std::to_string( GetObjectID() ) );
	}

	void PlaneMesh::SetSize( const float _Size )
	{
		m_Size = _Size;

		const float HalfSize = m_Size * 0.5f;

		const Vector3 BottomLeft( -HalfSize, 0.0f, -HalfSize );
		const Vector3 BottomRight( HalfSize, 0.0f, -HalfSize );
		const Vector3 TopRight( HalfSize, 0.0f, HalfSize );
		const Vector3 TopLeft( -HalfSize, 0.0f, HalfSize );

		const Uint32 WidthVerticesCount = m_SubdivisionWidth + 1;
		const Uint32 HeightVerticesCount = m_SubdivisionHeight + 1;

		for( Uint32 w = 0; w < WidthVerticesCount; w++ )
		{
			const float TimeW = Cast( float, w ) / Cast( float, m_SubdivisionWidth );

			for( Uint32 h = 0; h < HeightVerticesCount; h++ )
			{
				const float TimeH = Cast( float, h ) / Cast( float, m_SubdivisionHeight );

				Vertex3D& Vertex = Mesh3D::operator[]( h* WidthVerticesCount + w );

				Vertex.Position = Math::BiLerp( BottomLeft, BottomRight, TopRight, TopLeft, TimeW, TimeH );
			}
		}
	}

	float PlaneMesh::GetSize() const
	{
		return m_Size;
	}

	Uint32 PlaneMesh::GetSubdivisionWidth() const
	{
		return m_SubdivisionWidth;
	}

	void PlaneMesh::SetSubdivisionWidth( Uint32 _Subdvision )
	{
		m_SubdivisionWidth = Math::Max( _Subdvision, 1u );

		GeneratePlaneMesh();
	}

	Uint32 PlaneMesh::GetSubdivisionHeight() const
	{
		return m_SubdivisionHeight;
	}

	void PlaneMesh::SetSubdivisionHeight( Uint32 _Subdvision )
	{
		m_SubdivisionHeight = Math::Max( _Subdvision, 1u );

		GeneratePlaneMesh();
	}

	void PlaneMesh::ToEditor()
	{
		Mesh3D::ToEditor();
		priv::ui::PlaneMeshToEditor( *this );
	}

	void PlaneMesh::GeneratePlaneMesh()
	{
		const float HalfSize = m_Size * 0.5f;

		const size_t WidthVerticesCount = Cast( size_t, m_SubdivisionWidth ) + 1;
		const size_t HeightVerticesCount = Cast( size_t, m_SubdivisionHeight ) + 1;

		const size_t CountVertices = WidthVerticesCount * HeightVerticesCount;
		const size_t CountIndices = 6 * Cast( size_t, m_SubdivisionWidth ) * Cast( size_t, m_SubdivisionHeight );

		Vertex3DArray Vertices( CountVertices );
		IndexArray Indices( CountIndices );

		const Vector3 BottomLeft( -HalfSize, 0.0f, -HalfSize );
		const Vector3 BottomRight( HalfSize, 0.0f, -HalfSize );
		const Vector3 TopRight( HalfSize, 0.0f, HalfSize );
		const Vector3 TopLeft( -HalfSize, 0.0f, HalfSize );

		size_t iTri = 0;

		for( size_t h = 0; h < HeightVerticesCount; h++ )
		{
			const float TimeH = Cast( float, h ) / Cast( float, m_SubdivisionHeight );

			for( size_t w = 0; w < WidthVerticesCount; w++ )
			{
				const float TimeW = Cast( float, w ) / Cast( float, m_SubdivisionWidth );

				Vertex3D& Vertex = Vertices[h * WidthVerticesCount + w];

				Vertex.Position = Math::BiLerp( BottomLeft, BottomRight, TopRight, TopLeft, TimeW, TimeH );
				Vertex.Normal.Set( 0.0f, 1.0f, 0.0f );
				Vertex.UV.Set( TimeW, TimeH );

				// If we are not on the last line or column, add the 2 triangles of the current quad.
				if( w < m_SubdivisionWidth && h < m_SubdivisionHeight )
				{
					const Uint32 A = Cast( Uint32, h * WidthVerticesCount + w );
					const Uint32 B = Cast( Uint32, h * WidthVerticesCount + w + 1 );
					const Uint32 C = Cast( Uint32, ( h + 1 ) * WidthVerticesCount + w + 1 );
					const Uint32 D = Cast( Uint32, ( h + 1 ) * WidthVerticesCount + w );

					Indices[iTri] = A;
					Indices[iTri + 1] = C;
					Indices[iTri + 2] = B;

					iTri += 3;

					Indices[iTri] = A;
					Indices[iTri + 1] = D;
					Indices[iTri + 2] = C;

					iTri += 3;
				}
			}
		}


		Setup( std::move( Vertices ), std::move( Indices ) );
	}

} // ae

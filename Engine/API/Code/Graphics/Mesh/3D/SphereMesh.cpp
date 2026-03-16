#include "SphereMesh.h"

#include "../../../Maths/Maths.h"

#include "../../../Editor/TypesToEditor/SphereMeshToEditor.h"

namespace ae
{
	SphereMesh::SphereMesh( const float _Radius, const Uint32 _RingCount, const Uint32 _SegmentCount ) :
		Mesh3D( 0, 0 ),
		m_Radius( Math::Max( _Radius, Math::Epsilon() ) ),
		m_RingCount( std::max( _RingCount, 3u ) ),
		m_SegmentCount( std::max( _SegmentCount, 3u ) )
	{
		GenerateUVSphere();

		SetName( std::string( "SphereMesh_" ) + std::to_string( GetObjectID() ) );
	}

	void SphereMesh::SetRadius( const float _Radius )
	{
		m_Radius = Math::Max( _Radius, Math::Epsilon() );

		for( Vertex3D& Vertex : m_Vertices )
			Vertex.Position = Vertex.Position.GetNormalized() * m_Radius;
	}

	float SphereMesh::GetRadius() const
	{
		return m_Radius;
	}

	void SphereMesh::SetRingCount( const Uint32 _RingCount )
	{
		m_RingCount = std::max( _RingCount, 3u );

		GenerateUVSphere();
	}

	Uint32 SphereMesh::GetRingCount() const
	{
		return m_RingCount;
	}

	void SphereMesh::SetSegmentCount( const Uint32 _SegmentCount )
	{
		m_SegmentCount = std::max( _SegmentCount, 3u );

		GenerateUVSphere();
	}

	Uint32 SphereMesh::GetSegmentCount() const
	{
		return m_SegmentCount;
	}

	void SphereMesh::ToEditor()
	{
		Mesh3D::ToEditor();
		priv::ui::SphereMeshToEditor( *this );
	}

	void SphereMesh::GenerateUVSphere()
	{
		// Count vertices : 
		// 1 for each pole : + 2
		// m_SegmentCount for each seperation between rings : m_RingCount - 1.

		// Count indices :
		// A triangle for each m_SegmentCount on both poles : m_SegmentCount * 3 * 2
		// A quad (2*triangles) for each m_RingCount and m_SegmentCount without poles : ( m_RingCount - 2 ) * ( 2 * 3 ) * m_SegmentCount

		const Uint32 TotalVerticesCount = ( m_RingCount - 1 ) * m_SegmentCount + 2;
		const Uint32 TotalIndicesCount = ( m_SegmentCount * 3 * 2 ) + ( ( m_RingCount - 2 ) * 2 * 3 * m_SegmentCount );

		Vertex3DArray Vertices( TotalVerticesCount );
		IndexArray Indices( TotalIndicesCount );
				

		const float SegmentStep = Math::PiMulBy2() / Cast( float, m_SegmentCount ); // Segments cover a complete revolution.
		const float RingStep = Math::Pi() / Cast( float, m_RingCount );

		// Rings go from -Pi/2 to Pi/2.
		constexpr float MaxRingAngle = Math::PiDivBy2();
		float RingAngle = -MaxRingAngle + RingStep; // Start ring after the pole.

		Uint32 iVertex = 0;
		// Do point for first ring (we skip the first pole) to the last ring (skip the last pole).
		for( Uint32 iRing = 0; iRing < m_RingCount - 1; iRing++, RingAngle += RingStep )
		{
			float SegmentAngle = 0.0f;
			for( Uint32 iSegment = 0; iSegment < m_SegmentCount; iSegment++, SegmentAngle += SegmentStep )
			{
				Vertex3D& Vertex = Vertices[iVertex];

				Vector3& VertexPosition = Vertex.Position;
				VertexPosition.X = m_Radius * Math::Sin( SegmentAngle ) * Math::Cos( RingAngle );
				VertexPosition.Y = m_Radius * Math::Sin( RingAngle );
				VertexPosition.Z = m_Radius * Math::Cos( SegmentAngle ) * Math::Cos( RingAngle );

				Vertex.Normal = VertexPosition.GetNormalized();

				Vertex.UV = GetPointUV( Vertex.Normal );


				iVertex++;
			}
		}

		// Add poles.
		Vertex3D& TopPoleVertex = Vertices[iVertex];

		Vector3& TopPolePosition = TopPoleVertex.Position;
		TopPolePosition.X = m_Radius * Math::Cos( -MaxRingAngle );
		TopPolePosition.Y = m_Radius * Math::Sin( -MaxRingAngle );
		TopPolePosition.Z = m_Radius * Math::Cos( -MaxRingAngle );

		TopPoleVertex.Normal = TopPolePosition.GetNormalized();

		TopPoleVertex.UV = GetPointUV( TopPoleVertex.Normal );


		const Uint32 TopID = iVertex;
		iVertex++;


		Vertex3D& BottomPoleVertex = Vertices[iVertex];

		Vector3& BottomPolePosition = BottomPoleVertex.Position;
		BottomPolePosition.X = m_Radius * Math::Cos( MaxRingAngle );
		BottomPolePosition.Y = m_Radius * Math::Sin( MaxRingAngle );
		BottomPolePosition.Z = m_Radius * Math::Cos( MaxRingAngle );

		BottomPoleVertex.Normal = BottomPolePosition.GetNormalized();

		BottomPoleVertex.UV = GetPointUV( BottomPoleVertex.Normal );

		const Uint32 BottomID = iVertex;


		// Add faces

		size_t iTri = 0;

		// Add faces not linked to the poles first. (Only quads here).
		for( Uint32 iRing = 0; iRing < m_RingCount - 2; iRing++ )
		{
			const Uint32 iNextRing = iRing + 1;

			for( Uint32 iSegment = 0; iSegment < m_SegmentCount; iSegment++ )
			{
				const Uint32 iNextSegment = ( iSegment + 1 ) % m_SegmentCount;

				Indices[iTri] = iRing * m_SegmentCount + iSegment;
				Indices[iTri + 1] = iRing * m_SegmentCount + iNextSegment;
				Indices[iTri + 2] = iNextRing * m_SegmentCount + iNextSegment;
				
				iTri += 3;

				Indices[iTri] = iRing * m_SegmentCount + iSegment;
				Indices[iTri + 1] = iNextRing * m_SegmentCount + iNextSegment;
				Indices[iTri + 2] = iNextRing * m_SegmentCount + iSegment;
				
				iTri += 3;
			}
		}

		// Add faces linked to the poles. (Triangles here).
		const Uint32 LastLineOffset = ( m_RingCount - 2 ) * m_SegmentCount;

		for( Uint32 iSegment = 0; iSegment < m_SegmentCount; iSegment++ )
		{
			const Uint32 iNextSegment = ( iSegment + 1 ) % m_SegmentCount;

			// Top pole.
			Indices[iTri] = TopID;
			Indices[iTri + 1] = iNextSegment;
			Indices[iTri + 2] = iSegment;
			
			iTri += 3;

			// Bottom pole.
			Indices[iTri ] = BottomID;
			Indices[iTri + 1] = LastLineOffset + iSegment;
			Indices[iTri + 2] = LastLineOffset + iNextSegment;
			
			iTri += 3;
		}

		Setup( std::move( Vertices ), std::move( Indices ) );
	}

	Vector2 SphereMesh::GetPointUV( const Vector3& _Normal )
	{
		const Vector3 ToOrigin = -_Normal;

		const float U = 0.5f + ( Math::ATan2( ToOrigin.Z, ToOrigin.X ) / Math::PiMulBy2() );
		const float V = 0.5f - ( Math::ASin( ToOrigin.Y ) / Math::Pi() );

		return Vector2( U, V );
	}

} // ae
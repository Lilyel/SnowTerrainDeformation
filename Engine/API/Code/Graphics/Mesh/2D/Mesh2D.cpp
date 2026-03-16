#include "Mesh2D.h"

#include "../../../Debugging/Debugging.h"
#include "../../Renderer/Renderer.h"
#include "../../../Aero/Aero.h"
#include "../../Material/SpriteMaterial.h"

#include "../../../Editor/TypesToEditor/MaterialToEditor.h"

namespace ae
{

	Mesh2D::Mesh2D( const Uint32 _VerticesCount, const Uint32 _IndicesCount ) :
		m_Vertices( _VerticesCount ),
		m_Indices( _IndicesCount )
	{
		SetBufferType( BufferType::Static );
		SetAttributePointerTags( AttributePointer::Default2D );

		SetMaterial( *Aero.GetResourcesManager().GetDefault2DMaterial() );

		ApplyChanges();

		SetName( std::string( "Mesh2D_" ) + std::to_string( GetObjectID() ) );
	}

	Mesh2D::Mesh2D( const Vertex2DArray& _Vertices, const IndexArray& _Indices ) :
		m_Vertices( _Vertices ),
		m_Indices( _Indices )
	{
		SetBufferType( BufferType::Static );
		SetAttributePointerTags( AttributePointer::Default2D );

		SetMaterial( *Aero.GetResourcesManager().GetDefault2DMaterial() );

		ApplyChanges();

		SetName( std::string( "Mesh2D_" ) + std::to_string( GetObjectID() ) );
	}

	void Mesh2D::Setup( const Uint32 _VerticesCount, const Uint32 _IndicesCount )
	{
		m_Vertices.clear();
		m_Vertices.resize( _VerticesCount );

		m_Indices.clear();
		m_Indices.resize( _IndicesCount );

		ApplyChanges();
	}

	void Mesh2D::Setup( const Vertex2DArray& _Vertices, const IndexArray& _Indices )
	{
		m_Vertices = _Vertices;
		m_Indices = _Indices;

		ApplyChanges();
	}

	void Mesh2D::Setup( Vertex2DArray&& _Vertices, IndexArray&& _Indices )
	{
		m_Vertices = std::move( _Vertices );
		m_Indices = std::move( _Indices );

		ApplyChanges();
	}

	const Vertex2D& Mesh2D::operator[]( const Uint32 _Index ) const
	{
		return m_Vertices[_Index];
	}

	Vertex2D& Mesh2D::operator[]( const Uint32 _Index )
	{
		return m_Vertices[_Index];
	}

	void Mesh2D::SetVertex( const Uint32 _Index, const Vertex2D& _Vertex )
	{
		m_Vertices[_Index] = _Vertex;
	}

	const Vertex2D& Mesh2D::GetVertex( const Uint32 _Index ) const
	{
		return m_Vertices[_Index];
	}

	void Mesh2D::SetIndice( const Uint32 _Index, const Uint32 _Value )
	{
		m_Indices[_Index] = _Value;
	}

	void Mesh2D::SetTriangleIndices( const Uint32 _TriangleIndex, const Uint32 _Values[3] )
	{
		if( GetPrimitiveType() != PrimitiveType::Triangles )
			throw std::exception( "Incompatible mesh primitive type with SetTriangleIndices function. Must be set to PrimitiveType::Triangles." );

		if( m_Indices.size() < 3 || _TriangleIndex > ( m_Indices.size() - 3 ) )
			throw std::out_of_range( "Index out of range." );

		const size_t IndiceStart = Cast( size_t, _TriangleIndex ) * Cast( size_t, 3 );

		m_Indices[IndiceStart] = _Values[0];
		m_Indices[IndiceStart + 1] = _Values[1];
		m_Indices[IndiceStart + 2] = _Values[2];
	}

	void Mesh2D::SetQuadIndices( const Uint32 _QuadIndex, const Uint32 _Values[4] )
	{
		if( GetPrimitiveType() != PrimitiveType::Quads )
			throw std::exception( "Incompatible mesh primitive type with SetQuadIndices function. Must be set to PrimitiveType::Quads." );

		if( m_Indices.size() < 4 || _QuadIndex > ( m_Indices.size() - 4 ) )
			throw std::out_of_range( "Index out of range." );

		const size_t IndiceStart = Cast( size_t, _QuadIndex ) * Cast( size_t, 4 );

		m_Indices[IndiceStart] = _Values[0];
		m_Indices[IndiceStart + 1] = _Values[1];
		m_Indices[IndiceStart + 2] = _Values[2];
		m_Indices[IndiceStart + 3] = _Values[3];
	}

	Uint32 Mesh2D::GetIndice( const Uint32 _Index ) const
	{
		return m_Indices[_Index];
	}

	void Mesh2D::ApplyChanges()
	{
		UpdateBuffers( m_Vertices, m_Indices );
	}

	void Mesh2D::ToEditor()
	{
		WorldObject::ToEditor();
		Transform2D::ToEditor();
		priv::ui::MaterialToEditor( GetMaterial() );
	}

} // ae

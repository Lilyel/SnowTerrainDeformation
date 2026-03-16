#include "QuadMesh.h"

#include "../../Renderer/Renderer.h"

#include "../../Material/SpriteMaterial.h"

#include "../../../Aero/Aero.h"

#include "../../../Editor/TypesToEditor/WorldObjectToEditor.h"
#include "../../../Editor/TypesToEditor/Transform2DToEditor.h"
#include "../../../Editor/TypesToEditor/QuadMeshToEditor.h"

namespace ae
{

    QuadMesh::QuadMesh( const float _Width, const float _Height ) :
        Mesh2D( 0, 0 ),
        m_Width( _Width ),
        m_Height( _Height )
    {
        SetBufferType( BufferType::Static );
        SetAttributePointerTags( AttributePointer::Default2D );

        SetMaterial( *Aero.GetResourcesManager().GetDefault2DMaterial() );

        GenerateQuadMesh();

        SetName( std::string( "StaticQuad_" ) + std::to_string( GetObjectID() ) );
    }

    void QuadMesh::SetSize( const float _Width, const float _Height )
    {
        m_Width = _Width;
        m_Height = _Height;

        UpdateVerticesPositions( m_Vertices );
    }

    Vector2 QuadMesh::GetSize() const
    {
        return Vector2( m_Width, m_Height );
    }

    void QuadMesh::SetWidth( float _Width )
    {
        m_Width = _Width;

        UpdateVerticesPositions( m_Vertices );
    }

    float QuadMesh::GetWidth() const
    {
        return m_Width;
    }

    void QuadMesh::SetHeight( float _Height )
    {
        m_Height = _Height;

        UpdateVerticesPositions( m_Vertices );
    }

    float QuadMesh::GetHeight() const
    {
        return m_Height;
    }


    void QuadMesh::ToEditor()
    {
        priv::ui::WorldObjectToEditor( *this );
        priv::ui::TransformToEditor( *this );
        priv::ui::QuadMeshToEditor( *this );
    }



    void QuadMesh::GenerateQuadMesh()
    {
        Vertex2DArray Vertices( 4 );
        IndexArray Indices = { 0, 3, 1, 1, 3, 2 };

        UpdateVerticesPositions( Vertices );

        Vertices[0].UV = Vector2( 0.0f, 0.0f );
        Vertices[1].UV = Vector2( 1.0f, 0.0f );
        Vertices[2].UV = Vector2( 1.0f, 1.0f );
        Vertices[3].UV = Vector2( 0.0f, 1.0f );

        Setup( std::move( Vertices ), std::move( Indices ) );
    }

    void QuadMesh::UpdateVerticesPositions( Vertex2DArray& _Vertices )
    {
        const float HalfWidth = m_Width * 0.5f;
        const float HalfHeight = m_Height * 0.5f;

        _Vertices[0].Position = Vector2( -HalfWidth, -HalfHeight );
        _Vertices[1].Position = Vector2( HalfWidth, -HalfHeight );
        _Vertices[2].Position = Vector2( HalfWidth, HalfHeight );
        _Vertices[3].Position = Vector2( -HalfWidth, HalfHeight );
    }

} // ae

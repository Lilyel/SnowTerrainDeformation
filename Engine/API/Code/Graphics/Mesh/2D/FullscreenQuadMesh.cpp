#include "FullscreenQuadMesh.h"

#include "../../Material/FramebufferMaterial.h"
#include "../../../Aero/Aero.h"

namespace ae
{

	FullscreenQuadMesh::FullscreenQuadMesh( Bool _NewMaterialInstance ) :
		Drawable( BufferType::Static, AttributePointer::Default2D ),
		m_QuadVertices( 4 ),
		m_QuadIndices( { 0, 1, 2, 0, 2, 3 } )
	{
        m_QuadVertices[0].Position = Vector2( -1.0f, 1.0f );
        m_QuadVertices[1].Position = Vector2( -1.0f, -1.0f );
        m_QuadVertices[2].Position = Vector2( 1.0f, -1.0f );
        m_QuadVertices[3].Position = Vector2( 1.0f, 1.0f );

        m_QuadVertices[0].UV = Vector2( 0.0f, 1.0f );
        m_QuadVertices[1].UV = Vector2( 0.0f, 0.0f );
        m_QuadVertices[2].UV = Vector2( 1.0f, 0.0f );
        m_QuadVertices[3].UV = Vector2( 1.0f, 1.0f );


        UpdateBuffers( m_QuadVertices, m_QuadIndices );

		FramebufferMaterial* Mat = Aero.GetResourcesManager().GetDefaultFramebufferMaterial();

		// Create a copy of the material in case the user wants individual material for sprites.
		if( _NewMaterialInstance )
		{
			Mat = new FramebufferMaterial( *Mat );
			Mat->SetIsInstance( True );
		}

		SetMaterial( *Mat );

        SetName( std::string( "FullscreenQuadMesh_" ) + std::to_string( GetObjectID() ) );
	}

}

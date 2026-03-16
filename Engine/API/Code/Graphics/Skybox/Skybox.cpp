#include "Skybox.h"

#include "../Material/SkyboxMaterial.h"

#include "../../Editor/TypesToEditor/WorldObjectToEditor.h"
#include "../../Editor/TypesToEditor/SkyboxToEditor.h"
#include "../../Editor/TypesToEditor/MaterialToEditor.h"
#include "../Renderer/Renderer.h"

#include "../../Aero/Aero.h"

namespace ae
{
	Skybox::Skybox( Bool _NewMaterialInstance ) :
		Drawable( BufferType::Static, AttributePointer::Position ),
		m_CubeMap( nullptr ),
		m_Vertices( 24 ),
		m_Indices( 12 * 3 ),
		m_CubeMapParameter( nullptr ),
		m_SavedRendererDepthMode( DepthMode::Less )
	{
		SetupMaterial( _NewMaterialInstance );
		SetupCubeMesh();

		SetName( std::string( "Skybox_" ) + std::to_string( GetObjectID() ) );
	}

	Skybox::Skybox( const CubeMap& _CubeMap, Bool _NewMaterialInstance ) :
		Drawable( BufferType::Static, AttributePointer::Position ),
		m_CubeMap( nullptr ),
		m_Vertices( 24 ),
		m_Indices( 12 * 3 ),
		m_CubeMapParameter( nullptr )
	{
		SetupMaterial( _NewMaterialInstance );
		SetupCubeMesh();
		SetCubeMap( _CubeMap );

		SetName( std::string( "Skybox_" ) + std::to_string( GetObjectID() ) );
	}

	void Skybox::SetCubeMap( const CubeMap& _CubeMap )
	{
		m_CubeMap = &_CubeMap;
		UpdateMaterialCubeMap();
	}

	void Skybox::SetMaterial( Material& _Material )
	{
		Drawable::SetMaterial( _Material );
		m_CubeMapParameter = m_MaterialRef->GetParameter<ShaderParameterCubeMap>( Material::DefaultParameters::Skybox_CubeMap );
	}

	const CubeMap* Skybox::GetCubeMap() const
	{
		return m_CubeMap;
	}

	void Skybox::ToEditor()
	{
		priv::ui::WorldObjectToEditor( *this );
		priv::ui::SkyboxToEditor( *this );
		priv::ui::MaterialToEditor( GetMaterial() );
	}

	void Skybox::OnDrawBegin( Renderer& _Renderer ) const
	{
		m_SavedRendererDepthMode = _Renderer.GetDepthMode();
		_Renderer.SetDepthMode( DepthMode::LessEqual );
	}

	void Skybox::OnDrawEnd( Renderer& _Renderer ) const
	{
		_Renderer.SetDepthMode( m_SavedRendererDepthMode );
	}

	void Skybox::SetupCubeMesh()
	{
		constexpr float HalfSize = 0.5f;

		Uint32 triangleIndices[3] = { 0, 0, 0 };

		// Points
		// Front
		m_Vertices[0].Position.Set( -HalfSize, -HalfSize, HalfSize );
		m_Vertices[1].Position.Set( HalfSize, -HalfSize, HalfSize );
		m_Vertices[2].Position.Set( HalfSize, HalfSize, HalfSize );
		m_Vertices[3].Position.Set( -HalfSize, HalfSize, HalfSize );

		// Back
		m_Vertices[4].Position.Set( -HalfSize, -HalfSize, -HalfSize );
		m_Vertices[5].Position.Set( HalfSize, -HalfSize, -HalfSize );
		m_Vertices[6].Position.Set( HalfSize, HalfSize, -HalfSize );
		m_Vertices[7].Position.Set( -HalfSize, HalfSize, -HalfSize );

		// Bottom
		m_Vertices[8].Position.Set( -HalfSize, HalfSize, -HalfSize );
		m_Vertices[9].Position.Set( HalfSize, HalfSize, -HalfSize );
		m_Vertices[10].Position.Set( HalfSize, HalfSize, HalfSize );
		m_Vertices[11].Position.Set( -HalfSize, HalfSize, HalfSize );

		// Top
		m_Vertices[12].Position.Set( -HalfSize, -HalfSize, -HalfSize );
		m_Vertices[13].Position.Set( HalfSize, -HalfSize, -HalfSize );
		m_Vertices[14].Position.Set( HalfSize, -HalfSize, HalfSize );
		m_Vertices[15].Position.Set( -HalfSize, -HalfSize, HalfSize );

		// Right
		m_Vertices[16].Position.Set( HalfSize, -HalfSize, -HalfSize );
		m_Vertices[17].Position.Set( HalfSize, HalfSize, -HalfSize );
		m_Vertices[18].Position.Set( HalfSize, HalfSize, HalfSize );
		m_Vertices[19].Position.Set( HalfSize, -HalfSize, HalfSize );

		// Left
		m_Vertices[20].Position.Set( -HalfSize, -HalfSize, -HalfSize );
		m_Vertices[21].Position.Set( -HalfSize, HalfSize, -HalfSize );
		m_Vertices[22].Position.Set( -HalfSize, HalfSize, HalfSize );
		m_Vertices[23].Position.Set( -HalfSize, -HalfSize, HalfSize );

		// Front
		triangleIndices[0] = 0;
		triangleIndices[1] = 3;
		triangleIndices[2] = 1;
		SetTriangleIndices( 0, triangleIndices );

		triangleIndices[0] = 1;
		triangleIndices[1] = 3;
		triangleIndices[2] = 2;
		SetTriangleIndices( 1, triangleIndices );

		// Back
		triangleIndices[0] = 4;
		triangleIndices[1] = 5;
		triangleIndices[2] = 7;
		SetTriangleIndices( 2, triangleIndices );

		triangleIndices[0] = 5;
		triangleIndices[1] = 6;
		triangleIndices[2] = 7;
		SetTriangleIndices( 3, triangleIndices );

		// Bottom
		triangleIndices[0] = 8;
		triangleIndices[1] = 9;
		triangleIndices[2] = 11;
		SetTriangleIndices( 4, triangleIndices );

		triangleIndices[0] = 9;
		triangleIndices[1] = 10;
		triangleIndices[2] = 11;
		SetTriangleIndices( 5, triangleIndices );

		// Top
		triangleIndices[0] = 12;
		triangleIndices[1] = 15;
		triangleIndices[2] = 13;
		SetTriangleIndices( 6, triangleIndices );

		triangleIndices[0] = 13;
		triangleIndices[1] = 15;
		triangleIndices[2] = 14;
		SetTriangleIndices( 7, triangleIndices );

		// Right
		triangleIndices[0] = 16;
		triangleIndices[1] = 19;
		triangleIndices[2] = 17;
		SetTriangleIndices( 8, triangleIndices );

		triangleIndices[0] = 17;
		triangleIndices[1] = 19;
		triangleIndices[2] = 18;
		SetTriangleIndices( 9, triangleIndices );

		// Left
		triangleIndices[0] = 20;
		triangleIndices[1] = 21;
		triangleIndices[2] = 23;
		SetTriangleIndices( 10, triangleIndices );

		triangleIndices[0] = 21;
		triangleIndices[1] = 22;
		triangleIndices[2] = 23;
		SetTriangleIndices( 11, triangleIndices );

		UpdateBuffers( m_Vertices, m_Indices );
	}

	void Skybox::SetupMaterial( Bool _NewMaterialInstance )
	{
		SkyboxMaterial* Mat = Aero.GetResourcesManager().GetDefaultSkyboxMaterial();

		if( _NewMaterialInstance )
		{
			Mat = new SkyboxMaterial( *Mat );
			Mat->SetIsInstance( True );
			Mat->GetTexture().SetValue( nullptr );
		}

		SetMaterial( *Mat );
		m_CubeMapParameter = m_MaterialRef->GetParameter<ShaderParameterCubeMap>( Material::DefaultParameters::Skybox_CubeMap );
	}

	void Skybox::UpdateMaterialCubeMap()
	{
		if( m_CubeMapParameter != nullptr )
			m_CubeMapParameter->SetValue( m_CubeMap );
	}


	void Skybox::SetTriangleIndices( const Uint32 _TriangleIndex, const Uint32 _Values[3] )
	{
		if( m_Indices.size() < 3 || _TriangleIndex >= ( m_Indices.size() - 3 ) )
		{
			throw std::out_of_range( "Index out of range." );
			return;
		}

		const size_t IndiceStart = static_cast<size_t>( _TriangleIndex )* static_cast<size_t>( 3 );

		m_Indices[IndiceStart] = _Values[0];
		m_Indices[IndiceStart + 1] = _Values[1];
		m_Indices[IndiceStart + 2] = _Values[2];
	}
}

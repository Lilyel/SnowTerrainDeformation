#include "Mesh3D.h"

#include "../../../Debugging/Debugging.h"
#include "../../Renderer/Renderer.h"
#include "../../../Aero/Aero.h"
#include "../../Material/BlinnPhongMaterial.h"
#include "../../Material/CookTorranceMaterial.h"
#include "../../Material/ToonMaterial.h"

#include "../../../Editor/TypesToEditor/MaterialToEditor.h"

#pragma warning( push )
#pragma warning( disable : 26812 )


#include "../../AssimpHelper/AssimpHelper.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma warning( pop )

#include <string>

namespace ae
{
	Mesh3D::Mesh3D( const Uint32 _VerticesCount, const Uint32 _IndicesCount ) :
		m_Vertices( _VerticesCount ),
		m_Indices( _IndicesCount )
	{
		SetBufferType( BufferType::Static );
		SetAttributePointerTags( AttributePointer::Default3D );

		SetMaterial( *Aero.GetResourcesManager().GetDefault3DMaterial() );

		ApplyChanges();

		SetName( std::string( "Mesh3D_" ) + std::to_string( GetObjectID() ) );
	}
	Mesh3D::Mesh3D( const Vertex3DArray& _Vertices, const IndexArray& _Indices ) :
		m_Vertices( _Vertices ),
		m_Indices( _Indices )
	{
		SetBufferType( BufferType::Static );
		SetAttributePointerTags( AttributePointer::Default3D );

		SetMaterial( *Aero.GetResourcesManager().GetDefault3DMaterial() );

		ApplyChanges();

		SetName( std::string( "Mesh3D_" ) + std::to_string( GetObjectID() ) );
	}

	Mesh3D::Mesh3D( const std::string& _FileName, Bool _UseTextureBool )
	{
		SetBufferType( BufferType::Static );
		SetAttributePointerTags( AttributePointer::Default3D );

		LoadFromFile( _FileName, _UseTextureBool );

		SetName( std::string( "Mesh3D_" ) + std::to_string( GetObjectID() ) );
	}

	void Mesh3D::Setup( const Uint32 _VerticesCount, const Uint32 _IndicesCount )
	{
		m_Vertices.clear();
		m_Vertices.resize( _VerticesCount );

		m_Indices.clear();
		m_Indices.resize( _IndicesCount );

		ApplyChanges();
	}

	void Mesh3D::Setup( const Vertex3DArray& _Vertices, const IndexArray& _Indices )
	{
		m_Vertices = _Vertices;
		m_Indices = _Indices;

		ApplyChanges();
	}

	void Mesh3D::Setup( Vertex3DArray&& _Vertices, IndexArray&& _Indices )
	{
		m_Vertices = std::move( _Vertices );
		m_Indices = std::move( _Indices );

		ApplyChanges();
	}

	void Mesh3D::LoadFromFile( const std::string& _FileName, Bool _UseTextureBool )
	{
		Assimp::Importer Importer;
		const aiScene* Scene = Importer.ReadFile( _FileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_GenUVCoords );

		if( Scene == nullptr || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || Scene->mRootNode == nullptr )
		{
			AE_LogError( std::string( "Failed to load " ) + _FileName + ". " + Importer.GetErrorString() );
			return;
		}

		if( Scene->mNumMeshes == 0 )
			return;

		// For the moment, we support only one mesh per file.

		aiMesh* FirstMesh = Scene->mMeshes[0];

		if( FirstMesh == nullptr )
			return;

		m_Vertices.clear();
		m_Vertices.resize( FirstMesh->mNumVertices );

		m_Indices.clear();
		m_Indices.resize( static_cast<size_t>( FirstMesh->mNumFaces )* static_cast<size_t>( 3 ) );

		for( unsigned int v = 0; v < FirstMesh->mNumVertices; v++ )
		{
			if( FirstMesh->mVertices != nullptr )
			{
				m_Vertices[v].Position.X = static_cast<float>( FirstMesh->mVertices[v].x );
				m_Vertices[v].Position.Y = static_cast<float>( FirstMesh->mVertices[v].y );
				m_Vertices[v].Position.Z = static_cast<float>( FirstMesh->mVertices[v].z );
			}

			if( FirstMesh->mNormals != nullptr )
			{
				m_Vertices[v].Normal.X = static_cast<float>( FirstMesh->mNormals[v].x );
				m_Vertices[v].Normal.Y = static_cast<float>( FirstMesh->mNormals[v].y );
				m_Vertices[v].Normal.Z = static_cast<float>( FirstMesh->mNormals[v].z );
			}

			// Take only the first vertex color.
			if( FirstMesh->mColors != nullptr && FirstMesh->mColors[0] != nullptr )
			{
				m_Vertices[v].Color.R( static_cast<float>( FirstMesh->mColors[0][v].r ) );
				m_Vertices[v].Color.G( static_cast<float>( FirstMesh->mColors[0][v].g ) );
				m_Vertices[v].Color.B( static_cast<float>( FirstMesh->mColors[0][v].b ) );
				m_Vertices[v].Color.A( static_cast<float>( FirstMesh->mColors[0][v].a ) );
			}

			// Take only the first UV dim.
			if( FirstMesh->mTextureCoords != nullptr && FirstMesh->mTextureCoords[0] != nullptr )
			{
				m_Vertices[v].UV.X = static_cast<float>( FirstMesh->mTextureCoords[0][v].x );
				m_Vertices[v].UV.Y = static_cast<float>( FirstMesh->mTextureCoords[0][v].y );
			}
		}

		size_t IndiceCursor = 0;
		for( unsigned int f = 0; f < FirstMesh->mNumFaces; f++ )
		{
			const aiFace& Face = FirstMesh->mFaces[f];

			for( unsigned int i = 0; i < Face.mNumIndices; i++ )
			{
				m_Indices[IndiceCursor] = Face.mIndices[i];
				IndiceCursor++;
			}
		}

		if( Scene->mMaterials != nullptr && FirstMesh->mMaterialIndex < Scene->mNumMaterials )
		{
			const std::string Directory = _FileName.substr( 0, _FileName.find_last_of( '/' ) );
			const ::aiMaterial* AssimpMaterial = Scene->mMaterials[FirstMesh->mMaterialIndex];

			if( AssimpMaterial != nullptr )
			{

				SetMaterial( *Aero.GetResourcesManager().GetDefault3DMaterial() );


				int ShadingModel = aiShadingMode::aiShadingMode_Blinn;
				AssimpMaterial->Get( AI_MATKEY_SHADING_MODEL, ShadingModel );

				switch( ShadingModel )
				{
				case aiShadingMode::aiShadingMode_Blinn:
				case aiShadingMode::aiShadingMode_Phong:
				case aiShadingMode::aiShadingMode_Flat:
				case aiShadingMode::aiShadingMode_Gouraud:
				case aiShadingMode::aiShadingMode_NoShading:
				{
					BlinnPhongMaterial* Mat = new BlinnPhongMaterial;
					SetMaterial( *Mat );
					priv::AssimpLoadBlinnPhongMaterial( *Mat, AssimpMaterial, Directory );
				}
				break;

				case aiShadingMode::aiShadingMode_Toon:
				{
					ToonMaterial* Mat = new ToonMaterial;
					SetMaterial( *Mat );
					priv::AssimpLoadToonMaterial( *Mat, AssimpMaterial, Directory );
				}
				break;

				case aiShadingMode::aiShadingMode_CookTorrance:
				case aiShadingMode::aiShadingMode_Minnaert:
				case aiShadingMode::aiShadingMode_OrenNayar:
				{
					CookTorranceMaterial* Mat = new CookTorranceMaterial;
					SetMaterial( *Mat );
					priv::AssimpLoadCookTorranceMaterial( *Mat, AssimpMaterial, Directory );
				}
				break;

				default:
				{
					Material* Mat = new Material;
					SetMaterial( *Mat );
					priv::AssimpLoadMaterial( *Mat, AssimpMaterial, Directory, _UseTextureBool );
				}
				break;
				}

				GetMaterial().SetIsInstance( True );
				GetMaterial().SaveUniformsLocation();
			}
		}

		ApplyChanges();
	}

	const Vertex3D& Mesh3D::operator[]( const Uint32 _Index ) const
	{
		return m_Vertices[_Index];
	}

	Vertex3D& Mesh3D::operator[]( const Uint32 _Index )
	{
		return m_Vertices[_Index];
	}

	void Mesh3D::SetVertex( const Uint32 _Index, const Vertex3D& _Vertex )
	{
		m_Vertices[_Index] = _Vertex;
	}

	const Vertex3D& Mesh3D::GetVertex( const Uint32 _Index ) const
	{
		return m_Vertices[_Index];
	}

	void Mesh3D::SetIndice( const Uint32 _Index, const Uint32 _Value )
	{
		m_Indices[_Index] = _Value;
	}

	void Mesh3D::SetTriangleIndices( const Uint32 _TriangleIndex, const Uint32 _Values[3] )
	{
		if( GetPrimitiveType() != PrimitiveType::Triangles )
			throw std::exception( "Incompatible mesh primitive type with SetTriangleIndices function. Must be set to PrimitiveType::Triangles." );

		if( m_Indices.size() < 3 || _TriangleIndex > ( m_Indices.size() - 3 ) )
			throw std::out_of_range( "Index out of range." );

		const size_t IndiceStart = Cast( size_t, _TriangleIndex )* Cast( size_t, 3 );

		m_Indices[IndiceStart] = _Values[0];
		m_Indices[IndiceStart + 1] = _Values[1];
		m_Indices[IndiceStart + 2] = _Values[2];
	}

	void Mesh3D::SetQuadIndices( const Uint32 _QuadIndex, const Uint32 _Values[4] )
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

	Uint32 Mesh3D::GetIndice( const Uint32 _Index ) const
	{
		return m_Indices[_Index];
	}



	void Mesh3D::ApplyChanges()
	{
		UpdateBuffers( m_Vertices, m_Indices );
	}

	void Mesh3D::ToEditor()
	{
		WorldObject::ToEditor();
		Transform::ToEditor();
		priv::ui::MaterialToEditor( GetMaterial() );
	}

} // ae
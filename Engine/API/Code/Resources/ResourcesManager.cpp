#include "ResourcesManager.h"

#include "../Graphics/Texture/Texture.h"
#include "Resource/Resource.h"
#include "../Graphics/Shader/Shader.h"
#include "../Graphics/Material/BlinnPhongMaterial.h"
#include "../Graphics/Material/SpriteMaterial.h"
#include "../Graphics/Material/SkyboxMaterial.h"
#include "../Graphics/Material/FramebufferMaterial.h"
#include "../Graphics/Material/CurveMaterial.h"
#include "../Aero/Aero.h"

namespace ae
{
	ResourcesManager::ResourcesManager() :
		m_Default3DShader( nullptr ),
		m_DefaultCookTorranceShader( nullptr ),
		m_Default2DShader( nullptr ),
		m_DefaultToonShader( nullptr ),
		m_DefaultUniShadowMapShader( nullptr ),
		m_DefaultOmniShadowMapShader( nullptr ),
		m_DefaultCurveShader( nullptr ),
		m_FramebufferShader( nullptr ),
		m_DefaultSkyboxShader( nullptr ),
		m_Default3DMaterial( nullptr ),
		m_Default2DMaterial( nullptr ),
		m_DefaultFramebufferMaterial( nullptr ),
		m_DefaultSkyboxMaterial( nullptr )
	{
	}

	ResourcesManager::~ResourcesManager()
	{
		UnloadAll();
		UnloadEngineMaterials();
		UnloadEngineShaders();
	}
	const std::unordered_map<ResourcesManager::ResourceID, Resource*>& ResourcesManager::GetResources() const
	{
		return m_Resources;
	}

	std::unordered_map<ResourcesManager::ResourceID, Resource*>& ResourcesManager::GetResources()
	{
		return m_Resources;
	}

	const Resource* ResourcesManager::GetResource( ResourceID _ID ) const
	{
		if( _ID == InvalidResourceID )
		{
			AE_LogError( "Invalid ID. Function will return nullptr." );
			return nullptr;
		}

		std::unordered_map<ResourceID, Resource*>::const_iterator It = m_Resources.find( _ID );

		if( It != m_Resources.cend() )
			return It->second;

		else
		{
			AE_LogError( std::string( "Resource with the ID (" ) + std::to_string( _ID ) + ") not found." );
			return nullptr;
		}
	}

	Resource* ResourcesManager::GetResource( ResourceID _ID )
	{
		if( _ID == InvalidResourceID )
		{
			AE_LogError( "Invalid ID. Function will return nullptr." );
			return nullptr;
		}

		std::unordered_map<ResourceID, Resource*>::const_iterator It = m_Resources.find( _ID );

		if( It != m_Resources.cend() )
			return It->second;

		else
		{
			AE_LogError( std::string( "Resource with the ID (" ) + std::to_string( _ID ) + ") not found." );
			return nullptr;
		}
	}

	ResourcesManager::ResourceID ResourcesManager::GenerateResourceID()
	{
		return m_IDPool.GenerateID();
	}

	void ResourcesManager::FreeResourceID( ResourceID _ID )
	{
		m_IDPool.FreeID( _ID );
	}

	ResourcesManager::ResourceID ResourcesManager::AddResource( Resource* _ResourceToAdd )
	{
		if( _ResourceToAdd == nullptr )
		{
			AE_LogError( "Invalid resource to add to the manager." );
			return InvalidResourceID;
		}

		// Generate a new ID.
		const ResourceID NewID = GenerateResourceID();

		if( NewID == InvalidResourceID )
		{
			AE_LogError( "Invalid generated ID. resource will not be added to the manager." );
			return InvalidResourceID;
		}

		if( m_Resources.find( NewID ) != m_Resources.cend() )
		{
			AE_LogError( std::string( "Resource with the generated ID (" ) + std::to_string( NewID ) + ") already exists." );
			return InvalidResourceID;
		}

		// Add the resource to the manager with this ID.
		m_Resources.insert( { NewID , _ResourceToAdd } );

		return NewID;
	}

	void ResourcesManager::RemoveResource( Resource* _ResourceToRemove )
	{
		if( _ResourceToRemove == nullptr )
		{
			AE_LogError( "Invalid resource to remove from the manager." );
			return;
		}

		const ResourceID& ToDeleteID = _ResourceToRemove->GetResourceID();

		if( m_Resources.find( ToDeleteID ) == m_Resources.cend() )
		{
			AE_LogError( std::string( "Resource with the ID (" ) + std::to_string( ToDeleteID ) + ") doesn't exist. Impossible to remove it from the manager." );
			return;
		}

		// Remove the resource from the manager.
		m_Resources.erase( ToDeleteID );

		// Make its ID available again.
		FreeResourceID( ToDeleteID );
	}



	void ResourcesManager::UnloadAll()
	{
		std::vector<Resource*> ToFree;

		// Retrieve in the manager all the resources to free.
		for( std::pair<const ResourceID, Resource*> ResourcePair : m_Resources )
		{
			Resource* ResourcePtr = ResourcePair.second;
			if( ResourcePtr != nullptr && ResourcePtr->IsManagedByManager() )
				ToFree.push_back( ResourcePtr );
		}

		// Free the memory of these resources.
		// We do it separatly because the destructor of resources modify the resources map.
		for( Resource* ResourcePtr : ToFree )
			delete ResourcePtr;
	}

	Shader* ResourcesManager::GetDefault3DShader()
	{
		if( m_Default3DShader == nullptr )
		{
			const std::string& PathToEngineData = Aero.GetPathToEngineData() + "/Shader/";
			m_Default3DShader = new Shader( PathToEngineData + "Default3DVertex.glsl", PathToEngineData + "Default3DFragment.glsl" );
			m_Default3DShader->SetName( "Default 3D Shader" );
		}

		return m_Default3DShader;
	}

	Shader* ResourcesManager::GetDefaultCookTorranceShader()
	{
		if( m_DefaultCookTorranceShader == nullptr )
		{
			const std::string& PathToEngineData = Aero.GetPathToEngineData() + "/Shader/";
			m_DefaultCookTorranceShader = new Shader( PathToEngineData + "Default3DVertex.glsl", PathToEngineData + "PBRFragment.glsl" );
			m_DefaultCookTorranceShader->SetName( "Default Cook-Torrance Shader" );
		}

		return m_DefaultCookTorranceShader;
	}

	Shader* ResourcesManager::GetDefault2DShader()
	{
		if( m_Default2DShader == nullptr )
		{
			const std::string& PathToEngineData = Aero.GetPathToEngineData() + "/Shader/";
			m_Default2DShader = new Shader( PathToEngineData + "Default2DVertex.glsl", PathToEngineData + "Default2DFragment.glsl" );
			m_Default2DShader->SetName( "Default 2D Shader" );
		}

		return m_Default2DShader;
	}

	Shader* ResourcesManager::GetDefaultToonShader()
	{
		if( m_DefaultToonShader == nullptr )
		{
			const std::string& PathToEngineData = Aero.GetPathToEngineData() + "/Shader/";
			m_DefaultToonShader = new Shader( PathToEngineData + "Default3DVertex.glsl", PathToEngineData + "ToonFragment.glsl" );
			m_DefaultToonShader->SetName( "Default Toon Shader" );
		}

		return m_DefaultToonShader;
	}

	Shader* ResourcesManager::GetDefaultUniShadowMapShader()
	{
		if( m_DefaultUniShadowMapShader == nullptr )
		{
			const std::string& PathToEngineData = Aero.GetPathToEngineData() + "/Shader/";
			m_DefaultUniShadowMapShader = new Shader( PathToEngineData + "ShadowMapVertex.glsl", PathToEngineData + "ShadowMapFragment.glsl" );
			m_DefaultUniShadowMapShader->SetName( "Default Unidirectional Shadow Map Shader" );
		}

		return m_DefaultUniShadowMapShader;
	}

	Shader* ResourcesManager::GetDefaultOmniShadowMapShader()
	{
		if( m_DefaultOmniShadowMapShader == nullptr )
		{
			const std::string& PathToEngineData = Aero.GetPathToEngineData() + "/Shader/";
			m_DefaultOmniShadowMapShader = new Shader( PathToEngineData + "ShadowMapOmniVertex.glsl", 
													   PathToEngineData + "ShadowMapOmniFragment.glsl", 
													   PathToEngineData + "ShadowMapOmniGeometry.glsl" );
			m_DefaultOmniShadowMapShader->SetName( "Default Omnidirectional Shadow Map Shader" );
		}

		return m_DefaultOmniShadowMapShader;
	}

	Shader* ResourcesManager::GetDefaultCurveShader()
	{
		if( m_DefaultCurveShader == nullptr )
		{
			const std::string& PathToEngineData = Aero.GetPathToEngineData() + "/Shader/";
			m_DefaultCurveShader = new Shader( PathToEngineData + "CurveVertex.glsl",
											   PathToEngineData + "CurveFragment.glsl",
											   PathToEngineData + "CurveGeometry.glsl" );
			m_DefaultCurveShader->SetName( "Default Curve Shader" );
		}

		return m_DefaultCurveShader;
	}


	Shader* ResourcesManager::GetDefaultFramebufferShader()
	{
		if( m_FramebufferShader == nullptr )
		{
			const std::string& PathToEngineData = Aero.GetPathToEngineData() + "/Shader/";
			m_FramebufferShader = new Shader( PathToEngineData + "FramebufferVertex.glsl", PathToEngineData + "FramebufferFragment.glsl" );
			m_FramebufferShader->SetName( "Default Framebuffer Shader" );
		}

		return m_FramebufferShader;
	}

	Shader* ResourcesManager::GetDefaultSkyboxShader()
	{
		if( m_DefaultSkyboxShader == nullptr )
		{
			const std::string& PathToEngineData = Aero.GetPathToEngineData() + "/Shader/";
			m_DefaultSkyboxShader = new Shader( PathToEngineData + "SkyboxVertex.glsl", PathToEngineData + "SkyboxFragment.glsl" );
			m_DefaultSkyboxShader->SetName( "Default Skybox Shader" );
		}

		return m_DefaultSkyboxShader;
	}

	BlinnPhongMaterial* ResourcesManager::GetDefault3DMaterial()
	{
		if( m_Default3DMaterial == nullptr )
		{
			m_Default3DMaterial = new BlinnPhongMaterial;
			m_Default3DMaterial->SetName( "Default Blinn-Phong Material" );
		}

		return m_Default3DMaterial;
	}

	SpriteMaterial* ResourcesManager::GetDefault2DMaterial()
	{
		if( m_Default2DMaterial == nullptr )
		{
			m_Default2DMaterial = new SpriteMaterial;
			m_Default2DMaterial->SetName( "Default Sprite Material" );
		}

		return m_Default2DMaterial;
	}

	CurveMaterial* ResourcesManager::GetDefaultCurveMaterial()
	{
		if( m_DefaultCurveMaterial == nullptr )
		{
			m_DefaultCurveMaterial = new CurveMaterial;
			m_DefaultCurveMaterial->SetName( "Default Curve Material" );
		}

		return m_DefaultCurveMaterial;
	}

	FramebufferMaterial* ResourcesManager::GetDefaultFramebufferMaterial()
	{
		if( m_DefaultFramebufferMaterial == nullptr )
		{
			m_DefaultFramebufferMaterial = new FramebufferMaterial;
			m_DefaultFramebufferMaterial->SetName( "Default Framebuffer Material" );
		}

		return m_DefaultFramebufferMaterial;
	}

	SkyboxMaterial* ResourcesManager::GetDefaultSkyboxMaterial()
	{
		if( m_DefaultSkyboxMaterial == nullptr )
		{
			m_DefaultSkyboxMaterial = new SkyboxMaterial;
			m_DefaultSkyboxMaterial->SetName( "Default Skybox Material" );
		}

		return m_DefaultSkyboxMaterial;
	}


	void ResourcesManager::UnloadEngineShaders()
	{
		if( m_Default3DShader != nullptr )
		{
			delete m_Default3DShader;
			m_Default3DShader = nullptr;
		}

		if( m_DefaultCookTorranceShader != nullptr )
		{
			delete m_DefaultCookTorranceShader;
			m_DefaultCookTorranceShader = nullptr;
		}

		if( m_Default2DShader != nullptr )
		{
			delete m_Default2DShader;
			m_Default2DShader = nullptr;
		}

		if( m_DefaultToonShader != nullptr )
		{
			delete m_DefaultToonShader;
			m_DefaultToonShader = nullptr;
		}

		if( m_DefaultUniShadowMapShader != nullptr )
		{
			delete m_DefaultUniShadowMapShader;
			m_DefaultUniShadowMapShader = nullptr;
		}

		if( m_DefaultOmniShadowMapShader != nullptr )
		{
			delete m_DefaultOmniShadowMapShader;
			m_DefaultOmniShadowMapShader = nullptr;
		}

		if( m_FramebufferShader != nullptr )
		{
			delete m_FramebufferShader;
			m_FramebufferShader = nullptr;
		}

		if( m_DefaultSkyboxShader != nullptr )
		{
			delete m_DefaultSkyboxShader;
			m_DefaultSkyboxShader = nullptr;
		}
	}

	void ResourcesManager::UnloadEngineMaterials()
	{
		if( m_Default3DMaterial != nullptr )
		{
			delete m_Default3DMaterial;
			m_Default3DMaterial = nullptr;
		}

		if( m_Default2DMaterial != nullptr )
		{
			delete m_Default2DMaterial;
			m_Default2DMaterial = nullptr;
		}

		if( m_DefaultFramebufferMaterial != nullptr )
		{
			delete m_DefaultFramebufferMaterial;
			m_DefaultFramebufferMaterial = nullptr;
		}

		if( m_DefaultSkyboxMaterial != nullptr )
		{
			delete m_DefaultSkyboxMaterial;
			m_DefaultSkyboxMaterial = nullptr;
		}
	}

} // ae


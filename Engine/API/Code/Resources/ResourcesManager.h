#pragma once

#include "../Toolbox/Toolbox.h"
#include "../Toolbox/PoolUniqueID/PoolUniqueID.h"

#include <unordered_map>


namespace ae
{
	class Resource;
	class Shader;
	class Material;
	class BlinnPhongMaterial;
	class SpriteMaterial;
	class SkyboxMaterial;
	class FramebufferMaterial;
	class CurveMaterial;

	/// \ingroup resources
	/// <summary>
	/// Store references to resources (textures, shaders, ...)
	/// </summary>
	class AERO_CORE_EXPORT ResourcesManager
	{
		friend class Resource;
		friend class Renderer;

	public:
		/// <summary>Type used to identify resource in the manager.</summary>
		using ResourceID = Uint16;

		/// <summary>Value that represent an invalid resource ID.</summary>
		static constexpr ResourceID InvalidResourceID = PoolUniqueID::InvalidID;

		/// <summary>Represents the maximum amount of resources that the world can have at the same time.</summary>
		static constexpr ResourceID MaxResourceID = PoolUniqueID::MaxID;

	public:
		/// <summary>Default constructor.</summary>
		ResourcesManager();

		/// <summary>
		/// Destructor. <para/>
		/// Remove the resources stored by the manager.
		/// The memory of resources tagged as managed by the manager will be freed.
		/// </summary>
		~ResourcesManager();

		
		/// <summary>Retrieve all the resources of the manager.</summary>
		/// <returns>Manager's resources.</returns>
		const std::unordered_map<ResourceID, Resource*>& GetResources() const;

		/// <summary>Retrieve all the resources of the manager.</summary>
		/// <returns>Manager's resources.</returns>
		std::unordered_map<ResourceID, Resource*>& GetResources();

		/// <summary>Get the resource with the <paramref name="_ID"/> in the manager.</summary>
		/// <param name="_ID">The ID of the resource to retrieve from the manager.</param>
		/// <returns>Resource of the manager with the corresponding ID.</returns>
		const Resource* GetResource( ResourceID _ID ) const;

		/// <summary>Get the resource with the <paramref name="_ID"/> in the manager.</summary>
		/// <param name="_ID">The ID of the resource to retrieve from the manager.</param>
		/// <returns>Resource of the manager with the corresponding ID.</returns>
		Resource* GetResource( ResourceID _ID );
		
		/// <summary>
		/// Free memory of all resources stored tagged as managed by the manager.
		/// </summary>
		void UnloadAll();

		/// <summary>Retrieve the default 3D shader of the engine.</summary>
		/// <returns>The default 3D shader of the engine.</returns>
		Shader* GetDefault3DShader();

		/// <summary>Retrieve the default Cook-Torrance shader of the engine.</summary>
		/// <returns>The default Cook-Torrance shader of the engine.</returns>
		Shader* GetDefaultCookTorranceShader();
		
		/// <summary>Retrieve the default 2D shader of the engine.</summary>
		/// <returns>The default 2D shader of the engine.</returns>
		Shader* GetDefault2DShader();

		/// <summary>Retrieve the default toon shader of the engine.</summary>
		/// <returns>The default toon shader of the engine.</returns>
		Shader* GetDefaultToonShader();

		/// <summary>Retrieve the default unidirectional shadow map shader of the engine.</summary>
		/// <returns>The default unidirectional shadow map shader of the engine.</returns>
		Shader* GetDefaultUniShadowMapShader();

		/// <summary>Retrieve the default omnidirectional shadow map shader of the engine.</summary>
		/// <returns>The default omnidirectional shadow map shader of the engine.</returns>
		Shader* GetDefaultOmniShadowMapShader();

		/// <summary>Retrieve the default curve shader of the engine.</summary>
		/// <returns>The default curve shader of the engine.</returns>
		Shader* GetDefaultCurveShader();

		/// <summary>Retrieve the default framebuffer (textured quad screen space) shader of the engine.</summary>
		/// <returns>The default framebuffer (textured quad screen space) shader of the engine.</returns>
		Shader* GetDefaultFramebufferShader();

		/// <summary>Retrieve the default skybox shader of the engine.</summary>
		/// <returns>The default skybox shader of the engine.</returns>
		Shader* GetDefaultSkyboxShader();

		/// <summary>Retrieve the default 3D material of the engine.</summary>
		/// <returns>The default 3D material of the engine.</returns>
		BlinnPhongMaterial* GetDefault3DMaterial();

		/// <summary>Retrieve the default 2D material of the engine.</summary>
		/// <returns>The default 2D material of the engine.</returns>
		SpriteMaterial* GetDefault2DMaterial();

		/// <summary>Retrieve the default curve material of the engine.</summary>
		/// <returns>The default curve material of the engine.</returns>
		CurveMaterial* GetDefaultCurveMaterial();

		/// <summary>Retrieve the default framebuffer material of the engine.</summary>
		/// <returns>The default skybox framebuffer of the engine.</returns>
		FramebufferMaterial* GetDefaultFramebufferMaterial();

		/// <summary>Retrieve the default skybox material of the engine.</summary>
		/// <returns>The default skybox material of the engine.</returns>
		SkyboxMaterial* GetDefaultSkyboxMaterial();

	private:
		/// <summary>Take a new resource ID from the pool.</summary>
		/// <returns>The new ID taken from the pool (can be InvalidResourceID).</returns>
		ResourceID GenerateResourceID();

		/// <summary>Make available again an ID in the pool.</summary>
		/// <param name="_ID">ID to make available in the pool.</param>
		void FreeResourceID( ResourceID _ID );

		/// <summary>
		/// Add a new resource in the manager. <para/>
		/// If the resource is invalid or if there is not available ID
		/// <paramref name="_ResourceToAdd"/> will not be added to the manager. <para/>
		/// If a resource with the same ID already exists, <paramref name="_ResourceToAdd"/>
		/// will not be added to the manager.
		/// </summary>
		/// <returns>The ID of the resource added (can be InvalidResourceID).</returns>
		ResourceID AddResource( Resource* _ResourceToAdd );

		/// <summary>
		/// Remove a resource from the world. <para/>
		/// Its ID will be available again in the pool ID.
		/// </summary>
		void RemoveResource( Resource* _ResourceToRemove );

		

		/// <summary>Unload default engine shaders.</summary>
		void UnloadEngineShaders();

		/// <summary>Unlaod default engine materials.</summary>
		void UnloadEngineMaterials();

	private:
		/// <summary>Resource ID generator.</summary>
		PoolUniqueID m_IDPool;

		/// <summary>Textures.</summary>
		std::unordered_map<ResourceID, Resource*> m_Resources;


		/// <summary>Default 3D rendering shader.</summary>
		Shader* m_Default3DShader;

		/// <summary>Default Cook-Torrance BRDF shader.</summary>
		Shader* m_DefaultCookTorranceShader;

		/// <summary>Default 2D rendering shader.</summary>
		Shader* m_Default2DShader;

		/// <summary>Default toon rendering shader.</summary>
		Shader* m_DefaultToonShader;

		/// <summary>Default unidirectional shadow map shader.</summary>
		Shader* m_DefaultUniShadowMapShader;

		/// <summary>Default unidirectional shadow map shader.</summary>
		Shader* m_DefaultOmniShadowMapShader;

		/// <summary>Default curve shader.</summary>
		Shader* m_DefaultCurveShader;

		/// <summary>
		/// Shader to use with FramebufferSprite to render.<para/>
		/// It will render the framebuffer content on the entire current render target.
		/// </summary>
		Shader* m_FramebufferShader;

		/// <summary>Default skybox shader.</summary>
		Shader* m_DefaultSkyboxShader;




		/// <summary>Default 3D material for rendering.</summary>
		BlinnPhongMaterial* m_Default3DMaterial;

		/// <summary>Default 2D material for rendering.</summary>
		SpriteMaterial* m_Default2DMaterial;

		/// <summary>Default curve material for rendering.</summary>
		CurveMaterial* m_DefaultCurveMaterial;

		/// <summary>Default framebuffer material for rendering.</summary>
		FramebufferMaterial* m_DefaultFramebufferMaterial;

		/// <summary>Default skybox material for rendering.</summary>
		SkyboxMaterial* m_DefaultSkyboxMaterial;
	};

} // ae

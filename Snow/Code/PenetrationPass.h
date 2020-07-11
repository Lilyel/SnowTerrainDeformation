#pragma once

#include <API/Code/Graphics/Framebuffer/Framebuffer.h>
#include <API/Code/Graphics/Shader/Shader.h>
#include <API/Code/Graphics/Material/Material.h>
#include <API/Code/Graphics/Texture/Texture.h>
#include <API/Code/Graphics/Mesh/2D/FullscreenQuadMesh.h>

/// <summary>Process the penetration values of the objects interacting with the snow.</summary>
class PenetrationPass
{
public:
	/// <summary>Initialize the penetration pass.</summary>
	/// <param name="_TextureSize">The size to apply to the framebuffer (and the penetration texture).</param>
	/// <param name="_HeightMap">The snow height map.</param>
	/// <param name="_DepthMap">The depth map generated with the interacting objects.</param>
	PenetrationPass( Uint32 _TextureSize, ae::Texture& _HeightMap, ae::Texture& _DepthMap );

	/// <summary>Process the penetration texture.</summary>
	void Run();

	/// <summary>Retieve the penetration texture.</summary>
	/// <returns>The penetration texture.</returns>
	ae::Texture& GetPenetrationTexture();

	/// <summary>Resize the framebuffer (thus the penetration texture).</summary>
	/// <param name="_TextureSize">The size to apply.</param>
	void Resize( Uint32 _TextureSize );

private:
	/// <summary>The framebuffer used for the penetration pass.</summary>
	ae::Framebuffer m_FBO;

	/// <summary>Penetration pass shader.</summary>
	ae::Shader m_Shader;

	/// <summary>Material for the penetration pass shader.</summary>
	ae::Material m_Material;

	/// <summary>Fullscreen quad.</summary>
	ae::FullscreenQuadMesh m_Quad;
};
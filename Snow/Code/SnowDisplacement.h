#pragma once

#include <API/Code/Graphics/Framebuffer/Framebuffer.h>
#include <API/Code/Graphics/Mesh/2D/FullscreenQuadMesh.h>
#include <API/Code/Graphics/Material/Material.h>
#include <API/Code/Graphics/Texture/Texture2D.h>
#include <API/Code/Graphics/Shader/Shader.h>
#include <API/Code/Graphics/Camera/Camera.h>

/// <summary>Snow displacement pass : Move the snow from penetrating texel onto seeds.</summary>
class SnowDisplacement
{
public:
	/// <summary>Initialize the displacement pass.</summary>
	/// <param name="_TextureSize">The size of the working height map.</param>
	/// <param name="_HeightMap">The snow height map.</param>
	/// <param name="_PenetrationTexture">The penetrationg texture (generated in penetration pass).</param>
	/// <param name="_DistanceTexture">The distance texture (from flooding pass).</param>
	SnowDisplacement( Uint32 _TextureSize, ae::Texture& _HeightMap, ae::Texture& _PenetrationTexture, ae::Texture& _DistanceTexture );

	/// <summary>Move the penetrating snow onto seeds.</summary>
	/// <param name="_HeightMap">The snow height map to update.</param>
	/// <param name="_PenetrationTexture">The penetration texture (from the the penetration pass).</param>
	/// <param name="_DistanceTexture">The distance texture (from the flooding pass).</param>
	void Run( ae::Texture& _HeightMap, ae::Texture& _PenetrationTexture, ae::Texture& _DistanceTexture );

	/// <summary>Resize the working height map.</summary>
	/// <param name="_TextureSize">The size to apply.</param>
	void Resize( Uint32 _TextureSize );

	/// <summary>Expose properties in the editor panel.</summary>
	void ToEditor();


private:
	/// <summary>Shader to move the snow from penetrating texel to seeds.</summary>
	ae::Shader m_DisplacementShader;

	/// <summary>Shader to even the snow to avoid big spikes.</summary>
	ae::Shader m_EveningShader;

	/// <summary>Shader to copy the height map to working height map and the other way around.</summary>
	ae::Shader m_CopyShader;

	/// <summary>Temporary height map used to process the dispalcement on without touching directly the height map.</summary>
	ae::Texture2D m_WorkingHeightMap;

	/// <summary>Number of evening iteration to do per frame.</summary>
	Uint32 m_EveningIterationsCount;
};
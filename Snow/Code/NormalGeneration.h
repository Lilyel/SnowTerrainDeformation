#pragma once

#include <API/Code/Graphics/Texture/Texture2D.h>
#include <API/Code/Graphics/Shader/Shader.h>
#include <API/Code/Graphics/PostProcess/GaussianBlur.h>

/// <summary>Pass generating the normal map from the height map.</summary>
class NormalGeneration
{
public:
	/// <summary>Initialize the pass.</summary>
	/// <param name="_TextureSize">The size for the normal map.</param>
	NormalGeneration( Uint32 _TextureSize );

	/// <summary>Run the normal map pass.</summary>
	/// <param name="_HeightMap">The height map to generate the normal from.</param>
	void Run( ae::Texture& _HeightMap );

	/// <summary>Retrieve the normal map.</summary>
	/// <returns>The normal map.</returns>
	ae::Texture2D& GetNormalMap();

	/// <summary>Resize the normal map.</summary>
	/// <param name="_TextureSize">The size to apply.</param>
	void Resize( Uint32 _TextureSize );

private:
	/// <summary>Normal map texture.</summary>
	ae::Texture2D m_NormalMap;

	/// <summary>Shader processing the normal map from the height map.</summary>
	ae::Shader m_Shader;

	/// <summary>Blur post-process for the normal map.</summary>
	ae::GaussianBlur m_Blur;
};

#pragma once

#include <API/Code/Graphics/Framebuffer/Framebuffer.h>
#include <API/Code/Graphics/Framebuffer/FramebufferSprite.h>
#include <API/Code/Graphics/Material/Material.h>
#include <API/Code/Graphics/Texture/Texture2D.h>
#include <API/Code/Graphics/Shader/Shader.h>

/// <summary>Process the jump flooding algorithm on the GPU.</summary>
class JumpFlooding
{
public:
	/// <summary>Initializa the jump flooding pass.</summary>
	/// <param name="_TextureSize">The pingpong framebuffer size (and the distance texture).</param>
	/// <param name="_PenetrationTexture">The penetrationg texture resulting of previous step.</param>
	JumpFlooding( Uint32 _TextureSize, ae::Texture& _PenetrationTexture );

	/// <summary>Destructor.</summary>
	~JumpFlooding();

	/// <summary>Run the jump flooding algorithm from the penetration texture given in the constructor.</summary>
	void Run();

	/// <summary>Retrieve the result of the jump flooding algorithm (distance field).</summary>
	/// <returns>The jump flooding result.</returns>
	ae::Texture& GetDistanceTexture();

	/// <summary>Resize the framebuffer (thus the distance texture).</summary>
	/// <param name="_TextureSize">The size to apply.</param>
	void Resize( Uint32 _TextureSize );

	/// <summary>Expose properties to the editor panel.</summary>
	void ToEditor();

private:
	/// <summary>Shader for the first step of the algorithm to initialize a first time a ping pong texture.</summary>
	ae::Shader m_InitShader;

	/// <summary>Material for the first step shader.</summary>
	ae::Material m_InitMaterial;


	/// <summary>Shader for the flooding algorithm.</summary>
	ae::Shader m_FloodingShader;

	/// <summary>Material for the flooding algorithm.</summary>
	ae::Material m_FloodingMaterial;

	/// <summary>Parameter for the ping pong texture to read from.</summary>
	ae::ShaderParameterTexture* m_FloodingTextureParameter;

	/// <summary>Parameter for the flooding range.</summary>
	ae::ShaderParameterInt* m_FloodingRangeParameter;

	/// <summary>Parameter for the time (used to feed random function).</summary>
	ae::ShaderParameterFloat* m_FloodingTimeParameter;

	/// <summary>Ping-pong framebuffer.</summary>
	ae::Framebuffer* m_PingPongFBO[2];

	/// <summary>Fullscreen quad.</summary>
	ae::FramebufferSprite m_FullscreenSprite;

	/// <summary>Maximum possible range.</summary>
	Uint32 m_MaxFloodingRange;

	/// <summary>Size of the texture.</summary>
	Uint32 m_TextureSize;

	/// <summary>Index of the last ping pong texture written.</summary>
	Uint32 m_CurrentPingPongIndex;
};
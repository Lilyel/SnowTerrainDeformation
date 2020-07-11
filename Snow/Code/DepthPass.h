#pragma once

#include <API/Code/Graphics/Camera/CameraOrthographic.h>
#include <API/Code/Graphics/Framebuffer/Framebuffer.h>
#include <API/Code/Graphics/Material/Material.h>
#include <API/Code/Graphics/Shader/Shader.h>
#include <API/Code/Graphics/Texture/Texture.h>

class Scene;
class SnowPlane;

/// <summary>
/// Compute the depth texture of the objects interacting 
/// with the snow using a camera bellow the ground.
/// </summary>
class DepthPass
{
public:
	/// <summary>Initialize the depth pass (framebuffer, camera, material).</summary>
	/// <param name="_TextureSize">The size to apply to the framebuffer (will be the size of the depth map).</param>
	/// <param name="_Ground">Ground object to place the camera.</param>
	DepthPass( Uint32 _TextureSize, const SnowPlane& _Ground );

	/// <summary>Run the depth pass on the interacting objects of the scene.</summary>
	/// <param name="_Scene">The scene holding the objects to render.</param>
	void Run( Scene& _Scene );

	/// <summary>Depth texture generated during the Run() function.</summary>
	/// <returns>The depth texture.</returns>
	ae::Texture& GetDepthTexture();

	/// <summary>Retrieve the near distance of the camera bellow the ground.</summary>
	/// <returns>The near distance of the camera bellow the ground.</returns>
	float GetCameraNear() const;

	/// <summary>Retrieve the far distance of the camera bellow the ground.</summary>
	/// <returns>The far distance of the camera bellow the ground.</returns>
	float GetCameraFar() const;

	/// <summary>Update the camera placement from the provided <paramref name="_Ground"/>.</summary>
	/// <param name="_Ground">The ground object used to place the camera.</param>
	void UpdateCamera( const SnowPlane& _Ground );

	/// <summary>Resize the framebuffer (thus the depth map).</summary>
	/// <param name="_TextureSize">The new size to apply.</param>
	void Resize( Uint32 _TextureSize );

private:
	/// <summary>The camera bellow the ground.</summary>
	ae::CameraOrthographic m_Camera;

	/// <summary>Framebuffer to do the depth pass.</summary>
	ae::Framebuffer m_FBO;

	/// <summary>Shader for the depth pass.</summary>
	ae::Shader m_Shader;

	/// <summary>Material for the depth pass (simpler than default objects material).</summary>
	ae::Material m_Material;
};
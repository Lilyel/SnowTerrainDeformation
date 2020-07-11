#pragma once

#include <API/Code/Graphics/Material/CookTorranceMaterial.h>
#include <API/Code/Graphics/Mesh/3D/CubeMesh.h>
#include <API/Code/Graphics/Mesh/3D/SphereMesh.h>
#include <API/Code/Graphics/Mesh/3D/Mesh3D.h>

#include <API/Code/Graphics/Texture/TextureImage.h>

#include <API/Code/Graphics/Light/DirectionalLight/DirectionalLight.h>
#include <API/Code/Graphics/Light/PointLight/PointLight.h>

#include <API/Code/Graphics/Renderer/Renderer.h>

#include <API/Code/Maths/Curve/CurveHermite.h>

class SnowPlane;

/// <summary>
/// Holds : <para/>
/// - The objects interacting with the snow<para/>
/// - The lights<para/>
/// - The animation of the boots.
/// </summary>
class Scene
{
public:
	/// <summary>Initialize the scene objects.</summary>
	Scene();

	/// <summary>Render of the target only the objects interacting with the snow.</summary>
	/// <param name="_Renderer">The rendering target.</param>
	/// <param name="_DepthMaterial">The material to use (will be the one in the DepthPass class).</param>
	/// <param name="_Camera">The camera to use (will be the one bellow the ground).</param>
	void RenderDepthPass( ae::Renderer& _Renderer, const ae::Material& _DepthMaterial,  ae::Camera& _Camera );

	/// <summary>Render all the objects on the target.</summary>
	/// <param name="_Renderer">The rendering target.</param>
	void RenderColorPass( ae::Renderer& _Renderer );

	/// <summary>Update the boots objects animations.</summary>
	void UpdateBootsAnim();

private:
	/// <summary>Common material for objects.</summary>
	ae::CookTorranceMaterial m_ObjectsMat;


	// Objets.

	ae::SphereMesh m_Ball;
	ae::Mesh3D m_Lantern;
	ae::Mesh3D m_MooMoo;
	ae::TextureImage m_MooMooTexture;
	ae::Mesh3D m_FenceBack;
	ae::Mesh3D m_FenceLeft;

	ae::Mesh3D m_LeftBoot;
	ae::Mesh3D m_RightBoot;


	// Lights

	ae::DirectionalLight m_AmbientLight;
	ae::PointLight m_LanternLight;


	// Boots animation.

	ae::CurveHermite m_BootsTrajectoryLeft;
	ae::CurveHermite m_BootsTrajectoryRight;
	float m_BootsAnimTime;
	const float m_BootsAnimTotalTime;
};
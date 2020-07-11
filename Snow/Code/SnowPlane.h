#pragma once

#include <API/Code/Graphics/Mesh/3D/PlaneMesh.h>
#include <API/Code/Graphics/Shader/Shader.h>

/// <summary>Snow surface : Plane that will be tessellated and offset according to the snow height.</summary>
class SnowPlane : public ae::PlaneMesh
{
public:
	/// <summary>Initialize the snow surface.</summary>
	/// <param name="_HeightMap">The height used to offset the vertices.</param>
	/// <param name="_NormalMap">The normal map for shading.</param>
	/// <param name="_Size">Plane size.</param>
	/// <param name="_SubdivisionWidth">Initial subdvision of the plane in the width axis.</param>
	/// <param name="_SubdivisionHeight">Initial subdivision of the plane in the height axis.</param>
	SnowPlane( ae::Texture& _HeightMap, ae::Texture& _NormalMap, float _Size = 2.0f, Uint32 _SubdivisionWidth = 32, Uint32 _SubdivisionHeight = 32 );

private:
	/// <summary>
	/// Snow shader (tessellation + mix of Journey shader tutorial, snow studio and some tweaks).<para/>
	/// https://www.alanzucconi.com/2019/10/08/journey-sand-shader-1/ <para/>
	///	https://www.artstation.com/artwork/J2wBz
	/// </summary>
	ae::Shader m_Shader;
};
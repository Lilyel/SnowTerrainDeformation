#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../CubeMap/CubeMap.h"
#include "../Texture/Texture2D.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// A texture that make a cube (6 sides).<para>
	/// Can be send to shader to process refraction or reflection.<para/>
	/// Can also be used to make a skybox.<para/>
	/// The cubemap is composed of 6 textures, each one attached to a cube face.<para/>
	/// Order : Right, Left, Top, Bottom, Front, Back.
	/// </summary>
	class AERO_CORE_EXPORT ImageBasedLighting : public Resource
	{
	public:
		/// <summary>Precompute diffuse irradiance and specular radiance cube map with the given environment map.</summary>
		/// <param name="_EnvironmentMap">The environment map to use for precomputing the diffuse irradiance and specular radiance.</param>
		ImageBasedLighting( CubeMap& _EnvironmentMap );

		/// <summary>Precompute diffuse irradiance and specular radiance cube map with the given environment map.</summary>
		/// <param name="_EnvironmentMap">The environment map to use for precomputing the diffuse irradiance and specular radiance.</param>
		void Set( CubeMap& _EnvironmentMap );

		/// <summary>Retrieve the precomputed diffuse irradiance map.</summary>
		/// <returns>The precomputed irradiance map.</returns>
		const CubeMap& GetIrradianceMap() const;

		/// <summary>Retrieve the precomputed specular radiance map.</summary>
		/// <returns>The precomputed radiance map.</returns>
		const CubeMap& GetRadianceMap() const;

		/// <summary>Retrieve the precomputed integration of the BRDF.</summary>
		/// <returns>The precomputed integration of the BRDF.</returns>
		const Texture2D& GetBRDFLut() const;

		/// <summary>Retrieve the maximum level of mip-map of the radiance map.</summary>
		/// <returns>The maximum level of mip-map of the radiance map.</returns>
		Uint32 GetMaxLod() const;

	private:
		/// <summary>Precompute the diffuse irradiance and specular radiance from the given environment map.</summary>
		void Precompute( CubeMap& _EnvironmentMap );

	private:
		/// <summary>Diffuse irradiance map.</summary>
		CubeMap m_Irradiance;

		/// <summary>Specular radiance map.</summary>
		CubeMap m_Radiance;

		/// <summary>Integration of the BRDF.</summary>
		Texture2D m_BRDFLut;

		/// <summary>The maximum level of mip-map of the radiance map.</summary>
		Uint32 m_MaxLod;
	};
}
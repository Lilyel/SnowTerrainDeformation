#pragma once

#include "../../Toolbox/Toolbox.h"
#include "Material.h"
#include "../Shader/ShaderParameter/ShaderParameterCubeMap.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>Skybox shading settings for rendering.</summary>
	/// <seealso cref="Material"/>
	/// <seealso cref="Skybox"/>
	class AERO_CORE_EXPORT SkyboxMaterial : public Material
	{
	public:
		/// <summary>Set the shader to the default skybox shader and create the skybox properties.</summary>
		SkyboxMaterial();

		/// <summary>Retrieve the parameter for the skybox cubemap texture.</summary>
		/// <returns>The parameter for the skybox cubemap texture.</returns>
		ShaderParameterCubeMap& GetTexture();

		/// <summary>Retrieve the parameter for the skybox cubemap texture.</summary>
		/// <returns>The parameter for the skybox cubemap texture.</returns>
		const ShaderParameterCubeMap& GetTexture() const;

	private:
		/// <summary>Parameter for the skybox cubemap texture.</summary>
		ShaderParameterCubeMap* m_Texture;
	};

} // ae

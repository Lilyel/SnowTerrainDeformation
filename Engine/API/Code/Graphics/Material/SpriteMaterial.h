#pragma once

#include "../../Toolbox/Toolbox.h"
#include "Material.h"
#include "../Shader/ShaderParameter/ShaderParameterTextureBool.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>Sprite shading settings for rendering.</summary>
	/// <seealso cref="Material"/>
	/// <seealso cref="Sprite"/>
	class AERO_CORE_EXPORT SpriteMaterial : public Material
	{
	public:
		/// <summary>Set the shader to the default 2D shader and create the sprites properties.</summary>
		SpriteMaterial();

		/// <summary>Retrieve the parameter for the sprite texture.</summary>
		/// <returns>The parameter for the sprite texture.</returns>
		ShaderParameterTextureBool& GetTexture();

		/// <summary>Retrieve the parameter for the sprite texture.</summary>
		/// <returns>The parameter for the sprite texture.</returns>
		const ShaderParameterTextureBool& GetTexture() const;

	private:
		/// <summary>Parameter for the sprite texture.</summary>
		ShaderParameterTextureBool* m_Texture;
	};

} // ae

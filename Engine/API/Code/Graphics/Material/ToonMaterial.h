#pragma once

#include "../../Toolbox/Toolbox.h"
#include "Material.h"
#include "../Shader/ShaderParameter/ShaderParameterColor.h"
#include "../Shader/ShaderParameter/ShaderParameterTextureBool.h"
#include "../Shader/ShaderParameter/ShaderParameterFloat.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>Toon shading settings for rendering.</summary>
	/// <seealso cref="Material"/>
	class AERO_CORE_EXPORT ToonMaterial : public Material
	{
	public:
		/// <summary>Set the shader to the default toon shader and create all the shader parameters for it.</summary>
		ToonMaterial();

		/// <summary>Retrieve the parameter for the diffuse color.</summary>
		/// <returns>The parameter for the diffuse color.</returns>
		ShaderParameterColor& GetDiffuseColor();

		/// <summary>Retrieve the parameter for the diffuse color.</summary>
		/// <returns>The parameter for the diffuse color.</returns>
		const ShaderParameterColor& GetDiffuseColor() const;

		/// <summary>Retrieve the parameter for the diffuse texture.</summary>
		/// <returns>The parameter for the diffuse texture.</returns>
		ShaderParameterTextureBool& GetDiffuseTexture();

		/// <summary>Retrieve the parameter for the diffuse texture.</summary>
		/// <returns>The parameter for the diffuse texture.</returns>
		const ShaderParameterTextureBool& GetDiffuseTexture() const;



		/// <summary>Retrieve the parameter for the specular color.</summary>
		/// <returns>The parameter for the specular color.</returns>
		ShaderParameterColor& GetSpecularColor();

		/// <summary>Retrieve the parameter for the specular color.</summary>
		/// <returns>The parameter for the specular color.</returns>
		const ShaderParameterColor& GetSpecularColor() const;

		/// <summary>Retrieve the parameter for the specular texture.</summary>
		/// <returns>The parameter for the specular texture.</returns>
		ShaderParameterTextureBool& GetSpecularTexture();

		/// <summary>Retrieve the parameter for the specular texture.</summary>
		/// <returns>The parameter for the specular texture.</returns>
		const ShaderParameterTextureBool& GetSpecularTexture() const;



		/// <summary>Retrieve the parameter for the shininess.</summary>
		/// <returns>The parameter for the shininess.</returns>
		ShaderParameterFloat& GetShininess();

		/// <summary>Retrieve the parameter for the shininess.</summary>
		/// <returns>The parameter for the shininess.</returns>
		const ShaderParameterFloat& GetShininess() const;

		/// <summary>Retrieve the parameter for the shininess texture.</summary>
		/// <returns>The parameter for the shininess texture.</returns>
		ShaderParameterTextureBool& GetShininessTexture();

		/// <summary>Retrieve the parameter for the shininess texture.</summary>
		/// <returns>The parameter for the shininess texture.</returns>
		const ShaderParameterTextureBool& GetShininessTexture() const;


		/// <summary>Retrieve the parameter for the normal texture.</summary>
		/// <returns>The parameter for the normal texture.</returns>
		ShaderParameterTextureBool& GetNormalTexture();

		/// <summary>Retrieve the parameter for the normal texture.</summary>
		/// <returns>The parameter for the normal texture.</returns>
		const ShaderParameterTextureBool& GetNormalTexture() const;



		/// <summary>Retrieve the parameter for the ambient color.</summary>
		/// <returns>The parameter for the ambient color.</returns>
		ShaderParameterColor& GetAmbientColor();

		/// <summary>Retrieve the parameter for the ambient color.</summary>
		/// <returns>The parameter for the ambient color.</returns>
		const ShaderParameterColor& GetAmbientColor() const;

		/// <summary>Retrieve the parameter for the ambient texture.</summary>
		/// <returns>The parameter for the ambient texture.</returns>
		ShaderParameterTextureBool& GetAmbientTexture();

		/// <summary>Retrieve the parameter for the shininess texture.</summary>
		/// <returns>The parameter for the shininess texture.</returns>
		const ShaderParameterTextureBool& GetAmbientTexture() const;

		/// <summary>Retrieve the parameter for the ambient strength.</summary>
		/// <returns>The parameter for the ambient strength.</returns>
		ShaderParameterFloat& GetAmbientStrength();

		/// <summary>Retrieve the parameter for the ambient strength.</summary>
		/// <returns>The parameter for the ambient strength.</returns>
		const ShaderParameterFloat& GetAmbientStrength() const;


		/// <summary>Retrieve the parameter for the rim color.</summary>
		/// <returns>The parameter for the rim color.</returns>
		ShaderParameterColor& GetRimColor();

		/// <summary>Retrieve the parameter for the rim color.</summary>
		/// <returns>The parameter for the rim color.</returns>
		const ShaderParameterColor& GetRimColor() const;


		/// <summary>Retrieve the parameter for the rim size.</summary>
		/// <returns>The parameter for the rim size.</returns>
		ShaderParameterFloat& GetRimSize();

		/// <summary>Retrieve the parameter for the rim size.</summary>
		/// <returns>The parameter for the rim size.</returns>
		const ShaderParameterFloat& GetRimSize() const;


		/// <summary>Retrieve the parameter for the rim threshold.</summary>
		/// <returns>The parameter for the rim threshold.</returns>
		ShaderParameterFloat& GetRimThreshold();

		/// <summary>Retrieve the parameter for the rim threshold.</summary>
		/// <returns>The parameter for the rim threshold.</returns>
		const ShaderParameterFloat& GetRimThreshold() const;

	private:
		/// <summary>Parameter for the diffuse color.</summary>
		ShaderParameterColor* m_DiffuseColor;

		/// <summary>Parameter for the diffuse texture.</summary>
		ShaderParameterTextureBool* m_DiffuseTexture;


		/// <summary>Parameter for the specular color.</summary>
		ShaderParameterColor* m_SpecularColor;

		/// <summary>Parameter for the specular texture.</summary>
		ShaderParameterTextureBool* m_SpecularTexture;


		/// /// <summary>Parameter for the shininess.</summary>
		ShaderParameterFloat* m_Shininess;

		/// <summary>Parameter for the shininess texture.</summary>
		ShaderParameterTextureBool* m_ShininessTexture;


		/// <summary>Parameter for the normal texture.</summary>
		ShaderParameterTextureBool* m_NormalTexture;


		/// <summary>Parameter for the ambient color.</summary>
		ShaderParameterColor* m_AmbientColor;

		/// <summary>Parameter for the ambient texture.</summary>
		ShaderParameterTextureBool* m_AmbientTexture;

		/// <summary>Parameter for the ambient strength.</summary>
		ShaderParameterFloat* m_AmbientStrength;


		/// <summary>Parameter for rim color.</summary>
		ShaderParameterColor* m_RimColor;

		/// <summary>Parameter for the rim size.</summary>
		ShaderParameterFloat* m_RimSize;

		/// <summary>Parameter for the rim threshold.</summary>
		ShaderParameterFloat* m_RimThreshold;
	};

} // ae

#pragma once

#include "../../Toolbox/Toolbox.h"
#include "Material.h"
#include "../Shader/Shader.h"
#include "../Shader/ShaderParameter/ShaderParameterColor.h"
#include "../Shader/ShaderParameter/ShaderParameterTextureBool.h"
#include "../Shader/ShaderParameter/ShaderParameterTexture.h"
#include "../Shader/ShaderParameter/ShaderParameterCubeMap.h"
#include "../Shader/ShaderParameter/ShaderParameterFloat.h"
#include "../Shader/ShaderParameter/ShaderParameterInt.h"
#include "../Shader/ShaderParameter/ShaderParameterBool.h"

namespace ae
{
	class ImageBasedLighting;

	/// \ingroup graphics
	/// <summary>Cook-Torrance shading settings for rendering.</summary>
	/// <seealso cref="Material"/>
	class AERO_CORE_EXPORT CookTorranceMaterial : public Material
	{
	public:
		/// <summary>Set the shader to the default Cook-Torrance shader and setup its parameters.</summary>
		CookTorranceMaterial();

		/// <summary>Retrieve the parameter for the base color.</summary>
		/// <returns>The parameter for the base color.</returns>
		ShaderParameterColor& GetBaseColor();

		/// <summary>Retrieve the parameter for the base color.</summary>
		/// <returns>The parameter for the base color.</returns>
		const ShaderParameterColor& GetBaseColor() const;

		/// <summary>Retrieve the parameter for the base color texture.</summary>
		/// <returns>The parameter for the base color texture.</returns>
		ShaderParameterTextureBool& GetBaseColorTexture();

		/// <summary>Retrieve the parameter for the base color texture.</summary>
		/// <returns>The parameter for the base color texture.</returns>
		const ShaderParameterTextureBool& GetBaseColorTexture() const;


		/// <summary>Retrieve the parameter for the normal texture.</summary>
		/// <returns>The parameter for the base normal texture.</returns>
		ShaderParameterTextureBool& GetNormalTexture();

		/// <summary>Retrieve the parameter for the normal color texture.</summary>
		/// <returns>The parameter for the base normal texture.</returns>
		const ShaderParameterTextureBool& GetNormalTexture() const;


		/// <summary>Retrieve the parameter for the emissive color.</summary>
		/// <returns>The parameter for the emissive color.</returns>
		ShaderParameterColor& GetEmissiveColor();

		/// <summary>Retrieve the parameter for the emissive color.</summary>
		/// <returns>The parameter for the emissive color.</returns>
		const ShaderParameterColor& GetEmissiveColor() const;

		/// <summary>Retrieve the parameter for the emissive color texture.</summary>
		/// <returns>The parameter for the emissive color texture.</returns>
		ShaderParameterTextureBool& GetEmissiveColorTexture();

		/// <summary>Retrieve the parameter for the emissive color texture.</summary>
		/// <returns>The parameter for the emissive color texture.</returns>
		const ShaderParameterTextureBool& GetEmissiveColorTexture() const;


		/// <summary>Retrieve the parameter for the metalness.</summary>
		/// <returns>The parameter for the metalness.</returns>
		ShaderParameterFloat& GetMetalness();

		/// <summary>Retrieve the parameter for the metalness.</summary>
		/// <returns>The parameter for the metalness.</returns>
		const ShaderParameterFloat& GetMetalness() const;

		/// <summary>Retrieve the parameter for the metalness texture.</summary>
		/// <returns>The parameter for the metalness texture.</returns>
		ShaderParameterTextureBool& GetMetalnessTexture();

		/// <summary>Retrieve the parameter for the metalness texture.</summary>
		/// <returns>The parameter for the metalness texture.</returns>
		const ShaderParameterTextureBool& GetMetalnessTexture() const;


		/// <summary>Retrieve the parameter for the roughness.</summary>
		/// <returns>The parameter for the roughness.</returns>
		ShaderParameterFloat& GetRoughness();

		/// <summary>Retrieve the parameter for the roughness.</summary>
		/// <returns>The parameter for the roughness.</returns>
		const ShaderParameterFloat& GetRoughness() const;

		/// <summary>Retrieve the parameter for the roughness texture.</summary>
		/// <returns>The parameter for the roughness texture.</returns>
		ShaderParameterTextureBool& GetRoughnessTexture();

		/// <summary>Retrieve the parameter for the roughness texture.</summary>
		/// <returns>The parameter for the roughness texture.</returns>
		const ShaderParameterTextureBool& GetRoughnessTexture() const;

		
		/// <summary>Retrieve the parameter for the ambient occlusion.</summary>
		/// <returns>The parameter for the ambient occlusion.</returns>
		ShaderParameterFloat& GetAmbientOcclusion();

		/// <summary>Retrieve the parameter for the ambient occlusion.</summary>
		/// <returns>The parameter for the ambient occlusion.</returns>
		const ShaderParameterFloat& GetAmbientOcclusion() const;

		/// <summary>Retrieve the parameter for the ambient occlusion texture.</summary>
		/// <returns>The parameter for the ambient occlusion texture.</returns>
		ShaderParameterTextureBool& GetAmbientOcclusionTexture();

		/// <summary>Retrieve the parameter for the ambient occlusion texture.</summary>
		/// <returns>The parameter for the ambient occlusion texture.</returns>
		const ShaderParameterTextureBool& GetAmbientOcclusionTexture() const;


		/// <summary>Retrieve the parameter for the ambient strength.</summary>
		/// <returns>The parameter for the ambient strength.</returns>
		const ShaderParameterFloat& GetAmbientStrength() const;

		/// <summary>Retrieve the parameter for the ambient strength.</summary>
		/// <returns>The parameter for the ambient strength.</returns>
		ShaderParameterFloat& GetAmbientStrength();


		/// <summary>Retrieve the parameter for the usage of image based lighting.</summary>
		/// <returns>The parameter for the usage of the image based lighting.</returns>
		const ShaderParameterBool& GetUseIBL() const;

		/// <summary>Retrieve the parameter for the usage of image based lighting.</summary>
		/// <returns>The parameter for the usage of the image based lighting.</returns>
		ShaderParameterBool& GetUseIBL();


		/// <summary>Retrieve the parameter of the irradiance map used for image based lighting.</summary>
		/// <returns>The parameter of the irradiance map used for image based lighting.</returns>
		const ShaderParameterCubeMap& GetIrradianceMap() const;

		/// <summary>Retrieve the parameter of the irradiance map used for image based lighting.</summary>
		/// <returns>The parameter of the irradiance map used for image based lighting.</returns>
		ShaderParameterCubeMap& GetIrradianceMap();


		/// <summary>Retrieve the parameter of the radiance map used for image based lighting.</summary>
		/// <returns>The parameter of the radiance map used for image based lighting.</returns>
		const ShaderParameterCubeMap& GetRadianceMap() const;

		/// <summary>Retrieve the parameter of the radiance map used for image based lighting.</summary>
		/// <returns>The parameter of the radiance map used for image based lighting.</returns>
		ShaderParameterCubeMap& GetRadianceMap();


		/// <summary>Retrieve the parameter of the BRDF lut used for image based lighting.</summary>
		/// <returns>The parameter of the BRDF lut used for image based lighting.</returns>
		const ShaderParameterTexture& GetBRDFLut() const;

		/// <summary>Retrieve the parameter of the BRDF lut used for image based lighting.</summary>
		/// <returns>The parameter of the BRDF lut used for image based lighting.</returns>
		ShaderParameterTexture& GetBRDFLut();


		/// <summary>Retrieve the parameter of the maximum level of mip-map of the radiance map used for image based lighting.</summary>
		/// <returns>The parameter of the maximum level of mip-map of the radiance map used for image based lighting.</returns>
		const ShaderParameterInt& GetRadianceMaxLod() const;

		/// <summary>Retrieve the parameter of the maximum level of mip-map of the radiance map used for image based lighting.</summary>
		/// <returns>The parameter of the maximum level of mip-map of the radiance map used for image based lighting.</returns>
		ShaderParameterInt& GetRadianceMaxLod();

		/// <summary>Set the irradiance, radiance, BRDF lut and maximum mip-map settings from the given precomputed data.</summary>
		/// <param name="_IBL">The precomputed data for image based lighting.</param>
		void SetIBL( const ImageBasedLighting& _IBL );

		/// <summary>Reset the settings of the image based lighting.</summary>
		void RemoveIBL();



		/// <summary>Retrieve the parameter for the application of a gamma correction on the color result.</summary>
		/// <returns>The parameter for the application of a gamma correction on the color result.</returns>
		const ShaderParameterBool& GetApplyGammaCorrection() const;

		/// <summary>Retrieve the parameter the application of a gamma correction on the color result.</summary>
		/// <returns>The parameter for the application of a gamma correction on the color result.</returns>
		ShaderParameterBool& GetApplyGammaCorrection();

	private:
		/// <summary>Parameter for the base color.</summary>
		ShaderParameterColor* m_BaseColor;

		/// <summary>Parameter for the base texture.</summary>
		ShaderParameterTextureBool* m_BaseTexture;
		

		/// <summary>Parameter for the normal texture.</summary>
		ShaderParameterTextureBool* m_NormalTexture;


		/// <summary>Parameter for the emissive color.</summary>
		ShaderParameterColor* m_EmissiveColor;

		/// <summary>Parameter for the emissive texture.</summary>
		ShaderParameterTextureBool* m_EmissiveTexture;

		
		/// <summary>Parameter for the metalness color.</summary>
		ShaderParameterFloat* m_Metalness;

		/// <summary>Parameter for the metalness texture.</summary>
		ShaderParameterTextureBool* m_MetalnessTexture;


		/// <summary>Parameter for the roughness color.</summary>
		ShaderParameterFloat* m_Roughness;

		/// <summary>Parameter for the roughness texture.</summary>
		ShaderParameterTextureBool* m_RoughnessTexture;


		/// <summary>Parameter for the ambient occlusion.</summary>
		ShaderParameterFloat* m_AmbientOcclusion;

		/// <summary>Parameter for the ambient occlusion texture.</summary>
		ShaderParameterTextureBool* m_AmbientOcclusionTexture;


		/// <summary>Parameter for the ambient strength.</summary>
		ShaderParameterFloat* m_AmbientStrength;

		/// <summary>Parameter to tell if the shader must process the image based lighting.</summary>
		ShaderParameterBool* m_UseIBL;

		/// <summary>Irradiance map to use for the image based lighting.</summary>
		ShaderParameterCubeMap* m_IrradianceMap;

		/// <summary>Radiance map to use for the image based lighting.</summary>
		ShaderParameterCubeMap* m_RadianceMap;

		/// <summary>BRDF lut for the image based lighting.</summary>
		ShaderParameterTexture* m_BRDFLut;

		/// <summary>Maximum level of mip-map for the radiance of the image based lighting.</summary>
		ShaderParameterInt* m_RadianceMaxLod;


		/// <summary>Parameter to tell if the shader must convert the linear color result to sRGB.</summary>
		ShaderParameterBool* m_ApplyGammaCorrection;
	};

} // ae

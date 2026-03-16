#include "CookTorranceMaterial.h"

#include "../ImageBasedLighting/ImageBasedLighting.h"
#include "../../Aero/Aero.h"

namespace ae
{
	CookTorranceMaterial::CookTorranceMaterial()
	{
		SetShader( *Aero.GetResourcesManager().GetDefaultCookTorranceShader() );

		const std::string& BaseColorName = GetDefaultParameterName( DefaultParameters::PBR_BaseColor );
		m_BaseColor = AddColorParameterToMaterial( BaseColorName, BaseColorName, Color::White );

		const std::string& BaseColorTextureName = GetDefaultParameterName( DefaultParameters::PBR_BaseColorTexture );
		m_BaseTexture = (ShaderParameterTextureBool*)AddTextureParameterToMaterial( BaseColorTextureName, BaseColorTextureName, nullptr, True );


		const std::string& NormalCameraTextureName = GetDefaultParameterName( DefaultParameters::PBR_NormalCameraTexture );
		m_NormalTexture = (ShaderParameterTextureBool*)AddTextureParameterToMaterial( NormalCameraTextureName, NormalCameraTextureName, nullptr, True );


		const std::string& EmissionColorName = GetDefaultParameterName( DefaultParameters::PBR_EmissionColor );
		m_EmissiveColor = AddColorParameterToMaterial( EmissionColorName, EmissionColorName, Color::Black );

		const std::string& EmissionColorTextureName = GetDefaultParameterName( DefaultParameters::PBR_EmissionColorTexture );
		m_EmissiveTexture = (ShaderParameterTextureBool*)AddTextureParameterToMaterial( EmissionColorTextureName, EmissionColorTextureName, nullptr, True );


		const std::string& MetalnessName = GetDefaultParameterName( DefaultParameters::PBR_Metalness );
		m_Metalness = AddFloatParameterToMaterial( MetalnessName, MetalnessName, 0.0f, 0.0f, 1.0f );

		const std::string& MetalnessTextureName = GetDefaultParameterName( DefaultParameters::PBR_MetalnessTexture );
		m_MetalnessTexture = (ShaderParameterTextureBool*)AddTextureParameterToMaterial( MetalnessTextureName, MetalnessTextureName, nullptr, True );


		const std::string& RoughnessName = GetDefaultParameterName( DefaultParameters::PBR_Roughness );
		m_Roughness = AddFloatParameterToMaterial( RoughnessName, RoughnessName, 0.2f, 0.0f, 1.0f );

		const std::string& RoughnessTextureName = GetDefaultParameterName( DefaultParameters::PBR_RoughnessTexture );
		m_RoughnessTexture = (ShaderParameterTextureBool*)AddTextureParameterToMaterial( RoughnessTextureName, RoughnessTextureName, nullptr, True );


		const std::string& AmbientOcclusionName = GetDefaultParameterName( DefaultParameters::PBR_AmbientOcclusion );
		m_AmbientOcclusion = AddFloatParameterToMaterial( AmbientOcclusionName, AmbientOcclusionName, 0.0f, 0.0f, 1.0f );

		const std::string& AmbientOcclusionTextureName = GetDefaultParameterName( DefaultParameters::PBR_AmbientOcclusionTexture );
		m_AmbientOcclusionTexture = (ShaderParameterTextureBool*)AddTextureParameterToMaterial( AmbientOcclusionTextureName, AmbientOcclusionTextureName, nullptr, True );

		const std::string& AmbientStrengthName = GetDefaultParameterName( DefaultParameters::AmbientStrength );
		m_AmbientStrength = AddFloatParameterToMaterial( AmbientStrengthName, AmbientStrengthName, 0.0f );


		const std::string& UseIBLName = GetDefaultParameterName( DefaultParameters::IBL_UseIBL );
		m_UseIBL = AddBoolParameterToMaterial( UseIBLName, UseIBLName, False );
		m_UseIBL->SetEditable( False );

		const std::string& IrradianceName = GetDefaultParameterName( DefaultParameters::IBL_IrradianceMap );
		m_IrradianceMap = AddCubeMapParameterToMaterial( IrradianceName, IrradianceName, nullptr );

		const std::string& RadianceName = GetDefaultParameterName( DefaultParameters::IBL_RadianceMap );
		m_RadianceMap = AddCubeMapParameterToMaterial( RadianceName, RadianceName, nullptr );

		const std::string& BRDFLutName = GetDefaultParameterName( DefaultParameters::IBL_BRDFLut );
		m_BRDFLut = AddTextureParameterToMaterial( BRDFLutName, BRDFLutName, nullptr );

		const std::string& MaxLodName = GetDefaultParameterName( DefaultParameters::IBL_MaxLod );
		m_RadianceMaxLod = AddIntParameterToMaterial( MaxLodName, MaxLodName, 0 );
		m_RadianceMaxLod->SetEditable( False );
		

		const std::string& ApplyGammaName = GetDefaultParameterName( DefaultParameters::HDR_ApplyGammaCorrection );
		m_ApplyGammaCorrection = AddBoolParameterToMaterial( ApplyGammaName, ApplyGammaName, False );

		SaveUniformsLocation();

		SetName( std::string( "CookTorranceMaterial_" ) + std::to_string( GetResourceID() ) );
	}

	ShaderParameterColor& ae::CookTorranceMaterial::GetBaseColor()
	{
		return *m_BaseColor;
	}

	const ShaderParameterColor& CookTorranceMaterial::GetBaseColor() const
	{
		return *m_BaseColor;
	}

	ShaderParameterTextureBool& CookTorranceMaterial::GetBaseColorTexture()
	{
		return *m_BaseTexture;
	}

	const ShaderParameterTextureBool& CookTorranceMaterial::GetBaseColorTexture() const
	{
		return *m_BaseTexture;
	}

	ShaderParameterTextureBool& CookTorranceMaterial::GetNormalTexture()
	{
		return *m_NormalTexture;
	}

	const ShaderParameterTextureBool& CookTorranceMaterial::GetNormalTexture() const
	{
		return *m_NormalTexture;
	}

	ShaderParameterColor& CookTorranceMaterial::GetEmissiveColor()
	{
		return *m_EmissiveColor;
	}

	const ShaderParameterColor& CookTorranceMaterial::GetEmissiveColor() const
	{
		return *m_EmissiveColor;
	}

	ShaderParameterTextureBool& CookTorranceMaterial::GetEmissiveColorTexture()
	{
		return *m_EmissiveTexture;
	}

	const ShaderParameterTextureBool& CookTorranceMaterial::GetEmissiveColorTexture() const
	{
		return *m_EmissiveTexture;
	}

	ShaderParameterFloat& CookTorranceMaterial::GetMetalness()
	{
		return *m_Metalness;
	}

	const ShaderParameterFloat& CookTorranceMaterial::GetMetalness() const
	{
		return *m_Metalness;
	}

	ShaderParameterTextureBool& CookTorranceMaterial::GetMetalnessTexture()
	{
		return *m_MetalnessTexture;
	}

	const ShaderParameterTextureBool& CookTorranceMaterial::GetMetalnessTexture() const
	{
		return *m_MetalnessTexture;
	}

	ShaderParameterFloat& CookTorranceMaterial::GetRoughness()
	{
		return *m_Roughness;
	}

	const ShaderParameterFloat& CookTorranceMaterial::GetRoughness() const
	{
		return *m_Roughness;
	}

	ShaderParameterTextureBool& CookTorranceMaterial::GetRoughnessTexture()
	{
		return *m_RoughnessTexture;
	}

	const ShaderParameterTextureBool& CookTorranceMaterial::GetRoughnessTexture() const
	{
		return *m_RoughnessTexture;
	}

	ShaderParameterFloat& CookTorranceMaterial::GetAmbientOcclusion()
	{
		return *m_AmbientOcclusion;
	}

	const ShaderParameterFloat& CookTorranceMaterial::GetAmbientOcclusion() const
	{
		return *m_AmbientOcclusion;
	}

	ShaderParameterTextureBool& CookTorranceMaterial::GetAmbientOcclusionTexture()
	{
		return *m_AmbientOcclusionTexture;
	}

	const ShaderParameterTextureBool& CookTorranceMaterial::GetAmbientOcclusionTexture() const
	{
		return *m_AmbientOcclusionTexture;
	}

	const ShaderParameterFloat& CookTorranceMaterial::GetAmbientStrength() const
	{
		return *m_AmbientStrength;
	}

	ShaderParameterFloat& CookTorranceMaterial::GetAmbientStrength()
	{
		return *m_AmbientStrength;
	}

	const ShaderParameterBool& CookTorranceMaterial::GetUseIBL() const
	{
		return *m_UseIBL;
	}

	ShaderParameterBool& CookTorranceMaterial::GetUseIBL()
	{
		return *m_UseIBL;
	}

	const ShaderParameterCubeMap& CookTorranceMaterial::GetIrradianceMap() const
	{
		return *m_IrradianceMap;
	}

	ShaderParameterCubeMap& CookTorranceMaterial::GetIrradianceMap()
	{
		return *m_IrradianceMap;
	}

	const ShaderParameterCubeMap& CookTorranceMaterial::GetRadianceMap() const
	{
		return *m_RadianceMap;
	}

	ShaderParameterCubeMap& CookTorranceMaterial::GetRadianceMap()
	{
		return *m_RadianceMap;
	}

	const ShaderParameterTexture& CookTorranceMaterial::GetBRDFLut() const
	{
		return *m_BRDFLut;
	}

	ShaderParameterTexture& CookTorranceMaterial::GetBRDFLut()
	{
		return *m_BRDFLut;
	}

	const ShaderParameterInt& CookTorranceMaterial::GetRadianceMaxLod() const
	{
		return *m_RadianceMaxLod;
	}

	ShaderParameterInt& CookTorranceMaterial::GetRadianceMaxLod()
	{
		return *m_RadianceMaxLod;
	}

	void CookTorranceMaterial::SetIBL( const ImageBasedLighting& _IBL )
	{
		m_UseIBL->SetValue( True );
		m_IrradianceMap->SetValue( &_IBL.GetIrradianceMap() );
		m_RadianceMap->SetValue( &_IBL.GetRadianceMap() );
		m_BRDFLut->SetValue( &_IBL.GetBRDFLut() );
		m_RadianceMaxLod->SetValue( Cast( Int32, _IBL.GetMaxLod() ) );
	}

	void CookTorranceMaterial::RemoveIBL()
	{
		m_UseIBL->SetValue( False );
		m_IrradianceMap->SetValue( nullptr );
		m_RadianceMap->SetValue( nullptr );
		m_BRDFLut->SetValue( nullptr );
		m_RadianceMaxLod->SetValue( 0 );
	}

	const ShaderParameterBool& CookTorranceMaterial::GetApplyGammaCorrection() const
	{
		return *m_ApplyGammaCorrection;
	}

	ShaderParameterBool& CookTorranceMaterial::GetApplyGammaCorrection()
	{
		return *m_ApplyGammaCorrection;
	}

} // ae
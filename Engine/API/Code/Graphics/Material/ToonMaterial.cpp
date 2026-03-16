#include "ToonMaterial.h"

#include "../../Aero/Aero.h"

namespace ae
{
	ToonMaterial::ToonMaterial()
	{
		SetShader( *Aero.GetResourcesManager().GetDefaultToonShader() );

		const std::string& DiffuseColorName = GetDefaultParameterName( DefaultParameters::DiffuseColor );
		m_DiffuseColor = AddColorParameterToMaterial( DiffuseColorName, DiffuseColorName, Color::White );

		const std::string& DiffuseTextureName = GetDefaultParameterName( DefaultParameters::DiffuseTexture );
		m_DiffuseTexture = (ShaderParameterTextureBool*)AddTextureParameterToMaterial( DiffuseTextureName, DiffuseTextureName, nullptr, True );


		const std::string& SpecularColorName = GetDefaultParameterName( DefaultParameters::SpecularColor );
		m_SpecularColor = AddColorParameterToMaterial( SpecularColorName, SpecularColorName, Color::White );

		const std::string& SpecularTextureName = GetDefaultParameterName( DefaultParameters::SpecularTexture );
		m_SpecularTexture = (ShaderParameterTextureBool*)AddTextureParameterToMaterial( SpecularTextureName, SpecularTextureName, nullptr, True );


		const std::string& ShininessName = GetDefaultParameterName( DefaultParameters::Shininess );
		m_Shininess = AddFloatParameterToMaterial( ShininessName, ShininessName, 1024.0f );

		const std::string& ShininessTextureName = GetDefaultParameterName( DefaultParameters::ShininessTexture );
		m_ShininessTexture = (ShaderParameterTextureBool*)AddTextureParameterToMaterial( ShininessTextureName, ShininessTextureName, nullptr, True );


		const std::string& NormalTextureName = GetDefaultParameterName( DefaultParameters::NormalTexture );
		m_NormalTexture = (ShaderParameterTextureBool*)AddTextureParameterToMaterial( NormalTextureName, NormalTextureName, nullptr, True );


		const std::string& AmbientColorName = GetDefaultParameterName( DefaultParameters::AmbientColor );
		m_AmbientColor = AddColorParameterToMaterial( AmbientColorName, AmbientColorName, Color::White );

		const std::string& AmbientTextureName = GetDefaultParameterName( DefaultParameters::AmbientTexture );
		m_AmbientTexture = (ShaderParameterTextureBool*)AddTextureParameterToMaterial( AmbientTextureName, AmbientTextureName, nullptr, True );

		const std::string& AmbientStrengthName = GetDefaultParameterName( DefaultParameters::AmbientStrength );
		m_AmbientStrength = AddFloatParameterToMaterial( AmbientStrengthName, AmbientStrengthName, 0.0f );



		const std::string& RimColorName = GetDefaultParameterName( DefaultParameters::Toon_RimColor );
		m_RimColor = AddColorParameterToMaterial( RimColorName, RimColorName, Color::White );

		const std::string& RimSizeName = GetDefaultParameterName( DefaultParameters::Toon_RimSize );
		m_RimSize = AddFloatParameterToMaterial( RimSizeName, RimSizeName, 0.3f, 0.0f, 1.0f );

		const std::string& RimThresholdName = GetDefaultParameterName( DefaultParameters::Toon_RimThreshold );
		m_RimThreshold = AddFloatParameterToMaterial( RimThresholdName, RimThresholdName, 0.1f, 0.0f, 1.0f );

		SaveUniformsLocation();

		SetName( std::string( "ToonMaterial_" ) + std::to_string( GetResourceID() ) );
	}
	ShaderParameterColor& ToonMaterial::GetDiffuseColor()
	{
		return *m_DiffuseColor;
	}
	const ShaderParameterColor& ToonMaterial::GetDiffuseColor() const
	{
		return *m_DiffuseColor;
	}
	ShaderParameterTextureBool& ToonMaterial::GetDiffuseTexture()
	{
		return *m_DiffuseTexture;
	}
	const ShaderParameterTextureBool& ToonMaterial::GetDiffuseTexture() const
	{
		return *m_DiffuseTexture;
	}
	ShaderParameterColor& ToonMaterial::GetSpecularColor()
	{
		return *m_SpecularColor;
	}
	const ShaderParameterColor& ToonMaterial::GetSpecularColor() const
	{
		return *m_SpecularColor;
	}
	ShaderParameterTextureBool& ToonMaterial::GetSpecularTexture()
	{
		return *m_SpecularTexture;
	}
	const ShaderParameterTextureBool& ToonMaterial::GetSpecularTexture() const
	{
		return *m_SpecularTexture;
	}
	ShaderParameterFloat& ToonMaterial::GetShininess()
	{
		return *m_Shininess;
	}
	const ShaderParameterFloat& ToonMaterial::GetShininess() const
	{
		return *m_Shininess;
	}
	ShaderParameterTextureBool& ToonMaterial::GetShininessTexture()
	{
		return *m_ShininessTexture;
	}
	const ShaderParameterTextureBool& ToonMaterial::GetShininessTexture() const
	{
		return *m_ShininessTexture;
	}
	ShaderParameterTextureBool& ToonMaterial::GetNormalTexture()
	{
		return *m_NormalTexture;
	}
	const ShaderParameterTextureBool& ToonMaterial::GetNormalTexture() const
	{
		return *m_NormalTexture;
	}
	ShaderParameterColor& ToonMaterial::GetAmbientColor()
	{
		return *m_AmbientColor;
	}
	const ShaderParameterColor& ToonMaterial::GetAmbientColor() const
	{
		return *m_AmbientColor;
	}
	ShaderParameterTextureBool& ToonMaterial::GetAmbientTexture()
	{
		return *m_AmbientTexture;
	}
	const ShaderParameterTextureBool& ToonMaterial::GetAmbientTexture() const
	{
		return *m_AmbientTexture;
	}
	ShaderParameterFloat& ToonMaterial::GetAmbientStrength()
	{
		return *m_AmbientStrength;
	}
	const ShaderParameterFloat& ToonMaterial::GetAmbientStrength() const
	{
		return *m_AmbientStrength;
	}
	ShaderParameterColor& ToonMaterial::GetRimColor()
	{
		return *m_RimColor;
	}
	const ShaderParameterColor& ToonMaterial::GetRimColor() const
	{
		return *m_RimColor;
	}
	ShaderParameterFloat& ToonMaterial::GetRimSize()
	{
		return *m_RimSize;
	}
	const ShaderParameterFloat& ToonMaterial::GetRimSize() const
	{
		return *m_RimSize;
	}
	ShaderParameterFloat& ToonMaterial::GetRimThreshold()
	{
		return *m_RimThreshold;
	}
	const ShaderParameterFloat& ToonMaterial::GetRimThreshold() const
	{
		return *m_RimThreshold;
	}
} // ae

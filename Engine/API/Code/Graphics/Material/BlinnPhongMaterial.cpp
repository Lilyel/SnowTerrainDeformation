#include "BlinnPhongMaterial.h"

#include "../../Aero/Aero.h"

namespace ae
{

	BlinnPhongMaterial::BlinnPhongMaterial()
	{
		SetShader( Aero.GetResourcesManager().GetDefault3DShader() );

		const std::string& DiffuseColorName = GetDefaultParameterName( DefaultParameters::DiffuseColor );
		m_DiffuseColor = AddColorParameterToMaterial( DiffuseColorName, DiffuseColorName, Color::White );

		const std::string& DiffuseTextureName = GetDefaultParameterName( DefaultParameters::DiffuseTexture );
		m_DiffuseTexture = (ShaderParameterTextureBool*)AddTextureParameterToMaterial( DiffuseTextureName, DiffuseTextureName, nullptr, True );


		const std::string& SpecularColorName = GetDefaultParameterName( DefaultParameters::SpecularColor );
		m_SpecularColor = AddColorParameterToMaterial( SpecularColorName, SpecularColorName, Color::White );

		const std::string& SpecularTextureName = GetDefaultParameterName( DefaultParameters::SpecularTexture );
		m_SpecularTexture = (ShaderParameterTextureBool*)AddTextureParameterToMaterial( SpecularTextureName, SpecularTextureName, nullptr, True );


		const std::string& ShininessName = GetDefaultParameterName( DefaultParameters::Shininess );
		m_Shininess = AddFloatParameterToMaterial( ShininessName, ShininessName, 2.0f );

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

		SaveUniformsLocation();

		SetName( std::string( "BlinnPhongMaterial_" ) + std::to_string( GetResourceID() ) );
	}

	ShaderParameterColor& BlinnPhongMaterial::GetDiffuseColor()
	{
		return *m_DiffuseColor;
	}

	const ShaderParameterColor& BlinnPhongMaterial::GetDiffuseColor() const
	{
		return *m_DiffuseColor;
	}

	ShaderParameterTextureBool& BlinnPhongMaterial::GetDiffuseTexture()
	{
		return *m_DiffuseTexture;
	}

	const ShaderParameterTextureBool& BlinnPhongMaterial::GetDiffuseTexture() const
	{
		return *m_DiffuseTexture;
	}

	ShaderParameterColor& BlinnPhongMaterial::GetSpecularColor()
	{
		return *m_SpecularColor;
	}

	const ShaderParameterColor& BlinnPhongMaterial::GetSpecularColor() const
	{
		return *m_SpecularColor;
	}

	ShaderParameterTextureBool& BlinnPhongMaterial::GetSpecularTexture()
	{
		return *m_SpecularTexture;
	}

	const ShaderParameterTextureBool& BlinnPhongMaterial::GetSpecularTexture() const
	{
		return *m_SpecularTexture;
	}

	ShaderParameterFloat& BlinnPhongMaterial::GetShininess()
	{
		return *m_Shininess;
	}

	const ShaderParameterFloat& BlinnPhongMaterial::GetShininess() const
	{
		return *m_Shininess;
	}

	ShaderParameterTextureBool& BlinnPhongMaterial::GetShininessTexture()
	{
		return *m_ShininessTexture;
	}

	const ShaderParameterTextureBool& BlinnPhongMaterial::GetShininessTexture() const
	{
		return *m_ShininessTexture;
	}

	ShaderParameterTextureBool& BlinnPhongMaterial::GetNormalTexture()
	{
		return *m_NormalTexture;
	}

	const ShaderParameterTextureBool& BlinnPhongMaterial::GetNormalTexture() const
	{
		return *m_NormalTexture;
	}

	ShaderParameterColor& BlinnPhongMaterial::GetAmbientColor()
	{
		return *m_AmbientColor;
	}

	const ShaderParameterColor& BlinnPhongMaterial::GetAmbientColor() const
	{
		return *m_AmbientColor;
	}

	ShaderParameterTextureBool& BlinnPhongMaterial::GetAmbientTexture()
	{
		return *m_AmbientTexture;
	}

	const ShaderParameterTextureBool& BlinnPhongMaterial::GetAmbientTexture() const
	{
		return *m_AmbientTexture;
	}

	ShaderParameterFloat& BlinnPhongMaterial::GetAmbientStrength()
	{
		return *m_AmbientStrength;
	}

	const ShaderParameterFloat& BlinnPhongMaterial::GetAmbientStrength() const
	{
		return *m_AmbientStrength;
	}

} // ae

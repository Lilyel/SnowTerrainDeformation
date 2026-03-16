#include "SkyboxMaterial.h"

#include "../../Aero/Aero.h"

namespace ae
{
	SkyboxMaterial::SkyboxMaterial()
	{
		SetShader( Aero.GetResourcesManager().GetDefaultSkyboxShader() );

		const std::string& CubeMapUniformName = GetDefaultParameterName( DefaultParameters::Skybox_CubeMap );
		m_Texture = (ShaderParameterCubeMap*)AddCubeMapParameterToMaterial( CubeMapUniformName, CubeMapUniformName, nullptr, False );

		SaveUniformsLocation();

		SetName( std::string( "SkyboxMaterial_" ) + std::to_string( GetResourceID() ) );
	}

	ShaderParameterCubeMap& SkyboxMaterial::GetTexture()
	{
		return *m_Texture;
	}

	const ShaderParameterCubeMap& SkyboxMaterial::GetTexture() const
	{
		return *m_Texture;
	}

} // ae


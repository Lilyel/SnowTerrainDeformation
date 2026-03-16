#include "SpriteMaterial.h"

#include "../../Aero/Aero.h"

namespace ae
{

	SpriteMaterial::SpriteMaterial()
	{
		SetShader( Aero.GetResourcesManager().GetDefault2DShader() );

		const std::string& TextureName = GetDefaultParameterName( DefaultParameters::SpriteTexture );
		m_Texture = (ShaderParameterTextureBool*)AddTextureParameterToMaterial( TextureName, TextureName, nullptr, True );

		SaveUniformsLocation();

		SetName( std::string( "SpriteMaterial_" ) + std::to_string( GetResourceID() ) );
	}

	ShaderParameterTextureBool& SpriteMaterial::GetTexture()
	{
		return *m_Texture;
	}

	const ShaderParameterTextureBool& SpriteMaterial::GetTexture() const
	{
		return *m_Texture;
	}

} // ae


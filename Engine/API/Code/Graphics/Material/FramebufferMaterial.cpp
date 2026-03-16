#include "FramebufferMaterial.h"

#include "../../Aero/Aero.h"

namespace ae
{
	FramebufferMaterial::FramebufferMaterial()
	{
		SetShader( Aero.GetResourcesManager().GetDefaultFramebufferShader() );

		const std::string& TextureUniformName = GetDefaultParameterName( DefaultParameters::FramebufferTexture );
		m_Texture = (ShaderParameterTexture*)AddTextureParameterToMaterial( TextureUniformName, TextureUniformName, nullptr, False );

		const std::string& IsDepthUniformName = GetDefaultParameterName( DefaultParameters::FramebufferIsDepth );
		m_IsDepth = AddBoolParameterToMaterial( IsDepthUniformName, IsDepthUniformName, False );

		SaveUniformsLocation();

		SetNeedLights( False );

		SetName( std::string( "FramebufferMaterial_" ) + std::to_string( GetResourceID() ) );
	}
	ShaderParameterTexture& FramebufferMaterial::GetTexture()
	{
		return *m_Texture;
	}
	const ShaderParameterTexture& FramebufferMaterial::GetTexture() const
	{
		return *m_Texture;
	}
	ShaderParameterBool& FramebufferMaterial::GetIsDepth()
	{
		return *m_IsDepth;
	}
	const ShaderParameterBool& FramebufferMaterial::GetIsDepth() const
	{
		return *m_IsDepth;
	}
} // ae

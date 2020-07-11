#include "PenetrationPass.h"

PenetrationPass::PenetrationPass( Uint32 _TextureSize, ae::Texture& _HeightMap, ae::Texture& _DepthMap ) :
	m_FBO( _TextureSize, _TextureSize, ae::FramebufferAttachement( ae::FramebufferAttachement::Type::Color_0, ae::TexturePixelFormat::RGBA_I32 ) ),
	m_Shader( "../../../Data/Projects/Snow/PenetrationVertex.glsl", "../../../Data/Projects/Snow/PenetrationFragment.glsl" ),
	m_Material( m_Shader )
{
	m_FBO.GetAttachementTexture()->SetName( "Penetration Texture" );

	m_Shader.SetName( "Penetration Shader" );

	m_Material.SetName( "Penetration Material" );
	m_Material.AddTextureParameterToMaterial( "HeightMap", "HeightMap", &_HeightMap );
	m_Material.AddTextureParameterToMaterial( "DepthTexture", "DepthTexture", &_DepthMap );
	m_Material.SetNeedLights( False );
	m_Material.SetNeedCamera( False );

	m_Quad.SetName( "Penetration Quad" );
	m_Quad.SetMaterial( m_Material );
}

void PenetrationPass::Run()
{
	m_FBO.Bind();
	m_FBO.Clear();
	m_FBO.Draw( m_Quad );
	m_FBO.Unbind();
}

ae::Texture& PenetrationPass::GetPenetrationTexture()
{
	return *m_FBO.GetAttachementTexture();
}

void PenetrationPass::Resize( Uint32 _TextureSize )
{
	m_FBO.Resize( _TextureSize, _TextureSize );
}

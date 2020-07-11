#include "DepthPass.h"

#include "Scene.h"
#include "SnowPlane.h"

DepthPass::DepthPass( Uint32 _TextureSize, const SnowPlane& _Ground ) :
	m_FBO( _TextureSize, _TextureSize, ae::Framebuffer::AttachementPreset::Depth_Float ),
	m_Shader( "../../../Data/Projects/Snow/DepthVertex.glsl", "../../../Data/Projects/Snow/DepthFragment.glsl" ),
	m_Material( m_Shader )
{
	m_Camera.SetName( "Below Camera" );
	m_Camera.SetRotation( ae::Math::DegToRad_Const( 89.999f ), 0.0f, 0.0f );
	m_Camera.SetNear( 0.00f );
	m_Camera.SetFar( 1.0f );
	UpdateCamera( _Ground );

	m_FBO.GetAttachementTexture( ae::FramebufferAttachement::Type::Depth )->SetName( "Depth Texture" );
	m_Shader.SetName( "Depth Shader" );
	m_Material.SetName( "Depth Material" );
	m_Material.SetNeedLights( False );
}

void DepthPass::Run( Scene& _Scene )
{
	m_FBO.Bind();
	m_FBO.Clear();
	_Scene.RenderDepthPass( m_FBO, m_Material, m_Camera );
	m_FBO.Unbind();
}

ae::Texture& DepthPass::GetDepthTexture()
{
	return *m_FBO.GetAttachementTexture( ae::FramebufferAttachement::Type::Depth );
}

float DepthPass::GetCameraNear() const
{
	return m_Camera.GetNear();
}

float DepthPass::GetCameraFar() const
{
	return m_Camera.GetFar();
}

void DepthPass::UpdateCamera( const SnowPlane& _Ground )
{
	const float HalfSize = _Ground.GetSize() * 0.5f;

	m_Camera.SetViewport( ae::FloatRect( -HalfSize, HalfSize, HalfSize, -HalfSize ) );
	m_Camera.SetPosition( _Ground.GetPosition() );
}

void DepthPass::Resize( Uint32 _TextureSize )
{
	m_FBO.Resize( _TextureSize, _TextureSize );
}

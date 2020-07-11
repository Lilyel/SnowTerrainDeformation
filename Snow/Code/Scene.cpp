#include "Scene.h"
#include "SnowPlane.h"

#include <API/Code/Graphics/Image/Image.h>
#include <API/Code/Aero/Aero.h>

Scene::Scene() :
	m_Ball( 0.1f, 50, 50 ),
	m_Lantern( "../../../Data/Projects/Snow/Lantern/Lantern.ply" ),
	m_MooMoo( "../../../Data/Projects/Snow/MooMoo/spot_triangulated.obj" ),
	m_MooMooTexture( "../../../Data/Projects/Snow/MooMoo/spot_texture.png" ),
	m_FenceBack( "../../../Data/Projects/Snow/Fence/Fence.ply" ),
	m_FenceLeft( "../../../Data/Projects/Snow/Fence/Fence.ply" ),
	m_LeftBoot( "../../../Data/Projects/Snow/Boots/LeftBoot.obj" ),
	m_RightBoot( "../../../Data/Projects/Snow/Boots/RightBoot.obj" ),

	m_BootsTrajectoryLeft( { { 0.8f, 0.27f, 0.7f }, { 0.6f, 0.34f, 0.7f }, { 0.4f, 0.27f, 0.7f }, { 0.2f, 0.34f, 0.7f }, { 0.0f, 0.27f, 0.7f }, { -0.2f, 0.34f, 0.7f }, { -0.4f, 0.27f, 0.7f }, { -0.6f, 0.34f, 0.7f }, { -0.8f, 0.27f, 0.7f } },
						   { { 0.0f, 0.0f, 0.0f }, { -0.4f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { -0.4f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { -0.4f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { -0.4f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } ),
	m_BootsTrajectoryRight( { { 0.8f, 0.34f, 0.7f }, { 0.6f, 0.27f, 0.7f }, { 0.4f, 0.34f, 0.7f }, { 0.2f, 0.27f, 0.7f }, { 0.0f, 0.34f, 0.7f }, { -0.2f, 0.27f, 0.7f }, { -0.4f, 0.34f, 0.7f }, { -0.6f, 0.27f, 0.7f }, { -0.8f, 0.34f, 0.7f } },
							{ { -0.4f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { -0.4f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { -0.4f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { -0.4f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { -0.4f, 0.0f, 0.0f } } ),
	m_BootsAnimTime( 0.0f ),
	m_BootsAnimTotalTime( 10.0f )
{
	m_ObjectsMat.SetName( "Objects Mat" );
	m_ObjectsMat.GetRoughness().SetValue( 1.0f );
	m_ObjectsMat.GetApplyGammaCorrection().SetValue( False );
	m_ObjectsMat.GetAmbientOcclusion().SetValue( 1.0f );
	m_ObjectsMat.GetAmbientStrength().SetValue( 0.015f );


	m_Ball.SetName( "Ball" );
	m_Ball.SetMaterial( m_ObjectsMat );
	m_Ball.SetPosition( 0.0f, 0.32f, 0.0f );
	m_Ball.SetBlendMode( ae::BlendMode::BlendNone );

	m_Lantern.SetName( "Lantern" );
	m_Lantern.SetMaterial( m_ObjectsMat );
	m_Lantern.SetPosition( -0.8f, 0.2f, -0.8f );
	m_Lantern.SetScale( 0.4f, 0.4f, 0.4f );
	m_Lantern.SetBlendMode( ae::BlendMode::BlendNone );

	m_MooMoo.SetName( "Moo Moo" );
	m_MooMoo.SetPosition( -0.55f, 0.42f, -0.7f );
	m_MooMoo.SetRotation( 0.0f, ae::Math::Pi(), 0.0f );
	m_MooMoo.Scale( 0.2f, 0.2f, 0.2f );
	m_MooMoo.SetBlendMode( ae::BlendMode::BlendNone );
	m_MooMoo.GetMaterial().GetParameter<ae::ShaderParameterTextureBool>( ae::Material::DefaultParameters::DiffuseTexture )->SetTexture( &m_MooMooTexture );

	m_FenceBack.SetName( "Fence Back" );
	m_FenceBack.SetPosition( 0.0f, 0.2f, -0.8f );
	m_FenceBack.SetScale( 0.4f, 0.4f, 0.4f );
	m_FenceBack.SetMaterial( m_ObjectsMat );
	m_FenceBack.SetBlendMode( ae::BlendMode::BlendNone );

	m_FenceLeft.SetName( "Fence Left" );
	m_FenceLeft.SetPosition( -0.8f, 0.2f, 0.0f );
	m_FenceLeft.SetRotation( 0.0f, ae::Math::PiDivBy2(), 0.0f );
	m_FenceLeft.SetScale( 0.4f, 0.4f, 0.4f );
	m_FenceLeft.SetMaterial( m_ObjectsMat );
	m_FenceLeft.SetBlendMode( ae::BlendMode::BlendNone );


	m_LeftBoot.SetName( "Left Boot" );
	m_LeftBoot.SetScale( 0.05f, 0.05f, 0.05f );
	m_LeftBoot.SetPosition( 0.8f, 0.29f, 0.8f );
	m_LeftBoot.SetBlendMode( ae::BlendMode::BlendNone );

	m_RightBoot.SetName( "Right Boot" );
	m_RightBoot.SetScale( 0.05f, 0.05f, 0.05f );
	m_RightBoot.SetPosition( 0.8f, 0.29f, 0.8f );
	m_RightBoot.SetBlendMode( ae::BlendMode::BlendNone );


	m_LanternLight.SetName( "Lantern Light" );
	m_LanternLight.SetRadius( 1.5f );
	m_LanternLight.SetIntensity( 1.5f );
	m_LanternLight.SetColor( ae::Color( 0.922f, 0.870f, 0.483f ) );

	m_AmbientLight.SetName( "Ambient Light" );
	m_AmbientLight.SetRotation( ae::Math::DegToRad_Const( 130.0f ), 0.0f, 0.0f );
	m_AmbientLight.SetIntensity( 0.8f );
	m_AmbientLight.SetColor( ae::Color( 0.8f, 0.619f, 0.662f ) );
}

void Scene::RenderDepthPass( ae::Renderer& _Renderer, const ae::Material& _DepthMaterial, ae::Camera& _Camera )
{
	_Renderer.Draw( m_Ball, _DepthMaterial, &_Camera );
	_Renderer.Draw( m_Lantern, _DepthMaterial, &_Camera );
	_Renderer.Draw( m_MooMoo, _DepthMaterial, &_Camera );
	_Renderer.Draw( m_FenceBack, _DepthMaterial, &_Camera );
	_Renderer.Draw( m_FenceLeft, _DepthMaterial, &_Camera );

	_Renderer.Draw( m_LeftBoot, _DepthMaterial, &_Camera );
	_Renderer.Draw( m_RightBoot, _DepthMaterial, &_Camera );
}

void Scene::RenderColorPass( ae::Renderer& _Renderer )
{
	if( m_LanternLight.IsEnabled() )
	{
		m_LanternLight.SetPosition( m_Lantern.GetPosition() + ae::Vector3( 0.0f, 0.7f, 0.0f ) );
		m_LanternLight.SetEnabled( False );
		_Renderer.Draw( m_Lantern );
		m_LanternLight.SetEnabled( True );
	}
	else
		_Renderer.Draw( m_Lantern );


	_Renderer.Draw( m_Ball );
	_Renderer.Draw( m_MooMoo );
	_Renderer.Draw( m_FenceBack );
	_Renderer.Draw( m_FenceLeft );

	_Renderer.Draw( m_LeftBoot );
	_Renderer.Draw( m_RightBoot );

}

void Scene::UpdateBootsAnim()
{
	m_BootsAnimTime += Aero.GetDeltaTime();
	m_BootsAnimTime = ae::Math::Modulo( m_BootsAnimTime, m_BootsAnimTotalTime );

	float InterpParam = ae::Math::Remap( m_BootsAnimTime, 0.0f, m_BootsAnimTotalTime, m_BootsTrajectoryLeft.GetTimeMin(), m_BootsTrajectoryLeft.GetTimeMax() );

	m_LeftBoot.SetPosition( m_BootsTrajectoryLeft.GetPointAtParam( InterpParam ) );
	m_RightBoot.SetPosition( m_BootsTrajectoryRight.GetPointAtParam( InterpParam ) );
}

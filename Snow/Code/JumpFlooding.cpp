#include "JumpFlooding.h"

#include <API/Code/Graphics/Shader/ShaderParameter/ShaderParameterInt.h>
#include <API/Code/Graphics/Shader/ShaderParameter/ShaderParameterFloat.h>
#include <API/Code/Graphics/Shader/ShaderParameter/ShaderParameterTexture.h>
#include <API/Code/Maths/Functions/MathsFunctions.h>
#include <API/Code/Aero/Aero.h>

#include <API/Code/UI/Dependencies/IncludeImGui.h>

JumpFlooding::JumpFlooding( Uint32 _TextureSize, ae::Texture& _PenetrationTexture ) :
	m_InitShader( "../../../Data/Projects/Snow/FloodingVertex.glsl", "../../../Data/Projects/Snow/FloodingInitFragment.glsl" ),
	m_FloodingShader( "../../../Data/Projects/Snow/FloodingVertex.glsl", "../../../Data/Projects/Snow/FloodingFragment.glsl" ),
	m_FloodingTextureParameter( nullptr ),
	m_PingPongFBO{ new ae::Framebuffer( _TextureSize, _TextureSize, ae::FramebufferAttachement( ae::FramebufferAttachement::Type::Color_0, ae::TexturePixelFormat::RGBA_I32 ) ),
				new ae::Framebuffer( _TextureSize, _TextureSize, ae::FramebufferAttachement( ae::FramebufferAttachement::Type::Color_0, ae::TexturePixelFormat::RGBA_I32 ) ) },
	m_FullscreenSprite( *m_PingPongFBO[0] ),
	m_MaxFloodingRange( _TextureSize ),
	m_TextureSize( _TextureSize ),
	m_CurrentPingPongIndex( 0 )
{
	m_PingPongFBO[0]->GetAttachementTexture()->SetWrapMode( ae::TextureWrapMode::ClampToEdge );
	m_PingPongFBO[0]->GetAttachementTexture()->SetName( "Flooding Ping Texture" );
	m_PingPongFBO[1]->GetAttachementTexture()->SetWrapMode( ae::TextureWrapMode::ClampToEdge );
	m_PingPongFBO[1]->GetAttachementTexture()->SetName( "Flooding Pong Texture" );

	m_InitShader.SetName( "Flooding Initialization Shader" );

	m_InitMaterial.SetName( "Flooding Initialization Material" );
	m_InitMaterial.SetShader( m_InitShader );
	m_InitMaterial.AddTextureParameterToMaterial( "Penetration Map", "PenetrationMap", &_PenetrationTexture );
	m_InitMaterial.SetNeedLights( False );
	m_InitMaterial.SetNeedCamera( False );

	m_FloodingShader.SetName( "Flooding Shader" );

	m_FloodingMaterial.SetName( "Flooding Material" );
	m_FloodingMaterial.SetShader( m_FloodingShader );
	m_FloodingTextureParameter = m_FloodingMaterial.AddTextureParameterToMaterial( "PreviousPingPongTexture", "PreviousPingPongTexture", nullptr );
	m_FloodingRangeParameter = m_FloodingMaterial.AddIntParameterToMaterial( "Range", "Range", 0 );
	m_FloodingTimeParameter = m_FloodingMaterial.AddFloatParameterToMaterial( "Time", "Time", 0 );
	m_FloodingMaterial.SetNeedLights( False );
	m_FloodingMaterial.SetNeedCamera( False );

	m_FullscreenSprite.SetName( "Flooding Quad" );
}

JumpFlooding::~JumpFlooding()
{
	delete m_PingPongFBO[0];
	delete m_PingPongFBO[1];
}

void JumpFlooding::Run()
{
	// Initialize pinp-pong with penetraion values.

	m_FullscreenSprite.SetMaterial( m_InitMaterial );

	ae::Framebuffer* InitFBO = m_PingPongFBO[m_CurrentPingPongIndex];

	InitFBO->Bind();
	InitFBO->Clear();
	InitFBO->Draw( m_FullscreenSprite );
	InitFBO->Unbind();


	const Uint32 StepCount = ae::Math::Log2( ae::Math::Min( m_TextureSize, m_MaxFloodingRange ) );

	// Do log2(n) ping pong, n being the size of the texture.

	m_FullscreenSprite.SetMaterial( m_FloodingMaterial );

	Uint32 DivFactor = 2;

	for( Uint32 s = 0; s < StepCount; s++ )
	{
		m_CurrentPingPongIndex ^= 1;

		Uint32 StepRange = m_TextureSize / DivFactor;
		Uint32 UniformTexture = m_CurrentPingPongIndex ^ 1;

		m_FloodingRangeParameter->SetValue( StepRange );
		m_FloodingTextureParameter->SetValue( m_PingPongFBO[UniformTexture]->GetAttachementTexture() );
		m_FloodingTimeParameter->SetValue( Aero.GetLifeTime() );


		ae::Framebuffer* TargetFBO = m_PingPongFBO[m_CurrentPingPongIndex];

		TargetFBO->Bind();
		TargetFBO->Draw( m_FullscreenSprite );
		TargetFBO->Unbind();

		DivFactor *= 2;
	}
}

ae::Texture& JumpFlooding::GetDistanceTexture()
{
	return *m_PingPongFBO[m_CurrentPingPongIndex]->GetAttachementTexture();
}

void JumpFlooding::Resize( Uint32 _TextureSize )
{
	m_PingPongFBO[0]->Resize( _TextureSize, _TextureSize );
	m_PingPongFBO[0]->Bind();
	m_PingPongFBO[0]->Clear();
	m_PingPongFBO[0]->Unbind();

	m_PingPongFBO[1]->Resize( _TextureSize, _TextureSize );
	m_PingPongFBO[1]->Bind();
	m_PingPongFBO[1]->Clear();
	m_PingPongFBO[1]->Unbind();


	if( m_MaxFloodingRange == m_TextureSize )
		m_MaxFloodingRange = _TextureSize;

	m_TextureSize = _TextureSize;	
}

void JumpFlooding::ToEditor()
{
	ImGui::Text( "Flooding" );

	if( ImGui::BeginCombo( "Max Flooding Range", std::to_string( m_MaxFloodingRange ).c_str() ) )
	{
		Uint32 Sizes[9] = { 16, 32, 64, 128, 256, 512, 1024, 2048, 4096 };

		for( Uint32 s = 0u; s < 9u; s++ )
		{
			Bool IsSelected = Sizes[s] == m_MaxFloodingRange;

			if( ImGui::Selectable( std::to_string( Sizes[s] ).c_str(), &IsSelected ) )
			{
				if( IsSelected )
				{
					m_MaxFloodingRange = Sizes[s];
					ImGui::SetItemDefaultFocus();
				}
			}
		}

		ImGui::EndCombo();
	}

	ImGui::Separator();
}

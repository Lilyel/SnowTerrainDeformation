#include "SnowPlane.h"

SnowPlane::SnowPlane( ae::Texture& _HeightMap, ae::Texture& _NormalMap, float _Size, Uint32 _SubdivisionWidth, Uint32 _SubdivisionHeight ) :
	ae::PlaneMesh( _Size, _SubdivisionWidth, _SubdivisionHeight ),
	m_Shader( "../../../Data/Projects/Snow/SnowVertex.glsl", "../../../Data/Projects/Snow/SnowFragment.glsl", "",
			  "../../../Data/Projects/Snow/SnowControl.glsl", "../../../Data/Projects/Snow/SnowEvaluation.glsl" )
{
	SetName( "Ground" );
	m_Shader.SetName( "Ground Shader" );

	ae::Material* SnowMat = new ae::Material( m_Shader );
	SnowMat->SetName( "Ground Material" );
	SnowMat->SetIsInstance( True );
	SnowMat->AddTextureParameterToMaterial( "HeightMap", "HeightMap", &_HeightMap );
	SnowMat->AddTextureParameterToMaterial( "NormalMap", "NormalMap", &_NormalMap );
	SnowMat->AddColorParameterToMaterial( "SnowColor", "SnowColor", ae::Color::White );
	SnowMat->AddColorParameterToMaterial( "SnowShadowColor", "SnowShadowColor", ae::Color( 0.2f, 0.2f, 0.3f ) );
	SnowMat->AddColorParameterToMaterial( "SnowRimColor", "SnowRimColor", ae::Color( 0.75f, 0.75f, 1.0f ) );
	SnowMat->AddFloatParameterToMaterial( "SnowRimPower", "SnowRimPower", 10.0f );
	SnowMat->AddFloatParameterToMaterial( "SnowRimStrength", "SnowRimStrength", 0.0f, 0.0f, 1.0 );
	SnowMat->AddColorParameterToMaterial( "SnowOceanColor", "SnowOceanColor", ae::Color::White );
	SnowMat->AddFloatParameterToMaterial( "SnowOceanSpecularPower", "SnowOceanSpecularPower", 100.0f, 0.0f );
	SnowMat->AddFloatParameterToMaterial( "SnowOceanSpecularStrength", "SnowOceanSpecularStrength", 0.1f, 0.0f, 1.0f );
	SnowMat->AddColorParameterToMaterial( "SnowGlitterColor", "SnowGlitterColor", ae::Color( 7.0f, 7.0f, 7.0f ) );
	SnowMat->AddFloatParameterToMaterial( "SnowGlitterThreshold", "SnowGlitterThreshold", 0.75f, 0.0f, 1.0f );
	SnowMat->AddFloatParameterToMaterial( "SnowGlitterFrequency", "SnowGlitterFrequency", 200.0f, 0.0f );
	SnowMat->AddFloatParameterToMaterial( "SnowGlitterScintillationSpeed", "SnowGlitterScintillationSpeed", 50.0f );

	SetMaterial( *SnowMat );


	SetBlendMode( ae::BlendMode::BlendNone );
	SetPrimitiveType( ae::PrimitiveType::Patches );
}

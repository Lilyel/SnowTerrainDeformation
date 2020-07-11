#version 330 core

out vec4 Color;

uniform vec3 CameraPosition;

in ShaderData
{
	vec3 Position;
	vec4 Color;
	vec2 UV;
	vec3 Normal;	
	vec4 PosLightSpace;	
} VertexIn;

#include "PointLight.glsl"
#define MAX_POINT_LIGHTS_COUNT 20
uniform int PointLightsCount;
uniform PointLight PointLights[MAX_POINT_LIGHTS_COUNT];


#include "SpotLight.glsl"
#define MAX_SPOT_LIGHTS_COUNT 10
uniform int SpotLightsCount;
uniform SpotLight SpotLights[MAX_SPOT_LIGHTS_COUNT];

#include "DirectionalLight.glsl"
#define MAX_DIRECTIONAL_LIGHTS_COUNT 3
uniform int DirectionalLightsCount;
uniform DirectionalLight DirectionalLights[MAX_DIRECTIONAL_LIGHTS_COUNT];


#include "MathConstants.glsl"
#include "PBRUniforms.glsl"
#include "PBRData.glsl"
#include "GammaCorrection.glsl"
#include "CookTorranceBRDF.glsl"
#include "TangentNormalToWorld.glsl"

#include "ShadowCalculation.glsl"

vec3 ProcessPointLight( in PBRData _PBRData, in vec3 _ViewDirection, in int _LightIndex )
{
	vec3 LightDirection = GetPointLightDirection( PointLights[_LightIndex], VertexIn.Position );	
	vec3 Radiance = GetPointLightRadiance( PointLights[_LightIndex], _ViewDirection, VertexIn.Position );

	return CookTorranceBRDF( _PBRData, _ViewDirection, LightDirection, Radiance );
}

vec3 ProcessSpotLight( in PBRData _PBRData, in vec3 _ViewDirection, in int _LightIndex )
{
	vec3 LightDirection = GetSpotLightDirection( SpotLights[_LightIndex], VertexIn.Position );	
	vec3 Radiance = GetSpotLightRadiance( SpotLights[_LightIndex], _ViewDirection, VertexIn.Position );

	return CookTorranceBRDF( _PBRData, _ViewDirection, LightDirection, Radiance );
}

vec3 ProcessDirectionalLight( in PBRData _PBRData, in vec3 _ViewDirection, in int _LightIndex )
{
	vec3 LightDirection = GetDirectionalLightDirection( DirectionalLights[_LightIndex] );	
	vec3 Radiance = GetDirectionalLightRadiance( DirectionalLights[_LightIndex] );

	return CookTorranceBRDF( _PBRData, _ViewDirection, LightDirection, Radiance );
}



void main()
{
	// Material parameters.
	PBRData Params;
	vec4 RawBaseColor =  UseBaseColorTexture ? texture( BaseColorTexture, VertexIn.UV ) : BaseColor;
	Params.Albedo = UseBaseColorTexture ? sRGBToLinear( RawBaseColor.rgb ) : RawBaseColor.rgb;
	Params.Albedo *= VertexIn.Color.rgb;
	Params.Opacity = RawBaseColor.a;
	Params.EmissiveColor = UseEmissionColorTexture ? texture( EmissionColorTexture, VertexIn.UV ).rgb : EmissionColor.rgb;
	Params.Metalness = UseMetalnessTexture ? texture( MetalnessTexture, VertexIn.UV ).r : Metalness;
	Params.Roughness = UseRoughnessTexture ? texture( RoughnessTexture, VertexIn.UV ).r : Roughness;
	Params.AmbientOcclusion = UseAmbientOcclusionTexture ? texture( AmbientOcclusionTexture, VertexIn.UV ).r : AmbientOcclusion;

	// Need to retrieve the vertex normal to get texture normal in tangent space.
	Params.Normal = normalize( VertexIn.Normal );
	if( UseNormalCameraTexture )
	{
		vec3 TangentNormal = texture( NormalCameraTexture, VertexIn.UV ).xyz;
		Params.Normal = TangentNormalToWorld( TangentNormal, Params.Normal, VertexIn.Position, VertexIn.UV );
	}

	// For dielectric materials we assume 0.04 is an good value for all of them (they never really go above ~0.10 except for some exceptions)
	Params.BaseReflectivity = vec3( 0.04 );
	// Take albedo for metallic materials.
	Params.BaseReflectivity = mix( Params.BaseReflectivity, Params.Albedo, Params.Metalness );

	vec3 ViewDirection = normalize( CameraPosition - VertexIn.Position );

    vec3 Lo = vec3( 0.0 );
    
    for( int Index = 0; Index < PointLightsCount; Index++ )
        Lo += ProcessPointLight( Params, ViewDirection, Index );

	for( int Index = 0; Index < SpotLightsCount; Index++ )
        Lo += ProcessSpotLight( Params, ViewDirection, Index );

	for( int Index = 0; Index < DirectionalLightsCount; Index++ )
        Lo += ProcessDirectionalLight( Params, ViewDirection, Index );


	// Ambient color.
	vec3 Ambient = vec3( 0.0 );
	if( UseIBL )
	{
		Params.Irradiance = texture( IrradianceMap, Params.Normal ).rgb;

		vec3 R = reflect( -ViewDirection, Params.Normal );
		Params.Radiance = textureLod( RadianceMap, R, Params.Roughness * float( RadianceMaxLod ) ).rgb;

		Ambient = IBLCookTorranceBRDF( Params, ViewDirection );
	}
	else
		Ambient = vec3( AmbientStrength ) * Params.Albedo * Params.AmbientOcclusion;


	// Shadowing.
	float Shadow = ShadowCalculation( VertexIn.PosLightSpace, VertexIn.Normal, VertexIn.Position, CameraPosition );

	vec3 LinearColor = Ambient + ( Lo * ( 1.0 - Shadow ) );

	Color.rgb = ApplyGammaCorrection ? LinearTosRGB( LinearColor ) : LinearColor;
	Color.a = Params.Opacity;
}
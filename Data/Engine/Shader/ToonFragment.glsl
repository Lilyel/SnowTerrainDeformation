#version 330 core

// https://roystan.net/articles/toon-shader.html

out vec4 Color;

uniform vec4 DiffuseColor;
uniform sampler2D DiffuseTexture;
uniform bool UseDiffuseTexture;

uniform vec4 SpecularColor;	
uniform sampler2D SpecularTexture;
uniform bool UseSpecularTexture;

uniform float Shininess;
uniform sampler2D ShininessTexture;
uniform bool UseShininessTexture;

uniform sampler2D NormalTexture;
uniform bool UseNormalTexture;

uniform vec4 AmbientColor;
uniform sampler2D AmbientTexture;
uniform bool UseAmbientTexture;
uniform float AmbientStrength;

uniform vec4 RimColor;
uniform float RimSize;
uniform float RimThreshold;

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

#include "GammaCorrection.glsl"
#include "TangentNormalToWorld.glsl"

#include "ShadowCalculation.glsl"

struct ProcessParams
{
	vec3 DiffuseColor;
	vec3 SpecularColor;	
	float Shininess;
	vec3 Normal;
	float Shadow;
};

vec3 ToonRadiance(in ProcessParams _Data, in vec3 _ViewDirection, in vec3 _LightDirection, in vec3 _LightRadiance )
{
    float NdotL = dot( _Data.Normal, _LightDirection );
    float LightIntensity = smoothstep( 0.0, 0.01, NdotL * _Data.Shadow );	

	// Blinn-Phong specular intensity.
    vec3 ReflectionDir = reflect( -_LightDirection, _Data.Normal );
    float SpecAngle = max( dot( _ViewDirection, ReflectionDir ), 0.0 );
    float SpecPower = pow( SpecAngle * LightIntensity, _Data.Shininess ); 


    // Raw specular color.
    vec3 SpecularColor = _LightRadiance * _Data.SpecularColor;


    // Toon effect on light color.
    vec3 ToonedLight = _LightRadiance * LightIntensity;

    // Toon effect on specular.
    float SpecularIntensity = smoothstep( 0.005, 0.01, SpecPower );
    vec3 ToonedSpecular = SpecularColor * SpecularIntensity;

    // Rim lighting.
    float RimDot = 1.0 - dot( _ViewDirection, _Data.Normal );
    float RimIntensity = RimDot * pow( NdotL, RimThreshold );
    RimIntensity = smoothstep( RimSize - 0.01, RimSize + 0.01, 1.0 - RimIntensity );
    vec3 Rim = RimColor.rgb * RimIntensity;


    // Sum all toon effects.
    return ToonedLight + ToonedSpecular + Rim;
}

vec3 ProcessPointLight( in ProcessParams _Data, in vec3 _ViewDirection, in int _LightIndex )
{
	vec3 LightDirection = GetPointLightDirection( PointLights[_LightIndex], VertexIn.Position );	
	vec3 Radiance = GetPointLightRadiance( PointLights[_LightIndex], _ViewDirection, VertexIn.Position );

	return ToonRadiance( _Data, _ViewDirection, LightDirection, Radiance );
}

vec3 ProcessSpotLight( in ProcessParams _Data, in vec3 _ViewDirection, in int _LightIndex )
{
	vec3 LightDirection = GetSpotLightDirection( SpotLights[_LightIndex], VertexIn.Position );	
	vec3 Radiance = GetSpotLightRadiance( SpotLights[_LightIndex], _ViewDirection, VertexIn.Position );

	return ToonRadiance( _Data, _ViewDirection, LightDirection, Radiance );
}

vec3 ProcessDirectionalLight( in ProcessParams _Data, in vec3 _ViewDirection, in int _LightIndex )
{
	vec3 LightDirection = GetDirectionalLightDirection( DirectionalLights[_LightIndex] );	
	vec3 Radiance = GetDirectionalLightRadiance( DirectionalLights[_LightIndex] );

	return ToonRadiance( _Data, _ViewDirection, LightDirection, Radiance );
}


void main()
{
    vec3 FragAmbientColor = UseAmbientTexture ? sRGBToLinear( texture( AmbientTexture, VertexIn.UV ).rgb ) : AmbientColor.rgb;
	vec3 AmbientColor = VertexIn.Color.rgb * FragAmbientColor * AmbientStrength;

	// Material parameters.
	ProcessParams Params;
	vec4 TextureDiffuseColor = texture( DiffuseTexture, VertexIn.UV );
	Params.DiffuseColor = UseDiffuseTexture ? sRGBToLinear( TextureDiffuseColor.rgb ) : DiffuseColor.rgb;
	float Opacity =  UseDiffuseTexture ? TextureDiffuseColor.a : DiffuseColor.a;
	Params.SpecularColor = UseSpecularTexture ? sRGBToLinear( texture( DiffuseTexture, VertexIn.UV ).rgb ) : SpecularColor.rgb;
	Params.Shininess = UseShininessTexture ? sRGBToLinear( texture( ShininessTexture, VertexIn.UV ).rgb ).r : Shininess;


	// Need to retrieve the vertex normal to get texture normal in tangent space.
	Params.Normal = normalize( VertexIn.Normal );
	if( UseNormalTexture )
	{
        vec3 TangentNormal = texture( NormalTexture, VertexIn.UV ).xyz;
		Params.Normal = TangentNormalToWorld( TangentNormal, Params.Normal, VertexIn.Position, VertexIn.UV );
    }

	// Shadowing.
	Params.Shadow = 1.0 - ShadowCalculation( VertexIn.PosLightSpace, VertexIn.Normal, VertexIn.Position, CameraPosition );
	
	vec3 ViewDirection = normalize( CameraPosition - VertexIn.Position );

    vec3 Lo = vec3( 0.0 );
    
    for( int Index = 0; Index < PointLightsCount; Index++ )
        Lo += ProcessPointLight( Params, ViewDirection, Index );

	for( int Index = 0; Index < SpotLightsCount; Index++ )
        Lo += ProcessSpotLight( Params, ViewDirection, Index );

	for( int Index = 0; Index < DirectionalLightsCount; Index++ )
        Lo += ProcessDirectionalLight( Params, ViewDirection, Index );


	

    Color.rgb = Params.DiffuseColor * ( AmbientColor + Lo );

	Color.rgb = LinearTosRGB( Color.rgb );
	Color.a = Opacity;
}

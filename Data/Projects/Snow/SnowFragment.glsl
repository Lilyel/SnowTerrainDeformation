#version 450 core

out vec4 Color;

uniform vec3 CameraPosition;

in ShaderData
{
	vec3 Position;
	vec2 UV;
} VertexIn;

#include "../../Engine/Shader/PointLight.glsl"
#define MAX_POINT_LIGHTS_COUNT 20
uniform int PointLightsCount;
uniform PointLight PointLights[MAX_POINT_LIGHTS_COUNT];


#include "../../Engine/Shader/SpotLight.glsl"
#define MAX_SPOT_LIGHTS_COUNT 10
uniform int SpotLightsCount;
uniform SpotLight SpotLights[MAX_SPOT_LIGHTS_COUNT];

#include "../../Engine/Shader/DirectionalLight.glsl"
#define MAX_DIRECTIONAL_LIGHTS_COUNT 3
uniform int DirectionalLightsCount;
uniform DirectionalLight DirectionalLights[MAX_DIRECTIONAL_LIGHTS_COUNT];

#include "../../Engine/Shader/GammaCorrection.glsl"
#include "../../Engine/Shader/TangentNormalToWorld.glsl"

#include "SnowParameters.glsl"

uniform vec4 SnowColor;
uniform vec4 SnowShadowColor;
uniform vec4 SnowRimColor;
uniform float SnowRimPower;
uniform float SnowRimStrength;
uniform vec4 SnowOceanColor;
uniform float SnowOceanSpecularPower;
uniform float SnowOceanSpecularStrength;
uniform vec4 SnowGlitterColor;
uniform float SnowGlitterThreshold;
uniform float SnowGlitterFrequency;
uniform float SnowGlitterScintillationSpeed;

uniform sampler2D NormalMap;


#include "Simplex2DNoise.glsl"
float SimplexFractalNoise( ivec2 _Offset, float Frequency )
{
	vec2 UV = VertexIn.UV * 5.0 + vec2( _Offset );
	vec2 Seed = vec2( NoiseSeed ) + vec2( VertexIn.Position.y ) + VertexIn.Position.xy;

	const mat2 m = mat2( 1.6,  1.2, -1.2,  1.6 );
	float Result = 0.5000 * Simplex2DNoise( Seed + UV * Frequency ); UV = m * UV;
	Result += 0.2500 * Simplex2DNoise( Seed + UV * Frequency ); UV = m * UV;
	Result += 0.1250 * Simplex2DNoise( Seed + UV * Frequency ); UV = m * UV;
	Result += 0.0625 * Simplex2DNoise( Seed + UV * Frequency ); UV = m * UV;

	return Result;
}

vec3 SimplexNormal( float Frequency )
{
	const ivec3 Offsets = ivec3(-1,0,1);

	float Left = SimplexFractalNoise( Offsets.zy, Frequency );
	float Right = SimplexFractalNoise( Offsets.zy, Frequency );
	float Down = SimplexFractalNoise( Offsets.yx, Frequency );
	float Up = SimplexFractalNoise( Offsets.yz, Frequency );
    
    vec3 Horizontal = normalize( vec3( 2.0, 0.0, Right - Left ) );
    vec3 Vertical = normalize( vec3( 0.0, 2.0, Up - Down ) );
    vec3 Normal = cross( Horizontal,Vertical ) * 0.5 + vec3( 0.5 );

	return Normal;
}

float Saturate( float _Value )
{
	return clamp( _Value, 0.0, 1.0 );
}

vec3 Saturate3( vec3 _Value )
{
	return clamp( _Value, 0.0, 1.0 );
}

// https://www.alanzucconi.com/2019/10/08/journey-sand-shader-2/
vec3 DiffuseColor( vec3 _Normal, vec3 _LightDirection )
{
	_Normal.y *= 0.3f;
	float NdotL = Saturate( 4.0 * dot( _Normal, _LightDirection ) );

	return mix( SnowShadowColor.rgb, SnowColor.rgb, NdotL );
}

// https://www.alanzucconi.com/2019/10/08/journey-sand-shader-4/
vec3 RimSpecular( vec3 _Normal, vec3 _ViewDirection )
{
	float Rim = 1.0 - Saturate( dot( _Normal, _ViewDirection ) );
	Rim = Saturate( pow( Rim, SnowRimPower ) * SnowRimStrength );
	
	return Rim * SnowRimColor.rgb;
}

// https://www.alanzucconi.com/2019/10/08/journey-sand-shader-4/
vec3 OceanSpecular( vec3 _Normal, vec3 _ViewDirection, vec3 _LightDirection )
{
	vec3 Halfway = normalize( _LightDirection + _ViewDirection );
	float NdotH = max( dot( _Normal, Halfway ), 0.0 );
	float Specular = pow( NdotH, SnowOceanSpecularPower ) * SnowOceanSpecularStrength;

	return Specular * SnowOceanColor.rgb;
}


// https://www.alanzucconi.com/2019/10/08/journey-sand-shader-5/
vec3 GlitterSpecular( vec3 _Normal, vec3 _ViewDirection, vec3 _LightDirection )
{
	float Random = Simplex2DNoise( ( VertexIn.Position.xz + NoiseSeed ) * SnowGlitterFrequency );
	if( Random < SnowGlitterThreshold )
		return vec3( 0.0 );

	vec3 R = reflect( _LightDirection, _Normal );
	float RdotV = max( dot( R, _ViewDirection ), 0.0 );

	if( RdotV > SnowGlitterThreshold )
		return vec3( 0.0 );

	float Scintillation = Saturate( sin( ( Time * Random ) * SnowGlitterScintillationSpeed ) );

	return ( 1.0 - RdotV ) * ( SnowGlitterColor.rgb + Scintillation );
}

void ProcessPointLight( inout vec3 _Diffuse, inout vec3 _Specular, out vec3 _Glitter, in vec3 _Normal, in vec3 _ViewDirection, in int _LightIndex )
{
	vec3 LightDirection = GetPointLightDirection( PointLights[_LightIndex], VertexIn.Position );	
	vec3 Radiance = GetPointLightRadiance( PointLights[_LightIndex], _ViewDirection, VertexIn.Position );

	_Diffuse += DiffuseColor( _Normal, LightDirection ) * Radiance;
	_Specular += OceanSpecular( _Normal, _ViewDirection, LightDirection ) * Radiance;
	_Glitter += GlitterSpecular( _Normal, _ViewDirection, LightDirection ) * Radiance;
}

void ProcessSpotLight( inout vec3 _Diffuse, inout vec3 _Specular, inout vec3 _Glitter, in vec3 _Normal, in vec3 _ViewDirection, in int _LightIndex )
{
	vec3 LightDirection = GetSpotLightDirection( SpotLights[_LightIndex], VertexIn.Position );	
	vec3 Radiance = GetSpotLightRadiance( SpotLights[_LightIndex], _ViewDirection, VertexIn.Position );

	_Diffuse += DiffuseColor( _Normal, LightDirection ) * Radiance;
	_Specular += OceanSpecular( _Normal, _ViewDirection, LightDirection ) * Radiance;
	_Glitter += GlitterSpecular( _Normal, _ViewDirection, LightDirection ) * Radiance;
}

void ProcessDirectionalLight( inout vec3 _Diffuse, inout vec3 _Specular, inout vec3 _Glitter, in vec3 _Normal, in vec3 _ViewDirection, in int _LightIndex )
{
	vec3 LightDirection = GetDirectionalLightDirection( DirectionalLights[_LightIndex] );	
	vec3 Radiance = GetDirectionalLightRadiance( DirectionalLights[_LightIndex] );

	_Diffuse += DiffuseColor( _Normal, LightDirection ) * Radiance;
	_Specular += OceanSpecular( _Normal, _ViewDirection, LightDirection ) * Radiance;
	_Glitter += GlitterSpecular( _Normal, _ViewDirection, LightDirection ) * Radiance;
}



// https://www.artstation.com/artwork/J2wBz
vec3 BlendNormals()
{
	vec3 BaseNormal = texture( NormalMap, VertexIn.UV ).xyz;

	vec3 Chunk = SimplexNormal( ChunkFrequency );
	
	vec3 Grain = SimplexNormal( GrainFrequency );

	vec3 Normal = normalize( BaseNormal + ChunkAmount * Chunk + GrainAmount * Grain );

	return Normal;
}

void main()
{	
	vec3 TangentNormal = BlendNormals();
	vec3 Normal = TangentNormalToWorld( TangentNormal, vec3( 0.0, 1.0, 0.0 ), VertexIn.Position, VertexIn.UV );

	vec3 ViewDirection = normalize( CameraPosition - VertexIn.Position );

    vec3 Diffuse = vec3( 0.0 );
	vec3 Specular = vec3( 0.0 );
	vec3 Glitter = vec3( 0.0 );
    
    for( int Index = 0; Index < PointLightsCount; Index++ )
        ProcessPointLight( Diffuse, Specular, Glitter, Normal, ViewDirection, Index );

	for( int Index = 0; Index < SpotLightsCount; Index++ )
        ProcessSpotLight( Diffuse, Specular, Glitter, Normal, ViewDirection, Index );

	for( int Index = 0; Index < DirectionalLightsCount; Index++ )
        ProcessDirectionalLight( Diffuse, Specular, Glitter, Normal, ViewDirection, Index );


	vec3 Rim = RimSpecular( Normal, ViewDirection );

	Specular = Saturate3( max( Specular, Rim ) );

	Color.rgb = Diffuse + Specular + Glitter;
	Color.a = 1.0;
}
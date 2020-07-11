#version 330 core

out vec4 Color;


#define M_PI 3.1415926535897932384626433832795

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

uniform vec3 CameraPosition;

in ShaderData
{
	vec3 Position;
	vec4 Color;
	vec2 UV;
	vec3 Normal;
	vec4 PosLightSpace;	
} VertexIn;


struct PointLight
{
	vec3 Position;
	
	vec4 Color;
	
	float Intensity;
	float Radius;
};

#define MAX_POINT_LIGHTS_COUNT 20
uniform int PointLightsCount;
uniform PointLight PointLights[MAX_POINT_LIGHTS_COUNT];

struct SpotLight
{
	vec3 Position;
	vec3 LookAt;
	float Range;
	
	vec4 Color;
	
	float Intensity;

	float InnerAngle;
	float OuterAngle;
};

#define MAX_SPOT_LIGHTS_COUNT 10
uniform int SpotLightsCount;
uniform SpotLight SpotLights[MAX_SPOT_LIGHTS_COUNT];

struct DirectionalLight
{
	vec3 Position;
	vec3 LookAt;
	
	vec4 Color;
	
	float Intensity;
};

#define MAX_DIRECTIONAL_LIGHTS_COUNT 3
uniform int DirectionalLightsCount;
uniform DirectionalLight DirectionalLights[MAX_DIRECTIONAL_LIGHTS_COUNT];



struct ProcessParams
{
	vec4 DiffuseColor;
	vec4 SpecularColor;	
	float Shininess;
	vec3 Normal;
};


#include "ShadowCalculation.glsl"


// Taken from : 
// https://learnopengl.com/code_viewer_gh.php?code=src/6.pbr/1.2.lighting_textured/1.2.pbr.fs
vec3 GetNormalFromMap( in ProcessParams _Params )
{
    vec3 tangentNormal = texture( NormalTexture, VertexIn.UV ).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(VertexIn.Position);
    vec3 Q2  = dFdy(VertexIn.Position);
    vec2 st1 = dFdx(VertexIn.UV);
    vec2 st2 = dFdy(VertexIn.UV);

    vec3 N   = normalize( VertexIn.Normal );
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

vec4 GetBlinnPhongDiffuse( in ProcessParams _Params, in vec3 _LightDirection, in vec4 _LightColor )
{
	float DiffuseFactor = max( dot( _Params.Normal, _LightDirection ), 0.0 );
	vec4 Diffuse = _LightColor * ( _Params.DiffuseColor * DiffuseFactor );

	return Diffuse;
}

vec4 GetBlinnPhongSpecular( in ProcessParams _Params, in vec3 _LightDirection, in vec3 _ViewDirection, in vec4 _LightColor )
{
	vec3 ReflectionDir = reflect( -_LightDirection, _Params.Normal );
    float SpecAngle = max( dot( _ViewDirection, ReflectionDir ), 0.0 );
    float SpecPower = pow( SpecAngle, _Params.Shininess ); 

    vec4 Specular = _LightColor * ( _Params.SpecularColor * SpecPower );

    return Specular;
}

vec4 ProcessPointLight( in ProcessParams _Params, in vec3 _ViewDirection, in int _LightIndex )
{
	vec3 ToLight = PointLights[_LightIndex].Position - VertexIn.Position;
	vec3 LightDirection = normalize( ToLight );

	// Point light attenuation
	float DistanceToLight = length( ToLight );
	float Attenuation = PointLights[_LightIndex].Intensity * pow( max( 0.0, 1.0 - ( DistanceToLight / PointLights[_LightIndex].Radius ) ), 2 );

	// Diffuse
	vec4 Diffuse = GetBlinnPhongDiffuse( _Params, LightDirection, PointLights[_LightIndex].Color );   

	// Specular Blinn Phong
    vec4 Specular = GetBlinnPhongSpecular( _Params, LightDirection, _ViewDirection, PointLights[_LightIndex].Color );

	vec4 LightResult = ( Diffuse + Specular ) * Attenuation;
	LightResult.w = 1.0;
    
	return LightResult;
}

vec4 ProcessSpotLight( in ProcessParams _Params, in vec3 _ViewDirection, in int _LightIndex )
{
	vec3 ToLight = SpotLights[_LightIndex].Position - VertexIn.Position;
	float DistanceToLight = length( ToLight );
	vec3 LightDirection = normalize( ToLight );

	float InnerCos = cos( SpotLights[_LightIndex].InnerAngle );
	float OuterCos = cos( SpotLights[_LightIndex].OuterAngle );

	float Theta = dot( LightDirection, normalize( -SpotLights[_LightIndex].LookAt ) );
	float Epsilon = InnerCos - OuterCos;
	float IntensityFactor = clamp( (Theta - OuterCos) / Epsilon, 0.0, 1.0 );

	// Spot light attenuation
	float RangeAttenuation = pow( max( 0.0, 1.0 - DistanceToLight / SpotLights[_LightIndex].Range ), 2 );
	float Attenuation = SpotLights[_LightIndex].Intensity * IntensityFactor * RangeAttenuation;

	// Diffuse
	vec4 Diffuse = GetBlinnPhongDiffuse( _Params, LightDirection, SpotLights[_LightIndex].Color );   

	// Specular Blinn Phong
    vec4 Specular = GetBlinnPhongSpecular( _Params, LightDirection, _ViewDirection, SpotLights[_LightIndex].Color );

	vec4 LightResult = ( Diffuse + Specular ) * Attenuation;
	LightResult.w = 1.0;

	return LightResult;
}

vec4 ProcessDirectionalLight( in ProcessParams _Params, in vec3 _ViewDirection, in int _LightIndex )
{
	vec3 LightDirection = normalize( -DirectionalLights[_LightIndex].LookAt );

	// Diffuse
	vec4 Diffuse = GetBlinnPhongDiffuse( _Params, LightDirection, DirectionalLights[_LightIndex].Color );   

	// Specular Blinn Phong
    vec4 Specular = GetBlinnPhongSpecular( _Params, LightDirection, _ViewDirection, DirectionalLights[_LightIndex].Color );

	vec4 LightResult = ( Diffuse + Specular ) * DirectionalLights[_LightIndex].Intensity;
	LightResult.w = 1.0;

	return LightResult;
}



void main()
{
	vec4 FragAmbientColor = UseAmbientTexture ? texture( AmbientTexture, VertexIn.UV ) : AmbientColor;
	vec4 Ambient = FragAmbientColor * AmbientStrength;

	// Material parameters.
	ProcessParams Params;
	Params.DiffuseColor = UseDiffuseTexture ? texture( DiffuseTexture, VertexIn.UV ) : DiffuseColor;
	Params.DiffuseColor *= VertexIn.Color;
	Params.SpecularColor = UseSpecularTexture ? texture( DiffuseTexture, VertexIn.UV ) : SpecularColor;
	Params.Shininess = UseShininessTexture ? texture( ShininessTexture, VertexIn.UV ).r : Shininess;


	// Need to retrieve the vertex normal to get texture normal in tangent space.
	Params.Normal = normalize( VertexIn.Normal );
	if( UseNormalTexture )
		Params.Normal = GetNormalFromMap( Params );

	
	vec3 ViewDirection = normalize( CameraPosition - VertexIn.Position );

    vec4 LightColor = vec4( 0.0, 0.0, 0.0, 1.0 );
    
    for( int Index = 0; Index < PointLightsCount; Index++ )
        LightColor += ProcessPointLight( Params, ViewDirection, Index );

	for( int Index = 0; Index < SpotLightsCount; Index++ )
        LightColor += ProcessSpotLight( Params, ViewDirection, Index );

	for( int Index = 0; Index < DirectionalLightsCount; Index++ )
        LightColor += ProcessDirectionalLight( Params, ViewDirection, Index );

	float Shadow = ShadowCalculation( VertexIn.PosLightSpace, VertexIn.Normal, VertexIn.Position, CameraPosition );

    Color.rgb = ( Ambient.rgb + LightColor.rgb * ( 1.0 - Shadow ) );
	Color.a = 1.0;
}

#include "MathConstants.glsl"

#include "PBRData.glsl"
#include "DistributionGGX.glsl"
#include "GeometrySmith.glsl"
#include "FresnelSchlick.glsl"

vec3 CookTorranceBRDF( in PBRData _PBRData, in vec3 _ViewDirection, vec3 _LightDirection, vec3 _LightRadiance )
{
	vec3 Halfway = normalize( _ViewDirection + _LightDirection );

	float NormalDistribution = DistributionGGX( _PBRData.Roughness, _PBRData.Normal, Halfway );
	float GeometryShadowing = GeometrySmith( _PBRData.Roughness, _PBRData.Normal, _ViewDirection, _LightDirection );
	vec3 FresnelReflectivity = FresnelSchlick( dot( Halfway, _ViewDirection ), _PBRData.BaseReflectivity );

	// Amount of radiance reflected.
	vec3 kS = FresnelReflectivity;
	// Amount of radiance absorbed (must respect energy conservation).
	vec3 kD = vec3( 1.0 ) - kS;
	kD *= ( 1.0 - _PBRData.Metalness );

	float NdotL = max( dot( _PBRData.Normal, _LightDirection ), 0.0 );
    float NdotV =  max( dot( _PBRData.Normal, _ViewDirection ), 0.0 );

	vec3 Numerator = NormalDistribution * FresnelReflectivity * GeometryShadowing;
	float Denominator = 4.0 * NdotV * NdotL + 0.001; // 0.001 to prevent division by 0.
	vec3 Specular = Numerator / Denominator;	

	// Radiance Lo for this light direction.
	return ( kD * _PBRData.Albedo / M_PI + Specular ) * _LightRadiance * NdotL;
}

vec3 IBLCookTorranceBRDF( in PBRData _PBRData, in vec3 _ViewDirection )
{
	float NdotV = max( dot( _PBRData.Normal, _ViewDirection ), 0.0 );

	// Amount of radiance reflected.
	vec3 kS = FresnelSchlickRoughness( NdotV, _PBRData.BaseReflectivity, _PBRData.Roughness );
	// Amount of radiance absorbed (must respect energy conservation).
	vec3 kD = vec3( 1.0 ) - kS;
	kD *= ( 1.0 - _PBRData.Metalness );

	vec2 BRDF = texture( BRDFLut, vec2( NdotV, _PBRData.Roughness ) ).rg;

	vec3 Diffuse = _PBRData.Albedo * _PBRData.Irradiance;
	vec3 Specular = _PBRData.Radiance * ( kS * BRDF.x + BRDF.y );

	return ( kD * Diffuse + Specular ) * _PBRData.AmbientOcclusion;
}
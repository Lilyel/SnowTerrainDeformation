
#include "GeometrySchlickGGX.glsl"

// Process the overshadowing factor from the camera view and from the light view using the Smith formula (combination of two SchlickGGX).
float GeometrySmith( in float _Roughness, in vec3 _Normal, vec3 _ViewDirection, vec3 _LightDirection )
{
	// Geometry obstruction from the camera view.
    float NdotV = max( dot( _Normal, _ViewDirection ), 0.0 );
    float GGXView  = GeometrySchlickGGX( NdotV, _Roughness );

	// Geometry shadowing from the light view.
    float NdotL = max( dot( _Normal, _LightDirection ), 0.0 );
    float GGXLight  = GeometrySchlickGGX( NdotL, _Roughness );
	
	// Combine the two results.
    return GGXView * GGXLight;
}

float IBLGeometrySmith( in float _Roughness, in vec3 _Normal, vec3 _ViewDirection, vec3 _LightDirection )
{
	// Geometry obstruction from the camera view.
    float NdotV = max( dot( _Normal, _ViewDirection ), 0.0 );
    float GGXView  = IBLGeometrySchlickGGX( NdotV, _Roughness );

	// Geometry shadowing from the light view.
    float NdotL = max( dot( _Normal, _LightDirection ), 0.0 );
    float GGXLight  = IBLGeometrySchlickGGX( NdotL, _Roughness );
	
	// Combine the two results.
    return GGXView * GGXLight;
}
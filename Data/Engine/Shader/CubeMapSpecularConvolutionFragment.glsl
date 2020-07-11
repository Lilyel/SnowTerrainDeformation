#version 330

// https://learnopengl.com/PBR/IBL/Specular-IBL

out vec4 Color;

in vec3 WorldPosition;

uniform samplerCube CubeMap;
uniform float Roughness;
uniform int CubeMapSideSize;

#include "ImportanceSamplingGGX.glsl"



float DistrubutionGGX( float _NdotH, float _Roughness )
{
	// Roughness for indirect lighting.
    float R = _Roughness * _Roughness;
    float R2 = R * R;
    float NdotH2 = _NdotH * _NdotH;

    float Denominator = NdotH2 * ( R2 - 1.0 ) + 1.0;
    Denominator = M_PI * Denominator * Denominator;
	
    return R2 / Denominator;
}

void main()
{
    // Hemisphere orientation.
    vec3 Normal = normalize( WorldPosition );

    // To avoid integrating all view direction, we assume that the view direction is the the normal.
    vec3 ViewDirection = Normal;


    vec3 Radiance = vec3( 0.0 );

    const uint SampleCount = 1024u;
    float TotalWeight = 0.0;

    for( uint i = 0u; i < SampleCount; i++ )
    {
        vec2 Random = Hammersley( i, SampleCount );
        vec3 Halfway = ImportanceSamplingGGX( Random, Normal, Roughness );
        vec3 LightDir = normalize( 2.0 * dot(  ViewDirection, Halfway ) * Halfway - ViewDirection );

        float NdotL = max( dot( Normal, LightDir ), 0.0 );
        if( NdotL > 0.0 )
        {
            float NdotH = max( dot( Normal, Halfway ), 0.0 );
            float HdotV = max( dot( Halfway, ViewDirection ), 0.0 );

            float D = DistrubutionGGX( NdotH, Roughness );

            float PDF = D * NdotH / ( 4.0 * HdotV ) + 0.0001;


            float saTexel = 4.0 * M_PI / ( 6.0 * float( CubeMapSideSize * CubeMapSideSize ) );
            float saSample = 1.0 / ( float( SampleCount ) * PDF + 0.0001 );

            float MipLevel = Roughness == 0.0 ? 0.0 : 0.5 * log2( saSample / saTexel );

            Radiance += textureLod( CubeMap, LightDir, MipLevel ).rgb * NdotL;
            TotalWeight += NdotL;
        }
    }
    
    Radiance = Radiance / TotalWeight;

    Color = vec4( Radiance, 1.0 );
}
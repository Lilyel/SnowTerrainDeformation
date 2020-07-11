#version 330

#include "ImportanceSamplingGGX.glsl"
#include "GeometrySmith.glsl"

in vec2 FragUV;

out vec4 Color;

void main()
{
	float NdotV = FragUV.x;
    float Roughness = FragUV.y;

    vec3 ViewDir = vec3( sqrt( 1.0 - NdotV * NdotV ), 0.0, NdotV );

    float A = 0.0;
    float B = 0.0;

    vec3 Normal = vec3( 0.0, 0.0, 1.0 );

    const uint SampleCount = 1024u;
    for( uint i = 0u; i < SampleCount; i++ )
    {
        vec2 Random = Hammersley( i, SampleCount );
        vec3 Halfway = ImportanceSamplingGGX( Random, Normal, Roughness );
        vec3 LigthDir = normalize( 2.0 * dot( ViewDir, Halfway ) * Halfway - ViewDir );

        float NdotL = max( LigthDir.z, 0.0 );
        float NdotH = max( Halfway.z, 0.0 );
        float VdotH = max( dot( ViewDir, Halfway ), 0.0 );

        if( NdotL > 0.0 )
        {
            float G = IBLGeometrySmith( Roughness, Normal, ViewDir, LigthDir );
            float G_Visible = ( G * VdotH ) / ( NdotH * NdotV );
            float Fresnel = pow( 1.0 - VdotH, 5.0 );

            A += ( 1.0 - Fresnel ) * G_Visible;
            B += Fresnel * G_Visible;
        }
    }

    A /= float( SampleCount );
    B /= float( SampleCount );

    Color = vec4( A, B, 0.0, 1.0 );
}
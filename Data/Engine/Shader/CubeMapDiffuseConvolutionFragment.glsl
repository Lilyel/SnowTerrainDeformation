#version 330

out vec4 Color;

in vec3 WorldPosition;

uniform samplerCube CubeMap;

#include "MathConstants.glsl"

void main()
{
    // Hemisphere orientation.
    vec3 Normal = normalize( WorldPosition );


    vec3 Irradiance = vec3( 0.0 );

    vec3 Up = vec3( 0.0, 1.0, 0.0 );
    vec3 Right = cross( Up, Normal );
    Up = cross( Normal, Right );

    const float SampleDelta = 0.025;
    uint SamplesCount = 0u;

    for( float Phi = 0.0; Phi < 2.0 * M_PI; Phi += SampleDelta )
    {
        for( float Theta = 0.0; Theta < 0.5 * M_PI; Theta += SampleDelta )
        {
            // Spherical position (in tangent space).
            vec3 TangentSample = vec3( sin( Theta ) * cos( Phi ), sin( Theta ) * sin( Phi ), cos( Theta ) );

            // Tangent space to world space.
            vec3 SampleDirection = TangentSample.x * Right + TangentSample.y * Up + TangentSample.z * Normal;

            Irradiance += texture( CubeMap, SampleDirection ).rgb * cos( Theta ) * sin( Theta );
            SamplesCount++;
        }
    }

    Irradiance = M_PI * Irradiance / float( SamplesCount );

    Color = vec4( Irradiance, 1.0 );
}
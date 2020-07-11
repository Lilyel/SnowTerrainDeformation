#version 450 core

layout(binding = 0, r32ui)  uniform uimage2D HeightMap;

#include "SnowParameters.glsl"
#include "Perlin2DNoise.glsl"

layout (local_size_x = 8, local_size_y = 8) in;

void main()
{
    const ivec2 CurrentCoord = ivec2(gl_GlobalInvocationID.xy);
    
    if( CurrentCoord.x >= TextureSize || CurrentCoord.y >= TextureSize )
        return;

    const vec2 UV = vec2( CurrentCoord ) / TextureSize;
    const float DuneAmount = Perlin2DNoise( IntialSeed + UV * InitialDuneFrequency ) * 0.5 + 1.0;
    const float WorldHeight = smoothstep( 0.0, 1.0, DuneAmount ) * ( InitialMaxHeight - InitialMinHeight ) + InitialMinHeight;

    const uint Height = uint( WorldHeight * HeightMapScale );

    imageStore( HeightMap, CurrentCoord, uvec4( Height ) );
}
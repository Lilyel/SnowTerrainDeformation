#version 450 core

layout(binding = 0, r32ui) readonly uniform uimage2D ToRead;
layout(binding = 1, r32ui) writeonly uniform uimage2D ToWrite;

#include "SnowParameters.glsl"

layout (local_size_x = 8, local_size_y = 8) in;

void main()
{
    const ivec2 CurrentCoord = ivec2(gl_GlobalInvocationID.xy);
    
    if( CurrentCoord.x >= TextureSize || CurrentCoord.y >= TextureSize )
        return;

    const uvec4 Height = imageLoad( ToRead, CurrentCoord );
    imageStore( ToWrite, CurrentCoord, Height );
}
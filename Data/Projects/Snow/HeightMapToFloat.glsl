#version 450 core

layout(binding = 0, r32ui) readonly uniform uimage2D IntegerHeightMap;
layout(binding = 1, r32f) uniform image2D FloatHeightMap;

#include "SnowParameters.glsl"

layout (local_size_x = 8, local_size_y = 8) in;

void main()
{
	const ivec2 CurrentCoord = ivec2(gl_GlobalInvocationID.xy);
    
    if( CurrentCoord.x >= TextureSize || CurrentCoord.y >= TextureSize )
        return;

	const float PreviousHeight = imageLoad( FloatHeightMap, CurrentCoord ).r;
	const float Height = float( imageLoad( IntegerHeightMap, CurrentCoord ).r ) / HeightMapScale;

	const float MaxDifference = tan( SlopeMaxBetweenFrame ) * PixelSize;

	const float Difference = clamp( Height - PreviousHeight, -MaxDifference, MaxDifference );

	imageStore( FloatHeightMap, CurrentCoord, vec4( PreviousHeight + Difference ) );
}
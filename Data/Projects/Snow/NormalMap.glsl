#version 450 core

layout(binding = 0, r32ui) readonly uniform uimage2D HeightMap;
layout(binding = 1, rgba32f) writeonly uniform image2D NormalMap;

#include "SnowParameters.glsl"

layout (local_size_x = 8, local_size_y = 8) in;

ivec2 ClampCoord( ivec2 _Coord )
{
    return clamp( _Coord, ivec2( 0 ), ivec2( TextureSize - 1) );
}

void main()
{
	const ivec2 CurrentCoord = ivec2( gl_GlobalInvocationID.xy );
    
    if( CurrentCoord.x >= TextureSize || CurrentCoord.y >= TextureSize )
        return;

	const ivec3 Offsets = ivec3(-1,0,1);

    const float Left = float( imageLoad( HeightMap, ClampCoord( CurrentCoord + Offsets.xy ) ).r );
    const float Right = float( imageLoad( HeightMap, ClampCoord( CurrentCoord + Offsets.zy ) ).r );
    const float Down = float( imageLoad( HeightMap, ClampCoord( CurrentCoord + Offsets.yx ) ).r );
    const float Up = float( imageLoad( HeightMap, ClampCoord( CurrentCoord + Offsets.yz ) ).r );
    
    const vec3 Horizontal = normalize( vec3( 2.0, 0.0, Right - Left ) );
    const vec3 Vertical = normalize( vec3( 0.0, 2.0, Up - Down ) );
    const vec3 Normal = cross( Horizontal,Vertical ) * 0.5 + vec3( 0.5 );

    imageStore( NormalMap, CurrentCoord, vec4( Normal, 1.0 ) );
}
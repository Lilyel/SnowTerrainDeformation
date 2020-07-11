#version 450 core

uniform isampler2D PenetrationMap;

#include "SnowParameters.glsl"

in vec2 FragUV;

out ivec4 Color;

void main()
{
	ivec4 PenetrationValue = texture( PenetrationMap, FragUV );

    int MaxDistance = int( length( uvec2( TextureSize, TextureSize ) ) * HeightMapScale );

    int Distance = 0;
    ivec2 Coord = ivec2( 0, 0 );
    
    // Penetrating : must find seeds.
    if( PenetrationValue.b == -1 )
    {
        Distance = MaxDistance;
        Coord = ivec2( -1, -1 );
    }
    // Seeds : Can receive snow, Obstacles, can't receive snow.
    else
    {
        Distance = 0;
        Coord = ivec2( gl_FragCoord.xy );
    }
    

    Color = ivec4( Coord, PenetrationValue.b, MaxDistance );
}
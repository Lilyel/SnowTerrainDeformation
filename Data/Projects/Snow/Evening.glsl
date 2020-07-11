#version 450 core

layout(binding = 0, r32ui) uniform uimage2D PingMap;

// Format : Seed position(ivec2), Type ? -1 for penetrating point ("obstacle"), -2 for close to penetrating, -3 for not penetrating ("seed"), Penetration value.
layout(binding = 1, rgba32i) readonly uniform iimage2D Penetration;

#include "SnowParameters.glsl"

layout (local_size_x = 8, local_size_y = 8) in;

void main()
{
    const ivec2 CurrentCoord = ivec2(gl_GlobalInvocationID.xy);
    
    if( CurrentCoord.x >= TextureSize || CurrentCoord.y >= TextureSize )
        return;

    const uint CurrentHeight = imageLoad( PingMap, CurrentCoord ).r;
    
    const ivec2 Neighbors[8] = ivec2[8](
        ivec2( 0, 1 ),
        ivec2( 1, 1 ),
        ivec2( 1, 0 ),
        ivec2( 1, -1 ),
        ivec2( 0, -1 ),
        ivec2( -1, -1 ),
        ivec2( -1, 0 ),
        ivec2( -1, 1 )
    );

    uint SumDifferences = 0;
    uint CountNeighbor = 0;

    ivec2 NeighborCoords[8];

    uint HighestNeighbor = 0;

    for( int n = 0; n < 8; n++ )
    {
        const ivec2 NeighborCoord = CurrentCoord + Neighbors[n];

        const int NeighborType = imageLoad( Penetration, NeighborCoord ).b;
        if( NeighborType != -3 )
            continue;

        const uint NeighborHeight = imageLoad( PingMap, NeighborCoord ).r;
        if( NeighborHeight >= CurrentHeight )
            continue;

        const uint Difference = CurrentHeight - NeighborHeight;

        const float DistanceToNeighbor = length( vec2( Neighbors[n] ) * PixelSize ) * HeightMapScale;
        const float Slope = abs( atan( float( Difference ) / DistanceToNeighbor ) );

        if( Slope < SlopeThreshold )
            continue;

        SumDifferences += Difference;

        NeighborCoords[CountNeighbor] = NeighborCoord;
        CountNeighbor++;

        HighestNeighbor = max( HighestNeighbor, NeighborHeight );
    }
    
    if( SumDifferences == 0 )
        return;

    const uint MaxMovable = CurrentHeight - HighestNeighbor;
    SumDifferences = uint( min( SumDifferences, MaxMovable ) * SnowRoughness );

    const uint ToMove = SumDifferences / max( CountNeighbor, 1 );

    imageAtomicAdd( PingMap, CurrentCoord, uint( -SumDifferences ) );

    for( uint n = 0u; n < CountNeighbor; n++ )
        imageAtomicAdd( PingMap, NeighborCoords[n], ToMove );
}
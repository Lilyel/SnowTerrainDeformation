#version 450 core


layout(binding = 0, r32ui) uniform uimage2D Target;
// Format : Seed position(ivec2), Type ? -1 for penetrating point ("obstacle"), -2 for close to penetrating, -3 for not penetrating ("seed"), Penetration value.
layout(binding = 1, rgba32i) readonly uniform iimage2D Penetration;
// Format : Seed Position(ivec2), Filled ? (2 if seed, 1 if not seed, 0 if not filled), distance to closest seed.
layout(binding = 2, rgba32i) readonly uniform iimage2D DistanceTexture;


#include "SnowParameters.glsl"

layout (local_size_x = 8, local_size_y = 8) in;

void main()
{
    const ivec2 CurrentCoord = ivec2(gl_GlobalInvocationID.xy);
    
    if( CurrentCoord.x >= TextureSize || CurrentCoord.y >= TextureSize )
        return;

    ivec4 PenetrationValue = imageLoad( Penetration, CurrentCoord );

    // Transfert material only from penetrating points.
    if( PenetrationValue.b != -1 )
        return;


    const uint CurrentPeneration = uint( PenetrationValue.a );

    const vec2 ClosestSeed = vec2( imageLoad( DistanceTexture, CurrentCoord ).rg );

    // Add the new height to the current column.
    imageAtomicAdd( Target, CurrentCoord, uint( -CurrentPeneration ) );


    float Displaced = float( CurrentPeneration ) * ( 1.0 - SnowCompression );

    const vec2 Direction = normalize( ClosestSeed - vec2( CurrentCoord ) );

    const uint Range = uint( ceil( CurrentPeneration / ( HeightMapScale / 10.0 ) ) );

    Displaced /= Range;    

    for( uint i = 0u; i < Range; i++ )
        imageAtomicAdd( Target, ivec2( ClosestSeed + Direction * i ), uint( Displaced ) );
}
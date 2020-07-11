#version 450 core

uniform isampler2D PreviousPingPongTexture;

uniform int Range;

#include "SnowParameters.glsl"

in vec2 FragUV;

out ivec4 Color;

int ManhattanDistance( ivec2 _A, ivec2 _B )
{
    return abs( _B.x - _A.x ) + abs( _B.y - _A.y );
}

int ChebyshevDistance( ivec2 _A, ivec2 _B )
{
    return max( abs( _B.x - _A.x ), abs( _B.y - _A.y ) );
}


void main()
{
	ivec4 CurrentValue = texture( PreviousPingPongTexture, FragUV );

    ivec2 CurrentCoord = ivec2( gl_FragCoord.xy );

    // Skip seeds since they store their own coordinates.
    if( CurrentValue.b != -1 )
    {
        Color = CurrentValue;
        return;
    }

    ivec2 Neighbors[8] = ivec2[8](
        ivec2( 0, Range ),
        ivec2( Range, Range ),
        ivec2( Range, 0 ),
        ivec2( Range, -Range ),
        ivec2( 0, -Range ),
        ivec2( -Range, -Range ),
        ivec2( -Range, 0 ),
        ivec2( -Range, Range )
    );

    int MinDistance = CurrentValue.a;
    ivec2 MinCoord = CurrentValue.rg;

    int RandomOffset = int( 1.0 + noise1( Time + float( Range ) ) * 4 );

    for( int n = 0; n < 8; n++ )
    {
        int NeighborID = ( RandomOffset + n ) % 8;

        ivec3 NeighborValue = texelFetch( PreviousPingPongTexture, CurrentCoord + Neighbors[NeighborID], 0 ).rgb;

        // Check only seed pixels and penetrating points (they could contain close seeds).
        if( NeighborValue.b != -2 )
        {
            int Distance = int( length( CurrentCoord - NeighborValue.rg ) * HeightMapScale );
            
            if( Distance < MinDistance )
            {
                MinDistance = Distance;
                MinCoord = NeighborValue.rg;
            }
        }
    }

    // Write the closest seed found.
    Color = ivec4( MinCoord, CurrentValue.b, MinDistance );
}
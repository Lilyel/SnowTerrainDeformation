#version 330 core

in vec2 FragUV;

out vec4 Color;

uniform sampler2D Texture;
uniform bool IsHorizontal;
uniform float Coefs[5] = float[5]( 0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216 );

void main()
{
	vec2 TexelSize = 1.0 / vec2( textureSize( Texture, 0 ) );
    vec2 Offset = vec2( TexelSize.x * float( IsHorizontal ), TexelSize.y * float( !IsHorizontal ) );

    // We want only once the center, so do it outisde of the loop.
    vec3 Result = texture( Texture, FragUV ).rgb * Coefs[0];

    // Add the negative and positive neighbors.
    for( uint i = 1u; i < 5u; i++ )
    {
        vec2 NeighborOffset = Offset * i;
        Result += texture( Texture, FragUV + NeighborOffset ).rgb * Coefs[i];
        Result += texture( Texture, FragUV - NeighborOffset ).rgb * Coefs[i];
    }

    Color = vec4( Result, 1.0 );
}
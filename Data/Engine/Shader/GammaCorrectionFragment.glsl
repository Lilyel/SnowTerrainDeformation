#version 330 core

in vec2 FragUV;

out vec4 Color;

uniform sampler2D Texture;
uniform float Exposure;
uniform float Gamma;

void main()
{
    vec3 HDRColor = texture( Texture, FragUV ).rgb;

    vec3 ToneMapped = vec3( 1.0 ) - exp( -HDRColor * Exposure );

    vec3 GammaCorrected = pow( ToneMapped, vec3( 1.0 / Gamma ) );

    Color = vec4( GammaCorrected, 1.0 );
}
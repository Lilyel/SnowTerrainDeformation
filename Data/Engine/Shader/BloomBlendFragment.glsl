#version 330 core

layout (location = 0) out vec4 Color;

uniform sampler2D ColorTexture;
uniform sampler2D BloomTexture;

in vec2 FragUV;

void main()
{
    Color = vec4( texture( ColorTexture, FragUV ).rgb + texture( BloomTexture, FragUV ).rgb, 1.0 );
}

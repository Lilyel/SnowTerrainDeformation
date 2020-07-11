#version 330 core

uniform bool UseTexture;
uniform sampler2D Texture;

in vec4 FragmentColor;
in vec2 FragUV;

out vec4 Color;

void main()
{
	if( !UseTexture )
		Color = FragmentColor;

	else
		Color = FragmentColor * texture( Texture, FragUV );
}
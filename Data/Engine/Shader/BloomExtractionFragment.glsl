#version 330 core

layout (location = 0) out vec4 Color;
layout (location = 1) out vec4 BrightColor;

in vec2 FragUV;

uniform sampler2D Texture;
uniform vec3 BrightnessThreshold;

void main()
{
    Color.rgb = texture( Texture, FragUV ).rgb;
	Color.a = 1.0;	

	float Brightness = dot( Color.rgb, normalize( BrightnessThreshold ) );
	if( Brightness > 1.0 )
		BrightColor = Color;
	else
		BrightColor = vec4( 0.0, 0.0, 0.0, 1.0 );
}

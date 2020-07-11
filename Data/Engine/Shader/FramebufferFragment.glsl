#version 330 core

uniform sampler2D Texture;

in vec2 FragUV;

out vec4 Color;

uniform bool IsDepth;
uniform float CameraNear;
uniform float CameraFar;

// https://learnopengl.com/Advanced-OpenGL/Depth-testing
float LinearizeDepth(float _Depth) 
{
    float Z = _Depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * CameraNear * CameraFar ) / (CameraFar + CameraNear - Z * (CameraFar - CameraNear));	
}

void main()
{
	if( IsDepth )
	{
		float Depth = LinearizeDepth( texture( Texture, FragUV ).r ) / CameraFar;
		Color.rgb = vec3( Depth );
		Color.a = 1.0;
	}
	else
		Color = texture( Texture, FragUV );
}
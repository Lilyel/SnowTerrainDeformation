#version 330 core

layout (location = 0) in vec2 Position;
layout (location = 2) in vec2 UV;

out vec2 FragUV;

void main()
{
	gl_Position = vec4(Position.xy, 0.0, 1.0);

	FragUV = UV;
}
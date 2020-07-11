#version 330 core

layout (location = 0) in vec3 Position;

uniform mat4 ConvProjection;
uniform mat4 ConvView;

out vec3 WorldPosition;

void main()
{
	WorldPosition = Position;
	gl_Position = vec4(Position.xyz, 0.0) * (ConvView * ConvProjection);
	gl_Position = gl_Position.xyww;
}
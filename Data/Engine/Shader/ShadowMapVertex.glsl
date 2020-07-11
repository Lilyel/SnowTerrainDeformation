#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec4 Color;
layout (location = 2) in vec2 UV;
layout (location = 3) in vec3 Normal;


uniform mat4 Model;
uniform mat4 ShadowMapViewMatrix;
uniform mat4 ShadowMapProjectionMatrix;

void main()
{
	gl_Position = vec4(Position.xyz, 1.0) * (Model * ShadowMapViewMatrix * ShadowMapProjectionMatrix);
}
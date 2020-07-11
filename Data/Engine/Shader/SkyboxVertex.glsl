#version 330 core

layout (location = 0) in vec3 Position;

uniform mat4 Projection;
uniform mat4 View;

out vec3 UVs;

void main()
{
	UVs = Position;
	vec4 Position = vec4(Position.xyz, 0.0) * (mat4(mat3(View)) * Projection);
	gl_Position = Position.xyww; // Trick for rendering the skybox last and pass the depth test.
}
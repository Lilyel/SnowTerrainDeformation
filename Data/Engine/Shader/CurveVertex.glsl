#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 2) in vec2 UV;

out ShaderData
{
	bool IsControlCurve;
} VertexOut;


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	gl_Position = vec4(Position, 1.0) * (Model * View * Projection);

	VertexOut.IsControlCurve = UV.x == 1;
}
#version 450 core

layout (location = 0) in vec3 Position;
layout (location = 2) in vec2 UV;

out ShaderData
{
	vec3 Position;
	vec2 UV;
} VertexOut;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform sampler2D HeightMap;

void main()
{
	float DisplacementAmount = texture( HeightMap, UV ).r;
	vec3 OffsetedPosition = Position + vec3( 0.0, 1.0, 0.0 ) * DisplacementAmount;

	gl_Position = vec4(Position, 1.0) * (Model * View * Projection);

	VertexOut.Position = vec3( vec4( Position, 1.0 ) * Model );
	VertexOut.UV = UV;
}
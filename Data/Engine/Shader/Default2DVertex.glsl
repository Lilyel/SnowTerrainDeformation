#version 330 core

layout (location = 0) in vec2 Position;
layout (location = 1) in vec4 Color;
layout (location = 2) in vec2 UV;

out vec4 FragmentColor;
out vec2 FragUV;

uniform mat3 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	mat4 Model3D;
	Model3D[0] = vec4( Model[0].xy, 0.0, Model[0].z );
	Model3D[1] = vec4( Model[1].xy, 0.0, Model[1].z );
	Model3D[2] = vec4( 0.0, 0.0, 1.0, 0.0 );
	Model3D[3] = vec4( 0.0, 0.0, 0.0,  Model[2].z );

	gl_Position = vec4(Position.xy, 0.0, 1.0) * (Model3D * View * Projection);

	FragmentColor = Color;
	FragUV = UV;
}
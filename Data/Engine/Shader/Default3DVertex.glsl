#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec4 Color;
layout (location = 2) in vec2 UV;
layout (location = 3) in vec3 Normal;

out ShaderData
{
	vec3 Position;
	vec4 Color;
	vec2 UV;
	vec3 Normal;	
	vec4 PosLightSpace;
} VertexOut;


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform mat4 ShadowMapViewMatrix;
uniform mat4 ShadowMapProjectionMatrix;

void main()
{
	gl_Position = vec4(Position, 1.0) * (Model * View * Projection);

	VertexOut.Position = vec3( vec4(Position, 1.0) * Model );
	VertexOut.Color = Color;
	VertexOut.UV = UV;
	VertexOut.Normal = Normal * mat3( transpose( inverse( Model ) ) );

	VertexOut.PosLightSpace = vec4(Position, 1.0) * (Model * ShadowMapViewMatrix * ShadowMapProjectionMatrix);
}
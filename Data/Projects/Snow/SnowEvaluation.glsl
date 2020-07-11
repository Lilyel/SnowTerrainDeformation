#version 450 core

layout(triangles, equal_spacing, ccw) in;

uniform sampler2D HeightMap;

in ShaderData
{
	vec3 Position;
	vec2 UV;
} EvaluationIn[];

out ShaderData
{
	vec3 Position;
	vec2 UV;
} EvaluationOut;


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;


vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
    return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main()
{
	EvaluationOut.UV = interpolate2D( EvaluationIn[0].UV, EvaluationIn[1].UV, EvaluationIn[2].UV );

	vec3 Position = interpolate3D( EvaluationIn[0].Position, EvaluationIn[1].Position, EvaluationIn[2].Position );
	float Displacement = texture( HeightMap, EvaluationOut.UV ).r;
	Position.y = Displacement;


	gl_Position = vec4(Position, 1.0) * (Model * View * Projection);
	EvaluationOut.Position = vec3( vec4(Position, 1.0) * Model );
	
}

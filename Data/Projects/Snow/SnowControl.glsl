#version 450 core

// Define the tesselation patch size.
layout (vertices = 3) out;

// Patch input from vertex shader.
in ShaderData
{
	vec3 Position;
	vec2 UV;
} ControlIn[];

// Output patch for evaluation shader.
out ShaderData
{
	vec3 Position;
	vec2 UV;
} ControlOut[];


uniform vec3 CameraPosition;

#include "SnowParameters.glsl"

void main()
{
    const float DistanceToCam = length( CameraPosition - ControlIn[gl_InvocationID].Position );
    const float TessRatio = clamp( ( DistanceToCam - TessCameraDistanceMin ) / ( TessCameraDistanceMax - TessCameraDistanceMin ), 0.0, 1.0 );
    const float TessAmount = mix( TessMax, TessMin, TessRatio );

    ControlOut[gl_InvocationID].Position = ControlIn[gl_InvocationID].Position;
    ControlOut[gl_InvocationID].UV = ControlIn[gl_InvocationID].UV;

    gl_TessLevelOuter[0] = TessAmount;
    gl_TessLevelOuter[1] = TessAmount;
    gl_TessLevelOuter[2] = TessAmount;
    gl_TessLevelInner[0] = TessAmount;

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}

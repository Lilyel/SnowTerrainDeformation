#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in ShaderData
{
	vec3 Position;
	vec4 Color;
	vec2 UV;
	vec3 Normal;	
} VertexIn[];


const float MAGNITUDE = 5.0;

void GenerateLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4( VertexIn[index].Normal, 0.0 ) * MAGNITUDE;
    //gl_Position = gl_in[index].gl_Position + vec4( 1.0, 0.0, 0.0, 0.0 ) * MAGNITUDE;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0); // First vertex normal 
    GenerateLine(1); // Second vertex normal
    GenerateLine(2); // Third vertex normal
}

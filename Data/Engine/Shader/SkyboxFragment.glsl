#version 330 core

in vec3 UVs;
out vec4 Color;

uniform samplerCube CubeMap;

void main()
{	
    Color = texture( CubeMap, UVs );
}
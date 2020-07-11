#version 330 core

out vec4 Color;

in vec4 GeomColor;

void main()
{
	Color = GeomColor;
}
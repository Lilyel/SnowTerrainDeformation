#version 330 core

out vec4 Color;

// Material reflection index.
uniform float IOR;

// Transparency of the material.
uniform float Opacity;

// Skybox.
uniform samplerCube CubeMap;

uniform vec3 CameraPosition;

// Input from vertex shader.
in ShaderData
{
	vec3 Position;
	vec4 Color;
	vec2 UV;
	vec3 Normal;
	vec4 PosLightSpace;	
} VertexIn;

void main()
{	
    vec3 Normal = normalize( VertexIn.Normal );
    vec3 ViewDirection = normalize( VertexIn.Position - CameraPosition );
    
    // Sample the skybox at the relfected direction.
    vec3 ReflectedDirection = reflect( ViewDirection, Normal );
    vec4 ReflectionColor = texture( CubeMap, ReflectedDirection );

    // Sample the skybox at the refracted direction.
    float RefractionRatio = 1.0 / IOR;
    vec3 RefractedDirection = refract( ViewDirection, Normal, RefractionRatio );
    vec4 RefractedColor = texture( CubeMap, RefractedDirection );

    // If the material is transparent, take more of the refraction color.
    // If it is opaque, take more of the reflection color.
    Color = mix( RefractedColor, ReflectionColor, Opacity );
}
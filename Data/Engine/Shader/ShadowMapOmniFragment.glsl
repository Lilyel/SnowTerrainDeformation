#version 330 core

in vec4 FragPos;

uniform vec3 ShadowMapLightPosition;
uniform float ShadowMapFar;

void main()
{
    float LightDistance = length( FragPos.xyz - ShadowMapLightPosition );

    // Map the distance between 0 and 1;
    LightDistance = LightDistance / ShadowMapFar;

    gl_FragDepth = LightDistance;
}

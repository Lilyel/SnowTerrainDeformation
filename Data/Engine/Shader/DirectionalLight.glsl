struct DirectionalLight
{
	vec3 Position;
	vec3 LookAt;
	
	vec4 Color;
	
	float Intensity;
};

vec3 GetDirectionalLightRadiance( in DirectionalLight _Light )
{
	return _Light.Color.rgb * _Light.Intensity;
}

vec3 GetDirectionalLightDirection( in DirectionalLight _Light )
{
	return normalize( -_Light.LookAt );
}
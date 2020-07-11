struct PointLight
{
	vec3 Position;
	
	vec4 Color;
	
	float Intensity;
	float Radius;
};

vec3 GetPointLightRadiance( in PointLight _Light, in vec3 _ViewDirection, in vec3 _VertexPosition )
{
	vec3 ToLight = _Light.Position - _VertexPosition;
	vec3 LightDirection = normalize( ToLight );
	vec3 Halfway = normalize( _ViewDirection + LightDirection );

	// Point light radiance
	float DistanceToLight = length( ToLight );
	float Attenuation = _Light.Intensity * pow( max( 0.0, 1.0 - ( DistanceToLight / _Light.Radius ) ), 2 );
	vec3 Radiance = _Light.Color.rgb * Attenuation;

	return Radiance;
}

vec3 GetPointLightDirection( in PointLight _Light, in vec3 _VertexPosition)
{
	return normalize(  _Light.Position - _VertexPosition );
}
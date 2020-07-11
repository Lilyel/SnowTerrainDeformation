struct SpotLight
{
	vec3 Position;
	vec3 LookAt;
	float Range;
	
	vec4 Color;
	
	float Intensity;

	float InnerAngle;
	float OuterAngle;
};

vec3 GetSpotLightRadiance( in SpotLight _Light, in vec3 _ViewDirection, in vec3 _VertexPosition )
{
	vec3 ToLight = _Light.Position - _VertexPosition;
	float DistanceToLight = length( ToLight );
	vec3 LightDirection = normalize( ToLight );

	float InnerCos = cos( _Light.InnerAngle );
	float OuterCos = cos( _Light.OuterAngle );

	float Theta = dot( LightDirection, normalize( -_Light.LookAt ) );
	float Epsilon = InnerCos - OuterCos;
	float IntensityFactor = clamp( (Theta - OuterCos) / Epsilon, 0.0, 1.0 );

	// Spot light radiance
	float RangeAttenuation = pow( max( 0.0, 1.0 - DistanceToLight / _Light.Range ), 2 );
	float Attenuation = _Light.Intensity * IntensityFactor * RangeAttenuation;
	vec3 Radiance = _Light.Color.rgb * Attenuation;

	return Radiance;
}

vec3 GetSpotLightDirection( in SpotLight _Light, in vec3 _VertexPosition)
{
	return normalize(  _Light.Position - _VertexPosition );
}
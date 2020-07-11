// Process overshadowing factor (geometry hiding microfacets from the point view) using the SchlickGGX formula.
float GeometrySchlickGGX( float _NdotV, float _Roughness )
{
	// Roughness for direct lighting.
    float R = _Roughness + 1.0;
    float K = ( R * R ) / 8.0;

    float Denominator = _NdotV * ( 1.0 - K ) + K;
	
    return _NdotV / Denominator;
}

float IBLGeometrySchlickGGX( float _NdotV, float _Roughness )
{
	// Roughness for indirect lighting.
    float K = ( _Roughness * _Roughness ) / 2.0;

    float Denominator = _NdotV * ( 1.0 - K ) + K;
	
    return _NdotV / Denominator;
}
// Gamma correction to convert sRGB color to linear RGB color.
vec3 sRGBToLinear( in vec3 _sRGB )
{
	return pow( _sRGB, vec3( 2.2 ) );
}

vec4 sRGBAToLinear( in vec4 _sRGBA )
{
	return pow( _sRGBA, vec4( 2.2 ) );
}

vec3 LinearTosRGB( in vec3 _Linear )
{
    vec3 sRGB = _Linear / ( _Linear + vec3( 1.0 ) );

	// Gamma correction (linear color to sRGB).
	sRGB = pow( sRGB, vec3( 1.0 / 2.2 ) );

    return sRGB;
}

vec4 LinearTosRGBA( in vec4 _Linear )
{
    vec4 sRGBA = _Linear / ( _Linear + vec4( 1.0 ) );

	// Gamma correction (linear color to sRGB).
	sRGBA = pow( sRGBA, vec4( 1.0 / 2.2 ) );

    return sRGBA;
}
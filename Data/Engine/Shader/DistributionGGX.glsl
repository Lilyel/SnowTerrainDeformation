
#include "MathConstants.glsl"

// Process a normal distribution with Trowbridge-Reitz GGX formula.
float DistributionGGX( in float _Roughness, in vec3 _Normal, vec3 _Halfway )
{
    float Alpha = _Roughness * _Roughness;
    float AlphaSqr = Alpha * Alpha;
    float NdotH  = max( dot( _Normal, _Halfway ), 0.0 );
    float NdotHSqr = NdotH * NdotH;
	
    float Denominator = ( NdotHSqr * ( AlphaSqr - 1.0) + 1.0 );
    Denominator = M_PI * Denominator * Denominator;
	
    return AlphaSqr / Denominator;
}
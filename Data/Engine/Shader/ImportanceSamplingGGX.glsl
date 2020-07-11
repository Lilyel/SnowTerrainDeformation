#include "MathConstants.glsl"

// https://learnopengl.com/PBR/IBL/Specular-IBL

float RadicalInverse_VdC(uint _Bits) 
{
    _Bits = (_Bits << 16u) | (_Bits >> 16u);
    _Bits = ((_Bits & 0x55555555u) << 1u) | ((_Bits & 0xAAAAAAAAu) >> 1u);
    _Bits = ((_Bits & 0x33333333u) << 2u) | ((_Bits & 0xCCCCCCCCu) >> 2u);
    _Bits = ((_Bits & 0x0F0F0F0Fu) << 4u) | ((_Bits & 0xF0F0F0F0u) >> 4u);
    _Bits = ((_Bits & 0x00FF00FFu) << 8u) | ((_Bits & 0xFF00FF00u) >> 8u);
    return float(_Bits) * 2.3283064365386963e-10; // / 0x100000000
}
// ----------------------------------------------------------------------------
vec2 Hammersley(uint _Seed, uint _Count )
{
    return vec2( float( _Seed ) / float( _Count ), RadicalInverse_VdC( _Seed ) );
}

vec3 ImportanceSamplingGGX( vec2 _Random, vec3 _Normal, float _Roughness )
{
    float K = _Roughness * _Roughness;

    float Phi = 2.0 * M_PI * _Random.x;
    float CosTheta = sqrt( ( 1.0 - _Random.y ) / ( 1.0 + ( K * K - 1.0 ) * _Random.y ) );
    float SinTheta = sqrt( 1.0 - CosTheta * CosTheta );
    
    // Spherical to cartesian (tangent space) coordinates.
    vec3 H = vec3( cos( Phi ) * SinTheta, sin( Phi ) * SinTheta, CosTheta );

    // From tangent-space to world space.
    vec3 Up = abs( _Normal.z ) < 0.999 ? vec3( 0.0, 0.0, 1.0 ) : vec3( 1.0, 0.0, 0.0 );
    vec3 Tangent = normalize( cross( Up, _Normal ) );
    vec3 BiTangent = cross( _Normal, Tangent );

    vec3 Sample = Tangent * H.x + BiTangent * H.y + _Normal * H.z;
    return normalize( Sample );
}
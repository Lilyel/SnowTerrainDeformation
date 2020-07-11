
// Process the approximation of the Fresnel reflectivity coefficient with the FresnelSchlick formula.
// _CosTheta is the cosinus of the angle between the normal and the light incidence direction.
// _F0 is the surface reflection at a zero incidence (light incidence aligned with view direction).
vec3 FresnelSchlick( float _CosTheta, vec3 _F0 )
{
    return _F0 + ( 1.0 - _F0 ) * pow( 1.0 - _CosTheta, 5.0 );
}  

vec3 FresnelSchlickRoughness( float _CosTheta, vec3 _F0, float _Roughness )
{
    return _F0 + ( max( vec3( 1.0 - _Roughness ), _F0 ) - _F0 ) * pow( 1.0 - _CosTheta, 5.0 );
}  
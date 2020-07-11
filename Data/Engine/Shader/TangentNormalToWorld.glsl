

// Taken from : 
// https://learnopengl.com/code_viewer_gh.php?code=src/6.pbr/1.2.lighting_textured/1.2.pbr.fs
vec3 TangentNormalToWorld( in vec3 _TangentNormal, in vec3 _VertexNormal, in vec3 _VertexPosition, in vec2 _VertexUV )
{
    vec3 TangentNormal = _TangentNormal * 2.0 - 1.0;

    vec3 Q1  = dFdx( _VertexPosition );
    vec3 Q2  = dFdy( _VertexPosition );
    vec2 st1 = dFdx( _VertexUV );
    vec2 st2 = dFdy( _VertexUV );

    vec3 N   = normalize( _VertexNormal );
    vec3 T  = normalize( Q1 * st2.t - Q2 * st1.t );
    vec3 B  = -normalize( cross( N, T ) );
    mat3 TBN = mat3( T, B, N );

    return normalize( TBN * TangentNormal );
}

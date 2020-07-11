
uniform sampler2D ShadowMap;
uniform samplerCube ShadowMapOmni;
uniform vec3 ShadowMapLightPosition;
uniform bool ShadowMapUsePCF;
uniform float ShadowMapOmniPCFRadius;
uniform float ShadowMapBias;
uniform float ShadowMapFar;
uniform bool HasShadowMap;
uniform bool IsShadowMapOmni;

float ShadowUniCalculation( vec4 _PosLightSpace, vec3 _Normal, vec3 _Position )
{
    if( !HasShadowMap )
		return 0.0;

	vec3 ProjectedCoords = _PosLightSpace.xyz / _PosLightSpace.w;
	ProjectedCoords = ProjectedCoords * 0.5 + 0.5;

	float CurrentDepth = ProjectedCoords.z;
	if( CurrentDepth > 1.0 )
		return 0.0;


	vec3 Normal = normalize( _Normal );
	vec3 LightDirection = normalize( ShadowMapLightPosition - _Position );
	float Bias = max( ShadowMapBias * ( 1.0 - dot( Normal, LightDirection ) ), ShadowMapBias );

	vec2 TexelSize = 1.0 / textureSize( ShadowMap, 0 );
	float Shadow = 0.0;

    if( ShadowMapUsePCF )
    {
        // PCF for softer shadow.
        for( int x = -1; x <= 1; x++ )
        {
            for( int y = -1; y <= 1; y++)
            {
                float PCFDepth = texture( ShadowMap, ProjectedCoords.xy + vec2( x, y ) * TexelSize ).r;
                Shadow += ( CurrentDepth - Bias > PCFDepth ? 1.0 : 0.0 );
            }
        }	
	    return Shadow / 9.0;
    }
    else
    {
        float ClosestDepth = texture( ShadowMap, ProjectedCoords.xy ).r;
        return CurrentDepth - Bias > ClosestDepth ? 1.0 : 0.0;
    }
}

float ShadowOmniPCF( vec3 _Position, vec3 _LightDirection, vec3 _ViewPosition, float CurrentDepth, float Bias )
{
    float Shadow = 0.0;
    int SamplesCount = 20;
    float ViewDistance = length( _ViewPosition - _Position );
    float DiskRadius = ShadowMapOmniPCFRadius;

    vec3 SamplesOffsets[20] = vec3[]
    (
      vec3( 1.0, 1.0, 1.0 ), vec3( 1.0, -1.0, 1.0 ), vec3( -1.0, -1.0, 1.0 ), vec3( -1.0, 1.0, 1.0 ), 
      vec3( 1.0, 1.0, -1.0 ), vec3( 1.0, -1.0, -1.0 ), vec3( -1.0, -1.0, -1.0 ), vec3( -1.0, 1.0, -1.0 ),
      vec3( 1.0, 1.0, 0.0 ), vec3( 1.0, -1.0, 0.0 ), vec3( -1.0, 1.0, 0.0 ), vec3( -1.0, -1.0, 0.0 ),
      vec3( 1.0, 0.0, 1.0 ), vec3( -1.0, 0.0, 1.0 ), vec3( 1.0, 0.0, -1.0 ), vec3( -1.0, 0.0, -1.0 ),
      vec3( 0.0, 1.0, 1.0 ), vec3( 0.0, -1.0, 1.0 ), vec3( 0.0, 1.0, -1.0 ), vec3( 0.0, -1.0, -1.0 )
    );

    for( int s = 0; s < SamplesCount; s++ )
    {
        float ClosestDepth = texture( ShadowMapOmni, _LightDirection + SamplesOffsets[s] * DiskRadius ).r;
        ClosestDepth *= ShadowMapFar;
        if( CurrentDepth - Bias > ClosestDepth )
            Shadow += 1.0;   
    }

    return Shadow / float( SamplesCount );
}

float ShadowOmniCalculation( vec3 _Normal, vec3 _Position, vec3 _ViewPosition )
{
    vec3 LightDirection = _Position - ShadowMapLightPosition;
    
    float ClosestDepth = texture( ShadowMapOmni, LightDirection ).r;
    ClosestDepth *= ShadowMapFar;

    float CurrentDepth = length( LightDirection );

    vec3 Normal = normalize( _Normal );
    float Bias = max( ShadowMapBias * ( 1.0 - dot( Normal, LightDirection ) ), ShadowMapBias );

    if( ShadowMapUsePCF )
        return ShadowOmniPCF( _Position, LightDirection, _ViewPosition, CurrentDepth, Bias );
    else
        return CurrentDepth - Bias > ClosestDepth ? 1.0 : 0.0;
}

float ShadowCalculation( vec4 _PosLightSpace, vec3 _Normal, vec3 _Position, vec3 _ViewPosition )
{
	if( IsShadowMapOmni )
        return ShadowOmniCalculation( _Normal, _Position, _ViewPosition );
    else
        return ShadowUniCalculation( _PosLightSpace, _Normal, _Position );
}
#version 450 core

#define OBSTACLE_THRESHOLD 10u

uniform usampler2D HeightMap;
uniform sampler2D DepthTexture;

#include "SnowParameters.glsl"

in vec2 FragUV;

// Format : Seed position(ivec2), Type ? -1 for penetrating point ("obstacle"), -2 for close to penetrating, -3 for not penetrating ("seed"), Penetration value.
out ivec4 Color;

void main()
{
	const float FrustumHeight = CameraFar - CameraNear;

	const uint HeightMapValue = texture( HeightMap, FragUV ).r;
	const uint DepthValue = uint( texture( DepthTexture, FragUV ).r * HeightMapScale * FrustumHeight );

	const uint Penetration = HeightMapValue - min( HeightMapValue, DepthValue );
	

	int PixelType;
	ivec2 SeedPosition;
	
	// Penetrating point.
	if( Penetration > 0u )
		PixelType = -1;

	// Not penetrating but close. "Obstacles"
	else if( Penetration <= 0u && abs( int( DepthValue ) - int( HeightMapValue ) ) < OBSTACLE_THRESHOLD )
		PixelType = -2;

	// Not penetatring. "Seeds"
	else
	{
		PixelType = -3;
		SeedPosition = ivec2( gl_FragCoord.xy );
	}

	Color = ivec4( SeedPosition, PixelType, Penetration );
}
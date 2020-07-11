#pragma once

#include <API/Code/Toolbox/Toolbox.h>
#include <API/Code/Maths/Functions/MathsFunctions.h>

/// <summary>Parameter (some user tweakable) sent as a buffer to the shaders.</summary>
struct SnowParameters
{
public:
	inline constexpr size_t GetStructSize()
	{
		return 22 * sizeof( float ) + 1 * sizeof( Uint32 );
	}

	// Aligned size according to std140
	inline constexpr size_t GetStructAlignedSize()
	{
		return 23 * 4;
	}

	// Auto datas.

	float CameraNear = 0.0f;
	float CameraFar = 1.0f;
	float HeightMapScale = 10000.0f;

	Uint32 TextureSize = 512;
	float PixelSize = 1.0f;

	float Time = 0.0f;


	// Initialization datas.

	float InitialMinHeight = 0.20f;
	float InitialMaxHeight = 0.3f;
	float InitialDuneFrequency = 2.7f;
	float InitialSeed = 2.75f;

	// Deformation datas.

	float Compression = 0.0f;
	float Roughness = 0.2f;
	float SlopeThreshold = ae::Math::DegToRad_Const( 60.0f );

	
	// Noise datas.

	float ChunkFrequency = 15.0f;
	float ChunkAmount = 0.1f;

	float GrainFrequency = 1000.0f;
	float GrainAmount = 0.15f;

	float NoiseSeed = 0.0f;

	float SlopeMaxBetweenFrame = ae::Math::DegToRad_Const( 80.0f );


	// Tesselation data.

	float TessMin = 1.0f;
	float TessMax = 8.0f;
	float TessCameraDistanceMin = 3.0f;
	float TessCameraDistanceMax = 5.0f;
};
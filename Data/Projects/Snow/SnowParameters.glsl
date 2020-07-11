layout(std140, binding = 4) uniform Parameters
{   
  
    // Auto.

	float CameraNear;
	float CameraFar;
	float HeightMapScale;

    uint TextureSize;
	float PixelSize;

    float Time;


    // Initialization.

    float InitialMinHeight;
	float InitialMaxHeight;
	float InitialDuneFrequency;
    float IntialSeed;


      // Deformation.

	float SnowCompression;
	float SnowRoughness;
	float SlopeThreshold;

	


    // Noise.
    float ChunkFrequency;
    float ChunkAmount;

    float GrainFrequency;
    float GrainAmount;

    float NoiseSeed;

    float SlopeMaxBetweenFrame;


    // Tesselation.
    float TessMin;
	float TessMax;
	float TessCameraDistanceMin;
	float TessCameraDistanceMax;
};
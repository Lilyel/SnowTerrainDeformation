
struct PBRData
{
	vec3 Albedo;
	float Opacity;
	vec3 EmissiveColor;	
	float Metalness;
	float Roughness;
	vec3 Normal;
	float AmbientOcclusion;

	vec3 Irradiance;
	vec3 Radiance;

	vec3 BaseReflectivity; // F0
};

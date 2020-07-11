// Base color user inputs.
uniform vec4 BaseColor;
uniform sampler2D BaseColorTexture;
uniform bool UseBaseColorTexture;

// Normals user inputs.
uniform sampler2D NormalCameraTexture;
uniform bool UseNormalCameraTexture;

// Emissive user inputs.
uniform vec4 EmissionColor;
uniform sampler2D EmissionColorTexture;
uniform bool UseEmissionColorTexture;

// Metalness user inputs.
uniform float Metalness;
uniform sampler2D MetalnessTexture;
uniform bool UseMetalnessTexture;

// Roughness user inputs.
uniform float Roughness;
uniform sampler2D RoughnessTexture;
uniform bool UseRoughnessTexture;

// Ambient occlusion user inputs.
uniform float AmbientOcclusion;
uniform sampler2D AmbientOcclusionTexture;
uniform bool UseAmbientOcclusionTexture;

// Ambient color strength.
uniform float AmbientStrength;

// Image based lighting.
uniform bool UseIBL;
uniform samplerCube IrradianceMap;
uniform samplerCube RadianceMap;
uniform sampler2D BRDFLut;
uniform int RadianceMaxLod;

// HDR
uniform bool ApplyGammaCorrection;
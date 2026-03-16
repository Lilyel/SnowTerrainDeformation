#include "AssimpHelper.h"

#include "../Texture/TextureImage.h"
#include "../Material/Material.h"
#include "../Material/BlinnPhongMaterial.h"
#include "../Material/CookTorranceMaterial.h"
#include "../Material/ToonMaterial.h"
#include "../Color/Color.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace ae
{
	namespace priv
	{
		Color AssimpColorToEngineColor( const aiColor4D& _AssimpColor )
		{
			return Color( _AssimpColor.r, _AssimpColor.g, _AssimpColor.b, _AssimpColor.a );
		}

		void AssimpLoadBlinnPhongMaterial( BlinnPhongMaterial& _OurMaterial, const aiMaterial* _AssimpMaterial, const std::string& _Directory )
		{
			aiColor4D ResultColor;
			float ResultFloat;

			// Shininess.
			_AssimpMaterial->Get( AI_MATKEY_SHININESS, ResultFloat );
			_OurMaterial.GetShininess().SetValue( ResultFloat );
			
			// Diffuse color.
			_AssimpMaterial->Get( AI_MATKEY_COLOR_DIFFUSE, ResultColor );
			_OurMaterial.GetDiffuseColor().SetValue( AssimpColorToEngineColor( ResultColor ) );

			// Ambient color.
			_AssimpMaterial->Get( AI_MATKEY_COLOR_AMBIENT, ResultColor );
			_OurMaterial.GetAmbientColor().SetValue( AssimpColorToEngineColor( ResultColor ) );

			// Specular color.
			_AssimpMaterial->Get( AI_MATKEY_COLOR_SPECULAR, ResultColor );
			_OurMaterial.GetSpecularColor().SetValue( AssimpColorToEngineColor( ResultColor ) );


			// Diffuse texture.
			_OurMaterial.GetDiffuseTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_DIFFUSE ) );

			// Specular texture.
			_OurMaterial.GetSpecularTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_SPECULAR ) );

			// Ambient texture.
			_OurMaterial.GetAmbientTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_AMBIENT ) );

			// Normal texture.
			_OurMaterial.GetNormalTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_NORMALS ) );

			// Shininess texture.
			_OurMaterial.GetShininessTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_SHININESS ) );
		}

		void AssimpLoadCookTorranceMaterial( CookTorranceMaterial& _OurMaterial, const aiMaterial* _AssimpMaterial, const std::string& _Directory )
		{
			aiColor4D ResultColor;

			// Diffuse color.
			_AssimpMaterial->Get( AI_MATKEY_COLOR_DIFFUSE, ResultColor );
			_OurMaterial.GetBaseColor().SetValue( AssimpColorToEngineColor( ResultColor ) );


			// Base color texture.
			_OurMaterial.GetBaseColorTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_BASE_COLOR ) );

			// Normal camera texture.
			_OurMaterial.GetNormalTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_NORMAL_CAMERA ) );

			// Emissive color.
			_AssimpMaterial->Get( AI_MATKEY_COLOR_EMISSIVE, ResultColor );
			_OurMaterial.GetEmissiveColor().SetValue( AssimpColorToEngineColor( ResultColor ) );

			// Emission Color texture.
			_OurMaterial.GetEmissiveColorTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_EMISSION_COLOR ) );

			// Metalness texture.
			_OurMaterial.GetMetalnessTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_METALNESS ) );

			// Roughness texture.
			_OurMaterial.GetRoughnessTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_DIFFUSE_ROUGHNESS ) );

			// Ambient occlusion texture.
			_OurMaterial.GetAmbientOcclusionTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_AMBIENT_OCCLUSION ) );
		}

		void AssimpLoadToonMaterial( ToonMaterial& _OurMaterial, const aiMaterial* _AssimpMaterial, const std::string& _Directory )
		{
			aiColor4D ResultColor;
			float ResultFloat;

			// Shininess.
			_AssimpMaterial->Get( AI_MATKEY_SHININESS, ResultFloat );
			_OurMaterial.GetShininess().SetValue( ResultFloat );

			// Diffuse color.
			_AssimpMaterial->Get( AI_MATKEY_COLOR_DIFFUSE, ResultColor );
			_OurMaterial.GetDiffuseColor().SetValue( AssimpColorToEngineColor( ResultColor ) );

			// Ambient color.
			_AssimpMaterial->Get( AI_MATKEY_COLOR_AMBIENT, ResultColor );
			_OurMaterial.GetAmbientColor().SetValue( AssimpColorToEngineColor( ResultColor ) );

			// Specular color.
			_AssimpMaterial->Get( AI_MATKEY_COLOR_SPECULAR, ResultColor );
			_OurMaterial.GetSpecularColor().SetValue( AssimpColorToEngineColor( ResultColor ) );


			// Diffuse texture.
			_OurMaterial.GetDiffuseTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_DIFFUSE ) );

			// Specular texture.
			_OurMaterial.GetSpecularTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_SPECULAR ) );

			// Ambient texture.
			_OurMaterial.GetAmbientTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_AMBIENT ) );

			// Normal texture.
			_OurMaterial.GetNormalTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_NORMALS ) );

			// Shininess texture.
			_OurMaterial.GetShininessTexture().SetTexture( AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_SHININESS ) );
		}
		void AssimpLoadMaterial( Material& _OurMaterial, const aiMaterial* _AssimpMaterial, const std::string& _Directory, Bool _UseTextureBool )
		{
			aiColor4D ResultColor;
			float ResultFloat;

			// Shininess.
			_AssimpMaterial->Get( AI_MATKEY_SHININESS, ResultFloat );
			_OurMaterial.AddFloatParameterToMaterial( "Shininess", "Shininess", ResultFloat );

			// Reflectivity.
			_AssimpMaterial->Get( AI_MATKEY_REFLECTIVITY, ResultFloat );
			_OurMaterial.AddFloatParameterToMaterial( "Reflectivity", "Reflectivity", ResultFloat );

			// Refraction coeficient.
			_AssimpMaterial->Get( AI_MATKEY_REFRACTI, ResultFloat );
			_OurMaterial.AddFloatParameterToMaterial( "Refraction", "Refraction", ResultFloat );


			// Diffuse color.
			_AssimpMaterial->Get( AI_MATKEY_COLOR_DIFFUSE, ResultColor );
			_OurMaterial.AddColorParameterToMaterial( "DiffuseColor", "DiffuseColor", AssimpColorToEngineColor( ResultColor ) );

			// Ambient color.
			_AssimpMaterial->Get( AI_MATKEY_COLOR_AMBIENT, ResultColor );
			_OurMaterial.AddColorParameterToMaterial( "AmbientColor", "AmbientColor", AssimpColorToEngineColor( ResultColor ) );

			// Specular color.
			_AssimpMaterial->Get( AI_MATKEY_COLOR_SPECULAR, ResultColor );
			_OurMaterial.AddColorParameterToMaterial( "SpecularColor", "SpecularColor", AssimpColorToEngineColor( ResultColor ) );

			// Emissive color.
			_AssimpMaterial->Get( AI_MATKEY_COLOR_EMISSIVE, ResultColor );
			_OurMaterial.AddColorParameterToMaterial( "EmissiveColor", "EmissiveColor", AssimpColorToEngineColor( ResultColor ) );

			// Reflective color.
			_AssimpMaterial->Get( AI_MATKEY_COLOR_REFLECTIVE, ResultColor );
			_OurMaterial.AddColorParameterToMaterial( "ReflectiveColor", "ReflectiveColor", AssimpColorToEngineColor( ResultColor ) );


			// Diffuse texture.
			_OurMaterial.AddTextureParameterToMaterial( "DiffuseTexture", "DiffuseTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_DIFFUSE ),
														_UseTextureBool );

			// Specular texture.
			_OurMaterial.AddTextureParameterToMaterial( "SpecularTexture", "SpecularTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_SPECULAR ),
														_UseTextureBool );

			// Ambient texture.
			_OurMaterial.AddTextureParameterToMaterial( "AmbientTexture", "AmbientTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_AMBIENT ),
														_UseTextureBool );

			// Emissive texture.
			_OurMaterial.AddTextureParameterToMaterial( "EmissiveTexture", "EmissiveTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_EMISSIVE ),
														_UseTextureBool );

			// Height texture.
			_OurMaterial.AddTextureParameterToMaterial( "HeightTexture", "HeightTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_HEIGHT ),
														_UseTextureBool );

			// Normal texture.
			_OurMaterial.AddTextureParameterToMaterial( "NormalTexture", "NormalTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_NORMALS ),
														_UseTextureBool );

			// Shininess texture.
			_OurMaterial.AddTextureParameterToMaterial( "ShininessTexture", "ShininessTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_SHININESS ),
														_UseTextureBool );

			// Displacement texture.
			_OurMaterial.AddTextureParameterToMaterial( "DisplacementTexture", "DisplacementTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_DISPLACEMENT ),
														_UseTextureBool );

			// LightMap texture.
			_OurMaterial.AddTextureParameterToMaterial( "LightMapTexture", "LightMapTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_LIGHTMAP ),
														_UseTextureBool );

			// Reflection texture.
			_OurMaterial.AddTextureParameterToMaterial( "ReflectionTexture", "ReflectionTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_REFLECTION ),
														_UseTextureBool );

			// Base color texture.
			_OurMaterial.AddTextureParameterToMaterial( "BaseColorTexture", "BaseColorTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_BASE_COLOR ),
														_UseTextureBool );

			// Normal camera texture.
			_OurMaterial.AddTextureParameterToMaterial( "NormalCameraTexture", "NormalCameraTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_NORMAL_CAMERA ),
														_UseTextureBool );

			// Emission Color texture.
			_OurMaterial.AddTextureParameterToMaterial( "EmissionColorTexture", "EmissionColorTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_EMISSION_COLOR ),
														_UseTextureBool );

			// Metalness texture.
			_OurMaterial.AddTextureParameterToMaterial( "MetalnessTexture", "MetalnessTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_METALNESS ),
														_UseTextureBool );

			// Roughness texture.
			_OurMaterial.AddTextureParameterToMaterial( "RoughnessTexture", "RoughnessTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_DIFFUSE_ROUGHNESS ),
														_UseTextureBool );

			// Ambient occlusion texture.
			_OurMaterial.AddTextureParameterToMaterial( "AmbientOcclusionTexture", "AmbientOcclusionTexture",
														AssimpGetMaterialTexture( _AssimpMaterial, _Directory, aiTextureType::aiTextureType_AMBIENT_OCCLUSION ),
														_UseTextureBool );
		}

		Texture* AssimpGetMaterialTexture( const aiMaterial* _Material, const std::string& _Directory, Uint32 _TextureType )
		{
			if( _Material->GetTextureCount( Cast( aiTextureType, _TextureType ) ) > 0 )
			{
				aiString TextureFileName;
				_Material->GetTexture( Cast( aiTextureType, _TextureType ), 0, &TextureFileName );

				Texture* NewTexture = new TextureImage( _Directory + "/" + std::string( TextureFileName.C_Str() ) );

				// Let the manager handle the memory of the texture.
				NewTexture->SetIsManagedByManager( True );

				return NewTexture;
			}
			else
				return nullptr;
		}

	} // priv
} // ae
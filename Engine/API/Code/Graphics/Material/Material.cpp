#include "Material.h"

#include "../Shader/ShaderParameter/ShaderParameter.h"
#include "../Shader/ShaderParameter/ShaderParameterTextureBool.h"
#include "../Shader/ShaderParameter/ShaderParameterTexture.h"
#include "../Shader/ShaderParameter/ShaderParameterCubeMap.h"
#include "../Shader/ShaderParameter/ShaderParameterCubeMapBool.h"
#include "../Shader/ShaderParameter/ShaderParameterFloat.h"
#include "../Shader/ShaderParameter/ShaderParameterInt.h"
#include "../Shader/ShaderParameter/ShaderParameterBool.h"
#include "../Shader/ShaderParameter/ShaderParameterColor.h"
#include "../Shader/ShaderParameter/ShaderParameterVector2.h"
#include "../Shader/ShaderParameter/ShaderParameterVector3.h"
#include "../Shader/ShaderParameter/ShaderParameterMatrix3x3.h"
#include "../Shader/ShaderParameter/ShaderParameterMatrix4x4.h"
#include "../Texture/Texture.h"
#include "../CubeMap/CubeMap.h"
#include "../ShadowMap/ShadowMap.h"
#include "../../Aero/Aero.h"

#include "../../Editor/TypesToEditor/MaterialToEditor.h"

namespace ae
{
	const std::array<std::string, Cast( size_t, Material::DefaultParameters::Count )> Material::DefaultParametersNames =
	{
		// 3D
		"Shininess",
		"Reflectivity",
		"Refraction",
		"DiffuseColor",
		"AmbientColor",
		"AmbientStrength",
		"SpecularColor",
		"EmissiveColor",
		"ReflectiveColor",
		"DiffuseTexture",
		"SpecularTexture",
		"AmbientTexture",
		"EmissiveTexture",
		"HeightTexture",
		"NormalTexture",
		"ShininessTexture",
		"DisplacementTexture",
		"LightMapTexture",
		"ReflectionTexture",

		// PBR
		"BaseColor",
		"EmissionColor",
		"Metalness",
		"Roughness",
		"AmbientOcclusion",
		"BaseColorTexture",
		"NormalCameraTexture",
		"EmissionColorTexture",
		"MetalnessTexture",
		"RoughnessTexture",
		"AmbientOcclusionTexture",

		// IBL
		"UseIBL",
		"IrradianceMap",
		"RadianceMap",
		"BRDFLut",
		"RadianceMaxLod",

		// HDR
		"ApplyGammaCorrection",

		// Sprite
		"Texture",

		// Framebuffer
		"Texture",
		"IsDepth",


		// Transformation 2D matrix.
		"Model",

		// Transformation 3D matrix.
		"Model",


		// View matrix.
		"View",

		// Projection matrix.
		"Projection",

		// Camera position.
		"CameraPosition",

		// Camera near distance.
		"CameraNear",

		// Camera far distance.
		"CameraFar",

		// Camera viewport size.
		"CameraViewportSize",

		// Point lights array.
		"PointLights",

		// Spot lights array.
		"SpotLights",

		// Directional lights array.
		"DirectionalLights",

		// Point lights count.
		"PointLightsCount",

		// Spot lights count.
		"SpotLightsCount",

		// Directional lights count.
		"DirectionalLightsCount",

		// Skybox cube map.
		"CubeMap",

		// Toon.
		"RimColor",
		"RimSize",
		"RimThreshold",

		// Shadow map.
		"ShadowMapViewMatrix",
		"ShadowMapProjectionMatrix",
		"ShadowMapLightPosition",
		"ShadowMap",
		"ShadowMapOmni",
		"IsShadowMapOmni",
		"ShadowMapUsePCF",
		"ShadowMapOmniPCFRadius",
		"ShadowMapBias",
		"ShadowMapFar",
		"HasShadowMap",

		// Curve.
		"ControlCurveColor",
		"CurveColor",
		"DrawControlCurve",
		"DrawCurve"
	};

	Material::Material() :
		m_ShaderRef( nullptr ),
		m_IsInstance( False ),
		m_ShadowMapRef( nullptr ),
		m_NeedLights( True ),
		m_NeedCamera( True )
	{
		SetName( std::string( "Material_" ) + std::to_string( GetResourceID() ) );
	}

	Material::Material( const Shader& _Shader ) :
		m_IsInstance( False ),
		m_ShadowMapRef( nullptr ),
		m_NeedLights( True ),
		m_NeedCamera( True )
	{
		SetShader( _Shader );

		SetName( std::string( "Material_" ) + std::to_string( GetResourceID() ) );
	}

	Material::Material( const Material& _Other ) :
		m_IsInstance( False )
	{
		CopyMaterial( _Other );

		SetName( std::string( "Material_" ) + std::to_string( GetResourceID() ) );
	}

	Material& Material::operator=( const Material& _Other )
	{
		CopyMaterial( _Other );

		return *this;
	}

	void Material::AddParameter( ShaderParameter* _Parameter )
	{
		if( _Parameter == nullptr )
			return;

		// Remove the previous parameter with this name if it exists.
		RemoveParameter( _Parameter->GetName() );

		m_Parameters.emplace( _Parameter->GetName(), _Parameter );
	}

	void Material::RemoveParameter( const std::string& _ParameterName )
	{
		std::unordered_map<std::string, ShaderParameter*>::iterator ItParam = m_Parameters.find( _ParameterName );

		if( ItParam == m_Parameters.end() )
			return;

		if( ItParam->second->IsDestroyedWithMaterial() )
			delete ItParam->second;

		m_Parameters.erase( ItParam );
	}

	void Material::RemoveAllParameters()
	{
		if( m_Parameters.empty() )
			return;

		for( const std::pair<const std::string, ShaderParameter*>& ParamPair : m_Parameters )
		{
			if( ParamPair.second != nullptr && ParamPair.second->IsDestroyedWithMaterial() )
				delete ParamPair.second;
		}

		m_Parameters.clear();
	}

	const std::unordered_map<std::string, ShaderParameter*>& Material::GetAllParameters() const
	{
		return m_Parameters;
	}



	std::unordered_map<std::string, ShaderParameter*>::iterator Material::begin()
	{
		return m_Parameters.begin();
	}

	std::unordered_map<std::string, ShaderParameter*>::iterator Material::end()
	{
		return m_Parameters.end();
	}



	void Material::SendParametersToShader( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& _ImageUnit ) const
	{
		if( m_Parameters.empty() )
			return;

		for( const std::pair<const std::string, ShaderParameter*>& ParamPair : m_Parameters )
		{
			if( ParamPair.second == nullptr )
				continue;

			ParamPair.second->SendToShader( _Shader, _TextureUnit, _ImageUnit );
		}

		const std::string& HasShadowMapName = GetDefaultParameterName( DefaultParameters::ShadowMap_HasShadowMap );
		if( HasShadowMap() )
		{
			m_ShadowMapRef->SendParametersToShader( _Shader, _TextureUnit );
			_Shader.SetBool( _Shader.GetUniformLocation( HasShadowMapName ), True );
		}
		else
			_Shader.SetBool( _Shader.GetUniformLocation( HasShadowMapName ), False );
	}

	void Material::Clean( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& _ImageUnit ) const
	{
		if( m_Parameters.empty() )
			return;

		for( const std::pair<const std::string, ShaderParameter*>& ParamPair : m_Parameters )
		{
			if( ParamPair.second == nullptr )
				continue;

			ParamPair.second->Clean( _Shader, _TextureUnit, _ImageUnit );
		}

		if( HasShadowMap() )
			m_ShadowMapRef->Clean( _Shader, _TextureUnit );
	}



	ShaderParameter* Material::GetParameter( const std::string& _Name )
	{
		std::unordered_map<std::string, ShaderParameter*>::iterator ItParam = m_Parameters.find( _Name );

		return ItParam == m_Parameters.end() ? nullptr : ItParam->second;
	}

	const ShaderParameter* Material::GetParameter( const std::string& _Name ) const
	{
		std::unordered_map<std::string, ShaderParameter*>::const_iterator ItParam = m_Parameters.find( _Name );

		return ItParam == m_Parameters.cend() ? nullptr : ItParam->second;
	}


	ShaderParameter* Material::GetParameter( DefaultParameters _DefaultParameter )
	{
		std::unordered_map<std::string, ShaderParameter*>::iterator ItParam = m_Parameters.find( DefaultParametersNames[Cast( size_t, _DefaultParameter )] );

		return ItParam == m_Parameters.end() ? nullptr : ItParam->second;
	}

	const ShaderParameter* Material::GetParameter( DefaultParameters _DefaultParameter ) const
	{
		std::unordered_map<std::string, ShaderParameter*>::const_iterator ItParam = m_Parameters.find( DefaultParametersNames[Cast( size_t, _DefaultParameter )] );

		return ItParam == m_Parameters.cend() ? nullptr : ItParam->second;
	}



	const std::string& Material::GetDefaultParameterName( DefaultParameters _DefaultParameter )
	{
		return DefaultParametersNames[Cast( size_t, _DefaultParameter )];
	}



	void Material::SaveUniformsLocation()
	{
		if( m_ShaderRef == nullptr || m_Parameters.empty() )
			return;

		for( const std::pair<const std::string, ShaderParameter*>& ParamPair : m_Parameters )
		{
			if( ParamPair.second == nullptr )
				continue;

			ParamPair.second->SaveUniformLocation( *m_ShaderRef );
		}
	}

	void Material::DiscardSavedUniformsLocation()
	{
		if( m_Parameters.empty() )
			return;

		for( const std::pair<const std::string, ShaderParameter*>& ParamPair : m_Parameters )
		{
			if( ParamPair.second == nullptr )
				continue;

			ParamPair.second->DiscardSave();
		}
	}



	void Material::CopyMaterial( const Material& _Other )
	{
		RemoveAllParameters();

		if( !_Other.m_Parameters.empty() )
		{
			for( const std::pair<const std::string, ShaderParameter*>& ParamPair : _Other.m_Parameters )
			{
				if( ParamPair.second == nullptr )
					continue;

				ShaderParameter* NewParam = ParamPair.second->Clone();

				// The copy must be free manually, so tag it to be destroyed at the same time as the material.
				NewParam->SetIsDestroyedWithMaterial( True );

				// Put the new parameter in the material.
				m_Parameters.emplace( ParamPair.first, NewParam );
			}
		}

		SetShader( _Other.GetShader() );
		SetShadowMap( _Other.GetShadowMap() );
		SetNeedLights( _Other.NeedLights() );
		SetNeedCamera( _Other.NeedCamera() );
	}



	ShaderParameterFloat* Material::AddFloatParameterToMaterial( const std::string& _Name, const std::string& _UniformName, float _Value, float _Min, float _Max )
	{
		// Create the parameter, tag it to be freed at the same time as the material
		// since we lost its track at the end of the function.
		ShaderParameterFloat* NewParam = new ShaderParameterFloat( _Name, _UniformName, _Value );
		NewParam->SetIsDestroyedWithMaterial( True );
		NewParam->SetMin( _Min );
		NewParam->SetMax( _Max );

		// Add the parameter to the material.
		AddParameter( NewParam );

		return NewParam;
	}

	ShaderParameterInt* Material::AddIntParameterToMaterial( const std::string& _Name, const std::string& _UniformName, Int32 _Value, Int32 _Min, Int32 _Max )
	{
		// Create the parameter, tag it to be freed at the same time as the material
		// since we lost its track at the end of the function.
		ShaderParameterInt* NewParam = new ShaderParameterInt( _Name, _UniformName, _Value );
		NewParam->SetIsDestroyedWithMaterial( True );
		NewParam->SetMin( _Min );
		NewParam->SetMax( _Max );

		// Add the parameter to the material.
		AddParameter( NewParam );

		return NewParam;
	}

	ShaderParameterBool* Material::AddBoolParameterToMaterial( const std::string& _Name, const std::string& _UniformName, Bool _Value )
	{
		// Create the parameter, tag it to be freed at the same time as the material
		// since we lost its track at the end of the function.
		ShaderParameterBool* NewParam = new ShaderParameterBool( _Name, _UniformName, _Value );
		NewParam->SetIsDestroyedWithMaterial( True );

		// Add the parameter to the material.
		AddParameter( NewParam );

		return NewParam;
	}

	ShaderParameterColor* Material::AddColorParameterToMaterial( const std::string& _Name, const std::string& _UniformName, const Color& _Value )
	{
		// Create the parameter, tag it to be freed at the same time as the material
		// since we lost its track at the end of the function.
		ShaderParameterColor* NewParam = new ShaderParameterColor( _Name, _UniformName, _Value );
		NewParam->SetIsDestroyedWithMaterial( True );

		// Add the parameter to the material.
		AddParameter( NewParam );

		return NewParam;
	}


	ShaderParameter* Material::AddTextureParameterToMaterial( const std::string& _Name, const std::string& _UniformName, Texture* _Value, Bool _UseTextureBool )
	{
		ShaderParameter* NewParam = nullptr;

		// Create the parameter, tag it to be freed at the same time as the material
		// since we lost its track at the end of the function.
		if( _UseTextureBool )
			NewParam = new ShaderParameterTextureBool( _Name, _UniformName, _Value, std::string( "Use" ) + _UniformName );
		else
			NewParam = new ShaderParameterTexture( _Name, _UniformName, _Value );

		NewParam->SetIsDestroyedWithMaterial( True );

		// Add the parameter to the material.
		AddParameter( NewParam );

		return NewParam;
	}

	ShaderParameterTexture* Material::AddTextureParameterToMaterial( const std::string& _Name, const std::string& _UniformName, Texture* _Value )
	{
		// Create the parameter, tag it to be freed at the same time as the material
		// since we lost its track at the end of the function.
		ShaderParameterTexture* NewParam = new ShaderParameterTexture( _Name, _UniformName, _Value );
		NewParam->SetIsDestroyedWithMaterial( True );

		// Add the parameter to the material.
		AddParameter( NewParam );

		return NewParam;
	}

	ShaderParameter* Material::AddCubeMapParameterToMaterial( const std::string& _Name, const std::string& _UniformName, CubeMap* _Value, Bool _UseCubeMapBool )
	{
		ShaderParameter* NewParam = nullptr;

		// Create the parameter, tag it to be freed at the same time as the material
		// since we lost its track at the end of the function.
		if( _UseCubeMapBool )
			NewParam = new ShaderParameterCubeMapBool( _Name, _UniformName, _Value, std::string( "Use" ) + _UniformName );
		else
			NewParam = new ShaderParameterCubeMap( _Name, _UniformName, _Value );

		NewParam->SetIsDestroyedWithMaterial( True );

		// Add the parameter to the material.
		AddParameter( NewParam );

		return NewParam;
	}

	ShaderParameterCubeMap* Material::AddCubeMapParameterToMaterial( const std::string& _Name, const std::string& _UniformName, CubeMap* _Value )
	{
		// Create the parameter, tag it to be freed at the same time as the material
		// since we lost its track at the end of the function.
		ShaderParameterCubeMap* NewParam = new ShaderParameterCubeMap( _Name, _UniformName, _Value );
		NewParam->SetIsDestroyedWithMaterial( True );

		// Add the parameter to the material.
		AddParameter( NewParam );

		return NewParam;
	}

	ShaderParameterVector3* Material::AddVector3ParameterToMaterial( const std::string& _Name, const std::string& _UniformName, const Vector3& _Value )
	{
		// Create the parameter, tag it to be freed at the same time as the material
		// since we lost its track at the end of the function.
		ShaderParameterVector3* NewParam = new ShaderParameterVector3( _Name, _UniformName, _Value );
		NewParam->SetIsDestroyedWithMaterial( True );

		// Add the parameter to the material.
		AddParameter( NewParam );

		return NewParam;
	}

	ShaderParameterVector2* Material::AddVector2ParameterToMaterial( const std::string& _Name, const std::string& _UniformName, const Vector2& _Value )
	{
		// Create the parameter, tag it to be freed at the same time as the material
		// since we lost its track at the end of the function.
		ShaderParameterVector2* NewParam = new ShaderParameterVector2( _Name, _UniformName, _Value );
		NewParam->SetIsDestroyedWithMaterial( True );

		// Add the parameter to the material.
		AddParameter( NewParam );

		return NewParam;
	}

	ShaderParameterMatrix3x3* Material::AddMatrix3x3ParameterToMaterial( const std::string& _Name, const std::string& _UniformName, const Matrix3x3& _Value )
	{
		// Create the parameter, tag it to be freed at the same time as the material
		// since we lost its track at the end of the function.
		ShaderParameterMatrix3x3* NewParam = new ShaderParameterMatrix3x3( _Name, _UniformName, _Value );
		NewParam->SetIsDestroyedWithMaterial( True );

		// Add the parameter to the material.
		AddParameter( NewParam );

		return NewParam;
	}

	ShaderParameterMatrix4x4* Material::AddMatrix4x4ParameterToMaterial( const std::string& _Name, const std::string& _UniformName, const Matrix4x4& _Value )
	{
		// Create the parameter, tag it to be freed at the same time as the material
		// since we lost its track at the end of the function.
		ShaderParameterMatrix4x4* NewParam = new ShaderParameterMatrix4x4( _Name, _UniformName, _Value );
		NewParam->SetIsDestroyedWithMaterial( True );

		// Add the parameter to the material.
		AddParameter( NewParam );

		return NewParam;
	}


	void Material::SetShader( const Shader& _Shader )
	{
		m_ShaderRef = &_Shader;
		DiscardSavedUniformsLocation();
	}

	void Material::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::MaterialToEditor( *this );
	}

	void Material::SetShader( const Shader* _Shader )
	{
		m_ShaderRef = _Shader;
		DiscardSavedUniformsLocation();
	}

	const Shader* Material::GetShader() const
	{
		return m_ShaderRef;
	}

	Bool Material::IsInstance() const
	{
		return m_IsInstance;
	}

	void Material::SetIsInstance( Bool _IsInstance )
	{
		m_IsInstance = _IsInstance;
	}

	const ShadowMap* Material::GetShadowMap() const
	{
		return m_ShadowMapRef;
	}

	void Material::SetShadowMap( const ShadowMap* _ShadowMap )
	{
		m_ShadowMapRef = _ShadowMap;
	}

	Bool Material::HasShadowMap() const
	{
		return m_ShadowMapRef != nullptr;
	}

	void Material::SetNeedLights( Bool _NeedLights )
	{
		m_NeedLights = _NeedLights;
	}

	Bool Material::NeedLights() const
	{
		return m_NeedLights;
	}

	void Material::SetNeedCamera( Bool _NeedCamera )
	{
		m_NeedCamera = _NeedCamera;
	}

	Bool Material::NeedCamera() const
	{
		return m_NeedCamera;
	}

} // ae

#ifndef _MATERIAL_AERO_H_
#define _MATERIAL_AERO_H_

#include "../../Toolbox/Toolbox.h"
#include "../Color/Color.h"
#include "../Shader/Shader.h"
#include "../../Resources/Resource/Resource.h"

#include <unordered_map>
#include <array>
#include <string>

// Pre-declaration of Assimp material structure.
struct aiMaterial;

namespace ae
{
	class Texture;
	class CubeMap;
	class ShadowMap;

	class ShaderParameter;
	class ShaderParameterBool;
	class ShaderParameterColor;
	class ShaderParameterTexture;
	class ShaderParameterCubeMap;
	class ShaderParameterFloat;
	class ShaderParameterInt;
	class ShaderParameterMatrix3x3;
	class ShaderParameterMatrix4x4;
	class ShaderParameterVector2;
	class ShaderParameterVector3;


	/// \ingroup graphics
	/// <summary>Shading settings for rendering.</summary>
	class AERO_CORE_EXPORT Material : public Resource
	{
	public:
		/// <summary>
		/// List of parameters used for default shaders shipped with the engine.<para/>
		/// For the 3D parameters, it is also the supported attributes when loading models.
		/// </summary>
		enum class DefaultParameters : Uint8
		{
			// 3D : Blinn-Phong / PBR

			/// <summary>Float parameter for shininess.</summary>
			Shininess,
			/// <summary>Float parameter for reflectivity.</summary>
			Reflectivity,
			/// <summary>Float parameter for refraction.</summary>
			Refraction,
			/// <summary>Color parameter for diffuse color.</summary>
			DiffuseColor,
			/// <summary>Color parameter for ambient color.</summary>
			AmbientColor,
			/// <summary>Float parameter for ambient strength texture.</summary>
			AmbientStrength,
			/// <summary>Color parameter for specular color.</summary>
			SpecularColor,
			/// <summary>Color parameter for emissive color.</summary>
			EmissiveColor,
			/// <summary>Color parameter for reflective color.</summary>
			ReflectiveColor,
			/// <summary>Texture parameter for diffuse texture.</summary>
			DiffuseTexture,
			/// <summary>Texture parameter for specular texture.</summary>
			SpecularTexture,
			/// <summary>Texture parameter for ambient texture.</summary>
			AmbientTexture,
			/// <summary>Texture parameter for emissive texture.</summary>
			EmissiveTexture,
			/// <summary>Texture parameter for height texture.</summary>
			HeightTexture,
			/// <summary>Texture parameter for normal texture.</summary>
			NormalTexture,
			/// <summary>Texture parameter for shininess texture.</summary>
			ShininessTexture,
			/// <summary>Texture parameter for displacement texture.</summary>
			DisplacementTexture,
			/// <summary>Texture parameter for light map texture.</summary>
			LightMapTexture,
			/// <summary>Texture parameter for reflection texture.</summary>
			ReflectionTexture,

			/// <summary>Color parameter for PBR base color.</summary>
			PBR_BaseColor,
			/// <summary>Color parameter for PBR base color.</summary>
			PBR_EmissionColor,
			/// <summary>Float parameter for PBR metalness.</summary>
			PBR_Metalness,
			/// <summary>Float parameter for PBR roughness.</summary>
			PBR_Roughness,
			/// <summary>Float parameter for PBR ambien occlusion.</summary>
			PBR_AmbientOcclusion,
			/// <summary>Texture parameter for PBR base color texture.</summary>
			PBR_BaseColorTexture,
			/// <summary>Texture parameter for PBR normal camera texture.</summary>
			PBR_NormalCameraTexture,
			/// <summary>Texture parameter for PBR emissive color texture.</summary>
			PBR_EmissionColorTexture,
			/// <summary>Texture parameter for PBR metalness texture.</summary>
			PBR_MetalnessTexture,
			/// <summary>Texture parameter for PBR roughness texture.</summary>
			PBR_RoughnessTexture,
			/// <summary>Texture parameter for PBR ambient occlusion texture.</summary>
			PBR_AmbientOcclusionTexture,

			/// <summary>Boolean parameter to tell the shader if it must use the irradiance and radiance map for image based lighting.</summary>
			IBL_UseIBL,
			/// <summary>Cube map parameter for the irradiance map to use for the image based lighting.</summary>
			IBL_IrradianceMap,
			/// <summary>Cube map parameter for the radiance map to use for the image based lighting.</summary>
			IBL_RadianceMap,
			/// <summary>Texture parameter for the LUT of the BRDF to use for the image based lighting.</summary>
			IBL_BRDFLut,
			/// <summary>Integer parameter for the maximum level of mip map for the radiance map to use for the image based lighting.</summary>
			IBL_MaxLod,


			/// <summary>Boolean parameter to the shader if it must convert the linear color result to sRGB.</summary>
			HDR_ApplyGammaCorrection,


			/// <summary>Texture parameter for 2D default shader.</summary>
			SpriteTexture,

			/// <summary>Texture parameter for framebuffer default shader.</summary>
			FramebufferTexture,

			/// <summary>Texture parameter for framebuffer default shader.</summary>
			FramebufferIsDepth,

			/// <summary>Matrix 3x3 parameter for model transformation for 2D default shader.</summary>
			Model2DMatrix,

			/// <summary>Matrix 4x4 parameter for model transformation for 3D default shader.</summary>
			Model3DMatrix,

			/// <summary>Matrix 4x4 parameter for view matrix for 3D default shader.</summary>
			ViewMatrix,
			/// <summary>Matrix 4x4 parameter for projection matrix for 3D default shader.</summary>
			ProjectionMatrix,
			/// <summary>Vector 3D parameter for camera position matrix for 3D default shader.</summary>
			CameraPosition,
			/// <summary>Float parameter for near distance of the camera.</summary>
			CameraNear,
			/// <summary>Float parameter for far distance of the camera.</summary>
			CameraFar,
			/// <summary>Vector 2D parameter for camera viewport size.</summary>
			CameraViewportSize,

			/// <summary>Array of point light struct for 3D default shader.</summary>
			PointLights,
			/// <summary>Array of spot light struct for 3D default shader.</summary>
			SpotLights,
			/// <summary>Array of directional light struct for 3D default shader.</summary>
			DirectionalLights,
			/// <summary>Integer parameter for point light count for 3D default shader.</summary>
			PointLightsCount,
			/// <summary>Integer parameter for point light count for 3D default shader.</summary>
			SpotLightsCount,
			/// <summary>Integer parameter for point light count for 3D default shader.</summary>
			DirectionalLightsCount,

			/// <summary>Cube map parameter for default skybox shader.</summary>
			Skybox_CubeMap,

			// Toon

			/// <summary>Color parameter for the rim color of the default toon shader.</summary>
			Toon_RimColor,
			/// <summary>Float parameter for the rim size of the default toon shader.</summary>
			Toon_RimSize,
			/// <summary>Float parameter for the rim threshold of the default toon shader.</summary>
			Toon_RimThreshold,


			// Shadow map.

			/// <summary>Matrix 4x4 parameter for light view matrix in default shadow map shader.</summary>
			ShadowMap_ViewMatrix,

			/// <summary>Matrix 4x4 parameter for light projection matrix in default shadow map shader.</summary>
			ShadowMap_ProjectionMatrix,

			/// <summary>Vector 3D parameter for light position in default shadow map shader.</summary>
			ShadowMap_LightPosition,

			/// <summary>Texture parameter for shadow map texture in default 3D shader.</summary>
			ShadowMap_Texture,

			/// <summary>Cube map parameter for omnidirectional shadow map texture in default 3D shader.</summary>
			ShadowMap_TextureOmni,

			/// <summary>Boolean parameter for letting know in default 3D shader if it must use the 2D shadow map or the cube map one.</summary>
			ShadowMap_IsOmni,

			/// <summary>Boolean parameter for letting know in default 3D shader if it must filter the shadow.</summary>
			ShadowMap_UsePCF,

			/// <summary>Float parameter for the radius of the PCF filter in the default 3D shader. Affect only omnidirectional shadow map.</summary>
			ShadowMap_OmniPCFRadius,

			/// <summary>Float parameter for shadow bias in default 3D shader.</summary>
			ShadowMap_Bias,

			/// <summary>Float parameter for shadow far distance in default omnidirectional shadow map shader.</summary>
			ShadowMap_Far,

			/// <summary>Boolean parameter for letting know in default 3D shader if it must process the shadow map.</summary>
			ShadowMap_HasShadowMap,

			/// <summary>Color paramter for setting the control curve color in the default curve shader.</summary>
			Curve_ControlColor,

			/// <summary>Color paramter for setting the curve color in the default curve shader.</summary>
			Curve_Color,

			/// <summary>Boolean paramter for letting if the default curve shader must draw the control curve.</summary>
			Curve_DrawControlCurve,

			/// <summary>Boolean paramter for letting if the default curve shader must draw the curve.</summary>
			Curve_DrawCurve,

			Count
		};

		/// <summary>
		/// Name of the default parameters.<para/>
		/// If these parameters are present in the shader the name and the uniform name are the same.<para/>
		/// For the texture/bool parameters, the name of the boolean uniform has the same name but with "Use" at the beginning.
		/// </summary>
		static const std::array<std::string, Cast( size_t, DefaultParameters::Count )> DefaultParametersNames;

	public:
		/// <summary>Default material.</summary>
		Material();

		/// <summary>Create a material with shader to use when rendering object with this material.</summary>
		/// <param name="_Shader">Shader to use with this material.</param>
		Material( const Shader& _Shader );

		/// <summary>
		/// Copy the material into the calling one.<para/>
		/// The shader parameters are duplicated and their memory managed by the material.
		/// </summary>
		/// <param name="_Other">Other material to copy.</param>
		Material( const Material& _Other );

		/// <summary>
		/// Copy the material into the calling one.<para/>
		/// The shader parameters are duplicated and their memory managed by the material.
		/// </summary>
		/// <param name="_Other">Other material to copy.</param>
		/// <returns>The calling material after the copy.</returns>
		Material& operator=( const Material& _Other );

		/// <summary>
		/// Add a shader parameter to the material.<para/>
		/// If a parameter with the same name exists, the stored one will be removed  (and freed if it's managed by material)
		/// and replaced with <paramref name="_Parameter"/>.
		/// </summary>
		/// <param name="_Parameter">The new parameter to send to the shader.</param>
		void AddParameter( ShaderParameter* _Parameter );

		/// <summary>Remove a parameter from the material.</summary>
		/// <param name="_ParameterName">The name of the parameter to remove from the material.</param>
		void RemoveParameter( const std::string& _ParameterName );

		/// <summary>Remove all the parameters from the material.</summary>
		void RemoveAllParameters();

		/// <summary>
		/// Retrieve all parameters available in the material.
		/// </summary>
		/// <returns>The map with all the parameters.</returns>
		const std::unordered_map<std::string, ShaderParameter*>& GetAllParameters() const;

		/// <summary>
		/// Retrieve begin of the map containing the parameters.<para/>
		/// Editor purpose.
		/// </summary>
		/// <returns>Iterator on the begin of the map containing the parameters.</returns>
		std::unordered_map<std::string, ShaderParameter*>::iterator begin();

		/// <summary>
		/// Retrieve end of the map containing the parameters.<para/>
		/// Editor purpose.
		/// </summary>
		/// <returns>Iterator on the end of the map containing the parameters.</returns>
		std::unordered_map<std::string, ShaderParameter*>::iterator end();

		/// <summary>
		/// Send all the parameters stored in the material to the shader.
		/// The shader must be bound before calling this function.<para/>
		/// The texture unit is used with parameter that correspond to sampler uniforms.<para/>
		/// For texture parameters, the texture unit is activated, incremented then the texture is bound.
		/// </summary>
		/// <param name="_Shader">Shader to send the parameters to.</param>
		/// <param name="_TextureUnit">Texture unit to use with texture parameters bound as texture. Incremented for each texture sent.</param>
		/// <param name="_ImageUnit">Image unit to use with texture parameters bound as image. Incremented for each image sent.</param>
		void SendParametersToShader( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& _ImageUnit ) const;

		/// <summary>
		/// Called after a draw call.<para/>
		/// Give the possibility to reset parameters or unbind texture after the draw call.
		/// </summary>
		/// <param name="_Shader">The target shader for the parameter.</param>
		/// <param name="_TextureUnit">The target sampler unit in the shader for the parameter.</param>
		/// <param name="_ImageUnit">The target image unit in the shader for the parameter.</param>
		void Clean( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& _ImageUnit ) const;

		/// <summary>
		/// Retrieve a parameter with the given <paramref name="_Name"/> in the material.<para/>
		/// Return nullptr if the parameter is not found.
		/// </summary>
		/// <param name="_Name">Name of the shader parameter to retrieve.</param>
		/// <returns>Pointer of the found parameter. Nullptr if not found.</returns>
		ShaderParameter* GetParameter( const std::string& _Name );

		/// <summary>
		/// Retrieve a parameter with the given <paramref name="_Name"/> in the material.<para/>
		/// Return nullptr if the parameter is not found.
		/// </summary>
		/// <param name="_Name">Name of the shader parameter to retrieve.</param>
		/// <returns>Pointer of the found parameter. Nullptr if not found.</returns>
		const ShaderParameter* GetParameter( const std::string& _Name ) const;


		/// <summary>
		/// Retrieve a parameter with the given <paramref name="_Name"/> in the material.<para/>
		/// Try to cast the parameter to the given type in tempalte parameter.<para/>
		/// The template parameter type must inherits from ShaderParameter.<para/>
		/// Return nullptr if the parameter is not found or the cast failed.<para/>
		/// Be careful the cast can be quite expensive.
		/// </summary>
		/// <param name="_Name">Name of the shader parameter to retrieve.</param>
		/// <returns>Pointer of the found parameter. Nullptr if not found or if cast failed.</returns>
		template<typename ParameterType>
		ParameterType* GetParameter( const std::string& _Name )
		{
			return dynamic_cast<ParameterType*>( GetParameter( _Name ) );
		}

		/// <summary>
		/// Retrieve a parameter with the given <paramref name="_Name"/> in the material.<para/>
		/// Try to cast the parameter to the given type in tempalte parameter.<para/>
		/// The template parameter type must inherits from ShaderParameter.<para/>
		/// Return nullptr if the parameter is not found or the cast failed.<para/>
		/// Be careful the cast can be quite expensive.
		/// </summary>
		/// <param name="_Name">Name of the shader parameter to retrieve.</param>
		/// <returns>Pointer of the found parameter. Nullptr if not found or if cast failed.</returns>
		template<typename ParameterType>
		const ParameterType* GetParameter( const std::string& _Name ) const
		{
			return dynamic_cast<const ParameterType*>( GetParameter( _Name ) );
		}


		/// <summary>
		/// Retrieve a parameter with the given <paramref name="_DefaultParameter"/> name in the material.
		/// Return nullptr if the parameter is not found.
		/// </summary>
		/// <param name="_DefaultParameter">Name of the default parameter to retrieve.</param>
		/// <returns>Pointer of the found parameter. Nullptr if not found.</returns>
		ShaderParameter* GetParameter( DefaultParameters _DefaultParameter );

		/// <summary>
		/// Retrieve a parameter with the given <paramref name="_DefaultParameter"/> name in the material.
		/// Return nullptr if the parameter is not found.
		/// </summary>
		/// <param name="_DefaultParameter">Name of the default parameter to retrieve.</param>
		/// <returns>Pointer of the found parameter. Nullptr if not found.</returns>
		const ShaderParameter* GetParameter( DefaultParameters _DefaultParameter ) const;


		/// <summary>
		/// Retrieve a parameter with the given <paramref name="_DefaultParameter"/> name in the material.
		/// Try to cast the parameter to the given type in tempalte parameter.<para/>
		/// The template parameter type must inherits from ShaderParameter.<para/>
		/// Return nullptr if the parameter is not found or the cast failed.<para/>
		/// Be careful the cast can be quite expensive.
		/// </summary>
		/// <param name="_DefaultParameter">Name of the default parameter to retrieve.</param>
		/// <returns>Pointer of the found parameter. Nullptr if not found or if cast failed.</returns>
		template<typename ParameterType>
		ParameterType* GetParameter( DefaultParameters _DefaultParameter )
		{
			return dynamic_cast<ParameterType*>( GetParameter( _DefaultParameter ) );
		}

		/// <summary>
		/// Retrieve a parameter with the given <paramref name="_DefaultParameter"/> name in the material.
		/// Try to cast the parameter to the given type in tempalte parameter.<para/>
		/// The template parameter type must inherits from ShaderParameter.<para/>
		/// Return nullptr if the parameter is not found or the cast failed.<para/>
		/// Be careful the cast can be quite expensive.
		/// </summary>
		/// <param name="_DefaultParameter">Name of the default parameter to retrieve.</param>
		/// <returns>Pointer of the found parameter. Nullptr if not found or if cast failed.</returns>
		template<typename ParameterType>
		const ParameterType* GetParameter( DefaultParameters _DefaultParameter ) const
		{
			return dynamic_cast<const ParameterType*>( GetParameter( _DefaultParameter ) );
		}


		/// <summary>
		/// Get the name of a default parameter from the enum list of supported parameters.<para/>
		/// If these parameters are present in the shader the name and the uniform name are the same.<para/>
		/// For the texture/bool parameters, the name of the boolean uniform has the same name but with "Use" at the beginning.
		/// </summary>
		/// <param name="_DefaultParameter">The default parameter to retrieve the name of.</param>
		/// <returns>The default parameter name.</returns>
		static const std::string& GetDefaultParameterName( DefaultParameters _DefaultParameter );


		/// <summary>
		/// Add a float parameter with the given <paramref name="_Name"/> to the material.<para/>
		/// The parameter will be automatically destroyed with the material.
		/// </summary>
		/// <param name="_Name">Name of the parameter.</param>
		/// <param name="_UniformName">Name of the corresponding uniform in the shader.</param>
		/// <param name="_Value">Value of the parameter.</param>
		/// <param name="_Min">Minimum for the <paramref name="_Value"/>.</param>
		/// <param name="_Max">Maximum for the <paramref name="_Value"/>.</param>
		/// <returns>Pointer on the new parameter.</returns>
		ShaderParameterFloat* AddFloatParameterToMaterial( const std::string& _Name, const std::string& _UniformName, float _Value, float _Min = std::numeric_limits<float>::min(), float _Max = std::numeric_limits<float>::max() );

		/// <summary>
		/// Add a integer parameter with the given <paramref name="_Name"/> to the material.<para/>
		/// The parameter will be automatically destroyed with the material.
		/// </summary>
		/// <param name="_Name">Name of the parameter.</param>
		/// <param name="_UniformName">Name of the corresponding uniform in the shader.</param>
		/// <param name="_Value">Value of the parameter.</param>
		/// <param name="_Min">Minimum for the <paramref name="_Value"/>.</param>
		/// <param name="_Max">Maximum for the <paramref name="_Value"/>.</param>
		/// <returns>Pointer on the new parameter.</returns>
		ShaderParameterInt* AddIntParameterToMaterial( const std::string& _Name, const std::string& _UniformName, Int32 _Value, Int32 _Min = std::numeric_limits<Int32>::min(), Int32 _Max = std::numeric_limits<Int32>::max() );

		/// <summary>
		/// Add a boolean parameter with the given <paramref name="_Name"/> to the material.<para/>
		/// The parameter will be automatically destroyed with the material.
		/// </summary>
		/// <param name="_Name">Name of the parameter.</param>
		/// <param name="_UniformName">Name of the corresponding uniform in the shader.</param>
		/// <param name="_Value">Value of the parameter.</param>
		/// <returns>Pointer on the new parameter.</returns>
		ShaderParameterBool* AddBoolParameterToMaterial( const std::string& _Name, const std::string& _UniformName, Bool _Value );

		/// <summary>
		/// Add a color parameter with the given <paramref name="_Name"/> to the material. <para/>
		/// The parameter will be automatically destroyed with the material.
		/// </summary>
		/// <param name="_Name">Name of the parameter.</param>
		/// <param name="_UniformName">Name of the corresponding uniform in the shader.</param>
		/// <param name="_Value">Value of the parameter.</param>
		/// <returns>Pointer on the new parameter.</returns>
		ShaderParameterColor* AddColorParameterToMaterial( const std::string& _Name, const std::string& _UniformName, const Color& _Value );

		/// <summary>
		/// Add a texture/bool parameter with the given <paramref name="_Name"/> to the material. <para/>
		/// The parameter will be automatically destroyed with the material.
		/// </summary>
		/// <param name="_Name">Name of the parameter.</param>
		/// <param name="_UniformName">Name of the corresponding uniform in the shader.</param>
		/// <param name="_Value">Value of the parameter.</param>
		/// <param name="_UseTextureBool">Use Texture/Bool parameter or simple texture parameter ?</param>
		/// <returns>Pointer on the new parameter. Type : ShaderParameterTexture if <paramref name="_UseTextureBool"/> is set to false ShaderParameterTextureBool otherwise.</returns>
		ShaderParameter* AddTextureParameterToMaterial( const std::string& _Name, const std::string& _UniformName, Texture* _Value, Bool _UseTextureBool );

		/// <summary>
		/// Add a texture parameter with the given <paramref name="_Name"/> to the material. <para/>
		/// The parameter will be automatically destroyed with the material.
		/// </summary>
		/// <param name="_Name">Name of the parameter.</param>
		/// <param name="_UniformName">Name of the corresponding uniform in the shader.</param>
		/// <param name="_Value">Value of the parameter.</param>
		/// <returns>Pointer on the new parameter.</returns>
		ShaderParameterTexture* AddTextureParameterToMaterial( const std::string& _Name, const std::string& _UniformName, Texture* _Value );

		/// <summary>
		/// Add a cubeMap/bool parameter with the given <paramref name="_Name"/> to the material. <para/>
		/// The parameter will be automatically destroyed with the material.
		/// </summary>
		/// <param name="_Name">Name of the parameter.</param>
		/// <param name="_UniformName">Name of the corresponding uniform in the shader.</param>
		/// <param name="_Value">Value of the parameter.</param>
		/// <param name="_UseCubeMapBool">Use CubeMap/Bool parameter or simple texture parameter ?</param>
		/// <returns>Pointer on the new parameter. Type : ShaderParameterCubeMap if <paramref name="_UseTextureBool"/> is set to false ShaderParameterCubeMapBool otherwise.</returns>
		ShaderParameter* AddCubeMapParameterToMaterial( const std::string& _Name, const std::string& _UniformName, CubeMap* _Value, Bool _UseCubeMapBool );

		/// <summary>
		/// Add a cubeMap parameter with the given <paramref name="_Name"/> to the material. <para/>
		/// The parameter will be automatically destroyed with the material.
		/// </summary>
		/// <param name="_Name">Name of the parameter.</param>
		/// <param name="_UniformName">Name of the corresponding uniform in the shader.</param>
		/// <param name="_Value">Value of the parameter.</param>
		/// <returns>Pointer on the new parameter</returns>
		ShaderParameterCubeMap* AddCubeMapParameterToMaterial( const std::string& _Name, const std::string& _UniformName, CubeMap* _Value );

		/// <summary>
		/// Add a 3D vector parameter with the given <paramref name="_Name"/> to the material. <para/>
		/// The parameter will be automatically destroyed with the material.
		/// </summary>
		/// <param name="_Name">Name of the parameter.</param>
		/// <param name="_UniformName">Name of the corresponding uniform in the shader.</param>
		/// <param name="_Value">Value of the parameter.</param>
		/// <returns>Pointer on the new parameter.</returns>
		ShaderParameterVector3* AddVector3ParameterToMaterial( const std::string& _Name, const std::string& _UniformName, const Vector3& _Value );

		/// <summary>
		/// Add a 2D vector parameter with the given <paramref name="_Name"/> to the material. <para/>
		/// The parameter will be automatically destroyed with the material.
		/// </summary>
		/// <param name="_Name">Name of the parameter.</param>
		/// <param name="_UniformName">Name of the corresponding uniform in the shader.</param>
		/// <param name="_Value">Value of the parameter.</param>
		/// <returns>Pointer on the new parameter.</returns>
		ShaderParameterVector2* AddVector2ParameterToMaterial( const std::string& _Name, const std::string& _UniformName, const Vector2& _Value );

		/// <summary>
		/// Add a 3x3 matrix parameter with the given <paramref name="_Name"/> to the material. <para/>
		/// The parameter will be automatically destroyed with the material.
		/// </summary>
		/// <param name="_Name">Name of the parameter.</param>
		/// <param name="_UniformName">Name of the corresponding uniform in the shader.</param>
		/// <param name="_Value">Value of the parameter.</param>
		/// <returns>Pointer on the new parameter.</returns>
		ShaderParameterMatrix3x3* AddMatrix3x3ParameterToMaterial( const std::string& _Name, const std::string& _UniformName, const Matrix3x3& _Value );

		/// <summary>
		/// Add a 4x4 matrix parameter with the given <paramref name="_Name"/> to the material. <para/>
		/// The parameter will be automatically destroyed with the material.
		/// </summary>
		/// <param name="_Name">Name of the parameter.</param>
		/// <param name="_UniformName">Name of the corresponding uniform in the shader.</param>
		/// <param name="_Value">Value of the parameter.</param>
		/// <returns>Pointer on the new parameter.</returns>
		ShaderParameterMatrix4x4* AddMatrix4x4ParameterToMaterial( const std::string& _Name, const std::string& _UniformName, const Matrix4x4& _Value );

		/// <summary>
		/// Retrieve and save the material shader parameters uniform locations.<para/>
		/// That can allow to save some time during rendering.<para/>
		/// Has no effect if the ShaderRef member is not set.
		/// </summary>
		void SaveUniformsLocation();

		/// <summary>Remove the uniforms location saved from the parameters.</summary>
		void DiscardSavedUniformsLocation();


		/// <summary>Set the shader to use for this material.</summary>
		/// <param name="_Shader">The new shader to use.</param>
		void SetShader( const Shader& _Shader );

		/// <summary>Retrieve the shader that this material is using.</summary>
		/// <returns>The shader that the material is using. Can be null.</returns>
		const Shader* GetShader() const;

		/// <summary>Is the material has been created by the drawable that hold it ?</summary>
		/// <returns>True if the material is an instance, False otherwise.</returns>
		Bool IsInstance() const;

		/// <summary>Tag the material as instance if it was created by the drawable that hold it.</summary>
		/// <param name="_IsInstance">True to tag the material as instance, False otherwise.</param>
		void SetIsInstance( Bool _IsInstance );

		/// <summary>Retrieve the current shadow map of the material. Can be null.</summary>
		/// <returns>The current shadow map of the material.</returns>
		const ShadowMap* GetShadowMap() const;

		/// <summary>
		/// Apply a shadow map to process objects shadows.<para/>
		/// If null, the objects with this materials will no longer cast shadows.
		/// </summary>
		/// <param name="_ShadowMap"></param>
		void SetShadowMap( const ShadowMap* _ShadowMap );

		/// <summary>Has the material a shadow map ?</summary>
		/// <returns>True if the material has a shadow map, False otherwise.</returns>
		Bool HasShadowMap() const;


		/// <summary>Is the material shader need the world lights data ?</summary>
		/// <param name="_NeedLights">Is the material shader need the world lights data ?</param>
		void SetNeedLights( Bool _NeedLights );

		/// <summary>Is the material shader need the world lights data ?</summary>
		/// <returns>Is the material shader need the world lights data ?</returns>
		Bool NeedLights() const;

		/// <summary>Is the material shader need the camera data ?</summary>
		/// <param name="_NeedCamera">Is the material shader need the camera data ?</param>
		void SetNeedCamera( Bool _NeedCamera );

		/// <summary>Is the material shader need the camera data ?</summary>
		/// <returns>Is the material shader need the camera data ?</returns>
		Bool NeedCamera() const;

		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		void ToEditor() override;

	protected:
		/// <summary>Set the shader to use for this material.</summary>
		/// <param name="_Shader">The new shader to use.</param>
		void SetShader( const Shader* _Shader );

	private:
		/// <summary>
		/// Copy the material into the calling one.<para/>
		/// The shader parameters are duplicated and their memory managed by the material.
		/// </summary>
		/// <param name="_Other">Other material to copy.</param>
		void CopyMaterial( const Material& _Other );


	private:
		/// <summary>Shader to use when rendering.</summary>
		const Shader* m_ShaderRef;

		/// <summary>Shader parameters (uniforms).</summary>
		std::unordered_map<std::string, ShaderParameter*> m_Parameters;

		/// <summary>Is the material has been created by the drawable that hold it ?</summary>
		Bool m_IsInstance;

		/// <summary>Shadow map to use in case of shadow caster objects.</summary>
		const ShadowMap* m_ShadowMapRef;

		/// <summary>Must the renderer send the world lights to the material shader ?</summary>
		Bool m_NeedLights;

		/// <summary>Must the renderer send the camera data (matrices, far, near, position, ...) to the material shader ?</summary>
		Bool m_NeedCamera;
	};
} // ae

#endif // _MATERIAL_AERO_H_
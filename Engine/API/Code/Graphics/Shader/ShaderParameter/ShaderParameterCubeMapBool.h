#pragma once

#include "../../../Toolbox/Toolbox.h"

#include "ShaderParameter.h"

namespace ae
{
	class Shader;
	class CubeMap;

	/// \ingroup graphics
	/// <summary>
	/// Shader parameter for cube map uniforms.
	/// </summary>
	/// <seealso cref="Shader"/>
	/// <seealso cref="Material"/>
	/// <seealso cref="ShaderParameter"/>
	/// <seealso cref="CubeMap"/>
	class AERO_CORE_EXPORT ShaderParameterCubeMapBool : public ShaderParameter
	{
	public:
		/// <summary>
		/// Build the parameter with the key to find in the material and the uniform name
		/// to find it in the shader, and optionnaly a default value.
		/// </summary>
		/// <param name="_Name">
		/// Name of the parameter.<para/>
		/// Used as key to find it in the material.
		/// </param>
		/// <param name="_UniformCubeMapName">Name of the cube map texture parameter in the shader.</param>
		/// <param name="_CubeMap">Value for the texture parameter.</param>
		/// <param name="_UniformBoolName">Name of the parameter in the shader for the boolean parameter that tell if the texture is valid.</param>
		explicit ShaderParameterCubeMapBool( const std::string& _Name,
											 const std::string& _UniformCubeMapName, const CubeMap* _CubeMap,
											 const std::string& _UniformBoolName );

		/// <summary>Apply a new value for the cube map parameter.</summary>
		/// <param name="_Value">The new value of the cube map parameter.</param>
		void SetCubeMap( const CubeMap* _Value );

		/// <summary>Operator to set the cube map value.</summary>
		/// <param name="_Value">The new value for the parameter.</param>
		/// <returns>The parameter with the new value applied.</returns>
		ShaderParameter& operator=( const CubeMap* _Value );

		/// <summary>Retrieve the current value of the parameter.</summary>
		/// <returns>The value of the parameter.</returns>
		const CubeMap* GetCubeMap() const;

		/// <summary>Retrieve the current value of the boolean parameter that tell if the cube map is valid.</summary>
		/// <returns>The value of the parameter.</returns>
		Bool IsCubeMapValid() const;

		/// <summary>
		/// Retrieve the name of the uniform that tell if the cube map is valid or not.
		/// </summary>
		/// <returns>The name of the boolean uniform.</returns>
		const std::string& GetUniformNameBool() const;

		/// <summary>
		/// Set the name of the uniform in the shader that tell if the cube map is valid or not.
		/// </summary>
		/// <param name="_Name">The new name of the boolean uniform.</param>
		void SetUniformNameBool( const std::string& _Name );

		/// <summary>
		/// Retrive the location of the boolean uniform that tell if the cube map is valid or not.
		/// </summary>
		/// <returns>The location of the boolean uniform.</returns>
		Int32 GetUniformLocationBool( const Shader& _Shader ) const;

		/// <summary>
		/// Store the uniform location to save some rendering time.<para/>
		/// It allow to avoid fecthing the uniform location at each draw call.<para/>
		/// The uniform name must be set before calling this function !
		/// </summary>
		/// <param name="_Shader">The shader to search the uniform location into.</param>
		void SaveUniformLocation( const Shader& _Shader ) override final;

		/// <summary>
		/// Send the parameter to the shader.<para/>
		/// The shader must be bound before calling this function.<para/>
		/// The texture unit is used with parameter that correspond to sampler uniforms.<para/>
		/// For texture parameters, the texture unit is activated, incremented then the texture is bound.
		/// </summary>
		/// <param name="_Shader">The target shader for the parameter.</param>
		/// <param name="_TextureUnit">The target sampler unit in the shader for the parameter.</param>
		/// <param name="_ImageUnit">The target image unit in the shader for the parameter.</param>
		void SendToShader( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& _ImageUnit ) override final;

		/// <summary>
		/// Called after a draw call.<para/>
		/// Give the possibility to reset parameters or unbind texture after the draw call.
		/// </summary>
		/// <param name="_Shader">The target shader for the parameter.</param>
		/// <param name="_TextureUnit">The target sampler unit in the shader for the parameter.</param>
		/// <param name="_ImageUnit">The target image unit in the shader for the parameter.</param>
		void Clean( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& _ImageUnit ) override final;

		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		void ToEditor() override final;

		/// <summary>
		/// Clone the parameter.<para/>
		/// The pointer on the clone must be freed manually.
		/// </summary>
		/// <returns>A pointer on the cloned parameter.</returns>
		ShaderParameterCubeMapBool* Clone() const override final;

	private:
		/// <summary>Value of the cube map parameter.</summary>
		const CubeMap* m_CubeMap;

		/// <summary>Name of the uniform that tell if the cube map is valid or not.</summary>
		std::string m_UniformNameBool;

		/// <summary>Saved location of the boolean uniform in the shader.</summary>
		Int32 m_UniformLocationBool;
	};
} // ae

#pragma once

#include "../../../Toolbox/Toolbox.h"

#include <string>

namespace ae
{
	class Shader;

	/// \ingroup graphics
	/// <summary>
	/// Top class for shader parameters.<para/>
	/// Sub class will allow the user to add custom uniform settings.<para/>
	/// The uniform must exists in the shader, otherwise, the rendering will prone errors.
	/// </summary>
	/// <seealso cref="Shader"/>
	/// <seealso cref="Material"/>
	class AERO_CORE_EXPORT ShaderParameter
	{
	public:
		/// <summary>
		/// Build the top class of parameter with the key to find in the material and the uniform name
		/// to find it in the shader.
		/// </summary>
		/// <param name="_Name">
		/// Name of the parameter.<para/>
		/// Used as key to find it in the material.
		/// </param>
		/// <param name="_UniformName">Name of the parameter in the shader.</param>
		explicit ShaderParameter( const std::string& _Name, const std::string& _UniformName );

		/// <summary>
		/// Default destructor.<para/>
		/// Written for inheritance purpose.
		/// </summary>
		virtual ~ShaderParameter() = default;

		/// <summary>
		/// Retrieve the name of the parameter.<para/>
		/// Used as key to find it in the material.
		/// </summary>
		/// <returns>The name of the parameter.</returns>
		const std::string& GetName() const;


		/// <summary>Retrieve the name of the parameter in the shader.</summary>
		/// <returns>The name of the parameter in the shader.</returns>
		const std::string& GetUniformName() const;

		/// <summary>
		/// Set the name that correspond to this parameter in the shader.<para/>
		/// If the uniform location was saved, you'll have to recall the save to
		/// retrieve the location of the uniform with the new name.<para/>
		/// This function discard automatically the save.
		/// </summary>
		/// <param name="_Name">The name in the shader that correspond to this parameter.</param>
		void SetUniformName( const std::string& _Name );

		/// <summary>
		/// Store the uniform location to save some rendering time.<para/>
		/// It allow to avoid fecthing the uniform location at each draw call.<para/>
		/// The uniform name must be set before calling this function !
		/// </summary>
		/// <param name="_Shader">The shader that search the uniform location into.</param>
		virtual void SaveUniformLocation( const Shader& _Shader );

		/// <summary>Remove the saved location of the parameter.</summary>
		void DiscardSave();

		/// <summary>The uniform location has been saved ?</summary>
		/// <returns>True if the uniform location has been saved, False otherwise.</returns>
		Bool IsSaved() const;

		/// <summary>Is the parameter is visible in the editor ?</summary>
		/// <returns>True if the parameter is visible in the editor, False otherwise.</returns>
		Bool IsEditable() const;

		/// <summary>Specify if the parameter can be visible in the editor or not.</summary>
		/// <param name="_IsEditable">True if the parameter must be visible in the editor, False otherwise.</param>
		void SetEditable( Bool _IsEditable );

		/// <summary>
		/// If set to true, when the material that store this parameter is destroyed,
		/// the parameter will be freed too.
		/// </summary>
		/// <param name="_IsDestroyedWithMaterial">
		/// If set to true, when the material that store this parameter is destroyed,
		/// the parameter will be freed too.
		/// </param>
		void SetIsDestroyedWithMaterial( Bool _IsDestroyedWithMaterial );

		/// <summary>
		/// If set to true, when the material that store this parameter is destroyed,
		/// the parameter will be freed too.
		/// </summary>
		/// <returns>
		/// If set to true, when the material that store this parameter is destroyed,
		/// the parameter will be freed too.
		/// </returns>
		Bool IsDestroyedWithMaterial() const;

		/// <summary>
		/// Get the uniform location of the parameter.<para/>
		/// If the uniform is saved, the saved one is returned. <para/>
		/// Otherwise the location is asked to the <paramref name="_Shader"/>.<para/>
		/// </summary>
		/// <param name="_Shader">The shader to ask the uniform to if it is not saved.</param>
		/// <returns>The location of the parameter in the shader.</returns>
		Int32 GetUniformLocation( const Shader& _Shader ) const;

		/// <summary>
		/// Send the parameter to the shader.<para/>
		/// The shader must be bound before calling this function.<para/>
		/// The texture unit is used with parameter that correspond to sampler uniforms.<para/>
		/// For texture parameters, the texture unit is activated, incremented then the texture is bound.
		/// </summary>
		/// <param name="_Shader">The target shader for the parameter.</param>
		/// <param name="_TextureUnit">The target sampler unit in the shader for the parameter.</param>
		/// <param name="_ImageUnit">The target image unit in the shader for the parameter.</param>
		virtual void SendToShader( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& _ImageUnit );

		/// <summary>
		/// Called after a draw call.<para/>
		/// Give the possibility to reset parameters or unbind texture after the draw call.
		/// </summary>
		/// <param name="_Shader">The target shader for the parameter.</param>
		/// <param name="_TextureUnit">The target sampler unit in the shader for the parameter.</param>
		/// <param name="_ImageUnit">The target image unit in the shader for the parameter.</param>
		virtual void Clean( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& _ImageUnit );

		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor();

		/// <summary>
		/// Clone the parameter.<para/>
		/// The pointer on the clone must be freed manually.
		/// </summary>
		/// <returns>A pointer on the cloned parameter.</returns>
		virtual ShaderParameter* Clone() const;

	protected:
		/// <summary>
		/// Name of the parameter.<para/>
		/// Used as key to find it in the material.
		/// </summary>
		std::string m_Name;

		/// <summary>Name of the parameter in the shader.</summary>
		std::string m_UniformName;

		/// <summary>
		/// Determine if the location of the parameter in the shader has been saved.<para/>
		/// Saving the uniform location can save some time during rendering since its avoid 
		/// to fetch the uniform location each draw call.
		/// </summary>
		Bool m_IsLocationSaved;

		/// <summary>If saved, contains the uniform location in the shader.</summary>
		Int32 m_UniformLocation;

		/// <summary>If true, the editor will call ToEditor() function.</summary>
		Bool m_IsEditable;
		
		/// <summary>
		/// If set to true, when the material that store this parameter is destroyed,
		/// the parameter will be freed too.
		/// </summary>
		Bool m_IsDestroyedWithMaterial;
	};

} // ae

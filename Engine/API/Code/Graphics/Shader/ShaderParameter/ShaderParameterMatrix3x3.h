#pragma once

#include "../../../Toolbox/Toolbox.h"

#include "ShaderParameter.h"
#include "../../../Maths/Matrix/Matrix3x3.h"

namespace ae
{
	class Shader;

	/// \ingroup graphics
	/// <summary>
	/// Shader parameter for matrix 3x3 uniforms.
	/// </summary>
	/// <seealso cref="Shader"/>
	/// <seealso cref="Material"/>
	/// <seealso cref="ShaderParameter"/>
	/// <seealso cref="Matrix3x3"/>
	class AERO_CORE_EXPORT ShaderParameterMatrix3x3 : public ShaderParameter
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
		/// <param name="_UniformName">Name of the parameter in the shader.</param>
		/// <param name="_Value">Value for the matrix 3x3 parameter.</param>
		explicit ShaderParameterMatrix3x3( const std::string& _Name, const std::string& _UniformName, const Matrix3x3& _Value );


		/// <summary>Apply a new value for the parameter.</summary>
		/// <param name="_Value">The new value of the parameter.</param>
		void SetValue( const Matrix3x3& _Value );

		/// <summary>Retrieve the current value of the parameter.</summary>
		/// <returns>The value of the parameter.</returns>
		const Matrix3x3& GetValue() const;

		/// <summary>Operator to set the value.</summary>
		/// <param name="_Value">The new value for the parameter.</param>
		/// <returns>The parameter with the new value applied.</returns>
		ShaderParameter& operator=( const Matrix3x3& _Value );

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
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		void ToEditor() final;


		/// <summary>
		/// Clone the parameter.<para/>
		/// The pointer on the clone must be freed manually.
		/// </summary>
		/// <returns>A pointer on the cloned parameter.</returns>
		ShaderParameterMatrix3x3* Clone() const override final;

	private:
		/// <summary>Value of the matrix 3x3 parameter.</summary>
		Matrix3x3 m_Value;
	};
} // ae

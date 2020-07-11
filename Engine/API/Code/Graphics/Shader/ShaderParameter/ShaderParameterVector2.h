#pragma once

#include "../../../Toolbox/Toolbox.h"

#include "ShaderParameter.h"
#include "../../../Maths/Vector/Vector2.h"

namespace ae
{
	class Shader;

	/// \ingroup graphics
	/// <summary>
	/// Shader parameter for vector 2 uniforms.
	/// </summary>
	/// <seealso cref="Shader"/>
	/// <seealso cref="Material"/>
	/// <seealso cref="ShaderParameter"/>
	/// <seealso cref="Vector2"/>
	class AERO_CORE_EXPORT ShaderParameterVector2 : public ShaderParameter
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
		/// <param name="_Value">Value for the vector 2 parameter.</param>
		explicit ShaderParameterVector2( const std::string& _Name, const std::string& _UniformName, const Vector2& _Value );


		/// <summary>Apply a new value for the parameter.</summary>
		/// <param name="_Value">The new value of the parameter.</param>
		void SetValue( const Vector2& _Value );

		/// <summary>Retrieve the current value of the parameter.</summary>
		/// <returns>The value of the parameter.</returns>
		const Vector2& GetValue() const;

		/// <summary>Operator to set the value.</summary>
		/// <param name="_Value">The new value for the parameter.</param>
		/// <returns>The parameter with the new value applied.</returns>
		ShaderParameter& operator=( const Vector2& _Value );


		/// <summary>Set the minimum value possible for the parameter (applied to the two vector coordinates).</summary>
		/// <param name="_Min">The new minimum value for the parameter.</param>
		void SetMin( float _Min );

		/// <summary>Get the minimum possible value for the parameter(applied to the two vector coordinates).</summary>
		/// <returns>The minimum possible value for the parameter.</returns>
		float GetMin() const;


		/// <summary>Set the maximum value possible for the parameter(applied to the two vector coordinates).</summary>
		/// <param name="_Max">The new maximum value for the parameter.</param>
		void SetMax( float _Max );

		/// <summary>Get the maximum possible value for the parameter(applied to the two vector coordinates).</summary>
		/// <returns>The maximum possible value for the parameter.</returns>
		float GetMax() const;

		/// <summary>Set the step used in the editor to modify the parameter(applied to the two vector coordinates).</summary>
		/// <param name="_Step">The new step for the editor.</param>
		void SetStep( float _Step );

		/// <summary>Get the step used in the editor to modify the parameter(applied to the two vector coordinates).</summary>
		/// <returns>The step used in the editor.</returns>
		float GetStep() const;

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
		void ToEditor() override final;


		/// <summary>
		/// Clone the parameter.<para/>
		/// The pointer on the clone must be freed manually.
		/// </summary>
		/// <returns>A pointer on the cloned parameter.</returns>
		ShaderParameterVector2* Clone() const override final;

	private:
		/// <summary>Clamp the current value between the min and max stored.</summary>
		void ClampValue();

	private:
		/// <summary>Value of the vector 2 parameter.</summary>
		Vector2 m_Value;

		/// <summary>Optionnal minimum for the value.</summary>
		float m_Min;

		/// <summary>Optionnal maximum for the value.</summary>
		float m_Max;

		/// <summary>Optionnal step for setting the value in the editor.</summary>
		float m_Step;
	};
} // ae

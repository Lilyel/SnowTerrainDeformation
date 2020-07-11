#pragma once

#include "../../Toolbox/Toolbox.h"
#include "Material.h"
#include "../Shader/ShaderParameter/ShaderParameterColor.h"
#include "../Shader/ShaderParameter/ShaderParameterBool.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>Curve shading settings for rendering.</summary>
	/// <seealso cref="Material"/>
	class AERO_CORE_EXPORT CurveMaterial : public Material
	{
	public:
		/// <summary>Set the shader to the default curve shader and create all the shader parameters for it.</summary>
		CurveMaterial();

		/// <summary>Retrieve the parameter for the control curve color.</summary>
		/// <returns>The parameter for the control curve color.</returns>
		ShaderParameterColor& GetControlCurveColor();

		/// <summary>Retrieve the parameter for the control curve color.</summary>
		/// <returns>The parameter for the control curve color.</returns>
		const ShaderParameterColor& GetControlCurveColor() const;


		/// <summary>Retrieve the parameter for the curve color.</summary>
		/// <returns>The parameter for the curve color.</returns>
		ShaderParameterColor& GetCurveColor();

		/// <summary>Retrieve the parameter for the curve color.</summary>
		/// <returns>The parameter for the curve color.</returns>
		const ShaderParameterColor& GetCurveColor() const;

	private:
		/// <summary>Parameter for the control curve color.</summary>
		ShaderParameterColor* m_ControlCurveColor;

		/// <summary>Parameter for the curve color.</summary>
		ShaderParameterColor* m_CurveColor;
	};

} // ae

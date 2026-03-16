#include "CurveMaterial.h"

#include "../../Aero/Aero.h"

#include <string>

namespace ae
{

	CurveMaterial::CurveMaterial()
	{
		SetShader( Aero.GetResourcesManager().GetDefaultCurveShader() );


		const std::string& ControlCurveColorName = GetDefaultParameterName( DefaultParameters::Curve_ControlColor );
		m_ControlCurveColor = AddColorParameterToMaterial( ControlCurveColorName, ControlCurveColorName, Color::White );

		const std::string& CurveColorName = GetDefaultParameterName( DefaultParameters::Curve_Color );
		m_CurveColor = AddColorParameterToMaterial( CurveColorName, CurveColorName, Color::White );


		SaveUniformsLocation();

		SetName( std::string( "CurveMaterial_" ) + std::to_string( GetResourceID() ) );
	}

	ShaderParameterColor& CurveMaterial::GetControlCurveColor()
	{
		return *m_ControlCurveColor;
	}

	const ShaderParameterColor& CurveMaterial::GetControlCurveColor() const
	{
		return *m_ControlCurveColor;
	}

	ShaderParameterColor& CurveMaterial::GetCurveColor()
	{
		return *m_CurveColor;
	}

	const ShaderParameterColor& CurveMaterial::GetCurveColor() const
	{
		return *m_CurveColor;
	}

} // ae

#include "SpotLight.h"

#include "../../../Maths/Functions/MathsFunctions.h"
#include "../../Shader/Shader.h"
#include "../../../Editor/TypesToEditor/SpotLightToEditor.h"

#include <string.h>

namespace ae
{

	SpotLight::SpotLight( float _InnerAngle, float _OuterAngle, float _Range ) :
		m_InnerAngle( 0.0f ),
		m_OuterAngle( 1.0f )
	{
        m_Type = LightType::Spot;
		SetAngles( _InnerAngle, _OuterAngle );
		SetRange( _Range );

		SetName( std::string( "SpotLight_" ) + std::to_string( GetObjectID() ) );
	}

	void SpotLight::SetInnerAngle( float _Angle )
	{
		m_InnerAngle = Math::Clamp( 0.0f, Math::DegToRad_Const(89.0f), _Angle );

		if( m_InnerAngle > m_OuterAngle )
			m_OuterAngle = m_InnerAngle + Math::DegToRad_Const(1.0f);
	}

	float SpotLight::GetInnerAngle() const
	{
		return m_InnerAngle;
	}

	void SpotLight::SetOuterAngle( float _Angle )
	{
		m_OuterAngle = Math::Clamp( Math::DegToRad_Const( 1.0f ), Math::DegToRad_Const( 89.0f ), _Angle );

		if( m_OuterAngle < m_InnerAngle )
			m_InnerAngle = m_OuterAngle - Math::DegToRad_Const( 1.0f );
	}

	float SpotLight::GetOuterAngle() const
	{
		return m_OuterAngle;
	}

	void SpotLight::SetAngles( float _InnerAngle, float _OuterAngle )
	{
		SetInnerAngle( _InnerAngle );
		SetOuterAngle( _OuterAngle );
	}

	void SpotLight::SetRange( float _Range )
	{
		m_Range = Math::Max( _Range, 0.0f );
	}

	float SpotLight::GetRange()
	{
		return m_Range;
	}

	void SpotLight::SendToShader( const std::string& _LightName, Uint32 _LightIndex, const Shader& _Shader )
	{
        const std::string IndexedLightName = _LightName + "[" + std::to_string( _LightIndex ) + "]";

		Uint32 Location = _Shader.GetUniformLocation( IndexedLightName + ".Position" );
		_Shader.SetVector3( Location, m_Position );

		Location = _Shader.GetUniformLocation( IndexedLightName + ".Color" );
		_Shader.SetColor( Location, m_Color );

		Location = _Shader.GetUniformLocation( IndexedLightName + ".LookAt" );
		_Shader.SetVector3( Location, GetForward() );

		Location = _Shader.GetUniformLocation( IndexedLightName + ".InnerAngle" );
		_Shader.SetFloat( Location, m_InnerAngle );

		Location = _Shader.GetUniformLocation( IndexedLightName + ".OuterAngle" );
		_Shader.SetFloat( Location, m_OuterAngle );

		Location = _Shader.GetUniformLocation( IndexedLightName + ".Intensity" );
		_Shader.SetFloat( Location, m_Intensity );

		Location = _Shader.GetUniformLocation( IndexedLightName + ".Range" );
		_Shader.SetFloat( Location, m_Range );
	}

    void SpotLight::ToEditor()
    {
        Light::ToEditor();
        priv::ui::SpotLightToEditor( *this );
    }

} //ae
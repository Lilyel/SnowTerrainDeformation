#include "PointLight.h"

#include "../../Shader/Shader.h"

#include "../../../Maths/Functions/MathsFunctions.h"
#include "../../../Editor/TypesToEditor/PointLightToEditor.h"

namespace ae
{

	PointLight::PointLight( float _Radius )
	{
		m_Type = LightType::Point;
		SetRadius( _Radius );

		SetName( std::string( "PointLight_" ) + std::to_string( GetObjectID() ) );
	}

	void PointLight::SetRadius( float _Radius )
	{
		m_Radius = Math::Max( _Radius, 0.0f );
	}

	float PointLight::GetRadius() const
	{
		return m_Radius;
	}

	void PointLight::SendToShader( const std::string& _LightName, Uint32 _LightIndex, const Shader& _Shader )
	{
		const std::string IndexedLightName = _LightName + "[" + std::to_string( _LightIndex ) + "]";

		Uint32 Location = _Shader.GetUniformLocation( IndexedLightName + ".Position" );
		_Shader.SetVector3( Location, m_Position );

		Location = _Shader.GetUniformLocation( IndexedLightName + ".Color" );
		_Shader.SetColor( Location, m_Color );

		Location = _Shader.GetUniformLocation( IndexedLightName + ".Radius" );
		_Shader.SetFloat( Location, m_Radius );

		Location = _Shader.GetUniformLocation( IndexedLightName + ".Intensity" );
		_Shader.SetFloat( Location, m_Intensity );
	}

	void PointLight::ToEditor()
	{
		Light::ToEditor();
		priv::ui::PointLightToEditor( *this );
	}

} //ae
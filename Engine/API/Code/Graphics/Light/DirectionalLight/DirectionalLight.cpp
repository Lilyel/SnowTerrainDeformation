#include "DirectionalLight.h"

#include "../../Shader/Shader.h"

namespace ae
{
    DirectionalLight::DirectionalLight()
    {
        m_Type = LightType::Directional;

		SetName( std::string( "DirectionalLight_" ) + std::to_string( GetObjectID() ) );
    }

    void DirectionalLight::SendToShader( const std::string& _LightName, Uint32 _LightIndex, const Shader& _Shader )
	{
        const std::string IndexedLightName = _LightName + "[" + std::to_string( _LightIndex ) + "]";

		Uint32 Location = _Shader.GetUniformLocation( IndexedLightName + ".Position" );
		_Shader.SetVector3( Location, m_Position );

		Location = _Shader.GetUniformLocation( IndexedLightName + ".Color" );
		_Shader.SetColor( Location, m_Color );

		Location = _Shader.GetUniformLocation( IndexedLightName + ".LookAt" );
		_Shader.SetVector3( Location, GetForward() );

		Location = _Shader.GetUniformLocation( IndexedLightName + ".Intensity" );
		_Shader.SetFloat( Location, m_Intensity );
	}
} //ae
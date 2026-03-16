#include "ShaderParameterBool.h"

#include "../Shader.h"

#include "../../../Editor/TypesToEditor/ShaderParameterBoolToEditor.h"

namespace ae
{
	ShaderParameterBool::ShaderParameterBool( const std::string& _Name, const std::string& _UniformName, Bool _Value ) :
		ShaderParameter( _Name, _UniformName ),
		m_Value( _Value )
	{
	}
	void ShaderParameterBool::SetValue( Bool _Value )
	{
		m_Value = _Value;
	}
	Bool ShaderParameterBool::GetValue() const
	{
		return m_Value;
	}
	ShaderParameter& ShaderParameterBool::operator=( Bool _Value )
	{
		m_Value = _Value;

		return *this;
	}
	void ShaderParameterBool::SendToShader( const Shader& _Shader, Uint32&, Uint32& )
	{
		if( GetUniformName().empty() )
			return;

		Int32 Location = GetUniformLocation( _Shader );
		if( Location < 0 )
			return;

		Shader::SetBool( Location, m_Value );
	}
	void ShaderParameterBool::ToEditor()
	{
		ShaderParameter::ToEditor();
		priv::ui::ShaderParameterBoolToEditor( *this );
	}
	ShaderParameterBool* ShaderParameterBool::Clone() const
	{
		ShaderParameterBool* Clone = new ShaderParameterBool( m_Name, m_UniformName, m_Value );
		*Clone = *this;
		return Clone;
	}
} // ae

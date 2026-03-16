#include "ShaderParameterMatrix3x3.h"

#include "../Shader.h"
#include "../../../Maths/Functions/MathsFunctions.h"

#include "../../../Editor/TypesToEditor/ShaderParameterMatrix3x3ToEditor.h"

namespace ae
{
	ShaderParameterMatrix3x3::ShaderParameterMatrix3x3( const std::string& _Name, const std::string& _UniformName, const Matrix3x3& _Value ) :
		ShaderParameter( _Name, _UniformName ),
		m_Value( _Value )
	{
	}
	void ShaderParameterMatrix3x3::SetValue( const Matrix3x3& _Value )
	{
		m_Value = _Value;
	}
	const Matrix3x3& ShaderParameterMatrix3x3::GetValue() const
	{
		return m_Value;
	}
	ShaderParameter& ShaderParameterMatrix3x3::operator=( const Matrix3x3& _Value )
	{
		m_Value = _Value;

		return *this;
	}
	void ShaderParameterMatrix3x3::SendToShader( const Shader& _Shader, Uint32&, Uint32& )
	{
		if( GetUniformName().empty() )
			return;

		Int32 Location = GetUniformLocation( _Shader );
		if( Location < 0 )
			return;

		Shader::SetMatrix3x3( Location, m_Value );
	}
	void ShaderParameterMatrix3x3::ToEditor()
	{
		ShaderParameter::ToEditor();
		priv::ui::ShaderParameterMatrix3x3ToEditor( *this );
	}
	ShaderParameterMatrix3x3* ShaderParameterMatrix3x3::Clone() const
	{
		ShaderParameterMatrix3x3* Clone = new ShaderParameterMatrix3x3( m_Name, m_UniformName, m_Value );
		*Clone = *this;
		return Clone;
	}
} // ae

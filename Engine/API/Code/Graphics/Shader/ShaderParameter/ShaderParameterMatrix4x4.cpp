#include "ShaderParameterMatrix4x4.h"

#include "../Shader.h"
#include "../../../Maths/Functions/MathsFunctions.h"

#include "../../../Editor/TypesToEditor/ShaderParameterMatrix4x4ToEditor.h"

namespace ae
{
	ShaderParameterMatrix4x4::ShaderParameterMatrix4x4( const std::string& _Name, const std::string& _UniformName, const Matrix4x4& _Value ) :
		ShaderParameter( _Name, _UniformName ),
		m_Value( _Value )
	{
	}
	void ShaderParameterMatrix4x4::SetValue( const Matrix4x4& _Value )
	{
		m_Value = _Value;
	}
	const Matrix4x4& ShaderParameterMatrix4x4::GetValue() const
	{
		return m_Value;
	}
	ShaderParameter& ShaderParameterMatrix4x4::operator=( const Matrix4x4& _Value )
	{
		m_Value = _Value;

		return *this;
	}
	void ShaderParameterMatrix4x4::SendToShader( const Shader& _Shader, Uint32&, Uint32& )
	{
		if( GetUniformName().empty() )
			return;

		Int32 Location = GetUniformLocation( _Shader );
		if( Location < 0 )
			return;

		Shader::SetMatrix4x4( Location, m_Value );
	}
	void ShaderParameterMatrix4x4::ToEditor()
	{
		ShaderParameter::ToEditor();
		priv::ui::ShaderParameterMatrix4x4ToEditor( *this );
	}
	ShaderParameterMatrix4x4* ShaderParameterMatrix4x4::Clone() const
	{
		ShaderParameterMatrix4x4* Clone = new ShaderParameterMatrix4x4( m_Name, m_UniformName, m_Value );
		*Clone = *this;
		return Clone;
	}
} // ae

#include "ShaderParameterColor.h"

#include "../Shader.h"
#include "../../../Maths/Functions/MathsFunctions.h"

#include "../../../Editor/TypesToEditor/ShaderParameterColorToEditor.h"

namespace ae
{
	ShaderParameterColor::ShaderParameterColor( const std::string& _Name, const std::string& _UniformName, const Color& _Value ) :
		ShaderParameter( _Name, _UniformName ),
		m_Value( _Value )
	{
	}

	void ShaderParameterColor::SetValue( const Color& _Value )
	{
		m_Value = _Value;
	}

	const Color& ShaderParameterColor::GetValue() const
	{
		return m_Value;
	}

	ShaderParameter& ShaderParameterColor::operator=( const Color& _Value )
	{
		m_Value = _Value;

		return *this;
	}
	
	void ShaderParameterColor::SendToShader( const Shader& _Shader, Uint32&, Uint32& )
	{
		if( GetUniformName().empty() )
			return;

		Int32 Location = GetUniformLocation( _Shader );
		if( Location < 0 )
			return;

		Shader::SetColor( Location, m_Value );
	}

	void ShaderParameterColor::ToEditor()
	{
		ShaderParameter::ToEditor();
		priv::ui::ShaderParameterColorToEditor( *this );
	}

	ShaderParameterColor* ShaderParameterColor::Clone() const
	{
		ShaderParameterColor* Clone = new ShaderParameterColor( m_Name, m_UniformName, m_Value );
		*Clone = *this;
		return Clone;
	}

} // ae

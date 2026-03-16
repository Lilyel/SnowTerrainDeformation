#include "ShaderParameterFloat.h"

#include "../Shader.h"
#include "../../../Maths/Functions/MathsFunctions.h"

#include "../../../Editor/TypesToEditor/ShaderParameterFloatToEditor.h"

namespace ae
{
	ShaderParameterFloat::ShaderParameterFloat( const std::string& _Name, const std::string& _UniformName, float _Value ) :
		ShaderParameter( _Name, _UniformName ),
		m_Value( _Value ),
		m_Min( std::numeric_limits<float>::min() ),
		m_Max( std::numeric_limits<float>::max() ),
		m_Step( 0.01f )
	{
	}
	void ShaderParameterFloat::SetValue( float _Value )
	{
		m_Value = _Value;
		ClampValue();
	}
	float ShaderParameterFloat::GetValue() const
	{
		return m_Value;
	}
	ShaderParameter& ShaderParameterFloat::operator=( float _Value )
	{
		m_Value = _Value;
		ClampValue();

		return *this;
	}
	void ShaderParameterFloat::SetMin( float _Min )
	{
		m_Min = _Min;
		ClampValue();
	}
	float ShaderParameterFloat::GetMin() const
	{
		return m_Min;
	}
	void ShaderParameterFloat::SetMax( float _Max )
	{
		m_Max = _Max;
		ClampValue();
	}
	float ShaderParameterFloat::GetMax() const
	{
		return m_Max;
	}
	void ShaderParameterFloat::SetStep( float _Step )
	{
		// Avoid step too small.
		m_Step = Math::Max( Math::Epsilon(), _Step );
	}
	float ShaderParameterFloat::GetStep() const
	{
		return m_Step;
	}
	void ShaderParameterFloat::SendToShader( const Shader& _Shader, Uint32&, Uint32& )
	{
		if( GetUniformName().empty() )
			return;

		Int32 Location = GetUniformLocation( _Shader );
		if( Location < 0 )
			return;

		Shader::SetFloat( Location, m_Value );
	}
	void ShaderParameterFloat::ToEditor()
	{
		ShaderParameter::ToEditor();
		priv::ui::ShaderParameterFloatToEditor( *this );
	}

	ShaderParameterFloat* ShaderParameterFloat::Clone() const
	{
		ShaderParameterFloat* Clone = new ShaderParameterFloat( m_Name, m_UniformName, m_Value );
		*Clone = *this;
		return Clone;
	}

	void ShaderParameterFloat::ClampValue()
	{
		m_Value = Math::Clamp( m_Min, m_Max, m_Value );
	}
} // ae

#include "ShaderParameterVector2.h"

#include "../Shader.h"
#include "../../../Maths/Functions/MathsFunctions.h"

#include "../../../Editor/TypesToEditor/ShaderParameterVector2ToEditor.h"

namespace ae
{
	ShaderParameterVector2::ShaderParameterVector2( const std::string& _Name, const std::string& _UniformName, const Vector2& _Value ) :
		ShaderParameter( _Name, _UniformName ),
		m_Value( _Value ),
		m_Min( std::numeric_limits<float>::min() ),
		m_Max( std::numeric_limits<float>::max() ),
		m_Step( 1.0f )
	{
	}
	void ShaderParameterVector2::SetValue( const Vector2& _Value )
	{
		m_Value = _Value;
		ClampValue();
	}
	const Vector2& ShaderParameterVector2::GetValue() const
	{
		return m_Value;
	}
	ShaderParameter& ShaderParameterVector2::operator=( const Vector2& _Value )
	{
		m_Value = _Value;
		ClampValue();

		return *this;
	}
	void ShaderParameterVector2::SetMin( float _Min )
	{
		m_Min = _Min;
		ClampValue();
	}
	float ShaderParameterVector2::GetMin() const
	{
		return m_Min;
	}
	void ShaderParameterVector2::SetMax( float _Max )
	{
		m_Max = _Max;
		ClampValue();
	}
	float ShaderParameterVector2::GetMax() const
	{
		return m_Max;
	}
	void ShaderParameterVector2::SetStep( float _Step )
	{
		// Avoid step too small.
		m_Step = Math::Max( Math::Epsilon(), _Step );
	}
	float ShaderParameterVector2::GetStep() const
	{
		return m_Step;
	}
	void ShaderParameterVector2::SendToShader( const Shader& _Shader, Uint32&, Uint32& )
	{
		if( GetUniformName().empty() )
			return;

		Int32 Location = GetUniformLocation( _Shader );
		if( Location < 0 )
			return;

		Shader::SetVector2( Location, m_Value );
	}
	void ShaderParameterVector2::ToEditor()
	{
		ShaderParameter::ToEditor();
		priv::ui::ShaderParameterVector2ToEditor( *this );
	}
	ShaderParameterVector2* ShaderParameterVector2::Clone() const
	{
		ShaderParameterVector2* Clone = new ShaderParameterVector2( m_Name, m_UniformName, m_Value );
		*Clone = *this;
		return Clone;
	}
	void ShaderParameterVector2::ClampValue()
	{
		m_Value.X = Math::Clamp( m_Min, m_Max, m_Value.X );
		m_Value.Y = Math::Clamp( m_Min, m_Max, m_Value.Y );
	}
} // ae

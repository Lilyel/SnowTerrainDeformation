#include "ShaderParameterVector3.h"

#include "../Shader.h"
#include "../../../Maths/Functions/MathsFunctions.h"

#include "../../../Editor/TypesToEditor/ShaderParameterVector3ToEditor.h"

namespace ae
{
	ShaderParameterVector3::ShaderParameterVector3( const std::string& _Name, const std::string& _UniformName, const Vector3& _Value ) :
		ShaderParameter( _Name, _UniformName ),
		m_Value( _Value ),
		m_Min( std::numeric_limits<float>::min() ),
		m_Max( std::numeric_limits<float>::max() ),
		m_Step( 1.0f )
	{
	}
	void ShaderParameterVector3::SetValue( const Vector3& _Value )
	{
		m_Value = _Value;
		ClampValue();
	}
	const Vector3& ShaderParameterVector3::GetValue() const
	{
		return m_Value;
	}
	ShaderParameter& ShaderParameterVector3::operator=( const Vector3& _Value )
	{
		m_Value = _Value;
		ClampValue();

		return *this;
	}
	void ShaderParameterVector3::SetMin( float _Min )
	{
		m_Min = _Min;
		ClampValue();
	}
	float ShaderParameterVector3::GetMin() const
	{
		return m_Min;
	}
	void ShaderParameterVector3::SetMax( float _Max )
	{
		m_Max = _Max;
		ClampValue();
	}
	float ShaderParameterVector3::GetMax() const
	{
		return m_Max;
	}
	void ShaderParameterVector3::SetStep( float _Step )
	{
		// Avoid step too small.
		m_Step = Math::Max( Math::Epsilon(), _Step );
	}
	float ShaderParameterVector3::GetStep() const
	{
		return m_Step;
	}
	void ShaderParameterVector3::SendToShader( const Shader& _Shader, Uint32&, Uint32& )
	{
		if( GetUniformName().empty() )
			return;

		Int32 Location = GetUniformLocation( _Shader );
		if( Location < 0 )
			return;

		Shader::SetVector3( Location, m_Value );
	}
	void ShaderParameterVector3::ToEditor()
	{
		ShaderParameter::ToEditor();
		priv::ui::ShaderParameterVector3ToEditor( *this );
	}
	ShaderParameterVector3* ShaderParameterVector3::Clone() const
	{
		ShaderParameterVector3* Clone = new ShaderParameterVector3( m_Name, m_UniformName, m_Value );
		*Clone = *this;
		return Clone;
	}
	void ShaderParameterVector3::ClampValue()
	{
		m_Value.X = Math::Clamp( m_Min, m_Max, m_Value.X );
		m_Value.Y = Math::Clamp( m_Min, m_Max, m_Value.Y );
		m_Value.Z = Math::Clamp( m_Min, m_Max, m_Value.Z );
	}
} // ae

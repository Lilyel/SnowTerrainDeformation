#include "ShaderParameterInt.h"

#include "../Shader.h"
#include "../../../Maths/Functions/MathsFunctions.h"

#include "../../../Editor/TypesToEditor/ShaderParameterIntToEditor.h"

#include <limits>

namespace ae
{

	ShaderParameterInt::ShaderParameterInt( const std::string& _Name, const std::string& _UniformName, Int32 _Value ) :
		ShaderParameter( _Name, _UniformName ),
		m_Value( _Value ),
		m_Min( std::numeric_limits<Int32>::min() ),
		m_Max( std::numeric_limits<Int32>::max() ),
		m_Step( 1u )
	{
	}

	void ShaderParameterInt::SetValue( Int32 _Value )
	{
		m_Value = _Value;
		ClampValue();
	}

	Int32 ShaderParameterInt::GetValue() const
	{
		return m_Value;
	}

	ShaderParameter& ShaderParameterInt::operator=( Int32 _Value )
	{
		m_Value = _Value;
		ClampValue();

		return *this;
	}

	void ShaderParameterInt::SetMin( Int32 _Min )
	{
		m_Min = _Min;
		ClampValue();
	}

	Int32 ShaderParameterInt::GetMin() const
	{
		return m_Min;
	}

	void ShaderParameterInt::SetMax( Int32 _Max )
	{
		m_Max = _Max;
		ClampValue();
	}

	Int32 ShaderParameterInt::GetMax() const
	{
		return m_Max;
	}

	void ShaderParameterInt::SetStep( Uint32 _Step )
	{
		// Avoid step too small.
		m_Step = Math::Max( 1u, _Step );
	}

	Uint32 ShaderParameterInt::GetStep() const
	{
		return m_Step;
	}


	void ShaderParameterInt::SendToShader( const Shader& _Shader, Uint32&, Uint32& )
	{
		if( GetUniformName().empty() )
			return;

		Int32 Location = GetUniformLocation( _Shader );
		if( Location < 0 )
			return;

		Shader::SetInt( Location, m_Value );
	}


	void ShaderParameterInt::ToEditor()
	{
		ShaderParameter::ToEditor();
		priv::ui::ShaderParameterIntToEditor( *this );

	}

	ShaderParameterInt* ShaderParameterInt::Clone() const
	{
		ShaderParameterInt* Clone = new ShaderParameterInt( m_Name, m_UniformName, m_Value );
		*Clone = *this;
		return Clone;
	}

	void ShaderParameterInt::ClampValue()
	{
		m_Value = Math::Clamp( m_Min, m_Max, m_Value );
	}

} // ae

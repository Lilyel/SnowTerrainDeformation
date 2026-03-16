#include "ShaderParameter.h"

#include "../Shader.h"

#include "../../../Editor/TypesToEditor/ShaderParameterToEditor.h"

namespace ae
{
	ShaderParameter::ShaderParameter( const std::string& _Name, const std::string& _UniformName ) : 
		m_Name( _Name ),
		m_UniformName( _UniformName ),
		m_IsLocationSaved( False ),
		m_UniformLocation( -1 ),
		m_IsEditable( True ),
		m_IsDestroyedWithMaterial( False )
	{
	}

	const std::string& ShaderParameter::GetName() const
	{
		return m_Name;
	}

	const std::string& ShaderParameter::GetUniformName() const
	{
		return m_UniformName;
	}

	void ShaderParameter::SetUniformName( const std::string& _Name )
	{
		m_UniformName = _Name;

		// The uniform name has changed, so the saved location can be invalid now.
		// We disable the save for safety.
		DiscardSave();
	}

	void ShaderParameter::SaveUniformLocation( const Shader& _Shader )
	{
		if( m_UniformName.empty() )
			return;

		m_UniformLocation = _Shader.GetUniformLocation( m_UniformName );
		m_IsLocationSaved = True;
	}

	void ShaderParameter::DiscardSave()
	{
		m_IsLocationSaved = False;
		m_UniformLocation = -1;
	}

	Bool ShaderParameter::IsSaved() const
	{
		return m_IsLocationSaved;
	}

	Bool ShaderParameter::IsEditable() const
	{
		return m_IsEditable;
	}

	void ShaderParameter::SetEditable( Bool _IsEditable )
	{
		m_IsEditable = _IsEditable;
	}

	void ShaderParameter::SetIsDestroyedWithMaterial( Bool _IsDestroyedWithMaterial )
	{
		m_IsDestroyedWithMaterial = _IsDestroyedWithMaterial;
	}

	Bool ShaderParameter::IsDestroyedWithMaterial() const
	{
		return m_IsDestroyedWithMaterial;
	}

	Int32 ShaderParameter::GetUniformLocation( const Shader& _Shader ) const
	{
		return IsSaved() ? m_UniformLocation : _Shader.GetUniformLocation( GetUniformName() );
	}

	void ShaderParameter::SendToShader( const Shader&, AE_InOut Uint32&, AE_InOut Uint32& )
	{
	}



	void ShaderParameter::Clean( const Shader&, AE_InOut Uint32&, AE_InOut Uint32& )
	{
	}

	void ShaderParameter::ToEditor()
	{
		priv::ui::ShaderParameterToEditor( *this );
	}

	ShaderParameter* ShaderParameter::Clone() const
	{
		ShaderParameter* Clone = new ShaderParameter( m_Name, m_UniformName );
		*Clone = *this;
		return Clone;
	}

} // ae

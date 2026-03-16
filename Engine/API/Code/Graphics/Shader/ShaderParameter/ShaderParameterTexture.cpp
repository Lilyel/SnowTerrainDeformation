#include "ShaderParameterTexture.h"

#include "../Shader.h"
#include "../../Texture/Texture.h"

#include "../../../Debugging/Debugging.h"
#include "../../Dependencies/OpenGL.h"

namespace ae
{
	ShaderParameterTexture::ShaderParameterTexture( const std::string& _Name, const std::string& _UniformName, const Texture* _Value ) :
		ShaderParameter( _Name, _UniformName ),
		m_Value( _Value )
	{
	}
	void ShaderParameterTexture::SetValue( const Texture* _Value )
	{
		m_Value = _Value;
	}
	const Texture* ShaderParameterTexture::GetValue() const
	{
		return m_Value;
	}
	ShaderParameter& ShaderParameterTexture::operator=( const Texture* _Value )
	{
		m_Value = _Value;

		return *this;
	}
	void ShaderParameterTexture::SendToShader( const Shader& _Shader, Uint32& _TextureUnit, AE_InOut Uint32& _ImageUnit )
	{
		if( GetUniformName().empty() || m_Value == nullptr )
			return;

		Int32 Location = GetUniformLocation( _Shader );
		if( Location < 0 )
			return;

		// Bind as image.
		if( m_Value->IsBoundAsImage() )
		{
			// Bind the texture attached to this parameter.
			m_Value->BindAsImage( _ImageUnit );

			// Set the image in shader with the current image unit.
			_Shader.SetInt( Location, _ImageUnit );

			// Increment image unit for next bindings.
			_ImageUnit++;
		}
		
		// Bind as texture.
		else
		{
			// Activate texture in shader.
			glActiveTexture( GL_TEXTURE0 + _TextureUnit ); AE_ErrorCheckOpenGLError();

			// Bind the texture attached to this parameter.
			m_Value->Bind();

			// Set the sampler in shader with the current unit texture.
			_Shader.SetInt( Location, _TextureUnit );

			// Increment texture unit for next bindings.
			_TextureUnit++;
		}
	}
	void ShaderParameterTexture::Clean( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& )
	{
		if( GetUniformName().empty() || m_Value == nullptr )
			return;

		Int32 Location = GetUniformLocation( _Shader );
		if( Location < 0 )
			return;

		if( !m_Value->IsBoundAsImage() )
		{
			// Activate texture in shader.
			glActiveTexture( GL_TEXTURE0 + _TextureUnit ); AE_ErrorCheckOpenGLError();

			// Unbind the cube map texture attached to this parameter.
			m_Value->Unbind();

			// Reset the sampler in shader.
			_Shader.SetInt( Location, 0 );

			// Increment texture unit for next cleanup.
			_TextureUnit++;
		}
	}
	void ShaderParameterTexture::ToEditor()
	{
		ShaderParameter::ToEditor();
	}
	ShaderParameterTexture* ShaderParameterTexture::Clone() const
	{
		ShaderParameterTexture* Clone = new ShaderParameterTexture( m_Name, m_UniformName, m_Value );
		*Clone = *this;
		return Clone;
	}
} // ae

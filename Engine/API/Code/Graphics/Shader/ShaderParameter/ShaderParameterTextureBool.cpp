#include "ShaderParameterTextureBool.h"

#include "../Shader.h"
#include "../../Texture/Texture.h"

#include "../../../Debugging/Debugging.h"
#include "../../Dependencies/OpenGL.h"

namespace ae
{

	ShaderParameterTextureBool::ShaderParameterTextureBool( const std::string& _Name,
															const std::string& _UniformTextureName, const Texture* _Texture,
															const std::string& _UniformBoolName ) :
		ShaderParameter( _Name, _UniformTextureName ),
		m_Texture( _Texture ),
		m_UniformNameBool( _UniformBoolName ),
		m_UniformLocationBool( -1 )

	{
	}

	void ShaderParameterTextureBool::SetTexture( const Texture* _Value )
	{
		m_Texture = _Value;
	}

	ShaderParameterTextureBool& ShaderParameterTextureBool::operator=( const Texture* _Value )
	{
		m_Texture = _Value;

		return *this;
	}

	const Texture* ShaderParameterTextureBool::GetTexture() const
	{
		return m_Texture;
	}

	Bool ShaderParameterTextureBool::IsTextureValid() const
	{
		return m_Texture != nullptr;
	}

	const std::string& ShaderParameterTextureBool::GetUniformNameBool() const
	{
		return m_UniformNameBool;
	}

	void ShaderParameterTextureBool::SetUniformNameBool( const std::string& _Name )
	{
		m_UniformNameBool = _Name;

		// The uniform name has changed, so the saved location can be invalid now.
		// We disable the save for safety.
		DiscardSave();
	}

	Int32 ShaderParameterTextureBool::GetUniformLocationBool( const Shader& _Shader ) const
	{
		return IsSaved() ? m_UniformLocationBool : _Shader.GetUniformLocation( GetUniformNameBool() );
	}

	void ShaderParameterTextureBool::SaveUniformLocation( const Shader& _Shader )
	{
		if( m_UniformNameBool.empty() )
			return;

		m_UniformLocationBool = _Shader.GetUniformLocation( m_UniformNameBool );

		// Do after the top class since is set to true the saved tag.
		ShaderParameter::SaveUniformLocation( _Shader );
	}

	void ShaderParameterTextureBool::SendToShader( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& _ImageUnit )
	{
		Int32 LocationBool = GetUniformLocationBool( _Shader );
		if( LocationBool >= 0 )
		{
			// Tell the shader that the texture is valid or not via the boolean uniform.
			Shader::SetBool( LocationBool, IsTextureValid() );
		}


		if( !IsTextureValid() )
			return;

		Int32 LocationTexture = GetUniformLocation( _Shader );
		if( LocationTexture < 0 )
			return;

		// Bind as image.
		if( m_Texture->IsBoundAsImage() )
		{
			// Bind the texture attached to this parameter.
			m_Texture->BindAsImage( _ImageUnit );

			// Set the image in shader with the current image unit.
			_Shader.SetInt( LocationTexture, _ImageUnit );

			// Increment image unit for next bindings.
			_ImageUnit++;
		}

		// Bind as texture.
		else
		{
			// Activate texture in shader.
			glActiveTexture( GL_TEXTURE0 + _TextureUnit ); AE_ErrorCheckOpenGLError();

			// Bind the texture attached to this parameter.
			m_Texture->Bind();

			// Set the sampler in shader with the current unit texture. (Textures units start from 0 but not GL_TEXTURE0 ).
			_Shader.SetInt( LocationTexture, _TextureUnit );

			// Increment texture unit for next bindings.
			_TextureUnit++;
		}
	}

	void ShaderParameterTextureBool::Clean( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& )
	{
		Int32 LocationBool = GetUniformLocationBool( _Shader );
		if( LocationBool >= 0 )
		{
			// Tell the shader that the texture is valid or not via the boolean uniform.
			Shader::SetBool( LocationBool, IsTextureValid() );
		}


		if( !IsTextureValid() )
			return;

		Int32 LocationTexture = GetUniformLocation( _Shader );
		if( LocationTexture < 0 )
			return;

		if( !m_Texture->IsBoundAsImage() )
		{
			// Activate texture in shader.
			glActiveTexture( GL_TEXTURE0 + _TextureUnit ); AE_ErrorCheckOpenGLError();

			// Unbind the cube map texture attached to this parameter.
			m_Texture->Unbind();

			// Reset the sampler in shader.
			_Shader.SetInt( LocationTexture, 0 );

			// Increment texture unit for next cleanup.
			_TextureUnit++;
		}
	}

	void ShaderParameterTextureBool::ToEditor()
	{
		ShaderParameter::ToEditor();
	}

	ShaderParameterTextureBool* ShaderParameterTextureBool::Clone() const
	{
		ShaderParameterTextureBool* Clone = new ShaderParameterTextureBool( m_Name, m_UniformName, m_Texture, m_UniformNameBool );
		*Clone = *this;
		return Clone;
	}


} // ae
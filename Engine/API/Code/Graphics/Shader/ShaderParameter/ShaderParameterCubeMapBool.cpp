#include "ShaderParameterCubeMapBool.h"

#include "../Shader.h"
#include "../../CubeMap/CubeMap.h"
#include "../../../Debugging/Debugging.h"
#include "../../Dependencies/OpenGL.h"
#include "../../../Editor/TypesToEditor/CubeMapToEditor.h"

namespace ae
{

	ShaderParameterCubeMapBool::ShaderParameterCubeMapBool( const std::string& _Name,
															const std::string& _UniformCubeMapName, const CubeMap* _CubeMap,
															const std::string& _UniformBoolName ) :
		ShaderParameter( _Name, _UniformCubeMapName ),
		m_CubeMap( _CubeMap ),
		m_UniformNameBool( _UniformBoolName ),
		m_UniformLocationBool( -1 )
	{
	}

	void ShaderParameterCubeMapBool::SetCubeMap( const CubeMap* _Value )
	{
		m_CubeMap = _Value;
	}

	ShaderParameter& ShaderParameterCubeMapBool::operator=( const CubeMap* _Value )
	{
		m_CubeMap = _Value;

		return *this;
	}

	const CubeMap* ShaderParameterCubeMapBool::GetCubeMap() const
	{
		return m_CubeMap;
	}

	Bool ShaderParameterCubeMapBool::IsCubeMapValid() const
	{
		return m_CubeMap != nullptr;
	}

	const std::string& ShaderParameterCubeMapBool::GetUniformNameBool() const
	{
		return m_UniformNameBool;
	}

	void ShaderParameterCubeMapBool::SetUniformNameBool( const std::string& _Name )
	{
		m_UniformNameBool = _Name;

		DiscardSave();
	}

	Int32 ShaderParameterCubeMapBool::GetUniformLocationBool( const Shader& _Shader ) const
	{
		return IsSaved() ? m_UniformLocationBool : _Shader.GetUniformLocation( GetUniformNameBool() );
	}

	void ShaderParameterCubeMapBool::SaveUniformLocation( const Shader& _Shader )
	{
		if( m_UniformNameBool.empty() )
			return;

		m_UniformLocationBool = _Shader.GetUniformLocation( m_UniformNameBool );

		// Do after the top class since is set to true the saved tag.
		ShaderParameter::SaveUniformLocation( _Shader );
	}

	void ShaderParameterCubeMapBool::SendToShader( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& _ImageUnit )
	{
		Int32 LocationBool = GetUniformLocationBool( _Shader );
		if( LocationBool >= 0 )
		{
			// Tell the shader that the texture is valid or not via the boolean uniform.
			Shader::SetBool( LocationBool, IsCubeMapValid() );
		}


		if( !IsCubeMapValid() )
			return;

		Int32 LocationCubeMap = GetUniformLocation( _Shader );
		if( LocationCubeMap < 0 )
			return;

		// Bound as image.
		if( m_CubeMap->IsBoundAsImage() )
		{
			// Bind the cube map attached to this parameter.
			m_CubeMap->BindAsImage( _ImageUnit );

			// Set the image in shader with the current image unit.
			_Shader.SetInt( LocationCubeMap, _ImageUnit );

			// Increment texture unit for next bindings.
			_ImageUnit++;
		}

		// Bound as texture.
		else
		{
			// Activate texture in shader.
			glActiveTexture( GL_TEXTURE0 + _TextureUnit ); AE_ErrorCheckOpenGLError();

			// Bind the cube map attached to this parameter.
			m_CubeMap->Bind();

			// Set the sampler in shader with the current unit texture. (Textures units start from 0 but not GL_TEXTURE0 ).
			_Shader.SetInt( LocationCubeMap, _TextureUnit );

			// Increment texture unit for next bindings.
			_TextureUnit++;
		}
	}

	void ShaderParameterCubeMapBool::Clean( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& )
	{
		Int32 LocationBool = GetUniformLocationBool( _Shader );
		if( LocationBool >= 0 )
		{
			// Tell the shader that the texture is valid or not via the boolean uniform.
			Shader::SetBool( LocationBool, IsCubeMapValid() );
		}


		if( !IsCubeMapValid() )
			return;

		Int32 LocationCubeMap = GetUniformLocation( _Shader );
		if( LocationCubeMap < 0 )
			return;

		if( !m_CubeMap->IsBoundAsImage() )
		{
			// Activate texture in shader.
			glActiveTexture( GL_TEXTURE0 + _TextureUnit ); AE_ErrorCheckOpenGLError();

			// Unbind the cube map texture attached to this parameter.
			m_CubeMap->Unbind();

			// Reset the sampler in shader.
			_Shader.SetInt( LocationCubeMap, 0 );

			// Increment texture unit for next cleanup.
			_TextureUnit++;
		}
	}

	void ShaderParameterCubeMapBool::ToEditor()
	{
		ShaderParameter::ToEditor();
	}

	ShaderParameterCubeMapBool* ShaderParameterCubeMapBool::Clone() const
	{
		ShaderParameterCubeMapBool* Clone = new ShaderParameterCubeMapBool( m_Name, m_UniformName, m_CubeMap, m_UniformNameBool );
		*Clone = *this;
		return Clone;
	}

}

#include "ShaderParameterCubeMap.h"

#include "../Shader.h"
#include "../../CubeMap/CubeMap.h"

#include "../../../Debugging/Debugging.h"
#include "../../Dependencies/OpenGL.h"

namespace ae
{
	ShaderParameterCubeMap::ShaderParameterCubeMap( const std::string& _Name, const std::string& _UniformName, const CubeMap* _Value ) :
		ShaderParameter( _Name, _UniformName ),
		m_Value( _Value )
	{
	}
	void ShaderParameterCubeMap::SetValue( const CubeMap* _Value )
	{
		m_Value = _Value;
	}
	const CubeMap* ShaderParameterCubeMap::GetValue() const
	{
		return m_Value;
	}
	ShaderParameter& ShaderParameterCubeMap::operator=( CubeMap* _Value )
	{
		m_Value = _Value;

		return *this;
	}
	void ShaderParameterCubeMap::SendToShader( const Shader& _Shader, Uint32& _TextureUnit, Uint32& _ImageUnit )
	{
		if( GetUniformName().empty() || m_Value == nullptr )
			return;

		Int32 Location = GetUniformLocation( _Shader );
		if( Location < 0 )
			return;

		// Bound as image.
		if( m_Value->IsBoundAsImage() )
		{
			// Bind the cube map texture attached to this parameter.
			m_Value->BindAsImage( _ImageUnit );

			// Set the image in shader with the current image unit.
			_Shader.SetInt( Location, _ImageUnit );

			// Increment image unit for next bindings.
			_ImageUnit++;
		}

		// Bound as texture.
		else
		{
			// Activate texture in shader.
			glActiveTexture( GL_TEXTURE0 + _TextureUnit ); AE_ErrorCheckOpenGLError();

			// Bind the cube map texture attached to this parameter.
			m_Value->Bind();

			// Set the sampler in shader with the current unit texture.
			_Shader.SetInt( Location, _TextureUnit );

			// Increment texture unit for next bindings.
			_TextureUnit++;
		}
	}

	void ShaderParameterCubeMap::Clean( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& )
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
	void ShaderParameterCubeMap::ToEditor()
	{
		ShaderParameter::ToEditor();
	}
	ShaderParameterCubeMap* ShaderParameterCubeMap::Clone() const
	{
		ShaderParameterCubeMap* Clone = new ShaderParameterCubeMap( m_Name, m_UniformName, m_Value );
		*Clone = *this;
		return Clone;
	}
} // ae

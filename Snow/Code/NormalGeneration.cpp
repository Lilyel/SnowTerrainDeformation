#include "NormalGeneration.h"

#include "ComputeInfos.h"

#include <API/Code/Debugging/Error/Error.h>

NormalGeneration::NormalGeneration( Uint32 _TextureSize ) : 
	m_NormalMap( _TextureSize, _TextureSize, ae::TexturePixelFormat::RGBA_F32 ),
	m_Shader( "../../../Data/Projects/Snow/NormalMap.glsl" )
{
	m_NormalMap.SetName( "Normal Map" );
	m_NormalMap.SetWrapMode( ae::TextureWrapMode::ClampToEdge );

	m_Shader.SetName( "Normal Map Shader" );

	m_Blur.SetName( "Normap Map Blur" );
	m_Blur.SetStandardDeviation( 1.2f );
	m_Blur.NormalizeGaussian( True );
	m_Blur.SetRadius( ae::GaussianBlur::Radius::_11x11 );
}

void NormalGeneration::Run( ae::Texture& _HeightMap )
{
	m_Shader.Bind();
	_HeightMap.BindAsImage( 0, ae::TextureImageBindMode::ReadOnly );
	m_NormalMap.BindAsImage( 1, ae::TextureImageBindMode::WriteOnly );
	m_Shader.Dispatch( m_NormalMap.GetWidth() / ComputeLocalSize, m_NormalMap.GetHeight() / ComputeLocalSize );
	m_Shader.Unbind();

	glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
	AE_ErrorCheckOpenGLError();


	m_Blur.Apply( m_NormalMap );
}

ae::Texture2D& NormalGeneration::GetNormalMap()
{
	return m_NormalMap;
}

void NormalGeneration::Resize( Uint32 _TextureSize )
{
	m_NormalMap.Resize( _TextureSize, _TextureSize );

	glClearTexSubImage( m_NormalMap.GetTextureID(), 0, 0, 0, 0, m_NormalMap.GetWidth(), m_NormalMap.GetHeight(), 1,
						ae::ToGLFormat( m_NormalMap.GetFormat() ), ae::ToGLType( m_NormalMap.GetFormat() ), nullptr );
	AE_ErrorCheckOpenGLError();
}

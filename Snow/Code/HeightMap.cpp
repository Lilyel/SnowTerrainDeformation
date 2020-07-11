#include "HeightMap.h"

#include "ComputeInfos.h"

#include <API/Code/Debugging/Error/Error.h>

HeightMap::HeightMap( Uint32 _TextureSize ) :
	m_InitializationShader( "../../../Data/Projects/Snow/HeightInitialization.glsl" ),
	m_ToFloatShader( "../../../Data/Projects/Snow/HeightMapToFloat.glsl" ),
	m_IntegerHeightMap( _TextureSize, _TextureSize, ae::TexturePixelFormat::Red_U32 ),
	m_FloatHeightMap( _TextureSize, _TextureSize, ae::TexturePixelFormat::Red_F32 )
{
	m_InitializationShader.SetName( "Height Map Initialization Shader" );
	m_ToFloatShader.SetName( "Height Map To Float Shader" );

	m_IntegerHeightMap.SetName( "Integer Height Map" );
	m_IntegerHeightMap.SetWrapMode( ae::TextureWrapMode::ClampToEdge );

	m_FloatHeightMap.SetName( "Float Height Map" );
	m_FloatHeightMap.SetWrapMode( ae::TextureWrapMode::ClampToEdge );
}

void HeightMap::Initialize()
{
	m_InitializationShader.Bind();
	m_IntegerHeightMap.BindAsImage( 0 );
	m_InitializationShader.Dispatch( m_IntegerHeightMap.GetWidth() / ComputeLocalSize, m_IntegerHeightMap.GetHeight() / ComputeLocalSize );
	m_InitializationShader.Unbind();

	glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
	AE_ErrorCheckOpenGLError();
}

void HeightMap::ToFloat()
{
	m_ToFloatShader.Bind();
	m_IntegerHeightMap.BindAsImage( 0, ae::TextureImageBindMode::ReadOnly );
	m_FloatHeightMap.BindAsImage( 1 );
	m_ToFloatShader.Dispatch( m_FloatHeightMap.GetWidth() / ComputeLocalSize, m_FloatHeightMap.GetHeight() / ComputeLocalSize );
	m_ToFloatShader.Unbind();

	glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
	AE_ErrorCheckOpenGLError();
}

ae::Texture2D& HeightMap::GetIntegerHeightMap()
{
	return m_IntegerHeightMap;
}

ae::Texture2D& HeightMap::GetFloatHeightMap()
{
	return m_FloatHeightMap;
}

void HeightMap::Resize( Uint32 _TextureSize )
{
	m_IntegerHeightMap.Resize( _TextureSize, _TextureSize );
	m_FloatHeightMap.Resize( _TextureSize, _TextureSize );
}

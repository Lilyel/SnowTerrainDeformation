#include "SnowDisplacement.h"

#include "ComputeInfos.h"

#include <API/Code/Maths/Functions/MathsFunctions.h>
#include <API/Code/Debugging/Error/Error.h>
#include <API/Code/UI/Dependencies/IncludeImGui.h>
#include <API/Code/Aero/Aero.h>

SnowDisplacement::SnowDisplacement( Uint32 _TextureSize, ae::Texture& _HeightMap, ae::Texture& _PenetrationTexture, ae::Texture& _DistanceTexture ) :
	m_DisplacementShader( "../../../Data/Projects/Snow/Displacement.glsl" ),
	m_EveningShader( "../../../Data/Projects/Snow/Evening.glsl" ),
	m_CopyShader( "../../../Data/Projects/Snow/CopyHeightMap.glsl" ),

	m_WorkingHeightMap( _TextureSize, _TextureSize, ae::TexturePixelFormat::Red_U32 ),

	m_EveningIterationsCount( 5 )
{
	m_DisplacementShader.SetName( "Displacement Shader" );
	m_EveningShader.SetName( "Evening Shader" );
	m_CopyShader.SetName( "Copy Shader" );
}

void SnowDisplacement::Run( ae::Texture& _HeightMap, ae::Texture& _PenetrationTexture, ae::Texture& _DistanceTexture )
{
	Uint32 TextureUnit = 0;
	Uint32 ImageUnit = 0;

	const Uint32 GroupSize = m_WorkingHeightMap.GetWidth() / ComputeLocalSize;

	
	// Copy height map to temporary texture.

	_HeightMap.BindAsImage( 0, ae::TextureImageBindMode::ReadOnly );
	m_WorkingHeightMap.BindAsImage( 1, ae::TextureImageBindMode::WriteOnly );
	m_CopyShader.Bind();
	m_CopyShader.Dispatch( GroupSize, GroupSize, 1 );

	glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
	AE_ErrorCheckOpenGLError();


	// Displace the snow.

	m_WorkingHeightMap.BindAsImage( 0 );
	_PenetrationTexture.BindAsImage( 1, ae::TextureImageBindMode::ReadOnly );
	_DistanceTexture.BindAsImage( 2, ae::TextureImageBindMode::ReadOnly );

	m_DisplacementShader.Bind();
	m_DisplacementShader.Dispatch( GroupSize, GroupSize, 1 );

	glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
	AE_ErrorCheckOpenGLError();

	

	// Make the slopes a bit more even to avoid harsh ones.

	m_EveningShader.Bind();
	
	for( Uint32 i = 0; i < m_EveningIterationsCount; i++ )
	{
		m_EveningShader.Dispatch( GroupSize, GroupSize, 1 );

		glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
		AE_ErrorCheckOpenGLError();
	}


	// Copy back the result onto the height map.

	m_WorkingHeightMap.BindAsImage( 0, ae::TextureImageBindMode::ReadOnly );
	_HeightMap.BindAsImage( 1, ae::TextureImageBindMode::WriteOnly );
	m_CopyShader.Bind();
	m_CopyShader.Dispatch( GroupSize, GroupSize, 1 );

	glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
	AE_ErrorCheckOpenGLError();
}

void SnowDisplacement::Resize( Uint32 _TextureSize )
{
	m_WorkingHeightMap.Resize( _TextureSize, _TextureSize );

	glClearTexSubImage( m_WorkingHeightMap.GetTextureID(), 0, 0, 0, 0, m_WorkingHeightMap.GetWidth(), m_WorkingHeightMap.GetHeight(), 1,
						ae::ToGLFormat( m_WorkingHeightMap.GetFormat() ), ae::ToGLType( m_WorkingHeightMap.GetFormat() ), nullptr );
	AE_ErrorCheckOpenGLError();
}


void SnowDisplacement::ToEditor()
{
	int IterationsCount = Cast( int, m_EveningIterationsCount );
	if( ImGui::DragInt( "Evening Iterations", &IterationsCount, 1.0, 0, 50 ) )
		m_EveningIterationsCount = Cast( Uint32, IterationsCount );
}

#include "ImageBasedLighting.h"

#include "../Framebuffer/Framebuffer.h"
#include "../Material/Material.h"
#include "../Skybox/Skybox.h"
#include "../Camera/CameraPerspective.h"
#include "../Mesh/2D/FullscreenQuadMesh.h"
#include "../../Aero/Aero.h"

namespace ae
{

	ImageBasedLighting::ImageBasedLighting( CubeMap& _EnvironmentMap ) :
		m_Irradiance( 32, 32, TexturePixelFormat::RGB_F16 ),
		m_Radiance( 128, 128, TexturePixelFormat::RGB_F16 ),
		m_BRDFLut( 512, 512, TexturePixelFormat::RGB_F16 )
	{
		const std::string IBLName = std::string( "IBL_" ) + std::to_string( GetResourceID() );
		SetName( IBLName );

		m_Irradiance.SetWrapMode( TextureWrapMode::ClampToEdge );
		m_Irradiance.SetName( IBLName + "_Irradiance" );

		m_Radiance.SetWrapMode( TextureWrapMode::ClampToEdge );
		m_Radiance.SetFilterMode( TextureFilterMode::Linear_MipMap_Linear );
		m_Radiance.GenerateMipMap();
		m_Radiance.SetName( IBLName + "_Radiance" );

		m_BRDFLut.SetWrapMode( TextureWrapMode::ClampToEdge );
		m_BRDFLut.SetName( IBLName + "_LutBRDF" );

		Precompute( _EnvironmentMap );
	}

	void ImageBasedLighting::Set( CubeMap& _EnvironmentMap )
	{
		Precompute( _EnvironmentMap );
	}

	const CubeMap& ImageBasedLighting::GetIrradianceMap() const
	{
		return m_Irradiance;
	}

	const CubeMap& ImageBasedLighting::GetRadianceMap() const
	{
		return m_Radiance;
	}

	const Texture2D& ImageBasedLighting::GetBRDFLut() const
	{
		return m_BRDFLut;
	}

	Uint32 ImageBasedLighting::GetMaxLod() const
	{
		return m_MaxLod;
	}

	void ImageBasedLighting::Precompute( CubeMap& _EnvironmentMap )
	{
		// Prepare the environment material and mesh (cube) to render it.
		TextureWrapMode SavedWrapMode = _EnvironmentMap.GetWrapMode();
		TextureFilterMode SavedFilter = _EnvironmentMap.GetFilterMode();
		_EnvironmentMap.SetWrapMode( TextureWrapMode::ClampToEdge );
		_EnvironmentMap.SetFilterMode( TextureFilterMode::Linear_MipMap_Linear );
		_EnvironmentMap.GenerateMipMap();

		Material EnvironmentMat;
		EnvironmentMat.AddCubeMapParameterToMaterial( "CubeMap", "CubeMap", &_EnvironmentMap );
		EnvironmentMat.AddFloatParameterToMaterial( "Roughness", "Roughness", 0.0f );

		Skybox EnvironmentSkybox( _EnvironmentMap );
		EnvironmentSkybox.SetMaterial( EnvironmentMat );


		// Projection and view for each side of the environmenet map.

		const Matrix4x4&& Projection = std::move( Matrix4x4::GetPerspectiveMatrix( Math::DegToRad_Const( 90.0f ), 1.0f, 0.1f, 10.0f ) );
		Matrix4x4 Views[6] =
		{
			Matrix4x4::GetLookAtMatrix( Vector3::Zero, Vector3( 1.0f, 0.0f, 0.0f ), Vector3( 0.0f, 1.0f, 0.0f ) ),
			Matrix4x4::GetLookAtMatrix( Vector3::Zero, Vector3( -1.0f, 0.0f, 0.0f ), Vector3( 0.0f, 1.0f, 0.0f ) ),
			Matrix4x4::GetLookAtMatrix( Vector3::Zero, Vector3( 0.0f, 1.0f, 0.0f ), Vector3( 0.0f, 0.0f, 1.0f ) ),
			Matrix4x4::GetLookAtMatrix( Vector3::Zero, Vector3( 0.0f, -1.0f, 0.0f ), Vector3( 0.0f, 0.0f, -1.0f ) ),
			Matrix4x4::GetLookAtMatrix( Vector3::Zero, Vector3( 0.0f, 0.0f, 1.0f ), Vector3( 0.0f, 1.0f, 0.0f ) ),
			Matrix4x4::GetLookAtMatrix( Vector3::Zero, Vector3( 0.0f, 0.0f, -1.0f ), Vector3( 0.0f, 1.0f, 0.0f ) )
		};



		// Setup diffuse irradiance material.

		const std::string& PathToEngineData = Aero.GetPathToEngineData() + "/Shader/";
		Shader IrradianceShader( PathToEngineData + "CubeMapConvolutionVertex.glsl", PathToEngineData + "CubeMapDiffuseConvolutionFragment.glsl" );

		IrradianceShader.Bind();
		IrradianceShader.SetMatrix4x4( IrradianceShader.GetUniformLocation( "ConvProjection" ), Projection );
		IrradianceShader.Unbind();

		EnvironmentMat.SetShader( IrradianceShader );


		Framebuffer FBO( m_Irradiance.GetWidth( 0 ), m_Irradiance.GetHeight( 0 ), Framebuffer::AttachementPreset::RGBA_U8_DepthStencil_U_24_8 );
		FBO.Bind();

		// Apply filter to retrieve the irradiance on each side of the environment map and store the result in a new cube map.
		for( Uint32 i = 0; i < 6; i++ )
		{
			IrradianceShader.Bind();
			IrradianceShader.SetMatrix4x4( IrradianceShader.GetUniformLocation( "ConvView" ), Views[i] );
			IrradianceShader.Unbind();

			glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_Irradiance.GetTextureID(), 0 );
			// Check if the framebuffer is well created.
			if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
				AE_LogError( "Framebuffer creation failed." );


			FBO.Clear();

			FBO.Draw( EnvironmentSkybox );
		}

		FBO.Unbind();



		// Setup specular irradiance material.

		Shader RadianceShader( PathToEngineData + "CubeMapConvolutionVertex.glsl", PathToEngineData + "CubeMapSpecularConvolutionFragment.glsl" );

		RadianceShader.Bind();
		RadianceShader.SetMatrix4x4( RadianceShader.GetUniformLocation( "ConvProjection" ), Projection );
		RadianceShader.Unbind();

		EnvironmentMat.SetShader( RadianceShader );

		m_MaxLod = Cast( Uint32, Math::Log2( Cast( float, m_Radiance.GetWidth( 0 ) ) ) );
		for( Uint32 m = 0; m <= m_MaxLod; m++ )
		{
			const Uint32 MipWidth = Cast( Uint32, Cast( float, m_Radiance.GetWidth( 0 ) ) * Math::Pow( 0.5f, Cast( float, m ) ) );
			const Uint32 MipHeight = Cast( Uint32, Cast( float, m_Radiance.GetHeight( 0 ) ) * Math::Pow( 0.5f, Cast( float, m ) ) );

			FBO.Resize( MipWidth, MipHeight );

			const float Roughness = Cast( float, m ) / Cast( float, m_MaxLod - 1 );

			RadianceShader.Bind();
			RadianceShader.SetFloat( RadianceShader.GetUniformLocation( "Roughness" ), Roughness );
			RadianceShader.Unbind();

			FBO.Bind();

			// Apply filter to retrieve the irradiance on each side of the environment map and store the result in a new cube map.
			for( Uint32 i = 0; i < 6; i++ )
			{
				RadianceShader.Bind();
				RadianceShader.SetMatrix4x4( RadianceShader.GetUniformLocation( "ConvView" ), Views[i] );
				RadianceShader.Unbind();

				glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_Radiance.GetTextureID(), Cast( GLint, m ) );
				// Check if the framebuffer is well created.
				if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
					AE_LogError( "Framebuffer creation failed." );


				FBO.Clear();

				FBO.Draw( EnvironmentSkybox );
			}

			FBO.Unbind();
		}


		// Setup BRDF integration.
		Shader IntegrationShader( PathToEngineData + "FramebufferVertex.glsl", PathToEngineData + "IntegrateBRDF.glsl" );
		Material IntegrationMat( IntegrationShader );

		FullscreenQuadMesh Quad;
		Quad.SetMaterial( IntegrationMat );

		FBO.Resize( m_BRDFLut.GetWidth(), m_BRDFLut.GetHeight() );

		FBO.Bind();
		glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_BRDFLut.GetTextureID(), 0 );
		// Check if the framebuffer is well created.
		if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
			AE_LogError( "Framebuffer creation failed." );

		FBO.Clear();

		FBO.Draw( Quad );

		FBO.Unbind();

		_EnvironmentMap.SetWrapMode( SavedWrapMode );
		_EnvironmentMap.SetFilterMode( SavedFilter );
	}

}

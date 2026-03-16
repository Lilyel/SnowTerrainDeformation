#include "GammaCorrection.h"

#include "../Texture/Texture2D.h"
#include "../Framebuffer/Attachement/FramebufferAttachement.h"
#include "../Material/FramebufferMaterial.h"
#include "../../Aero/Aero.h"
#include "../../Editor/TypesToEditor/GammaCorrectionToEditor.h"

namespace ae
{

	GammaCorrection::GammaCorrection() :
		m_GammaShader( Aero.GetPathToEngineData() + "/Shader/FramebufferVertex.glsl", Aero.GetPathToEngineData() + "/Shader/GammaCorrectionFragment.glsl" ),
		m_Exposure( 1.0f ),
		m_Gamma( 2.2f )
	{
		const std::string GammaCorrectionName = std::string( "GammaCorrection_" ) + std::to_string( GetResourceID() );
		SetName( GammaCorrectionName );

		m_GammaShader.SetName( GammaCorrectionName + "_Shader" );

		m_Quad.SetName( GammaCorrectionName + "_Quad" );
	}

	void GammaCorrection::Apply( Texture2D& _Texture, Bool _SaveFBOs )
	{
		// Setup blur shader.
		m_GammaShader.Bind();
		m_GammaShader.SetFloat( m_GammaShader.GetUniformLocation( "Exposure" ), m_Exposure );
		m_GammaShader.SetFloat( m_GammaShader.GetUniformLocation( "Gamma" ), m_Gamma );
		m_GammaShader.Unbind();

		ShaderParameterTexture* QuadTextureParam = (ShaderParameterTexture*)m_Quad.GetMaterial().GetParameter( Material::DefaultParameters::FramebufferTexture );

		// Setup FBO.
		if( !_SaveFBOs || m_FBO == nullptr || m_FBO->GetAttachementTexture()->GetFormat() != _Texture.GetFormat() )
		{
			if( !Aero.CheckContext() )
				return;

			FramebufferAttachement Attachement( FramebufferAttachement::Type::Color_0, _Texture.GetFormat(), _Texture.GetFilterMode(), _Texture.GetDimension() );
			m_FBO = std::make_unique<Framebuffer>( _Texture.GetWidth(), _Texture.GetHeight(), Attachement );

			m_FBO->Bind();
			m_FBO->SetDepthMode( DepthMode::NoDepthTest );
			m_FBO->Unbind();
		}

		if( m_FBO == nullptr )
			return;

		m_FBO->Resize( _Texture.GetWidth(), _Texture.GetHeight() );


		// Apply the gamma correction.

		m_Quad.GetMaterial().SetShader( m_GammaShader );
		QuadTextureParam->SetValue( &_Texture );
		
		m_FBO->Bind();
		m_FBO->Draw( m_Quad );
		m_FBO->Unbind();


		// Put result in the parameter texture.

		m_Quad.GetMaterial().SetShader( *Aero.GetResourcesManager().GetDefaultFramebufferShader() );
		QuadTextureParam->SetValue( m_FBO->GetAttachementTexture() );

		m_FBO->Bind();
		_Texture.AttachToFramebuffer( m_FBO->GetFirstAvailableAttachement() );
		m_FBO->Draw( m_Quad );
		m_FBO->GetAttachementTexture()->AttachToFramebuffer( m_FBO->GetFirstAvailableAttachement() );
		m_FBO->Unbind();
	}

	void GammaCorrection::SetExposure( float _Exposure )
	{
		m_Exposure = _Exposure;
	}

	float GammaCorrection::GetExposure() const
	{
		return m_Exposure;
	}

	void GammaCorrection::SetGamma( float _Gamma )
	{
		m_Gamma = Math::Max( _Gamma, Math::Epsilon() );
	}

	float GammaCorrection::GetGamma() const
	{
		return m_Gamma;
	}

	void GammaCorrection::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::GammaCorrectionToEditor( *this );
	}

}

#include "Bloom.h"

#include "../Texture/Texture2D.h"
#include "../Shader/ShaderParameter/ShaderParameterTexture.h"
#include "../../Aero/Aero.h"
#include "../../Editor/TypesToEditor/BloomToEditor.h"

namespace ae
{

	Bloom::Bloom() :
		m_ExtractionShader( Aero.GetPathToEngineData() + "/Shader/FramebufferVertex.glsl", Aero.GetPathToEngineData() + "/Shader/BloomExtractionFragment.glsl" ),
		m_BlendShader( Aero.GetPathToEngineData() + "/Shader/FramebufferVertex.glsl", Aero.GetPathToEngineData() + "/Shader/BloomBlendFragment.glsl" ),
		m_BrightnessThreshold( 0.2126f, 0.7152f, 0.0722f )
	{
		const std::string BloomName = std::string( "Bloom_" ) + std::to_string( GetResourceID() );
		SetName( BloomName );

		m_ExtractionShader.SetName( BloomName + "_ExrtractionShader" );
		m_BlendShader.SetName( BloomName + "_BlendShader" );

		m_BloomQuad.SetName( BloomName + "_Quad" );

		m_ColorTextureParam = m_BloomQuad.GetMaterial().AddTextureParameterToMaterial( "ColorTexture", "ColorTexture", nullptr );
		m_BloomTextureParam = m_BloomQuad.GetMaterial().AddTextureParameterToMaterial( "BloomTexture", "BloomTexture", nullptr );
	}

	void Bloom::Apply( Texture2D& _Texture, Bool _SaveFBOs )
	{
		if( m_ColorTextureParam == nullptr || m_BloomTextureParam == nullptr )
		{
			AE_LogError( "Invalid bloom material for the quad : impossible to set the texture for the blend shader." );
			return;
		}

		// Setup extraction shader.
		m_ExtractionShader.Bind();
		m_ExtractionShader.SetVector3( m_ExtractionShader.GetUniformLocation( "BrightnessThreshold" ), m_BrightnessThreshold );
		m_ExtractionShader.Unbind();

		ShaderParameterTexture* QuadTextureParam = (ShaderParameterTexture*)m_BloomQuad.GetMaterial().GetParameter( Material::DefaultParameters::FramebufferTexture );

		// Setup FBO.
		if( !_SaveFBOs || m_FBO == nullptr || m_FBO->GetAttachementTexture()->GetFormat() != _Texture.GetFormat() )
		{
			if( !Aero.CheckContext() )
				return;

			FramebufferAttachement AttachementColor( FramebufferAttachement::Type::Color_0, _Texture.GetFormat(), _Texture.GetFilterMode(), _Texture.GetDimension() );
			FramebufferAttachement AttachementBrightColor( FramebufferAttachement::Type::Color_1, _Texture.GetFormat(), _Texture.GetFilterMode(), _Texture.GetDimension() );
			m_FBO = std::make_unique<Framebuffer>( _Texture.GetWidth(), _Texture.GetHeight(), std::initializer_list<FramebufferAttachement>{ AttachementColor, AttachementBrightColor } );

			m_FBO->Bind();
			m_FBO->SetDepthMode( DepthMode::NoDepthTest );
			m_FBO->Unbind();
		}

		if( m_FBO == nullptr )
			return;

		m_FBO->Resize( _Texture.GetWidth(), _Texture.GetHeight() );


		// Extract bright colors.

		m_BloomQuad.GetMaterial().SetShader( m_ExtractionShader );
		QuadTextureParam->SetValue( &_Texture );

		m_FBO->Bind();
		m_FBO->Clear();
		m_FBO->Draw( m_BloomQuad );
		m_FBO->Unbind();


		// Blur the bright colors.
		GaussianBlur::Apply( *(Texture2D*)m_FBO->GetAttachementTexture( FramebufferAttachement::Type::Color_1 ) );


		// Blend the color and the bloom texture onto the parameter texture.

		m_BloomQuad.GetMaterial().SetShader( m_BlendShader );
		m_ColorTextureParam->SetValue( m_FBO->GetAttachementTexture( FramebufferAttachement::Type::Color_0 ) );
		m_BloomTextureParam->SetValue( m_FBO->GetAttachementTexture( FramebufferAttachement::Type::Color_1 ) );

		m_FBO->Bind();
		_Texture.AttachToFramebuffer( m_FBO->GetFirstAvailableAttachement() );
		m_FBO->Draw( m_BloomQuad );
		m_FBO->GetAttachementTexture()->AttachToFramebuffer( m_FBO->GetFirstAvailableAttachement() );
		m_FBO->Unbind();
	}

	void Bloom::SetBrightnessThreshold( const Vector3& _Threshold )
	{
		m_BrightnessThreshold = _Threshold;
	}

	const Vector3& Bloom::GetBrightnessThreshold() const
	{
		return m_BrightnessThreshold;
	}

	void Bloom::ToEditor()
	{
		GaussianBlur::ToEditor();
		priv::ui::BloomToEditorBegin();
		priv::ui::BloomToEditor( *this );
		priv::ui::BloomToEditorEnd();
	}

}

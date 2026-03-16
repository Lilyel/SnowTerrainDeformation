#include "GaussianBlur.h"

#include "../Texture/Texture2D.h"
#include "../Framebuffer/Attachement/FramebufferAttachement.h"
#include "../Material/FramebufferMaterial.h"
#include "../../Maths/Functions/MathsFunctions.h"
#include "../../Aero/Aero.h"
#include "../../Editor/TypesToEditor/GaussianBlurToEditor.h"

namespace ae
{
	GaussianBlur::GaussianBlur() :
		m_GaussianShader( Aero.GetPathToEngineData() + "/Shader/FramebufferVertex.glsl", Aero.GetPathToEngineData() + "/Shader/GaussianBlurFragment.glsl" ),
		m_IterationsCount( 1u ),
		m_Coefs{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		m_StandardDeviation( 5.0f ),
		m_IsNormalized( False ),
		m_MustUpdateCoefs( True ),
		m_Radius( Radius::_5x5 )
	{
		const std::string BlurName = std::string( "GaussianBlur_" ) + std::to_string( GetResourceID() );
		SetName( BlurName );

		m_GaussianShader.SetName( BlurName + "_Shader" );

		m_Quad.SetName( BlurName + "_Quad" );
	}

	void GaussianBlur::Apply( Texture2D& _Texture, Bool _SaveFBOs )
	{
		if( m_IterationsCount == 0u )
			return;

		TextureFilterMode SavedFilterMode = _Texture.GetFilterMode();
		TextureWrapMode SavedWrapMode = _Texture.GetWrapMode();

		_Texture.SetFilterMode( TextureFilterMode::Linear );
		_Texture.SetWrapMode( TextureWrapMode::ClampToEdge );

		UpdateCoefs();

		// Setup blur shader.
		m_GaussianShader.Bind();
		m_GaussianShader.SetFloat( m_GaussianShader.GetUniformLocation( "Coefs[0]" ), m_Coefs[0] );
		m_GaussianShader.SetFloat( m_GaussianShader.GetUniformLocation( "Coefs[1]" ), m_Coefs[1] );
		m_GaussianShader.SetFloat( m_GaussianShader.GetUniformLocation( "Coefs[2]" ), m_Coefs[2] );
		m_GaussianShader.SetFloat( m_GaussianShader.GetUniformLocation( "Coefs[3]" ), m_Coefs[3] );
		m_GaussianShader.SetFloat( m_GaussianShader.GetUniformLocation( "Coefs[4]" ), m_Coefs[4] );
		m_GaussianShader.Unbind();

		// Setup ping-pong FBOs.

		Uint32 NewWidth = _Texture.GetWidth() / Cast( Uint32, m_Radius );
		Uint32 NewHeight = _Texture.GetHeight() / Cast( Uint32, m_Radius );

		if( !_SaveFBOs || m_HorizontalFBO == nullptr || m_VerticalFBO == nullptr || m_HorizontalFBO->GetAttachementTexture()->GetFormat() != _Texture.GetFormat() )
			CreateFBOs( _Texture, NewWidth, NewHeight );

		if( m_HorizontalFBO == nullptr || m_VerticalFBO == nullptr )
			return;

		m_HorizontalFBO->Resize( NewWidth, NewHeight );
		m_VerticalFBO->Resize( NewWidth, NewHeight );


		m_Quad.GetMaterial().SetShader( m_GaussianShader );


		Int32 IsHorizontalLocation = m_GaussianShader.GetUniformLocation( "IsHorizontal" );
		ShaderParameterTexture* QuadTextureParam = (ShaderParameterTexture*)m_Quad.GetMaterial().GetParameter( Material::DefaultParameters::FramebufferTexture );

		// Do blur iteration.
		for( Uint32 i = 0; i < m_IterationsCount; i++ )
		{
			m_GaussianShader.Bind();
			m_GaussianShader.SetBool( IsHorizontalLocation, True );
			m_GaussianShader.Unbind();

			QuadTextureParam->SetValue( i == 0 ? &_Texture : m_VerticalFBO->GetAttachementTexture() );

			m_HorizontalFBO->Bind();
			m_HorizontalFBO->Draw( m_Quad );
			m_HorizontalFBO->Unbind();

			m_GaussianShader.Bind();
			m_GaussianShader.SetBool( IsHorizontalLocation, False );
			m_GaussianShader.Unbind();

			QuadTextureParam->SetValue( m_HorizontalFBO->GetAttachementTexture() );

			m_VerticalFBO->Bind();
			m_VerticalFBO->Draw( m_Quad );
			m_VerticalFBO->Unbind();
		}

		// Put result in the parameter texture.

		m_Quad.GetMaterial().SetShader( *Aero.GetResourcesManager().GetDefaultFramebufferShader() );
		QuadTextureParam->SetValue( m_VerticalFBO->GetAttachementTexture() );

		m_HorizontalFBO->Resize( _Texture.GetWidth(), _Texture.GetHeight() );

		m_HorizontalFBO->Bind();
		_Texture.AttachToFramebuffer( m_HorizontalFBO->GetFirstAvailableAttachement() );
		m_HorizontalFBO->Draw( m_Quad );
		m_HorizontalFBO->GetAttachementTexture()->AttachToFramebuffer( m_HorizontalFBO->GetFirstAvailableAttachement() );
		m_HorizontalFBO->Unbind();

		_Texture.SetFilterMode( SavedFilterMode );
		_Texture.SetWrapMode( SavedWrapMode );
	}

	void GaussianBlur::SetIterationsCount( Uint32 _IterationsCount )
	{
		m_IterationsCount = _IterationsCount;
	}

	Uint32 GaussianBlur::GetIterationsCount() const
	{
		return m_IterationsCount;
	}

	void GaussianBlur::SetStandardDeviation( float _StandardDeviation )
	{
		m_StandardDeviation = Math::Max( _StandardDeviation, 0.01f );
		m_MustUpdateCoefs = True;
	}

	float GaussianBlur::GetStandardDeviation() const
	{
		return m_StandardDeviation;
	}

	void GaussianBlur::NormalizeGaussian( Bool _Normalize )
	{
		m_IsNormalized = _Normalize;
		m_MustUpdateCoefs = True;
	}

	Bool GaussianBlur::IsGaussianNormalized() const
	{
		return m_IsNormalized;
	}

	void GaussianBlur::SetRadius( Radius _Radius )
	{
		m_Radius = _Radius;
	}

	GaussianBlur::Radius GaussianBlur::GetRadius() const
	{
		return m_Radius;
	}

	void GaussianBlur::GetCoefs( AE_Out float _Coefs[5] )
	{
		UpdateCoefs();

		std::memcpy( _Coefs, m_Coefs, 5 * sizeof( float ) );
	}

	void GaussianBlur::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::GaussianBlurToEditorBegin();
		priv::ui::GaussianBlurToEditor( *this );
		priv::ui::GaussianBlurToEditorEnd();
	}

	void GaussianBlur::UpdateCoefs()
	{
		if( !m_MustUpdateCoefs )
			return;

		float Normalization = 0.0f;
		for( Uint8 x = 0; x < 5; x++ )
		{
			const float Coef = Math::Gaussian<float>( Cast( float, x ), m_StandardDeviation );
			m_Coefs[x] = Coef;
			Normalization += Coef * ( x == 0 ? 1.0f : 2.0f );
		}

		if( m_IsNormalized )
		{
			for( Uint8 x = 0; x < 5; x++ )
				m_Coefs[x] /= Normalization;
		}

		m_MustUpdateCoefs = False;
	}

	void GaussianBlur::CreateFBOs( const Texture2D& _Texture, Uint32 _Width, Uint32 _Height )
	{
		if( !Aero.CheckContext() )
			return;

		FramebufferAttachement Attachement( FramebufferAttachement::Type::Color_0, _Texture.GetFormat(), TextureFilterMode::Linear, TextureDimension::Texture2D );
		m_HorizontalFBO = std::make_unique<Framebuffer>( _Width, _Height, Attachement );
		m_VerticalFBO = std::make_unique<Framebuffer>( _Width, _Height, Attachement );

		m_HorizontalFBO->GetAttachementTexture()->SetWrapMode( TextureWrapMode::ClampToEdge );
		m_VerticalFBO->GetAttachementTexture()->SetWrapMode( TextureWrapMode::ClampToEdge );

		m_HorizontalFBO->Bind();
		m_HorizontalFBO->SetDepthMode( DepthMode::NoDepthTest );
		m_HorizontalFBO->Unbind();

		m_VerticalFBO->Bind();
		m_VerticalFBO->SetDepthMode( DepthMode::NoDepthTest );
		m_VerticalFBO->Unbind();
	}

}

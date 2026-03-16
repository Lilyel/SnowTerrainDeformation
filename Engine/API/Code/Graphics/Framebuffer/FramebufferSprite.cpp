#include "FramebufferSprite.h"

#include "../Material/FramebufferMaterial.h"
#include "../../Editor/TypesToEditor/WorldObjectToEditor.h"
#include "../../Editor/TypesToEditor/FramebufferToEditor.h"

#include "../../Aero/Aero.h"

namespace ae
{
    FramebufferSprite::FramebufferSprite( Framebuffer& _Framebuffer ) :
        Drawable( BufferType::Static, AttributePointer::DefaultFramebuffer ),
        m_Framebuffer( _Framebuffer ),
        m_QuadVertices( 4 ),
        m_QuadIndices( { 0, 1, 2, 0, 2, 3 } ),
        m_Attachement( _Framebuffer.GetFirstAvailableAttachement() ),
        m_TextureParameter( nullptr ),
        m_IsDepthParameter( nullptr )
    {
        m_QuadVertices[0].Position = Vector2( -1.0f, 1.0f );
        m_QuadVertices[1].Position = Vector2( -1.0f, -1.0f );
        m_QuadVertices[2].Position = Vector2( 1.0f, -1.0f );
        m_QuadVertices[3].Position = Vector2( 1.0f, 1.0f );

        m_QuadVertices[0].UV = Vector2( 0.0f, 1.0f );
        m_QuadVertices[1].UV = Vector2( 0.0f, 0.0f );
        m_QuadVertices[2].UV = Vector2( 1.0f, 0.0f );
        m_QuadVertices[3].UV = Vector2( 1.0f, 1.0f );

        UpdateVerticesBuffer( m_QuadVertices );
        UpdateIndicesBuffer( m_QuadIndices );

        SetupMaterial();
        UpdateMaterialTexture();

        SetName( std::string( "FramebufferSprite_" ) + std::to_string( GetObjectID() ) );
    }

    void FramebufferSprite::SetFramebuffer( Framebuffer& _Framebuffer )
    {
        m_Framebuffer = std::ref( _Framebuffer );
        m_Attachement = _Framebuffer.GetFirstAvailableAttachement();
        UpdateMaterialTexture();
    }


    const Framebuffer& FramebufferSprite::GetFramebuffer() const
    {
        return m_Framebuffer.get();
    }

	Framebuffer& FramebufferSprite::GetFramebuffer()
	{
		return m_Framebuffer.get();
	}

    void FramebufferSprite::SetAttachementToDraw( FramebufferAttachement::Type _Attachement )
    {
        if( m_Framebuffer.get().HasAttachement( _Attachement ) )
        {
            m_Attachement = _Attachement;
            UpdateMaterialTexture();
        }
    }

    FramebufferAttachement::Type FramebufferSprite::GetAttachementToDraw() const
    {
        return m_Attachement;
    }

	void FramebufferSprite::ToEditor()
	{
		priv::ui::WorldObjectToEditor( *this );
		priv::ui::FramebufferToEditor( GetFramebuffer() );
	}

    void FramebufferSprite::UpdateMaterialTexture()
    {
        const Framebuffer& CurrentFramebuffer = m_Framebuffer.get();
        if( !CurrentFramebuffer.HasAttachement( m_Attachement ) )
            return;

        m_TextureParameter = m_MaterialRef->GetParameter<ShaderParameterTexture>( Material::DefaultParameters::FramebufferTexture );
        if( m_TextureParameter != nullptr )
            m_TextureParameter->SetValue( CurrentFramebuffer.GetAttachementTexture( m_Attachement ) );
            
        m_IsDepthParameter = m_MaterialRef->GetParameter<ShaderParameterBool>( Material::DefaultParameters::FramebufferIsDepth );
        if( m_IsDepthParameter != nullptr )
            m_IsDepthParameter->SetValue( FramebufferAttachement::IsDepthAttachement( m_Attachement ) );
    }

    void FramebufferSprite::SetupMaterial()
    {
        SetMaterial( *Aero.GetResourcesManager().GetDefaultFramebufferMaterial() );
    }

} // ae


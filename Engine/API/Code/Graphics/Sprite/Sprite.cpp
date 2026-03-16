#include "Sprite.h"

#include "../Renderer/Renderer.h"
#include "../Texture/Texture2D.h"
#include "../Material/Material.h"
#include "../Material/SpriteMaterial.h"
#include "../Shader/ShaderParameter/ShaderParameterTextureBool.h"
#include "../../Aero/Aero.h"

#include "../../Editor/TypesToEditor/WorldObjectToEditor.h"
#include "../../Editor/TypesToEditor/Transform2DToEditor.h"
#include "../../Editor/TypesToEditor/SpriteToEditor.h"
#include "../../Editor/TypesToEditor/MaterialToEditor.h"



namespace ae
{
	Sprite::Sprite( const Texture2D& _Texture, Bool _NewMaterialInstance ) :
		Mesh2D( 4, 6 ),
		m_TextureParameter( nullptr )
	{
		SetBufferType( BufferType::Static );
		SetAttributePointerTags( AttributePointer::Default2D );

		SetupMaterial( _NewMaterialInstance );

		SetupIndices();

		SetTexture( _Texture );


		SetName( std::string( "Sprite_" ) + std::to_string( GetObjectID() ) );
	}

	Sprite::Sprite( const Texture2D& _Texture, const IntRect& _SubRect, Bool _IsNormalizedCoordinates, Bool _NewMaterialInstance ) :
		Mesh2D( 4, 6 ),
		m_TextureParameter( nullptr )
	{
		SetBufferType( BufferType::Static );
		SetAttributePointerTags( AttributePointer::Default2D );

		SetupMaterial( _NewMaterialInstance );

		SetupIndices();

		SetTexture( _Texture, _SubRect, _IsNormalizedCoordinates );


		SetName( std::string( "Sprite_" ) + std::to_string( GetObjectID() ) );
	}


	void Sprite::SetTexture( const Texture2D& _Texture, Bool _ResetRect )
	{
		m_Texture = &_Texture;

		if( _ResetRect )
			SetTextureRect( IntRect( 0, 0, _Texture.GetWidth(), _Texture.GetHeight() ) );

		UpdateMaterialTexture();
	}

	void Sprite::SetTexture( const Texture2D& _Texture, const IntRect& _SubRect, Bool _IsNormalizedCoordinates )
	{
		m_Texture = &_Texture;
		SetTextureRect( _SubRect, _IsNormalizedCoordinates );

		UpdateMaterialTexture();
	}

	void Sprite::SetTextureRect( const IntRect& _SubRect, Bool _IsNormalizedCoordinates )
	{
		if( _IsNormalizedCoordinates )
		{
			m_TextureRect = IntRect( _SubRect.Left * m_Texture->GetWidth(),
									 _SubRect.Top * m_Texture->GetHeight(),
									 _SubRect.Right * m_Texture->GetWidth(),
									 _SubRect.Bottom * m_Texture->GetHeight() );
		}
		else
			m_TextureRect = _SubRect;	

		UpdateQuad();
	}

	void Sprite::SetRelativOrigin( const Vector2& _RelativOrigin )
	{
		const float SizeX = Cast( float, m_TextureRect.Right - m_TextureRect.Left );
		const float SizeY = Cast( float, m_TextureRect.Bottom - m_TextureRect.Top );

		const Vector2 NewOrigin( _RelativOrigin.X * SizeX, _RelativOrigin.Y * SizeY );

		SetOrigin( NewOrigin );
	}

	void Sprite::SetRelativOrigin( float _RelativOriginX, float _RelativOriginY )
	{
		const float SizeX = Cast( float, m_TextureRect.Right - m_TextureRect.Left );
		const float SizeY = Cast( float, m_TextureRect.Bottom - m_TextureRect.Top );

		const Vector2 NewOrigin( _RelativOriginX * SizeX, _RelativOriginY * SizeY );

		SetOrigin( NewOrigin );
	}

	void Sprite::SetMaterial( Material& _Material )
	{
		Drawable::SetMaterial( _Material );
		m_TextureParameter = m_MaterialRef->GetParameter<ShaderParameterTextureBool>( Material::DefaultParameters::SpriteTexture );
	}

	const Texture2D* Sprite::GetTexture() const
	{
		return m_Texture;
	}

    void Sprite::ToEditor()
    {
        priv::ui::WorldObjectToEditor( *this );
        priv::ui::TransformToEditor( *this );
        priv::ui::SpriteToEditor( *this );
		priv::ui::MaterialToEditor( GetMaterial() );
    }

	void Sprite::SetupIndices()
	{
		m_Indices = { 0, 3, 1, 1, 3, 2 };
	}

	void Sprite::UpdateQuad()
	{
		const float SizeX = Cast( float, m_TextureRect.Right - m_TextureRect.Left );
		const float SizeY = Cast( float, m_TextureRect.Bottom - m_TextureRect.Top );

		m_Vertices[0].Position = Vector2( 0.0f, 0.0f );
		m_Vertices[1].Position = Vector2( SizeX, 0.0f );
		m_Vertices[2].Position = Vector2( SizeX, SizeY );
		m_Vertices[3].Position = Vector2( 0.0f, SizeY );

		m_Vertices[0].UV = Vector2( Cast( float, m_TextureRect.Left ) / SizeX, Cast( float, m_TextureRect.Top ) / SizeY );
		m_Vertices[1].UV = Vector2( Cast( float, m_TextureRect.Right ) / SizeX, Cast( float, m_TextureRect.Top ) / SizeY  );
		m_Vertices[2].UV = Vector2( Cast( float, m_TextureRect.Right ) / SizeX, Cast( float, m_TextureRect.Bottom ) / SizeY );
		m_Vertices[3].UV = Vector2( Cast( float, m_TextureRect.Left ) / SizeX, Cast( float, m_TextureRect.Bottom ) / SizeY );

		ApplyChanges();
	}

	void Sprite::UpdateMaterialTexture()
	{
		if( m_TextureParameter != nullptr )
			m_TextureParameter->SetTexture( m_Texture );
	}

	void Sprite::SetupMaterial( Bool _NewMaterialInstance )
	{
		SpriteMaterial* Mat = Aero.GetResourcesManager().GetDefault2DMaterial();

		// Create a copy of the material in case the user wants individual material for sprites.
		if( _NewMaterialInstance )
		{
			Mat = new SpriteMaterial( *Mat );
			Mat->SetIsInstance( True );
			Mat->GetTexture().SetTexture( nullptr );
		}

		SetMaterial( *Mat );
		m_TextureParameter = m_MaterialRef->GetParameter<ShaderParameterTextureBool>( Material::DefaultParameters::SpriteTexture );
	}
} // ae
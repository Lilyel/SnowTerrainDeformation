#include "Framebuffer.h"

#include "../../Debugging/Debugging.h"

#include "../Texture/Texture1D.h"
#include "../Texture/Texture2D.h"
#include "../Texture/TextureMultisample.h"
#include "../Texture/Texture3D.h"
#include "../CubeMap/CubeMap.h"


namespace ae
{
	std::stack<Uint32> Framebuffer::m_BoundFramebuffers;

	Framebuffer::Framebuffer( Uint32 _Width, Uint32 _Height, AttachementPreset _Preset ) :
		m_FramebufferID( 0 ),
		m_Width( _Width ),
		m_Height( _Height )
	{
		CreateFramebuffer();
		Create( _Preset );
		InitializeRendering();
	}

	Framebuffer::Framebuffer( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _Attachement ) :
		m_FramebufferID( 0 ),
		m_Width( _Width ),
		m_Height( _Height )
	{
		CreateFramebuffer();
		Create( { _Attachement } );
		InitializeRendering();
	}

	Framebuffer::Framebuffer( Uint32 _Width, Uint32 _Height, std::initializer_list<FramebufferAttachement> _Attachements ) :
		m_FramebufferID( 0 ),
		m_Width( _Width ),
		m_Height( _Height )
	{
		CreateFramebuffer();

		if( _Attachements.size() == 0 )
			throw std::exception( "Cannot create a framebuffer with no attachement." );

		Create( _Attachements );
		InitializeRendering();
	}

	Framebuffer::~Framebuffer()
	{
		FreeResource();
	}

	void Framebuffer::Resize( Uint32 _Width, Uint32 _Height )
	{
		// Do not resize if the new size is the same.
		if( m_Width == _Width && m_Height == _Height )
			return;

		m_Width = _Width;
		m_Height = _Height;
		UpdateAttachement();
	}

	void Framebuffer::BindAttachementTexture( FramebufferAttachement::Type _Type ) const
	{
		glBindTexture( GL_TEXTURE_2D, GetAttachementTextureID( _Type ) ); AE_ErrorCheckOpenGLError();
	}

	void Framebuffer::UnbindTexture() const
	{
		glBindTexture( GL_TEXTURE_2D, 0 ); AE_ErrorCheckOpenGLError();
	}


	void Framebuffer::Bind()
	{
		glBindFramebuffer( GL_FRAMEBUFFER, m_FramebufferID ); AE_ErrorCheckOpenGLError();
		SaveModes();
		ApplyAllModes();

		// Stack up this framebuffer in the bound heap.
		m_BoundFramebuffers.push( m_FramebufferID );
	}

	void Framebuffer::Unbind()
	{
		// Remove this framebuffer from the bound heap.
		m_BoundFramebuffers.pop();

		// Retrieve the previous bound FBO, if the bound heap is empty, take the default buffer (window).
		Uint32 PreviousFBO = m_BoundFramebuffers.empty() ? 0 : m_BoundFramebuffers.top();

		RestoreSavedModes();
		glBindFramebuffer( GL_FRAMEBUFFER, PreviousFBO ); AE_ErrorCheckOpenGLError();
	}

	Uint32 Framebuffer::GetWidth() const
	{
		return m_Width;
	}

	Uint32 Framebuffer::GetHeight() const
	{
		return m_Height;
	}


	Uint32 Framebuffer::GetAttachementTextureID( FramebufferAttachement::Type _Type ) const
	{
		AttachementMap::const_iterator It = m_Attachements.find( Cast( Uint32, _Type ) );
		if( It == m_Attachements.cend() )
		{
			AE_LogWarning( "Trying to retrieve an framebuffer attachement that doesn't exists. The function will return 0." );
			return 0;
		}
		else
			return It->second.Texture->GetTextureID();
	}

	Texture* Framebuffer::GetAttachementTexture( FramebufferAttachement::Type _Type )
	{
		AttachementMap::const_iterator It = m_Attachements.find( Cast( Uint32, _Type ) );
		if( It == m_Attachements.cend() )
		{
			AE_LogWarning( "Trying to retrieve an framebuffer attachement that doesn't exists. The function will return nullptr." );
			return 0;
		}
		else
			return It->second.Texture.get();
	}

	const Texture* Framebuffer::GetAttachementTexture( FramebufferAttachement::Type _Type ) const
	{
		AttachementMap::const_iterator It = m_Attachements.find( Cast( Uint32, _Type ) );
		if( It == m_Attachements.cend() )
		{
			AE_LogWarning( "Trying to retrieve an framebuffer attachement that doesn't exists. The function will return nullptr." );
			return nullptr;
		}
		else
			return It->second.Texture.get();
	}

	void Framebuffer::GetAvailableAttachementTypes( AE_Out std::vector<FramebufferAttachement::Type>& _OutTypes ) const
	{
		_OutTypes.reserve( m_Attachements.size() );

		for( const std::pair<const Uint32, AttachementPair>& Attachement : m_Attachements )
			_OutTypes.push_back( Attachement.second.Attachement.GetType() );
	}

	Bool Framebuffer::HasAttachement( FramebufferAttachement::Type _Type ) const
	{
		return m_Attachements.find( Cast( Uint32, _Type ) ) != m_Attachements.cend();
	}

	FramebufferAttachement::Type Framebuffer::GetFirstAvailableAttachement() const
	{
		FramebufferAttachement::Type AttachementFound = FramebufferAttachement::Type::None;

		for( const std::pair<const Uint32, AttachementPair>& AttachementPair : m_Attachements )
		{
			const FramebufferAttachement::Type& AttachementType = AttachementPair.second.Attachement.GetType();

			if( FramebufferAttachement::IsColorAttachement( AttachementType ) )
			{
				if( FramebufferAttachement::IsDepthAttachement( AttachementFound ) )
					AttachementFound = AttachementType;

				else if( Cast( Uint32, AttachementType ) < Cast( Uint32, AttachementFound ) )
					AttachementFound = AttachementType;
			}

			// Take depth only we don't found color before.
			else if( !FramebufferAttachement::IsColorAttachement( AttachementFound ) )
				AttachementFound = AttachementType;
		}

		return AttachementFound;
	}

	void Framebuffer::SetSamplesCount( Uint32 _SamplesCount )
	{
		for( std::pair<const Uint32, AttachementPair>& AttachementPair : m_Attachements )
			AttachementPair.second.Attachement.SetSamplesCount( _SamplesCount );
		
		UpdateAttachement();
	}

	void Framebuffer::Blit( const Framebuffer& _Other, TextureFilterMode _Filter, Bool _BlitColor, Bool _BlitDepth, Bool _BlitStencil ) const
	{
		BindForBlit( GL_DRAW_FRAMEBUFFER );
		_Other.BindForBlit( GL_READ_FRAMEBUFFER );

		GLbitfield BlitMask = _BlitColor ? GL_COLOR_BUFFER_BIT : 0;
		if( _BlitDepth )
			BlitMask = BlitMask | GL_DEPTH_BUFFER_BIT;
		if( _BlitStencil )
			BlitMask = BlitMask | GL_STENCIL_BUFFER_BIT;


		glBlitFramebuffer( 0, 0, _Other.GetWidth(), _Other.GetHeight(),
						   0, 0, GetWidth(), GetHeight(),
						   BlitMask, Cast( GLenum, _Filter ) );


		_Other.UnbindForBlit( GL_READ_FRAMEBUFFER );
		UnbindForBlit( GL_DRAW_FRAMEBUFFER );
	}


	void Framebuffer::Create( const std::initializer_list<FramebufferAttachement>& _Attachements )
	{
		// Create the attachements and link them to the framebuffer.
		CreateAttachements( _Attachements );

		LinkAttachementToFramebuffer();
	}


	void Framebuffer::CreateAttachements( const std::initializer_list<FramebufferAttachement>& _Attachements )
	{
		Bool IsDepthAlreadyCreated = False;

		for( const FramebufferAttachement& Attachement : _Attachements )
		{
			// Skip invalid attachement.
			if( Attachement.GetType() == FramebufferAttachement::Type::None )
				continue;

			if( Attachement.IsDepthAttachement() )
			{
				if( IsDepthAlreadyCreated )
				{
					AE_LogWarning( "Impossible to create several depth or depth/stencil on a framebuffer. Only the first one will be created." );
					continue;
				}
				else
					IsDepthAlreadyCreated = True;
			}

			Texture* AttachementTexture = nullptr;

			switch( Attachement.GetDimension() )
			{
			case TextureDimension::Texture1D:
				AttachementTexture = new Texture1D( m_Width, Attachement );
				break;

			case TextureDimension::Texture2D:
				AttachementTexture = new Texture2D( m_Width, m_Height, Attachement );
				break;

			case TextureDimension::Texture2DMultiSample:
				AttachementTexture = new TextureMultisample( m_Width, m_Height, Attachement );
				break;

			case TextureDimension::Texture3D:
				AE_LogWarning( "Framebuffer with 3D attachements is not support yet." );
				break;

			case TextureDimension::CubeMap:
				AttachementTexture = new CubeMap( m_Width, m_Height, Attachement );
				break;

			default:
				throw std::exception( "Unknow texture attachement dimension." );
				break;
			}

			// Skip unsupported attachements.
			if( AttachementTexture == nullptr )
				continue;

			AttachementPair NewAttachement( Attachement, std::move( AttachementTexture ) );

			Uint32 AttachementType = Cast( Uint32, Attachement.GetType() );
			m_Attachements.emplace( std::make_pair( AttachementType, std::move( NewAttachement ) ) );
		}
	}

	void Framebuffer::UpdateAttachement()
	{
		for( const std::pair<const Uint32, AttachementPair>& Attachement : m_Attachements )
		{
			Texture* CurrentTexture = Attachement.second.Texture.get();

			switch( CurrentTexture->GetDimension() )
			{
			case TextureDimension::Texture1D:
				( (Texture1D*)CurrentTexture )->Set( m_Width, Attachement.second.Attachement );
				break;

			case TextureDimension::Texture2D:
				( (Texture2D*)CurrentTexture )->Set( m_Width, m_Height, Attachement.second.Attachement );
				break;
			case TextureDimension::Texture2DMultiSample:
				( (TextureMultisample*)CurrentTexture )->Set( m_Width, m_Height, Attachement.second.Attachement );
				break;

			case TextureDimension::Texture3D:
				AE_LogWarning( "Framebuffer with 3D attachements is not support yet." );
				//( (Texture3D*)CurrentTexture )->Set( m_Width, m_Height, , Attachement.second.Attachement );
				break;

			case TextureDimension::CubeMap:
				( (CubeMap*)CurrentTexture )->Set( m_Width, m_Height, Attachement.second.Attachement );
				break;

			default:
				throw std::exception( "Unknow texture attachement dimension." );
				break;
			}
		}


		LinkAttachementToFramebuffer();
	}

	void Framebuffer::LinkAttachementToFramebuffer()
	{
		Bind();

		std::vector<Uint32> ColorAttachements;
		ColorAttachements.reserve( m_Attachements.size() );

		for( std::pair<const Uint32, AttachementPair>& AttachementPair : m_Attachements )
		{
			const FramebufferAttachement& Attachement = AttachementPair.second.Attachement;
			const Texture* AttachementTexture = AttachementPair.second.Texture.get();

			AttachementTexture->Bind();

			// If it is a color attachement store it to set draw buffer later.
			if( Attachement.IsColorAttachement() )
				ColorAttachements.push_back( GL_COLOR_ATTACHMENT0 + Cast( Uint32, ColorAttachements.size() ) );

			AttachementTexture->AttachToFramebuffer( Attachement );

			AttachementTexture->Unbind();
		}

		// If there is more than one color attachement, tell OpenGl.
		if( ColorAttachements.size() > 1 )
		{
			glDrawBuffers( Cast( GLsizei, ColorAttachements.size() ), ColorAttachements.data() );
			AE_ErrorCheckOpenGLError();
		}
		// If there is only depth or depth/stencil, disable drawing on the framebuffer.
		else if( ColorAttachements.size() == 0 )
		{
			glDrawBuffer( GL_NONE ); AE_ErrorCheckOpenGLError();
			glReadBuffer( GL_NONE ); AE_ErrorCheckOpenGLError();
		}

		// Check if the framebuffer is well created.
		if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
			AE_LogError( "Framebuffer creation failed." );

		Unbind();
	}

	void Framebuffer::Create( AttachementPreset _Preset )
	{
		switch( _Preset )
		{
		case AttachementPreset::RGB_U8:
			Create( { FramebufferAttachement( FramebufferAttachement::Type::Color_0, TexturePixelFormat::RGB_U8 ) } );
			break;

		case AttachementPreset::RGBA_U8:
			Create( { FramebufferAttachement( FramebufferAttachement::Type::Color_0, TexturePixelFormat::RGBA_U8 ) } );
			break;

		case AttachementPreset::RGBA_F16:
			Create( { FramebufferAttachement( FramebufferAttachement::Type::Color_0, TexturePixelFormat::RGBA_F16 ) } );
			break;

		case AttachementPreset::Depth_Float:
			Create( { FramebufferAttachement( FramebufferAttachement::Type::Depth, TexturePixelFormat::Depth_F32, TextureFilterMode::Nearest ) } );
			break;

		case AttachementPreset::RGBA_U16_DepthStencil_U_24_8:
			Create( { FramebufferAttachement( FramebufferAttachement::Type::Color_0, TexturePixelFormat::RGBA_U16 ),
							  FramebufferAttachement( FramebufferAttachement::Type::DepthStencil, TexturePixelFormat::DepthStencil_U24_U8, TextureFilterMode::Nearest ) } );
			break;

		case AttachementPreset::RGBA_U8_DepthStencil_U_24_8_MS:
			Create( { FramebufferAttachement( FramebufferAttachement::Type::Color_0, 4, TexturePixelFormat::RGBA_U8 ),
							  FramebufferAttachement( FramebufferAttachement::Type::DepthStencil, 4, TexturePixelFormat::DepthStencil_U24_U8, TextureFilterMode::Nearest ) } );
			break;

		case AttachementPreset::RGBA_F16_DepthStencil_U_24_8_MS:
			Create( { FramebufferAttachement( FramebufferAttachement::Type::Color_0, 4, TexturePixelFormat::RGBA_F16 ),
							  FramebufferAttachement( FramebufferAttachement::Type::DepthStencil, 4, TexturePixelFormat::DepthStencil_U24_U8, TextureFilterMode::Nearest ) } );
			break;

		case AttachementPreset::RGBA_U8_DepthStencil_U_24_8:
		default:
			Create( { FramebufferAttachement( FramebufferAttachement::Type::Color_0, TexturePixelFormat::RGBA_U8 ),
							  FramebufferAttachement( FramebufferAttachement::Type::DepthStencil, TexturePixelFormat::DepthStencil_U24_U8, TextureFilterMode::Nearest ) } );
			break;
		}
	}



	void Framebuffer::CreateFramebuffer()
	{
		FreeFramebuffer();
		glGenFramebuffers( 1, &m_FramebufferID );  AE_ErrorCheckOpenGLError();
	}


	void Framebuffer::FreeResource()
	{
		FreeFramebuffer();

		m_Attachements.clear();
	}

	void Framebuffer::FreeFramebuffer()
	{
		if( m_FramebufferID != 0 )
		{
			glDeleteFramebuffers( 1, &m_FramebufferID ); AE_ErrorCheckOpenGLError();
			m_FramebufferID = 0;
		}
	}

	void Framebuffer::BindForBlit( GLenum _Mode ) const
	{
		glBindFramebuffer( _Mode, m_FramebufferID ); AE_ErrorCheckOpenGLError();

		// Stack up this framebuffer in the bound heap.
		m_BoundFramebuffers.push( m_FramebufferID );
	}

	void Framebuffer::UnbindForBlit( GLenum _Mode ) const
	{
		// Remove this framebuffer from the bound heap.
		m_BoundFramebuffers.pop();

		// Retrieve the previous bound FBO, if the bound heap is empty, take the default buffer (window).
		Uint32 PreviousFBO = m_BoundFramebuffers.empty() ? 0 : m_BoundFramebuffers.top();
		
		glBindFramebuffer( _Mode, PreviousFBO ); AE_ErrorCheckOpenGLError();
	}

} // ae

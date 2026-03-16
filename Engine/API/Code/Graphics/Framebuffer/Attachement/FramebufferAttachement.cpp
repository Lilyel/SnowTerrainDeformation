#include "FramebufferAttachement.h"

namespace ae
{

	FramebufferAttachement::FramebufferAttachement( Type _Type, TexturePixelFormat _Format, TextureFilterMode _Filter, TextureDimension _Dimension ) :
		m_Type( _Type ),
		m_Format( _Format ),
		m_Filter( _Filter ),
		m_Dimension( _Dimension ),
		m_SamplesCount( 0 )
	{
	}

	FramebufferAttachement::FramebufferAttachement( Type _Type, Uint32 _SamplesCount, TexturePixelFormat _Format, TextureFilterMode _Filter ) :
		m_Type( _Type ),
		m_Format( _Format ),
		m_Filter( _Filter ),
		m_Dimension( TextureDimension::Texture2DMultiSample ),
		m_SamplesCount( _SamplesCount )
	{
	}

	GLint FramebufferAttachement::GetGLInternalFormat() const
	{
		return ToGLInternalFormat( m_Format );
	}

	GLenum FramebufferAttachement::GetGLFormat() const
	{
		return ToGLFormat( m_Format );
	}

	GLenum FramebufferAttachement::GetGLType() const
	{
		return ToGLType( m_Format );
	}

	GLint FramebufferAttachement::GetGLFilter() const
	{
		return static_cast<GLint>( m_Filter );
	}

	GLenum FramebufferAttachement::GetGLAttachement() const
	{
		return static_cast<GLenum>( m_Type );
	}

	void FramebufferAttachement::SetFormat( TexturePixelFormat _Format )
	{
		m_Format = _Format;
	}

	TexturePixelFormat FramebufferAttachement::GetFormat() const
	{
		return m_Format;
	}

	void FramebufferAttachement::SetFilter( TextureFilterMode _FilterMode )
	{
		m_Filter = _FilterMode;
	}

	TextureFilterMode FramebufferAttachement::GetFilter() const
	{
		return m_Filter;
	}

	void FramebufferAttachement::SetDimension( TextureDimension _Dimension )
	{
		m_Dimension = _Dimension;
	}

	TextureDimension FramebufferAttachement::GetDimension() const
	{
		return m_Dimension;
	}
	
	void FramebufferAttachement::SetSamplesCount( Uint32 _SamplesCount )
	{
		m_SamplesCount = _SamplesCount;
	}

	Uint32 FramebufferAttachement::GetSamplesCount() const
	{
		return m_SamplesCount;
	}

	FramebufferAttachement::Type FramebufferAttachement::GetType() const
	{
		return m_Type;
	}

	Bool FramebufferAttachement::IsColorAttachement() const
	{
		return IsColorAttachement( m_Type);
	}

	Bool FramebufferAttachement::IsDepthAttachement() const
	{
		return IsDepthAttachement( m_Type );
	}

	Bool FramebufferAttachement::IsInvalidAttachement() const
	{
		return IsInvalidAttachement( m_Type );
	}

	Bool FramebufferAttachement::IsColorAttachement( Type _Type )
	{
		return !IsDepthAttachement( _Type ) && !IsInvalidAttachement( _Type );
	}

	Bool FramebufferAttachement::IsDepthAttachement( Type _Type )
	{
		return ( _Type == Type::Depth || _Type == Type::DepthStencil ) && !IsInvalidAttachement( _Type );
	}

	Bool FramebufferAttachement::IsInvalidAttachement( Type _Type )
	{
		return _Type == FramebufferAttachement::Type::None;
	}

	std::string FramebufferAttachement::TypeToString() const
	{
		return ToString( m_Type );
	}


	std::string ToString( FramebufferAttachement::Type _Type )
	{
		if( _Type == FramebufferAttachement::Type::Depth )
			return "Depth";

		else if( _Type == FramebufferAttachement::Type::DepthStencil )
			return "DepthStencil";

		else
			return std::string( "Color_" ) + std::to_string( static_cast<Uint32>( _Type ) - static_cast<Uint32>( FramebufferAttachement::Type::Color_0 ) );
	}

}

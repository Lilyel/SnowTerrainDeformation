#include "Color.h"
#include "../../Maths/Maths.h"

namespace ae
{
	const Color Color::White( 1.0f, 1.0f, 1.0f );

	const Color Color::Black( 0.0f, 0.0f, 0.0f );
	const Color Color::Transparent( 0.0f, 0.0f, 0.0f, 0.0f );
	const Color Color::Red( 1.0f, 0.0f, 0.0f );
	const Color Color::Green( 0.0f, 1.0f, 0.0f );
	const Color Color::Blue( 0.0f, 0.0f, 1.0f );
	const Color Color::Yellow( 1.0f, 1.0f, 0.0f );
	const Color Color::Cyan( 0.0f, 1.0f, 1.0f );
	const Color Color::Magenta( 1.0f, 0.0f, 1.0f );

	Color::Color() :
		m_R( 1.0f ),
		m_G( 1.0f ),
		m_B( 1.0f ),
		m_A( 1.0f )
	{
	}
	Color::Color( Uint8 _Red, Uint8 _Green, Uint8 _Blue, Uint8 _Alpha ) :
		m_R( Cast( float, _Red ) / 255.0f ),
		m_G( Cast( float, _Green ) / 255.0f ),
		m_B( Cast( float, _Blue ) / 255.0f ),
		m_A( Cast( float, _Alpha ) / 255.0f )
	{
	}

	Color::Color( Uint32 _Red, Uint32 _Green, Uint32 _Blue, Uint32 _Alpha ) :
		m_R( Cast( float, _Red ) / 255.0f ),
		m_G( Cast( float, _Green ) / 255.0f ),
		m_B( Cast( float, _Blue ) / 255.0f ),
		m_A( Cast( float, _Alpha ) / 255.0f )
	{
	}

	Color::Color( float _Red, float _Green, float _Blue, float _Alpha ) :
		m_R( Math::Max( 0.0f, _Red ) ),
		m_G( Math::Max( 0.0f,_Green ) ),
		m_B( Math::Max( 0.0f,_Blue ) ),
		m_A( Math::Max( 0.0f,_Alpha ) )
	{
	}

	Color::Color( const Color& _Color ) :
		m_R( _Color.m_R ),
		m_G( _Color.m_G ),
		m_B( _Color.m_B ),
		m_A( _Color.m_A )
	{
	}


	inline Color& Color::operator=( const Color& _Color )
	{
		m_R = _Color.m_R;
		m_G = _Color.m_G;
		m_B = _Color.m_B;
		m_A = _Color.m_A;

		return *this;
	}


	Color& Color::operator*=( const Color& _Color2 )
	{
		m_R *= _Color2.m_R;
		m_G *= _Color2.m_G;
		m_B *= _Color2.m_B;
		m_A *= _Color2.m_A;

		return *this;
	}
	Color& Color::operator*=( const float _Value )
	{
		R( m_R * _Value );
		G( m_G * _Value );
		B( m_B * _Value );
		A( m_A * _Value );

		return *this;
	}
	Color operator*( const Color& _Color1, const Color& _Color2 )
	{
		Color Result;

		Result.R( _Color1.R() * _Color2.R() );
		Result.G( _Color1.G() * _Color2.G() );
		Result.B( _Color1.B() * _Color2.B() );
		Result.A( _Color1.A() * _Color2.A() );

		return Result;
	}

	Color operator*( const Color& _Color, const float _Value )
	{
		Color Result;

		Result.R( _Color.R() * _Value );
		Result.G( _Color.G() * _Value );
		Result.B( _Color.B() * _Value );
		Result.A( _Color.A() * _Value );

		return Result;
	}

	Color& Color::operator/=( const Color& _Color2 )
	{
		R( m_R / _Color2.m_R );
		G( m_G / _Color2.m_G );
		B( m_B / _Color2.m_B );
		A( m_A / _Color2.m_A );

		return *this;
	}
	Color& Color::operator/=( const float _Value )
	{
		R( m_R / _Value );
		G( m_G / _Value );
		B( m_B / _Value );
		A( m_A / _Value );

		return *this;
	}
	Color operator/( const Color& _Color1, const Color& _Color2 )
	{
		Color Result;

		Result.R( _Color1.R() / _Color2.R() );
		Result.G( _Color1.G() / _Color2.G() );
		Result.B( _Color1.B() / _Color2.B() );
		Result.A( _Color1.A() / _Color2.A() );

		return Result;
	}
	Color operator/( const Color& _Color, const float _Value )
	{
		Color Result;

		Result.R( _Color.R() / _Value );
		Result.G( _Color.G() / _Value );
		Result.B( _Color.B() / _Value );
		Result.A( _Color.A() / _Value );

		return Result;
	}

	Color& Color::operator-=( const Color& _Color2 )
	{
		R( m_R - _Color2.m_R );
		G( m_G - _Color2.m_G );
		B( m_B - _Color2.m_B );
		A( m_A - _Color2.m_A );

		return *this;
	}
	Color& Color::operator-=( const float _Value )
	{
		R( m_R - _Value );
		G( m_G - _Value );
		B( m_B - _Value );
		A( m_A - _Value );

		return *this;
	}
	Color operator-( const Color& _Color1, const Color& _Color2 )
	{
		Color Result;

		Result.R( _Color1.R() - _Color2.R() );
		Result.G( _Color1.G() - _Color2.G() );
		Result.B( _Color1.B() - _Color2.B() );
		Result.A( _Color1.A() - _Color2.A() );

		return Result;
	}
	Color operator-( const Color& _Color, const float _Value )
	{
		Color Result;

		Result.R( _Color.R() - _Value );
		Result.G( _Color.G() - _Value );
		Result.B( _Color.B() - _Value );
		Result.A( _Color.A() - _Value );

		return Result;
	}

	Color& Color::operator+=( const Color& _Color2 )
	{
		R( m_R + _Color2.m_R );
		G( m_G + _Color2.m_G );
		B( m_B + _Color2.m_B );
		A( m_A + _Color2.m_A );

		return *this;
	}
	Color& Color::operator+=( const float _Value )
	{
		R( m_R + _Value );
		G( m_G + _Value );
		B( m_B + _Value );
		A( m_A + _Value );

		return *this;
	}

	inline float Color::R() const
	{
		return m_R;
	}

	inline float Color::G() const
	{
		return m_G;
	}

	inline float Color::B() const
	{
		return m_B;
	}

	inline float Color::A() const
	{
		return m_A;
	}

	inline void Color::R( float _R )
	{
		m_R = Math::Max( 0.0f, _R );
	}

	inline void Color::G( float _G )
	{
		m_G = Math::Max( 0.0f, _G );
	}

	inline void Color::B( float _B )
	{
		m_B = Math::Max( 0.0f, _B );
	}

	inline void Color::A( float _A )
	{
		m_A = Math::Max( 0.0f, _A );
	}

	inline void Color::Set( float _R, float _G, float _B, float _A )
	{
		R( _R ); G( _G ); B( _B ); A( _A );
	}

	inline void Color::Set( float _R, float _G, float _B )
	{
		R( _R ); G( _G ); B( _B );
	}
	
	Color operator+( const Color& _Color1, const Color& _Color2 )
	{
		Color Result;

		Result.R( _Color1.R() + _Color2.R() );
		Result.G( _Color1.G() + _Color2.G() );
		Result.B( _Color1.B() + _Color2.B() );
		Result.A( _Color1.A() + _Color2.A() );

		return Result;
	}
	Color operator+( const Color& _Color, const float _Value )
	{
		Color Result;

		Result.R( _Color.R() + _Value );
		Result.G( _Color.G() + _Value );
		Result.B( _Color.B() + _Value );
		Result.A( _Color.A() + _Value );

		return Result;
	}


	Bool operator==( const Color& _Color1, const Color& _Color2 )
	{
		return ( _Color1.R() == _Color2.R() && _Color1.G() == _Color2.G() && _Color1.B() == _Color2.B() && _Color1.A() == _Color2.A() );
	}
	Bool operator!=( const Color& _Color1, const Color& _Color2 )
	{
		return ( _Color1.R() != _Color2.R() || _Color1.G() != _Color2.G() || _Color1.B() != _Color2.B() || _Color1.A() != _Color2.A() );
	}



    std::string ToString( const ae::Color& _Color )
    {
        return std::string( "R = " ) + std::to_string( _Color.R() )
            + std::string( " G = " ) + std::to_string( _Color.G() )
            + std::string( " B = " ) + std::to_string( _Color.B() )
            + std::string( " A = " ) + std::to_string( _Color.A() );
    }

} // ae


std::ostream& operator<<( std::ostream& os, const ae::Color& _Color )
{
    os << ae::ToString( _Color );

    return os;
}

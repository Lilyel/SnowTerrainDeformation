#include "Vector2.h"

#include "Vector3.h"
#include "../Maths.h"

#include "../../Debugging/Log/Log.h"

namespace ae
{
    const Vector2 Vector2::Zero( 0.0f, 0.0f );
    const Vector2 Vector2::One( 1.0f, 1.0f );
    const Vector2 Vector2::AxeX( 1.0f, 0.0f );
    const Vector2 Vector2::AxeY( 0.0f, 1.0f );

    Vector2::Vector2() :
        X( 0.0f ),
        Y( 0.0f )
    {
    }
    Vector2::Vector2( float _X, float _Y ) :
        X( _X ),
        Y( _Y )
    {
    }
    Vector2::Vector2( const Vector2& _v2 ) :
        X( _v2.X ),
        Y( _v2.Y )
    {
    }
    Vector2::Vector2( const Vector2& _A, const Vector2& _B ) :
        Vector2( _B - _A )
    {
    }

    Vector2::Vector2( const Vector3& _Vec3D ) :
        Vector2( _Vec3D.X, _Vec3D.Y )
    {
    }


    Vector2& Vector2::operator=( const Vector3& _Vec3D )
    {
        X = _Vec3D.X;
        Y = _Vec3D.Y;

        return *this;
    }


    float& Vector2::operator[]( Uint32 _Index )
    {
        if( _Index > 1 )
            throw std::out_of_range( "Vector access index must be 0, 1." );

        return ( &X )[_Index];
    }

    const float& Vector2::operator[]( Uint32 _Index ) const
    {
        if( _Index > 1 )
            throw std::out_of_range( "Vector access index must be 0, 1." );

        return ( &X )[_Index];
    }


    Vector2 operator*( const Vector2& _v1, const Vector2& _v2 )
    {
        return Vector2( _v1.X * _v2.X, _v1.Y * _v2.Y );
    }

    Vector2& Vector2::operator*=( const Vector2& _v2 )
    {
        X *= _v2.X;
        Y *= _v2.Y;

        return *this;
    }
    Vector2 operator*( const Vector2& _Vector, const float _Value )
    {
        return Vector2( _Vector.X * _Value, _Vector.Y * _Value );
    }
    Vector2&  Vector2::operator*=( const float _Value )
    {
        X *= _Value;
        Y *= _Value;

        return *this;
    }

    Vector2 operator/( const Vector2& _v1, const Vector2& _v2 )
    {
        return Vector2( _v1.X / _v2.X, _v1.Y / _v2.Y );
    }
    Vector2&  Vector2::operator/=( const Vector2& _v2 )
    {
        X /= _v2.X;
        Y /= _v2.Y;

        return *this;
    }
    Vector2 operator/( const Vector2& _Vector, const float _Value )
    {
        return Vector2( _Vector.X / _Value, _Vector.Y / _Value );
    }
    Vector2&  Vector2::operator/=( const float _Value )
    {
        X /= _Value;
        Y /= _Value;

        return *this;
    }

    Vector2 operator-( const Vector2& _v1, const Vector2& _v2 )
    {
        return Vector2( _v1.X - _v2.X, _v1.Y - _v2.Y );
    }
    Vector2&  Vector2::operator-=( const Vector2& _v2 )
    {
        X -= _v2.X;
        Y -= _v2.Y;

        return *this;
    }
    Vector2 operator-( const Vector2& _Vector, const float _Value )
    {
        return Vector2( _Vector.X - _Value, _Vector.Y - _Value );
    }
    Vector2&  Vector2::operator-=( const float _Value )
    {
        X -= _Value;
        Y -= _Value;

        return *this;
    }

    Vector2 operator+( const Vector2& _v1, const Vector2& _v2 )
    {
        return Vector2( _v1.X + _v2.X, _v1.Y + _v2.Y );
    }
    Vector2&  Vector2::operator+=( const Vector2& _v2 )
    {
        X += _v2.X;
        Y += _v2.Y;

        return *this;
    }
    Vector2 operator+( const Vector2& _Vector, const float _Value )
    {
        return Vector2( _Vector.X + _Value, _Vector.Y + _Value );
    }
    Vector2&  Vector2::operator+=( const float _Value )
    {
        X += _Value;
        Y += _Value;

        return *this;
    }

    Bool operator==( const Vector2& _v1, const Vector2& _v2 )
    {
        return ( _v1.X == _v2.X && _v1.Y == _v2.Y );
    }
    Bool operator!=( const Vector2& _v1, const Vector2& _v2 )
    {
        return ( _v1.X != _v2.X || _v1.Y != _v2.Y );
    }

    Vector2 Vector2::operator-() const
    {
        return Vector2( -X, -Y );
    }


    float Vector2::Length() const
    {
        return Math::Sqrt( Math::Pow2( X ) + Math::Pow2( Y ) );
    }

    float Vector2::Length( VectorLength _Algorithm, float _P ) const
    {
        switch( _Algorithm )
        {
        case ae::VectorLength::Norm_1:
        return ( Math::Abs( X ) + Math::Abs( Y ) );

        case ae::VectorLength::Norm_2:
        return Length();

        case ae::VectorLength::Norm_p:
        return Math::Pow( Math::Pow2( X ) + Math::Pow2( Y ), 1.0f / _P );

        case ae::VectorLength::Norm_infinite:
        return Math::Max( Math::Abs( X ), Math::Abs( Y ) );

        default:
        AE_LogError( "Unknown vector length algorithm" );
        return 0.0f;
        }
    }

    float Vector2::LengthSqr() const
    {
        return ( Math::Pow2( X ) + Math::Pow2( Y ) );
    }

    Vector2&  Vector2::Rotate( const float _Angle )
    {
        const float Cos = Math::Cos( _Angle );
        const float Sin = Math::Sin( _Angle );

        const float RotatedX = ( Cos * X ) - ( Sin * Y );
        const float RotatedY = ( Sin * X ) + ( Cos * Y );

        X = RotatedX;
        Y = RotatedY;

        return *this;
    }

    Vector2& Vector2::Translate( const Vector2& _Offset )
    {
        *this += _Offset;

        return *this;
    }

    Vector2& Vector2::Scale( const Vector2& _Scale )
    {
        *this *= _Scale;

        return *this;
    }

    float Vector2::Dot( const Vector2& _v2 ) const
    {
        return ( X * _v2.X + Y * _v2.Y );
    }

    float Vector2::Cross( const Vector2& _v2 ) const
    {
        return ( X * _v2.Y - Y * _v2.X );
    }

    float Vector2::Angle( const VectorAngleRange _AngleRange ) const
    {
        float Angle = Math::ATan2( *this, True);

        priv::VectorToolbox::ProcessAngleRange( Angle, _AngleRange );

        return Angle;
    }

    /*float Vector2::Angle( const Vector2& _v2 ) const
    {
        const float LengthV1 = Length();
        const float LengthV2 = _v2.Length();

        // Prevent division by 0.
        if( LengthV1 == 0.0f )
        {
            AE_LogError( L"Calling Vector length is null, impossible to do the rotation.\n" );
            return 0.0f;
        }
        if( LengthV2 == 0.0f )
        {
            AE_LogError( L"_v2 length is null, impossible to do the rotation.\n" );
            return 0.0f;
        }

        const float Dot = ( X * _v2.X ) + ( Y * _v2.Y );

        const float Div = Dot / ( LengthV1 * LengthV2 );

        return Math::ACos( Div );
    }*/

    float Vector2::Angle( const Vector2& _v2, const VectorAngleRange _AngleRange ) const
    {
        // https://stackoverflow.com/a/21486462

        float Angle = Math::ATan2( Cross( _v2 ), Dot( _v2 ) );

        priv::VectorToolbox::ProcessAngleRange( Angle, _AngleRange );

        return Angle;
    }

    Vector2 Vector2::GetNormalized() const
    {
        Vector2 Unit( 0.0f, 0.0f );

        const float VectorLength = Length();

        // Prevent division by 0.
        if( !VectorLength )
        {
            AE_LogError( "Vector length is null, impossible to normalize.\n" );
            return *this;
        }

        // If already unit, exit now.
        if( VectorLength == 1.0f )
            return *this;

        const float InvLength = 1.0f / VectorLength;

        Unit.X = X * InvLength;
        Unit.Y = Y * InvLength;

        return Unit;
    }

    Vector2&  Vector2::Normalize()
    {
        const float VectorLength = Length();

        // Prevent division by 0.
        if( !VectorLength )
        {
            AE_LogError( "Vector length is null, impossible to normalize.\n" );
            return *this;
        }

        // If already unit, exit now.
        if( VectorLength == 1.0f )
            return *this;;

        const float InvLength = 1.0f / VectorLength;

        X = X * InvLength;
        Y = Y * InvLength;

        return *this;
    }

    Bool Vector2::IsUnit() const
    {
        const float VectorLength = LengthSqr();

        return ( VectorLength == 1.0f );
    }

    Bool Vector2::IsUnitByEpsilon() const
    {
        const float VectorLength = LengthSqr();

        return ( Math::IsEqualByEpsilon( VectorLength, 1.0f ) );
    }

    Bool Vector2::IsNull() const
    {
        return ( X == 0.0f && Y == 0.0f );
    }

    Bool Vector2::IsNullByEpsilon() const
    {
        return ( Math::IsNullByEpsilon( X ) && Math::IsNullByEpsilon( Y ) );
    }

	Vector2& Vector2::Set( float _X, float _Y )
	{
		X = _X;
		Y = _Y;

		return *this;
	}



    std::string ToString( const ae::Vector2& _Vector )
    {
        return std::string( "X = " ) + std::to_string( _Vector.X )
            + std::string( " Y = " ) + std::to_string( _Vector.Y );
    }
} // ae


std::ostream& operator<<( std::ostream& os, const ae::Vector2& _Vector )
{
    os << ae::ToString( _Vector );

    return os;
}


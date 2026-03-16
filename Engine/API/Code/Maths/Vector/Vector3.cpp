#include "Vector3.h"

#include "../Maths.h"
#include "../Matrix/Matrix4x4.h"

#include "../../Debugging/Log/Log.h"

#include <sstream>
#include <iomanip>

namespace ae
{
    const Vector3 Vector3::Zero( 0.0f, 0.0f, 0.0f );
    const Vector3 Vector3::One( 1.0f, 1.0f, 1.0f );
    const Vector3 Vector3::AxeX( 1.0f, 0.0f, 0.0f );
    const Vector3 Vector3::AxeY( 0.0f, 1.0f, 0.0f );
    const Vector3 Vector3::AxeZ( 0.0f, 0.0f, 1.0f );

    Vector3::Vector3() :
        X( 0.0f ),
        Y( 0.0f ),
        Z( 0.0f )
    {
    }
    Vector3::Vector3( float _X, float _Y, float _Z ) :
        X( _X ),
        Y( _Y ),
        Z( _Z )
    {
    }
    Vector3::Vector3( const Vector3& _v2 ) :
        X( _v2.X ),
        Y( _v2.Y ),
        Z( _v2.Z )
    {
    }
    Vector3::Vector3( const Vector3& _A, const Vector3& _B ) :
        Vector3( _B - _A )
    {
    }

    Vector3::Vector3( const Vector2& _Vec2D ) :
        Vector3( _Vec2D.X, _Vec2D.Y, 0.0f )
    {
    }

    Vector3& Vector3::operator=( const Vector2& _Vec2D )
    {
        X = _Vec2D.X;
        Y = _Vec2D.Y;

        return *this;
    }


    float& Vector3::operator[]( Uint32 _Index )
    {
        if( _Index > 2 )
            throw std::out_of_range( "Vector access index must be 0, 1 or 2." );

        return ( &X )[_Index];
    }

    const float& Vector3::operator[]( Uint32 _Index ) const
    {
        if( _Index > 2 )
            throw std::out_of_range( "Vector access index must be 0, 1 or 2." );

        return ( &X )[_Index];
    }


    Vector3 operator*( const Vector3& _v1, const Vector3& _v2 )
    {
        return Vector3( _v1.X * _v2.X, _v1.Y  * _v2.Y, _v1.Z * _v2.Z );
    }
    Vector3& Vector3::operator*=( const Vector3& _v2 )
    {
        X *= _v2.X;
        Y *= _v2.Y;
        Z *= _v2.Z;

        return *this;
    }
    Vector3 operator*( const Vector3& _Vector, const float _Value )
    {
        return Vector3( _Vector.X * _Value, _Vector.Y  * _Value, _Vector.Z * _Value );
    }
	Vector3 operator*( const float _Value, const Vector3& _Vector )
	{
		return Vector3( _Vector.X * _Value, _Vector.Y * _Value, _Vector.Z * _Value );
	}
    Vector3& Vector3::operator*=( const float _Value )
    {
        X *= _Value;
        Y *= _Value;
        Z *= _Value;

        return *this;
    }

    Vector3 operator/( const Vector3& _v1, const Vector3& _v2 )
    {
        return Vector3( _v1.X / _v2.X, _v1.Y / _v2.Y, _v1.Z / _v2.Z );
    }
    Vector3& Vector3::operator/=( const Vector3& _v2 )
    {
        X /= _v2.X;
        Y /= _v2.Y;
        Z /= _v2.Z;

        return *this;
    }
    Vector3 operator/( const Vector3& _Vector, const float _Value )
    {
        return Vector3( _Vector.X / _Value, _Vector.Y / _Value, _Vector.Z / _Value );
    }
	Vector3 operator/( const float _Value, const Vector3& _Vector )
	{
		return Vector3( _Value / _Vector.X , _Value / _Vector.Y, _Value / _Vector.Z );
	}
    Vector3& Vector3::operator/=( const float _Value )
    {
        if( _Value == 0.0f )
            return *this;

        X /= _Value;
        Y /= _Value;
        Z /= _Value;

        return *this;
    }

    Vector3 operator-( const Vector3& _v1, const Vector3& _v2 )
    {
        return Vector3( _v1.X - _v2.X, _v1.Y - _v2.Y, _v1.Z - _v2.Z );
    }
    Vector3& Vector3::operator-=( const Vector3& _v2 )
    {
        X -= _v2.X;
        Y -= _v2.Y;
        Z -= _v2.Z;

        return *this;
    }
    Vector3 operator-( const Vector3& _Vector, const float _Value )
    {
        return Vector3( _Vector.X - _Value, _Vector.Y - _Value, _Vector.Z - _Value );
    }
	Vector3 operator-( const float _Value, const Vector3& _Vector )
	{
		return Vector3( _Vector.X - _Value, _Vector.Y - _Value, _Vector.Z - _Value );
	}
    Vector3& Vector3::operator-=( const float _Value )
    {
        X -= _Value;
        Y -= _Value;
        Z -= _Value;

        return *this;
    }

    Vector3 operator+( const Vector3& _v1, const Vector3& _v2 )
    {
        return Vector3( _v1.X + _v2.X, _v1.Y + _v2.Y, _v1.Z + _v2.Z );
    }
    Vector3& Vector3::operator+=( const Vector3& _v2 )
    {
        X += _v2.X;
        Y += _v2.Y;
        Z += _v2.Z;

        return *this;
    }
    Vector3 operator+( const Vector3& _Vector, const float _Value )
    {
        return Vector3( _Vector.X + _Value, _Vector.Y + _Value, _Vector.Z + _Value );
    }
	Vector3 operator+( const float _Value, const Vector3& _Vector )
	{
		return Vector3( _Vector.X + _Value, _Vector.Y + _Value, _Vector.Z + _Value );
	}
    Vector3& Vector3::operator+=( const float _Value )
    {
        X += _Value;
        Y += _Value;
        Z += _Value;

        return *this;
    }

    Bool operator==( const Vector3& _v1, const Vector3& _v2 )
    {
        return ( _v1.X == _v2.X && _v1.Y == _v2.Y  && _v1.Z == _v2.Z );
    }
    Bool operator!=( const Vector3& _v1, const Vector3& _v2 )
    {
        return ( _v1.X != _v2.X || _v1.Y != _v2.Y || _v1.Z != _v2.Z );
    }

    Vector3 Vector3::operator-() const
    {
        return Vector3( -X, -Y, -Z );
    }


    float Vector3::Length() const
    {
        return Math::Sqrt( Math::Pow2( X ) + Math::Pow2( Y ) + Math::Pow2( Z ) );
    }

    float Vector3::Length( VectorLength _Algorithm, float _P ) const
    {
        switch( _Algorithm )
        {
        case ae::VectorLength::Norm_1:
        return ( Math::Abs( X ) + Math::Abs( Y ) + Math::Abs( Z ) );

        case ae::VectorLength::Norm_2:
        return Length();

        case ae::VectorLength::Norm_p:
        return Math::Pow( Math::Pow2( X ) + Math::Pow2( Y ) + Math::Pow2( Z ), 1.0f / _P );

        case ae::VectorLength::Norm_infinite:
        return Math::Max( Math::Abs( X ), Math::Max( Math::Abs( Y ), Math::Abs( Z ) ) );

        default:
        AE_LogError( "Unknown vector length algorithm" );
        return 0.0f;
        }
    }

    float Vector3::LengthSqr() const
    {
        return ( Math::Pow2( X ) + Math::Pow2( Y ) + Math::Pow2( Z ) );
    }

    Vector3& Vector3::Rotate( const float _Angle, const Vector3& _Axis )
    {
        Matrix4x4 RotationMatrix = Matrix4x4::GetRotationMatrix( _Angle, _Axis );

        RotationMatrix.TransformPoint( *this );

        return *this;
    }

    Vector3& Vector3::Translate( const Vector3& _Offset )
    {
        *this += _Offset;

        return *this;
    }

    Vector3 & Vector3::Scale( const Vector3 & _Scale )
    {
        *this *= _Scale;

        return *this;
    }

    float Vector3::Dot( const Vector3& _v2 ) const
    {
        return ( ( X * _v2.X ) + ( Y  * _v2.Y ) + ( Z * _v2.Z ) );
    }

    Vector3 Vector3::Cross( const Vector3& _v2 ) const
    {
        Vector3 Ret;

        Ret.X = Y * _v2.Z - Z * _v2.Y;
        Ret.Y = -( X * _v2.Z - Z * _v2.X );
        Ret.Z = X * _v2.Y - Y * _v2.X;

        return Ret;
    }

    Vector3 Vector3::Angle( const VectorAngleRange _AngleRange ) const
    {
        Vector3 EulerAngle;

        // Check null coordinate ( to prevent divide bY  0 ).
        if( !X && !Y && !Z )
            return EulerAngle;

        // Find Yaw.
        EulerAngle.X = Math::ATan2( Y, X );

        // Find pitch.
        EulerAngle.Y = Math::ATan2( Z, sqrtf( Math::Pow2( X ) + Math::Pow2( Y ) ) );

        // Find roll.
        EulerAngle.Z = 0.0f;

		priv::VectorToolbox::ProcessAngleRange( EulerAngle.X, _AngleRange );
		priv::VectorToolbox::ProcessAngleRange( EulerAngle.Y, _AngleRange );
		priv::VectorToolbox::ProcessAngleRange( EulerAngle.Z, _AngleRange );

        return EulerAngle;
    }

    float Vector3::Angle( const Vector3& _v2, const VectorAngleRange _AngleRange ) const
    {
		// https://stackoverflow.com/a/33920320

		const Vector3& NormalAB = _v2.Cross( *this );
		const Vector3& NormalABUnit = Cross( _v2 ).Normalize();
		const float DotAB = Dot( _v2 );

		float Angle = Math::ATan2( NormalAB.Dot( NormalABUnit ), DotAB );

		priv::VectorToolbox::ProcessAngleRange( Angle, _AngleRange );

		return Angle;
    }

    Vector3& Vector3::Normalize()
    {
        const float VectorLength = Length();

        if( !VectorLength )
            return *this;

        X = X / VectorLength;
        Y = Y / VectorLength;
        Z = Z / VectorLength;

        return *this;
    }

    Vector3 Vector3::GetNormalized() const
    {
        Vector3 Unit( 0.0f, 0.0f, 0.0f );

        const float VectorLength = Length();

        if( !VectorLength )
            return Unit;

        Unit.X = X / VectorLength;
        Unit.Y = Y / VectorLength;
        Unit.Z = Z / VectorLength;

        return Unit;
    }

    Bool Vector3::IsUnit() const
    {
        const float VectorLength = LengthSqr();

        return VectorLength == 1.0f;
    }

    Bool Vector3::IsUnitByEpsilon() const
    {
        const float VectorLength = LengthSqr();

        return ( Math::IsEqualByEpsilon( VectorLength, 1.0f ) );
    }

    Bool Vector3::IsNull() const
    {
        return ( X == 0.0f ) && ( Y == 0.0f ) && ( Z == 0.0f );
    }
    Bool Vector3::IsNullByEpsilon() const
    {
        return ( Math::IsNullByEpsilon( X ) && Math::IsNullByEpsilon( Y ) && Math::IsNullByEpsilon( Z ) );
    }

    Vector3& Vector3::Set( float _X, float _Y, float _Z )
    {
        X = _X;
        Y = _Y;
        Z = _Z;

        return *this;
    }

	float Vector3::ScalarTriple( const Vector3& _ToCross, const Vector3& _ToDot ) const
	{
		return Cross( _ToCross ).Dot( _ToDot );
	}


    std::string ToString( const ae::Vector3& _Vector )
    {
        return std::string( "X = " ) + std::to_string( _Vector.X )
            + std::string( " Y = " ) + std::to_string( _Vector.Y )
            + std::string( " Z = " ) + std::to_string( _Vector.Z );
    }


} // ae



std::ostream& operator<<( std::ostream& os, const ae::Vector3& _Vector )
{
    os << ae::ToString( _Vector );

    return os;
}


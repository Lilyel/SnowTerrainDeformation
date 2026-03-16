#include "Quaternion.h"

#include "../Maths.h"
#include "../Vector/Vector3.h"


namespace ae
{
	const Quaternion Quaternion::Zero( 0.0f, 0.0f, 0.0f, 0.0f );
	const Quaternion Quaternion::Identity( 0.0f, 0.0f, 0.0f, 1.0f );

	Quaternion::Quaternion() :
		X( 0.0f ),
		Y( 0.0f ),
		Z( 0.0f ),
		W( 0.0f )
	{
	}
	Quaternion::Quaternion( float _X, float _Y, float _Z, float _W ) :
		X( _X ),
		Y( _Y ),
		Z( _Z ),
		W( _W )
	{
		Normalise();
	}
	Quaternion::Quaternion( const Vector3& _Axis, float _Angle )
	{
		const Vector3 AxisUnit = _Axis.GetNormalized();

		const float HalfAngle = _Angle / 2.0f;
		const float Sin = Math::Sin( HalfAngle );

		W = Math::Cos( HalfAngle );
		X = AxisUnit.X * Sin;
		Y = AxisUnit.Y * Sin;
		Z = AxisUnit.Z * Sin;

		Normalise();
	}
	Quaternion::Quaternion( const Quaternion& _Quat ) :
		X( _Quat.X ),
		Y( _Quat.Y ),
		Z( _Quat.Z ),
		W( _Quat.W )
	{
		Normalise();
	}

	void Quaternion::operator *= ( const Quaternion& _Quat )
	{
		// Based on works of 
		// http://www.cprogramming.com/tutorial/3d/quaternions.html
		// http://mathworld.wolfram.com/Quaternion.html

		Quaternion Result;

		Result.W = ( W * _Quat.W ) - ( X * _Quat.W ) - ( Y * _Quat.Y ) - ( Z * _Quat.Z );
		Result.X = ( W * _Quat.X ) + ( X * _Quat.W ) + ( Y * _Quat.Z ) - ( Z * _Quat.Y );
		Result.Y = ( W * _Quat.Y ) - ( X * _Quat.Z ) + ( Y * _Quat.W ) + ( Z * _Quat.X );
		Result.Z = ( W * _Quat.Z ) + ( X * _Quat.Y ) - ( Y * _Quat.X ) + ( Z * _Quat.W );

		W = Result.W;
		X = Result.X;
		Y = Result.Y;
		Z = Result.Z;
	}
	Quaternion operator*( const Quaternion& _Quat1, const Quaternion& _Quat2 )
	{
		// Based on works of 
		// http://www.cprogramming.com/tutorial/3d/quaternions.html
		// http://mathworld.wolfram.com/Quaternion.html

		Quaternion Result;

		Result.W = ( _Quat1.W * _Quat2.W ) - ( _Quat1.X * _Quat2.W ) - ( _Quat1.Y * _Quat2.Y ) - ( _Quat1.Z * _Quat2.Z );
		Result.X = ( _Quat1.W * _Quat2.X ) + ( _Quat1.X * _Quat2.W ) + ( _Quat1.Y * _Quat2.Z ) - ( _Quat1.Z * _Quat2.Y );
		Result.Y = ( _Quat1.W * _Quat2.Y ) - ( _Quat1.X * _Quat2.Z ) + ( _Quat1.Y * _Quat2.W ) + ( _Quat1.Z * _Quat2.X );
		Result.Z = ( _Quat1.W * _Quat2.Z ) + ( _Quat1.X * _Quat2.Y ) - ( _Quat1.Y * _Quat2.X ) + ( _Quat1.Z * _Quat2.W );

		return Result;
	}

	void Quaternion::operator+=( const Quaternion& _Quat )
	{
		X = X + _Quat.X;
		Y = Y + _Quat.Y;
		Z = Z + _Quat.Z;
		W = W + _Quat.W;
	}
	Quaternion operator+( const Quaternion& _Quat1, const Quaternion& _Quat2 )
	{
		Quaternion Result;

		Result.X = _Quat1.X + _Quat2.X;
		Result.Y = _Quat1.Y + _Quat2.Y;
		Result.Z = _Quat1.Z + _Quat2.Z;
		Result.W = _Quat1.W + _Quat2.W;

		return Result;
	}

	Quaternion Quaternion::GetConjugate() const
	{
		// Based on works of
		// http://mathworld.wolfram.com/Quaternion.html

		Quaternion Result;

		Result.X = -X;
		Result.Y = -Y;
		Result.Z = -Z;
		Result.W = W;

		return Result;
	}

	float Quaternion::Length() const
	{
		return sqrtf( Math::Pow2( X ) + Math::Pow2( Y ) + Math::Pow2( Z ) + Math::Pow2( W ) );
	}
	float Quaternion::LengthSquared() const
	{
		return ( Math::Pow2( X ) + Math::Pow2( Y ) + Math::Pow2( Z ) + Math::Pow2( W ) );
	}

	void Quaternion::Normalise()
	{
		float QuatLength = Length();

		// Prevent division bY 0.
		if( !QuatLength )
			return;

		X = X / QuatLength;
		Y = Y / QuatLength;
		Z = Z / QuatLength;
		W = W / QuatLength;
	}
	Quaternion Quaternion::GetNormalised() const
	{
		float QuatLength = Length();

		Quaternion Result;

		// Prevent division bY 0.
		if( !QuatLength )
			return Result;


		Result.X = X / QuatLength;
		Result.Y = Y / QuatLength;
		Result.Z = Z / QuatLength;
		Result.W = W / QuatLength;

		return Result;
	}

	Matrix4x4 Quaternion::GetMatrix() const
	{
		// Based on works of 
		// http://www.cprogramming.com/tutorial/3d/quaternions.html

		const float XX = Math::Pow2( X );
		const float YY = Math::Pow2( Y );
		const float ZZ = Math::Pow2( Z );
		const float WW = Math::Pow2( W );

		const float XY = X * Y;
		const float XZ = X * Z;
		const float XW = X * W;
		const float YZ = Y * Z;
		const float YW = Y * W;
		const float ZW = Z * W;

		Matrix4x4 Result;

		Result[0] = WW + XX - YY - ZZ;				Result[1] = ( 2.0f * XY ) - ( 2.0f * ZW );	Result[2] = ( 2.0f * XZ ) + ( 2.0f * YW );	Result[3] = 0.0f;
		Result[4] = ( 2.0f * XY ) + ( 2.0f * ZW );	Result[5] = WW - XX + YY - ZZ;				Result[6] = ( 2.0f * YZ ) - ( 2.0f * XW );	Result[7] = 0.0f;
		Result[8] = ( 2.0f * XZ ) - ( 2.0f * YW );	Result[9] = ( 2.0f * XW ) + ( 2.0f * YZ );	Result[10] = WW - XX - YY + ZZ;				Result[11] = 0.0f;
		Result[12] = 0.0f;							Result[13] = 0.0f;							Result[14] = 0.0f;							Result[15] = 1.0f;

		return Result;
	}

	Matrix4x4 Quaternion::GetTransposedMatrix() const
	{
		const float XX = Math::Pow2( X );
		const float YY = Math::Pow2( Y );
		const float ZZ = Math::Pow2( Z );
		const float WW = Math::Pow2( W );

		const float XY = X * Y;
		const float XZ = X * Z;
		const float XW = X * W;
		const float YZ = Y * Z;
		const float YW = Y * W;
		const float ZW = Z * W;

		Matrix4x4 Result;

		Result[0] = WW + XX - YY - ZZ;				Result[4] = ( 2.0f * XY ) - ( 2.0f * ZW );	Result[8] = ( 2.0f * XZ ) + ( 2.0f * YW );	Result[12] = 0.0f;
		Result[1] = ( 2.0f * XY ) + ( 2.0f * ZW );	Result[5] = WW - XX + YY - ZZ;				Result[9] = ( 2.0f * YZ ) - ( 2.0f * XW );	Result[13] = 0.0f;
		Result[2] = ( 2.0f * XZ ) - ( 2.0f * YW );	Result[6] = ( 2.0f * XW ) + ( 2.0f * YZ );	Result[10] = WW - XX - YY + ZZ;				Result[14] = 0.0f;
		Result[3] = 0.0f;							Result[7] = 0.0f;							Result[11] = 0.0f;							Result[15] = 1.0f;

		return Result;
	}

	Vector3 Quaternion::GetAxis() const
	{
		// Based on :
		// http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToAngle/
		// http://jeux.developpez.com/faq/math/?page=quaternions
		

		Vector3 Result;

		float Length = Math::Sqrt( X * X + Y * Y + Z * Z );
		// Prevent division by 0.0f.
		if( Length != 0.0f )
		{
			Result.X = X / Length;
			Result.Y = Y / Length;
			Result.Z = Z / Length;
		}

		return Result;
	}
	Vector3 Quaternion::GetEulerAngle() const
	{
		// Based on :
		// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles

		Vector3 Result;

		Result.X = Math::ATan2( 2.0f * ( W * X + Y * Z ), 1.0f - 2.0f * ( X * X + Y * Y ) );
		Result.Y = Math::ASin( 2.0f * ( W * Y - Z * X ) );
		Result.Z = Math::ATan2( 2.0f * ( W * Z + X * Y ), 1.0f - 2.0f * ( Y * Y + Z * Z ) );

		return Result;
	}
	float Quaternion::GetAngle() const
	{
		return 2.0f * Math::ACos( W );
	}

} // ae
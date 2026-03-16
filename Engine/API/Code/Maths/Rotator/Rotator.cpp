#include "Rotator.h"

#include "../Functions/MathsFunctions.h"

namespace ae
{
	Rotator::Rotator() :
		m_Angles( 0.0f, 0.0f, 0.0f ),
		m_RotationMatrix( MatrixInitMode::Identity ),
        m_UpdateMatrix( False )
	{
	}

	Rotator::Rotator( float _Pitch, float _Yaw, float _Roll ) :
		m_Angles( 0.0f, 0.0f, 0.0f ),
		m_RotationMatrix( MatrixInitMode::Identity ),
		m_UpdateMatrix( False )
	{
		Pitch( _Pitch );
		Yaw( _Yaw );
		Roll( _Roll );
	}

	void Rotator::Reset()
	{
		m_Angles = Vector3( 0.0f, 0.0f, 0.0f );

		m_RotationMatrix.SetToIdentity();
	}

	Vector3 Rotator::GetLeft() const
	{
        UpdateMatrix();
		return m_RotationMatrix.GetLeft();
	}
	Vector3 Rotator::GetUp() const
	{
		UpdateMatrix();
		return m_RotationMatrix.GetUp();
	}
	Vector3 Rotator::GetForward() const
	{
		UpdateMatrix();
		return m_RotationMatrix.GetForward();
	}


	void Rotator::Pitch( float _Angle )
	{
		m_Angles.X += _Angle;
        m_UpdateMatrix = True;
	}
	void Rotator::Yaw( float _Angle )
	{
		m_Angles.Y += _Angle;
		m_UpdateMatrix = True;
	}
	void Rotator::Roll( float _Angle )
	{
		m_Angles.Z += _Angle;
		m_UpdateMatrix = True;
	}

	void Rotator::SetEulerAngles( const Vector3& _Angles )
	{
		Reset();

		Pitch( _Angles.X );
		Yaw( _Angles.Y );
		Roll( _Angles.Z );
	}
	const Vector3& Rotator::GetEulerAngles() const
	{
		return m_Angles;
	}

	const Matrix4x4& Rotator::GetMatrix() const
	{
        UpdateMatrix();

		return m_RotationMatrix;
	}

	Matrix4x4 Rotator::GetMatrixTransposed()
	{
		return GetMatrix().GetTranspose();
	}

	Rotator Rotator::Combine( const Rotator& _Rotation1, const Rotator& _Rotation2 )
	{
		Rotator Result;

		Result.Pitch( _Rotation1.m_Angles.X );
		Result.Yaw( _Rotation1.m_Angles.Y );
		Result.Roll( _Rotation1.m_Angles.Z );

		Result.Pitch( _Rotation2.m_Angles.X );
		Result.Yaw( _Rotation2.m_Angles.Y );
		Result.Roll( _Rotation2.m_Angles.Z );

		return Result;
	}

    void Rotator::UpdateMatrix() const
    {
        if( !m_UpdateMatrix )
            return;

		Matrix4x4 RotationX( Matrix4x4::Identity );
		RotationX.SetRotation( m_Angles.X, ae::Vector3::AxeX );

		Matrix4x4 RotationY( Matrix4x4::Identity );
		RotationY.SetRotation( m_Angles.Y, ae::Vector3::AxeY );

		Matrix4x4 RotationZ( Matrix4x4::Identity );
		RotationZ.SetRotation( m_Angles.Z, ae::Vector3::AxeZ );

        m_RotationMatrix = std::move( RotationZ * RotationX * RotationY );
        
		m_UpdateMatrix = False;
    }


} // ae
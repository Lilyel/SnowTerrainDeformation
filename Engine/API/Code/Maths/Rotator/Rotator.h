#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Vector/Vector3.h"
#include "../Matrix/Matrix4x4.h"

namespace ae
{
	/// \ingroup math
	/// <summary>
	/// Represent a euler rotation in 3D space.
	/// </summary>
	class AERO_CORE_EXPORT Rotator
	{
	public:
		/// <summary>Default constructor.</summary>
		Rotator();

		/// <summary>Construct a rotation with 3 angles.</summary>
		/// <param name="_Pitch">Angle to apply around the X of the rotator.</param>
		/// <param name="_Yaw">Angle to apply around the Y of the rotator.</param>
		/// <param name="_Roll">Angle to apply around the Z of the rotator.</param>
		Rotator( float _Pitch, float _Yaw, float _Roll );

		/// <summary>Reset the rotation (all angles to 0).</summary>
		void Reset();

		/// <summary>Get the X axis of the rotator.</summary>
		/// <returns>X axis of the rotator.</returns>
		Vector3 GetLeft() const;

		/// <summary>Get the Y axis of the rotator.</summary>
		/// <returns>Y of the rotator.</returns>
		Vector3 GetUp() const;
		
		/// <summary>Get the Z axis of the rotator.</summary>
		/// <returns>Z of the rotator.</returns>
		Vector3 GetForward() const;

		
		/// <summary>Apply a rotation around the X axis of the rotator.</summary>
		/// <param name="_Angle">Angle to apply around the X axis.</param>
		void Pitch( float _Angle );		

		/// <summary>Apply a rotation around the Y axis of the rotator.</summary>
		/// <param name="_Angle">Angle to apply around the Y axis.</param>
		void Yaw( float _Angle );
		
		/// <summary>Apply a rotation around the Z axis of the rotator.</summary>
		/// <param name="_Angle">Angle to apply around the Z axis.</param>
		void Roll( float _Angle );

		/// <summary>Set the angles of the rotation.</summary>
		/// <param name="_Angles">Angles to apply around on each axis.</param>
		void SetEulerAngles( const Vector3& _Angles );
		
		/// <summary>Retrieve euler angles of the rotation.</summary>
		/// <returns>Vector containing all angles.</returns>
		const Vector3& GetEulerAngles() const;


		/// <summary>Retrieve the matrix representing the rotation.</summary>
		/// <returns>Rotation matrix.</returns>
		const Matrix4x4& GetMatrix() const;
		
		/// <summary>Retrieve the transposed matrix representing the rotation.</summary>
		/// <returns>Transposed rotation matrix.</returns>
		Matrix4x4 GetMatrixTransposed();

		/// <summary>Combine two rotation.</summary>
		/// <param name="_Rotation1">First rotation to combine.</param>
		/// <param name="_Rotation2">Second rotation to combine.</param>
		/// <returns>Rotation representing the combination of _Rotation1 and _Rotation2.</returns>
		static Rotator Combine( const Rotator& _Rotation1, const Rotator& _Rotation2 );

    private:
        /// <summary>Update the rotation matrix.</summary>
        void UpdateMatrix() const;

	protected:
		/// <summary>Angles on each axis ( X = Pitch, Y = Yaw, Z = Roll ).</summary>
		Vector3 m_Angles;

		/// <summary>Rotation matrix of the rotator.</summary>
		mutable Matrix4x4 m_RotationMatrix;

        /// <summary>Set to true to update matrix when retrieving it of the forward, left or up axis.</summary>
        mutable Bool m_UpdateMatrix;
	};

} // ae

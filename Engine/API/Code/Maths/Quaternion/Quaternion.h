#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Vector/Vector3.h"
#include "../Matrix/Matrix4x4.h"

// https://www.3dgep.com/understanding-quaternions/

namespace ae
{
	/// \ingroup math
	/**   
	 * Represent a rotation around an axis in 3D space.
	 */
	class AERO_CORE_EXPORT Quaternion
	{
	public:
		/** Default constructor. */
		Quaternion();

		/**
		 * Constructor with composante.
		 *
		 * @param	_X	The x part of the axis.
		 * @param	_Y	The y part of the axis.
		 * @param	_Z	The z part of the axis.
		 * @param	_W	The amount of rotation around the axis.
		 */
		Quaternion( float _X, float _Y, float _Z, float _W );

		/**
		 * Constructor from Axis Angle.
		 *
		 * @param	_Axis 	The axis to rotate around.
		 * @param	_Angle	The angle in radians.
		 */
		Quaternion( const Vector3& _Axis, float _Angle);

		/**
		 * Copy constructor.
		 *
		 * @param	_Quat	The other Quaternion.
		 */
		Quaternion( const Quaternion& _Quat );

		/**
		 * Multiplication with an other Quaternion.
		 * Quaternion multiplication IS NOT commutative.
		 *
		 * @param	_Quat	The other Quaternion.
		 */
		inline void operator*=( const Quaternion& _Quat );

		/**
		 * Addition with an other Quaternion.
		 *
		 * @param	_Quat	The other Quaternion.
		 */
		inline void operator+=( const Quaternion& _Quat );

		/**
		 * Gets the conjugate of the Quaternion.
		 * 
		 * @return	The conjugate.
		 */
		Quaternion GetConjugate() const;

		/**
		 * Gets the magnitude of the Quaternion.
		 *
		 * @return	The magnitude of the Quaternion.
		 */
		float Length() const;

		/**
		 * Gets the magnitude squared of the Quaternion.
		 *
		 * @return	The magnitude of the Quaternion.
		 */
		float LengthSquared() const;

		/**   
		 * Make unit the Quaternion.
		 */
		void Normalise();

		/**
		 * Get a copy of the Quaternion but normalised.
		 *
		 * @return	The Quaternion normalised.
		 */
		Quaternion GetNormalised() const;

		/**
		 * Get the Quaternion matrix.
		 *
		 * @return	Quaternion matrix.
		 */
		Matrix4x4 GetMatrix() const;

		/**
		* Get the Quaternion matrix transposed.
		*
		* @return	Quaternion matrix transposed.
		*/
		Matrix4x4 GetTransposedMatrix() const;

		/**
		 * Get the Axis with which the Quaternion turn around.
		 *
		 * @return	The Quaternion axis.
		 */
		Vector3 GetAxis() const;

		/**
		 * Get Euler rotation of the Quaternion.
		 *
		 * @return	The Euler rotation.
		 */
		Vector3 GetEulerAngle() const;

		/**
		 * Get the angle of the Quaternion.
		 *
		 * @return	The angle in radians.
		 */
		float GetAngle() const;

	public:
		/** The x coordinate. */
		float X;
		/** The y coordinate. */
		float Y;
		/** The z coordinate. */
		float Z;
		/** The amount of rotation. */
		float W;

		/** The zero Quaternion. ( x = 0, y = 0, z = 0, w = 0 ) */
		static const Quaternion Zero;
		/** The Quaternion identity. ( x = 0, y = 0, z = 0, w = 1 ) */
		static const Quaternion Identity;
	};

	/**
	 * Multiplication between two Quaternion.
	 * Quaternion multiplication IS NOT commutative.
	 *
	 * @param	_Quat1	The first Quaternion to multiply.
	 * @param	_Quat2	The second Quaternion to multiply.
	 *
	 * @return	The result of the multiplication.
	 */
	AERO_CORE_EXPORT inline Quaternion operator*( const Quaternion& _Quat1, const Quaternion& _Quat2 );

	/**
	 * Addition between two Quaternion.
	 *
	 * @param	_Quat1	The Quaternion value.
	 * @param	_Quat2	Quaternion to add to it.
	 *
	 * @return	The result of the addition.
	 */
	AERO_CORE_EXPORT inline Quaternion operator+( const Quaternion& _Quat1, const Quaternion& _Quat2 );

} // ae

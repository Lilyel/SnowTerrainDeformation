#pragma once

#include "../../Toolbox/Toolbox.h"

#include "VectorToolbox.h"

#include <string>
#include <iostream>

namespace ae
{
    class Vector2;

	/// \ingroup math

    /// <summary>
    /// Represent a position in 3D space. Floating point precision.
    /// </summary>
    /// <seealso cref="Vector2" />
	class AERO_CORE_EXPORT Vector3
	{
	public:
        /// <summary>
        /// Default constructor.
        /// Fill the vector with zeros.
        /// </summary>
		/// \par Example :
		/// \snippet UnitTestVector3/Constructors.cpp DefaultConstructor example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Constructors.cpp DefaultConstructor expected output
		Vector3();

        /// <summary>
        /// Constructor with values.
        /// </summary>
        /// <param name="_X">The x coordinate.</param>
        /// <param name="_Y">The y coordinate.</param>
        /// <param name="_Z">The z coordinate.</param>
		/// \par Example :
		/// \snippet UnitTestVector3/Constructors.cpp ConstructorValues example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Constructors.cpp ConstructorValues expected output
		Vector3( float _X, float _Y, float _Z );

        /// <summary>
        /// Copy constructor.
        /// </summary>
        /// <param name="_V2">The second vector to do a copy from.</param>
		/// \par Example :
		/// \snippet UnitTestVector3/Constructors.cpp ConstructorCopy example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Constructors.cpp ConstructorCopy expected output
		Vector3( const Vector3& _V2 );

        /// <summary>
        /// Constructor. Create a vector between two coordinates. ( B - A ).
        /// </summary>
        /// <param name="_A">The starting point A.</param>
        /// <param name="_B">The ending point B.</param>
		/// \par Example :
		/// \snippet UnitTestVector3/Constructors.cpp ConstructorTwoPoints example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Constructors.cpp ConstructorTwoPoints expected output
		Vector3( const Vector3& _A, const Vector3& _B );

        /// <summary>
        /// Constructor with 2D vector. Copy X and Y from the 2D vector and set Z to zero.
        /// </summary>
        /// <param name="_Vec2D">The 2D vector to take X and Y from.</param>
		/// \par Example :
		/// \snippet UnitTestVector3/Constructors.cpp Constructor2DVector example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Constructors.cpp Constructor2DVector expected output
        Vector3( const Vector2& _Vec2D );

        /// <summary>
        ///  Copy X and Y from the 2D vector and set Z to zero.
        /// </summary>
        /// <param name="_Vec2D">The 2D vector to take X and Y from.</param>
		/// \par Example :
		/// \snippet UnitTestVector3/Operators.cpp Equal2DOperator example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Operators.cpp Equal2DOperator expected output
        Vector3& operator=( const Vector2& _Vec2D );


		/// <summary>
		/// Acces a component of the vector.<para/>
		/// <paramref name="_Index"/> must be 0, 1 or 2.
		/// </summary>
		/// <param name="_Index">The component of the vector..</param>
		float& operator[]( Uint32 _Index );

		/// <summary>
		/// Acces a component of the vector.<para/>
		/// <paramref name="_Index"/> must be 0, 1 or 2.
		/// </summary>
		/// <param name="_Index">The component of the vector..</param>
		const float& operator[]( Uint32 _Index ) const;


        /// <summary>
        /// Multiplication assignment operator with a vector (element wise).
        /// </summary>
        /// <param name="_v2">The vector to multiply the calling vector with.</param>
        /// <returns>The calling vector after the multiplication.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Operators.cpp MulEqOperator example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Operators.cpp MulEqOperator expected output
		inline Vector3& operator*=( const Vector3& _v2 );

        /// <summary>
        /// Multiplication assignment operator with a value.
        /// </summary>
        /// <param name="_Value">The value to multiply the vector coordinates with.</param>
        /// <returns>The calling vector after the multiplication.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Operators.cpp MulEqValueOperator example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Operators.cpp MulEqValueOperator expected output
		inline Vector3& operator*=( const float _Value );

        /// <summary>
        /// Division assignment operator with a vector (element wise).
        /// </summary>
        /// <param name="_v2">The second vector to divide the calling vector with.</param>
        /// <returns>The calling vector after the division.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Operators.cpp DivEqOperator example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Operators.cpp DivEqOperator expected output
		inline Vector3& operator/=( const Vector3& _v2 );

        /// <summary>
        /// Division assignment operator with a value.
        /// </summary>
        /// <param name="_Value">The value to divide the vector coordinates with.</param>
        /// <returns>The calling vector after the division.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Operators.cpp DivEqValueOperator example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Operators.cpp DivEqValueOperator expected output
		inline Vector3& operator/=( const float _Value );

        /// <summary>
        /// Subtraction assignment operator with a vector.
        /// </summary>
        /// <param name="_v2">The second vector to subtract the calling vector with.</param>
        /// <returns>The calling vector after the subtraction.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Operators.cpp SubEqOperator example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Operators.cpp SubEqOperator expected output
		inline Vector3& operator-=( const Vector3& _v2 );

        /// <summary>
        ///Subtraction assignment operator with a value.
        /// </summary>
        /// <param name="_Value">The value to subtract the vector coordinates with.</param>
        /// <returns>The calling vector after the subtraction.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Operators.cpp SubEqValueOperator example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Operators.cpp SubEqValueOperator expected output
		inline Vector3& operator-=( const float _Value );

        /// <summary>
        /// Addition assignment operator with a vector.
        /// </summary>
        /// <param name="_v2">The second vector to add the calling vector with.</param>
        /// <returns>The calling vector after the addition.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Operators.cpp AddEqOperator example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Operators.cpp AddEqOperator expected output
		inline Vector3& operator+=( const Vector3& _v2 );

        /// <summary>
        /// Addition assignment operator with a value.
        /// </summary>
        /// <param name="_Value">The value to add the vector coordinates with.</param>
        /// <returns>The calling vector after the addition.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Operators.cpp AddEqValueOperator example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Operators.cpp AddEqValueOperator expected output
		inline Vector3& operator+=( const float _Value );


        /// <summary>
        /// Negation operator.
        /// Multiply each coordinates with -1.
        /// </summary>
        /// <returns>A copy negated of the calling matrix.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Operators.cpp NegativeOperator example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Operators.cpp NegativeOperator expected output
		inline Vector3 operator-( ) const;


        /// <summary>
        /// Calculate the length of vector (Euclidean, L2).
        /// </summary>
        /// <returns>Length of the vector. Or 0.0f if both coordinates equals 0.0f.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp Length example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp Length expected output
		float Length() const;

        /// <summary>
        ///  Calculate the length of vector using a specific algorithm.
        /// </summary>
        /// <param name="_Algorithm">Algorithm to use to process the length of the vector.</param>
        /// <param name="_P">P value for VectorLength::Norm_p</param>
        /// <returns>Length of the vector using the given algorithm.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp LengthAlgos example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp LengthAlgos expected output
        float Length( VectorLength _Algorithm, float _P = 2.0f ) const;

        /// <summary>
        /// Calculate the squared length of the vector (Squared euclidean, squared L2).
        /// </summary>
        /// <returns>Squared length of the vector. Or 0.0f if both coordinates equals 0.0f.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp LengthSqr example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp LengthSqr expected output
		float LengthSqr() const;


        /// <summary>
        /// Rotate the vector.
        /// </summary>
        /// <param name="_Angle">The angle to apply in radians.</param>
        /// <param name="_Axis">The axis to rotate around.</param>
        /// <returns>The calling vector rotated.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp Rotate example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp Rotate expected output
		Vector3& Rotate( const float _Angle, const Vector3& _Axis );

        /// <summary>
        /// Translate the vector.
        /// </summary>
        /// <param name="_Offset">The offset to apply.</param>
        /// <returns>The calling vector translated.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp Translate example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp Translate expected output
        Vector3& Translate( const Vector3& _Offset );

        /// <summary>
        /// Scale the vector.
        /// </summary>
        /// <param name="_Scale">The scale factors to apply in each axis.</param>
        /// <returns>The calling vector scaled.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp Scale example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp Scale expected output
        Vector3& Scale( const Vector3& _Scale );


        /// <summary>
        /// Calculate a dot product between the calling vector and <paramref name="_v2"/>
        /// </summary>
        /// <param name="_v2">Second vector to do the dot product with.</param>
        /// <returns>Result of the dot product between the calling vector and <paramref name="_v2"/></returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp Dot example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp Dot expected output
		float Dot( const Vector3& _v2 ) const;


        /// <summary>
        /// Calculate a cross product between the calling vector and <paramref name="_v2"/>
        /// </summary>
        /// <param name="_v2">Second vector to do the cross product with.</param>
        /// <returns>Result of the cross product between the calling vector and <paramref name="_v2"/></returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp Cross example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp Cross expected output
		Vector3 Cross( const Vector3& _v2 ) const;


        /// <summary>
        /// Calculate the euler angles between the vector and the axis X in radians.
		/// The angle is clockwise.
        /// </summary>
		/// <param name="_AngleRange">The angle range.</param>
        /// <returns>Euler angles between the calling vector and the axis X in radians.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp AngleX example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp AngleX expected output
		Vector3 Angle( const VectorAngleRange _AngleRange = VectorAngleRange::Unsigned_0_2PI ) const;


        /// <summary>
        /// Calculate the angle in radians between the calling vector and <paramref name="_v2"/>.
		/// The angle is clockwise.
        /// </summary>
        /// <param name="_v2">Second vector to process the angle with the calling vector.</param>
		/// <param name="_AngleRange">The angle range.</param>
        /// <returns>Angle between the calling vector and <paramref name="_v2" /> in radians.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp AngleVector example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp AngleVector expected output
		float Angle( const Vector3& _v2, const VectorAngleRange _AngleRange = VectorAngleRange::Signed_0_PI ) const;


        /// <summary>
        /// Make a unit the calling vector.
        ///	The Vector will have the same direction
        ///	But its length will be equal to 1.0f.
        /// </summary>
        /// <returns>The calling vector normalized.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp GetNormalized example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp GetNormalized expected output
		Vector3& Normalize();

        /// <summary>
        /// Make a unit vector from calling vector.
        /// The Vector will have the same direction of the calling vector
        /// But its length will be equal to 1.0f.
        /// </summary>
        /// <returns>A copy normalized of the calling vector.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp Normalize example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp Normalize expected output
		Vector3 GetNormalized() const;

        /// <summary>
        /// Query if the vector is unit.
        /// </summary>
        /// <returns>True if unit, False if not.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp IsUnit example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp IsUnit expected output
		Bool IsUnit() const;

        /// <summary>
        /// Query if the vector is unit by epsilon.
        /// </summary>
        /// <returns>True if unit by epsilon, False if not.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp IsUnitByEpsilon example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp IsUnitByEpsilon expected output
		Bool IsUnitByEpsilon() const;


         /// <summary>
         /// Query if the vector is null ( all coordinates equal to 0 ).
         /// </summary>
         /// <returns>True if null, False otherwise.</returns>
		 /// \par Example :
		 /// \snippet UnitTestVector3/Functionalities.cpp IsNull example
		 /// \par Expected Output :
		 /// \snippetdoc UnitTestVector3/Functionalities.cpp IsNull expected output
		Bool IsNull() const;

        /// <summary>
        /// Query if the vector is null by epsilon ( all coordinates null by epsilon ). 
        /// </summary>
        /// <returns>True if null by epsilon, False otherwise.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp IsNullByEpsilon example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp IsNullByEpsilon expected output
		Bool IsNullByEpsilon() const;


        /// <summary>
        /// Set all three coordinates with the given parameters.
        /// </summary>
        /// <param name="_X">New value for the x coordinate.</param>
        /// <param name="_Y">New value for the y coordinate.</param>
        /// <param name="_Z">New value for the z coordinate.</param>
        /// <returns>Calling vector with the new coordinates values.</returns>
		/// \par Example :
		/// \snippet UnitTestVector3/Functionalities.cpp Set example
		/// \par Expected Output :
		/// \snippetdoc UnitTestVector3/Functionalities.cpp Set expected output
		Vector3& Set( float _X, float _Y, float _Z );

		/// <summary>
		/// Compute the scalar triple product : <para/>
		/// Caller.Cross( <paramref name="_ToCross"/> ).Dot( <paramref name="_ToDot"/> )</summary>
		/// <param name="_ToCross">Vector to use for the cross product (first part of the scalar triple product).</param>
		/// <param name="_ToDot">Vector to use for the dot product (second part of the scalar triple product).</param>
		/// <returns>Result of the scalar triple product.</returns>
		float ScalarTriple( const Vector3& _ToCross, const Vector3& _ToDot ) const;

	public:
        /// <summary>The x coordinate of the vector.</summary>
		float X;
        /// <summary>The y coordinate of the vector.</summary>
		float Y;
        /// <summary>The z coordinate of the vector.</summary>
		float Z;


        /// <summary>
        /// The zero vector.
        /// x = 0.0f, y = 0.0f and z = 0.0f.
        /// </summary>
		static const Vector3 Zero;
        /// <summary>
        /// The one vector.
        /// x = 1.0f, y = 1.0f and z = 1.0f.
        /// </summary>
		static const Vector3 One;
        /// <summary>
        /// The X axis vector.
        /// x = 1.0f, y = 0.0f and z = 0.0f.
        /// </summary>
		static const Vector3 AxeX;
        /// <summary>
        /// The Y axis vector.
        /// x = 0.0f, y = 1.0f and z = 0.0f.
        /// </summary>
		static const Vector3 AxeY;
        /// <summary>
        /// The Z axis vector.
        /// x = 0.0f, y = 0.0f and z = 1.0f.
        /// </summary>
		static const Vector3 AxeZ;
	};




    /// <summary>Multiplication operator with two vectors (element wise).</summary>
    /// <param name="_v1">The first vector.</param>
    /// <param name="_v2">The second vector to multiply <paramref name = "_v1"/> with.</param>
    /// <returns>The result of the multiplication as a new vector.</returns>
	/// \par Example :
	/// \snippet UnitTestVector3/Operators.cpp MulOperator example
	/// \par Expected Output :
	/// \snippetdoc UnitTestVector3/Operators.cpp MulOperator expected output
	AERO_CORE_EXPORT inline Vector3 operator*( const Vector3& _v1, const Vector3& _v2 );

    /// <summary>Multiplication operator with a vector and a value.</summary>
    /// <param name="_Vector">The vector to multiply with the value.</param>
    /// <param name="_Value">The value to multiply  <paramref name = "_Vector"/> with.</param>
    /// <returns>The result of the multiplication as a new vector.</returns>
	/// \par Example :
	/// \snippet UnitTestVector3/Operators.cpp MulValueOperator example
	/// \par Expected Output :
	/// \snippetdoc UnitTestVector3/Operators.cpp MulValueOperator expected output
	AERO_CORE_EXPORT inline Vector3 operator*( const Vector3& _Vector, const float _Value );

	/// <summary>Multiplication operator with a vector and a value.</summary>
   /// <param name="_Value">The value to multiply  <paramref name = "_Vector"/> with.</param>
   /// <param name="_Vector">The vector to multiply with the value.</param>
   /// <returns>The result of the multiplication as a new vector.</returns>
	AERO_CORE_EXPORT inline Vector3 operator*( const float _Value, const Vector3& _Vector );

    /// <summary>Division operator with two vectors (element wise).</summary>
    /// <param name="_v1">The first vector.</param>
    /// <param name="_v2">The second vector to divide <paramref name = "_v1"/> with.</param>
    /// <returns>The result of the division as a new vector.</returns>
	/// \par Example :
	/// \snippet UnitTestVector3/Operators.cpp DivOperator example
	/// \par Expected Output :
	/// \snippetdoc UnitTestVector3/Operators.cpp DivOperator expected output
	AERO_CORE_EXPORT inline Vector3 operator/( const Vector3& _v1, const Vector3& _v2 );

    /// <summary>
    /// Division operator with a vector and a value.<para/>
    /// X = <paramref name="_Value"/> / X<para/>
	/// Y = <paramref name="_Value"/> / Y<para/>
	/// Z = <paramref name="_Value"/> / Z<para/>
    /// </summary>
    /// <param name="_Vector">The vector to divide with the value.</param>
    /// <param name="_Value">The value to divide  <paramref name = "_Vector"/> with.</param>
    /// <returns>The result of the division as a new vector.</returns>
	/// \par Example :
	/// \snippet UnitTestVector3/Operators.cpp DivValueOperator example
	/// \par Expected Output :
	/// \snippetdoc UnitTestVector3/Operators.cpp DivValueOperator expected output
	AERO_CORE_EXPORT inline Vector3 operator/( const Vector3& _Vector, const float _Value );

	/// <summary>
	/// Division operator with a value and a vector. <para/>
	/// X = <paramref name="_Value"/> / X<para/>
	/// Y = <paramref name="_Value"/> / Y<para/>
	/// Z = <paramref name="_Value"/> / Z<para/>
	/// </summary>
	/// <param name="_Value">The value to divide  <paramref name = "_Vector"/> with.</param>
	/// <param name="_Vector">The vector to divide with the value.</param>
	/// <returns>The result of the division as a new vector.</returns>
	AERO_CORE_EXPORT inline Vector3 operator/( const float _Value, const Vector3& _Vector );

    /// <summary>Subtraction operator with two vectors.</summary>
    /// <param name="_v1">The first vector.</param>
    /// <param name="_v2">The second vector to subtract <paramref name = "_v1"/> with.</param>
    /// <returns>The result of the subtraction as a new vector.</returns>
	/// \par Example :
	/// \snippet UnitTestVector3/Operators.cpp SubOperator example
	/// \par Expected Output :
	/// \snippetdoc UnitTestVector3/Operators.cpp SubOperator expected output
	AERO_CORE_EXPORT inline Vector3 operator-( const Vector3& _v1, const Vector3& _v2 );

    /// <summary>Subtraction operator with a vector and a value.</summary>
    /// <param name="_Vector">The vector to subtrct with the value.</param>
    /// <param name="_Value">The value to subtract  <paramref name = "_Vector"/> with.</param>
    /// <returns>The result of the subtraction as a new vector.</returns>
	/// \par Example :
	/// \snippet UnitTestVector3/Operators.cpp SubValueOperator example
	/// \par Expected Output :
	/// \snippetdoc UnitTestVector3/Operators.cpp SubValueOperator expected output
	AERO_CORE_EXPORT inline Vector3 operator-( const Vector3& _Vector, const float _Value );

	/// <summary>Subtraction operator with a vector and a value.</summary>
	/// <param name="_Value">The value to subtract  <paramref name = "_Vector"/> with.</param>
	/// <param name="_Vector">The vector to subtrct with the value.</param>
	/// <returns>The result of the subtraction as a new vector.</returns>
	AERO_CORE_EXPORT inline Vector3 operator-( const float _Value, const Vector3& _Vector );

    /// <summary>Addition operator with two vectors.</summary>
    /// <param name="_v1">The first vector.</param>
    /// <param name="_v2">The second vector to add <paramref name = "_v1"/> with.</param>
    /// <returns>The result of the addition as a new vector.</returns>
	/// \par Example :
	/// \snippet UnitTestVector3/Operators.cpp AddOperator example
	/// \par Expected Output :
	/// \snippetdoc UnitTestVector3/Operators.cpp AddOperator expected output
	AERO_CORE_EXPORT inline Vector3 operator+( const Vector3& _v1, const Vector3& _v2 );

    /// <summary>Addition operator with a vector and a value.</summary>
    /// <param name="_Vector">The vector to add with the value.</param>
    /// <param name="_Value">The value to add  <paramref name = "_Vector"/> with.</param>
    /// <returns>The result of the addition as a new vector.</returns>
	/// \par Example :
	/// \snippet UnitTestVector3/Operators.cpp AddValueOperator example
	/// \par Expected Output :
	/// \snippetdoc UnitTestVector3/Operators.cpp AddValueOperator expected output
	AERO_CORE_EXPORT inline Vector3 operator+( const Vector3& _Vector, const float _Value );

	/// <summary>Addition operator with a vector and a value.</summary>
	/// <param name="_Value">The value to add  <paramref name = "_Vector"/> with.</param>
	/// <param name="_Vector">The vector to add with the value.</param>
	/// <returns>The result of the addition as a new vector.</returns>
	/// \par Example :
	/// \snippet UnitTestVector3/Operators.cpp AddValueOperator example
	/// \par Expected Output :
	/// \snippetdoc UnitTestVector3/Operators.cpp AddValueOperator expected output
	AERO_CORE_EXPORT inline Vector3 operator+( const float _Value, const Vector3& _Vector );

    /// <summary>Equality operator with two vectors.</summary>
    /// <param name="_v1">The first vector to compare.</param>
    /// <param name="_v2">The second vector to compare.</param>
    /// <returns>True if both x coordinates are the same and if both y coordinates are the same.</returns>
	/// \par Example :
	/// \snippet UnitTestVector3/Operators.cpp EqualOperator example
	/// \par Expected Output :
	/// \snippetdoc UnitTestVector3/Operators.cpp EqualOperator expected output
	AERO_CORE_EXPORT inline Bool operator==( const Vector3& _v1, const Vector3& _v2 );

    /// <summary>Inequality operator with two vectors.</summary>
    /// <param name="_v1">The first vector to compare.</param>
    /// <param name="_v2">The second vector to compare.</param>
    /// <returns>True if both x coordinates are NOT the same OR if both y coordinates are NOT the same.</returns>
	/// \par Example :
	/// \snippet UnitTestVector3/Operators.cpp DiffOperator example
	/// \par Expected Output :
	/// \snippetdoc UnitTestVector3/Operators.cpp DiffOperator expected output
	AERO_CORE_EXPORT inline Bool operator!=( const Vector3& _v1, const Vector3& _v2 );


    /// <summary>Convert a vector 3D to a string.</summary>
    /// <param name="_Vector">Vector 3D to convert.</param>
    /// <returns>Vector 3D as a C++ string. ( Format : X = ... Y = ... Z = ... ).</returns>
    AERO_CORE_EXPORT inline std::string ToString( const ae::Vector3& _Vector );

} // ae


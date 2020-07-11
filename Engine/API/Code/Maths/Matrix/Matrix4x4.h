#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Vector/Vector3.h"

#include "MatrixToolbox.h"

#include <string>
#include <iostream>
#include <array>

namespace ae
{
    /// \ingroup math   
    /// <summary>Matrix with 4 lines and 4 columns.</summary>
    /// <seealso cref="Matrix3x3" />
    class AERO_CORE_EXPORT Matrix4x4
    {
    public:

        /// <summary>
        /// Enum to help to read access with operator[].
        /// Mostly used internally. 
        /// <remarks>
        /// operator( row, column ) is available for an easy public access.
        /// R are rows and C the columns.
        /// For example [R1C0] is equivalent to [1][0].
        /// </remarks>
        /// </summary>
        enum IndexHelper
        {
            R0C0 = 0, R0C1 = 1, R0C2 = 2, R0C3 = 3,
            R1C0 = 4, R1C1 = 5, R1C2 = 6, R1C3 = 7,
            R2C0 = 8, R2C1 = 9, R2C2 = 10, R2C3 = 11,
            R3C0 = 12, R3C1 = 13, R3C2 = 14, R3C3 = 15
        };

    public:
        /// <summary>Create an matrix with default elements constructor.</summary>
        /// <param name="_InitMode">Determine how to fill the value.</param>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Constructors.cpp Constructor Init example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Constructors.cpp Constructor Init expected output
        explicit Matrix4x4( MatrixInitMode _InitMode = MatrixInitMode::Default );


        /// <summary>Create an matrix with given elements.</summary>
        /// <param name="_Elements">Elements to fill the new matrix with.</param>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Constructors.cpp Constructor Elements example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Constructors.cpp Constructor Elements expected output
        Matrix4x4( const std::initializer_list<float>& _Elements );


        /// <summary>Create an matrix with given elements.</summary>
        /// <param name="_Elements">2D list to fill the new matrix with.</param>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Constructors.cpp Constructor Elements2D example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Constructors.cpp Constructor Elements2D expected output
        Matrix4x4( const std::initializer_list<std::initializer_list<float>>& _Elements );


        /// <summary>Create an matrix and copy the element from the other matrix. </summary>
        /// <remarks>
        /// Copy each element with "=" operator, be sure that this operator
        /// do what you expect with the objects.
        /// </remarks>
        /// <param name="_Copy">Matrix to copy the elements from.</param>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Constructors.cpp Constructor Copy example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Constructors.cpp Constructor Copy expected output
        Matrix4x4( const Matrix4x4& _Copy );


        /// <summary>Copy operator</summary>
        /// <param name="_Copy">Matrix to copy the elements from.</param>
        /// <returns>Matrix with the elements copied.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp CopyOperator example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp CopyOperator expected output
        Matrix4x4& operator=( const Matrix4x4& _Copy );


        /// <summary>
        /// Negation operator.
        /// Will multiply with -1 each value of the matrix.
        /// </summary>
        /// <returns>The calling matrix negated (not the calling matrix, a copy negated).</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp NegativeOperator example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp NegativeOperator expected output
         Matrix4x4 operator-() const;


        /// <summary>
        /// Sets to identity the matrix.
        /// The diagonal will be set to 1.0f and other values to 0.0f.
        /// </summary>
        /// <returns>The calling matrix set to identity.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp SetToIdentity example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp SetToIdentity expected output
        Matrix4x4& SetToIdentity();

        /// <summary>
        /// Sets to zero the matrix.
        /// Every values will be set to 0.0f.
        /// </summary>
        /// <returns>The calling matrix filled with zeros.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp SetToZero example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp SetToZero expected output
        Matrix4x4& SetToZero();


        /// <summary>Get the direction in front of the current transformation.</summary>
        /// <returns>Forward direction of the transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetForward example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetForward expected output
        Vector3 GetForward() const;

        /// <summary>Get the direction to the left of the current transformation.</summary>
        /// <returns>Left direction of the transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetLeft example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetLeft expected output
        Vector3 GetLeft() const;

        /// <summary>Get the direction above the current transformation.</summary>
        /// <returns>Upward direction of the transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetUp example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetUp expected output
        Vector3 GetUp() const;


        /// <summary>Get the direction (normalized) in front of the current transformation.</summary>
        /// <returns>Forward direction of the transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetForwardUnit example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetForwardUnit expected output
        Vector3 GetForwardUnit() const;

        /// <summary>Get the direction (normalized) to the left of the current transformation.</summary>
        /// <returns>Left direction of the transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetLeftUnit example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetLeftUnit expected output
        Vector3 GetLeftUnit() const;

        /// <summary>Get the direction (normalized) above the current transformation.</summary>
        /// <returns>Upward direction of the transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetUpUnit example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetUpUnit expected output
        Vector3 GetUpUnit() const;



        /// <summary>
        /// Rotate the matrix around an axis.
        /// Add the rotation to the current one.
        /// </summary>
        /// <param name="_Angle">The angle in radians.</param>
        /// <param name="_Axis">The axis to rotate around.</param>
        /// <returns>The calling matrix rotated.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp Rotations example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp Rotations expected output
        Matrix4x4& Rotate( const float _Angle, const Vector3& _Axis );

        /// <summary>
        /// Rotate the matrix around X axis.
        /// Add the new rotation to the old one.
        /// </summary>
        /// <param name="_Angle">The angle in radians.</param>
        /// <returns>The calling matrix rotated.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp Rotations example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp Rotations expected output
        Matrix4x4& RotateX( const float _Angle );

        /// <summary>
        /// Rotate the matrix around Y axis.
        /// Add the new rotation to the old one.
        /// </summary>
        /// <param name="_Angle">The angle in radians.</param>
        /// <returns>The calling matrix rotated.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp Rotations example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp Rotations expected output
        Matrix4x4& RotateY( const float _Angle );

        /// <summary>
        /// Rotate the matrix around Z axis.
        /// Add the new rotation to the old one.
        /// </summary>
        /// <param name="_Angle">TThe angle in radians.</param>
        /// <returns>The calling matrix rotated.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp Rotations example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp Rotations expected output
        Matrix4x4& RotateZ( const float _Angle );


        /// <summary>
        /// Rotate the matrix around an axis.
        /// Override the current rotation.
        /// </summary>
        /// <param name="_Angle">The angle in radians.</param>
        /// <param name="_Axis">The axis to rotate around.</param>
        /// <returns>The calling matrix with the new rotation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp SetRotation example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp SetRotation expected output
        Matrix4x4& SetRotation( const float _Angle, const Vector3& _Axis );

        /// <summary>
        /// Rotate the matrix around X axis.
        /// Override the old roration.
        /// </summary>
        /// <param name="_Angle">The new angle in radians.</param>
        /// <returns>The calling matrix with the new rotation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp SetRotationX example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp SetRotationX expected output
        Matrix4x4& SetRotationX( const float _Angle );

        /// <summary>
        /// Rotate the matrix around Y axis.
        /// Override the old roration.
        /// </summary>
        /// <param name="_Angle">The new angle in radians.</param>
        /// <returns>The calling matrix with the new rotation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp SetRotationY example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp SetRotationY expected output
        Matrix4x4& SetRotationY( const float _Angle );

        /// <summary>
        /// Rotate the matrix around Y axis.
        /// Override the old roration.
        /// </summary>
        /// <param name="_Angle">The new angle in radians.</param>
        /// <returns>The calling matrix with the new rotation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp SetRotationZ example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp SetRotationZ expected output
        Matrix4x4& SetRotationZ( const float _Angle );


        /// <summary>
        /// Scale the matrix.
        /// Multiply the new scale with the old one.
        /// </summary>
        /// <param name="_Scale">The scale factor.</param>
        /// <returns>The calling matrix scaled.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp Scale example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp Scale expected output
        Matrix4x4& Scale( const Vector3& _Scale );

        /// <summary>
        /// Scale the matrix.
        /// Override the old scale.
        /// </summary>
        /// <param name="_Scale">The new scale.</param>
        /// <returns>The calling matrix with the new scale.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp SetScale example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp SetScale expected output
        Matrix4x4& SetScale( const Vector3& _Scale );


        /// <summary>
        /// Translate the matrix.
        /// Add the new translation to the old one.
        /// </summary>
        /// <param name="_Vector">The offset to apply.</param>
        /// <returns>The calling matrix translated.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp Translate example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp Translate expected output
        Matrix4x4& Translate( const Vector3& _Vector );

        /// <summary>
        /// Translate the matrix.
        /// </summary>
        /// <param name="_Vector">The new offset.</param>
        /// <returns>The calling matrix with the new translation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp SetTranslation example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp SetTranslation expected output
        Matrix4x4& SetTranslation( const Vector3& _Vector );


        /// <summary>
        /// Set the matrix to look at a point.
        /// Be aware that will be override the current value of the matrix.
        /// </summary>
        /// <param name="_Eye">The eye position.</param>
        /// <param name="_PointToLookAt">The point position to look at.</param>
        /// <param name="_UpWorld">The up of the world.</param>
        /// <returns>The calling matrix set to look at the specified point.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp LookAt example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp LookAt expected output
        Matrix4x4& LookAt( const Vector3& _Eye, const Vector3& _PointToLookAt, const Vector3& _UpWorld );


        /// <summary>
        /// Get the determinant of the matrix.
        /// </summary>
        /// <returns>The determinant of the matrix.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetDeterminant example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetDeterminant expected output
        float GetDeterminant() const;


        /// <summary>
        /// Inverse the matrix.
        /// Can fail due to Determinant = 0.
        /// </summary>
        /// <returns>The calling matrix inversed if success, matrix unchanged otherwise.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp Inverse example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp Inverse expected output
        Matrix4x4& Inverse();

        /// <summary>
        /// Get the inverse of the calling matrix.
        /// Can fail due to Determinant = 0.
        /// </summary>
        /// <returns>The matrix inversed, if it fail, return the matrix unchanged.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetInverse example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetInverse expected output
        Matrix4x4 GetInverse() const;

        /// <summary>
        /// Switch the last column with the last line of the matrix.
        /// </summary>
        /// <returns>The calling matrix with the translation moved.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp SwitchVectorPosition example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp SwitchVectorPosition expected output
        Matrix4x4&  SwitchVectorPosition();


        /// <summary>
        /// Copy the point, transform then return the copy.
        /// </summary>
        /// <param name="_Point">The point to transform.</param>
        /// <returns>The transformed point.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetTransformedPoint example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetTransformedPoint expected output
        Vector3 GetTransformedPoint( const Vector3& _Point ) const;


        /// <summary>
        /// Transforms the point.
        /// </summary>
        /// <param name="_Point">The point to transform.</param>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp TransformPoint example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp TransformPoint expected output
        void TransformPoint( AE_InOut Vector3& _Point ) const;


        /// <summary>
        /// Set the matrix to do a perspective projection.
        /// </summary>
        /// <param name="_Fov">The field of view.</param>
        /// <param name="_Aspect">The aspect ratio.</param>
        /// <param name="_Near">The near distance.</param>
        /// <param name="_Far">The far distance.</param>
        /// <returns>The callind matrix computed to do a perspective projection.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp SetToPerspectiveMatrix example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp SetToPerspectiveMatrix expected output
        Matrix4x4& SetToPerspectiveMatrix( const float _Fov, const float _Aspect, const float _Near, const float _Far );

        /// <summary>
        /// Set the matrix to do an orthogonal projection.
        /// </summary>
        /// <param name="_Left">The left of the viewport.</param>
        /// <param name="_Top">The top of the viewport.</param>
        /// <param name="_Right">The right of the viewport.</param>
        /// <param name="_Bottom">The botton of the viewport.</param>
        /// <param name="_Near">The closest distance possible to see objects.</param>
        /// <param name="_Far">The biggest distance possible to see objects.</param>
        /// <returns>The calling matrix computed to do a orthogonal projection.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp SetToOrthogonalMatrix example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp SetToOrthogonalMatrix expected output
        Matrix4x4& SetToOrthogonalMatrix( const float _Left, const float _Top, const float _Right, const float _Bottom,
                                          const float _Near, const float _Far );


        /// <summary>
        /// Get a matrix which do a perspective projection.
        /// </summary>
        /// <param name="_Fov">The field of view.</param>
        /// <param name="_Aspect">The aspect ratio.</param>
        /// <param name="_Near">The near distance.</param>
        /// <param name="_Far">The far distance.</param>
        /// <returns>The computed perspective matrix.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetPerspectiveMatrix example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetPerspectiveMatrix expected output
        static Matrix4x4 GetPerspectiveMatrix( const float _Fov, const float _Aspect, const float _Near, const float _Far );


        /// <summary>
        /// Get a matrix which do an orthogonal projection.
        /// </summary>
        /// <param name="_Left">The left of the viewport.</param>
        /// <param name="_Top">The top of the viewport.</param>
        /// <param name="_Right">The right of the viewport.</param>
        /// <param name="_Bottom">The botton of the viewport.</param>
        /// <param name="_Near">The closest distance possible to see objects.</param>
        /// <param name="_Far">The biggest distance possible to see objects.</param>
        /// <returns>The orthogonal matrix.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetOrthogonalMatrix example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetOrthogonalMatrix expected output
        static Matrix4x4 GetOrthogonalMatrix( const float _Left, const float _Top, const float _Right, const float _Bottom,
                                              const float _Near, const float _Far );


        /// <summary>
        /// Do a matrix with the scale transformation.
        /// </summary>
        /// <param name="_Scale">The scale factor on each axis.</param>
        /// <returns>The matrix containing the scale transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetScaleMatrix example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetScaleMatrix expected output
        static Matrix4x4 GetScaleMatrix( const Vector3& _Scale );

        /// <summary>
        /// Do a matrix with the rotation transformation.
        /// </summary>
        /// <param name="_Angle">The angle in radians.</param>
        /// <param name="_Axis">The axis to rotate around.</param>
        /// <returns>The matrix containing the rotation transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetRotationMatrix example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetRotationMatrix expected output
        static Matrix4x4 GetRotationMatrix( const float _Angle, const Vector3& _Axis );

        /// <summary>
        /// Do a matrix with the translation transformation.
        /// </summary>
        /// <param name="_Vector">The translation to apply.</param>
        /// <returns>The matrix containing the translation transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetTranslationMatrix example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetTranslationMatrix expected output
        static Matrix4x4 GetTranslationMatrix( const Vector3& _Vector );

        /// <summary>
        /// Get a matrix which look at a point.
        /// </summary>
        /// <param name="_Eye">The eye position.</param>
        /// <param name="_PointToLookAt">The point position to look at.</param>
        /// <param name="_UpWorld">The up of the world.</param>
        /// <returns>The look at matrix.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetLookAtMatrix example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetLookAtMatrix expected output
        static Matrix4x4 GetLookAtMatrix( const Vector3& _Eye, const Vector3& _PointToLookAt, const Vector3& _UpWorld );





        /// <summary>Tranpose the matrix.</summary>
        /// <returns>Matrix transposed.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp Transpose example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp Transpose expected output
         Matrix4x4& Transpose();

        /// <summary>Retrieve the transpose of the calling matrix (without modifying it).</summary>
        /// <returns>The calling matrix transposed.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetTranspose example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetTranspose expected output
         Matrix4x4 GetTranspose() const;


        /// <summary>Apply absolute value to each element of the matrix.</summary>
        /// <returns>Matrix with all element as absolute value.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp Abs example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp Abs expected output
         Matrix4x4& Abs();


        /// <summary>Apply absolute value to each element of the matrix.</summary>
        /// <returns>Matrix with all element as absolute value.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetAbs example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetAbs expected output
         Matrix4x4 GetAbs() const;

        /// <summary>Process the sum of all diagonal elements.</summary>
        /// <returns>Sum of diagonal elements.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Functionalities.cpp GetTrace example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Functionalities.cpp GetTrace expected output
         float GetTrace() const;




        /// <summary>Multiply each element of the matrix with a scalar value.</summary>
        /// <param name="_Scalar">The scalar value to multiply the matrix with.</param>
        /// <returns>Matrix multiplied by the <paramref name="_Scalar"/></returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp MulEqual example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp MulEqual expected output
         Matrix4x4& operator*=( const float& _Scalar );


        /// <summary>Divide each element of the matrix with a scalar value.</summary>
        /// <param name="_Scalar">The scalar value to divide the matrix with.</param>
        /// <returns>Matrix divided by the <paramref name="_Scalar"/>.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp DivEqual example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp DivEqual expected output
         Matrix4x4& operator/=( const float& _Scalar );


        /// <summary>Add to each element of the matrix a scalar value.</summary>
        /// <param name="_Scalar">The scalar value to add to the matrix with.</param>
        /// <returns>Matrix with the <paramref name="_Scalar"/> added to each elements.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp AddEqual example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp AddEqual expected output
         Matrix4x4& operator+=( const float& _Scalar );


        /// <summary>Subtract to each element of the matrix a scalar value.</summary>
        /// <param name="_Scalar">The scalar value to add to the matrix with.</param>
        /// <returns>Matrix with the <paramref name="_Scalar"/> subtracted to each elements.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp SubEqual example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp SubEqual expected output
         Matrix4x4& operator-=( const float& _Scalar );


        /// <summary>Multuply a matrix with another one.</summary>
        /// <remarks>
        /// Apply : A * B. Where A is the calling matrix and B is 
        /// <paramref name="_MatB"/>
        /// </remarks>
        /// <param name="_MatB">The second matrix to multiply the calling one with.</param>
        /// <returns>The calling matrix multiplied by <paramref name="_MatB"/></returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp MulEqualMat example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp MulEqualMat expected output
         Matrix4x4& operator*=( const Matrix4x4& _MatB );


        /// <summary>Divide each element calling matrix with the respective elements of another one.</summary>_MatB"/>
        /// <remarks>
        /// Dimensions must be the same.
        /// This operation is NOT the inverse of multiplication.
        /// It does an element per element division.
        /// </remarks>
        /// <param name="_MatB">The second matrix to divide the calling one with.</param>
        /// <returns>
        /// The calling matrix with its elements divided by 
        /// the respective elements of <paramref name="_MatB"/>
        /// </returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp DivEqualMat example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp DivEqualMat expected output
         Matrix4x4& operator/=( const Matrix4x4& _MatB );


        /// <summary>Add each elemens the calling matrix with the respective elements of another one.</summary>
        /// <param name="_MatB">The second matrix to add the calling one with.</param>
        /// <returns>
        /// The calling matrix with its elements added with 
        /// the respective elements of <paramref name="_MatB"/>
        /// </returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp AddEqualMat example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp AddEqualMat expected output
         Matrix4x4& operator+=( const Matrix4x4& _MatB );


        /// <summary>Subtract each elemens the calling matrix with the respective elements of another one.</summary>
        /// <param name="_MatB">The second matrix to subtract the calling one with.</param>
        /// <returns>
        /// The calling matrix with its elements subtracted with 
        /// the respective elements of <paramref name="_MatB"/>
        /// </returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp SubEqualMat example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp SubEqualMat expected output
         Matrix4x4& operator-=( const Matrix4x4& _MatB );

        /// <summary>Raise to power of <paramref name="_Power"/> each elements the calling matrix.</summary>
        /// <param name="_Power">The power factor.</param>
        /// <returns>
        /// The calling matrix with its elements raised to 
        /// power of <paramref name="_Power"/>
        /// </returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp PowEqual example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp PowEqual expected output
         Matrix4x4& operator^=( const float& _Power );

        /// <summary>Retrieve element with linear index</summary>
        /// <param name="_Index">Linear index of the element.</param>
        /// <returns>Value at the index</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp Access example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp Access expected output
         float operator[]( const Uint32 _Index ) const;

        /// <summary>Retrieve element with linear index</summary>
        /// <param name="_Index">Linear index of the element.</param>
        /// <returns>Value at the index</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp Access example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp Access expected output
         float& operator[]( const Uint32 _Index );

        /// <summary>Retrieve element with linear index</summary>
        /// <param name="_Index">Linear index of the element.</param>
        /// <returns>Value at the index</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp Access example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp Access expected output
         float operator()( const Uint32 _Index ) const;

        /// <summary>Retrieve element with linear index</summary>
        /// <param name="_Index">Linear index of the element.</param>
        /// <returns>Value at the index</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp Access example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp Access expected output
         float& operator()( const Uint32 _Index );

        /// <summary>Retrieve element with row and column indices</summary>
        /// <param name="_Row">Row index of the element.</param>
        /// <param name="_Col">Column index of the element.</param>
        /// <returns>Value at the row and column indices.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp Access example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp Access expected output
         float operator()( const Uint32 _Row, const Uint32 _Col ) const;

        /// <summary>Retrieve element with row and column indices</summary>
        /// <param name="_Row">Row index of the element.</param>
        /// <param name="_Col">Column index of the element.</param>
        /// <returns>Value at the row and column indices.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix4x4/Operators.cpp Access example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix4x4/Operators.cpp Access expected output
         float& operator()( const Uint32 _Row, const Uint32 _Col );

        /// <summary>Retrieve raw data of the matrix.</summary>
        /// <returns>Raw data of the matrix</returns>
         const float* const GetData() const;

        /// <summary>Retrieve raw data of the matrix.</summary>
        /// <returns>Raw data of the matrix</returns>
         float* const GetData();

    public:
        /// <summary> The zero matrix. All values set to 0.
        /// <para>0 0 0 0</para>
        /// <para>0 0 0 0</para>
        /// <para>0 0 0 0</para>
        /// <para>0 0 0 0</para> 
        /// </summary>
        static const Matrix4x4 Zero;
        /// <summary> The identity matrix. All values set to 0 except diagonal.
        /// <para>1 0 0 0</para>
        /// <para>0 1 0 0</para>
        /// <para>0 0 1 0</para>
        /// <para>0 0 0 1</para> 
        /// </summary>
        static const Matrix4x4 Identity;

    private:
        /// <summary>Data of the matrix, linearly stored.</summary>
        float m_Mat[16];
    };




    /// \relatesalso Matrix4x4
    /// <summary>Multiply each element of the matrix <paramref name="_Mat"/> with a scalar value.</summary>
    /// <param name="_Mat">The matrix value to multiply with <paramref name="_Scalar"/>.</param>
    /// <param name="_Scalar">The scalar value to multiply the matrix with.</param>
    /// <returns>Matrix multiplied by the <paramref name="_Scalar"/></returns>
    /// \par Example :
    /// \snippet UnitTestMatrix4x4/Operators.cpp Mul example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix4x4/Operators.cpp Mul expected output
    AERO_CORE_EXPORT Matrix4x4 operator*( const Matrix4x4& _Mat, const float& _Scalar );


    /// \relatesalso Matrix4x4
    /// <summary>Divide each element of the matrix <paramref name="_Mat"/> with a scalar value.</summary>
    /// <param name="_Mat">The matrix value to divide by <paramref name="_Scalar"/>.</param>
    /// <param name="_Scalar">The scalar value to divide the matrix with.</param>
    /// <returns>Matrix divided by the <paramref name="_Scalar"/></returns>
    /// \par Example :
    /// \snippet UnitTestMatrix4x4/Operators.cpp Div example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix4x4/Operators.cpp Div expected output
    AERO_CORE_EXPORT Matrix4x4 operator/( const Matrix4x4& _Mat, const float& _Scalar );


    /// \relatesalso Matrix4x4
    /// <summary>Add each element of the matrix <paramref name="_Mat"/> a scalar value.</summary>
    /// <param name="_Mat">The matrix value to add <paramref name="_Scalar"/>.</param>
    /// <param name="_Scalar">The scalar value to add to the matrix.</param>
    /// <returns>Matrix with <paramref name="_Scalar"/> added to each elements</returns>
    /// \par Example :
    /// \snippet UnitTestMatrix4x4/Operators.cpp Add example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix4x4/Operators.cpp Add expected output
    AERO_CORE_EXPORT Matrix4x4 operator+( const Matrix4x4& _Mat, const float& _Scalar );



    /// \relatesalso Matrix4x4
    /// <summary>Subtract each element of the matrix <paramref name="_Mat"/> a scalar value.</summary>
    /// <param name="_Mat">The matrix value to subtract <paramref name="_Scalar"/>.</param>
    /// <param name="_Scalar">The scalar value to subtract to the matrix.</param>
    /// <returns>Matrix with <paramref name="_Scalar"/> subtracted to each elements</returns>
    /// \par Example :
    /// \snippet UnitTestMatrix4x4/Operators.cpp Sub example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix4x4/Operators.cpp Sub expected output
    AERO_CORE_EXPORT Matrix4x4 operator-( const Matrix4x4& _Mat, const float& _Scalar );


    /// \relatesalso Matrix4x4
    /// <summary>Multiply a matrix with another one.</summary>
    /// <remarks>
    /// Apply : A * B. Where A is <paramref name="_MatA"/> and B is 
    /// <paramref name="_MatB"/>
    /// </remarks>
    /// <param name="_MatA">The matrix to multiply with <paramref name="_MatB"/>.</param>
    /// <param name="_MatB">The matrix to multiply <paramref name="_MatA"/> with.</param>
    /// <returns>The result of the multiplication between <paramref name="_MatA"/> and <paramref name="_MatB"/></returns>
    /// \par Example :
    /// \snippet UnitTestMatrix4x4/Operators.cpp MulMat example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix4x4/Operators.cpp MulMat expected output
    AERO_CORE_EXPORT Matrix4x4 operator*( const Matrix4x4& _MatA, const Matrix4x4& _MatB );


    /// \relatesalso Matrix4x4
    /// <summary>Divide a matrix with another one. (Element by element)</summary>
    /// <param name="_MatA">The matrix to divide with <paramref name="_MatB"/>.</param>
    /// <param name="_MatB">The matrix to divide <paramref name="_MatA"/> with.</param>
    /// <returns>The result of the division of <paramref name="_MatA"/> with <paramref name="_MatB"/></returns>
    /// \par Example :
    /// \snippet UnitTestMatrix4x4/Operators.cpp DivMat example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix4x4/Operators.cpp DivMat expected output
    AERO_CORE_EXPORT Matrix4x4 operator/( const Matrix4x4& _MatA, const Matrix4x4& _MatB );



    /// \relatesalso Matrix4x4
    /// <summary>Add a matrix to another one. (Element by element)</summary>
    /// <param name="_MatA">The matrix to add to <paramref name="_MatB"/>.</param>
    /// <param name="_MatB">The matrix to add to <paramref name="_MatA"/>.</param>
    /// <returns>The result of the addition of <paramref name="_MatA"/> and <paramref name="_MatB"/></returns>
    /// \par Example :
    /// \snippet UnitTestMatrix4x4/Operators.cpp AddMat example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix4x4/Operators.cpp AddMat expected output
    AERO_CORE_EXPORT Matrix4x4 operator+( const Matrix4x4& _MatA, const Matrix4x4& _MatB );


    /// \relatesalso Matrix4x4
    /// <summary>Subtract a matrix to another one. (Element by element)</summary>
    /// <param name="_MatA">The matrix to subtract to <paramref name="_MatB"/>.</param>
    /// <param name="_MatB">The matrix to subtract to <paramref name="_MatA"/>.</param>
    /// <returns>The result of the subtraction of <paramref name="_MatA"/> and <paramref name="_MatB"/></returns>
    /// \par Example :
    /// \snippet UnitTestMatrix4x4/Operators.cpp SubMat example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix4x4/Operators.cpp SubMat expected output
    AERO_CORE_EXPORT Matrix4x4 operator-( const Matrix4x4& _MatA, const Matrix4x4& _MatB );


    /// \relatesalso Matrix4x4
    /// <summary>Raise to power of <paramref name="_Power"/> each elements of <paramref name="_Mat"/>.</summary>
    /// <param name="_Mat">The matrix to raised to power of <paramref name="_Power"/>.</param>
    /// <param name="_Power">The power factor.</param>
    /// <returns>
    /// <paramref name="_Mat"/> with its elements raised to 
    /// power of <paramref name="_Power"/>
    /// </returns>
    /// \par Example :
    /// \snippet UnitTestMatrix4x4/Operators.cpp Pow example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix4x4/Operators.cpp Pow expected output
    AERO_CORE_EXPORT Matrix4x4 operator^( const Matrix4x4& _Mat, const float& _Power );



    /// \relatesalso Matrix4x4
    /// <summary>Test if two matrices are the same.</summary>
    /// <param name="_MatA">First matrix to compare.</param>
    /// <param name="_MatB">Seconde matrix to compare</param>
    /// <returns>
    /// True if <paramref name="_MatA"/> and <paramref name="_MatB"/> have the same values.
    /// False otherwise.
    /// </returns>
    /// \par Example :
    /// \snippet UnitTestMatrix4x4/Operators.cpp Equal example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix4x4/Operators.cpp Equal expected output
    AERO_CORE_EXPORT Bool operator==( const Matrix4x4& _MatA, const Matrix4x4& _MatB );

    /// \relatesalso Matrix4x4
    /// <summary>Test if two matrices are different.</summary>
    /// <param name="_MatA">First matrix to compare.</param>
    /// <param name="_MatB">Seconde matrix to compare</param>
    /// <returns>
    /// True if <paramref name="_MatA"/> and <paramref name="_MatB"/> have NOT the same values.
    /// False otherwise.
    /// </returns>
    /// \par Example :
    /// \snippet UnitTestMatrix4x4/Operators.cpp NotEqual example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix4x4/Operators.cpp NotEqual expected output
    AERO_CORE_EXPORT Bool operator!=( const Matrix4x4& _MatA, const Matrix4x4& _MatB );



    /// <summary>
    /// Convert a matrix 4x4 to a string.
    /// </summary>
    /// <param name="_Color">Matrix 4x4 to convert.</param>
    /// <returns>Matrix 4x4 as a C++ string. ( Format : x x x x\nx x x x\nx x x x\nx x x x ).</returns>
    AERO_CORE_EXPORT  std::string ToString( const Matrix4x4& _Matrix );


} // ae

/// <summary>
/// Convert a matrix 4x4 to a string and push it in the out stream.
/// </summary>
/// <param name="_Color">Matrix 4x4 to convert and push to the out stream.</param>
/// <returns>Out stream.</returns>
AERO_CORE_EXPORT std::ostream& operator<<( std::ostream& os, const ae::Matrix4x4& _Matrix );

#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Vector/Vector2.h"

#include "MatrixToolbox.h"

#include <string>
#include <iostream>
#include <array>

namespace ae
{
    /// \ingroup math   
    /// <summary>Matrix with 3 lines and 3 columns.</summary>
    /// <seealso cref="Matrix4x4"/>
    class AERO_CORE_EXPORT Matrix3x3
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
            R0C0 = 0, R0C1 = 1, R0C2 = 2,
            R1C0 = 3, R1C1 = 4, R1C2 = 5,
            R2C0 = 6, R2C1 = 7, R2C2 = 8,
        };

    public:
        /// <summary>Create an matrix with default elements constructor.</summary>
        /// <param name="_InitMode">Determine how to fill the value.</param>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Constructors.cpp Constructor Init example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Constructors.cpp Constructor Init expected output
        explicit Matrix3x3( MatrixInitMode _InitMode = MatrixInitMode::Default );


        /// <summary>Create an matrix with given elements.</summary>
        /// <param name="_Elements">Elements to fill the new matrix with.</param>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Constructors.cpp Constructor Elements example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Constructors.cpp Constructor Elements expected output
        Matrix3x3( const std::initializer_list<float>& _Elements );


        /// <summary>Create an matrix with given elements.</summary>
        /// <param name="_Elements">2D list to fill the new matrix with.</param>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Constructors.cpp Constructor Elements2D example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Constructors.cpp Constructor Elements2D expected output
        Matrix3x3( const std::initializer_list<std::initializer_list<float>>& _Elements );

        /// <summary>Create an matrix and copy the element from the other matrix. </summary>
        /// <param name="_Copy">Matrix to copy the elements from.</param>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Constructors.cpp Constructor Copy example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Constructors.cpp Constructor Copy expected output
        Matrix3x3( const Matrix3x3& _Copy );


        /// <summary>Copy operator</summary>
        /// <param name="_Copy">Matrix to copy the elements from.</param>
        /// <returns>Matrix with the elements copied.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp CopyOperator example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp CopyOperator expected output
        Matrix3x3& operator=( const Matrix3x3& _Copy );


        /// <summary>
        /// Negation operator.
        /// Will multiply with -1 each value of the matrix.
        /// </summary>
        /// <returns>The calling matrix negated (not the calling matrix, a copy negated).</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp NegativeOperator example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp NegativeOperator expected output
        Matrix3x3 operator-() const;


        /// <summary>
        /// Sets to identity the matrix.
        /// The diagonal will be set to 1.0f and other values to 0.0f.
        /// </summary>
        /// <returns>The calling matrix set to identity.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp SetToIdentity example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp SetToIdentity expected output
        Matrix3x3& SetToIdentity();

        /// <summary>
        /// Sets to zero the matrix.
        /// Every values will be set to 0.0f.
        /// </summary>
        /// <returns>The calling matrix filled with zeros.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp SetToZero example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp SetToZero expected output
        Matrix3x3& SetToZero();


        /// <summary>Get the direction in front of the current transformation.</summary>
        /// <returns>Forward direction of the transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp GetForward example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp GetForward expected output
        Vector2 GetForward() const;

        /// <summary>Get the direction above the current transformation.</summary>
        /// <returns>Upward direction of the transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp GetUp example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp GetUp expected output
        Vector2 GetUp() const;


        /// <summary>Get the direction (normalized) in front of the current transformation.</summary>
        /// <returns>Forward direction of the transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp GetForwardUnit example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp GetForwardUnit expected output
        Vector2 GetForwardUnit() const;

        /// <summary>Get the direction (normalized) above the current transformation.</summary>
        /// <returns>Upward direction of the transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp GetUpUnit example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp GetUpUnit expected output
        Vector2 GetUpUnit() const;


        /// <summary>
        /// Rotate the matrix in 2D.
        /// Add the new rotation to the old one.
        /// </summary>
        /// <param name="_Angle">The angle in radians.</param>
        /// <returns>The calling matrix rotated.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp Rotate example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp Rotate expected output
        Matrix3x3& Rotate( const float _Angle );


        /// <summary>
        /// Rotate the matrix in 2D.
        /// Override the old roration.
        /// </summary>
        /// <param name="_Angle">The new angle in radians.</param>
        /// <returns>The calling matrix with the new rotation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp SetRotation example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp SetRotation expected output
        Matrix3x3& SetRotation( const float _Angle );



        /// <summary>
        /// Scale the matrix.
        /// Multiply the new scale with the old one.
        /// </summary>
        /// <param name="_Scale">The scale factor.</param>
        /// <returns>The calling matrix scaled.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp Scale example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp Scale expected output
        Matrix3x3& Scale( const Vector2& _Scale );

        /// <summary>
        /// Scale the matrix.
        /// Override the old scale.
        /// </summary>
        /// <param name="_Scale">The new scale.</param>
        /// <returns>The calling matrix with the new scale.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp SetScale example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp SetScale expected output
        Matrix3x3& SetScale( const Vector2& _Scale );


        /// <summary>
        /// Translate the matrix.
        /// Add the new translation to the old one.
        /// </summary>
        /// <param name="_Vector">The offset to apply.</param>
        /// <returns>The calling matrix translated.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp Translate example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp Translate expected output
        Matrix3x3& Translate( const Vector2& _Vector );

        /// <summary>
        /// Translate the matrix.
        /// </summary>
        /// <param name="_Vector">The new offset.</param>
        /// <returns>The calling matrix with the new translation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp SetTranslation example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp SetTranslation expected output
        Matrix3x3& SetTranslation( const Vector2& _Vector );


        /// <summary>
        /// Get the determinant of the matrix.
        /// </summary>
        /// <returns>The determinant of the matrix.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp GetDeterminant example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp GetDeterminant expected output
        float GetDeterminant() const;


        /// <summary>
        /// Inverse the matrix.
        /// Can fail due to Determinant = 0.
        /// </summary>
        /// <returns>The calling matrix inversed if success, matrix unchanged otherwise.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp Inverse example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp Inverse expected output
        Matrix3x3& Inverse();

        /// <summary>
        /// Get the inverse of the calling matrix.
        /// Can fail due to Determinant = 0.
        /// </summary>
        /// <returns>The matrix inversed, if it fail, return the matrix unchanged.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp GetInverse example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp GetInverse expected output
        Matrix3x3 GetInverse() const;

        /// <summary>
        /// Switch the last column with the last line of the matrix.
        /// </summary>
        /// <returns>The calling matrix with the translation moved.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp SwitchVectorPosition example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp SwitchVectorPosition expected output
        Matrix3x3&  SwitchVectorPosition();


        /// <summary>
        /// Copy the point, transform then return the copy.
        /// </summary>
        /// <param name="_Point">The point to transform.</param>
        /// <returns>The transformed point.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp GetTransformedPoint example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp GetTransformedPoint expected output
        Vector2 GetTransformedPoint( const Vector2& _Point ) const;


        /// <summary>
        /// Transforms the point.
        /// </summary>
        /// <param name="_Point">The point to transform.</param>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp TransformPoint example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp TransformPoint expected output
        void TransformPoint( AE_InOut Vector2& _Point ) const;


        /// <summary>
        /// Do a matrix with the scale transformation.
        /// </summary>
        /// <param name="_Scale">The scale factor on each axis.</param>
        /// <returns>The matrix containing the scale transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp GetScaleMatrix example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp GetScaleMatrix expected output
        static Matrix3x3 GetScaleMatrix( const Vector2& _Scale );

        /// <summary>
        /// Do a matrix with the rotation transformation.
        /// </summary>
        /// <param name="_Angle">The angle in radians.</param>
        /// <returns>The matrix containing the rotation transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp GetRotationMatrix example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp GetRotationMatrix expected output
        static Matrix3x3 GetRotationMatrix( const float _Angle );

        /// <summary>
        /// Do a matrix with the translation transformation.
        /// </summary>
        /// <param name="_Vector">The translation to apply.</param>
        /// <returns>The matrix containing the translation transformation.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp GetTranslationMatrix example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp GetTranslationMatrix expected output
        static Matrix3x3 GetTranslationMatrix( const Vector2& _Vector );



        /// <summary>Tranpose the matrix.</summary>
        /// <returns>Matrix transposed.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp Transpose example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp Transpose expected output
        Matrix3x3& Transpose();

        /// <summary>Retrieve the transpose of the calling matrix (without modifying it).</summary>
        /// <returns>The calling matrix transposed.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp GetTranspose example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp GetTranspose expected output
        Matrix3x3 GetTranspose() const;


        /// <summary>Apply absolute value to each element of the matrix.</summary>
        /// <returns>Matrix with all element as absolute value.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp Abs example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp Abs expected output
        Matrix3x3& Abs();


        /// <summary>Copy the matrix then apply absolute value to each element of the copy.</summary>
        /// <returns>Copy of the matrix with all element as absolute value.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp GetAbs example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp GetAbs expected output
        Matrix3x3 GetAbs() const;

        /// <summary>Process the sum of all diagonal elements.</summary>
        /// <returns>Sum of diagonal elements.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Functionalities.cpp GetTrace example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Functionalities.cpp GetTrace expected output
        float GetTrace() const;




        /// <summary>Multiply each element of the matrix with a scalar value.</summary>
        /// <param name="_Scalar">The scalar value to multiply the matrix with.</param>
        /// <returns>Matrix multiplied by the <paramref name="_Scalar"/></returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp MulEqual example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp MulEqual expected output
        Matrix3x3& operator*=( const float& _Scalar );


        /// <summary>Divide each element of the matrix with a scalar value.</summary>
        /// <param name="_Scalar">The scalar value to divide the matrix with.</param>
        /// <returns>Matrix divided by the <paramref name="_Scalar"/>.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp DivEqual example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp DivEqual expected output
        Matrix3x3& operator/=( const float& _Scalar );


        /// <summary>Add to each element of the matrix a scalar value.</summary>
        /// <param name="_Scalar">The scalar value to add to the matrix with.</param>
        /// <returns>Matrix with the <paramref name="_Scalar"/> added to each elements.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp AddEqual example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp AddEqual expected output
        Matrix3x3& operator+=( const float& _Scalar );


        /// <summary>Subtract to each element of the matrix a scalar value.</summary>
        /// <param name="_Scalar">The scalar value to add to the matrix with.</param>
        /// <returns>Matrix with the <paramref name="_Scalar"/> subtracted to each elements.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp SubEqual example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp SubEqual expected output
        Matrix3x3& operator-=( const float& _Scalar );


        /// <summary>Multuply a matrix with another one.</summary>
        /// <remarks>
        /// Apply : A * B. Where A is the calling matrix and B is 
        /// <paramref name="_MatB"/>
        /// </remarks>
        /// <param name="_MatB">The second matrix to multiply the calling one with.</param>
        /// <returns>The calling matrix multiplied by <paramref name="_MatB"/></returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp MulEqualMat example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp MulEqualMat expected output
        Matrix3x3& operator*=( const Matrix3x3& _MatB );


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
        /// \snippet UnitTestMatrix3x3/Operators.cpp DivEqualMat example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp DivEqualMat expected output
        Matrix3x3& operator/=( const Matrix3x3& _MatB );


        /// <summary>Add each elemens the calling matrix with the respective elements of another one.</summary>
        /// <param name="_MatB">The second matrix to add the calling one with.</param>
        /// <returns>
        /// The calling matrix with its elements added with 
        /// the respective elements of <paramref name="_MatB"/>
        /// </returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp AddEqualMat example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp AddEqualMat expected output
        Matrix3x3& operator+=( const Matrix3x3& _MatB );


        /// <summary>Subtract each elemens the calling matrix with the respective elements of another one.</summary>
        /// <param name="_MatB">The second matrix to subtract the calling one with.</param>
        /// <returns>
        /// The calling matrix with its elements subtracted with 
        /// the respective elements of <paramref name="_MatB"/>
        /// </returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp SubEqualMat example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp SubEqualMat expected output
        Matrix3x3& operator-=( const Matrix3x3& _MatB );

        /// <summary>Raise to power of <paramref name="_Power"/> each elements the calling matrix.</summary>
        /// <param name="_Power">The power factor.</param>
        /// <returns>
        /// The calling matrix with its elements raised to 
        /// power of <paramref name="_Power"/>
        /// </returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp PowEqual example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp PowEqual expected output
        Matrix3x3& operator^=( const float& _Power );


        /// <summary>Retrieve element with linear index</summary>
        /// <param name="_Index">Linear index of the element.</param>
        /// <returns>Value at the index</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp Access example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp Access expected output
        float operator[]( const Uint32 _Index ) const;

        /// <summary>Retrieve element with linear index</summary>
        /// <param name="_Index">Linear index of the element.</param>
        /// <returns>Value at the index</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp Access example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp Access expected output
        float& operator[]( const Uint32 _Index );

        /// <summary>Retrieve element with linear index</summary>
        /// <param name="_Index">Linear index of the element.</param>
        /// <returns>Value at the index</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp Access example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp Access expected output
        float operator()( const Uint32 _Index ) const;

        /// <summary>Retrieve element with linear index</summary>
        /// <param name="_Index">Linear index of the element.</param>
        /// <returns>Value at the index</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp Access example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp Access expected output
        float& operator()( const Uint32 _Index );

        /// <summary>Retrieve element with row and column indices</summary>
        /// <param name="_Row">Row index of the element.</param>
        /// <param name="_Col">Column index of the element.</param>
        /// <returns>Value at the row and column indices.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp Access example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp Access expected output
        float operator()( const Uint32 _Row, const Uint32 _Col ) const;

        /// <summary>Retrieve element with row and column indices</summary>
        /// <param name="_Row">Row index of the element.</param>
        /// <param name="_Col">Column index of the element.</param>
        /// <returns>Value at the row and column indices.</returns>
        /// \par Example :
        /// \snippet UnitTestMatrix3x3/Operators.cpp Access example
        /// \par Expected Output :
        /// \snippetdoc UnitTestMatrix3x3/Operators.cpp Access expected output
        float& operator()( const Uint32 _Row, const Uint32 _Col );

        /// <summary>Retrieve raw data of the matrix.</summary>
        /// <returns>Raw data of the matrix</returns>
        const float* const GetData() const;

        /// <summary>Retrieve raw data of the matrix.</summary>
        /// <returns>Raw data of the matrix</returns>
        float* const GetData();

    public:
        /// <summary> The zero matrix. All values set to 0.
        /// <para>0 0 0</para>
        /// <para>0 0 0</para>
        /// <para>0 0 0</para>
        /// </summary>
        static const Matrix3x3 Zero;
        /// <summary> The identity matrix. All values set to 0 except diagonal.
        /// <para>1 0 0</para>
        /// <para>0 1 0</para>
        /// <para>0 0 1</para>
        /// </summary>
        static const Matrix3x3 Identity;

    private:
        /// <summary>Data of the matrix, linearly stored.</summary>
        float m_Mat[9];
    };





    /// \relatesalso Matrix3x3
    /// <summary>Multiply each element of the matrix <paramref name="_Mat"/> with a scalar value.</summary>
    /// <param name="_Mat">The matrix value to multiply with <paramref name="_Scalar"/>.</param>
    /// <param name="_Scalar">The scalar value to multiply the matrix with.</param>
    /// <returns>Matrix multiplied by the <paramref name="_Scalar"/></returns>
    /// \par Example :
    /// \snippet UnitTestMatrix3x3/Operators.cpp Mul example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix3x3/Operators.cpp Mul expected output
    AERO_CORE_EXPORT Matrix3x3 operator*( const Matrix3x3& _Mat, const float& _Scalar );


    /// \relatesalso Matrix3x3
    /// <summary>Divide each element of the matrix <paramref name="_Mat"/> with a scalar value.</summary>
    /// <param name="_Mat">The matrix value to divide by <paramref name="_Scalar"/>.</param>
    /// <param name="_Scalar">The scalar value to divide the matrix with.</param>
    /// <returns>Matrix divided by the <paramref name="_Scalar"/></returns>
    /// \par Example :
    /// \snippet UnitTestMatrix3x3/Operators.cpp Div example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix3x3/Operators.cpp Div expected output
    AERO_CORE_EXPORT Matrix3x3 operator/( const Matrix3x3& _Mat, const float& _Scalar );


    /// \relatesalso Matrix3x3
    /// <summary>Add each element of the matrix <paramref name="_Mat"/> a scalar value.</summary>
    /// <param name="_Mat">The matrix value to add <paramref name="_Scalar"/>.</param>
    /// <param name="_Scalar">The scalar value to add to the matrix.</param>
    /// <returns>Matrix with <paramref name="_Scalar"/> added to each elements</returns>
    /// \par Example :
    /// \snippet UnitTestMatrix3x3/Operators.cpp Add example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix3x3/Operators.cpp Add expected output
    AERO_CORE_EXPORT Matrix3x3 operator+( const Matrix3x3& _Mat, const float& _Scalar );



    /// \relatesalso Matrix3x3
    /// <summary>Subtract each element of the matrix <paramref name="_Mat"/> a scalar value.</summary>
    /// <param name="_Mat">The matrix value to subtract <paramref name="_Scalar"/>.</param>
    /// <param name="_Scalar">The scalar value to subtract to the matrix.</param>
    /// <returns>Matrix with <paramref name="_Scalar"/> subtracted to each elements</returns>
    /// \par Example :
    /// \snippet UnitTestMatrix3x3/Operators.cpp Sub example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix3x3/Operators.cpp Sub expected output
    AERO_CORE_EXPORT Matrix3x3 operator-( const Matrix3x3& _Mat, const float& _Scalar );


    /// \relatesalso Matrix3x3
    /// <summary>Multiply a matrix with another one.</summary>
    /// <remarks>
    /// Apply : A * B. Where A is <paramref name="_MatA"/> and B is 
    /// <paramref name="_MatB"/>
    /// </remarks>
    /// <param name="_MatA">The matrix to multiply with <paramref name="_MatB"/>.</param>
    /// <param name="_MatB">The matrix to multiply <paramref name="_MatA"/> with.</param>
    /// <returns>The result of the multiplication between <paramref name="_MatA"/> and <paramref name="_MatB"/></returns>
    /// \par Example :
    /// \snippet UnitTestMatrix3x3/Operators.cpp MulMat example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix3x3/Operators.cpp MulMat expected output
    AERO_CORE_EXPORT Matrix3x3 operator*( const Matrix3x3& _MatA, const Matrix3x3& _MatB );


    /// \relatesalso Matrix3x3
    /// <summary>Divide a matrix with another one. (Element by element)</summary>
    /// <param name="_MatA">The matrix to divide with <paramref name="_MatB"/>.</param>
    /// <param name="_MatB">The matrix to divide <paramref name="_MatA"/> with.</param>
    /// <returns>The result of the division of <paramref name="_MatA"/> with <paramref name="_MatB"/></returns>
    /// \par Example :
    /// \snippet UnitTestMatrix3x3/Operators.cpp DivMat example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix3x3/Operators.cpp DivMat expected output
    AERO_CORE_EXPORT Matrix3x3 operator/( const Matrix3x3& _MatA, const Matrix3x3& _MatB );



    /// \relatesalso Matrix3x3
    /// <summary>Add a matrix to another one. (Element by element)</summary>
    /// <param name="_MatA">The matrix to add to <paramref name="_MatB"/>.</param>
    /// <param name="_MatB">The matrix to add to <paramref name="_MatA"/>.</param>
    /// <returns>The result of the addition of <paramref name="_MatA"/> and <paramref name="_MatB"/></returns>
    /// \par Example :
    /// \snippet UnitTestMatrix3x3/Operators.cpp AddMat example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix3x3/Operators.cpp AddMat expected output
    AERO_CORE_EXPORT Matrix3x3 operator+( const Matrix3x3& _MatA, const Matrix3x3& _MatB );


    /// \relatesalso Matrix3x3
    /// <summary>Subtract a matrix to another one. (Element by element)</summary>
    /// <param name="_MatA">The matrix to subtract to <paramref name="_MatB"/>.</param>
    /// <param name="_MatB">The matrix to subtract to <paramref name="_MatA"/>.</param>
    /// <returns>The result of the subtraction of <paramref name="_MatA"/> and <paramref name="_MatB"/></returns>
    /// \par Example :
    /// \snippet UnitTestMatrix3x3/Operators.cpp SubMat example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix3x3/Operators.cpp SubMat expected output
    AERO_CORE_EXPORT Matrix3x3 operator-( const Matrix3x3& _MatA, const Matrix3x3& _MatB );


    /// \relatesalso Matrix3x3
    /// <summary>Raise to power of <paramref name="_Power"/> each elements of <paramref name="_Mat"/>.</summary>
    /// <param name="_Mat">The matrix to raised to power of <paramref name="_Power"/>.</param>
    /// <param name="_Power">The power factor.</param>
    /// <returns>
    /// <paramref name="_Mat"/> with its elements raised to 
    /// power of <paramref name="_Power"/>
    /// </returns>
    /// \par Example :
    /// \snippet UnitTestMatrix3x3/Operators.cpp Pow example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix3x3/Operators.cpp Pow expected output
    AERO_CORE_EXPORT Matrix3x3 operator^( const Matrix3x3& _Mat, const float& _Power );


    /// \relatesalso Matrix3x3
    /// <summary>Test if two matrices are the same.</summary>
    /// <param name="_MatA">First matrix to compare.</param>
    /// <param name="_MatB">Seconde matrix to compare</param>
    /// <returns>
    /// True if <paramref name="_MatA"/> and <paramref name="_MatB"/> have the same values.
    /// False otherwise.
    /// </returns>
    /// \par Example :
    /// \snippet UnitTestMatrix3x3/Operators.cpp Equal example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix3x3/Operators.cpp Equal expected output
    AERO_CORE_EXPORT Bool operator==( const Matrix3x3& _MatA, const Matrix3x3& _MatB );

    /// \relatesalso Matrix3x3
    /// <summary>Test if two matrices are different.</summary>
    /// <param name="_MatA">First matrix to compare.</param>
    /// <param name="_MatB">Seconde matrix to compare</param>
    /// <returns>
    /// True if <paramref name="_MatA"/> and <paramref name="_MatB"/> have NOT the same values.
    /// False otherwise.
    /// </returns>
    /// \par Example :
    /// \snippet UnitTestMatrix3x3/Operators.cpp NotEqual example
    /// \par Expected Output :
    /// \snippetdoc UnitTestMatrix3x3/Operators.cpp NotEqual expected output
    AERO_CORE_EXPORT Bool operator!=( const Matrix3x3& _MatA, const Matrix3x3& _MatB );



    /// <summary>
    /// Convert a matrix 3x3 to a string.
    /// </summary>
    /// <param name="_Color">Matrix 3x3 to convert.</param>
    /// <returns>Matrix 3x3 as a C++ string. ( Format :  x x x\nx x x\nx x x ).</returns>
    AERO_CORE_EXPORT  std::string ToString( const Matrix3x3& _Matrix );

} // ae

/// <summary>
/// Convert a matrix 3x3 to a string and push it in the out stream.
/// </summary>
/// <param name="_Color">Matrix 3x3 to convert and push to the out stream.</param>
/// <returns>Out stream.</returns>
AERO_CORE_EXPORT std::ostream& operator<<( std::ostream& os, const ae::Matrix3x3& _Matrix );




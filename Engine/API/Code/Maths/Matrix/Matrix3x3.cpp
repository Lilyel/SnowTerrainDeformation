#include "Matrix3x3.h"

#include "../Functions/MathsFunctions.h"
#include "../../Debugging/Log/Log.h"

namespace ae
{
    const Matrix3x3 Matrix3x3::Zero =
    {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    const Matrix3x3 Matrix3x3::Identity =
    {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    Matrix3x3::Matrix3x3( MatrixInitMode _InitMode )
    {
        priv::MatrixToolbox::Init( m_Mat, 3, 3, _InitMode );
    }

    Matrix3x3::Matrix3x3( const std::initializer_list<float>& _Elements )
    {
        size_t i = 0;
        for( float element : _Elements )
        {
            if( i >= 9 )
                break;

            m_Mat[i] = element;
            i++;
        }
    }

    Matrix3x3::Matrix3x3( const std::initializer_list<std::initializer_list<float>>& _Elements )
    {
        size_t iRow = 0;
        for( const std::initializer_list<float>& Row : _Elements )
        {
            if( iRow >= 3 )
                break;

            size_t iCol = 0;
            for( float element : Row )
            {
                if( iCol >= 3 )
                    break;

                m_Mat[iRow * 3 + iCol] = element;
                iCol++;
            }

            iRow++;
        }
    }

    Matrix3x3::Matrix3x3( const Matrix3x3& _Copy )
    {
        std::memcpy( m_Mat, _Copy.m_Mat, 9 * sizeof( float ) );
    }

     Matrix3x3& Matrix3x3::operator=( const Matrix3x3& _Copy )
    {
         std::memcpy( m_Mat, _Copy.m_Mat, 9 * sizeof( float ) );

        return *this;
    }


    inline Matrix3x3 Matrix3x3::operator-() const
    {
        return
        {
            -m_Mat[R0C0], -m_Mat[R0C1], -m_Mat[R0C2],
            -m_Mat[R1C0], -m_Mat[R1C1], -m_Mat[R1C2],
            -m_Mat[R2C0], -m_Mat[R2C1], -m_Mat[R2C2]
        };
    }

    Matrix3x3& Matrix3x3::SetToIdentity()
    {
        std::memcpy( m_Mat, Identity.m_Mat, 9 * sizeof( float ) );

        return *this;
    }

    Matrix3x3& Matrix3x3::SetToZero()
    {
        memset( m_Mat, 0, 9 * sizeof( float ) );

        return *this;
    }



    Vector2 Matrix3x3::GetForward() const
    {
        return Vector2( m_Mat[R0C0], m_Mat[R1C0] );
    }

    Vector2 Matrix3x3::GetUp() const
    {
        return Vector2( m_Mat[R0C1], m_Mat[R1C1] );
    }

    Vector2 Matrix3x3::GetForwardUnit() const
    {
        return GetForward().Normalize();
    }

    Vector2 Matrix3x3::GetUpUnit() const
    {
        return GetUp().Normalize();
    }



    Matrix3x3& Matrix3x3::Rotate( const float _Angle )
    {
        Matrix3x3 Rotation( MatrixInitMode::Identity );
        Rotation.SetRotation( _Angle );

        *this *= Rotation;

        return *this;
    }

    Matrix3x3& Matrix3x3::SetRotation( const float _Angle )
    {
        const float SinAngle = Math::Sin( _Angle );
        const float CosAngle = Math::Cos( _Angle );

        m_Mat[R0C0] = CosAngle;
        m_Mat[R0C1] = -SinAngle;
        m_Mat[R1C0] = SinAngle;
        m_Mat[R1C1] = CosAngle;

        return *this;
    }

    Matrix3x3& Matrix3x3::Scale( const Vector2& _Scale )
    {
        Matrix3x3 Scaling( MatrixInitMode::Identity );
        Scaling.SetScale( _Scale );

        *this *= Scaling;

        return *this;
    }

    Matrix3x3& Matrix3x3::SetScale( const Vector2& _Scale )
    {
        m_Mat[R0C0] = _Scale.X;
        m_Mat[R1C1] = _Scale.Y;

        return *this;
    }

    Matrix3x3& Matrix3x3::Translate( const Vector2& _Vector )
    {
        m_Mat[R0C2] += _Vector.X;
        m_Mat[R1C2] += _Vector.Y;

        return *this;
    }

    Matrix3x3& Matrix3x3::SetTranslation( const Vector2& _Vector )
    {
        m_Mat[R0C2] = _Vector.X;
        m_Mat[R1C2] = _Vector.Y;

        return *this;
    }

    float Matrix3x3::GetDeterminant() const
    {
        float C1, C2, C3, C4, C5, C6;

        C1 = m_Mat[R0C0] * m_Mat[R1C1] * m_Mat[R2C2];
        C2 = m_Mat[R1C0] * m_Mat[R2C1] * m_Mat[R0C2];
        C3 = m_Mat[R2C0] * m_Mat[R0C1] * m_Mat[R1C2];
        C4 = m_Mat[R0C0] * m_Mat[R2C1] * m_Mat[R1C2];
        C5 = m_Mat[R2C0] * m_Mat[R1C1] * m_Mat[R0C2];
        C6 = m_Mat[R1C0] * m_Mat[R0C1] * m_Mat[R2C2];

        return ( C1 + C2 + C3 - C4 - C5 - C6 );
    }

    Matrix3x3& Matrix3x3::Inverse()
    {
        const float Determinant = GetDeterminant();

        if( Determinant == 0.0f )
        {
            AE_LogError( "Can't inverse the matrix, derterminant is equal to 0." );
            return *this;
        }

        const float InvDeterminant = 1.0f / Determinant;

        float C11 = m_Mat[R1C1] * m_Mat[R2C2] - m_Mat[R1C2] * m_Mat[R2C1];

        float C12 = m_Mat[R0C2] * m_Mat[R2C1] - m_Mat[R0C1] * m_Mat[R2C2];

        float C13 = m_Mat[R0C1] * m_Mat[R1C2] - m_Mat[R0C2] * m_Mat[R1C1];


        float C21 = m_Mat[R1C2] * m_Mat[R2C0] - m_Mat[R1C0] * m_Mat[R2C2];

        float C22 = m_Mat[R0C0] * m_Mat[R2C2] - m_Mat[R0C2] * m_Mat[R2C0];

        float C23 = m_Mat[R0C2] * m_Mat[R1C0] - m_Mat[R0C0] * m_Mat[R1C2];


        float C31 = m_Mat[R1C0] * m_Mat[R2C1] - m_Mat[R1C1] * m_Mat[R2C0];

        float C32 = m_Mat[R0C1] * m_Mat[R2C0] - m_Mat[R0C0] * m_Mat[R2C1];

        float C33 = m_Mat[R0C0] * m_Mat[R1C1] - m_Mat[R0C1] * m_Mat[R1C0];

        m_Mat[R0C0] = C11 * InvDeterminant;
        m_Mat[R0C1] = C12 * InvDeterminant;
        m_Mat[R0C2] = C13 * InvDeterminant;

        m_Mat[R1C0] = C21 * InvDeterminant;
        m_Mat[R1C1] = C22 * InvDeterminant;
        m_Mat[R1C2] = C23 * InvDeterminant;

        m_Mat[R2C0] = C31 * InvDeterminant;
        m_Mat[R2C1] = C32 * InvDeterminant;
        m_Mat[R2C2] = C33 * InvDeterminant;

        return *this;
    }

    Matrix3x3 Matrix3x3::GetInverse() const
    {
        Matrix3x3 Result = *this;

        return Result.Inverse();
    }

    Matrix3x3& Matrix3x3::SwitchVectorPosition()
    {
        std::swap( m_Mat[R0C2], m_Mat[R2C0] );
        std::swap( m_Mat[R1C2], m_Mat[R2C1] );

        return *this;
    }

    Vector2 Matrix3x3::GetTransformedPoint( const Vector2& _Point ) const
    {
        Vector2 Result;

        Result.X = _Point.X * m_Mat[R0C0] + _Point.Y * m_Mat[R0C1] + m_Mat[R0C2];
        Result.Y = _Point.X * m_Mat[R1C0] + _Point.Y * m_Mat[R1C1] + m_Mat[R1C2];

        return Result;
    }

    void Matrix3x3::TransformPoint( AE_InOut Vector2& _Point ) const
    {
        Vector2 Copy( _Point );

        _Point.X = Copy.X * m_Mat[R0C0] + Copy.Y * m_Mat[R0C1] + m_Mat[R0C2];
        _Point.Y = Copy.X * m_Mat[R1C0] + Copy.Y * m_Mat[R1C1] + m_Mat[R1C2];
    }

    Matrix3x3 Matrix3x3::GetScaleMatrix( const Vector2& _Scale )
    {
        Matrix3x3 Result( MatrixInitMode::Identity );
        Result.SetScale( _Scale );

        return Result;
    }

    Matrix3x3 Matrix3x3::GetRotationMatrix( const float _Angle )
    {
        Matrix3x3 Result( MatrixInitMode::Identity );
        Result.SetRotation( _Angle );

        return Result;
    }

    Matrix3x3 Matrix3x3::GetTranslationMatrix( const Vector2& _Vector )
    {
        Matrix3x3 Result( MatrixInitMode::Identity );
        Result.SetTranslation( _Vector );

        return Result;
    }




    inline Matrix3x3& Matrix3x3::Transpose()
    {
        std::swap( m_Mat[R1C0], m_Mat[R0C1] );
        std::swap( m_Mat[R2C0], m_Mat[R0C2] );
        std::swap( m_Mat[R2C1], m_Mat[R1C2] );

        return *this;
    }

    Matrix3x3 Matrix3x3::GetTranspose() const
    {
        Matrix3x3 Result = *this;

        return Result.Transpose();
    }


    Matrix3x3& Matrix3x3::Abs()
    {
        priv::MatrixToolbox::Abs( m_Mat, m_Mat, 3, 3 );

        return *this;
    }


    Matrix3x3 Matrix3x3::GetAbs() const
    {
        Matrix3x3 Result;

        priv::MatrixToolbox::Abs( Result.m_Mat, m_Mat, 3, 3 );

        return Result;
    }

    float Matrix3x3::GetTrace() const
    {
        return m_Mat[R0C0] + m_Mat[R1C1] + m_Mat[R2C2];
    }





    Matrix3x3& Matrix3x3::operator*=( const float& _Scalar )
    {
        priv::MatrixToolbox::Multiply( m_Mat, m_Mat, _Scalar, 3, 3 );

        return *this;
    }


    Matrix3x3& Matrix3x3::operator/=( const float& _Scalar )
    {
        priv::MatrixToolbox::Divide( m_Mat, m_Mat, _Scalar, 3, 3 );

        return *this;
    }


    inline Matrix3x3& Matrix3x3::operator+=( const float& _Scalar )
    {
        priv::MatrixToolbox::Add( m_Mat, m_Mat, _Scalar, 3, 3 );

        return *this;
    }


    Matrix3x3& Matrix3x3::operator-=( const float& _Scalar )
    {
        priv::MatrixToolbox::Subtract( m_Mat, m_Mat, _Scalar, 3, 3 );

        return *this;
    }


    Matrix3x3& Matrix3x3::operator*=( const Matrix3x3& _MatB )
    {
        Matrix3x3 Result;

        priv::MatrixToolbox::Multiply( Result.m_Mat, m_Mat, 3, 3, _MatB.m_Mat, 3 );

        *this = Result;

        return *this;
    }



    Matrix3x3& Matrix3x3::operator/=( const Matrix3x3& _MatB )
    {
        priv::MatrixToolbox::Divide( m_Mat, m_Mat, 3, 3, _MatB.m_Mat );

        return *this;
    }



    Matrix3x3& Matrix3x3::operator+=( const Matrix3x3& _MatB )
    {
        priv::MatrixToolbox::Add( m_Mat, m_Mat, 3, 3, _MatB.m_Mat );

        return *this;
    }


    Matrix3x3& Matrix3x3::operator-=( const Matrix3x3& _MatB )
    {
        priv::MatrixToolbox::Subtract( m_Mat, m_Mat, 3, 3, _MatB.m_Mat );

        return *this;
    }



    Matrix3x3& Matrix3x3::operator^=( const float& _Power )
    {
        priv::MatrixToolbox::Pow( m_Mat, m_Mat, _Power, 3, 3 );

        return *this;
    }


    float Matrix3x3::operator[]( const Uint32 _Index ) const
    {
        if( _Index < 0 || _Index >= 9 )
            throw std::out_of_range( "Invalid index" );

        return m_Mat[_Index];
    }



    float& Matrix3x3::operator[]( const Uint32 _Index )
    {
        if( _Index < 0 || _Index >= 9 )
            throw std::out_of_range( "Invalid index" );

        return m_Mat[_Index];
    }


    float Matrix3x3::operator()( const Uint32 _Index ) const
    {
        if( _Index < 0 || _Index >= 9 )
            throw std::out_of_range( "Invalid index" );

        return m_Mat[_Index];
    }



    float& Matrix3x3::operator()( const Uint32 _Index )
    {
        if( _Index < 0 || _Index >= 9 )
            throw std::out_of_range( "Invalid index" );

        return m_Mat[_Index];
    }


    float Matrix3x3::operator()( const Uint32 _Row, const Uint32 _Col ) const
    {
        if( _Row < 0 || _Row >= 3 )
            throw std::out_of_range( "Invalid row" );

        if( _Col < 0 || _Col >= 3 )
            throw std::out_of_range( "Invalid column" );

        return m_Mat[_Row * 3 + _Col];
    }


    float& Matrix3x3::operator()( const Uint32 _Row, const Uint32 _Col )
    {
        if( _Row < 0 || _Row >= 3 )
            throw std::out_of_range( "Invalid row" );

        if( _Col < 0 || _Col >= 3 )
            throw std::out_of_range( "Invalid column" );

        return m_Mat[_Row * 3 + _Col];
    }

    const float* const Matrix3x3::GetData() const
    {
        return m_Mat;
    }

    float* const Matrix3x3::GetData()
    {
        return m_Mat;
    }



    Matrix3x3 operator*( const Matrix3x3& _Mat, const float& _Scalar )
    {
        Matrix3x3 Result;

        priv::MatrixToolbox::Multiply( Result.GetData(), _Mat.GetData(), _Scalar, 3, 3 );

        return Result;
    }


    Matrix3x3 operator/( const Matrix3x3& _Mat, const float& _Scalar )
    {
        Matrix3x3 Result;

        priv::MatrixToolbox::Divide( Result.GetData(), _Mat.GetData(), _Scalar, 3, 3 );

        return Result;
    }


    Matrix3x3 operator+( const Matrix3x3& _Mat, const float& _Scalar )
    {
        Matrix3x3 Result;

        priv::MatrixToolbox::Add( Result.GetData(), _Mat.GetData(), _Scalar, 3, 3 );

        return Result;
    }


    Matrix3x3 operator-( const Matrix3x3& _Mat, const float& _Scalar )
    {
        Matrix3x3 Result;

        priv::MatrixToolbox::Subtract( Result.GetData(), _Mat.GetData(), _Scalar, 3, 3 );

        return Result;
    }


    Matrix3x3 operator*( const Matrix3x3& _MatA, const Matrix3x3& _MatB )
    {
        Matrix3x3 Result;

        priv::MatrixToolbox::Multiply( Result.GetData(), _MatA.GetData(), 3, 3, _MatB.GetData(), 3 );

        return Result;
    }


    Matrix3x3 operator/( const Matrix3x3& _MatA, const Matrix3x3& _MatB )
    {
        Matrix3x3 Result;

        priv::MatrixToolbox::Divide( Result.GetData(), _MatA.GetData(), 3, 3, _MatB.GetData() );

        return Result;
    }



    Matrix3x3 operator+( const Matrix3x3& _MatA, const Matrix3x3& _MatB )
    {
        Matrix3x3 Result;

        priv::MatrixToolbox::Add( Result.GetData(), _MatA.GetData(), 3, 3, _MatB.GetData() );

        return Result;
    }


    Matrix3x3 operator-( const Matrix3x3& _MatA, const Matrix3x3& _MatB )
    {
        Matrix3x3 Result;

        priv::MatrixToolbox::Subtract( Result.GetData(), _MatA.GetData(), 3, 3, _MatB.GetData() );

        return Result;
    }


    Matrix3x3 operator^( const Matrix3x3& _Mat, const float& _Power )
    {
        Matrix3x3 Result;

        priv::MatrixToolbox::Pow( Result.GetData(), _Mat.GetData(), _Power, 3, 3 );

        return Result;
    }



    Bool operator==( const Matrix3x3& _MatA, const Matrix3x3& _MatB )
    {
        for( Uint32 i = 0; i < 9; i++ )
        {
            if( _MatA[i] != _MatB[i] )
                return False;
        }

        return True;
    }

    Bool operator!=( const Matrix3x3& _MatA, const Matrix3x3& _MatB )
    {
        for( Uint32 i = 0; i < 9; i++ )
        {
            if( _MatA[i] != _MatB[i] )
                return True;
        }

        return False;
    }



    std::string ToString( const Matrix3x3& _Matrix )
    {
        std::string AsString = "";
        AsString += std::to_string( _Matrix[Matrix3x3::R0C0] ) + " " + std::to_string( _Matrix[Matrix3x3::R0C1] ) + " " + std::to_string( _Matrix[Matrix3x3::R0C2] ) + "\n";
        AsString += std::to_string( _Matrix[Matrix3x3::R1C0] ) + " " + std::to_string( _Matrix[Matrix3x3::R1C1] ) + " " + std::to_string( _Matrix[Matrix3x3::R1C2] ) + "\n";
        AsString += std::to_string( _Matrix[Matrix3x3::R2C0] ) + " " + std::to_string( _Matrix[Matrix3x3::R2C1] ) + " " + std::to_string( _Matrix[Matrix3x3::R2C2] );

        return AsString;
    }
} // ae

std::ostream& operator<<( std::ostream& os, const ae::Matrix3x3& _Matrix )
{
    os << ae::ToString( _Matrix );

    return os;
}
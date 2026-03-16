#include "Matrix4x4.h"

#include "../Functions/MathsFunctions.h"
#include "../../Debugging/Log/Log.h"



namespace ae
{
    const Matrix4x4 Matrix4x4::Zero =
    {
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    };

    const Matrix4x4 Matrix4x4::Identity =
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };


    Matrix4x4::Matrix4x4( const MatrixInitMode _InitMode )
    {
        priv::MatrixToolbox::Init( m_Mat, 4, 4, _InitMode );
    }

    Matrix4x4::Matrix4x4( const std::initializer_list<float>& _Elements )
    {
        size_t i = 0;
        for( float element : _Elements )
        {
            if( i >= 16 )
                break;

            m_Mat[i] = element;
            i++;
        }
    }

    Matrix4x4::Matrix4x4( const std::initializer_list<std::initializer_list<float>>& _Elements )
    {
        size_t iRow = 0;
        for( const std::initializer_list<float>& Row : _Elements )
        {
            if( iRow >= 4 )
                break;

            size_t iCol = 0;
            for( float element : Row )
            {
                if( iCol >= 4 )
                    break;

                m_Mat[iRow * 4 + iCol] = element;
                iCol++;
            }

            iRow++;
        }
    }

    Matrix4x4::Matrix4x4( const Matrix4x4& _Copy )
    {
        std::memcpy( m_Mat, _Copy.m_Mat, 16 * sizeof( float ) );
    }

    Matrix4x4& Matrix4x4::operator=( const Matrix4x4& _Copy )
    {
        std::memcpy( m_Mat, _Copy.m_Mat, 16 * sizeof( float ) );

        return *this;
    }

    Matrix4x4 Matrix4x4::operator-() const
    {
        return
        {
            -m_Mat[R0C0], -m_Mat[R0C1], -m_Mat[R0C2], -m_Mat[R0C3],
            -m_Mat[R1C0], -m_Mat[R1C1], -m_Mat[R1C2], -m_Mat[R1C3],
            -m_Mat[R2C0], -m_Mat[R2C1], -m_Mat[R2C2], -m_Mat[R2C3],
            -m_Mat[R3C0], -m_Mat[R3C1], -m_Mat[R3C2], -m_Mat[R3C3]
        };
    }

    Matrix4x4& Matrix4x4::SetToIdentity()
    {
        std::memcpy( m_Mat, Identity.m_Mat, 16 * sizeof( float ) );

        return *this;
    }
    Matrix4x4& Matrix4x4::SetToZero()
    {
        std::memset( m_Mat, 0, 16 * sizeof( float ) );

        return *this;
    }


    Vector3 Matrix4x4::GetForward() const
    {
        return Vector3( m_Mat[R0C2], m_Mat[R1C2], m_Mat[R2C2] );
    }
    Vector3 Matrix4x4::GetLeft() const
    {
        return Vector3( m_Mat[R0C0], m_Mat[R1C0], m_Mat[R2C0] );
    }
    Vector3 Matrix4x4::GetUp() const
    {
        return Vector3( m_Mat[R0C1], m_Mat[R1C1], m_Mat[R2C1] );
    }

    Vector3 Matrix4x4::GetForwardUnit() const
    {
        return GetForward().Normalize();
    }

    Vector3 Matrix4x4::GetLeftUnit() const
    {
        return GetLeft().Normalize();
    }

    Vector3 Matrix4x4::GetUpUnit() const
    {
        return GetUp().Normalize();
    }


    Matrix4x4& Matrix4x4::Rotate( const float _Angle, const Vector3& _Axis )
    {
        *this *= Matrix4x4::GetRotationMatrix( _Angle, _Axis );

        return *this;
    }
    Matrix4x4& Matrix4x4::RotateX( const float _Angle )
    {
        Matrix4x4 Rotation( MatrixInitMode::Identity );
        Rotation.SetRotationX( _Angle );

        *this *= Rotation;

        return *this;
    }
    Matrix4x4& Matrix4x4::RotateY( const float _Angle )
    {
        Matrix4x4 Rotation( MatrixInitMode::Identity );
        Rotation.SetRotationY( _Angle );

        *this *= Rotation;

        return *this;
    }
    Matrix4x4& Matrix4x4::RotateZ( const float _Angle )
    {
        Matrix4x4 Rotation( MatrixInitMode::Identity );
        Rotation.SetRotationZ( _Angle );

        *this *= Rotation;

        return *this;
    }
    Matrix4x4& Matrix4x4::SetRotation( const float _Angle, const Vector3& _Axis )
    {
        const float Cos = Math::Cos( _Angle );
        const float Cos1 = 1.0f - Cos;
        const float Sin = Math::Sin( _Angle );

        const float AxisLength = _Axis.Length();

        const float X = _Axis.X / AxisLength;
        const float Y = _Axis.Y / AxisLength;
        const float Z = _Axis.Z / AxisLength;

        const float XX = Math::Pow2( X );
        const float YY = Math::Pow2( Y );
        const float ZZ = Math::Pow2( Z );

        const float XY = X * Y;
        const float XZ = X * Z;
        const float YZ = Y * Z;

        m_Mat[R0C0] = XX * Cos1 + Cos;		m_Mat[R0C1] = XY * Cos1 - Z * Sin;	m_Mat[R0C2] = XZ * Cos1 + Y * Sin;	//m_Mat[R0C3] = 0.0f;
        m_Mat[R1C0] = XY * Cos1 + Z * Sin;	m_Mat[R1C1] = YY * Cos1 + Cos;		m_Mat[R1C2] = YZ * Cos1 - X * Sin;	//m_Mat[R1C3] = 0.0f;
        m_Mat[R2C0] = XZ * Cos1 - Y * Sin;	m_Mat[R2C1] = YZ * Cos1 + X * Sin;	m_Mat[R2C2] = ZZ * Cos1 + Cos;		//m_Mat[R2C3] = 0.0f;
        //m_Mat[R3C0] = 0.0f;				m_Mat[R3C1] = 0.0f;				m_Mat[R3C2] = 0.0f;				//m_Mat[R3C3] = 1.0f;

        return *this;
    }
    Matrix4x4& Matrix4x4::SetRotationX( const float _Angle )
    {
        const float SinAngle = Math::Sin( _Angle );
        const float CosAngle = Math::Cos( _Angle );

        m_Mat[R1C1] = CosAngle;
        m_Mat[R1C2] = -SinAngle;
        m_Mat[R2C1] = SinAngle;
        m_Mat[R2C2] = CosAngle;

        return *this;
    }
    Matrix4x4& Matrix4x4::SetRotationY( const float _Angle )
    {
        const float SinAngle = Math::Sin( _Angle );
        const float CosAngle = Math::Cos( _Angle );

        m_Mat[R0C0] = CosAngle;
        m_Mat[R0C2] = SinAngle;
        m_Mat[R2C0] = -SinAngle;
        m_Mat[R2C2] = CosAngle;

        return *this;
    }
    Matrix4x4& Matrix4x4::SetRotationZ( const float _Angle )
    {
        const float SinAngle = Math::Sin( _Angle );
        const float CosAngle = Math::Cos( _Angle );

        m_Mat[R0C0] = CosAngle;
        m_Mat[R0C1] = -SinAngle;
        m_Mat[R1C0] = SinAngle;
        m_Mat[R1C1] = CosAngle;

        return *this;
    }
    Matrix4x4& Matrix4x4::Scale( const Vector3& _Scale )
    {
        Matrix4x4 Scaling( MatrixInitMode::Identity );
        Scaling.SetScale( _Scale );

        *this *= Scaling;

        return *this;
    }
    Matrix4x4& Matrix4x4::SetScale( const Vector3& _Scale )
    {
        m_Mat[R0C0] = _Scale.X;
        m_Mat[R1C1] = _Scale.Y;
        m_Mat[R2C2] = _Scale.Z;

        return *this;
    }
    Matrix4x4& Matrix4x4::Translate( const Vector3& _Vector )
    {
        m_Mat[R0C3] += _Vector.X;
        m_Mat[R1C3] += _Vector.Y;
        m_Mat[R2C3] += _Vector.Z;

        return *this;
    }
    Matrix4x4& Matrix4x4::SetTranslation( const Vector3& _Vector )
    {
        m_Mat[R0C3] = _Vector.X;
        m_Mat[R1C3] = _Vector.Y;
        m_Mat[R2C3] = _Vector.Z;

        return *this;
    }

    Matrix4x4& Matrix4x4::LookAt( const Vector3& _Eye, const Vector3& _PointToLookAt, const Vector3& _UpWorld )
    {
        Vector3 Forward( _Eye, _PointToLookAt );
        Forward.Normalize();

        const Vector3&& UpWorldUnit = static_cast<Vector3&&>( _UpWorld.GetNormalized() );

        const Vector3&& Side = static_cast<Vector3&&>( Forward.Cross( UpWorldUnit ).Normalize() );

        const Vector3&& Up = static_cast<Vector3&&>( Side.Cross( Forward ) );

        /*const Matrix4x4 Result = { Side.X, Up.X, -Forward.X, -0.0f,
                                    Side.Y, Up.Y, -Forward.Y, -0.0f,
                                    Side.Z, Up.Z, -Forward.Z, 0.0f,
                                    -Side.Dot( _Eye ), -Up.Dot( _Eye ), Forward.Dot( _Eye ), 1.0f };*/


        m_Mat[R0C0] = Side.X;     m_Mat[R0C1] = Side.Y;     m_Mat[R0C2] = Side.Z;     m_Mat[R0C3] = -Side.Dot( _Eye );
        m_Mat[R1C0] = Up.X;       m_Mat[R1C1] = Up.Y;       m_Mat[R1C2] = Up.Z;       m_Mat[R1C3] = -Up.Dot( _Eye );
        m_Mat[R2C0] = -Forward.X; m_Mat[R2C1] = -Forward.Y; m_Mat[R2C2] = -Forward.Z; m_Mat[R2C3] = Forward.Dot( _Eye );
        m_Mat[R3C0] = 0.0f;       m_Mat[R3C1] = 0.0f;       m_Mat[R3C2] = 0.0f;       m_Mat[R3C3] = 1.0f;

        return *this;
    }


    float Matrix4x4::GetDeterminant() const
    {
        const float SubFactors[]
        {
            m_Mat[R2C2] * m_Mat[R3C3] - m_Mat[R2C3] * m_Mat[R3C2],
            m_Mat[R1C2] * m_Mat[R3C3] - m_Mat[R1C3] * m_Mat[R3C2],
            m_Mat[R1C2] * m_Mat[R2C3] - m_Mat[R1C3] * m_Mat[R2C2],
            m_Mat[R0C2] * m_Mat[R3C3] - m_Mat[R0C3] * m_Mat[R3C2],
            m_Mat[R0C2] * m_Mat[R2C3] - m_Mat[R0C3] * m_Mat[R2C2],
            m_Mat[R0C2] * m_Mat[R1C3] - m_Mat[R0C3] * m_Mat[R1C2]
        };

        const float Coefs[] =
        {
            m_Mat[R1C1] * SubFactors[0] - m_Mat[R2C1] * SubFactors[1] + m_Mat[R3C1] * SubFactors[2],
            -( m_Mat[R0C1] * SubFactors[0] - m_Mat[R2C1] * SubFactors[3] + m_Mat[R3C1] * SubFactors[4] ),
            m_Mat[R0C1] * SubFactors[1] - m_Mat[R1C1] * SubFactors[3] + m_Mat[R3C1] * SubFactors[5],
            -( m_Mat[R0C1] * SubFactors[2] - m_Mat[R1C1] * SubFactors[4] + m_Mat[R2C1] * SubFactors[5] )
        };

        return ( m_Mat[R0C0] * Coefs[0] + m_Mat[R1C0] * Coefs[1] + m_Mat[R2C0] * Coefs[2] + m_Mat[R3C0] * Coefs[3] );
    }

    Matrix4x4& Matrix4x4::Inverse()
    {
        // http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html

        // b11 = 112233 122331 132132 112332 122133 132231
        // b12 = 012332 022133 032231 012233 022331 032132
        // b13 = 011233 021331 031132 011332 021133 031231
        // b14 = 011233 021331 031132 011332 021321 031122
        // b21 = 102332 122033 132230 102233 122330 132032
        // b22 = 002233 022330 032032 002332 022033 032230
        // b23 = 001332 021033 031230 001233 021330 031032
        // b24 = 001223 021320 031022 001322 021023 031220
        // b31 = 102133 112330 132031 102331 112033 132130
        // b32 = 002331 012033 032130 002133 012330 032031
        // b33 = 001133 011330 031031 001331 011033 031130
        // b34 = 001321 011023 031120 001123 011320 031021
        // b41 = 102231 112032 122130 102132 112230 122031
        // b42 = 002132 012230 022031 002231 012032 022130
        // b43 = 001231 011032 021130 001132 011230 021031
        // b44 = 001122 011220 021021 001221 011022 021120

        float C11, C12, C13, C14;
        float C21, C22, C23, C24;
        float C31, C32, C33, C34;
        float C41, C42, C43, C44;

        const float Determinant =
            m_Mat[R0C0] * m_Mat[R1C1] * m_Mat[R2C2] * m_Mat[R3C3]
            + m_Mat[R0C0] * m_Mat[R1C2] * m_Mat[R2C3] * m_Mat[R3C1]
            + m_Mat[R0C0] * m_Mat[R1C3] * m_Mat[R2C1] * m_Mat[R3C2]

            + m_Mat[R0C1] * m_Mat[R1C0] * m_Mat[R2C3] * m_Mat[R3C2]
            + m_Mat[R0C1] * m_Mat[R1C2] * m_Mat[R2C0] * m_Mat[R3C3]
            + m_Mat[R0C1] * m_Mat[R1C3] * m_Mat[R2C2] * m_Mat[R3C0]

            + m_Mat[R0C2] * m_Mat[R1C0] * m_Mat[R2C1] * m_Mat[R3C3]
            + m_Mat[R0C2] * m_Mat[R1C1] * m_Mat[R2C3] * m_Mat[R3C0]
            + m_Mat[R0C2] * m_Mat[R1C3] * m_Mat[R2C0] * m_Mat[R3C1]

            + m_Mat[R0C3] * m_Mat[R1C0] * m_Mat[R2C2] * m_Mat[R3C1]
            + m_Mat[R0C3] * m_Mat[R1C1] * m_Mat[R2C0] * m_Mat[R3C2]
            + m_Mat[R0C3] * m_Mat[R1C2] * m_Mat[R2C1] * m_Mat[R3C0]

            - m_Mat[R0C0] * m_Mat[R1C1] * m_Mat[R2C3] * m_Mat[R3C2]
            - m_Mat[R0C0] * m_Mat[R1C2] * m_Mat[R2C1] * m_Mat[R3C3]
            - m_Mat[R0C0] * m_Mat[R1C3] * m_Mat[R2C2] * m_Mat[R3C1]

            - m_Mat[R0C1] * m_Mat[R1C0] * m_Mat[R2C2] * m_Mat[R3C3]
            - m_Mat[R0C1] * m_Mat[R1C2] * m_Mat[R2C3] * m_Mat[R3C0]
            - m_Mat[R0C1] * m_Mat[R1C3] * m_Mat[R2C0] * m_Mat[R3C2]

            - m_Mat[R0C2] * m_Mat[R1C0] * m_Mat[R2C3] * m_Mat[R3C1]
            - m_Mat[R0C2] * m_Mat[R1C1] * m_Mat[R2C0] * m_Mat[R3C3]
            - m_Mat[R0C2] * m_Mat[R1C3] * m_Mat[R2C1] * m_Mat[R3C0]

            - m_Mat[R0C3] * m_Mat[R1C0] * m_Mat[R2C1] * m_Mat[R3C2]
            - m_Mat[R0C3] * m_Mat[R1C1] * m_Mat[R2C2] * m_Mat[R3C0]
            - m_Mat[R0C3] * m_Mat[R1C2] * m_Mat[R2C0] * m_Mat[R3C1];

        if( Determinant == 0.0f )
        {
            AE_LogError( "Can't inverse the matrix, derterminant is equal to 0." );
            return *this;
        }

        const float InvDeterminant = 1.0f / Determinant;

        C11 = ( m_Mat[R1C1] * m_Mat[R2C2] * m_Mat[R3C3] + m_Mat[R1C2] * m_Mat[R2C3] * m_Mat[R3C1] + m_Mat[R1C3] * m_Mat[R2C1] * m_Mat[R3C2] )
            - ( m_Mat[R1C1] * m_Mat[R2C3] * m_Mat[R3C2] + m_Mat[R1C2] * m_Mat[R2C1] * m_Mat[R3C3] + m_Mat[R1C3] * m_Mat[R2C2] * m_Mat[R3C1] );

        C12 = ( m_Mat[R0C1] * m_Mat[R2C3] * m_Mat[R3C2] + m_Mat[R0C2] * m_Mat[R2C1] * m_Mat[R3C3] + m_Mat[R0C0] * m_Mat[R2C2] * m_Mat[R3C1] )
            - ( m_Mat[R0C1] * m_Mat[R2C2] * m_Mat[R3C3] + m_Mat[R0C2] * m_Mat[R2C3] * m_Mat[R3C1] + m_Mat[R0C3] * m_Mat[R2C1] * m_Mat[R3C2] );

        C13 = ( m_Mat[R0C1] * m_Mat[R1C2] * m_Mat[R3C3] + m_Mat[R0C2] * m_Mat[R1C3] * m_Mat[R3C1] + m_Mat[R0C0] * m_Mat[R1C1] * m_Mat[R3C2] )
            - ( m_Mat[R0C1] * m_Mat[R1C3] * m_Mat[R3C2] + m_Mat[R0C2] * m_Mat[R1C1] * m_Mat[R3C3] + m_Mat[R0C3] * m_Mat[R1C2] * m_Mat[R3C1] );

        C14 = ( m_Mat[R0C1] * m_Mat[R1C3] * m_Mat[R2C2] + m_Mat[R0C2] * m_Mat[R1C1] * m_Mat[R2C3] + m_Mat[R0C3] * m_Mat[R1C2] * m_Mat[R2C1] )
            - ( m_Mat[R0C1] * m_Mat[R1C2] * m_Mat[R2C3] + m_Mat[R0C2] * m_Mat[R1C3] * m_Mat[R2C1] + m_Mat[R0C3] * m_Mat[R1C1] * m_Mat[R2C2] );


        C21 = ( m_Mat[R1C0] * m_Mat[R2C3] * m_Mat[R3C2] + m_Mat[R1C2] * m_Mat[R2C0] * m_Mat[R3C3] + m_Mat[R1C3] * m_Mat[R2C2] * m_Mat[R3C0] )
            - ( m_Mat[R1C0] * m_Mat[R2C2] * m_Mat[R3C3] + m_Mat[R1C2] * m_Mat[R2C3] * m_Mat[R3C0] + m_Mat[R1C3] * m_Mat[R2C0] * m_Mat[R3C2] );

        C22 = ( m_Mat[R0C0] * m_Mat[R2C2] * m_Mat[R3C3] + m_Mat[R0C2] * m_Mat[R2C3] * m_Mat[R3C0] + m_Mat[R0C3] * m_Mat[R2C0] * m_Mat[R3C2] )
            - ( m_Mat[R0C0] * m_Mat[R2C3] * m_Mat[R3C2] + m_Mat[R0C2] * m_Mat[R2C0] * m_Mat[R3C3] + m_Mat[R0C3] * m_Mat[R2C2] * m_Mat[R3C0] );

        C23 = ( m_Mat[R0C0] * m_Mat[R1C3] * m_Mat[R3C2] + m_Mat[R0C2] * m_Mat[R1C0] * m_Mat[R3C3] + m_Mat[R0C3] * m_Mat[R1C2] * m_Mat[R3C0] )
            - ( m_Mat[R0C0] * m_Mat[R1C2] * m_Mat[R3C3] + m_Mat[R0C2] * m_Mat[R1C3] * m_Mat[R3C0] + m_Mat[R0C3] * m_Mat[R1C0] * m_Mat[R3C2] );

        C24 = ( m_Mat[R0C0] * m_Mat[R1C2] * m_Mat[R2C3] + m_Mat[R0C2] * m_Mat[R1C3] * m_Mat[R2C0] + m_Mat[R0C3] * m_Mat[R1C0] * m_Mat[R2C2] )
            - ( m_Mat[R0C0] * m_Mat[R1C3] * m_Mat[R2C2] + m_Mat[R0C2] * m_Mat[R1C0] * m_Mat[R2C3] + m_Mat[R0C3] * m_Mat[R1C2] * m_Mat[R2C0] );


        C31 = ( m_Mat[R1C0] * m_Mat[R2C1] * m_Mat[R3C3] + m_Mat[R1C1] * m_Mat[R2C3] * m_Mat[R3C0] + m_Mat[R1C3] * m_Mat[R2C0] * m_Mat[R3C1] )
            - ( m_Mat[R1C0] * m_Mat[R2C3] * m_Mat[R3C1] + m_Mat[R1C1] * m_Mat[R2C0] * m_Mat[R3C3] + m_Mat[R1C3] * m_Mat[R2C1] * m_Mat[R3C0] );

        C32 = ( m_Mat[R0C0] * m_Mat[R2C3] * m_Mat[R3C1] + m_Mat[R0C1] * m_Mat[R2C0] * m_Mat[R3C3] + m_Mat[R0C3] * m_Mat[R2C1] * m_Mat[R3C0] )
            - ( m_Mat[R0C0] * m_Mat[R2C1] * m_Mat[R3C3] + m_Mat[R0C1] * m_Mat[R2C3] * m_Mat[R3C0] + m_Mat[R0C3] * m_Mat[R2C0] * m_Mat[R3C1] );

        C33 = ( m_Mat[R0C0] * m_Mat[R1C1] * m_Mat[R3C3] + m_Mat[R0C1] * m_Mat[R1C3] * m_Mat[R3C0] + m_Mat[R0C3] * m_Mat[R1C0] * m_Mat[R3C1] )
            - ( m_Mat[R0C0] * m_Mat[R1C3] * m_Mat[R3C1] + m_Mat[R0C1] * m_Mat[R1C0] * m_Mat[R3C3] + m_Mat[R0C3] * m_Mat[R1C1] * m_Mat[R3C0] );

        C34 = ( m_Mat[R0C0] * m_Mat[R1C3] * m_Mat[R2C1] + m_Mat[R0C1] * m_Mat[R1C0] * m_Mat[R2C3] + m_Mat[R0C3] * m_Mat[R1C1] * m_Mat[R2C0] )
            - ( m_Mat[R0C0] * m_Mat[R1C1] * m_Mat[R2C3] + m_Mat[R0C1] * m_Mat[R1C3] * m_Mat[R2C0] + m_Mat[R0C3] * m_Mat[R1C0] * m_Mat[R2C1] );


        C41 = ( m_Mat[R1C0] * m_Mat[R2C2] * m_Mat[R3C1] + m_Mat[R1C1] * m_Mat[R2C0] * m_Mat[R3C2] + m_Mat[R1C2] * m_Mat[R2C1] * m_Mat[R3C0] )
            - ( m_Mat[R1C0] * m_Mat[R2C1] * m_Mat[R3C2] + m_Mat[R1C1] * m_Mat[R2C2] * m_Mat[R3C0] + m_Mat[R1C2] * m_Mat[R2C0] * m_Mat[R3C1] );

        C42 = ( m_Mat[R0C0] * m_Mat[R2C1] * m_Mat[R3C2] + m_Mat[R0C1] * m_Mat[R2C2] * m_Mat[R3C0] + m_Mat[R0C2] * m_Mat[R2C0] * m_Mat[R3C1] )
            - ( m_Mat[R0C0] * m_Mat[R2C2] * m_Mat[R3C1] + m_Mat[R0C1] * m_Mat[R2C0] * m_Mat[R3C2] + m_Mat[R0C2] * m_Mat[R2C1] * m_Mat[R3C0] );

        C43 = ( m_Mat[R0C0] * m_Mat[R1C2] * m_Mat[R3C1] + m_Mat[R0C1] * m_Mat[R1C0] * m_Mat[R3C2] + m_Mat[R0C2] * m_Mat[R1C1] * m_Mat[R3C0] )
            - ( m_Mat[R0C0] * m_Mat[R1C1] * m_Mat[R3C2] + m_Mat[R0C1] * m_Mat[R1C2] * m_Mat[R3C0] + m_Mat[R0C2] * m_Mat[R1C0] * m_Mat[R3C1] );

        C44 = ( m_Mat[R0C0] * m_Mat[R1C1] * m_Mat[R2C2] + m_Mat[R0C1] * m_Mat[R1C2] * m_Mat[R2C0] + m_Mat[R0C2] * m_Mat[R1C0] * m_Mat[R2C1] )
            - ( m_Mat[R0C0] * m_Mat[R1C2] * m_Mat[R2C1] + m_Mat[R0C1] * m_Mat[R1C0] * m_Mat[R2C2] + m_Mat[R0C2] * m_Mat[R1C1] * m_Mat[R2C0] );

        m_Mat[R0C0] = C11 * InvDeterminant;
        m_Mat[R0C1] = C12 * InvDeterminant;
        m_Mat[R0C2] = C13 * InvDeterminant;
        m_Mat[R0C3] = C14 * InvDeterminant;

        m_Mat[R1C0] = C21 * InvDeterminant;
        m_Mat[R1C1] = C22 * InvDeterminant;
        m_Mat[R1C2] = C23 * InvDeterminant;
        m_Mat[R1C3] = C24 * InvDeterminant;

        m_Mat[R2C0] = C31 * InvDeterminant;
        m_Mat[R2C1] = C32 * InvDeterminant;
        m_Mat[R2C2] = C33 * InvDeterminant;
        m_Mat[R2C3] = C34 * InvDeterminant;

        m_Mat[R3C0] = C41 * InvDeterminant;
        m_Mat[R3C1] = C42 * InvDeterminant;
        m_Mat[R3C2] = C43 * InvDeterminant;
        m_Mat[R3C3] = C44 * InvDeterminant;

        return *this;
    }
    Matrix4x4 Matrix4x4::GetInverse() const
    {
        Matrix4x4 Result = *this;

        return Result.Inverse();
    }

    Matrix4x4& Matrix4x4::SwitchVectorPosition()
    {
        std::swap( m_Mat[R0C3], m_Mat[R3C0] );
        std::swap( m_Mat[R1C3], m_Mat[R3C1] );
        std::swap( m_Mat[R2C3], m_Mat[R3C2] );

        return *this;
    }

    Vector3 Matrix4x4::GetTransformedPoint( const Vector3& _Point ) const
    {
        Vector3 Result;

        Result.X = _Point.X * m_Mat[R0C0] + _Point.Y * m_Mat[R0C1] + _Point.Z * m_Mat[R0C2] + m_Mat[R0C3];
        Result.Y = _Point.X * m_Mat[R1C0] + _Point.Y * m_Mat[R1C1] + _Point.Z * m_Mat[R1C2] + m_Mat[R1C3];
        Result.Z = _Point.X * m_Mat[R2C0] + _Point.Y * m_Mat[R2C1] + _Point.Z * m_Mat[R2C2] + m_Mat[R2C3];

        return Result;
    }
    void Matrix4x4::TransformPoint( AE_InOut Vector3& _Point ) const
    {
        Vector3 Copy( _Point );

        _Point.X = Copy.X * m_Mat[R0C0] + Copy.Y * m_Mat[R0C1] + Copy.Z * m_Mat[R0C2] + m_Mat[R0C3];
        _Point.Y = Copy.X * m_Mat[R1C0] + Copy.Y * m_Mat[R1C1] + Copy.Z * m_Mat[R1C2] + m_Mat[R1C3];
        _Point.Z = Copy.X * m_Mat[R2C0] + Copy.Y * m_Mat[R2C1] + Copy.Z * m_Mat[R2C2] + m_Mat[R2C3];
    }

    Matrix4x4& Matrix4x4::SetToPerspectiveMatrix( const float _Fov, const float _Aspect, const float _Near, const float _Far )
    {
        float TanHalfFovY = Math::Tan( _Fov / 2.0f );
        float RangeInv = 1.0f / ( _Far - _Near );

        m_Mat[R0C0] = 1.0f / ( TanHalfFovY * _Aspect );
        m_Mat[R0C1] = 0.0f;
        m_Mat[R0C2] = 0.0f;
        m_Mat[R0C3] = 0.0f;

        m_Mat[R1C0] = 0.0f;
        m_Mat[R1C1] = 1.0f / TanHalfFovY;
        m_Mat[R1C2] = 0.0f;
        m_Mat[R1C3] = 0.0f;

        m_Mat[R2C0] = 0.0f;
        m_Mat[R2C1] = 0.0f;
        m_Mat[R2C2] = -( _Near + _Far ) * RangeInv;
        m_Mat[R2C3] = -2.0f * _Far * _Near * RangeInv;

        m_Mat[R3C0] = 0.0f;
        m_Mat[R3C2] = -1.0f;
        m_Mat[R3C1] = 0.0f;
        m_Mat[R3C3] = 0.0f;

        return *this;
    }

    Matrix4x4& Matrix4x4::SetToOrthogonalMatrix( const float _Left, const float _Top, const float _Right, const float _Bottom,
                                                 const float _Near, const float _Far )
    {
        m_Mat[R0C0] = 2.0f / ( _Right - _Left );
        m_Mat[R0C1] = 0.0f;
        m_Mat[R0C2] = 0.0f;
        m_Mat[R0C3] = -( _Right + _Left ) / ( _Right - _Left );

        m_Mat[R1C0] = 0.0f;
        m_Mat[R1C1] = 2.0f / ( _Top - _Bottom );
        m_Mat[R1C2] = 0.0f;
        m_Mat[R1C3] = -( _Top + _Bottom ) / ( _Top - _Bottom );

        m_Mat[R2C0] = 0.0f;
        m_Mat[R2C1] = 0.0f;
        m_Mat[R2C2] = -2.0f / ( _Far - _Near );
        m_Mat[R2C3] = -( _Far + _Near ) / ( _Far - _Near );

        m_Mat[R3C0] = 0.0f;
        m_Mat[R3C2] = 0.0f;
        m_Mat[R3C1] = 0.0f;
        m_Mat[R3C3] = 1.0f;

        return *this;
    }

    Matrix4x4 Matrix4x4::GetPerspectiveMatrix( const float _Fov, const float _Aspect, const float _Near, const float _Far )
    {
        Matrix4x4 Result;
        Result.SetToPerspectiveMatrix( _Fov, _Aspect, _Near, _Far );
        return Result;
    }

    Matrix4x4 Matrix4x4::GetOrthogonalMatrix( const float _Left, const float _Top, const float _Right, const float _Bottom,
                                              const float _Near, const float _Far )
    {
        Matrix4x4 Result;
        Result.SetToOrthogonalMatrix( _Left, _Top, _Right, _Bottom, _Near, _Far );
        return Result;
    }

    Matrix4x4 Matrix4x4::GetScaleMatrix( const Vector3& _Scale )
    {
        Matrix4x4 Result( MatrixInitMode::Identity );
        Result.SetScale( _Scale );

        return Result;
    }
    Matrix4x4 Matrix4x4::GetRotationMatrix( const float _Angle, const Vector3& _Axis )
    {
        Matrix4x4 Result( MatrixInitMode::Identity );
        Result.SetRotation( _Angle, _Axis );

        return Result;
    }
    Matrix4x4 Matrix4x4::GetTranslationMatrix( const Vector3& _Vector )
    {
        Matrix4x4 Result( MatrixInitMode::Identity );
        Result.SetTranslation( _Vector );

        return Result;
    }
    Matrix4x4 Matrix4x4::GetLookAtMatrix( const Vector3& _Eye, const Vector3& _PointToLookAt, const Vector3& _UpWorld )
    {
        Matrix4x4 Result;
        Result.LookAt( _Eye, _PointToLookAt, _UpWorld );
        return Result;
    }




    inline Matrix4x4& Matrix4x4::Transpose()
    {
        std::swap( m_Mat[R1C0], m_Mat[R0C1] );
        std::swap( m_Mat[R2C0], m_Mat[R0C2] );
        std::swap( m_Mat[R3C0], m_Mat[R0C3] );
        std::swap( m_Mat[R2C1], m_Mat[R1C2] );
        std::swap( m_Mat[R3C1], m_Mat[R1C3] );
        std::swap( m_Mat[R3C2], m_Mat[R2C3] );

        return *this;
    }

    Matrix4x4 Matrix4x4::GetTranspose() const
    {
        Matrix4x4 Result = *this;

        return Result.Transpose();
    }


    Matrix4x4& Matrix4x4::Abs()
    {
        priv::MatrixToolbox::Abs( m_Mat, m_Mat, 4, 4 );

        return *this;
    }


    Matrix4x4 Matrix4x4::GetAbs() const
    {
        Matrix4x4 Result;

        priv::MatrixToolbox::Abs( Result.m_Mat, m_Mat, 4, 4 );

        return Result;
    }

    float Matrix4x4::GetTrace() const
    {
        return m_Mat[R0C0] + m_Mat[R1C1] + m_Mat[R2C2] + m_Mat[R3C3];
    }





    Matrix4x4& Matrix4x4::operator*=( const float& _Scalar )
    {
        priv::MatrixToolbox::Multiply( m_Mat, m_Mat, _Scalar, 4, 4 );

        return *this;
    }


    Matrix4x4& Matrix4x4::operator/=( const float& _Scalar )
    {
        priv::MatrixToolbox::Divide( m_Mat, m_Mat, _Scalar, 4, 4 );

        return *this;
    }


    inline Matrix4x4& Matrix4x4::operator+=( const float& _Scalar )
    {
        priv::MatrixToolbox::Add( m_Mat, m_Mat, _Scalar, 4, 4 );

        return *this;
    }


    Matrix4x4& Matrix4x4::operator-=( const float& _Scalar )
    {
        priv::MatrixToolbox::Subtract( m_Mat, m_Mat, _Scalar, 4, 4 );

        return *this;
    }


    Matrix4x4& Matrix4x4::operator*=( const Matrix4x4& _MatB )
    {
        Matrix4x4 Result;

        priv::MatrixToolbox::Multiply( Result.m_Mat, m_Mat, 4, 4, _MatB.m_Mat, 4 );

        *this = Result;

        return *this;
    }



    Matrix4x4& Matrix4x4::operator/=( const Matrix4x4& _MatB )
    {
        priv::MatrixToolbox::Divide( m_Mat, m_Mat, 4, 4, _MatB.m_Mat );

        return *this;
    }



    Matrix4x4& Matrix4x4::operator+=( const Matrix4x4& _MatB )
    {
        priv::MatrixToolbox::Add( m_Mat, m_Mat, 4, 4, _MatB.m_Mat );

        return *this;
    }


    Matrix4x4& Matrix4x4::operator-=( const Matrix4x4& _MatB )
    {
        priv::MatrixToolbox::Subtract( m_Mat, m_Mat, 4, 4, _MatB.m_Mat );

        return *this;
    }



    Matrix4x4& Matrix4x4::operator^=( const float& _Power )
    {
        priv::MatrixToolbox::Pow( m_Mat, m_Mat, _Power, 4, 4 );

        return *this;
    }


    float Matrix4x4::operator[]( const Uint32 _Index ) const
    {
        if( _Index < 0 || _Index >= 16 )
            throw std::out_of_range( "Invalid index" );

        return m_Mat[_Index];
    }



    float& Matrix4x4::operator[]( const Uint32 _Index )
    {
        if( _Index < 0 || _Index >= 16 )
            throw std::out_of_range( "Invalid index" );

        return m_Mat[_Index];
    }


    float Matrix4x4::operator()( const Uint32 _Index ) const
    {
        if( _Index < 0 || _Index >= 16 )
            throw std::out_of_range( "Invalid index" );

        return m_Mat[_Index];
    }



    float& Matrix4x4::operator()( const Uint32 _Index )
    {
        if( _Index < 0 || _Index >= 16 )
            throw std::out_of_range( "Invalid index" );

        return m_Mat[_Index];
    }


    float Matrix4x4::operator()( const Uint32 _Row, const Uint32 _Col ) const
    {
        if( _Row < 0 || _Row >= 4 )
            throw std::out_of_range( "Invalid row" );

        if( _Col < 0 || _Col >= 4 )
            throw std::out_of_range( "Invalid column" );

        return m_Mat[_Row * +_Col];
    }


    float& Matrix4x4::operator()( const Uint32 _Row, const Uint32 _Col )
    {
        if( _Row < 0 || _Row >= 4 )
            throw std::out_of_range( "Invalid row" );

        if( _Col < 0 || _Col >= 4 )
            throw std::out_of_range( "Invalid column" );

        return m_Mat[_Row * 4 + _Col];
    }

    const float* const Matrix4x4::GetData() const
    {
        return m_Mat;
    }


    float* const Matrix4x4::GetData()
    {
        return m_Mat;
    }



    Matrix4x4 operator*( const Matrix4x4& _Mat, const float& _Scalar )
    {
        Matrix4x4 Result;

        priv::MatrixToolbox::Multiply( Result.GetData(), _Mat.GetData(), _Scalar, 4, 4 );

        return Result;
    }


    Matrix4x4 operator/( const Matrix4x4& _Mat, const float& _Scalar )
    {
        Matrix4x4 Result;

        priv::MatrixToolbox::Divide( Result.GetData(), _Mat.GetData(), _Scalar, 4, 4 );

        return Result;
    }


    Matrix4x4 operator+( const Matrix4x4& _Mat, const float& _Scalar )
    {
        Matrix4x4 Result;

        priv::MatrixToolbox::Add( Result.GetData(), _Mat.GetData(), _Scalar, 4, 4 );

        return Result;
    }


    Matrix4x4 operator-( const Matrix4x4& _Mat, const float& _Scalar )
    {
        Matrix4x4 Result;

        priv::MatrixToolbox::Subtract( Result.GetData(), _Mat.GetData(), _Scalar, 4, 4 );

        return Result;
    }


    Matrix4x4 operator*( const Matrix4x4& _MatA, const Matrix4x4& _MatB )
    {
        Matrix4x4 Result;

        priv::MatrixToolbox::Multiply( Result.GetData(), _MatA.GetData(), 4, 4, _MatB.GetData(), 4 );

        return Result;
    }


    Matrix4x4 operator/( const Matrix4x4& _MatA, const Matrix4x4& _MatB )
    {
        Matrix4x4 Result;

        priv::MatrixToolbox::Divide( Result.GetData(), _MatA.GetData(), 4, 4, _MatB.GetData() );

        return Result;
    }



    Matrix4x4 operator+( const Matrix4x4& _MatA, const Matrix4x4& _MatB )
    {
        Matrix4x4 Result;

        priv::MatrixToolbox::Add( Result.GetData(), _MatA.GetData(), 4, 4, _MatB.GetData() );

        return Result;
    }


    Matrix4x4 operator-( const Matrix4x4& _MatA, const Matrix4x4& _MatB )
    {
        Matrix4x4 Result;

        priv::MatrixToolbox::Subtract( Result.GetData(), _MatA.GetData(), 4, 4, _MatB.GetData() );

        return Result;
    }


    Matrix4x4 operator^( const Matrix4x4& _Mat, const float& _Power )
    {
        Matrix4x4 Result;

        priv::MatrixToolbox::Pow( Result.GetData(), _Mat.GetData(), _Power, 4, 4 );

        return Result;
    }


    Bool operator==( const Matrix4x4& _MatA, const Matrix4x4& _MatB )
    {
        for( Uint32 i = 0; i < 16; i++ )
        {
            if( _MatA[i] != _MatB[i] )
                return False;
        }

        return True;
    }

    Bool operator!=( const Matrix4x4& _MatA, const Matrix4x4& _MatB )
    {
        for( Uint32 i = 0; i < 16; i++ )
        {
            if( _MatA[i] != _MatB[i] )
                return True;
        }

        return False;
    }



    std::string ToString( const Matrix4x4& _Matrix )
    {
        std::string AsString = "";
        AsString += std::to_string( _Matrix[Matrix4x4::R0C0] ) + " " + std::to_string( _Matrix[Matrix4x4::R0C1] ) + " " + std::to_string( _Matrix[Matrix4x4::R0C2] ) + " " + std::to_string( _Matrix[Matrix4x4::R0C3] ) + "\n";
        AsString += std::to_string( _Matrix[Matrix4x4::R1C0] ) + " " + std::to_string( _Matrix[Matrix4x4::R1C1] ) + " " + std::to_string( _Matrix[Matrix4x4::R1C2] ) + " " + std::to_string( _Matrix[Matrix4x4::R1C3] ) + "\n";
        AsString += std::to_string( _Matrix[Matrix4x4::R2C0] ) + " " + std::to_string( _Matrix[Matrix4x4::R2C1] ) + " " + std::to_string( _Matrix[Matrix4x4::R2C2] ) + " " + std::to_string( _Matrix[Matrix4x4::R2C3] ) + "\n";
        AsString += std::to_string( _Matrix[Matrix4x4::R3C0] ) + " " + std::to_string( _Matrix[Matrix4x4::R3C1] ) + " " + std::to_string( _Matrix[Matrix4x4::R3C2] ) + " " + std::to_string( _Matrix[Matrix4x4::R3C3] );

        return AsString;
    }


} // ae


std::ostream& operator<<( std::ostream& os, const ae::Matrix4x4& _Matrix )
{
    os << ae::ToString( _Matrix );

    return os;
}
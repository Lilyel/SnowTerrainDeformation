#include "Plane.h"

#include "../Functions/MathsFunctions.h"

namespace ae
{

    Plane::Plane( const Vector3& _Point, const Vector3& _Normal ) :
        m_Point( _Point ),
        m_Normal( _Normal.GetNormalized() )
    {
    }

    void Plane::SetPoint( const Vector3& _Point )
    {
        m_Point = _Point;
    }

    const Vector3& Plane::GetPoint() const
    {
        return m_Point;
    }

    void Plane::SetNormal( const Vector3& _Normal )
    {
        m_Normal = _Normal.GetNormalized();
    }

    const Vector3& Plane::GetNormal() const
    {
        return m_Normal;
    }

    float Plane::GetDistanceToPlane( const Vector3& _Point ) const
    {
        return Math::Abs( GetSignedDistanceToPlane( _Point ) );
    }

    float Plane::GetSignedDistanceToPlane( const Vector3& _Point ) const
    {
        return m_Normal.Dot( _Point - m_Point );
    }

} // ae

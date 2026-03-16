#include "Sphere.h"

namespace ae
{

    Sphere::Sphere( const Vector3& _Center, float _Radius ) :
        m_Center( _Center ),
        m_Radius( _Radius )
    {
    }

    void Sphere::SetCenter( const Vector3& _Center )
    {
        m_Center = _Center;
    }

    const Vector3& Sphere::GetCenter() const
    {
        return m_Center;
    }

    void Sphere::SetRadius( float _Radius )
    {
        m_Radius = _Radius;
    }

    float Sphere::GetRadius() const
    {
        return m_Radius;
    }

    Bool Sphere::Intersects( const Sphere& _Other, Bool _WithBoundaries, Bool _UseSquaredLength ) const
    {
        // If we have to take boundaries into account use '<=' otherwise, use '<'.
        bool( *LessOperator )( float, float ) = _WithBoundaries ? &islessequal<float, float> : &isless<float, float>;

        const Vector3 ToOther( _Other.m_Center - m_Center );
        const float DistanceToOther = _UseSquaredLength ? ToOther.LengthSqr() : ToOther.Length();

        const float IntersectionDistance = _Other.m_Radius + m_Radius;

        return LessOperator( DistanceToOther, IntersectionDistance );
    }

    Bool Sphere::Contains( const Sphere& _Other, Bool _WithBoundaries, Bool _UseSquaredLength ) const
    {
        // If we have to take boundaries into account use '<=' otherwise, use '<'.
        bool( *LessOperator )( float, float ) = _WithBoundaries ? &islessequal<float, float> : &isless<float, float>;

        const Vector3 ToOther( _Other.m_Center - m_Center );
        const float DistanceToOther = _UseSquaredLength ? ToOther.LengthSqr() : ToOther.Length();

        return LessOperator( DistanceToOther + _Other.m_Radius, m_Radius );
    }

    Bool Sphere::Contains( const Vector3& _Point, Bool _WithBoundaries, Bool _UseSquaredLength ) const
    {
        // If we have to take boundaries into account use '<=' otherwise, use '<'.
        bool( *LessOperator )( float, float ) = _WithBoundaries ? &islessequal<float, float> : &isless<float, float>;

        const Vector3 ToPoint( _Point - m_Center );
        const float DistanceToPoint = _UseSquaredLength ? ToPoint.LengthSqr() : ToPoint.Length();

        return LessOperator( DistanceToPoint, m_Radius );
    }
} // ae

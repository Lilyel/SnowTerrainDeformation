#include "Transform.h"

#include "../../Editor/TypesToEditor/TransformToEditor.h"

namespace ae
{
    Transform::Transform() :
        m_Position( 0.0f, 0.0f, 0.0f ),
        m_Scale( 1.0f, 1.0f, 1.0f ),
        m_Pivot( 0.0f, 0.0f, 0.0f ),
        m_UpdateTransform( False ),
        m_Transform( Matrix4x4::Identity )
    {
    }
    Transform::Transform( const Vector3& _Position ) :
        m_Position( _Position ),
        m_Scale( 1.0f, 1.0f, 1.0f ),
        m_Pivot( 0.0f, 0.0f, 0.0f ),
        m_UpdateTransform( True ),
        m_Transform( Matrix4x4::Identity )
    {
    }
    Transform::Transform( const Vector3& _Position, const Rotator& _Rotation, const Vector3& _Scale ) :
        m_Position( _Position ),
        m_Rotation( _Rotation ),
        m_Scale( _Scale ),
        m_Pivot( 0.0f, 0.0f, 0.0f ),
        m_UpdateTransform( True ),
        m_Transform( Matrix4x4::Identity )
    {
    }

    /// TRANSLATION

    void Transform::SetPosition( float _X, float _Y, float _Z )
    {
        m_Position.X = _X;
        m_Position.Y = _Y;
        m_Position.Z = _Z;

        m_UpdateTransform = True;
        OnTransformChanged();
    }
    void Transform::SetPosition( const Vector3& _Position )
    {
        m_Position = _Position;

        m_UpdateTransform = True;
        OnTransformChanged();
    }
    const Vector3& Transform::GetPosition() const
    {
        return m_Position;
    }
    void Transform::Translate( const Vector3& _Offset )
    {
        m_Position += _Offset;

        m_UpdateTransform = True;
        OnTransformChanged();
    }
    void Transform::Translate( float _X, float _Y, float _Z )
    {
        m_Position.X += _X;
        m_Position.Y += _Y;
        m_Position.Z += _Z;

        m_UpdateTransform = True;
        OnTransformChanged();
    }

    /// ROTATION

    void Transform::SetRotation( float _Pitch, float _Yaw, float _Roll )
    {
        m_Rotation.SetEulerAngles( Vector3( _Pitch, _Yaw, _Roll ) );

        m_UpdateTransform = True;
        OnTransformChanged();
    }
    void Transform::SetRotation( const Vector3& _Angles )
    {
        m_Rotation.SetEulerAngles( _Angles );

        m_UpdateTransform = True;
        OnTransformChanged();
    }
    void Transform::SetRotation( const Rotator& _Rotation )
    {
        m_Rotation = _Rotation;

        m_UpdateTransform = True;
        OnTransformChanged();
    }
    const Vector3& Transform::GetRotationAngles() const
    {
        return m_Rotation.GetEulerAngles();
    }
    const Rotator& Transform::GetRotation() const
    {
        return m_Rotation;
    }
    void Transform::Rotate( float _Pitch, float _Yaw, float _Roll )
    {
        m_Rotation.Pitch( _Pitch );
        m_Rotation.Yaw( _Yaw );
        m_Rotation.Roll( _Roll );

        m_UpdateTransform = True;
        OnTransformChanged();
    }
    void Transform::Rotate( const ae::Vector3& _Angles )
    {
        m_Rotation.Yaw( _Angles.X );
        m_Rotation.Pitch( _Angles.Y );
        m_Rotation.Roll( _Angles.Z );

        m_UpdateTransform = True;
        OnTransformChanged();
    }
    void Transform::Rotate( const Rotator& _Rotation )
    {
        m_Rotation = Rotator::Combine( _Rotation, m_Rotation );

        m_UpdateTransform = True;
        OnTransformChanged();
    }

    /// SCALE

    void Transform::SetScale( float _X, float _Y, float _Z )
    {
        m_Scale.X = _X;
        m_Scale.Y = _Y;
        m_Scale.Z = _Z;

        m_UpdateTransform = True;
        OnTransformChanged();
    }
    void Transform::SetScale( const Vector3& _Scale )
    {
        m_Scale = _Scale;

        m_UpdateTransform = True;
        OnTransformChanged();
    }
    const Vector3& Transform::GetScale() const
    {
        return m_Scale;
    }
    void Transform::Scale( float _X, float _Y, float _Z )
    {
        m_Scale.X *= _X;
        m_Scale.Y *= _Y;
        m_Scale.Z *= _Z;

        m_UpdateTransform = True;
        OnTransformChanged();
    }
    void Transform::Scale( const Vector3& _Scale )
    {
        m_Scale *= _Scale;

        m_UpdateTransform = True;
        OnTransformChanged();
    }

    /// UTILITIES

    void Transform::Combine( const Transform& _Other )
    {
        m_Position += _Other.m_Position;
        m_Rotation = std::move( Rotator::Combine( _Other.m_Rotation, m_Rotation ) );
        m_Scale *= _Other.m_Scale;

        m_UpdateTransform = True;
        OnTransformChanged();
    }
    Transform Transform::Combine( const Transform& _Transform1, const Transform& _Transform2 )
    {
        Transform Result;

        Result.SetPosition( _Transform1.m_Position + _Transform2.m_Position );

        const Rotator&& TotalRotation = std::move( Rotator::Combine( _Transform1.m_Rotation, _Transform2.m_Rotation ) );
        Result.SetRotation( TotalRotation );

        Result.SetScale( _Transform1.m_Scale * _Transform2.m_Scale );

        return Result;
    }
    void Transform::Combine( const Transform& _Transform1, const Transform& _Transform2, Transform& _Result )
    {
        _Result.SetPosition( _Transform1.m_Position + _Transform2.m_Position );

        const Rotator&& TotalRotation = std::move( Rotator::Combine( _Transform1.m_Rotation, _Transform2.m_Rotation ) );
        _Result.SetRotation( TotalRotation );

        _Result.SetScale( _Transform1.m_Scale * _Transform2.m_Scale );
    }


    void Transform::ToEditor()
    {
        priv::ui::TransformToEditor( *this );
    }


    void Transform::UpdateTransform()
    {
        if( !m_UpdateTransform )
            return;

        m_Transform = std::move( GetUpdatedMatrix() );

        m_UpdateTransform = False;
        OnTransformUpdated();
    }

    void Transform::OnTransformUpdated()
    {
        // To fill in subclasses if needed.
    }

    void Transform::OnTransformChanged()
    {
        // To fill in subclasses if needed.
    }

    const Matrix4x4& Transform::GetMatrix()
    {
        UpdateTransform();

        return m_Transform;
    }

    Matrix4x4 Transform::GetUpdatedMatrix()
    {
        Matrix4x4 Result( Matrix4x4::Identity );
        Result *= Matrix4x4::GetTranslationMatrix( m_Pivot );
        Result *= m_Rotation.GetMatrix();
        Result *= Matrix4x4::GetScaleMatrix( m_Scale );
        Result *= Matrix4x4::GetTranslationMatrix( -m_Pivot );
        Result.Translate( m_Position );

        return Result;
    }

    Matrix4x4 Transform::GetInversedMatrix()
    {
        UpdateTransform();

        return std::move( m_Transform.GetInverse() );
    }

    Matrix4x4 Transform::GetTransposedMatrix()
    {
        UpdateTransform();

        return std::move( m_Transform.GetTranspose() );
    }

    Vector3 Transform::GetForward()
    {
        return m_Rotation.GetForward();
    }
    Vector3 Transform::GetLeft()
    {
        return m_Rotation.GetLeft();
    }
    Vector3 Transform::GetUp()
    {
        return m_Rotation.GetUp();
    }

    void Transform::SetPivot( const Vector3& _Pivot )
    {
        m_Pivot = _Pivot;

        m_UpdateTransform = True;
        OnTransformChanged();
    }

    const Vector3& Transform::GetPivot()
    {
        UpdateTransform();

        return m_Pivot;
    }

    std::string ToString( const Transform& _Transform )
    {
        std::string AsString = "";
        AsString += "t: " + std::to_string( _Transform.GetPosition().X ) + " " + std::to_string( _Transform.GetPosition().Y ) + " " + std::to_string( _Transform.GetPosition().Z ) + "\n";
        AsString += "r: " + std::to_string( _Transform.GetRotationAngles().X ) + " " + std::to_string( _Transform.GetRotationAngles().Y ) + " " + std::to_string( _Transform.GetRotationAngles().Z ) + "\n";
        AsString += "s: " + std::to_string( _Transform.GetScale().X ) + " " + std::to_string( _Transform.GetScale().Y ) + " " + std::to_string( _Transform.GetScale().Z ) + "\n";

        return AsString;
    }

} // ae

std::ostream& operator<<( std::ostream& os, const ae::Transform& _Transform )
{
    os << ae::ToString( _Transform );

    return os;
}

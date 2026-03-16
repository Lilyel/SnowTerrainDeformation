#include "Transform2D.h"

#include "../../Editor/TypesToEditor/Transform2DToEditor.h"

namespace ae
{

	Transform2D::Transform2D( const Vector2& _Position, float _Rotation, const Vector2& _Scale ) :
		m_Position( _Position ),
		m_Scale( _Scale ),
		m_Rotation( _Rotation ),
		m_Origin( 0.0f, 0.0f ),
		m_Transform( MatrixInitMode::Identity ),
		m_UpdateTransform( True )
	{
	}

	Transform2D& Transform2D::SetPosition( const Vector2& _Position )
	{
		m_Position = _Position;

		m_UpdateTransform = True;
		OnTransformChanged();

		return *this;
	}

	Transform2D& Transform2D::SetPosition( float _X, float _Y )
	{
		m_Position.X = _X;
		m_Position.Y = _Y;

		m_UpdateTransform = True;
		OnTransformChanged();

		return *this;
	}

	Transform2D& Transform2D::Translate( const Vector2& _Offset )
	{
		m_Position += _Offset;
		
		m_UpdateTransform = True;
		OnTransformChanged();

		return *this;
	}

	Transform2D& Transform2D::Translate( float _OffsetX, float _OffsetY )
	{
		m_Position.X += _OffsetX;
		m_Position.Y += _OffsetY;

		m_UpdateTransform = True;
		OnTransformChanged();

		return *this;
	}

	const Vector2& Transform2D::GetPosition() const
	{
		return m_Position;
	}

	Transform2D& Transform2D::SetRotation( float _Angle )
	{
		m_Rotation = _Angle;

		m_UpdateTransform = True;
		OnTransformChanged();

		return *this;
	}

	Transform2D& Transform2D::Rotate( float _Angle )
	{
		m_Rotation += _Angle;

		m_UpdateTransform = True;
		OnTransformChanged();

		return *this;
	}

	float Transform2D::GetRotation() const
	{
		return m_Rotation;
	}

	Transform2D& Transform2D::SetScale( const Vector2& _Scale )
	{
		m_Scale = _Scale;

		m_UpdateTransform = True;
		OnTransformChanged();

		return *this;
	}

	Transform2D& Transform2D::SetScale( float _ScaleX, float _ScaleY )
	{
		m_Scale.X = _ScaleX;
		m_Scale.Y = _ScaleY;

		m_UpdateTransform = True;
		OnTransformChanged();

		return *this;
	}

	Transform2D& Transform2D::Scale( const Vector2& _Scale )
	{
		m_Scale *= _Scale;

		m_UpdateTransform = True;
		OnTransformChanged();

		return *this;
	}

	Transform2D& Transform2D::Scale( float _ScaleX, float _ScaleY )
	{
		m_Scale.X *= _ScaleX;
		m_Scale.Y *= _ScaleY;

		m_UpdateTransform = True;
		OnTransformChanged();

		return *this;
	}

	const Vector2& Transform2D::GetScale() const
	{
		return m_Scale;
	}

	Transform2D& Transform2D::SetOrigin( const Vector2& _Origin )
	{
		m_Origin = _Origin;

		m_UpdateTransform = True;
		OnTransformChanged();

		return *this;
	}

	Transform2D& Transform2D::SetOrigin( float _OriginX, float _OriginY )
	{
		m_Origin.X = _OriginX;
		m_Origin.Y = _OriginY;

		m_UpdateTransform = True;
		OnTransformChanged();

		return *this;
	}

	const Vector2& Transform2D::GetOrigin() const
	{
		return m_Origin;
	}

	void Transform2D::Combine( const Transform2D& _Other )
	{
		m_Position += _Other.m_Position;
		m_Rotation += _Other.m_Rotation;
		m_Scale *= _Other.m_Scale;

		m_UpdateTransform = True;
		OnTransformChanged();
	}

	Transform2D Transform2D::Combine( const Transform2D& _TransformA, const Transform2D& _TransformB )
	{
		Transform2D Result
		{
			_TransformA.m_Position + _TransformB.m_Position,
			_TransformA.m_Rotation + _TransformB.m_Rotation,
			_TransformA.m_Scale * _TransformB.m_Scale
		};

		Result.SetOrigin( _TransformA.m_Origin );

		return Result;
	}

	void Transform2D::Combine( AE_Out Transform2D& _Result, const Transform2D& _TransformA, const Transform2D& _TransformB )
	{
		_Result.SetPosition( _TransformA.m_Position + _TransformB.m_Position );
		_Result.SetRotation( _TransformA.m_Rotation + _TransformB.m_Rotation );
		_Result.SetScale( _TransformA.m_Scale * _TransformB.m_Scale );
		_Result.SetOrigin( _TransformA.m_Origin );
	}

	Vector2 Transform2D::TransformPoint( const Vector2& _Point )
	{
		const Matrix3x3& TransformMatrix = GetMatrix();

		Vector2 Result = _Point;
		TransformMatrix.TransformPoint( Result );

		return Result;
	}

	void Transform2D::TransformPoint( AE_InOut Vector2& _Point )
	{
		const Matrix3x3& TransformMatrix = GetMatrix();

		TransformMatrix.TransformPoint( _Point );
	}

	const Matrix3x3& Transform2D::GetMatrix()
	{
		if( m_UpdateTransform )
			UpdateTransform();

		return m_Transform;
	}

	Matrix3x3 Transform2D::GetUpdatedMatrix()
	{
		if( m_UpdateTransform )
			UpdateTransform();

		return Matrix3x3( m_Transform );
	}

	Matrix3x3 Transform2D::GetInversedMatrix()
	{
		if( m_UpdateTransform )
			UpdateTransform();

		return m_Transform.GetInverse();
	}

	Matrix3x3 Transform2D::GetTransposedMatrix()
	{
		if( m_UpdateTransform )
			UpdateTransform();

		return m_Transform.GetTranspose();
	}


    void Transform2D::ToEditor()
    {
        priv::ui::TransformToEditor( *this );
    }


    void Transform2D::UpdateTransform()
	{
		// https://stackoverflow.com/questions/27698778/create-a-2d-transformation-matrix-with-rotation-origin

		m_Transform.SetToIdentity();

		m_Transform.Rotate( m_Rotation );
		m_Transform.Scale( m_Scale );

		const Vector2 PositionWithOrigin
		{
			-m_Origin.X * m_Transform( 0, 0 ) - m_Origin.Y * m_Transform( 0, 1 ) + m_Position.X,
			m_Origin.X * -m_Transform( 1, 0 ) - m_Origin.Y * m_Transform( 1, 1 ) + m_Position.Y
		};

		m_Transform.Translate( PositionWithOrigin );



		m_UpdateTransform = False;
		OnTransformUpdated();
	}

	void Transform2D::OnTransformUpdated()
	{
		// To fill in subclasses if needed.
	}

	void Transform2D::OnTransformChanged()
	{
		// To fill in subclasses if needed.
	}

	std::string ToString( const Transform2D& _Transform2D )
	{
		std::string AsString = "";
		AsString += "t: " + std::to_string( _Transform2D.GetPosition().X ) + " " + std::to_string( _Transform2D.GetPosition().Y ) + "\n";
		AsString += "r: " + std::to_string( _Transform2D.GetRotation() ) + "\n";
		AsString += "s: " + std::to_string( _Transform2D.GetScale().X ) + " " + std::to_string( _Transform2D.GetScale().Y ) + "\n";

		return AsString;
	}

} //ae

std::ostream& operator<<( std::ostream& os, const ae::Transform2D& _Transform2D )
{
	os << ae::ToString( _Transform2D );

	return os;
}

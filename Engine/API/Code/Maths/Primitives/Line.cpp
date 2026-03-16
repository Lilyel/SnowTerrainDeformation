#include "Line.h"

namespace ae
{

	Line::Line() :
		m_A( Vector3::Zero ),
		m_B( Vector3::Zero )
	{
	}

	Line::Line( const Vector3& _A, const Vector3& _B ) :
		m_A( _A ),
		m_B( _B )
	{
	}

	Line::Line( const std::array<Vector3, 2>& _Array ) :
		m_A( _Array[0] ),
		m_B( _Array[0] )
	{
	}

	Vector3 Line::GetDirection() const
	{
		return Vector3( m_A, m_B ).Normalize();
	}

	const Vector3& Line::GetFirstPoint() const
	{
		return m_A;
	}

	void Line::SetFirstPoint( const Vector3& _Point )
	{
		m_A = _Point;
	}

	const Vector3& Line::GetSecondPoint() const
	{
		return m_B;
	}

	void Line::SetSecondPoint( const Vector3& _Point )
	{
		m_B = _Point;
	}


} // ae


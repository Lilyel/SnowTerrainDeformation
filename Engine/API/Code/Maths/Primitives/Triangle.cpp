#include "Triangle.h"

#include "Line.h"
#include "../Functions/MathsFunctions.h"


namespace ae
{
	Triangle::Triangle() :
		m_A( Vector3::Zero ),
		m_B( Vector3::Zero ),
		m_C( Vector3::Zero )
	{
	}

	Triangle::Triangle( const Vector3& _A, const Vector3& _B, const Vector3& _C ) :
		m_A( _A ),
		m_B( _B ),
		m_C( _C )
	{
	}
	Triangle::Triangle( const std::array<Vector3, 3>& _Array ) :
		m_A( _Array[0] ),
		m_B( _Array[1] ),
		m_C( _Array[2] )
	{
	}

	Vector3 Triangle::GetNormal( Bool _Normalized ) const
	{
		const Vector3 AB( m_A, m_B );
		const Vector3 AC( m_A, m_C );

		if( _Normalized )
			return AB.Cross( AC ).Normalize();
		else
			return AB.Cross( AC );
	}

	const Vector3& Triangle::GetFirstPoint() const
	{
		return m_A;
	}

	void Triangle::SetFirstPoint( const Vector3& _Point )
	{
		m_A = _Point;
	}

	const Vector3& Triangle::GetSecondPoint() const
	{
		return m_B;
	}

	void Triangle::SetSecondPoint( const Vector3& _Point )
	{
		m_B = _Point;
	}

	const Vector3& Triangle::GetThirdPoint() const
	{
		return m_C;
	}

	void Triangle::SetThirdPoint( const Vector3& _Point )
	{
		m_C = _Point;
	}

	const Vector3& Triangle::operator[]( Uint32 _Index ) const
	{
		if( _Index > 2 )
			throw std::out_of_range( "Invalid index. Triangle point index must be 0, 1 or 2." );

		return _Index == 0 ? m_A : ( _Index == 1 ? m_B : m_C );
	}

	Vector3& Triangle::operator[]( Uint32 _Index )
	{
		if( _Index > 2 )
			throw std::out_of_range( "Invalid index. Triangle point index must be 0, 1 or 2." );

		return _Index == 0 ? m_A : ( _Index == 1 ? m_B : m_C );
	}

	void Triangle::BarycentricCoordinates( float& _OutU, float& _OutV, float& _OutW, const Vector3& _P ) const
	{
		const Vector3 AB( m_A, m_B );
		const Vector3 BC( m_B, m_C );
		const Vector3 AC( m_A, m_C );

		const Vector3 PB( _P, m_B );
		const Vector3 PC( _P, m_C );

		const Vector3 NormalNotNormalized = AB.Cross( BC );
		const float Areax2 = NormalNotNormalized.Length(); // Area of the triangle x2.
		const Vector3 Normal = NormalNotNormalized / Areax2;

		// If area null, avoid division by 0. 
		if( Math::IsNullByEpsilon( Areax2 ) )
		{
			_OutU = 0.0f;
			_OutV = 0.0f;
			_OutW = 0.0f;
		}
		else
		{
			_OutU = BC.Cross( PB ).Dot( Normal ) / Areax2;
			_OutV = AC.Cross( PC ).Dot( Normal ) / Areax2;
			_OutW = 1.0f - _OutU - _OutV;
		}
	}

	Vector3 Triangle::GetPointFromBarycentricCoordinates( float _U, float _V, float _W ) const
	{
		return m_A * _U + m_B * _V + m_C * _W;
	}


	Bool Triangle::Intersects( float& _OutU, float& _OutV, float& _OutW, const Line& _Line ) const
	{
		Vector3 Hit;

		if( MollerTrumboreIntersection( Hit, _OutU, _OutV, _Line ) )
		{
			_OutW = 1.0f - _OutU - _OutV;
			return True;
		}	

		return False;
	}

	Bool Triangle::Intersects( Vector3& _OutHitPoint, float& _OutU, float& _OutV, float& _OutW, const Line& _Line ) const
	{
		if( MollerTrumboreIntersection( _OutHitPoint, _OutU, _OutV, _Line ) )
		{
			_OutW = 1.0f - _OutU - _OutV;
			return True;
		}

		return False;
	}

	Bool Triangle::Intersects( Vector3& _OutHitPoint, const Line& _Line ) const
	{
		float U = 0.0f;
		float V = 0.0f;

		return MollerTrumboreIntersection( _OutHitPoint, U, V, _Line );
	}

	Bool Triangle::Intersects( const Line& _Line ) const
	{
		float U = 0.0f;
		float V = 0.0f;
		Vector3 Hit;

		return MollerTrumboreIntersection( Hit, U, V, _Line );
	}

	Bool Triangle::MollerTrumboreIntersection( Vector3& _OutHitPoint, float& _OutU, float& _OutV, const Line& _Line, bool _HandleParallel ) const
	{
		// Möller–Trumbore intersection algorithm
		// Ref : https://www.tandfonline.com/doi/abs/10.1080/10867651.1997.10487468
		// PDF : https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
		// Wiki : https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

		constexpr float Epsilon = Math::Epsilon();

		const Vector3 AB( m_A, m_B );
		const Vector3 AC( m_A, m_C );

		const Vector3&& Direction = _Line.GetDirection();
		const Vector3& Start = _Line.GetFirstPoint();

		const Vector3 P = Direction.Cross( AC );
		const float Determinent = AB.Dot( P );

		if( _HandleParallel )
		{
			if( Determinent < Epsilon )
				return False;

			const Vector3 AToStart( m_A, Start );

			// Barycentric coordinate U.
			_OutU = AToStart.Dot( P );

			// Test bounds with U.
			if( _OutU < 0.0f || _OutU > Determinent )
				return False;

			const Vector3 Q = AToStart.Cross( AC );

			// Barycentric coordinate V.
			_OutV = Direction.Dot( Q );

			// Test bounds with V.
			if( _OutV < 0.0f || ( _OutU + _OutV ) > Determinent )
				return False;

			// Scale.
			const float InverseDeterminent = 1.0f / Determinent;


			const float ParametricPosition = AC.Dot( Q ) * InverseDeterminent;
			_OutU *= InverseDeterminent;
			_OutV *= InverseDeterminent;

			_OutHitPoint = Start + Direction * ParametricPosition;
		}
		else
		{
			// Ray lies in the plane of the triangle.
			if( Math::IsNullByEpsilon( Determinent ) )
				return False;

			const float InverseDeterminent = 1.0f / Determinent;

			const Vector3 AToStart( m_A, Start );

			// Barycentric coordinate U.
			_OutU = AToStart.Dot( P ) * InverseDeterminent;

			// Test bounds with U.
			if( _OutU < 0.0f || _OutU > 1.0f )
				return False;

			const Vector3 Q = AToStart.Cross( AC );

			// Barycentric coordinate V.
			_OutV = Direction.Dot( Q ) * InverseDeterminent;

			// Test bounds with V.
			if( _OutV < 0.0f || ( _OutU + _OutV ) > 1.0f )
				return False;

			const float ParametricPosition = AC.Dot( Q ) * InverseDeterminent;

			_OutHitPoint = Start + Direction * ParametricPosition;
		}

		return True;
	}

} // ae

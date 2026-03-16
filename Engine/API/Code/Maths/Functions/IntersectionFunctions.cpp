#include "IntersectionFunctions.h"

#include "MathsFunctions.h"

namespace ae
{
	namespace Intersections
	{

		Bool LinePlane( Vector3& _OutIntersection, const Vector3& _LinePoint, const Vector3& _LineDirection,
						const Vector3& _PlanePosition, const Vector3& _PlaneNormal )
		{
			// https://stackoverflow.com/a/52711312/10466566

			const Vector3&& Direction = _LineDirection.GetNormalized();

			// If the line is parallel to the plane, there is not possible intersection.
			if( Math::IsNullByEpsilon( _PlaneNormal.Dot( Direction ) ) )
				return False;

			float ParametricPosition = _PlaneNormal.Dot( _PlanePosition ) - _PlaneNormal.Dot( _LinePoint );
			ParametricPosition /= _PlaneNormal.Dot( Direction );

			_OutIntersection = _LinePoint + Direction * ParametricPosition;

			return True;
		}

		Bool LineTriangle( Vector3& _OutIntersection, const Vector3& _LinePoint, const Vector3& _LineDirection,
						   const Vector3& _TriA, const Vector3& _TriB, const Vector3& _TriC )
		{
			float U = 0.0f;
			float V = 0.0f;
			return LineTriangle( _OutIntersection, U, V, _LinePoint, _LineDirection, _TriA, _TriB, _TriC );
		}

		Bool LineTriangle( Vector3& _OutIntersection, float& _OutU, float& _OutV,
						   const Vector3& _LinePoint, const Vector3& _LineDirection,
						   const Vector3& _TriA, const Vector3& _TriB, const Vector3& _TriC )
		{
			const Vector3 LineToA( _LinePoint, _TriA );
			const Vector3 LineToB( _LinePoint, _TriB );
			const Vector3 LineToC( _LinePoint, _TriC );

			_OutU = _LineDirection.ScalarTriple( LineToC, LineToB );
			if( _OutU < 0.0f )
				return False;

			_OutV = _LineDirection.ScalarTriple( LineToA, LineToC );
			if( _OutV < 0.0f )
				return False;

			float W = _LineDirection.ScalarTriple( LineToB, LineToA );
			if( W < 0.0f )
				return False;

			float Denom = _OutU + _OutV + W;

			// Avoid division by 0.
			if( Math::IsNullByEpsilon( Denom ) )
				return False;


			Denom = 1.0f / Denom;

			_OutU *= Denom;
			_OutV *= Denom;
			W *= Denom;

			_OutIntersection = _OutU * _TriA + _OutV * _TriB + W * _TriC;

			return True;
		}

		Bool RayTriangle( Vector3& _OutIntersection, const Vector3& _RayPoint, const Vector3& _RayDirection,
						  const Vector3& _TriA, const Vector3& _TriB, const Vector3& _TriC, Bool _HandleParallel )
		{
			float U = 0.0f;
			float V = 0.0f;
			return RayTriangle( _OutIntersection, U, V, _RayPoint, _RayDirection, _TriA, _TriB, _TriC, _HandleParallel );
		}

		Bool RayTriangle( Vector3& _OutIntersection, float& _OutU, float& _OutV,
						  const Vector3& _RayPoint, const Vector3& _RayDirection,
						  const Vector3& _TriA, const Vector3& _TriB, const Vector3& _TriC, Bool _HandleParallel )
		{
			// Möller–Trumbore intersection algorithm
			// Ref : https://www.tandfonline.com/doi/abs/10.1080/10867651.1997.10487468
			// PDF : https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
			// Wiki : https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

			constexpr float Epsilon = Math::Epsilon();

			const Vector3 AB( _TriA, _TriB );
			const Vector3 AC( _TriA, _TriC );

			const Vector3&& Direction = _RayDirection.GetNormalized();

			const Vector3 P = Direction.Cross( AC );
			const float Determinent = AB.Dot( P );

			if( _HandleParallel )
			{
				if( Determinent < Epsilon )
					return False;

				const Vector3 AToStart( _TriA, _RayPoint );

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

				_OutIntersection = _RayPoint + Direction * ParametricPosition;
			}
			else
			{
				// Ray lies in the plane of the triangle.
				if( Math::IsNullByEpsilon( Determinent ) )
					return False;

				const float InverseDeterminent = 1.0f / Determinent;

				const Vector3 AToStart( _TriA, _RayPoint );

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

				_OutIntersection = _RayPoint + Direction * ParametricPosition;
			}

			return True;
		}

		Bool MovingSpherePlane( float& _OutTime, Vector3& _OutSphereCenterWhenIntersects,
								const Vector3& _SphereCenter, float _SphereRadius, const Vector3& _SphereVelocity,
								const Vector3& _PlanePosition, const Vector3& _PlaneNormal )
		{
			// See Real-Time Collision Detection, Christer Ericson, 5.5.3 Intersecting Moving Sphere Against Plane, p219

			const float DistanceSpherePlane = _PlaneNormal.Dot( _SphereCenter - _PlanePosition );

			// The sphere is already intersecting the plane.
			if( Math::Abs( DistanceSpherePlane ) <= _SphereRadius )
			{
				_OutTime = 0.0f;
				_OutSphereCenterWhenIntersects = _SphereCenter;
				return True;
			}

			const float Denom = _PlaneNormal.Dot( _SphereVelocity );

			// The sphere is moving parallel to or away from the plane, no possible intersection.
			if( Denom * DistanceSpherePlane >= 0.0f )
				return False;

			// Otherwise the sphere is moving forward the plane.

			// Use +Radius if the sphere is in front of the plane, -Radius otherwise.
			const float SignedRadius = DistanceSpherePlane > 0.0f ? _SphereRadius : -_SphereRadius;

			_OutTime = ( SignedRadius - DistanceSpherePlane ) / Denom;
			_OutSphereCenterWhenIntersects = _SphereCenter + _OutTime * _SphereVelocity - SignedRadius * _PlaneNormal;

			return True;
		}

	} // Intersections
} // ae

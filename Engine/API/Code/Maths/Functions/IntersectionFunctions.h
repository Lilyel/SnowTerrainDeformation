#pragma once

#include "../../Toolbox/Toolbox.h"

#include "../Vector/Vector3.h"

namespace ae
{
	namespace Intersections
	{
		/// <summary>Compute the intersection point between a line and a plane.</summary>
		/// <param name="_OutIntersection"/>Position of the intersection. Stay unchanged if there is no intersection.<param/>
		/// <param name="_LinePoint"/>A point on the line.<param/>
		/// <param name="_LineDirection"/>Direction of the line.<param/>
		/// <param name="_PlanePosition"/>A point on the plane.<param/>
		/// <param name="_PlaneNormal"/>Normal of the plane. Assumed to be normalized.<param/>
		/// <returns>True if there is an intersection, false otherwise.</returns>
		Bool LinePlane( Vector3& _OutIntersection, const Vector3& _LinePoint, const Vector3& _LineDirection,
						const Vector3& _PlanePosition, const Vector3& _PlaneNormal );

		/// <summary>Compute the intersection point between a line and a triangle.</summary>
		/// <param name="_LinePoint"/>A point on the line.<param/>
		/// <param name="_LineDirection"/>Direction of the line.<param/>
		/// <param name="_TriA">First point of the triangle.</param>
		/// <param name="_TriB">Second point of the triangle.</param>
		/// <param name="_TriC">Third point of the triangle.</param>
		Bool LineTriangle( Vector3& _OutIntersection, const Vector3& _LinePoint, const Vector3& _LineDirection,
						   const Vector3& _TriA, const Vector3& _TriB, const Vector3& _TriC );

		/// <summary>Compute the intersection point between a line and a triangle.</summary>
		/// <param name="_OutU">
		/// The weight of the first point of the triangle on the intersection point.<para/>
		/// Stay unchanged if there is no intersection.
		/// </param>
		/// <param name="_OutV">
		/// The weight of the second point of the triangle on the intersection point.<para/>
		/// Stay unchanged if there is no intersection.
		/// </param>
		/// <param name="_LinePoint"/>A point on the line.<param/>
		/// <param name="_LineDirection"/>Direction of the line.<param/>
		/// <param name="_TriA">First point of the triangle.</param>
		/// <param name="_TriB">Second point of the triangle.</param>
		/// <param name="_TriC">Third point of the triangle.</param>
		Bool LineTriangle( Vector3& _OutIntersection, float& _OutU, float& _OutV, 
						   const Vector3& _LinePoint, const Vector3& _LineDirection,
						   const Vector3& _TriA, const Vector3& _TriB, const Vector3& _TriC );

		/// <summary>
		/// Compute the intersection between the calling triangle and the ray defined by <paramref name="_Line"/>.<para/>
		/// The ray start is the first point on the line and the ray direction is the line direction.
		/// </summary>
		/// <param name="_OutIntersection"/>Position of the intersection. Stay unchanged if there is no intersection.<param/>
		/// <param name="_RayPoint"/>A point on the line.<param/>
		/// <param name="_RayDirection"/>Direction of the line.<param/>
		/// <param name="_TriA">First point of the triangle.</param>
		/// <param name="_TriB">Second point of the triangle.</param>
		/// <param name="_TriC">Third point of the triangle.</param>
		/// <param name="_HandleParallel">
		/// Do the algorithm handle the case where the ray lies in the plane of the triange ?<para/>
		/// If it is handled, the algorithm may be a bit slower.
		/// </param>
		/// <returns>True if there is an intersection, false otherwise.</returns>
		Bool RayTriangle( Vector3& _OutIntersection, const Vector3& _RayPoint, const Vector3& _RayDirection,
						  const Vector3& _TriA, const Vector3& _TriB, const Vector3& _TriC, Bool _HandleParallel = True );


		/// <summary>
		/// Compute the intersection between the calling triangle and the ray defined by <paramref name="_Line"/>.<para/>
		/// The ray start is the first point on the line and the ray direction is the line direction.
		/// </summary>
		/// <param name="_OutIntersection"/>Position of the intersection. Stay unchanged if there is no intersection.<param/>
		/// <param name="_OutU">
		/// The weight of the first point of the triangle on the intersection point.<para/>
		/// Stay unchanged if there is no intersection.
		/// </param>
		/// <param name="_OutV">
		/// The weight of the second point of the triangle on the intersection point.<para/>
		/// Stay unchanged if there is no intersection.
		/// </param>
		/// <param name="_RayPoint"/>A point on the line.<param/>
		/// <param name="_RayDirection"/>Direction of the line.<param/>
		/// <param name="_TriA">First point of the triangle.</param>
		/// <param name="_TriB">Second point of the triangle.</param>
		/// <param name="_TriC">Third point of the triangle.</param>
		/// <param name="_HandleParallel">
		/// Do the algorithm handle the case where the ray lies in the plane of the triange ?<para/>
		/// If it is handled, the algorithm may be a bit slower.
		/// </param>
		/// <returns>True if there is an intersection, false otherwise.</returns>
		Bool RayTriangle( Vector3& _OutIntersection, float& _OutU, float& _OutV,
						  const Vector3& _RayPoint, const Vector3& _RayDirection,
						  const Vector3& _TriA, const Vector3& _TriB, const Vector3& _TriC, Bool _HandleParallel = True );


		/// <summary>Compute the intersection between a moving sphere and a plane.</summary>
		/// <param name="_OutTime">
		/// Parametric distance until the intersection. <para/>
		/// Real distance can be computed as : <paramref name="_OutTime"/> * <paramref name="_SphereVelocity"/>.
		/// </param>
		/// <param name="_OutSphereCenterWhenIntersects">Intersection point between the sphere and the plane at time <paramref name="_OutTime"/></param>
		/// <param name="_SphereCenter">Position of the sphere</param>
		/// <param name="_SphereRadius">Radius of the sphere.</param>
		/// <param name="_SphereVelocity">Velocity of the sphere.</param>
		/// <param name="_PlanePosition"/>A point on the plane.<param/>
		/// <param name="_PlaneNormal"/>Normal of the plane. Assumed to be normalized.<param/>
		Bool MovingSpherePlane( float& _OutTime, Vector3& _OutSphereCenterWhenIntersects,
								const Vector3& _SphereCenter, float _SphereRadius, const Vector3& _SphereVelocity,
								const Vector3& _PlanePosition, const Vector3& _PlaneNormal );

	} // Intersections
} // ae

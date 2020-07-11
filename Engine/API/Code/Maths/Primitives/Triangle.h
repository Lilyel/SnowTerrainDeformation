#pragma once


#include "../../Toolbox/Toolbox.h"
#include "../Vector/Vector3.h"

#include <array>

namespace ae
{
	class Line;

	/// \ingroup math
	/// <summary>
	/// 3D triangle represented by 3 points.
	/// </summary>
	class AERO_CORE_EXPORT Triangle
	{
	public:
		/// <summary>Default constructor. All points are set to zero.</summary>
		Triangle();

		/// <summary>Build the triangle with 3 points.</summary>
		/// <param name="_A">The first point of the triangle.</param>
		/// <param name="_B">The second point of the triangle.</param>
		/// <param name="_C">The third point of the triangle.</param>
		Triangle( const Vector3& _A, const Vector3& _B, const Vector3& _C );

		/// <summary>Build the triangle with the content of the <paramref name="_Array"/>.</summary>
		/// <param name="_Array">Array containing the 3 points to build the triangle with.</param>
		Triangle( const std::array<Vector3, 3> & _Array );

		/// <summary>Compute the normal of the triangle.</summary>
		/// <param name="_Normalized">If true, the returned normal will be normalized.</param>
		/// <returns>The normal of the triangle.</returns>
		Vector3 GetNormal( Bool _Normalized = True ) const;

		/// <summary>Retrieve the first point of the triangle.</summary>
		/// <returns>The first point of the triangle.</returns>
		const Vector3& GetFirstPoint() const;

		/// <summary>Set the first point of the triangle.</summary>
		/// <param name="_Point">The new position for the first point of the triangle.</param>
		void SetFirstPoint( const Vector3& _Point );

		/// <summary>Retrieve the second point of the triangle.</summary>
		/// <returns>The second point of the triangle.</returns>
		const Vector3& GetSecondPoint() const;

		/// <summary>Set the second point of the triangle.</summary>
		/// <param name="_Point">The new position for the second point of the triangle.</param>
		void SetSecondPoint( const Vector3& _Point );

		/// <summary>Retrieve the third point of the triangle.</summary>
		/// <returns>The third point of the triangle.</returns>
		const Vector3& GetThirdPoint() const;

		/// <summary>Set the third point of the triangle.</summary>
		/// <param name="_Point">The new position for the third point of the triangle.</param>
		void SetThirdPoint( const Vector3& _Point );

		/// <summary>Retrieve a point of the triangle.</summary>
		/// <param name="_Index">
		/// 0 : The first point of the triangle.<para/>
		/// 1 : The second point of the triangle.<para/>
		/// 2 : The third point of the triangle.<para/>
		/// Other indices raise an out of range exception.
		/// </param>
		/// <returns>The point of the triangle corresponding to the <paramref name="_Index"/></returns>
		const Vector3& operator[]( Uint32 _Index ) const;

		/// <summary>Retrieve a point of the triangle.</summary>
		/// <param name="_Index">
		/// 0 : The first point of the triangle.<para/>
		/// 1 : The second point of the triangle.<para/>
		/// 2 : The third point of the triangle.<para/>
		/// Other indices raise an out of range exception.
		/// </param>
		/// <returns>The point of the triangle corresponding to the <paramref name="_Index"/></returns>
		Vector3& operator[]( Uint32 _Index );

		/// <summary>Compute the barycentric coordinates of a point on the triangle.</summary>
		/// <param name="_OutU">Weight of the first point of the triangle.</param>
		/// <param name="_OutV">Weight of the second point of the triangle.</param>
		/// <param name="_OutW">Weight of the third point of the triangle.</param>
		/// <param name="_P">Point to process to find its barycentric coordinates on the triangle.</param>
		void BarycentricCoordinates( float& _OutU, float& _OutV, float& _OutW, const Vector3& _P ) const;

		/// <summary>Compute the point that corresponds to the given barycentric coordinates.</summary>
		/// <param name="_U">The weight of the first point of the triangle.</param>
		/// <param name="_V">The weight of the second point of the triangle.</param>
		/// <param name="_W">The weight of the third point of the triangle.</param>
		/// <returns>The point that corresponds to the given barycentric coordinates.</returns>
		Vector3 GetPointFromBarycentricCoordinates( float _U, float _V, float _W ) const;

		/// <summary>Compute the intersection between the calling triangle and a <paramref name="_Line"/>.</summary>
		/// <param name="_OutU">
		/// The weight of the first point of the triangle on the intersection point.<para/>
		/// Stay unchanged if there is no intersection.
		/// </param>
		/// <param name="_OutV">
		/// The weight of the second point of the triangle on the intersection point.<para/>
		/// Stay unchanged if there is no intersection.
		/// </param>
		/// <param name="_OutW">
		/// The weight of the third point of the triangle on the intersection point.<para/>
		/// Stay unchanged if there is no intersection.
		/// </param>
		/// <param name="_Line">The line to process the intersection with.</param>
		/// <returns>True if there is an intersection, false otherwise.</returns>
		Bool Intersects( float& _OutU, float& _OutV, float& _OutW, const Line& _Line ) const;

		/// <summary>Compute the intersection between the calling triangle and a <paramref name="_Line"/>.</summary>
		/// <param name="_OutHitPoint">The intersdection point. If there is no intersection, stay unchanged.</param>
		/// <param name="_OutU">
		/// The weight of the first point of the triangle on the intersection point.<para/>
		/// Stay unchanged if there is no intersection.
		/// </param>
		/// <param name="_OutV">
		/// The weight of the second point of the triangle on the intersection point.<para/>
		/// Stay unchanged if there is no intersection.
		/// </param>
		/// <param name="_OutW">
		/// The weight of the third point of the triangle on the intersection point.<para/>
		/// Stay unchanged if there is no intersection.
		/// </param>
		/// <param name="_Line">The line to process the intersection with.</param>
		/// <returns>True if there is an intersection, false otherwise.</returns>
		Bool Intersects( Vector3& _OutHitPoint, float& _OutU, float& _OutV, float& _OutW, const Line& _Line ) const;

		/// <summary>Compute the intersection between the calling triangle and a <paramref name="_Line"/>.</summary>
		/// <param name="_OutHitPoint">The intersdection point. If there is no intersection, stay unchanged.</param>
		/// <param name="_Line">The line to process the intersection with.</param>
		/// <returns>True if there is an intersection, false otherwise.</returns>
		Bool Intersects( Vector3& _OutHitPoint, const Line& _Line ) const;

		/// <summary>Compute the intersection between the calling triangle and a <paramref name="_Line"/>.</summary>
		/// <param name="_Line">The line to process the intersection with.</param>
		/// <returns>True if there is an intersection, false otherwise.</returns>
		Bool Intersects( const Line& _Line ) const;


	private:
		/// <summary>
		/// Compute the intersection between the calling triangle and the ray defined by <paramref name="_Line"/>.<para/>
		/// The ray start is the first point on the line and the ray direction is the line direction.<para/>
		/// Use the Möller–Trumbore intersection algorithm.
		/// </summary>
		/// <param name="_OutHitPoint">The intersection point. If there is no intersection, stay unchanged.</param>
		/// <param name="_OutU">
		/// The weight of the first point of the triangle on the intersection point.<para/>
		/// Stay unchanged if there is no intersection.
		/// </param>
		/// <param name="_OutV">
		/// The weight of the second point of the triangle on the intersection point.<para/>
		/// Stay unchanged if there is no intersection.
		/// </param>
		/// <param name="_Line">
		/// Line data that define the ray.<para/>
		/// The ray start is the first point on the line and the ray direction is the line direction.
		/// </param>
		/// <param name="_HandleParallel">
		/// Do the algorithm handle the case where the ray lies in the plane of the triange ?<para/>
		/// If it is handled, the algorithm may be a bit slower.
		/// </param>
		/// <returns>True if there is an intersection, false otherwise.</returns>
		Bool MollerTrumboreIntersection( Vector3& _OutHitPoint, float& _OutU, float& _OutV, const Line& _Line, bool _HandleParallel = True ) const;

	private:
		/// <summary>The first point of the triangle.</summary>
		Vector3 m_A;
		/// <summary>The second point of the triangle.</summary>
		Vector3 m_B;
		/// <summary>The third point of the triangle.</summary>
		Vector3 m_C;
	};

} // ae

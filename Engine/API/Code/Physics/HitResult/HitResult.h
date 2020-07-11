#pragma once

#include "../../Toolbox/Toolbox.h"

#include "../../Maths/Vector/Vector3.h"
#include "../../World/World.h"

namespace ae
{
	/// \ingroup physics
	/// <summary>
	/// Physic component to make objects collide with each others.
	/// </summary>
	/// <seealso cref="PhysicObject" />
	/// <seealso cref="Collider" />
	struct AERO_CORE_EXPORT HitResult
	{
		/// <summary>Initialize default values.</summary>
		HitResult() :
			IsHit( False ),
			ObjectHit( World::InvalidObjectID ),
			FaceID( 0 ),
			U( 0.0f ),
			V( 0.0f ),
			W( 0.0f )
		{
		}

		/// <summary>Reset the structure with its default values.</summary>
		inline void Reset()
		{
			IsHit = False;
			ImpactPoint = Vector3::Zero;
			ImpactNormal = Vector3::Zero;
			ObjectHit = World::InvalidObjectID;
			FaceID = 0;
			U = 0.0f;
			V = 0.0f;
			W = 0.0f;
		}

		/// <summary>True if an object has been hit, False otherwise.</summary>
		Bool IsHit;

		/// <summary>If an object has been hit, will contain the position of the impact.</summary>
		Vector3 ImpactPoint;

		/// <summary>
		/// If an object has been hit, will contain the normal at the impact using the incomming direction of the first object.<para/>
		/// This normal can be used to process bounces.
		/// </summary>
		Vector3 ImpactNormal;

		/// <summary>If an object has beend hit, will contain its Object ID.</summary>
		World::ObjectID ObjectHit;

		/// <summary>
		/// If an object has beend hit, will contain the ID of hit face.<para/>
		/// Will be empty when hitting something than a mesh collider.
		/// </summary>
		Uint32 FaceID;

		/// <summary>
		/// If a triangle (from a triangle primitive or a mesh collider) has been hit
		/// will contain the barycentric coordinate U of the hit in this triangle. <para/>
		/// To convert barycentric coordinates to a point see <see cref="Triangle::GetPointFromBarycentricCoordinates"/>.
		/// </summary>
		float U;

		/// <summary>
		/// If a triangle (from a triangle primitive or a mesh collider) has been hit
		/// will contain the barycentric coordinate V of the hit in this triangle. <para/>
		/// To convert barycentric coordinates to a point see <see cref="Triangle::GetPointFromBarycentricCoordinates"/>.
		/// </summary>
		float V;

		/// <summary>
		/// If a triangle (from a triangle primitive or a mesh collider) has been hit
		/// will contain the barycentric coordinate W of the hit in this triangle. <para/>
		/// To convert barycentric coordinates to a point see <see cref="Triangle::GetPointFromBarycentricCoordinates"/>.
		/// </summary>
		float W;
	};

} // ae
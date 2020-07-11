#pragma once

#include "../../Toolbox/Toolbox.h"

#include "../HitResult/HitResult.h"

namespace ae
{
	/// \ingroup physics
	/// <summary>
	/// Physic component to make objects collide with each others.
	/// </summary>
	/// <seealso cref="PhysicObject" />
	class AERO_CORE_EXPORT Collider
	{
	private:
		enum class Type : Uint8
		{
			None,
			Sphere,
			Triangle,
			Plane,
			AABB,
			Mesh
		};

	public:
		/// <summary>Default constructor.</summary>
		Collider();
		/// <summary>Default destructor.</summary>
		virtual ~Collider() = default;

		/// <summary>Process the intersection between the calling collider and <paramref name="_Other"/>.</summary>
		/// <param name="_Other">The other collider to do the intersection test with.</param>
		/// <returns>True if the colliders are intersecting each other, false otherwise.</returns>
		virtual Bool Intersects( const Collider& _Other ) const;

		/// <summary>Process the intersection between the calling collider and <paramref name="_Other"/>.</summary>
		/// <param name="_OutHit">
		/// Filled with informations concerning the hit if an intersection happens.<para/>
		/// Stay unchanged if no hit happens.
		/// </param>
		/// <param name="_Other">The other collider to do the intersection test with.</param>
		/// <returns>True if the colliders are intersecting each other, false otherwise.</returns>
		virtual Bool Intersects( HitResult&  _OutHit, const Collider& _Other ) const;

	private:
		/// <summary>Type of the collider : Sphere, Triangle, Plane, ...</summary>
		Type m_Type;
	};

} // ae
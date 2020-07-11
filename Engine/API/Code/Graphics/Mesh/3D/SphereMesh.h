#pragma once

#include "../../../Toolbox/Toolbox.h"
#include "Mesh3D.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Simple 3D colored sphere.
	/// </summary>
	/// <seealso cref="Mesh3D" />
	/// <seealso cref="Drawable" />
	class AERO_CORE_EXPORT SphereMesh : public Mesh3D
	{
	public:
		/// <summary>Create a colored sphere with a radius and spans count.</summary>
		/// <param name="_Radius">The radius of sphere.</param>
		/// <param name="_RingCount">Count of spans on longitude ("vertical spans").</param>
		/// <param name="_SegmentCount">Count of spans on colatitude ("horizontal spans").</param>
		SphereMesh( const float _Radius = 1.0f, const Uint32 _RingCount = 5, const Uint32 _SegmentCount = 5 );


		/// <summary>Set the radius of the sphere.</summary>
		/// <param name="_Radius">The new radius to apply.</param>
		void SetRadius( const float _Radius );

		/// <summary>Retrieve the current radius of the sphere.</summary>
		/// <returns>The current radius of the sphere.</returns>
		float GetRadius() const;

		/// <summary>Set the number of rings of the sphere.</summary>
		/// <param name="_RingCount">The new number of rings to apply.</param>
		void SetRingCount( const Uint32 _RingCount );

		/// <summary>Retrieve the current number of rings of the sphere.</summary>
		/// <returns>The current number of rings of the sphere.</returns>
		Uint32 GetRingCount() const;

		/// <summary>Set the number of segments of the sphere.</summary>
		/// <param name="_SegmentCount">The new number of segments to apply.</param>
		void SetSegmentCount( const Uint32 _SegmentCount );

		/// <summary>Retrieve the current number of segments of the sphere.</summary>
		/// <returns>The current number of segments of the sphere.</returns>
		Uint32 GetSegmentCount() const;

		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor() override;

	private:
		/// <summary>Create the sphere vertices according to the stored parameters.</summary>
		void GenerateUVSphere();

		/// <summary>
		/// Process the UV coordinate for a given <paramref name="_Normal"/> at a vertex position.<para/>
		/// The normal is assumed to be the vector from (0,0,0) to the vertex position, normalized.
		/// </summary>
		/// <param name="_Normal">The normal at the position which we want to process the UV.</param>
		/// <returns>The UV coordinates.</returns>
		Vector2 GetPointUV( const Vector3& _Normal );

	private:
		/// <summary>Radius of the sphere.</summary>
		float m_Radius;

		/// <summary>Count of spans on longitude ("vertical spans").</summary>
		Uint32 m_RingCount;

		/// <summary>Count of spans on colatitude ("horizontal spans").</summary>
		Uint32 m_SegmentCount;
	};
} // ae


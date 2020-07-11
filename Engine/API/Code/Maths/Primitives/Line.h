#pragma once

#pragma once


#include "../../Toolbox/Toolbox.h"
#include "../Vector/Vector3.h"

#include <array>

namespace ae
{
	/// \ingroup math
	/// <summary>
	/// 3D line represented by two points.<para/>
	/// The line is infinite and not restricted between the points.
	/// </summary>
	class AERO_CORE_EXPORT Line
	{
	public:
		/// <summary>Default constructor. All points are set to zero.</summary>
		Line();

		/// <summary>Build the triangle with 3 points.</summary>
		/// <param name="_A">The first point of the triangle.</param>
		/// <param name="_B">The second point of the triangle.</param>
		Line( const Vector3& _A, const Vector3& _B );

		/// <summary>Build the triangle with the content of the <paramref name="_Array"/>.</summary>
		/// <param name="_Array">Array containing the 3 points to build the triangle with.</param>
		Line( const std::array<Vector3, 2>& _Array );


		/// <summary>
		/// Get the direction vector of the line.<para/>
		/// The direction is the unit vector that go from the first point of the line to the second.
		/// </summary>
		/// <returns>The direction of the line</returns>
		Vector3 GetDirection() const;

		/// <summary>Retrieve the first point that defines the line.</summary>
		/// <returns>The first point of the line.</returns>
		const Vector3& GetFirstPoint() const;

		/// <summary>Set the first point that defines the line.</summary>
		/// <param name="_Point">The new position for the first point of the line.</param>
		void SetFirstPoint( const Vector3& _Point );

		/// <summary>Retrieve the second that defines the line.</summary>
		/// <returns>The second point of the line.</returns>
		const Vector3& GetSecondPoint() const;

		/// <summary>Set the second point that defines the line.</summary>
		/// <param name="_Point">The new position for the second point of the line.</param>
		void SetSecondPoint( const Vector3& _Point );
		
	private:
		/// <summary>The first point of the line.</summary>
		Vector3 m_A;

		/// <summary>The second point of the line.</summary>
		Vector3 m_B;
	};

} // ae

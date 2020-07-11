#pragma once


#include "../../Toolbox/Toolbox.h"
#include "../Vector/Vector3.h"

namespace ae
{
    /// \ingroup math
    /// <summary>
    /// 3D plane represented by a point (on the plane) and a normal vector.
    /// </summary>
    class AERO_CORE_EXPORT Plane
    {
    public:
        /// <summary>
        /// Plane constructor.
        /// </summary>
        /// <param name="_Point">Point on the plane.</param>
        /// <param name="_Normal">Normal of the plane.</param>
        Plane( const Vector3& _Point = Vector3::Zero, const Vector3& _Normal = Vector3::AxeY );

        /// <summary>Set the point that define the plane position.</summary>
        /// <param name="_Point">The point that define the new plane position.</param>
        void SetPoint( const Vector3& _Point );

        /// <summary>Retrieve the point on the plane.</summary>
        /// <returns>The point on the plane.</returns>
        const Vector3& GetPoint() const;

        /// <summary>Set the normal of the plane.</summary>
        /// <param name="_Normal">The new normal of the plane.</param>
        void SetNormal( const Vector3& _Normal );

        /// <summary>Retrieve the normal of the plane.</summary>
        /// <returns>The normal of the plane.</returns>
        const Vector3& GetNormal() const;

        /// <summary>Process the shortest distance between <paramref name="_Point"/> and the plane.</summary>
        /// <param name="_Point">The point to process the distance between it and the plane.</param>
        /// <returns>The shortest distance between the point and the plane.</returns>
        float GetDistanceToPlane( const Vector3& _Point ) const;

        /// <summary>
        /// Process the shortest signed distance between <paramref name="_Point"/> and the plane.<para/>
        /// It will be positive if the point is above the plane, negative if it is below.
        /// </summary>
        /// <param name="_Point">The point to process the distance between it and the plane.</param>
        /// <returns>
        /// The shortest signed distance between the point and the plane.<para/>
        /// It will be positive if the point is above the plane, negative if it is below.
        /// </returns>
        float GetSignedDistanceToPlane( const Vector3& _Point ) const;

    private:
        /// <summary>
        /// A point on the plane. <para/>
        /// It's define the plane position.
        /// </summary>
        Vector3 m_Point;

        /// <summary>
        /// Normal of the plane.<para/>
        /// It's define the plane orientation.
        /// </summary>
        Vector3 m_Normal;
    };

} // ae

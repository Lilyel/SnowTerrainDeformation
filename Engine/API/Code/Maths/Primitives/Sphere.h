#pragma once



#include "../../Toolbox/Toolbox.h"
#include "../Vector/Vector3.h"

namespace ae
{
    /// \ingroup math
    /// <summary>
    /// 3D sphere represented by a center and a radius.
    /// </summary>
    class AERO_CORE_EXPORT Sphere
    {
    public:
        /// <summary>Build a sphere with a center and a radius.</summary>
        /// <param name="_Center">The center of the sphere.</param>
        /// <param name="_Radius">The radius of the sphere.</param>
        Sphere( const Vector3& _Center = Vector3::Zero, float _Radius = 1.0f );

        /// <summary>Set the center of the sphere.</summary>
        /// <param name="_Center">The new center of the sphere.</param>
        void SetCenter( const Vector3& _Center );

        /// <summary>Retrieve the center of the sphere.</summary>
        /// <returns>The center of the sphere.</returns>
        const Vector3& GetCenter() const;

        /// <summary>Set the radius of the sphere.</summary>
        /// <param name="_Radius">The new radius of the sphere.</param>
        void SetRadius( float _Radius );

        /// <summary>Retrieve the radius of the sphere.</summary>
        /// <returns>The radius of the sphere.</returns>
        float GetRadius() const;


        /// <summary>
        /// Test if the sphere is intersecting the <paramref name="_Other"/> sphere.<para/>
        /// Intersection occurs if the spheres touch each others or if one contains the other one.
        /// </summary>
        /// <param name="_Other">The other sphere to do the intersection test with.</param>
        /// <param name="_WithBoundaries">
        /// If True, the surface of the sphere is considered.<para/>
        /// That means, if the <paramref name="_Other"/> touch the calling sphere just on 
        /// the surface without going in the function will return True. <para/>
        /// If this parameter is set to False, then the function will return False
        /// if the intersection is on an the surface.
        /// </param>
        /// <param name="_UseSquaredLength">
        /// If True the squared length will be used to process the distance between the spheres.<para/>
        /// It will be faster but could lead to lack of precision.<para/>
        /// Otherwise, the euclidean length will be used.
        /// </param>
        /// <returns>True if the sphere are intersecting each other, false otherwise.</returns>
        Bool Intersects( const Sphere& _Other, Bool _WithBoundaries = True, Bool _UseSquaredLength = True ) const;


        /// <summary>
        /// Test if the sphere contains the <paramref name="_Other"/> sphere. <para/>
        /// This occurs when the other sphere is completly inside the calling one.
        /// </summary>
        /// <param name="_Other">The other sphere to test if it is inside the calling one.</param>
        /// <param name="_WithBoundaries">
        /// If True, the surface of the sphere is considered.<para/>
        /// That means, if the <paramref name="_Other"/> will be considered contained
        /// even if it touches the surface of the calling one. <para/>
        /// If this parameter is set to False, then the function will return False
        /// if the <paramref name="_Other"/> touches the surface of the calling one.
        /// </param>
        /// <param name="_UseSquaredLength">
        /// If True the squared length will be used to process the distance between the spheres.<para/>
        /// It will be faster but could lead to lack of precision.<para/>
        /// Otherwise, the euclidean length will be used.
        /// </param>
        /// <returns>True if the <paramref name="_Other"/> sphere is inside the calling one, false otherwise.</returns>
        Bool Contains( const Sphere& _Other, Bool _WithBoundaries = True, Bool _UseSquaredLength = True ) const;


        /// <summary>
        /// Test if the sphere contains the <paramref name="_Point"/>. <para/>
        /// This occurs when the point is inside the sphere.
        /// </summary>
        /// <param name="_Point">The to test if it is inside the sphere.</param>
        /// <param name="_WithBoundaries">
        /// If True, the surface of the sphere is considered.<para/>
        /// That means, if the <paramref name="_Point"/> will be considered contained
        /// even if it touches the surface of the sphere. <para/>
        /// If this parameter is set to False, then the function will return False
        /// if the <paramref name="_Point"/> touches the surface of the sphere.
        /// </param>
        /// <param name="_UseSquaredLength">
        /// If True the squared length will be used to process the distance between the sphere and the point.<para/>
        /// It will be faster but could lead to lack of precision.<para/>
        /// Otherwise, the euclidean length will be used.
        /// </param>
        /// <returns>True if the <paramref name="_Point"/> is inside the calling one, false otherwise.</returns>
        Bool Contains( const Vector3& _Point, Bool _WithBoundaries = True, Bool _UseSquaredLength = True ) const;

    private:
        /// <summary>The center of the sphere.</summary>
        Vector3 m_Center;

        /// <summary>The radius of the sphere.</summary>
        float m_Radius;
    };

} // ae

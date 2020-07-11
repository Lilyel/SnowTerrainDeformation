#pragma once

#include "Curve.h"

namespace ae
{
    /// \ingroup math   
   /// <summary>Linear 3D parametric curve.</summary>
    class AERO_CORE_EXPORT CurveLinear : public Curve
    {
    public:
        /// <summary>
        /// Build a curve with the given control points.<para/>
        /// The tangents are automaticaly computed from the points.
        /// </summary>
        /// <param name="_ControlPoints">The curve control points.</param>
        CurveLinear( const std::vector<Vector3>& _ControlPoints );


        /// <summary>Get a curve point at the given parameter.</summary>
        /// <param name="_Param">The parameter on the curve.</param>
        /// <returns>Position on the curve at the given parameter.</returns>
        Vector3 GetPointAtParam( float _Param ) const override;


        /// <summary>Get the interpolation type of the curve.</summary>
        /// <returns>The interpolation type of the curve.</returns>
        Type GetType() const override;

    private:
        /// <summary>Linear interpolate the two control data around the parameter index.</summary>
        /// <param name="_Param">The parameter on the curve.</param>
        /// <param name="_ToInterpolate">The data to interpolate.</param>
        /// <returns>The interpolated data.</returns>
        Vector3 LinearInterpolation( float _Param, const std::vector<Vector3>& _ToInterpolate ) const;
    };

} // ae
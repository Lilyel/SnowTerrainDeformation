#pragma once

#include "Curve.h"

namespace ae
{
    /// \ingroup math   
   /// <summary>Hermite 3D interpolation curve.</summary>
    class AERO_CORE_EXPORT CurveHermite : public Curve
    {
    public:
        /// <summary>
        /// Build a curve with the given control points.<para/>
        /// The tangents are automaticaly computed from the points.
        /// </summary>
        /// <param name="_ControlPoints">The curve control points.</param>
        CurveHermite( const std::vector<Vector3>& _ControlPoints );

        /// <summary>
        /// Build a curve with the given control points and tangents.<para/>
        /// The tangents array must be the same size as the control points array.
        /// </summary>
        /// <param name="_ControlPoints">The curve control points.</param>
        /// <param name="_ControlTangents">Tangents at control points.</param>
        CurveHermite( const std::vector<Vector3>& _ControlPoints, const std::vector<Vector3>& _ControlTangents );


        /// <summary>
        /// Rebuild a curve with the given control points.<para/>
        /// The tangents are automaticaly computed from the points.
        /// </summary>
        /// <param name="_ControlPoints">The curve control points.</param>
        void Rebuild( const std::vector<Vector3>& _ControlPoints ) override;

        /// <summary>
        /// Build a curve with the given control points and tangents.<para/>
        /// The tangents array must be the same size as the control points array.
        /// </summary>
        /// <param name="_ControlPoints">The curve control points.</param>
        /// <param name="_ControlTangents">Tangents at control points.</param>
        void Rebuild( const std::vector<Vector3>& _ControlPoints, const std::vector<Vector3>& _ControlTangents );



        /// <summary>Get the tangent of a control point.</summary>
        /// <param name="_Index">The index of the control point.</param>
        /// <returns>The tangent of the control point.</returns>
        const Vector3& GetControlTangent( Uint32 _Index ) const;

        /// <summary>Set the tangent of a control point.</summary>
        /// <param name="_Index">The index of the control point.</param>
        /// <param name="_Tangent">The new tangent for the control point.</param>
        void SetControlTangent( Uint32 _Index, const Vector3& _Tangent );



        /// <summary>Get a curve point at the given parameter.</summary>
        /// <param name="_Param">The parameter on the curve.</param>
        /// <returns>Position on the curve at the given parameter.</returns>
        Vector3 GetPointAtParam( float _Param ) const override;


        /// <summary>Get the interpolation type of the curve.</summary>
        /// <returns>The interpolation type of the curve.</returns>
        Type GetType() const override;


        /// <summary>Get the number of properties to display in the curve editor.</summary>
        /// <returns>The number of propertiers to display in the curve editor.</returns>
        virtual Uint32 EditorGetPropertiesCount() const;

        /// <summary>Get the name of a property to display in the curve editor.</summary>
       /// <returns>The name of the property.</returns>
        virtual const std::string& EditorGetPropertyName( Uint32 _Index ) const;

        /// <summary>Called by curve editor when displaying (and potentialy editing) a property of the curve.</summary>
        /// <param name="_Label">Label in the editor.</param>
        /// <param name="_ControlPoint">The index of the control point.</param>
        /// <param name="_Property">The index of the property.</param>
        /// <returns>True if the property was changed, False otherwise.</returns>
        virtual Bool EditorEditProperty( const std::string& _Label, Uint32 _ControlPoint, Uint32 _Property );

    private:
        /// <summary>Compute the Hermite interpolation the two control point around the parameter index.</summary>
        /// <param name="_Param">The parameter on the curve.</param>
        /// <returns>The interpolated point.</returns>
        Vector3 HermiteInterpolationPoint( float _Param ) const;

        /// <summary>Process the tangent from the control points.</summary>
        void AutoProcessTangents();

    private:
        /// <summary>Tangents at control points.</summary>
        std::vector<Vector3> m_ControlTangents;
    };

} // ae
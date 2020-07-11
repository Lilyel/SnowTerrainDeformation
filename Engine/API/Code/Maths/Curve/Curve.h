#pragma once

#include "../../Toolbox/Toolbox.h"

#include "../Vector/Vector3.h"

#include <vector>

namespace ae
{
    /// \ingroup math   
    /// <summary>Base class for 3D parametric curve.</summary>
    class AERO_CORE_EXPORT Curve
    {
    public:
        /// <summary>Interpolation type of the curve.</summary>
        enum class Type : Uint8
        {
            /// <summary>Linear interpolation between points.</summary>
            Linear,

            /// <summary>Hermite interpolation between points using their tangents.</summary>
            Hermite,

            /// <summary>Kochanek-Bartels interpolation between points using their tangents with bias and tension options.</summary>
            KochanekBartels,

            /// <summary>Unknown interpolation type.</summary>
            Unknown
        };

    public:
        /// <summary>
        /// Build a curve with the given control points.<para/>
        /// The tangents are automaticaly computed from the points.
        /// </summary>
        /// <param name="_ControlPoints">The curve control points.</param>
        Curve( const std::vector<Vector3>& _ControlPoints );


        /// <summary>Virtal destructor for inherit classes.</summary>
        virtual ~Curve() = default;


        /// <summary>
        /// Rebuild a curve with the given control points.<para/>
        /// The tangents are automaticaly computed from the points.
        /// </summary>
        /// <param name="_ControlPoints">The curve control points.</param>
        virtual void Rebuild( const std::vector<Vector3>& _ControlPoints );


        /// <summary>Get the time at the first control point.</summary>
        /// <returns>The time at the first control point.</returns>
        float GetTimeMin() const;

        /// <summary>Get the time at the last control point.</summary>
        /// <returns>The time at the last control point.</returns>
        float GetTimeMax() const;

        /// <summary>Get the time of a control point.</summary>
        /// <param name="_ControlPointIndex">The index of the control point.</param>
        /// <returns>The time at the control point.</returns>
        float GetTime( Uint32 _ControlPointIndex ) const;


        /// <summary>Get the position of a control point.</summary>
        /// <returns>The position of the control point.</returns>
        const Vector3& GetControlPoint( Uint32 _Index ) const;

        /// <summary>Set the position of a control point.</summary>
        /// <param name="_Index">The index of the control point to set.</param>
        /// <param name="_Position">The new position for the control point.</param>
        void SetControlPoint( Uint32 _Index, const Vector3& _Position );


        /// <summary>Get the number of control points.</summary>
        /// <returns>The number of control points of the curve.</returns>
        Uint32 GetControlPointsCount() const;

        /// <summary>Get a curve point at the given parameter.</summary>
        /// <param name="_Param">The parameter on the curve.</param>
        /// <returns>Position on the curve at the given parameter.</returns>
        virtual Vector3 GetPointAtParam( float _Param ) const AE_IsVirtualPure;


        /// <summary>Get the interpolation type of the curve.</summary>
        /// <returns>The interpolation type of the curve.</returns>
        virtual Type GetType() const;


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

    protected:
        /// <summary>Filled the times by 0.0, 1.0, 2.0, ... according the control points count.</summary>
        void AutoProcessTimes();

    protected:
        /// <summary>Control points of the curve.</summary>
        std::vector<Vector3> m_ControlPoints;

        /// <summary>Times at control points.</summary>
        std::vector<float> m_Times;
    };


    /// <summary>Convert a Curve interpolation type to a string.</summary>
    /// <param name="_Type">Interpolation type to convert.</param>
    /// <returns>Interpolation type as string.</returns>
    AERO_CORE_EXPORT std::string ToString( const Curve::Type& _Type );

} // ae
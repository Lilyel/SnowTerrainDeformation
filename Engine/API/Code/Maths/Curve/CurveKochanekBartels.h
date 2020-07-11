#pragma once

#include "Curve.h"

namespace ae
{
	/// \ingroup math   
    /// <summary>
    /// Kochanek-Bartels 3D interpolation curve.<para/>
    /// Equivalent to Hermite curve with bias and tension settings for each control points.
    /// </summary>
	class AERO_CORE_EXPORT CurveKochanekBartels : public Curve
	{
	public:
		/// <summary>Bias and tension setting for control tangents.</summary>
		struct ControlPointSettings
		{
			/// <summary>Initialize a control point setting.</summary>
			/// <param name="_Bias">Bias of the tangent.</param>
			/// <param name="_Tension">Tension of the tangent.</param>
			ControlPointSettings( float _Bias = 0.0f, float _Tension = 0.0f ) :
				Bias( _Bias ),
				Tension( _Tension )
			{
			}

			/// <summary>Bias of the tangent to change its direction.</summary>
			float Bias;

			/// <summary>Tension of the tangent to change its length.</summary>
			float Tension;
		};

	public:
		/// <summary>
		/// Build a curve with the given control points.<para/>
		/// The tangents are automaticaly computed from the points.
		/// </summary>
		/// <param name="_ControlPoints">The curve control points.</param>
		CurveKochanekBartels( const std::vector<Vector3>& _ControlPoints );

		/// <summary>
		/// Build a curve with the given control points.<para/>
		/// The tangents are automaticaly computed from the points.
		/// </summary>
		/// <param name="_ControlPoints">The curve control points.</param>
		/// <param name="_Settings">Per control points bias and tension settings for tangents.</param>
		CurveKochanekBartels( const std::vector<Vector3>& _ControlPoints, const std::vector<ControlPointSettings>& _Settings );


		/// <summary>
		/// Rebuild a curve with the given control points.<para/>
		/// The tangents are automaticaly computed from the points.
		/// </summary>
		/// <param name="_ControlPoints">The curve control points.</param>
		void Rebuild( const std::vector<Vector3>& _ControlPoints ) override;

		/// <summary>
		/// Rebuild a curve with the given control points.<para/>
		/// The tangents are automaticaly computed from the points.
		/// </summary>
		/// <param name="_ControlPoints">The curve control points.</param>
		/// <param name="_Settings">Per control points bias and tension settings for tangents.</param>
		void Rebuild( const std::vector<Vector3>& _ControlPoints, const std::vector<ControlPointSettings>& _Settings );



		/// <summary>Get a curve point at the given parameter.</summary>
		/// <param name="_Param">The parameter on the curve.</param>
		/// <returns>Position on the curve at the given parameter.</returns>
		Vector3 GetPointAtParam( float _Param ) const override;


		/// <summary>Get the interpolation type of the curve.</summary>
		/// <returns>The interpolation type of the curve.</returns>
		Type GetType() const override;


		/// <summary>Get a control point settings.</summary>
		/// <param name="_Index">The index of the control point.</param>
		/// <returns>The settings of the control point.</returns>
		const ControlPointSettings& GetControlPointSetting( Uint32 _Index ) const;

		/// <summary>Set a control point settings.</summary>
		/// <param name="_Index">The index of the control point.</param>
		/// <param name="_Settings">Setting to apply to the control point.</param>
		void SetControlPointSetting( Uint32 _Index, const ControlPointSettings& _Settings );



		/// <summary>Get a control point bias.</summary>
		/// <param name="_Index">The index of the control point.</param>
		/// <returns>The bias of the control point.</returns>
		float GetControlPointBias( Uint32 _Index ) const;

		/// <summary>Set a control point bias.</summary>
		/// <param name="_Index">The index of the control point.</param>
		/// <param name="_Bias">Bias to apply to the control point.</param>
		void SetControlPointBias( Uint32 _Index, float _Bias);

		/// <summary>Get a control point tension.</summary>
		/// <param name="_Index">The index of the control point.</param>
		/// <returns>The tension of the control point.</returns>
		float GetControlPointTension( Uint32 _Index ) const;

		/// <summary>Set a control point tension.</summary>
		/// <param name="_Index">The index of the control point.</param>
		/// <param name="_Tension">Tension to apply to the control point.</param>
		void SetControlPointTension( Uint32 _Index, float _Tension );


		/// <summary>Retrieve the tangent of a control point on the side of its previous point.</summary>
		/// <param name="_Index">The index of the control point.</param>
		/// <returns>The tangent at the control point on the site of its previous point.</returns>
		const Vector3& GetPreviousTangent( Uint32 _Index ) const;

		/// <summary>Set the tangent of a control point on the side of its previous point.</summary>
		/// <param name="_Index">The index of the control point.</param>
		/// <param name="_Tangent">The new tangent to apply.</param>
		void SetPreviousTangent( Uint32 _Index, const Vector3& _Tangent );


		/// <summary>Retrieve the tangent of a control point on the side of its next point.</summary>
		/// <param name="_Index">The index of the control point.</param>
		/// <returns>The tangent at the control point on the site of its next point.</returns>
		const Vector3& GetNextTangent( Uint32 _Index ) const;

		/// <summary>Set the tangent of a control point on the side of its next point.</summary>
		/// <param name="_Index">The index of the control point.</param>
		/// <param name="_Tangent">The new next to apply.</param>
		void SetNextTangent( Uint32 _Index, const Vector3& _Tangent );



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

		/// <summary>Update a control point tangent.</summary>
		/// <param name="_Index">The control point to update.</param>
		void UpdateTangent( Uint32 _Index );

	private:
		/// <summary>Tangents at control points from their previous point.</summary>
		std::vector<Vector3> m_PreviousTangents;

		/// <summary>Tangents at control points to their next point.</summary>
		std::vector<Vector3> m_NextTangents;

		/// <summary>Tangents at control points with their settings applied.</summary>
		std::vector<Vector3> m_ModifiedTangents;

		/// <summary>Bias and tension settings for every control points.</summary>
		std::vector<ControlPointSettings> m_Settings;
	};

} // ae
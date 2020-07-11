#pragma once

#include "../../../Toolbox/Toolbox.h"
#include "Mesh3D.h"

namespace ae
{
	class Curve;

	/// \ingroup graphics
	/// <summary>
	/// Give the possibility to draw a parametric curve.
	/// </summary>
	/// <seealso cref="Mesh3D" />
	/// <seealso cref="Drawable" />
	/// <seealso cref="Curve" />
	class AERO_CORE_EXPORT CurveMesh : public Mesh3D
	{
	public:
		/// <summary>Initialize the curve mesh with the given point count.</summary>
		/// <param name="_Curve">The curve to draw.</param>
		/// <param name="_PointCount">The number of points to draw.</param>
		CurveMesh( const Curve& _Curve, Uint32 _PointCount = 30 );

		/// <summary>Set the curve mesh with the given point count.</summary>
		/// <param name="_Curve">The curve to draw.</param>
		/// <param name="_PointCount">The number of points to draw.</param>
		void SetCurve( const Curve& _Curve, Uint32 _PointCount = 30 );

		
		/// /// <summary>Retrieve the number of points to draw.</summary>
		/// <returns>The number of points to draw.</returns>
		Uint32 GetPointCount() const;

		/// <summary>Set the number of points of the curve to draw.</summary>
		/// <param name="_PointCount">The number of points to draw.</param>
		void SetPointCount( Uint32 _PointCount );


		/// <summary>Is the control put in the mesh ?</summary>
		/// <returns>True if the control curve is in the mesh, False otherwise.</returns>
		Bool IsControlCurveDrawn() const;

		/// <summary>Set if the control curve must be put in the mesh.</summary>
		/// <param name="_Draw">True to put the control in the mesh, False otherwise.</param>
		void SetDrawControlCurve( Bool _Draw );

		/// <summary>Is the curve put in the mesh ?</summary>
		/// <returns>True if the curve is in the mesh, False otherwise.</returns>
		Bool IsCurveDrawn() const;

		/// <summary>Set if the curve must be put in the mesh.</summary>
		/// <param name="_Draw">True to put the curve in the mesh, False otherwise.</param>
		void SetDrawCurve( Bool _Draw );



		/// <summary>Get the current curve.</summary>
		/// <returns>The current curve.</returns>
		const Curve& GetCurve() const;


		/// <summary>Update the mesh from the assigned curve.</summary>
		void Update();


		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		void ToEditor() override;

	private:
		/// <summary>Put the control curve in mesh ?</summary>
		Bool m_DrawControlCurve;

		/// <summary>Put the interpolated curve in mesh ?</summary>
		Bool m_DrawCurve;

		/// <summary>Number of points to discretize.</summary>
		Uint32 m_PointCounts;

		/// <summary>Curve to use when updating the mesh points.</summary>
		const Curve* m_Curve;
	};

} // ae
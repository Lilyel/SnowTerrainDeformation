#pragma once

#include "Camera.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Represent a 3D perspective camera.<para/>
	/// </summary>
	class AERO_CORE_EXPORT CameraPerspective : public Camera
	{
	public:
		/// <summary>Create a perspective camera.</summary>
		/// <param name="_FieldOfView">Angle in radians representing the "opening" of the camera cone.</param>
		/// <param name="_Aspect">Ratio width / height of the camera frame.</param>
		/// <param name="_Near">Near distance.</param>
		/// <param name="_Far">Far distance.</param>
		CameraPerspective( float _FieldOfView = Math::PiDivBy4(), float _Aspect = 16.0f / 9.0f, float _Near = 0.001f, float _Far = 1000.0f );

		/// <summary>
		/// Create perspective camera with default parameters. <para/>
		/// ( 45° FoV, 16/9 aspect, 0.001 near and 1000 far distance ).
		/// </summary>
		void SetToDefaultPerspectiveCamera();


		/// <summary>Update the aspect ratio from the given renderer width and height.</summary>
		/// <param name="_Renderer">The renderer to update the camera with.</param>
		virtual void UpdateFromRenderer( const Renderer& _Renderer ) override;

		/// <summary>Change the field of view of the camera (angle in radians).</summary>
		/// <param name="_FieldOfView">New value for the field of view (angle in radians).</param>
		void SetFieldOfView( float _FieldOfView );

		/// <summary>Retrieve the field of view of the camera (angle in radians).</summary>
		/// <returns>The field of view of the camera (angle in radians).</returns>
		float GetFieldOfView() const;


		/// <summary>Change the aspect ratio avec the camera (width / height).</summary>
		/// <param name="_Aspect">The new aspect ratio of the camera.</param>
		void SetAspect( float _Aspect );

		/// <summary>Retrieve the aspect ratio avec the camera (width / height).</summary>
		/// <returns>The aspect ratio avec the camera (width / height).</returns>
		float GetAspect() const;


		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor() override;

	protected:
		/// <summary>Update the projection matrix with the current settings.</summary>
		void UpdateProjectionMatrix() override;

	private:
		/// <summary>Angle in radians representing the "opening" of the camera cone.</summary>
		float m_FieldOfView;

		/// <summary>Ratio width / height of the camera frame.</summary>
		float m_Aspect;
	};

} // ae

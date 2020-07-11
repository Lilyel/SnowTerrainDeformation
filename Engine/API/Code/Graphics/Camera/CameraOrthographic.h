#pragma once

#include "Camera.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Represent a 3D orthographic camera.<para/>
	/// </summary>
	class AERO_CORE_EXPORT CameraOrthographic : public Camera
	{
	public:
		/// <summary>Create a orthographic camera.</summary>
		/// <param name="_Viewport">Shape and size of the camera surface.</param>
		/// <param name="_Near">Near distance.</param>
		/// <param name="_Far">Far distance.</param>
		CameraOrthographic( const FloatRect& _Viewport = FloatRect( 0.0f, 0.0f, 1.0f, 1.0f ), float _Near = 0.001f, float _Far = 10.0f );

		/// <summary>
		/// Create orthographic camera with default parameters.<para/>
		/// ( Viewport : Left = 0, Top = 0 , Right = 1, Bottom = 1, 0.001 near and 10 far distance ).<para/>
		/// Move the camera to (0.0, 0.0, 1.0).
		/// </summary>
		void SetToDefaultOrthographicCamera();


		/// <summary>
		/// Update the viewport from the given renderer width and height.<para/>
		/// Left = 0, Top = 0, Right = renderer width, Bottom = renderer height.
		/// </summary>
		/// <param name="_Renderer">The renderer to update the camera with.</param>
		void UpdateFromRenderer( const Renderer& _Renderer ) override;

		/// <summary>
		/// Change the viewport of the camera. <para/>
		/// The viewport is the surface of the camera. (Shape and size).
		/// </summary>
		/// <param name="_Viewport">The new viewport to apply.</param>
		void SetViewport( const FloatRect& _Viewport );

		/// <summary>
		/// Retrieve the viewport of the camera. <para/>
		/// The viewport is the surface of the camera. (Shape and size).
		/// </summary>
		/// <returns>The current viewport of the camera.</returns>
		const FloatRect& GetViewport() const;


		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor() override;

		/// <summary>
		/// Set shader uniform with camera composant. <para/>
		/// Set the OpenGL viewport with the camera viewport.</summary>
		/// <param name="_Shader">The shader to send the camera to.</param>
		void SendToShader( const class Shader& _Shader ) override;

	protected:
		/// <summary>Update the projection matrix with the current settings.</summary>
		void UpdateProjectionMatrix() override;

	private:
		/// <summary>Rectangle that define the shape and the size of the camera surface.</summary>
		FloatRect m_Viewport;
	};

} // ae

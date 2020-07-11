#pragma once

#include "../../Toolbox/Toolbox.h"

#include "../../Maths/Transform/Transform.h"
#include "../../Maths/Primitives/TRect.h"
#include "../../Maths/Functions/MathsFunctions.h"
#include "../../World/WorldObject/WorldObject.h"

namespace ae
{
	class Renderer;

	/// \ingroup graphics
	/// <summary>
	/// Represent a 3D camera.<para/>
	/// A camera represent a point of view. <para/>
	/// It also holds the projection matrix that we use for the rendering.
	/// </summary>
	class AERO_CORE_EXPORT Camera : public Transform, public WorldObject
	{
	public:
        /// <summary>Type of control of the camera (constraints on rotation, orbit, total freedom ...).</summary>
        enum class ControlType : Uint8
        {
            /// <summary>No constraints on movement.</summary>
            Free,

            /// <summary>Roll rotation will always be 0.</summary>
            FPS,

            /// <summary>Will rotate around a position and move around it. No roll rotation.</summary>
            Orbit
        };

	public:        
        /// <summary>Default constructor.</summary>
        Camera( float _Near = 0.001f, float _Far = 1000.0f );

		/// <summary>Tag destructor as virtual for inherit classes.</summary>
		virtual ~Camera() = default;


		/// <summary>Update settings from the given renderer parameter.</summary>
		/// <param name="_Renderer">The renderer to update the camera with.</param>
		virtual void UpdateFromRenderer( const Renderer& _Renderer ) AE_IsVirtualPure;

		/// <summary>
		/// Change nearest distance at which the camera can see. <para/>
		/// Objects nearer to this distance will not be visible.
		/// </summary>
		/// <param name="_Near">The new minimum distance for camera to see objects.</param>
		void SetNear( float _Near );

		/// <summary>
		/// Retrieve the nearest distance at which the camera can see. <para/>
		/// Objects nearer to this distance will not be visible.
		/// </summary>
		/// <returns>The minimum distance for camera to see objects.</returns>
		float GetNear() const;


		/// <summary>
		/// Change farest distance at which the camera can see. <para/>
		/// Objects further to this distance will not be visible.
		/// </summary>
		/// <param name="_Far">The new maximum distance for camera to see objects.</param>
		void SetFar( float _Far );

		/// <summary>
		/// Retrieve the farest distance at which the camera can see. <para/>
		/// Objects further to this distance will not be visible.
		/// </summary>
		/// <returns>The maximum distance for camera to see objects.</returns>
		float GetFar() const;

		
		/// <summary>Retrieve the current projection matrix of the camera.</summary>
		/// <returns>The current projection matrix of the camera.</returns>
		const Matrix4x4& GetProjectionMatrix();

		/// <summary>
		/// Retrieve the current look at matrix of the camera. <para/>
		/// This matrix represent the orientation of the camera.
		/// </summary>
		/// <returns>The current look at matrix of the camera.</returns>
		const Matrix4x4& GetLookAtMatrix();


        /// <summary>Set the camera control to ControlType::Free.</summary>
        void SetControlToFree();

        /// <summary>Set the camera control to ControlType::FPS.</summary>
        void SetControlToFPS();

        /// <summary>Set the camera control to ControlType::Orbit.</summary>
        /// <param name="_OrbitCenter">
        /// The orbite center of the camera.<para/>
        /// The camera will rotate and move around this position.
        /// </param>
        void SetControlToOrbit( const Vector3& _OrbitCenter );

        /// <summary>Retrieve the type of control applied to the camera.</summary>
        /// <returns>Camera's control type.</returns>
        ControlType GetControlType() const;

        /// <summary>Retrieve the distance between the camera and the orbit center.</summary>
        /// <returns>The distance between the camera and the orbit center.</returns>
        float GetOrbitDistance() const;

        /// <summary>Set the distance between the camera and the orbit center.</summary>
        /// <param name="_Distance">The new distance between the camera and the orbit center to respect.</param>
        void SetOrbitDistance( float _Distance );

		/// <summary>
		/// Retrieve the point that the camera look at.<para/>
		/// </summary>
		/// <returns>Orbit center if camera is set to orbit, closest point in front of the camera otherwise.</returns>
		Vector3 GetLookAtPoint();


		/// <summary>Set this camera to be used for the next rendering and for the viewport.</summary>
		void SetToActiveCamera();

		
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
		virtual void SendToShader( const class Shader& _Shader );

	protected:
		/// <summary>
		/// Callback implemented from Transform. <para/>
		/// It signals that the tranform (position, rotation or scale) has changed. <para/>
		/// Here, we simply add a signal that the look at matrix must be updated too.
		/// </summary>
		void OnTransformChanged() override;

		/// <summary>
		/// Callback implemented from Transform. <para/>
		/// It signals that the tranform is now up to date. <para/>
		/// If the transform has changed, we update the look at matrix.
		/// </summary>
		void OnTransformUpdated() override;

	protected:
		/// <summary>Update the projection matrix with the current settings.</summary>
		virtual void UpdateProjectionMatrix() AE_IsVirtualPure;

		/// <summary>Update the look at matrix with the current transform.</summary>
		void UpdateLookAtMatrix();

	protected:
        /// <summary>Type of control of the camera.</summary>
        ControlType m_ControlType;

		/// <summary>Signal to know if we must rebuild the projection matrix before returning it.</summary>
		Bool m_UpdateProjectionMatrix;
		/// <summary>Matrix that hold the projection with the current settings.</summary>
		Matrix4x4 m_ProjectionMatrix;

		/// <summary>Signal to know if we must rebuild the look at matrix once the transform is updated.</summary>
		Bool m_UpdateLookAtMatrix;
		/// <summary>Matrix that hold the orientation of the camera.</summary>
		Matrix4x4 m_LookAtMatrix;

        /// <summary>Point to look at when camera is set to orbit.</summary>
        Vector3 m_OrbitCenter;

		/// <summary>Closest distance at which the camera can see objects.</summary>
		float m_Near;

		/// <summary>Farest distance at which the camera can see ojects.</summary>
		float m_Far;

        /// <summary>Distance to respect between the camera and the orbit center.</summary>
        float m_OrbitDistance;
	};

} // ae

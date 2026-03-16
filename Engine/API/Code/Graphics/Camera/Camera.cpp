#include "Camera.h"
#include "../Window/Window.h"
#include "../Material/Material.h"
#include "../../Aero/Aero.h"
#include "../../Editor/TypesToEditor/CameraToEditor.h"
#include "../../Debugging/Error/Error.h"

#include <string>

namespace ae
{
	Camera::Camera( float _Near, float _Far ) :
		m_UpdateProjectionMatrix( True ),
		m_UpdateLookAtMatrix( True ),
		m_LookAtMatrix( Matrix4x4::Identity ),
		m_Near( _Near ),
		m_Far( _Far ),
		m_OrbitCenter( Vector3::Zero ),
		m_OrbitDistance( 50.0f )
	{
		SetName( std::string( "Camera_" ) + std::to_string( GetObjectID() ) );

		SetNear( _Near );
		SetFar( _Far );
	}

	void Camera::SetNear( float _Near )
	{
		m_Near = Math::Clamp( Math::Epsilon(), m_Far - Math::Epsilon(), _Near );

		m_UpdateProjectionMatrix = True;
	}
	float Camera::GetNear() const
	{
		return m_Near;
	}

	void Camera::SetFar( float _Far )
	{
		m_Far = Math::Max( m_Near + Math::Epsilon(), _Far );

		m_UpdateProjectionMatrix = True;
	}
	float Camera::GetFar() const
	{
		return m_Far;
	}

	const Matrix4x4& Camera::GetProjectionMatrix()
	{
		if( m_UpdateProjectionMatrix )
			UpdateProjectionMatrix();

		return m_ProjectionMatrix;
	}

	const Matrix4x4& Camera::GetLookAtMatrix()
	{
		if( m_UpdateLookAtMatrix )
			UpdateLookAtMatrix();

		return m_LookAtMatrix;
	}

	void Camera::SetControlToFree()
	{
		m_ControlType = ControlType::Free;
		m_UpdateLookAtMatrix = True;
	}

	void Camera::SetControlToFPS()
	{
		m_ControlType = ControlType::FPS;
		m_UpdateLookAtMatrix = True;
	}

	void Camera::SetControlToOrbit( const Vector3& _OrbitCenter )
	{
		m_ControlType = ControlType::Orbit;
		m_OrbitCenter = _OrbitCenter;

		m_UpdateLookAtMatrix = True;
	}

	Camera::ControlType Camera::GetControlType() const
	{
		return m_ControlType;
	}

	float Camera::GetOrbitDistance() const
	{
		return m_OrbitDistance;
	}

	void Camera::SetOrbitDistance( float _Distance )
	{
		m_OrbitDistance = Math::Max( _Distance, Math::Epsilon() );
		m_UpdateLookAtMatrix = True;
	}

	Vector3 Camera::GetLookAtPoint()
	{
		if( m_ControlType == ControlType::Orbit )
			return m_OrbitCenter;

		else
		{
			const Vector3 TransformedPosition = GetPosition();
			return TransformedPosition - GetForward();
		}
	}

	void Camera::SetToActiveCamera()
	{
		Aero.SetCamera( *this );
	}


	void Camera::ToEditor()
	{
		WorldObject::ToEditor();
		Transform::ToEditor();
	}

	void Camera::SendToShader( const Shader& _Shader )
	{
		Int32 Location = _Shader.GetUniformLocation( Material::GetDefaultParameterName( Material::DefaultParameters::ViewMatrix ) );
		_Shader.SetMatrix4x4( Location, GetLookAtMatrix() );

		Location = _Shader.GetUniformLocation( Material::GetDefaultParameterName( Material::DefaultParameters::ProjectionMatrix ) );
		_Shader.SetMatrix4x4( Location, GetProjectionMatrix() );

		Location = _Shader.GetUniformLocation( Material::GetDefaultParameterName( Material::DefaultParameters::CameraPosition ) );
		_Shader.SetVector3( Location, GetPosition() );
		
		Location = _Shader.GetUniformLocation( Material::GetDefaultParameterName( Material::DefaultParameters::CameraNear ) );
		_Shader.SetFloat( Location, GetNear() );

		Location = _Shader.GetUniformLocation( Material::GetDefaultParameterName( Material::DefaultParameters::CameraFar ) );
		_Shader.SetFloat( Location, GetFar() );

		
	}

	void Camera::OnTransformChanged()
	{
		m_UpdateLookAtMatrix = True;
	}

	void Camera::OnTransformUpdated()
	{
		if( m_UpdateLookAtMatrix )
			UpdateLookAtMatrix();
	}


	void Camera::UpdateLookAtMatrix()
	{
		if( m_ControlType == ControlType::Orbit )
		{
			const float Azimuthal = GetRotationAngles().Y;
			// Clamp angles to avoid weird behavior.
			const float Polar = Math::Clamp( Math::DegToRad_Const( -89.0f ), Math::DegToRad_Const( 89.0f ), GetRotationAngles().X );

			// Find the camera position on the sphere around the orbit center.
			Vector3 NewPosition;
			NewPosition.X = m_OrbitDistance * Math::Cos( Polar ) * Math::Sin( Azimuthal );
			NewPosition.Y = m_OrbitDistance * Math::Sin( Polar );
			NewPosition.Z = m_OrbitDistance * Math::Cos( Polar ) * Math::Cos( Azimuthal );

			// Center the sphere on orbit center.
			NewPosition += m_OrbitCenter;

			// Look from this new position to the orbit center.
			m_LookAtMatrix.LookAt( NewPosition, m_OrbitCenter, Vector3::AxeY );

			m_Transform = m_LookAtMatrix;
			SetPosition( NewPosition );
		}
		else
		{
			const Vector3 TransformedPosition = GetPosition();
			const Vector3 Up = m_ControlType == ControlType::Free ? GetUp() : Vector3::AxeY;
			const Vector3 At = TransformedPosition - GetForward();

			m_LookAtMatrix.LookAt( TransformedPosition, At, Up );
		}

		m_UpdateLookAtMatrix = False;
	}

} // ae
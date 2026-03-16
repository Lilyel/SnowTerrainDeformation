#include "CameraPerspective.h"

#include "../Renderer/Renderer.h"

#include "../../Editor/TypesToEditor/CameraToEditor.h"

namespace ae
{
	CameraPerspective::CameraPerspective( float _FieldOfView, float _Aspect, float _Near, float _Far ) :
		Camera( _Near, _Far ),
		m_FieldOfView( _FieldOfView ),
		m_Aspect( _Aspect )
	{
	}
	void ae::CameraPerspective::SetToDefaultPerspectiveCamera()
	{
		SetAspect( 16.0f / 9.0f );
		SetFieldOfView( Math::PiDivBy4() );
		SetNear( 0.001f );
		SetFar( 1000.0f );
	}
	void CameraPerspective::UpdateFromRenderer( const Renderer& _Renderer )
	{
		SetAspect( Cast( float, _Renderer.GetWidth() ) / Cast( float, _Renderer.GetHeight() ) );
	}
	void CameraPerspective::SetFieldOfView( float _FieldOfView )
	{
		m_FieldOfView = _FieldOfView;

		m_UpdateProjectionMatrix = True;
	}
	float CameraPerspective::GetFieldOfView() const
	{
		return m_FieldOfView;
	}
	void CameraPerspective::SetAspect( float _Aspect )
	{
		m_Aspect = _Aspect;

		m_UpdateProjectionMatrix = True;
	}
	float CameraPerspective::GetAspect() const
	{
		return m_Aspect;
	}
	void CameraPerspective::ToEditor()
	{
		Camera::ToEditor();
		priv::ui::CameraPerspectiveToEditor( *this );
	}
	void CameraPerspective::UpdateProjectionMatrix()
	{
		m_ProjectionMatrix.SetToPerspectiveMatrix( GetFieldOfView(), GetAspect(), GetNear(), GetFar() );

		m_UpdateProjectionMatrix = False;
	}
}

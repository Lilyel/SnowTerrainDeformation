#include "CameraOrthographic.h"

#include "../Material/Material.h"
#include "../Renderer/Renderer.h"

#include "../../Editor/TypesToEditor/CameraToEditor.h"

namespace ae
{
	CameraOrthographic::CameraOrthographic( const FloatRect& _Viewport, float _Near, float _Far ) :
		Camera( _Near, _Far ),
		m_Viewport( _Viewport )
	{
	}
	void CameraOrthographic::SetToDefaultOrthographicCamera()
	{
		SetPosition( 0.0f, 0.0f, 1.0f );
		SetNear( 0.001f );
		SetFar( 10.0f );

		SetViewport( { 0.0f, 0.0f, 1.0f, 1.0f } );
	}

	void CameraOrthographic::UpdateFromRenderer( const Renderer& _Renderer )
	{
		SetViewport( FloatRect( 0.0f, 0.0f, Cast( float, _Renderer.GetWidth() ), Cast( float, _Renderer.GetHeight() ) ) );
	}

	void CameraOrthographic::SetViewport( const FloatRect& _Viewport )
	{
		m_Viewport = _Viewport;

		m_UpdateProjectionMatrix = True;
	}

	const FloatRect& CameraOrthographic::GetViewport() const
	{
		return m_Viewport;
	}

	void CameraOrthographic::ToEditor()
	{
		Camera::ToEditor();
		priv::ui::CameraOrthographicToEditor( *this );
	}

	void CameraOrthographic::SendToShader( const Shader& _Shader )
	{
		Camera::SendToShader( _Shader );

		Int32 Location = _Shader.GetUniformLocation( Material::GetDefaultParameterName( Material::DefaultParameters::CameraViewportSize ) );
		_Shader.SetVector2( Location, Vector2( m_Viewport.GetWidth(), m_Viewport.GetHeight() ) );
	}

	void CameraOrthographic::UpdateProjectionMatrix()
	{
		m_ProjectionMatrix.SetToOrthogonalMatrix( m_Viewport.Left, m_Viewport.Top, m_Viewport.Right, m_Viewport.Bottom, GetNear(), GetFar() );

		m_UpdateProjectionMatrix = False;
	}
}

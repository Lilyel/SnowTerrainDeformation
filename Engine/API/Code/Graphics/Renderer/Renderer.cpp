#include "Renderer.h"

#include "../../Aero/Aero.h"
#include "../Drawable/Drawable.h"
#include "../Camera/Camera.h"
#include "../Color/Color.h"
#include "../Vertex/Vertex3D.h"
#include "../Vertex/Vertex2D.h"
#include "../Texture/Texture.h"
#include "../Shader/Shader.h"
#include "../Light/Lights.h"
#include "../../Maths/Transform/Transform.h"
#include "../../Maths/Transform/Transform2D.h"
#include "../../World/World.h"

#include "../../Debugging/Debugging.h"
#include "../../Maths/Maths.h"

#include "../Dependencies/OpenGL.h"
#include <Windows.h>

namespace ae
{
	Renderer::Renderer() :
		m_DrawMode( DrawMode::Unknown ),
		m_CullingMode( CullingMode::Unknown ),
		m_DepthMode( DepthMode::Unknown )
	{
	}
	Renderer::~Renderer()
	{
		// Unbind buffers.
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		// Unbind vertex array buffer.
		glBindVertexArray( 0 );
	}

	void Renderer::InitializeRendering()
	{
		// We assume to have a valid OpenGL context here.

		// Needed for transparancy.
		glEnable( GL_BLEND ); AE_ErrorCheckOpenGLError();

		// To avoid cube map artefact.
		glEnable( GL_TEXTURE_CUBE_MAP_SEAMLESS ); AE_ErrorCheckOpenGLError();


		ResetAllModes();
	}

	void Renderer::Clear( const Color& _ClearColor )
	{
		glClearColor( _ClearColor.R(), _ClearColor.G(), _ClearColor.B(), _ClearColor.A() );
		AE_ErrorCheckOpenGLError();

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		AE_ErrorCheckOpenGLError();
	}

	void Renderer::Draw( const Drawable& _Object, Camera* _Camera )
	{
		Draw( _Object, _Object.GetMaterial(), _Camera );
	}


	void Renderer::Draw( const Drawable& _Object, const Material& _Material, Camera* _Camera )
	{
		if( !_Object.IsEnabled() )
			return;

		if( _Material.GetShader() == nullptr )
		{
			AE_LogWarning( "Invalid shader. Object will not be drawn." );
			return;
		}

		if( _Camera == nullptr && !Aero.HasCamera() )
		{
			AE_LogWarning( "No valid camera to use for rendering. Object will not be drawn." );
			return;
		}

		// Don't draw empty meshes.
		if( _Object.GetVerticesCount() == 0 )
			return;

		if( !CheckCountPrimitive( _Object.GetIndicesCount(), _Object.GetPrimitiveType() ) )
		{
			AE_LogWarning( "Count of indices do not fit with the primitive. Object will not be drawn." );
			return;
		}


		glViewport( Cast( GLint, 0 ), Cast( GLint, 0 ), Cast( GLint, GetWidth() ), Cast( GLint, GetHeight() ) );
		AE_ErrorCheckOpenGLError();

		// Call user event.
		_Object.OnDrawBegin( *this );


		Camera& CurrentCamera = _Camera != nullptr ? *_Camera : Aero.GetCamera();

		const Shader& ObjectShader = *_Material.GetShader();

		// Attach the material shader to OpenGL and send its parameters.
		ObjectShader.Bind();
		Uint32 TextureUnit = 0;
		Uint32 ImageUnit = 0;
		_Material.SendParametersToShader( ObjectShader, TextureUnit, ImageUnit );

		// Send object transform if there is.
		_Object.SendTransformToShader( ObjectShader );

		// Send camera parameters.
		if( _Material.NeedCamera() )
			CurrentCamera.SendToShader( ObjectShader );

		// Apply object blending mode.
		SetBlendingMode( _Object.GetBlendMode() );

		// Send world lights to shader.
		if( _Material.NeedLights() )
			SendLightsToShader( ObjectShader );


		// Draw the object with the bound shader.
		DrawVertexArray( _Object, _Object.GetPrimitiveType() );


		// Clean/Unbind data from the shader.
		TextureUnit = 0;
		ImageUnit = 0;
		_Material.Clean( ObjectShader, TextureUnit, ImageUnit );

		// Clear the shader from OpenGL.
		ObjectShader.Unbind();


		// Call user event.
		_Object.OnDrawEnd( *this );
	}

	void Renderer::Render()
	{
		;
	}


	void Renderer::FreeResource()
	{
	}

	void Renderer::ApplyDrawMode() const
	{
		switch( m_DrawMode )
		{
		case DrawMode::Filled:
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			AE_ErrorCheckOpenGLError();
			break;

		case DrawMode::Wireframe:
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			AE_ErrorCheckOpenGLError();
			break;

		case DrawMode::Points:
			glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
			AE_ErrorCheckOpenGLError();
			break;

		default:
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			AE_ErrorCheckOpenGLError();
			break;
		}
	}

	void Renderer::ApplyCullingMode() const
	{
		switch( m_CullingMode )
		{
		case ae::CullingMode::NoCulling:
			glDisable( GL_CULL_FACE ); AE_ErrorCheckOpenGLError();
			break;

		case ae::CullingMode::BackFaces:
			glEnable( GL_CULL_FACE ); AE_ErrorCheckOpenGLError();
			glCullFace( GL_BACK ); AE_ErrorCheckOpenGLError();
			break;

		case ae::CullingMode::FrontFaces:
			glEnable( GL_CULL_FACE ); AE_ErrorCheckOpenGLError();
			glCullFace( GL_FRONT ); AE_ErrorCheckOpenGLError();
			break;

		case ae::CullingMode::BackAndFrontFaces:
			glEnable( GL_CULL_FACE ); AE_ErrorCheckOpenGLError();
			glCullFace( GL_FRONT_AND_BACK ); AE_ErrorCheckOpenGLError();
			break;

		default:
			glEnable( GL_CULL_FACE ); AE_ErrorCheckOpenGLError();
			glCullFace( GL_BACK ); AE_ErrorCheckOpenGLError();
			break;
		}
	}

	void Renderer::ApplyDepthMode() const
	{
		if( m_DepthMode == DepthMode::NoDepthTest )
		{
			glDisable( GL_DEPTH_TEST );
			AE_ErrorCheckOpenGLError();
		}
		else
		{
			glEnable( GL_DEPTH_TEST ); AE_ErrorCheckOpenGLError();
			glDepthFunc( static_cast<GLenum>( m_DepthMode ) ); AE_ErrorCheckOpenGLError();
		}
	}

	void Renderer::ApplyAllModes() const
	{
		ApplyDrawMode();
		ApplyCullingMode();
		ApplyDepthMode();
	}

	void Renderer::ResetAllModes()
	{
		ResetDrawMode();
		ResetCullingMode();
		ResetDepthMode();
	}


	void Renderer::SaveModes() const
	{
		glPushAttrib( GL_ALL_ATTRIB_BITS ); AE_ErrorCheckOpenGLError();
		glPushClientAttrib( GL_CLIENT_ALL_ATTRIB_BITS ); AE_ErrorCheckOpenGLError();
	}

	void Renderer::RestoreSavedModes() const
	{
		glPopClientAttrib();
		glPopAttrib();
	}


	void Renderer::DrawVertexArray( const Drawable& _Object, PrimitiveType _PrimitiveType )
	{
		// Bind the drawable OpenGL buffers.
		glBindVertexArray( _Object.GetVertexArrayObject() ); AE_ErrorCheckOpenGLError();

		// Draw the vertex array's buffers.
		glDrawElements( Cast( GLenum, _PrimitiveType ), _Object.GetIndicesCount(), GL_UNSIGNED_INT, 0 ); AE_ErrorCheckOpenGLError();

		// Unbind vertex array buffer.
		glBindVertexArray( 0 );
	}

	void Renderer::SetBlendingMode( const BlendMode& _BlendMode )
	{
		glBlendFunc( Cast( GLenum, _BlendMode.SourceFactor ), Cast( GLenum, _BlendMode.DestinationFactor ) );
		AE_ErrorCheckOpenGLError();
	}

	void Renderer::SetDrawMode( const DrawMode& _DrawMode )
	{
		if( m_DrawMode != _DrawMode )
		{
			m_DrawMode = _DrawMode;
			ApplyDrawMode();
		}
	}

	DrawMode Renderer::GetDrawMode() const
	{
		return m_DrawMode;
	}

	void Renderer::ResetDrawMode()
	{
		SetDrawMode( DrawMode::Filled );
	}

	void Renderer::SetCullingMode( const CullingMode& _CullingMode )
	{
		if( m_CullingMode != _CullingMode )
		{
			m_CullingMode = _CullingMode;
			ApplyCullingMode();
		}
	}

	CullingMode Renderer::GetCullingMode() const
	{
		return m_CullingMode;
	}

	void Renderer::ResetCullingMode()
	{
		SetCullingMode( CullingMode::BackFaces );
	}

	void Renderer::SetDepthMode( const DepthMode& _DepthMode )
	{
		if( m_DepthMode != _DepthMode )
		{
			m_DepthMode = _DepthMode;
			ApplyDepthMode();
		}
	}

	DepthMode Renderer::GetDepthMode() const
	{
		return m_DepthMode;
	}

	void Renderer::ResetDepthMode()
	{
		SetDepthMode( DepthMode::Default );
	}


	void Renderer::SendLightsToShader( const Shader& _Shader )
	{
		const std::array<std::string, 3> UniformNames =
		{
			 Material::GetDefaultParameterName( Material::DefaultParameters::PointLights ),
			 Material::GetDefaultParameterName( Material::DefaultParameters::SpotLights ),
			 Material::GetDefaultParameterName( Material::DefaultParameters::DirectionalLights )
		};

		std::array<Uint32, 3> LightsCount = { 0, 0, 0 };

		const World& WorldRef = Aero.GetWorld();
		const std::unordered_map<World::ObjectID, Light*>& Lights = WorldRef.GetLights();
		for( const std::pair<World::ObjectID, Light*>& LightItem : Lights )
		{
			Light* Light = LightItem.second;
			if( !Light->IsEnabled() || Light->GetLightType() == Light::LightType::Unknown )
				continue;

			const size_t LightTypeID = static_cast<size_t>( Light->GetLightType() );

			Light->SendToShader( UniformNames[LightTypeID], LightsCount[LightTypeID], _Shader );
			LightsCount[LightTypeID]++;
		}

		Int32 CountLocation = _Shader.GetUniformLocation( Material::GetDefaultParameterName( Material::DefaultParameters::PointLightsCount ) );
		_Shader.SetInt( CountLocation, LightsCount[static_cast<size_t>( Light::LightType::Point )] );

		CountLocation = _Shader.GetUniformLocation( Material::GetDefaultParameterName( Material::DefaultParameters::SpotLightsCount ) );
		_Shader.SetInt( CountLocation, LightsCount[static_cast<size_t>( Light::LightType::Spot )] );

		CountLocation = _Shader.GetUniformLocation( Material::GetDefaultParameterName( Material::DefaultParameters::DirectionalLightsCount ) );
		_Shader.SetInt( CountLocation, LightsCount[static_cast<size_t>( Light::LightType::Directional )] );
	}


	Bool Renderer::CheckCountPrimitive( const Uint32 _Count, const PrimitiveType& _PrimitiveType ) const
	{
		if( _Count <= 0 )
			return False;

		if( _Count == 1 && _PrimitiveType != PrimitiveType::Points )
			return False;

		if( _Count < 2 && _PrimitiveType >= PrimitiveType::LineLoop )
			return False;

		if( _Count < 3 && ( _PrimitiveType >= PrimitiveType::TriangleFan || _PrimitiveType == PrimitiveType::Polygon ) )
			return False;

		if( _Count < 4 && ( _PrimitiveType >= PrimitiveType::QuadStip && _PrimitiveType != PrimitiveType::Polygon ) )
			return False;

		return True;
	}

} // ae
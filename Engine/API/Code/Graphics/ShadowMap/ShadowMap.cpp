#include "ShadowMap.h"

#include "../Light/SpotLight/SpotLight.h"
#include "../Drawable/Drawable.h"
#include "../../Debugging/Debugging.h"
#include "../../Aero/Aero.h"

#include "../../Editor/TypesToEditor/ShadowMapToEditor.h"

namespace ae
{

	ShadowMap::ShadowMap( const Light& _Light, Uint32 _Width, Uint32 _Height, float _Near, float _Far, const Vector2& _Coverage ) :
		Framebuffer( _Width, _Height, GetAttachementFromLight( _Light ) )
	{
		m_Near = _Near;
		m_Far = Math::Max( _Near + Math::Epsilon(), _Far );
		m_Coverage = _Coverage;
		m_Bias = 0.005f;
		m_OmniPCFRadius = 0.005f;

		m_LightRef = &_Light;

		m_IsOmnidirectional = _Light.GetLightType() == Light::LightType::Point;

		m_ShadowMap = GetAttachementTexture( FramebufferAttachement::Type::Depth );

		if( !m_IsOmnidirectional )
			m_ShadowMap->SetWrapMode( TextureWrapMode::ClampToBorder );

		SetCullingMode( CullingMode::FrontFaces );

		m_ShaderRef = m_IsOmnidirectional ? Aero.GetResourcesManager().GetDefaultOmniShadowMapShader() : Aero.GetResourcesManager().GetDefaultUniShadowMapShader();

		m_UsePCF = True;


		SetName( std::string( "ShadowMap_" ) + std::to_string( GetResourceID() ) );
	}

	void ShadowMap::Bind()
	{
		UpdateMatrices();

		Framebuffer::Bind();
	}


	void ShadowMap::Clear( const Color& )
	{
		// We only need to clear the depth.
		glClear( GL_DEPTH_BUFFER_BIT );
		AE_ErrorCheckOpenGLError();
	}

	void ShadowMap::Draw( const Drawable& _Object, Camera* )
	{
		if( !_Object.IsEnabled() )
			return;

		if( !CheckCountPrimitive( _Object.GetIndicesCount(), _Object.GetPrimitiveType() ) )
		{
			AE_LogWarning( "Count of indices do not fit with the primitive. Object will not be drawn." );
			return;
		}

		// Call user event.
		_Object.OnDrawBegin( *this );

		// Use the shadow map shader to generate depth map.
		m_ShaderRef->Bind();

		// Apply the shadow map viewport.
		glViewport( 0, 0, Cast( GLint, GetWidth() ), Cast( GLint, GetHeight() ) ); AE_ErrorCheckOpenGLError();

		// Send light matrices and datas.
		const std::string& ProjectionName = Material::GetDefaultParameterName( Material::DefaultParameters::ShadowMap_ProjectionMatrix );
		m_ShaderRef->SetMatrix4x4( m_ShaderRef->GetUniformLocation( ProjectionName ), m_ProjectionMatrix );

		if( IsOmnidirectional() )
			SetupOmniShaderUniforms();
		else
			SetupUniShaderUniforms();

		// Send object transform if there is.
		_Object.SendTransformToShader( *m_ShaderRef );

		// Draw the object with the bound shader.
		DrawVertexArray( _Object, _Object.GetPrimitiveType() );

		// Clear the shader from OpenGL.
		m_ShaderRef->Unbind();


		// Call user event.
		_Object.OnDrawEnd( *this );
	}

	void ShadowMap::Draw( const Drawable& _Object, const Material&, Camera* )
	{
		Draw( _Object, nullptr );
	}

	const Light& ShadowMap::GetLight() const
	{
		return *m_LightRef;
	}

	float ShadowMap::GetNear() const
	{
		return m_Near;
	}

	void ShadowMap::SetNear( float _Near )
	{
		m_Near = Math::Clamp( Math::Epsilon(), m_Far - Math::Epsilon(), _Near );
	}

	float ShadowMap::GetFar() const
	{
		return m_Far;
	}

	void ShadowMap::SetFar( float _Far )
	{
		m_Far = Math::Max( m_Near + Math::Epsilon(), _Far );
	}

	const Vector2& ShadowMap::GetOrthographicCoverage() const
	{
		return m_Coverage;
	}

	void ShadowMap::SetOrthographicCoverage( const Vector2& _Coverage )
	{
		m_Coverage = _Coverage;
	}

	const Shader* ShadowMap::GetShader() const
	{
		return m_ShaderRef;
	}

	void ShadowMap::SetShader( const Shader& _Shader )
	{
		m_ShaderRef = &_Shader;
	}

	const Texture* ShadowMap::GetShadowMap() const
	{
		return m_ShadowMap;
	}

	Bool ShadowMap::IsUsingPCF() const
	{
		return m_UsePCF;
	}

	void ShadowMap::SetUsePCF( Bool _UsePCF )
	{
		m_UsePCF = _UsePCF;
	}

	float ShadowMap::GetOmniPCFRadius() const
	{
		return m_OmniPCFRadius;
	}

	void ShadowMap::SetOmniPCFRadius( float _Radius )
	{
		m_OmniPCFRadius = Math::Clamp01( _Radius );
	}

	float ShadowMap::GetBias() const
	{
		return m_Bias;
	}

	void ShadowMap::SetBias( float _Bias )
	{
		m_Bias = Math::Clamp01( _Bias );
	}

	Bool ShadowMap::IsOmnidirectional() const
	{
		return m_IsOmnidirectional;
	}

	void ShadowMap::SendParametersToShader( const Shader& _Shader, AE_InOut Uint32& _TextureUnit ) const
	{
		// Send light matrices.
		const std::string& ViewName = Material::GetDefaultParameterName( Material::DefaultParameters::ShadowMap_ViewMatrix );
		_Shader.SetMatrix4x4( _Shader.GetUniformLocation( ViewName ), m_ViewMatrix[0] );

		const std::string& ProjectionName = Material::GetDefaultParameterName( Material::DefaultParameters::ShadowMap_ProjectionMatrix );
		_Shader.SetMatrix4x4( _Shader.GetUniformLocation( ProjectionName ), m_ProjectionMatrix );

		// Light position.
		const std::string& LightPositionName = Material::GetDefaultParameterName( Material::DefaultParameters::ShadowMap_LightPosition );
		_Shader.SetVector3( _Shader.GetUniformLocation( LightPositionName ), m_LightRef->GetPosition() );

		// Activate texture in shader.
		glActiveTexture( GL_TEXTURE0 + _TextureUnit ); AE_ErrorCheckOpenGLError();

		// Bind the texture attached to this parameter.
		m_ShadowMap->Bind();

		// Set the shadow map in shader with the current unit texture.
		const std::string& ShadowMapName = Material::GetDefaultParameterName( IsOmnidirectional() ? Material::DefaultParameters::ShadowMap_TextureOmni : Material::DefaultParameters::ShadowMap_Texture );;
		if( IsOmnidirectional() )
			_Shader.SetInt( _Shader.GetUniformLocation( ShadowMapName ), _TextureUnit );
		else
			_Shader.SetInt( _Shader.GetUniformLocation( ShadowMapName ), _TextureUnit );

		// Increment texture unit for next bindings.
		_TextureUnit++;

		// Is the light is point and thus, need to sample a cube map ?
		const std::string& IsOmniName = Material::GetDefaultParameterName( Material::DefaultParameters::ShadowMap_IsOmni );
		_Shader.SetBool( _Shader.GetUniformLocation( IsOmniName ), IsOmnidirectional() );

		// Filter for softer shadow ?
		const std::string& UsePCFName = Material::GetDefaultParameterName( Material::DefaultParameters::ShadowMap_UsePCF );
		_Shader.SetBool( _Shader.GetUniformLocation( UsePCFName ), IsUsingPCF() );

		// Radius of PCF filter for omnidirection shadow map.
		if( IsUsingPCF() && IsOmnidirectional() )
		{
			const std::string& OmniPCFRadiusName = Material::GetDefaultParameterName( Material::DefaultParameters::ShadowMap_OmniPCFRadius );
			_Shader.SetFloat( _Shader.GetUniformLocation( OmniPCFRadiusName ), GetOmniPCFRadius() );
		}

		// Shadow bias to avoid acne.
		const std::string& BiasName = Material::GetDefaultParameterName( Material::DefaultParameters::ShadowMap_Bias );
		_Shader.SetFloat( _Shader.GetUniformLocation( BiasName ), GetBias() );

		// Far distance.
		const std::string& FarName = Material::GetDefaultParameterName( Material::DefaultParameters::ShadowMap_Far );
		_Shader.SetFloat( _Shader.GetUniformLocation( FarName ), m_Far );
	}

	void ShadowMap::Clean( const Shader& _Shader, AE_InOut Uint32& _TextureUnit ) const
	{
		// Activate texture in shader.
		glActiveTexture( GL_TEXTURE0 + _TextureUnit ); AE_ErrorCheckOpenGLError();

		// Bind the texture attached to this parameter.
		m_ShadowMap->Unbind();

		// Set the shadow map in shader with the current unit texture.
		const std::string& ShadowMapName = Material::GetDefaultParameterName( IsOmnidirectional() ? Material::DefaultParameters::ShadowMap_TextureOmni : Material::DefaultParameters::ShadowMap_Texture );;
		if( IsOmnidirectional() )
			_Shader.SetInt( _Shader.GetUniformLocation( ShadowMapName ), 0 );
		else
			_Shader.SetInt( _Shader.GetUniformLocation( ShadowMapName ), 0 );

		// Increment texture unit for next bindings.
		_TextureUnit++;
	}

	void ShadowMap::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::ShadowMapToEditor( *this );
	}

	void ShadowMap::UpdateMatrices()
	{
		if( m_LightRef->GetLightType() == Light::LightType::Directional )
		{
			m_ProjectionMatrix.SetToOrthogonalMatrix( -m_Coverage.X, -m_Coverage.Y, m_Coverage.X, m_Coverage.Y, m_Near, m_Far );

			const Vector3& LightForward = m_LightRef->GetRotation().GetForward();
			const Vector3 OffsetDirectionnalLight = ( m_Far - m_Near ) * 0.5f * LightForward;
			m_ViewMatrix[0].LookAt( m_LightRef->GetPosition() - OffsetDirectionnalLight, m_LightRef->GetPosition() + LightForward, Vector3::AxeY );
		}
		else if( m_LightRef->GetLightType() == Light::LightType::Spot )
		{
			const float Aspect = Cast( float, GetWidth() ) / Cast( float, GetHeight() );
			const float FOV = ( (SpotLight*)m_LightRef )->GetOuterAngle();
			m_ProjectionMatrix.SetToPerspectiveMatrix( FOV, Aspect, m_Near, m_Far );

			const Vector3& LightForward = m_LightRef->GetRotation().GetForward();
			m_ViewMatrix[0].LookAt( m_LightRef->GetPosition(), m_LightRef->GetPosition() + LightForward, Vector3::AxeY );
		}
		else
		{
			const float Aspect = Cast( float, GetWidth() ) / Cast( float, GetHeight() );
			constexpr float FOV = Math::PiDivBy2();
			m_ProjectionMatrix.SetToPerspectiveMatrix( FOV, Aspect, m_Near, m_Far );

			const Vector3& LightPosition = m_LightRef->GetPosition();
			m_ViewMatrix[0].LookAt( LightPosition, LightPosition + Vector3::AxeX, -Vector3::AxeY ); // Side X
			m_ViewMatrix[1].LookAt( LightPosition, LightPosition - Vector3::AxeX, -Vector3::AxeY ); // Side -X
			m_ViewMatrix[2].LookAt( LightPosition, LightPosition + Vector3::AxeY, Vector3::AxeZ ); // Side Y
			m_ViewMatrix[3].LookAt( LightPosition, LightPosition - Vector3::AxeY, -Vector3::AxeZ ); // Side Y
			m_ViewMatrix[4].LookAt( LightPosition, LightPosition + Vector3::AxeZ, -Vector3::AxeY ); // Side Z
			m_ViewMatrix[5].LookAt( LightPosition, LightPosition - Vector3::AxeZ, -Vector3::AxeY ); // Side -Z
		}
	}

	void ShadowMap::SetupUniShaderUniforms() const
	{
		// Send light matrices.
		const std::string& ViewName = Material::GetDefaultParameterName( Material::DefaultParameters::ShadowMap_ViewMatrix );
		m_ShaderRef->SetMatrix4x4( m_ShaderRef->GetUniformLocation( ViewName ), m_ViewMatrix[0] );
	}

	void ShadowMap::SetupOmniShaderUniforms() const
	{
		// Send light matrices.
		const std::string& ViewName = Material::GetDefaultParameterName( Material::DefaultParameters::ShadowMap_ViewMatrix );
		for( Uint32 s = 0; s < 6; s++ )
			m_ShaderRef->SetMatrix4x4( m_ShaderRef->GetUniformLocation( ViewName + '[' + std::to_string( s ) + ']' ), m_ViewMatrix[s] );

		// Far distance.
		const std::string& FarName = Material::GetDefaultParameterName( Material::DefaultParameters::ShadowMap_Far );
		m_ShaderRef->SetFloat( m_ShaderRef->GetUniformLocation( FarName ), m_Far );

		// Light position.
		const std::string& LightPositionName = Material::GetDefaultParameterName( Material::DefaultParameters::ShadowMap_LightPosition );
		m_ShaderRef->SetVector3( m_ShaderRef->GetUniformLocation( LightPositionName ), m_LightRef->GetPosition() );
	}

	FramebufferAttachement ShadowMap::GetAttachementFromLight( const Light& _Light )
	{
		TextureDimension Dimension = _Light.GetLightType() == Light::LightType::Point ? TextureDimension::CubeMap : TextureDimension::Texture2D;

		return FramebufferAttachement( FramebufferAttachement::Type::Depth, TexturePixelFormat::Depth_F32, TextureFilterMode::Nearest, Dimension );
	}


} // ae

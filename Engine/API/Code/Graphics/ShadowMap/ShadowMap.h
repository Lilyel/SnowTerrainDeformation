#pragma once


#include "../../Toolbox/Toolbox.h"
#include "../Framebuffer/Framebuffer.h"
#include "../Texture/Texture.h"
#include "../Light/Light.h"
#include "../../Resources/Resource/Resource.h"

#include <unordered_map>
#include <memory>
#include <stack>

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Offscreen rendering to generate a shadow map texture.<para/>
	/// The shadow map texture can then be send to shaders to create shadows.
	/// </summary>
	/// <seealso cref="Framebuffer" />
	/// <seealso cref="Light" />
	/// <seealso cref="Texture" />
	class AERO_CORE_EXPORT ShadowMap : public Framebuffer, public Resource
	{
	public:
		/// <summary>Initialize a shadow map.</summary>
		/// <param name="_Light">The light to use for the shadow map.</param>
		/// <param name="_Width">The width of the shadow map texture.</param>
		/// <param name="_Height">The height of the shadow map texture.</param>
		/// <param name="_Near">The near distance when rendering on the shadow map.</param>
		/// <param name="_Far">The far sitance when rendering on the shadow map.</param>
		/// <param name="_Coverage">Coverage of the world for orthographic shadow map.</param>
		ShadowMap( const Light& _Light, Uint32 _Width, Uint32 _Height, float _Near, float _Far, const Vector2& _Coverage = Vector2( 10.0f, 10.0f ) );

		/// <summary>Bind the framebuffer to OpenGL to hold the result of the next draws.</summary>
		void Bind() override;
		

		/// <summary>Clear the current OpenGL buffer.</summary>
		/// <param name="_ClearColor">The color to apply after the clear.</param>
		void Clear( const Color& _ClearColor = ae::Color::Black ) override;

		/// <summary>Draw an object to the render target.</summary>
		/// <param name="_Object">The object to draw.</param>
		/// <param name="_Camera">Optionnal camera. If null, the current active camera will be taken.</param>
		void Draw( const Drawable& _Object, Camera* _Camera = nullptr ) override;

		/// <summary>Draw an object to the render target.</summary>
		/// <param name="_Object">The object to draw.</param>
		/// <param name="_Material">Material to use instead of the object material.</param>
		/// <param name="_Camera">Optionnal camera. If null, the current active camera will be taken.</param>
		void Draw( const Drawable& _Object, const Material& _Material, Camera* _Camera = nullptr ) override;

		/// <summary>Retrieve the current light used for the shadow map.</summary>
		/// <returns>The light used for the shadow map.</returns>
		const Light& GetLight() const;

		/// <summary>Retrieve the near distance when rendering on the shadow map.</summary>
		/// <returns>The near distance of the shadow map.</returns>
		float GetNear() const;

		/// <summary>Set the near distance when rendering on the shadow map.</summary>
		/// <param name="_Near">The new near distance.</param>
		void SetNear( float _Near );

		/// <summary>Retrieve the far distance when rendering on the shadow map.</summary>
		/// <returns>The far distance of the shadow map.</returns>
		float GetFar() const;

		/// <summary>Set the far distance when rendering on the shadow map.</summary>
		/// <param name="_Far">The new far distance.</param>
		void SetFar( float _Far );

		/// <summary>Retrieve the current coverage of the world for orthographic shadow map.</summary>
		/// <returns>The current coverage.</returns>
		const Vector2& GetOrthographicCoverage() const;

		/// <summary>Set the coverage of the world for orthographic shadow map.</summary>
		/// <param name="_Coverage">The new coverage.</param>
		void SetOrthographicCoverage( const Vector2& _Coverage );

		/// <summary>Retrieve the current shader used when rendering on the shadow map.</summary>
		/// <returns>The current shader used for rendering.</returns>
		const Shader* GetShader() const;

		/// <summary>Set the shader used when rendering on the shadow map.</summary>
		/// <param name="_Shader">The shader to use.</param>
		void SetShader( const Shader& _Shader );

		/// <summary>Get the shadow map texture.</summary>
		/// <returns>The shadow map.</returns>
		const Texture* GetShadowMap() const;

		/// <summary>Is the shadow map must be filtered using a percentage-close technique ?</summary>
		/// <returns>If True, the shadow map must be filtered, False otherwise.</returns>
		Bool IsUsingPCF() const;

		/// <summary>Must the shadow be filtered with percentage-close technique to soften the shadows ?</summary>
		/// <param name="_UsePCF">True to filter the shadows, False otherwise.</param>
		void SetUsePCF( Bool _UsePCF );

		/// <summary>Retrieve the radius of the PCF filter for omnidirectional shadow map.</summary>
		/// <returns>The radius of the filter.</returns>
		float GetOmniPCFRadius() const;

		/// <summary>Set the radius of the PCF filter for omnidirectional shadow map.</summary>
		/// <param name="_Radius">The new radius to apply.</param>
		void SetOmniPCFRadius( float _Radius );

		/// <summary>Retrieve the current value of shadow bias.</summary>
		/// <returns>The current shadow bias.</returns>
		float GetBias() const;

		/// <summary>Set the shadow bias to avoid acne.</summary>
		/// <param name="_Bias">The bias to apply.</param>
		void SetBias( float _Bias );

		/// <summary>Is the shadow map used with point light and using a cube map shadow map ?</summary>
		/// <returns>True if the shadow map is a cube map, False otherwise.</returns>
		Bool IsOmnidirectional() const;

		/// <summary>
		/// Set shader uniform with shadow composant. <para/>
		/// Send view and projection matrix, light position and the texture.</summary>
		/// <param name="_Shader">Shader to send the parameters to.</param>
		/// <param name="_TextureUnit">Texture unit to use with texture parameters. Incremented for each texture sent.</param>
		void SendParametersToShader( const Shader& _Shader, AE_InOut Uint32& _TextureUnit ) const;

		/// <summary>
		/// Called after a draw call.<para/>
		/// Give the possibility to reset parameters or unbind texture after the draw call.
		/// </summary>
		/// <param name="_Shader">The target shader for the parameter.</param>
		/// <param name="_TextureUnit">The target sampler unit in the shader for the parameter.</param>
		void Clean( const Shader& _Shader, AE_InOut Uint32& _TextureUnit ) const;

		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		void ToEditor() override;

	private:
		/// <summary>Update the view and projection matrices from the light.</summary>
		void UpdateMatrices();

		/// <summary>Update unidirectional shader view matrix.</summary>
		void SetupUniShaderUniforms() const;

		/// <summary>Update omnidirectional shader views matrices and far distance.</summary>
		void SetupOmniShaderUniforms() const;

		/// <summary>
		/// Process the right attachement for the given light.<para/>
		/// Directionnal and spot lights are 2D depth. Point light are cube map depth.
		/// </summary>
		/// <param name="_Light">The light to find the right shadow map attachement for.</param>
		/// <returns>The attachement for the shadow map framebuffer.</returns>
		static FramebufferAttachement GetAttachementFromLight( const Light& _Light );

	private:
		/// <summary>Amount of coverage of the shadow map of the world.</summary>
		Vector2 m_Coverage;

		/// <summary>Shadow map texture.</summary>
		Texture* m_ShadowMap;

		/// <summary>The light used for this shadow map.</summary>
		const Light* m_LightRef;

		/// <summary>The view matrix of the light.</summary>
		Matrix4x4 m_ViewMatrix[6];

		/// <summary>The projection matrix of the light.</summary>
		Matrix4x4 m_ProjectionMatrix;

		/// <summary>Near distance when rendering on the shadow map.</summary>
		float m_Near;

		/// <summary>Far distance when rendering on the shadow map.</summary>
		float m_Far;

		/// <summary>Shader reference to the default shadow map shader.</summary>
		const Shader* m_ShaderRef;

		/// <summary>Use Percentage-close filtering to soften the shadows ?</summary>
		Bool m_UsePCF;

		/// <summary>Radius of the PCF filter for omnidirectional shadow map.</summary>
		float m_OmniPCFRadius;

		/// <summary>Shadow bias to avoid shadow acne.</summary>
		float m_Bias;

		/// <summary>Is the shadow is omnidirectional ? (Point light / cube map)</summary>
		Bool m_IsOmnidirectional;
	};
} // ae

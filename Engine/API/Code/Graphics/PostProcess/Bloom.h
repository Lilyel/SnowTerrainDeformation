#pragma once

#include "GaussianBlur.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Apply a bloom effect to texture : <para/>
	/// Extract the bright pixels then blur them and blend the blurred texture with the original texture.
	/// </summary>
	class AERO_CORE_EXPORT Bloom : public GaussianBlur
	{
	public:
		/// <summary>Default values of the bloom effect.</summary>
		Bloom();

		/// <summary>Apply bloom effect on a texture with the stored parameters.</summary>
		/// <param name="_Texture">The texture to process.</param>
		/// <param name="_SaveFBOs">
		/// Save the FBO use for the ping-pong for next application ?<para/>
		/// It can save some time ot avoid the creation of framebuffer at each call.<para/>
		/// If the <paramref name="_Texture"/> has a different pixel format than the saved FBOs,
		/// they will be re-created with the new format.
		/// </param>
		void Apply( Texture2D& _Texture, Bool _SaveFBOs = True ) override;


		/// <summary>Set the threshold that consider a pixel bright.</summary>
		/// <param name="_Threshold">The new threshold to apply.</param>
		void SetBrightnessThreshold( const Vector3& _Threshold );

		/// <summary>Retrieve the threshold that consider a pixel bright.</summary>
		/// <returns>The current threshold.</returns>
		const Vector3& GetBrightnessThreshold() const;


		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		void ToEditor() override;

	private:
		/// <summary>Extract the bright pixel from a texture.</summary>
		Shader m_ExtractionShader;

		/// <summary>Blend the bloom texture and the color texture.</summary>
		Shader m_BlendShader;

		/// <summary>Target with two attachement : the bloom texture (for bright pixels) and the color texture.</summary>
		std::unique_ptr<Framebuffer> m_FBO;

		/// <summary>Fullscreen quad mesh.</summary>
		FullscreenQuadMesh m_BloomQuad;

		/// <summary>Threshold to put a pixel to the bloom texture.</summary>
		Vector3 m_BrightnessThreshold;

		/// <summary>Color texture parameter of the blend shader.</summary>
		ShaderParameterTexture* m_ColorTextureParam;

		/// <summary>Bloom texture parameter of the blend shader.</summary>
		ShaderParameterTexture* m_BloomTextureParam;
	};
}

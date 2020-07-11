#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Shader/Shader.h"
#include "../Mesh/2D/FullscreenQuadMesh.h"
#include "../Framebuffer/Framebuffer.h"

#include <memory>

namespace ae
{
	class Texture2D;

	/// \ingroup graphics
	/// <summary>
	/// Apply a gamma correction to a HDR texture.
	/// </summary>
	class AERO_CORE_EXPORT GammaCorrection : public Resource
	{
	public:
		/// <summary>Default values of gamma and exposure.</summary>
		GammaCorrection();

		/// <summary>Apply gaussian blur on a texture with the stored parameters.</summary>
		/// <param name="_Texture">The HDR texture to correct.</param>
		/// <param name="_SaveFBOs">
		/// Save the FBO use for the ping-pong for next application ?<para/>
		/// It can save some time ot avoid the creation of framebuffer at each call.<para/>
		/// If the <paramref name="_Texture"/> has a different pixel format than the saved FBOs,
		/// they will be re-created with the new format.
		/// </param>
		void Apply( Texture2D& _Texture, Bool _SaveFBOs = True );


		/// <summary>Set the exposure to apply to the HDR image.</summary>
		/// <param name="_Exposure">The exposure to apply.</param>
		void SetExposure( float _Exposure );

		/// <summary>Retrieve the current exposure applied to the image.</summary>
		/// <returns>The current exposure value.</returns>
		float GetExposure() const;


		/// <summary>Set the gamma to apply to the HDR image.</summary>
		/// <param name="_Gamma">The new gamma to apply.</param>
		void SetGamma( float _Gamma );

		/// <summary>Retrieve the current gamma value applied to the image.</summary>
		/// <returns>The current gamma value.</returns>
		float GetGamma() const;


		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor();

	private:
		/// <summary>Shader used for the gamma correction.</summary>
		Shader m_GammaShader;

		/// <summary>Fullscreen quad mesh.</summary>
		FullscreenQuadMesh m_Quad;

		/// <summary>Intermediate target for gamma correction.</summary>
		std::unique_ptr<Framebuffer> m_FBO;

		/// <summary>Exposure factor to apply.</summary>
		float m_Exposure;

		/// <summary>Gamma value to apply.</summary>
		float m_Gamma;
	};
}
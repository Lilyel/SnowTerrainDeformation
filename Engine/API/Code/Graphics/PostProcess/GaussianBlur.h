#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Shader/Shader.h"
#include "../Framebuffer/Framebuffer.h"
#include "../Mesh/2D/FullscreenQuadMesh.h"

#include <memory>

namespace ae
{
	class Texture2D;

	/// \ingroup graphics
	/// <summary>
	/// Apply a gaussian blur to a texture in a ping-pong fashion.
	/// </summary>
	class AERO_CORE_EXPORT GaussianBlur : public Resource
	{
	public:
		enum class Radius : Uint8
		{
			_5x5 = 1,
			_11x11 = 2,
			_21x21 = 4,
			_41x41 = 8
		};

	public:
		/// <summary>Default values of gaussian blur.</summary>
		GaussianBlur();

		/// <summary>Tag destructor as virtual for inherited classes.</summary>
		virtual ~GaussianBlur() = default;


		/// <summary>Apply gaussian blur on a texture with the stored parameters.</summary>
		/// <param name="_Texture">The texture to blur.</param>
		/// <param name="_SaveFBOs">
		/// Save the FBO use for the ping-pong for next application ?<para/>
		/// It can save some time ot avoid the creation of framebuffer at each call.<para/>
		/// If the <paramref name="_Texture"/> has a different pixel format than the saved FBOs,
		/// they will be re-created with the new format.
		/// </param>
		virtual void Apply( Texture2D& _Texture, Bool _SaveFBOs = True );

		/// <summary>Set the number of iteration of the blur application.s</summary>
		/// <param name="_IterationsCount">The new number of iteration.</param>
		void SetIterationsCount( Uint32 _IterationsCount );

		/// <summary>Retrieve the number of iteration of the blur applications.</summary>
		/// <returns>The current number of iteration of the blur applications.</returns>
		Uint32 GetIterationsCount() const;


		/// <summary>Set the standard deviation of the gaussian function.</summary>
		/// <param name="_StandardDeviation">The new standard deviation to use.</param>
		void SetStandardDeviation( float _StandardDeviation );

		/// <summary>Retrieve the standard deviation of the gaussian function.</summary>
		/// <returns>The current standard deviation of the gaussian function.</returns>
		float GetStandardDeviation() const;


		/// <summary>
		/// Must the gaussian coeficients must be normalized ? <para/>
		/// If true the sum of coeficients will be equal to 1.</summary>
		/// <param name="_Normalize">Must normalize the gaussian coeficients ?</param>
		void NormalizeGaussian( Bool _Normalize );

		/// <summary>Is the sum of the gaussian coeficients equal to 1 ?</summary>
		/// <returns>True if the gaussian is normalized, False otherwise.</returns>
		Bool IsGaussianNormalized() const;


		/// <summary>Set the radius of the kernel.</summary>
		/// <param name="_Radius">The new radius to apply to the kernel.</param>
		void SetRadius( Radius _Radius );

		/// <summary>Retrieve the radius of the kernel.</summary>
		/// <returns>The current radius of the kernel.</returns>
		Radius GetRadius() const;

		/// <summary>Get the gaussian coeficient used for the blur.</summary>
		/// <param name="_Coefs">The gaussian coeficients.</param>
		void GetCoefs( AE_Out float _Coefs[5] );

		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		void ToEditor() override;

	private:
		/// <summary>Process the gaussian coeficients with the stored standard deviation.</summary>
		void UpdateCoefs();

		/// <summary>Create the FBO used for the blur.</summary>
		/// <param name="_Texture">The texture to blur.</param>
		/// <param name="_Width">Width of the FBOs.</param>
		/// <param name="_Height">Height of the FBOs.</param>
		void CreateFBOs( const Texture2D& _Texture, Uint32 _Width, Uint32 _Height );

	private:
		/// <summary>Shader used for the ping-pong blur.</summary>
		Shader m_GaussianShader;

		/// <summary>Fullscreen quad mesh.</summary>
		FullscreenQuadMesh m_Quad;

		/// <summary>Target for horizontal blur.</summary>
		std::unique_ptr<Framebuffer> m_HorizontalFBO;

		/// <summary>Target for vertical blur.</summary>
		std::unique_ptr<Framebuffer> m_VerticalFBO;

		/// <summary>Number of ping-pong iterations.</summary>
		Uint32 m_IterationsCount;

		/// <summary>Gaussian coeficients.</summary>
		float m_Coefs[5];

		/// <summary>Standard deviation.</summary>
		float m_StandardDeviation;

		/// <summary>Normalize the gaussian coeficients ?</summary>
		Bool m_IsNormalized;

		/// <summary>Must update the gaussian coeficients before the next blur process ?</summary>
		Bool m_MustUpdateCoefs;

		/// <summary>Radius of the gaussian kernel.</summary>
		Radius m_Radius;
	};
}
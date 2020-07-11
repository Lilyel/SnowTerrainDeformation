#pragma once

#include "../../Toolbox/Toolbox.h"
#include "Texture2D.h"

namespace ae
{
	class FramebufferAttachement;

	/// \ingroup graphics
	/// <summary>
	/// 2D multisample data that can be link to a shader to be rendered.
	/// </summary>
	class AERO_CORE_EXPORT TextureMultisample : public Texture2D
	{
	public:
		/// <summary>Create an empty multisample texture 2D.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_Format">Format of the texture : channels, type.</param>
		/// <param name="_SamplesCount">Number of sample for multi sample texture. 0 or 1 mean no multi sampling.</param>
		TextureMultisample( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format = TexturePixelFormat::DefaultTexture, Uint32 _SamplesCount = 0 );

		/// <summary>Create an empty multisample texture with framebuffer attachement settings.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_FramebufferAttachement">Settings to apply.</param>
		TextureMultisample( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _FramebufferAttachement );


		/// <summary>Create an empty multisample texture 2D.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_Format">Format of the texture : channels, type.</param>
		/// <param name="_SamplesCount">Number of sample for multi sample texture. 0 or 1 mean no multi sampling.</param>
		void Set( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format = TexturePixelFormat::DefaultTexture, Uint32 _SamplesCount = 0 );

		/// <summary>Create an empty multisample texture 2D.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_Format">Format of the texture : channels, type.</param>
		void Set( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format = TexturePixelFormat::DefaultTexture ) override;

		/// <summary>Create an empty texture with framebuffer attachement settings..</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_FramebufferAttachement">Settings to apply.</param>
		void Set( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _FramebufferAttachement );


		/// <summary>Set the number of samples for the texture in case of 2D mutli sample texture.</summary>
		/// <param name="_SamplesCount">The number of samples for multi sample texture to apply.</param>
		void SetSamplesCount( Uint32 _SamplesCount );

		/// <summary>The number of samples for the texture in case of 2D mutli sample texture.</summary>
		/// <returns>The number of samples for multi sample texture.</returns>
		Uint32 GetSamplesCount() const;


		/// <summary>Called by the framebuffer to attach the texture to it.</summary>
		void AttachToFramebuffer( const FramebufferAttachement& _Attachement ) const override;


		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor();

	protected:	
		/// <summary>Hide ToImage method of Texture2D, it is not supported for multisample texture..</summary>
		using Texture2D::ToImage;

		/// <summary>Create an empty texture.</summary>
		void SetupEmpty() override;

	protected:
		/// <summary>In case of multi sample 2D texture, the number of sample in the texture.</summary>
		Uint32 m_SampleCount;
	};

} // ae

#pragma once

#include "../../Toolbox/Toolbox.h"
#include "Texture2D.h"

namespace ae
{
	class FramebufferAttachement;

	/// \ingroup graphics
	/// <summary>
	/// 2D rectangle data that can be link to a shader to be rendered.
	/// </summary>
	class AERO_CORE_EXPORT Texture2DRect : public Texture2D
	{
	public:
		/// <summary>Create an empty multisample texture 2D.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_Format">Format of the texture : channels, type.</param>
		Texture2DRect( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format = TexturePixelFormat::DefaultTexture );

		/// <summary>Create an empty multisample texture with framebuffer attachement settings.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_FramebufferAttachement">Settings to apply.</param>
		Texture2DRect( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _FramebufferAttachement );

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


		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor();

	protected:
		/// <summary>Create an empty texture.</summary>
		void SetupEmpty() override;

		/// <summary>
		/// Called by the framebuffer to attach the texture to it.<para/>
		/// Not available for texture rectangle.
		/// </summary>
		void AttachToFramebuffer( const FramebufferAttachement& _Attachement ) const override final;
	};

} // ae

#pragma once

#include "../../Toolbox/Toolbox.h"
#include "Texture.h"
#include "../Image/Image.h"

namespace ae
{
	class FramebufferAttachement;

	/// \ingroup graphics
	/// <summary>
	/// 2D samplable data that can be link to a shader to be rendered.
	/// </summary>
	class AERO_CORE_EXPORT Texture2D : public Texture
	{
	public:
		/// <summary>Create an empty texture 2D.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_Format">Format of the texture : channels, type.</param>
		Texture2D( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format = TexturePixelFormat::DefaultTexture );

		/// <summary>Create an empty texture with framebuffer attachement settings.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_FramebufferAttachement">Settings to apply.</param>
		Texture2D( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _FramebufferAttachement );
		
		/// <summary>Create an empty texture 2D.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_Format">Format of the texture : channels, type.</param>
		virtual void Set( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format = TexturePixelFormat::DefaultTexture );

		/// <summary>Create an empty texture with framebuffer attachement settings.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_FramebufferAttachement">Settings to apply.</param>
		virtual void Set( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _FramebufferAttachement );

		/// <summary>Resize the texture 1D.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		void Resize( Uint32 _Width, Uint32 _Height );

		/// <summary>Get the width of the texture.</summary>
		/// <returns>Width of the texture.</returns>
		Uint32 GetWidth() const;

		/// <summary>Get the height of the texture.</summary>
		/// <returns>Height of the texture.</returns>
		Uint32 GetHeight() const;

		/// <summary>Called by the framebuffer to attach the texture to it.</summary>
		void AttachToFramebuffer( const FramebufferAttachement& _Attachement ) const override;

		/// <summary>Retrieve texture data from the GPU and store it in an image.</summary>
		/// <returns>Image containing the texture data.</returns>
		Image ToImage() const;

		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor();

	protected:
		/// <summary>Constructor that does nothing. For inherited class only.</summary>
		Texture2D();

	protected:
		/// <summary>Create an empty texture.</summary>
		virtual void SetupEmpty();

	protected:
		/// <summary>Width of the texture.</summary>
		Uint32 m_Width;

		/// <summary>Width of the texture.</summary>
		Uint32 m_Height;
	};

} // ae

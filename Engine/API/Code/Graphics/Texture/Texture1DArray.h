#pragma once

#include "../../Toolbox/Toolbox.h"
#include "Texture.h"

namespace ae
{
	class FramebufferAttachement;

	/// \ingroup graphics
	/// <summary>
	/// 1D array samplable data that can be link to a shader to be rendered.
	/// </summary>
	class AERO_CORE_EXPORT Texture1DArray : public Texture
	{
	public:
		/// <summary>Create an empty texture 1D.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Depth">The depth of the texture.</param>
		/// <param name="_Format">Format of the texture : channels, type.</param>
		Texture1DArray( Uint32 _Width, Uint32 _Depth, TexturePixelFormat _Format = TexturePixelFormat::DefaultTexture );

		/// <summary>Create an empty texture with framebuffer attachement settings.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Depth">The depth of the texture.</param>
		/// <param name="_FramebufferAttachement">Settings to apply.</param>
		Texture1DArray( Uint32 _Width, Uint32 _Depth, const FramebufferAttachement& _FramebufferAttachement );

		/// <summary>Create an empty texture 1D.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Depth">The depth of the texture.</param>
		/// <param name="_Format">Format of the texture : channels, type.</param>
		void Set( Uint32 _Width, Uint32 _Depth, TexturePixelFormat _Format = TexturePixelFormat::DefaultTexture );

		/// <summary>Create an empty texture with framebuffer attachement settings.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Depth">The depth of the texture.</param>
		/// <param name="_FramebufferAttachement">Settings to apply.</param>
		void Set( Uint32 _Width, Uint32 _Depth, const FramebufferAttachement& _FramebufferAttachement );

		/// <summary>Resize the texture 1D.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Depth">The depth of the texture.</param>
		void Resize( Uint32 _Width, Uint32 _Depth );

		/// <summary>Get the width of the texture.</summary>
		/// <returns>Width of the texture.</returns>
		Uint32 GetWidth() const;

		/// <summary>Get the depth of the texture.</summary>
		/// <returns>Depth of the texture.</returns>
		Uint32 GetDepth() const;

		/// <summary>Called by the framebuffer to attach the texture to it.</summary>
		void AttachToFramebuffer( const FramebufferAttachement& _Attachement ) const override;

		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor();

	private:
		/// <summary>Create 1D texture with the user parameters.</summary>
		virtual void SetupEmpty();

	protected:
		/// <summary>Width of the texture.</summary>
		Uint32 m_Width;

		/// <summary>Depth of the texture (number of slices of the array).</summary>
		Uint32 m_Depth;
	};

} // ae

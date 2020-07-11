#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Color/Color.h"
#include "TextureFilterMode.h"
#include "TexturePixelFormat.h"
#include "TextureWrapMode.h"
#include "TextureDimension.h"
#include "TextureImageBindMode.h"

#include "../../Resources/Resource/Resource.h"

namespace ae
{
	class FramebufferAttachement;

	/// \ingroup graphics
	/// <summary>
	/// 1D or 2D samplable data that can be link to a shader to be rendered.
	/// </summary>
	class AERO_CORE_EXPORT Texture : public Resource
	{
	public:
		/// <summary>Create OpenGL texture.</summary>
		Texture();

		/// <summary>Destroy the texture, free the resource.</summary>
		virtual ~Texture();

		/// <summary>Set the texture filtering mode.</summary>
		/// <param name="_Mode">The new filtering mode.</param>
		void SetFilterMode( TextureFilterMode _Mode );
		/// <summary>Get the current filter mode.</summary>
		/// <returns>Current used filter mode.</returns>
		TextureFilterMode GetFilterMode() const;

		/// <summary>Set how the texture coordinates need to be processed.</summary>
		/// <param name="_Mode">The new wrap mode.</param>
		virtual void SetWrapMode( TextureWrapMode _Mode );
		/// <summary>Get the current wraping mode.</summary>
		/// <returns>The current wraping mode.</returns>
		TextureWrapMode GetWrapMode() const;

		/// <summary>Get the format of the pixel of the texture.</summary>
		/// <returns>The format of the texture.</returns>
		TexturePixelFormat GetFormat() const;

		/// <summary>Get the current dimension of the texture (1D, 2D, 3D, ...)</summary>
		/// <returns>The current texture dimension.</returns>
		TextureDimension GetDimension() const;

		/// <summary>Set the texture border color for ClampToBorder wraping mode.</summary>
		/// <param name="_Color">The new border color.</param>
		void SetBorderColor( const Color& _Color );

		/// <summary>Get the texture border color for ClampToBorder wraping mode.</summary>
		/// <returns>Texture border color.</returns>
		const Color& GetBorderColor() const;

		/// <summary>Generates the mip map.</summary>
		void GenerateMipMap() const;

		/// <summary>Bind the texture to OpenGL for the next draws.</summary>
		void Bind() const;

		/// <summary>Unbind the texture from OpenGL.</summary>
		void Unbind() const;

		/// <summary>Bind the texture as image to be used with gimage samplers</summary>
		/// <param name="_ImageUnit">The OpenGL image unit for the image.</param>
		/// <param name="_AccessMode">Access mode to the image.</param>
		/// <param name="_IsLayered">Must send a particular layer ? (Texture must be array or 3D).</param>
		/// <param name="_Layer">Layer to send for layered texture.</param>
		void BindAsImage( Uint32 _ImageUnit, TextureImageBindMode _AccessMode = TextureImageBindMode::ReadWrite, Bool _IsLayered = False, Uint32 _Layer = 0 ) const;
		
		/// <summary>Unbind the texture from OpenGL.</summary>
		void UnbindAsImage() const;

		/// <summary>Set the name of the object.</summary>
		/// <param name="_NewName">The new name to apply to the object.</param>
		void SetName( const std::string& _NewName ) final;

		/// <summary>Get the OpenGL ID of the texture.</summary>
		/// <returns>The OpenGL ID of the texture.</returns>
		Uint32 GetTextureID() const;

		/// <summary>Is the texture must be bound as iamge when sent to shader or as regular texture ?</summary>
		/// <returns>True if bound as image, False otherwise.</returns>
		Bool IsBoundAsImage() const;

		/// <summary>Precise if the texture texture must be bound as image when sent to shader or as regular texture.</summary>
		/// <param name="_IsBoundAsImage">True to bind the texture as image, False to bind it as regular texture.</param>
		void SetIsBoundAsImage( Bool _IsBoundAsImage );

		/// <summary>Called by the framebuffer to attach the texture to it.</summary>
		virtual void AttachToFramebuffer( const FramebufferAttachement& _Attachement ) const AE_IsVirtualPure;

		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor();

	private:
		/// <summary>Create OpenGL texture.</summary>
		void CreateResource();

		/// <summary>Frees OpenGL texture.</summary>
		void FreeResource();

	protected:
		/// <summary>OpenGL ID of the texutre.</summary>
		Uint32 m_TextureID;

		/// <summary>The filter mode (sampling of the texel).</summary>
		TextureFilterMode m_Filter;

		/// <summary>The wrap mode (processing of the texture coordinates).</summary>
		TextureWrapMode m_Wrap;

		/// <summary>Format of the data (type, channels).</summary>
		TexturePixelFormat m_Format;

		/// <summary>The dimension (1D, 2D, 3D, ..) of the texture.</summary>
		TextureDimension m_Dimension;

		/// <summary>Texture border color for ClampToBorder wraping mode.</summary>
		Color m_BorderColor;

		/// <summary>If true, the texture will be bound as image to the shader, otherwise as regular texture.</summary>
		Bool m_IsBoundAsImage;
	};

} // ae

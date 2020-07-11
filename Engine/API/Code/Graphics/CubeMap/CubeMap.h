#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Texture/Texture.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// A texture that make a cube (6 sides).<para>
	/// Can be send to shader to process refraction or reflection.<para/>
	/// Can also be used to make a skybox.<para/>
	/// The cubemap is composed of 6 textures, each one attached to a cube face.<para/>
	/// Order : Right, Left, Top, Bottom, Front, Back.
	/// </summary>
	class AERO_CORE_EXPORT CubeMap : public Texture
	{
	public:
		/// <summary>Create an empty texture 2D.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_Format">Format of the texture : channels, type.</param>
		CubeMap( Uint32 _Width, Uint32 _Height, TexturePixelFormat _Format = TexturePixelFormat::DefaultTexture );

		/// <summary>Create an empty texture with framebuffer attachement settings.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_FramebufferAttachement">Settings to apply.</param>
		CubeMap( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _FramebufferAttachement );

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
		
		/// <summary>Set how the texture coordinates need to be processed.</summary>
		/// <param name="_Mode">The new wrap mode.</param>
		void SetWrapMode( TextureWrapMode _Mode ) override;

		/// <summary>Get the width of the texture.</summary>
		/// <returns>Width of the texture.</returns>
		Uint32 GetWidth( Uint32 _Index ) const;

		/// <summary>Get the height of the texture.</summary>
		/// <returns>Height of the texture.</returns>
		Uint32 GetHeight( Uint32 _Index ) const;


		/// <summary>Called by the framebuffer to attach the texture to it.</summary>
		void AttachToFramebuffer( const FramebufferAttachement& _Attachement ) const override;


		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		void ToEditor() override;

	protected:
		/// <summary>Constructor that does nothing. For inherited class only.</summary>
		CubeMap();

		/// <summary>Create an empty texture.</summary>
		virtual void SetupEmpty();

		/// <summary>Set all 6 widths at once.</summary>
		/// <param name="_Width">The width to apply.</param>
		void SetWidths( Uint32 _Width );

		/// <summary>Set all 6 heights at once.</summary>
		/// <param name="_Height">The height to apply.</param>
		void SetHeights( Uint32 _Height );

	protected:
		/// <summary>Width of each side of the cube map.</summary>
		Uint32 m_Widths[6];

		/// <summary>Height of each side of the cube map.</summary>
		Uint32 m_Heights[6];
	};

} // ae

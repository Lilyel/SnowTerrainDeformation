#pragma once


#include "../../Toolbox/Toolbox.h"
#include "../Renderer/Renderer.h"
#include "Attachement/FramebufferAttachement.h"
#include "../Texture/Texture.h"

#include <unordered_map>
#include <memory>
#include <stack>

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Offscreen render target.
	/// </summary>
	class AERO_CORE_EXPORT Framebuffer : public Renderer
	{
		struct AttachementPair
		{
			AttachementPair( const FramebufferAttachement& _Attachement, Texture* _Texture ) :
				Attachement( _Attachement ),
				Texture( _Texture )
			{}

			FramebufferAttachement Attachement;
			std::unique_ptr<Texture> Texture;
		};
		using AttachementMap = std::unordered_map<Uint32, AttachementPair>;

	public:
		/// <summary>
		/// Some attachement presets to make easier the initialization of some framebuffers.<para/>
		/// The filter of color preset is linear.
		/// </summary>
		enum class AttachementPreset : Uint8
		{
			/// <summary>One color attachement RGB of type unsigned byte.</summary>
			RGB_U8,

			/// <summary>One color attachement RGBA of type unsigned byte.</summary>
			RGBA_U8,

			/// <summary>One color attachement RGBA of type half-float.</summary>
			RGBA_F16,

			/// <summary>
			/// One color attachement RGBA of type unsigned byte.<para/>
			/// And one Depth/Stencil attachement of type unsigned int (24 bits for depth, 8 bits for stencil).
			/// </summary>
			RGBA_U8_DepthStencil_U_24_8,

			/// <summary>
			/// One color attachement RGBA of type unsigned byte.<para/>
			/// And one Depth/Stencil attachement of type unsigned int (24 bits for depth, 8 bits for stencil).<para/>
			/// The attachements is multisample (4 samples by default).
			/// </summary>
			RGBA_U8_DepthStencil_U_24_8_MS,

			/// <summary>
			/// One color attachement RGBA of type unsigned short.<para/>
			/// And one Depth/Stencil attachement of type unsigned int (24 bits for depth, 8 bits for stencil).
			/// </summary>
			RGBA_U16_DepthStencil_U_24_8,

			/// <summary>
			/// One color attachement RGBA of type half-float.<para/>
			/// And one Depth/Stencil attachement of type unsigned int (24 bits for depth, 8 bits for stencil).<para/>
			/// The attachements is multisample (4 samples by default).
			/// </summary>
			RGBA_F16_DepthStencil_U_24_8_MS,

			/// <summary>One depth attachement of type half float.</summary>
			Depth_Float
		};

	public:
		/// <summary>
		/// Framebuffer constructor with a given preset..<para/>
		/// By default, initialize the framebuffer with a RGBA (unsigned byte) color attachement
		/// and a depth stencil (unsigned int 24/8) attachement.
		/// </summary>
		/// <param name="_Width">Width the texture of the framebuffer.</param>
		/// <param name="_Height">Height the texture of the framebuffer.</param>
		/// <param name="_Preset">Optional preset to set the framebuffer.</param>
		Framebuffer( Uint32 _Width, Uint32 _Height, AttachementPreset _Preset = AttachementPreset::RGBA_U8_DepthStencil_U_24_8 );

		/// <summary>
		/// Framebuffer constructor.<para/>
		/// Initialize the framebuffer with the given attachement.
		/// </summary>
		/// <param name="_Width">Width the texture of the framebuffer.</param>
		/// <param name="_Height">Height the texture of the framebuffer.</param>
		/// <param name="_Attachement">Description of the texture to create for the framebuffer.</param>
		Framebuffer( Uint32 _Width, Uint32 _Height, const FramebufferAttachement& _Attachement );

		/// <summary>
		/// Framebuffer constructor.<para/>
		/// Initialize the framebuffer with the given attachements.<para/>
		/// If there is no attachement provided, the framebuffer will be initialized with
		/// a RGBA (unsigned byte) color attachement and a depth stencil (unsigned int 24/8) attachement.
		/// </summary>
		/// <param name="_Width">Width the texture of the framebuffer.</param>
		/// <param name="_Height">Height the texture of the framebuffer.</param>
		/// <param name="_Attachements">Descriptions of the textures to create for the framebuffer.</param>
		Framebuffer( Uint32 _Width, Uint32 _Height, std::initializer_list<FramebufferAttachement> _Attachements );


		/// <summary>Destroy the framebuffer.</summary>
		virtual ~Framebuffer();

		/// <summary>Rebuild the framebuffer with the <paramref name="_Width"/> and <paramref name="_Height"/></summary>
		/// <param name="_Width">The new width to apply to the framebuffer.</param>
		/// <param name="_Height">The new height to apply to the framebuffer.</param>
		virtual void Resize( Uint32 _Width, Uint32 _Height );


		/// <summary>Bind the attachement texture of the framebuffer to OpenGL.</summary>
		/// <param name="_Type">Attachement of the texture to bind.</param>
		void BindAttachementTexture( FramebufferAttachement::Type _Type = FramebufferAttachement::Type::Color_0 ) const;

		/// <summary>Unbind all texture from OpenGL.</summary>
		void UnbindTexture() const;

		/// <summary>Bind the framebuffer to OpenGL to hold the result of the next draws.</summary>
		virtual void Bind();

		/// <summary>Unbind the framebuffer from OpenGL.</summary>
		virtual void Unbind();

		/// <summary>
		/// Retrieve the width of the framebuffer texture.
		/// </summary>
		/// <returns>Width of the framebuffer texture.</returns>
		Uint32 GetWidth() const override;

		/// <summary>
		/// Retrieve the height of the framebuffer texture.
		/// </summary>
		/// <returns>Height of the framebuffer texture.</returns>
		Uint32 GetHeight() const override;

		/// <summary>Get the OpenGL ID of the attachement texture.</summary>
		/// <param name="_Type">Attachement to retrieve the texture ID from.</param>
		/// <returns>
		/// The OpenGL ID of the attachement texture.<para/>
		/// Return 0 if the attachement doesn't exist on the framebuffer.
		/// </returns>
		Uint32 GetAttachementTextureID( FramebufferAttachement::Type _Type = FramebufferAttachement::Type::Color_0 ) const;

		/// <summary>Get the tecxture of the attachement.</summary>
		/// <param name="_Type">Attachement to retrieve the texture from.</param>
		/// <returns>The texture of the attachement.</returns>
		Texture* GetAttachementTexture( FramebufferAttachement::Type _Type = FramebufferAttachement::Type::Color_0 );

		/// <summary>Get the tecxture of the attachement.</summary>
		/// <param name="_Type">Attachement to retrieve the texture from.</param>
		/// <returns>The texture of the attachement.</returns>
		const Texture* GetAttachementTexture( FramebufferAttachement::Type _Type = FramebufferAttachement::Type::Color_0 ) const;

		/// <summary>Retrieve the attachement available (created and bindable) on the framebuffer.</summary>
		/// <param name="_OutTypes">The available attachements.</param>
		void GetAvailableAttachementTypes( AE_Out std::vector<FramebufferAttachement::Type>& _OutTypes ) const;

		/// <summary>Check if the framebuffer has the specified attachement.</summary>
		/// <param name="_Type">Type of attachement to find in the framebuffer.</param>
		/// <returns>True if the framebuffer has the attachement, False otherwise.</returns>
		Bool HasAttachement( FramebufferAttachement::Type _Type ) const;

		/// <summary>
		/// Retrieve the first available attachemement. <para/>
		/// Priorities : Color then Depth or Depth/Stencil.<para/>
		/// Mostly for internal usage.
		/// </summary>
		/// <returns></returns>
		FramebufferAttachement::Type GetFirstAvailableAttachement() const;

		/// <summary>Set the samples count for all current attachements. If the attachements are not 2D, the function does nothing.</summary>
		/// <param name="_SamplesCount">The samples count to apply.</param>
		void SetSamplesCount( Uint32 _SamplesCount );

		/// <summary>
		/// Blit the <paramref name="_Other"/> onto the calling one : <para/>
		/// Copy the datas of the <paramref name="_Other"/> framebuffer into the calling one.
		/// </summary>
		/// <param name="_Other">The framebuffer to read.</param>
		/// <param name="_Filter">The filter to apply when blitting the textures.</param>
		/// <param name="_BlitColor">Should the color be blitted ?</param>
		/// <param name="_BlitDepth">Should the depth be blitted ?</param>
		/// <param name="_BlitStencil">Should the stencil be blitted ?</param>
		void Blit( const Framebuffer& _Other, TextureFilterMode _Filter = TextureFilterMode::Nearest, Bool _BlitColor = True, Bool _BlitDepth = False, Bool _BlitStencil = False ) const;


	protected:
		/// <summary>Initialize the framebuffer with OpenGL.</summary>
		void Create( const std::initializer_list<FramebufferAttachement>& _Attachements );

		/// <summary>Setup the attachement map with the provided preset.</summary>
		/// <param name="_Preset">The preset to apply.</param>
		void Create( AttachementPreset _Preset );

		/// <summary>Setup the attachement map with the new provided ones.</summary>
		/// <param name="_Attachements">The new attachements to place in the map.</param>
		void CreateAttachements( const std::initializer_list<FramebufferAttachement>& _Attachements );

		/// <summary>Update the attachements texture.</summary>
		void UpdateAttachement();

		/// <summary>Set the framebuffer attachements.</summary>
		void LinkAttachementToFramebuffer();

		/// <summary>Create the OpenGL framebuffer object.</summary>
		void CreateFramebuffer();

		/// <summary>
		/// Frees OpenGL texture and Framebuffer.
		/// </summary>
		void FreeResource();

		/// <summary>Destroy the OpenGL framebuffer object.</summary>
		void FreeFramebuffer();

		/// <summary>Specific bind to specify a read or draw mode.</summary>
		/// <param name="_Mode">The mode to apply when binding.</param>
		void BindForBlit( GLenum _Mode ) const;

		/// <summary>Specific unbind to specify a read or draw mode.</summary>
		/// <param name="_Mode">The mode to apply when unbinding</param>
		void UnbindForBlit( GLenum _Mode ) const;

	private:
		/// <summary>OpenGL ID of the framebuffer.</summary>
		Uint32 m_FramebufferID;

		/// <summary>Map of attachement with their texture IDs.</summary>
		AttachementMap m_Attachements;

		/// <summary>Width of the framebuffer.</summary>
		Uint32 m_Width;
		/// <summary>Height of the framebuffer.</summary>
		Uint32 m_Height;

		/// <summary>Track of all current bound FBO.</summary>
		static std::stack<Uint32> m_BoundFramebuffers;
	};

} // ae

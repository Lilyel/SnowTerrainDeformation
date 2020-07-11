#pragma once


#include "../../Toolbox/Toolbox.h"
#include "../Drawable/Drawable.h"
#include "Framebuffer.h"
#include "../Shader/ShaderParameter/ShaderParameterTexture.h"
#include "../Shader/ShaderParameter/ShaderParameterBool.h"

#include <functional>

namespace ae
{
    class Framebuffer;

    /// \ingroup graphics
    /// <summary>
    /// 2D holder to draw a framebuffer on the entire screen. Can be drawn on a Renderer.
    /// </summary>
    /// <seealso cref="Framebuffer"/>
    /// <seealso cref="Drawable"/>
    /// \par Example :
    /// \snippet SpriteSample/Code/main.cpp Sprite example
    class AERO_CORE_EXPORT FramebufferSprite : public Drawable
    {
    public:
        /// <summary>Create a sprite from a texture. The whole texture will be used.</summary>
        /// <param name="_Framebuffer">The framebuffer to use for the sprite.</param>
        FramebufferSprite( Framebuffer& _Framebuffer );

        /// <summary>Change the framebuffer attached to the sprite.</summary>
        /// <param name="_Framebuffer">The new framebuffer to use.</param>
        void SetFramebuffer( Framebuffer& _Framebuffer );
        
        /// <summary>Retrieve the current attached framebuffer.</summary>
        /// <returns>The current attached framebuffer.</returns>
        const Framebuffer& GetFramebuffer() const;

		/// <summary>Retrieve the current attached framebuffer.</summary>
		/// <returns>The current attached framebuffer.</returns>
		Framebuffer& GetFramebuffer();

        /// <summary>
        /// Set the attachement to draw.<para/>
        /// If the framebuffer doesn't have the attachement, the function does nothing.
        /// </summary>
        /// <param name="_Attachement">The attachement of the framebuffer to draw.</param>
        void SetAttachementToDraw( FramebufferAttachement::Type _Attachement );

        /// <summary>Get the attachement that the sprite is drawing.</summary>
        /// <returns>The framebuffer attachement that the sprite is drawing.</returns>
        FramebufferAttachement::Type GetAttachementToDraw() const;

		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		void ToEditor() override;

    private:
        /// <summary>
        /// Update the texture and IsDepth parameters according to the chosen attachement.<para/>
        /// If the parameters not longer exist, the function does nothing.
        /// </summary>
        void UpdateMaterialTexture();

        /// <summary>Setup the material to default framebuffer shader.</summary>
        void SetupMaterial();

    private:
        /// <summary>Reference to the framebuffer to render.</summary>
        std::reference_wrapper<Framebuffer> m_Framebuffer;

        /// <summary>Vertices to render that hold the texture.</summary>
        Vertex2DArray m_QuadVertices;
        /// <summary>Indices of the triangles made with the vertices.</summary>
        IndexArray m_QuadIndices;

        /// <summary>Attachement of the framebuffer to draw.</summary>
        FramebufferAttachement::Type m_Attachement;

        /// <summary>Parameter to texture of the shader.</summary>
        ShaderParameterTexture* m_TextureParameter;

        /// <summary>Parameter to know if we send the color or the depth attachement of the shader</summary>
        ShaderParameterBool* m_IsDepthParameter;
    };

} // ae

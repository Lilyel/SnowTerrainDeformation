#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Mesh/2D/Mesh2D.h"
#include "../../Maths/Primitives/TRect.h"
#include "../Vertex/VertexArray.h"

namespace ae
{
	class Texture2D;
	class ShaderParameterTextureBool;

	/// \ingroup graphics
	/// <summary>
	/// 2D holder for texture. Can be drawn on a Renderer.<para/>
	/// By default, the material is set with the parameters for the sprite shader shipped with the engine.
	/// </summary>
	/// <seealso cref="Texture"/>
	/// <seealso cref="Transform2D"/>
	/// <seealso cref="Drawable"/>
	/// \par Example :
	/// \snippet SpriteSample/Code/main.cpp Sprite example
	class AERO_CORE_EXPORT Sprite : public Mesh2D
	{
	public:
		/// <summary>Create a sprite from a texture. The whole texture will be used.</summary>
		/// <param name="_Texture">The texture to use for the sprite.</param>
		/// <param name="_NewMaterialInstance">
		/// Must create a new material instance for this sprite ?<para/>
		/// If set to False, the default 2D material is taken and will be shared with all others sprite and 2D shapes with the default material.
		/// </param>
		Sprite( const Texture2D& _Texture, Bool _NewMaterialInstance = True );
		/// <summary>Create a sprite from a texture. With the possibility to select a part of it.</summary>
		/// <param name="_Texture">The texture to use.</param>
		/// <param name="_SubRect">The area of the texture to use.</param>
		/// <param name="_IsNormalizedCoordinates">Area of the texture coordinates are in [0, 1] (True) or are pixel coordinates (False).</param>
		/// <param name="_NewMaterialInstance">
		/// Must create a new material instance for this sprite ?<para/>
		/// If set to False, the default 2D material is taken and will be shared with all others sprite and 2D shapes with the default material.
		/// </param>
		Sprite( const Texture2D& _Texture, const IntRect& _SubRect, Bool _IsNormalizedCoordinates = False, Bool _NewMaterialInstance = True );


		/// <summary>Change the texture.</summary>
		/// <param name="_Texture">The new texture to use.</param>
		/// <param name="_ResetRect">Override the old texture area to use the whole texture ?</param>
		void SetTexture( const Texture2D& _Texture, Bool _ResetRect = True );
		/// <summary>Change the texture.</summary>
		/// <param name="_Texture">The new texture to use.</param>
		/// <param name="_SubRect">The area of the texture to use.</param>
		/// <param name="_IsNormalizedCoordinates">Area of the texture coordinates are in [0, 1] (True) or are pixel coordinates (False).</param>
		void SetTexture( const Texture2D& _Texture, const IntRect& _SubRect, Bool _IsNormalizedCoordinates = False );
		/// <summary>Change the area of the texture to use.</summary>
		/// <param name="_SubRect">The new area of the texture to use.</param>
		/// <param name="_IsNormalizedCoordinates">Area of the texture coordinates are in [0, 1] (True) or are pixel coordinates (False).</param>
		void SetTextureRect( const IntRect& _SubRect, Bool _IsNormalizedCoordinates = False );
		
		/// <summary>Set the origin with relativ coordinates [0,1]</summary>
		/// <param name="_RelativOrigin">The new origin in relativ coordinates.</param>
		void SetRelativOrigin( const Vector2& _RelativOrigin );

		/// <summary>Set the origin with relativ coordinates [0,1]</summary>
		/// <param name="_RelativOriginX">The new origin X in relativ coordinates.</param>
		/// <param name="_RelativOriginY">The new origin Y in relativ coordinates.</param>
		void SetRelativOrigin( float _RelativOriginX, float _RelativOriginY );
		
		/// <summary>Set the current material for the sprite.</summary>
		/// <param name="_Material">The new material to apply to the sprite.</param>
		void SetMaterial( Material& _Material ) override;

		/// <summary>Get the current texture used for the sprite.</summary>
		/// <returns>The current texture used for the sprite.</returns>
		const Texture2D* GetTexture() const;

        /// <summary>
        /// Function called by the editor.
        /// It allows the class to expose some attributes for user editing.
        /// Think to call all inherited class function too when overloading.
        /// </summary>
        void ToEditor() override;

	private:
		/// <summary>Set the indices for the sprite quad mesh.</summary>
		void SetupIndices();

		/// <summary>Update the vertices of the sprite.</summary>
		void UpdateQuad();
			

		/// <summary>
		/// Update the texture parameter set by default in the constructor.<para/>
		/// If the parameters not longer exist, the function does nothing.
		/// </summary>
		void UpdateMaterialTexture();

		/// <summary>Setup the material to default 2D shader.</summary>
		/// <param name="_NewMaterialInstance">
		/// Must create a new material instance for this sprite ?<para/>
		/// If set to False, the default 2D material is taken and will be shared with all others sprite and 2D shapes with the default material.
		/// </param>
		void SetupMaterial( Bool _NewMaterialInstance );

	private:
		/// <summary>Reference to the texture to use.</summary>
		const Texture2D* m_Texture;

		/// <summary>Area of the texture to use.</summary>
		IntRect m_TextureRect;


		/// <summary>Texture parameter in the shader.</summary>
		ShaderParameterTextureBool* m_TextureParameter;
	};

} // ae


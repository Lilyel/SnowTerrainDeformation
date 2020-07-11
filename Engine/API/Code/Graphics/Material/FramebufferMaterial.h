#pragma once

#include "../../Toolbox/Toolbox.h"
#include "Material.h"
#include "../Shader/ShaderParameter/ShaderParameterTexture.h"
#include "../Shader/ShaderParameter/ShaderParameterBool.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>Framebuffer shading settings for rendering.</summary>
	/// <seealso cref="Material"/>
	/// <seealso cref="FramebufferSprite"/>
	class AERO_CORE_EXPORT FramebufferMaterial : public Material
	{
	public:
		/// <summary>Set the shader to the default framebuffer shader and create the its properties.</summary>
		FramebufferMaterial();

		/// <summary>Retrieve the parameter for the framebuffer texture.</summary>
		/// <returns>The parameter for the framebuffer texture.</returns>
		ShaderParameterTexture& GetTexture();

		/// <summary>Retrieve the parameter for the framebuffer texture.</summary>
		/// <returns>The parameter for the framebuffer texture.</returns>
		const ShaderParameterTexture& GetTexture() const;


		/// <summary>Retrieve the parameter for the IsDepth parameter.</summary>
		/// <returns>The parameter for the IsDepth parameter.</returns>
		ShaderParameterBool& GetIsDepth();

		/// <summary>Retrieve the parameter for the IsDepth parameter.</summary>
		/// <returns>The parameter for the IsDepth parameter.</returns>
		const ShaderParameterBool& GetIsDepth() const;

	private:
		/// <summary>Parameter for the framebuffer texture.</summary>
		ShaderParameterTexture* m_Texture;

		ShaderParameterBool* m_IsDepth;
	};

} // ae

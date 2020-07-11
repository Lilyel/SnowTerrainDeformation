#ifndef _DIRECTIONALLIGHT_AERO_H_
#define _DIRECTIONALLIGHT_AERO_H_

#include "../../../Toolbox/Toolbox.h"
#include "../Light.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// A 3D uniform light that enlight everything without distance attenuation.
	/// </summary>
	/// <seealso cref="Light" />
	/// <seealso cref="PointLight" />
	/// <seealso cref="SpotLight" />
	class AERO_CORE_EXPORT DirectionalLight : public Light
	{
	public:
        /// <summary>Build a 3D directional light</summary>
        DirectionalLight();

		/// <summary>Set shader uniform with light composant.</summary>
		/// <param name="_LightName">The light array name in the shader.</param>
		/// <param name="_LightIndex">The index in the array of the light.</param>
		/// <param name="_Shader">The shader to send the light to.</param>
		void SendToShader( const std::string& _LightName, Uint32 _LightIndex, const class Shader& _Shader ) override;
	};

} // ae

#endif // _DIRECTIONALLIGHT_AERO_H_
#ifndef _POINTLIGHT_AERO_H_
#define _POINTLIGHT_AERO_H_

#include "../../../Toolbox/Toolbox.h"
#include "../Light.h"
#include "../../Color/Color.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// A 3D point light.
	/// </summary>
	/// <seealso cref="Light" />
	/// <seealso cref="SpotLight" />
	/// <seealso cref="DirectionalLight" />
	class AERO_CORE_EXPORT PointLight : public Light
	{
	public:
		/// <summary>Build a 3D point light</summary>
		/// <param name="_Radius">The radius of the light.</param>
		PointLight( float _Radius = 10.0f );

		/// <summary>Set the light radius.</summary>
		/// <param name="_Radius">The new radius to apply.</param>
		void SetRadius( float _Radius );

		/// <summary>Get the light radius.</summary>
		/// <returns>Light radius.</returns>
		float GetRadius() const;

		/// <summary>Set shader uniform with light composant.</summary>
		/// <param name="_LightName">The light array name in the shader.</param>
		/// <param name="_LightIndex">The index in the array of the light.</param>
		/// <param name="_Shader">The shader to send the light to.</param>
		void SendToShader( const std::string& _LightName, Uint32 _LightIndex, const class Shader& _Shader ) override;

        /// <summary>
        /// Function called by the editor.
        /// It allows the class to expose some attributes for user editing.
        /// Think to call all inherited class function too when overloading.
        /// </summary>
        virtual void ToEditor() override;

	private:
		/// <summary>Radius of the light (Range).</summary>
		float m_Radius;
	};

} // ae

#endif // _POINTLIGHT_AERO_H_
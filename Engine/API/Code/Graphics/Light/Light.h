#ifndef _LIGHT_AERO_H_
#define _LIGHT_AERO_H_

#include "../../Toolbox/Toolbox.h"
#include "../../Maths/Transform/Transform.h"
#include "../Color/Color.h"
#include "../../World/WorldObject/WorldObject.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Basic class for lights.
	/// </summary>
	/// <seealso cref="Transform" />
	/// <seealso cref="PointLight" />
	/// <seealso cref="SpotLight" />
	/// <seealso cref="DirectionalLight" />
	class AERO_CORE_EXPORT Light : public Transform, public WorldObject
	{
    public:
        /// <summary>Enum listing the possible types of lights.</summary>
        enum class LightType : Uint8
        {
            /// <summary>Point light.</summary>
            Point,
            /// <summary>Spotlight.</summary>
            Spot,
            /// <summary>Directional light.</summary>
            Directional,

			/// <summary>Other kind of light.</summary>
			Unknown
        };

	public:
		/// <summary>Initialise a light.</summary>
		Light();

        /// <summary>Light destructor (remove the light from the world).</summary>
        virtual ~Light();

		/// <summary>Set the light color.</summary>
		/// <param name="_Color">The new color to apply.</param>
		void SetColor( const Color& _Color );

		/// <summary>Get the light color.</summary>
		/// <returns>Color of the light.</returns>
		const Color& GetColor() const;


		/// <summary>Set the light intensity.</summary>
		/// <param name="_Intensity">The light intensity.</param>
		void SetIntensity( float _Intensity );
		/// <summary>Get the light intensity.</summary>
		/// <returns>The current light intensity.</returns>
		float GetIntensity() const;

		/// <summary>Set shader uniform with light composant.</summary>
		/// <param name="_LightName">The light array name in the shader.</param>
		/// <param name="_LightIndex">The index in the array of the light.</param>
		/// <param name="_Shader">The shader to send the light to.</param>
		virtual void SendToShader( const std::string& _LightName, Uint32 _LightIndex, const class Shader& _Shader ) AE_IsVirtualPure;

        /// <summary>Get the light type.</summary>
        /// <returns>The light type.</returns>
        LightType GetLightType() const;

        /// <summary>
        /// Function called by the editor.
        /// It allows the class to expose some attributes for user editing.
        /// Think to call all inherited class function too when overloading.
        /// </summary>
        virtual void ToEditor() override;

	protected:
		/// <summary>Light color.</summary>
		Color m_Color;

		/// <summary>Intensity of the light.</summary>
		float m_Intensity;

        /// <summary>Type of the light.</summary>
        LightType m_Type;
	};

} // ae

#endif // _LIGHT_AERO_H_
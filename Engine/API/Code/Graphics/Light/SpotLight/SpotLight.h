#ifndef _SPOTLIGHT_AERO_H_
#define _SPOTLIGHT_AERO_H_

#include "../../../Toolbox/Toolbox.h"
#include "../Light.h"
#include "../../Color/Color.h"
#include "../../../Maths/Functions/MathsFunctions.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Instantiate a 3D spotlight. ( Torchlight ).
	/// The outer angle is the maximum limit of the spotlight on the sides.
	/// All the area inside the inner cone will have the maximum light intensity.
	/// </summary>
	/// <seealso cref="Light" />
	/// <seealso cref="PointLight" />
	/// <seealso cref="DirectionalLight" />
	class AERO_CORE_EXPORT SpotLight : public Light
	{
	public:
		/// <summary>Build a spot light.</summary>
		/// <param name="_InnerAngle">The inner angle of the light cone.</param>
		/// <param name="_OuterAngle">The outer angle of the light cone.</param>
		/// <param name="_Range">The spot range.</param>
		SpotLight( float _InnerAngle = 0.0f, float _OuterAngle = Math::DegToRad( 45.0f ), float _Range = 100.0f );

		/// <summary>Set the angle of the inner cone.</summary>
		/// <param name="_Angle">The new angle to apply.</param>
		void SetInnerAngle( float _Angle );

		/// <summary>Get the inner cone angle.</summary>
		/// <returns>Inner cone angle.</returns>
		float GetInnerAngle() const;


		/// <summary>Set the angle of the outer cone.</summary>
		/// <param name="_Angle">The new angle to apply.</param>
		void SetOuterAngle( float _Angle );

		/// <summary>Get the outer cone angle.</summary>
		/// <returns>Outer cone angle.</returns>
		float GetOuterAngle() const;

		/// <summary>Set the inner and outer cone angles.</summary>
		/// <param name="_InnerAngle">The new inner cone angle.</param>
		/// <param name="_OuterAngle">The new outer cone angle.</param>
		void SetAngles( float _InnerAngle, float _OuterAngle );


		/// <summary>Set the spot light range</summary>
		/// <param name="_Range">The new range to apply.</param>
		void SetRange( float _Range );
		/// <summary>Get the spot range.</summary>
		/// <returns>The spot light range.</returns>
		float GetRange();

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
		/// <summary>Inner cone angle.</summary>
		float m_InnerAngle;
		/// <summary>Outer cone angle.</summary>
		float m_OuterAngle;

		/// <summary>Range of the spot.</summary>
		float m_Range;
	};

} // ae

#endif // _SPOTLIGHT_AERO_H_
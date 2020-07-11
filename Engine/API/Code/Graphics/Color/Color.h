#ifndef _COLOR_AERO_H_
#define _COLOR_AERO_H_

#include "../../Toolbox/Toolbox.h"

#include <string>
#include <iostream>

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Represent a color RGBA.
	/// Values are between 0.0 and 1.0.
	/// </summary>
	class AERO_CORE_EXPORT Color
	{
	public:
		/// <summary>
		/// Default Constructor.
		/// Create a White color.
		/// </summary>
		Color();

		/// <summary>
		/// Create color from given component.<para/>
		/// The value will be converted to floats. (Divided by 255).
		/// </summary>
		/// <param name="_Red">The red component.</param>
		/// <param name="_Green">The green component.</param>
		/// <param name="_Blue">The blue component.</param>
		/// <param name="_Alpha">The alpha component.</param>
		explicit Color( Uint8 _Red, Uint8 _Green, Uint8 _Blue, Uint8 _Alpha = 255 );

		/// <summary>
		/// Create color from given component.<para/>
		/// The value will be converted to floats. (Divided by 255).
		/// </summary>
		/// <param name="_Red">The red component.</param>
		/// <param name="_Green">The green component.</param>
		/// <param name="_Blue">The blue component.</param>
		/// <param name="_Alpha">The alpha component.</param>
		explicit Color( Uint32 _Red, Uint32 _Green, Uint32 _Blue, Uint32 _Alpha = 255 );

		/// <summary>Create color from given component.</summary>
		/// <param name="_Red">The red component.</param>
		/// <param name="_Green">The green component.</param>
		/// <param name="_Blue">The blue component.</param>
		/// <param name="_Alpha">The alpha component.</param>
		explicit Color( float _Red, float _Green, float _Blue, float _Alpha = 1.0f );

		/// <summary>Copy constructor</summary>
		/// <param name="_Color">The second color to do a copy from.</param>
		Color( const Color& _Color );


		/// <summary>
		/// Copy operator with a color.
		/// </summary>
		/// <param name="_Color">The color to copy.</param>
		/// <returns>The calling color after the copy.</returns>
		inline Color& operator=( const Color& _Color );


		/// <summary>Multiply the components with the corresponding ones of <paramref name="_Color2">.</summary>
		/// <param name="_Color2">The second color.</param>
		/// <returns>The calling operator after the operation.</returns>
		inline Color& operator*=( const Color& _Color2 );

		/// <summary>Multiplication each component with the value.</summary>
		/// <param name="_Value">The value to multiply each component with.</param>
		/// <returns>The calling operator after the operation</returns>
		inline Color& operator*=( const float _Value );

		/// <summary>Divide the components with the corresponding ones of <paramref name="_Color2">.</summary>
		/// <param name="_Color2">The second color.</param>
		/// <returns>The calling operator after the operation.</returns>
		inline Color& operator/=( const Color& _Color2 );

		/// <summary>Divide each component with the value.</summary>
		/// <param name="_Value">The value to divide each component with.</param>
		/// <returns>The calling operator after the operation</returns>
		inline Color& operator/=( const float _Value );

		/// <summary>Subtract the components with the corresponding ones of <paramref name="_Color2">.</summary>
		/// <param name="_Color2">The second color.</param>
		/// <returns>The calling operator after the operation.</returns>
		inline Color& operator-=( const Color& _Color2 );

		/// <summary>Subtract each component with the value.</summary>
		/// <param name="_Value">The value to subtract each component with.</param>
		/// <returns>The calling operator after the operation</returns>
		inline Color& operator-=( const float _Value );

		/// <summary>Add the components with the corresponding ones of <paramref name="_Color2">.</summary>
		/// <param name="_Color2">The second color.</param>
		/// <returns>The calling operator after the operation.</returns>
		inline Color& operator+=( const Color& _Color2 );

		/// <summary>Add each component with the value.</summary>
		/// <param name="_Value">The value to add each component with.</param>
		/// <returns>The calling operator after the operation</returns>
		inline Color& operator+=( const float _Value );

		/// <summary>Retrieve the red component of the color</summary>
		/// <returns>Retrieve the red component of the color</returns>
		inline float R() const;

		/// <summary>Retrieve the green component of the color</summary>
		/// <returns>Retrieve the green component of the color</returns>
		inline float G() const;

		/// <summary>Retrieve the blue component of the color</summary>
		/// <returns>Retrieve the blue component of the color</returns>
		inline float B() const;

		/// <summary>Retrieve the alpha component of the color</summary>
		/// <returns>Retrieve the alpha component of the color</returns>
		inline float A() const;

		/// <summary>Set the red component of the color</summary>
		/// <param name="_R">The new red value</param>
		inline void R( float _R );

		/// <summary>Set the green component of the color</summary>
		/// <param name="_G">The new green value</param>
		inline void G( float _G );

		/// <summary>Set the blue component of the color</summary>
		/// <param name="_B">The new blue value</param>
		inline void B( float _B );

		/// <summary>Set the alpha component of the color</summary>
		/// <param name="_A">The new alpha value</param>
		inline void A( float _A );

		/// <summary>Set the components of the color</summary>
		/// <param name="_R">The new red value</param>
		/// <param name="_G">The new green value</param>
		/// <param name="_B">The new blue value</param>
		/// <param name="_A">The new alpha value</param>
		inline void Set( float _R, float _G, float _B, float _A );

		/// <summary>Set the components of the color</summary>
		/// <param name="_R">The new red value</param>
		/// <param name="_G">The new green value</param>
		/// <param name="_B">The new blue value</param>
		inline void Set( float _R, float _G, float _B );

	private:
		/// <summary> Red component of the color. </summary>
		float m_R;
		/// <summary> Green component of the color. </summary>
		float m_G;
		/// <summary> Blue component of the color. </summary>
		float m_B;
		/// <summary> Alpha (transparency) component of the color. </summary>
		float m_A;

	public:
		/// <summary> 
		/// The black color.
		/// r = 1, g = 1, b = 1, a = 1.
		/// </summary>
		static const Color Black;

		/// <summary> 
		/// The white color.
		/// r = 0, g = 0, b = 0, a = 1.
		/// </summary>
		static const Color White;

		/// <summary> 
		/// The transparent color.
		/// r = 0, g = 0, b = 0, a = 0.
		/// </summary>
		static const Color Transparent;


		/// <summary> 
		/// The red color.
		/// r = 1, g = 0, b = 0, a = 1.
		/// </summary>
		static const Color Red;

		/// <summary> 
		/// The green color.
		/// r = 0, g = 1, b = 0, a = 1.
		/// </summary>
		static const Color Green;

		/// <summary> 
		/// The blue color.
		/// r = 0, g = 0, b = 1, a = 1.
		/// </summary>
		static const Color Blue;

		/// <summary> 
		/// The yellow color.
		/// r = 1, g = 1, b = 0, a = 1.
		/// </summary>
		static const Color Yellow;

		/// <summary> 
		/// The cyan color.
		/// r = 0, g = 1, b = 1, a = 1.
		/// </summary>
		static const Color Cyan;

		/// <summary> 
		/// The magenta color.
		/// r = 1, g = 0, b = 1, a = 1.
		/// </summary>
		static const Color Magenta;
	};



	/// <summary>Multiply each component of each color between them ( Red with Red, Green with Green, ... ).</summary>
	/// <param name="_Color1">The first color to multiply.</param>
	/// <param name="_Color2">The second color to multiply.</param>
	/// <returns>The result of the operation as a new color</returns>
	AERO_CORE_EXPORT inline Color operator*( const Color& _Color1, const Color& _Color2 );

	/// <summary>Multiply each component of the color with the value.</summary>
	/// <param name="_Color1">The first color to multiply.</param>
	/// <param name="_Value">The value to multiply components with.</param>
	/// <returns>The result of the operation as a new color</returns>
	AERO_CORE_EXPORT inline Color operator*( const Color& _Color, const float _Value );


	/// <summary>Divide each component of each color between them ( Red with Red, Green with Green, ... ).</summary>
	/// <param name="_Color1">The first color to divide.</param>
	/// <param name="_Color2">The second color to divide.</param>
	/// <returns>The result of the operation as a new color</returns>
	AERO_CORE_EXPORT inline Color operator/( const Color& _Color1, const Color& _Color2 );

	/// <summary>Divide each component of the color with the value.</summary>
	/// <param name="_Color1">The first color to divide.</param>
	/// <param name="_Value">The value to divide components with.</param>
	/// <returns>The result of the operation as a new color</returns>
	AERO_CORE_EXPORT inline Color operator/( const Color& _Color, const float _Value );


	/// <summary>Subtract each component of each color between them ( Red with Red, Green with Green, ... ).</summary>
	/// <param name="_Color1">The first color to subtract.</param>
	/// <param name="_Color2">The second color to subtract.</param>
	/// <returns>The result of the operation as a new color</returns>
	AERO_CORE_EXPORT inline Color operator-( const Color& _Color1, const Color& _Color2 );

	/// <summary>Subtract each component of the color with the value.</summary>
	/// <param name="_Color1">The first color to subtract.</param>
	/// <param name="_Value">The value to subtract components with.</param>
	/// <returns>The result of the operation as a new color</returns>
	AERO_CORE_EXPORT inline Color operator-( const Color& _Color, const float _Value );


	/// <summary>Add each component of each color between them ( Red with Red, Green with Green, ... ).</summary>
	/// <param name="_Color1">The first color to add.</param>
	/// <param name="_Color2">The second color to add.</param>
	/// <returns>The result of the operation as a new color</returns>
	AERO_CORE_EXPORT inline Color operator+( const Color& _Color1, const Color& _Color2 );

	/// <summary>Add each component of the color with the value.</summary>
	/// <param name="_Color1">The first color to add.</param>
	/// <param name="_Value">The value to add components with.</param>
	/// <returns>The result of the operation as a new color</returns>
	AERO_CORE_EXPORT inline Color operator+( const Color& _Color, const float _Value );


	/// <summary>Compare each component of each color between them ( Red with Red, Green with Green, ... ).</summary>
	/// <param name="_Color1">The first color to compare.</param>
	/// <param name="_Value">The second color to compare.</param>
	/// <returns>True if all components are the same in each colors</returns>
	AERO_CORE_EXPORT inline Bool operator==( const Color& _Color1, const Color& _Color2 );

	/// <summary>Compare each component of each color between them ( Red with Red, Green with Green, ... ).</summary>
	/// <param name="_Color1">The first color to compare.</param>
	/// <param name="_Value">The second color to compare.</param>
	/// <returns>True if one of the components are NOT the same.</returns>
	AERO_CORE_EXPORT inline Bool operator!=( const Color& _Color1, const Color& _Color2 );


	/// <summary>Convert a color to a string.</summary>
	/// <param name="_Color">Color to convert.</param>
	/// <returns>Color as a C++ string. ( Format : R = 0   G = 0   B = 0   A = 0 ).</returns>
	AERO_CORE_EXPORT inline std::string ToString( const ae::Color& _Color );

} // ae


/// <summary>Convert a color to a string and push it in the out stream.</summary>
/// <param name="_Color">Color to convert and push to the out stream.</param>
/// <returns>Out stream.</returns>
AERO_CORE_EXPORT std::ostream& operator<<( std::ostream& os, const ae::Color& _Color );

#endif
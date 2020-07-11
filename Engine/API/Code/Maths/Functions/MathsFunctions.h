#pragma once

#include "../../Toolbox/Toolbox.h"

#include "../../Maths/Vector/Vector3.h"
#include "../../Maths/Vector/Vector2.h"

#include <cmath>
#include <limits>

namespace ae
{
    /// \ingroup math
	/// <summary>Regroup a set of maths functions and constants.</summary>
    class Math
    {
    public:
        ///
        ///			Fibonacci
        ///

		/// <summary>
		/// Golen Ratio.<para/>
		/// https://en.wikipedia.org/wiki/Golden_ratio <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <returns>Golden ratio.</returns>
        template<typename T>
        inline static constexpr T GoldenRatio()
        {
            return ( ( static_cast<T>( 1.0 ) + Sqrt( static_cast<T>( 5.0 ) ) ) / static_cast<T>( 2.0 ) );
        }

		/// <summary>
		/// Golen Ratio as Float.<para/>
		/// https://en.wikipedia.org/wiki/Golden_ratio <para/>
		/// </summary>
		/// <returns>Golden ratio.</returns>
        inline static constexpr float GoldenRatio()
        {
            return GoldenRatio<float>();
        }

        ///
        ///			Trigonometry
        ///

		/// <summary>
		/// Pi number. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <returns>Pi number.</returns>
        template<typename T>
        inline static constexpr T Pi()
        {
            return static_cast<T>( 3.1415926535897932384626433832795028841971693993751058209749445923078164062 );
        }

		/// <summary>Pi number as Float.</summary>
		/// <returns>Pi number.</returns>
        inline static constexpr float Pi()
        {
            return Pi<float>();
        }


		/// <summary>
		/// 1 / Pi. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <returns>1 / Pi.</returns>
        template<typename T>
        inline static constexpr T OneDivByPi()
        {
            return static_cast<T>( static_cast<T>( 1.0 ) / Pi<T>() );
        }

		/// <summary>1 / Pi as Float.</summary>
		/// <returns>1 / Pi.</returns>
        inline static constexpr float OneDivByPi()
        {
            return static_cast<float>( OneDivByPi<double>() );
        }


		/// <summary>
		/// Pi / 180. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <returns>Pi / 180.</returns>
        template<typename T>
        inline static constexpr T PiDivBy180()
        {
            return static_cast<T>( Pi<T>() / static_cast<T>( 180.0 ) );
        }

		/// <summary>Pi / 180 as Float.</summary>
		/// <returns>Pi / 180.</returns>
        inline static constexpr float PiDivBy180()
        {
            return static_cast<float>( PiDivBy180<double>() );
        }


		/// <summary>
		/// 180 / Pi. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <returns>180 / Pi.</returns>
        template<typename T>
        inline static constexpr T PiDiv180()
        {
            return static_cast<T>( static_cast<T>( 180.0 ) / Pi<T>() );
        }

		/// <summary>180 / Pi as Float.</summary>
		/// <returns>180 / Pi.</returns>
        inline static constexpr float PiDiv180()
        {
            return static_cast<float>( PiDiv180<double>() );
        }


		/// <summary>
		/// Pi / 4. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <returns>Pi / 4.</returns>
        template<typename T>
        inline static constexpr T PiDivBy4()
        {
            return static_cast<T>( Pi<T>() / static_cast<T>( 4.0 ) );
        }

		/// <summary>Pi / 4 as Float.</summary>
		/// <returns>Pi / 4.</returns>
        inline static constexpr float PiDivBy4()
        {
            return static_cast<float>( PiDivBy4<double>() );
        }


		/// <summary>
		/// Pi / 2. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <returns>Pi / 2.</returns>
        template<typename T>
        inline static constexpr T PiDivBy2()
        {
            return static_cast<T>( Pi<T>() / static_cast<T>( 2.0 ) );
        }

		/// <summary>Pi / 2 as Float.</summary>
		/// <returns>Pi / 2.</returns>
        inline static constexpr float PiDivBy2()
        {
            return static_cast<float>( PiDivBy2<double>() );
        }


		/// <summary>
		/// Pi * 2. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <returns>Pi * 2.</returns>
        template<typename T>
        inline static constexpr T PiMulBy2()
        {
            return static_cast<T>( Pi<T>() * static_cast<T>( 2.0 ) );
        }

		/// <summary>Pi * 2 as Float.</summary>
		/// <returns>Pi * 2.</returns>
        inline static constexpr float PiMulBy2()
        {
            return static_cast<float>( PiMulBy2<double>() );
        }


		/// <summary>
		/// Convert radians to degrees. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Angle">Angle in radians to convert in degrees.</param>
		/// <returns>Angle converted in degrees.</returns>
        template<typename T>
        inline static T RadToDeg( const T& _Angle )
        {
            return ( _Angle * PiDiv180<T>() );
        }

		/// <summary>Convert Euler angles in radians to degrees.</summary>
		/// <param name="_EulerAngles">Euler angle in radians to convert in degrees.</param>
		/// <returns>Euler angles converted in degrees.</returns>
		inline static Vector3 RadToDeg( const Vector3& _EulerAngles )
		{
			return Vector3( _EulerAngles.X * PiDiv180<float>(), _EulerAngles.Y * PiDiv180<float>(), _EulerAngles.Z * PiDiv180<float>() );
		}
		
		/// <summary>
		/// Convert a constexpr angle in radians to degrees. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Angle">Constexpr angle in radians to convert in degrees.</param>
		/// <returns>Angle converted in degrees.</returns>
		template<typename T>
		inline static constexpr T RadToDeg_Const( const T& _Angle )
		{
			return ( _Angle * PiDiv180<T>() );
		}


		/// <summary>
		/// Convert degrees to radians. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Angle">Angle in degrees to convert in radians.</param>
		/// <returns>Angle converted in radians.</returns>
        template<typename T>
        inline static T DegToRad( const T& _Angle )
        {
            return ( _Angle * PiDivBy180<T>() );
        }

		/// <summary>Convert Euler angles in degrees to radians.</summary>
		/// <param name="_EulerAngles">Euler angles in degrees to convert in radians.</param>
		/// <returns>Euler angles converted in radians.</returns>
		inline static Vector3 DegToRad( const Vector3& _EulerAngles )
		{
			return Vector3( _EulerAngles.X * PiDivBy180<float>(), _EulerAngles.Y * PiDivBy180<float>(), _EulerAngles.Z * PiDivBy180<float>() );
		}

		/// <summary>
		/// Convert constexpr angle in degrees to radians. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Angle">Constexpr angle in degrees to convert in radians.</param>
		/// <returns>Angle converted in radians.</returns>
		template<typename T>
		inline static constexpr T DegToRad_Const( const T& _Angle )
		{
			return ( _Angle * PiDivBy180<T>() );
		}


		/// <summary>
		/// Cosinus of an angle in radians. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Angle">Angle in radians to use for the cosinus.</param>
		/// <returns>Cosinus of the angle.</returns>
        template<typename T>
        inline static T Cos( const T& _Angle )
        {
            return cos( _Angle );
        }


		/// <summary>
		/// Arc Cosinus of an angle in radians. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Angle">Angle in radians to use for the arc cosinus.</param>
		/// <returns>Arc cosinus of the angle.</returns>
        template<typename T>
        inline static T ACos( const T& _Angle )
        {
            return acos( _Angle );
        }


		/// <summary>
		/// Sinus of an angle in radians. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Angle">Angle in radians to use for the sinus.</param>
		/// <returns>Sinus of the angle.</returns>
        template<typename T>
        inline static T Sin( const T& _Angle )
        {
            return sin( _Angle );
        }

		/// <summary>
		/// Arc sinus of an angle in radians. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Angle">Angle in radians to use for the arc sinus.</param>
		/// <returns>Arc sinus of the angle.</returns>
        template<typename T>
        inline static T ASin( const T& _Angle )
        {
            return asin( _Angle );
        }


		/// <summary>
		/// Tangente of an angle in radians. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Angle">Angle in radians to use for the tangente.</param>
		/// <returns>Tangente of the angle.</returns>
        template<typename T>
        inline static T Tan( const T& _Angle )
        {
            return tan( _Angle );
        }


		/// <summary>
		/// Arc tangente of an angle in radians. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Angle">Angle in radians to use for the arc tangente.</param>
		/// <returns>Arc tangente of the angle.</returns>
        template<typename T>
        inline static T ATan( const T& _Angle )
        {
            return atan( _Angle );
        }


		/// <summary>
		/// Arc tangente 2  of a vector ( position 2D ). <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_X">X composante of vector.</param>
		/// <param name="_Y">Y composante of vector.</param>
		/// <returns>Arc tangente 2 of the position.</returns>
        template<typename T>
        inline static T ATan2( const T& _X, const T& _Y )
        {
            return atan2( _X, _Y );
        }


		/// <summary>
		/// Arc tangente 2  of a vector ( position 2D ) as Float. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Position">2D Position.</param>
		/// <param name="_Clockwise">Determine if the returned angle is clockwise or not.</param>
		/// <returns>Arc tangente 2 of the position.</returns>
		inline static float ATan2( const Vector2& _Position, Bool _Clockwise = True )
		{
			if( _Clockwise )
				return ATan2<float>( _Position.Y, _Position.X );
			else
				return ATan2<float>( _Position.X, _Position.Y );
		}


        ///
        ///				Numerics
        ///

		/// <summary>
		/// Epsilon value ( very small ) ( 5 decimal ). <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <returns>Epsilon value.</returns>
        template<typename T>
        inline static constexpr T Epsilon()
        {
            return static_cast<T>( 0.00001 );
        }

		/// <summary>Epsilon value ( very small ) ( 5 decimal ) as Float.</summary>
		/// <returns>Epsilon value.</returns>
        inline static constexpr float Epsilon()
        {
            return static_cast<float>( Epsilon<double>() );
        }

		/// <summary>
		/// Epsilon ( very small value ) on which you can choose the number of decimal. <para/>
		/// For example, a precision of 1 will give 0.1. For 5 it will give 0.00001. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <returns>Epsilon value.</returns>
        template<typename T, Uint8 Precision>
        inline static constexpr T Epsilon()
        {
            return static_cast<T>( 1.0 ) / Pow<T>( static_cast<T>( 10.0 ), static_cast<T>( Precision ) );
        }

		/// <summary>
		/// Power of 2 of Epsilon value ( very very small ) ( 10 decimal ). <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <returns>Power of 2 of Epsilon value.</returns>
        template<typename T>
        inline static constexpr T EpsilonSquared()
        {
            return static_cast<T>( 0.0000000001 );
        }

		/// <summary>Power of 2 of Epsilon value ( very very small ) ( 10 decimal ) as Float. </summary>
		/// <returns>Power of 2 of Epsilon value.</returns>
        inline static constexpr float EpsilonSquared()
        {
            return static_cast<float>( EpsilonSquared<double>() );
        }


		/// <summary>
		/// Absolute of a value ( always positive ). <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Number to retrieve its positive value.</param>
		/// <returns>Positive value of <paramref name="_Value"/>.</returns>
        template<typename T>
        inline static T Abs( const T& _Value )
        {
            return  ( ( _Value < 0 ) ? ( -_Value ) : _Value );
        }


		/// <summary>
		/// Process the maximum between two values. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_A">First value to compare.</param>
		/// <param name="_B">Second value to compare.</param>
		/// <returns>Biggest value between <paramref name="_A"/> and <paramref name="_B"/>.</returns>
        template<typename T>
        inline static T Max( const T& _A, const T& _B )
        {
            return  ( ( _A > _B ) ? _A : _B );
        }


		/// <summary>
		/// Process the minmum between two values. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_A">First value to compare.</param>
		/// <param name="_B">Second value to compare.</param>
		/// <returns>Smallest value between <paramref name="_A"/> and <paramref name="_B"/>.</returns>
        template<typename T>
        inline static T Min( const T& _A, const T& _B )
        {
            return  ( ( _A < _B ) ? _A : _B );
        }


		/// <summary>
		/// Force a value to be in an interval. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Min">Minimum of the interval.</param>
		/// <param name="_Max">Maximum of the interval.</param>
		/// <param name="_Value">Number to force to be between <paramref name="_Min"/> and  <paramref name="_Max"/>.</param>
		/// <returns>
		/// <paramref name="_Min"/> if <paramref name="_Value"/> is smaller than <paramref name="_Min"/>.
		/// <paramref name="_Max"/> if <paramref name="_Value"/> is bigger than <paramref name="_Max"/>.
		/// <paramref name="_Value"/> otherwise.
		/// </returns>
        template<typename T>
        inline static T Clamp( const T& _Min, const T& _Max, const T& _Value )
        {
            return ( ( _Value > _Max ) ? _Max : ( ( _Value < _Min ) ? _Min : _Value ) );
        }


		/// <summary>
		/// Force a value to be in the interval [0, 1]. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Number to force to be between 0 and 1.</param>
		/// <returns>
		/// 0 if <paramref name="_Value"/> is smaller than 0.
		/// 1 if <paramref name="_Value"/> is bigger than 1.
		/// <paramref name="_Value"/> otherwise.
		/// </returns>
        template<typename T>
        inline static T Clamp01( const T& _Value )
        {
			return Clamp( static_cast<T>( 0 ), static_cast<T>( 1 ), _Value );
        }


		/// <summary>
		/// Look if the value is equal to 0 +/- Epsilon. <para/>
		/// Useful for floating values that are not often very equal to 0. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Value to compare with 0 +/- Epsilon.</param>
		/// <returns>True if almost equal to 0, false otherwise.</returns>
        template<typename T>
        inline static Bool IsNullByEpsilon( const T& _Value )
        {
            return ( Abs( _Value ) <= Epsilon<T>() );
        }

		/// <summary>
		/// Look if the value is equal to 0 +/- EpsilonSquared. <para/>
		/// Useful for floating values that are not often very equal to 0. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Value to compare with 0 +/- EpsilonSquared.</param>
		/// <returns>True if almost equal to 0, false otherwise.</returns>
        template<typename T>
        inline static Bool IsNullByEpsilonSquared( const T& _Value )
        {
            return ( Abs( _Value ) <= EpsilonSquared<T>() );
        }


		/// <summary>
		/// Look if the value is equal to other value +/- Epsilon. <para/>
		/// Useful for floating values that are not often very equal to each others. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">To compare with <paramref name="_EqualTo"/> +/- Epsilon.</param>
		/// <param name="_EqualTo">Value +/- Epsilon to compare <paramref name="_Value"/> with.</param>
		/// <returns>True if <paramref name="_Value"/> is almost equal to <paramref name="_EqualTo"/> +/- Epsilon, false otherwise.</returns>
        template<typename T>
        inline static Bool IsEqualByEpsilon( const T& _Value, const T& _EqualTo )
        {
			return IsNullByEpsilon( _Value - _EqualTo );
        }

		/// <summary>
		/// Look if the value is equal to other value +/- EpsilonSquared. <para/>
		/// Useful for floating values that are not often very equal to each others. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">To compare with <paramref name="_EqualTo"/> +/- EpsilonSquared.</param>
		/// <param name="_EqualTo">Value +/- Epsilon to compare <paramref name="_Value"/> with.</param>
		/// <returns>True if <paramref name="_Value"/> is almost equal to <paramref name="_EqualTo"/> +/- EpsilonSquared, false otherwise.</returns>
        template<typename T>
        inline static Bool IsEqualByEpsilonSquared( const T& _Value, const T& _EqualTo )
        {
			return IsNullByEpsilonSquared( _Value - _EqualTo );
        }


		/// <summary>
		/// Linear interpolation between two values. <para/>
		/// https://en.wikipedia.org/wiki/Linear_interpolation <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Start">Start of the linear interpolation.</param>
		/// <param name="_End">End of the linear interpolation.</param>
		/// <param name="_Time">Progress in the linear interpolation ( usually in [0, 1] interval ).</param>
		/// <returns>Result of the linear interpolation between <paramref name="_Start"/> and <paramref name="_End"/> at <paramref name="_Time"/> time.</returns>
        template<typename T>
        inline static T Lerp( const T& _Start, const T& _End, const float _Time )
        {
            return _Start * ( 1.0f - _Time ) + _End * _Time;
        }


		/// <summary>
		/// Linear interpolation between two values. <para/>
		/// It is a different algorithm from Lerp. There is one less multiplication 
		/// but it is not guaranteed to arrive to <paramref name="_End"/> exactly. <para/>
		/// https://en.wikipedia.org/wiki/Linear_interpolation <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Start">Start of the linear interpolation.</param>
		/// <param name="_End">End of the linear interpolation.</param>
		/// <param name="_Time">Progress in the linear interpolation ( usually in [0, 1] interval ).</param>
		/// <returns>Result of the linear interpolation between <paramref name="_Start"/> and <paramref name="_End"/> at <paramref name="_Time"/> time.</returns>
        template<typename T>
        inline static T LerpNotAccurate( const T& _Start, const T& _End, const float _Time )
        {
            return _Start + ( _End - _Start ) * _Time;
        }



		/// <summary>
		/// Bilinear interpolation between two pair of values.<para/>
		/// Interpolate from bottom left to top right value.<para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_BottomLeft">Start of linear the interpolation.</param>
		/// <param name="_BottomRight">End of the linear interpolation at the bottom.</param>
		/// <param name="_TopLeft">Start of the linear interpolation at the top.</param>
		/// <param name="_TopRight">End of the linear interpolation at the top.</param>
		/// <param name="_TimeHorizontal">Progress in the linear interpolation between the two bottoms and the two tops ( usually in [0, 1] interval ).</param>
		/// <param name="_Time">
		/// Progress in the linear interpolation between the result of the two linear interpolations 
		/// between the two bottoms and the two tops ( usually in [0, 1] interval ).
		/// </param>
		/// <returns>Result of the linear interpolation between <paramref name="_Start"/> and <paramref name="_End"/> at <paramref name="_Time"/> time.</returns>
		template<typename T>
		inline static T BiLerp( const T& _BottomLeft, const T& _BottomRight, const T& _TopRight, const T& _TopLeft, const float _TimeHorizontal, const float _TimeVertical )
		{
			const T LerpHorizontalBottom = Lerp( _BottomLeft, _BottomRight, _TimeHorizontal );
			const T LerpHorizontalTop = Lerp( _TopLeft, _TopRight, _TimeHorizontal );

			return Lerp( LerpHorizontalBottom, LerpHorizontalTop, _TimeVertical );
		}


		/// <summary>
		/// Bilinear interpolation between two pair of values.<para/>
		/// Interpolate from bottom left to top right value.<para/>
		/// It is a different algorithm from Lerp. There is 3 less multiplication
		/// but it is not guaranteed to arrive to end exactly. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_BottomLeft">Start of linear the interpolation.</param>
		/// <param name="_BottomRight">End of the linear interpolation at the bottom.</param>
		/// <param name="_TopLeft">Start of the linear interpolation at the top.</param>
		/// <param name="_TopRight">End of the linear interpolation at the top.</param>
		/// <param name="_TimeHorizontal">Progress in the linear interpolation between the two bottoms and the two tops ( usually in [0, 1] interval ).</param>
		/// <param name="_Time">
		/// Progress in the linear interpolation between the result of the two linear interpolations 
		/// between the two bottoms and the two tops ( usually in [0, 1] interval ).
		/// </param>
		/// <returns>Result of the linear interpolation between <paramref name="_Start"/> and <paramref name="_End"/> at <paramref name="_Time"/> time.</returns>
		template<typename T>
		inline static T BiLerpNotAccurate( const T& _BottomLeft, const T& _BottomRight, const T& _TopRight, const T& _TopLeft, const float _TimeHorizontal, const float _TimeVertical )
		{
			const T LerpHorizontalBottom = LerpNotAccurate( _BottomLeft, _BottomRight, _TimeHorizontal );
			const T LerpHorizontalTop = LerpNotAccurate( _TopLeft, _TopRight, _TimeHorizontal );

			return LerpNotAccurate( LerpHorizontalBottom, LerpHorizontalTop, _TimeVertical );
		}


		/// <summary>
		/// Round a number to the nearest integer. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Number to round.</param>
		/// <returns><paramref name="_Value"/> rounded to the nearest integer.</returns>
        template<typename T>
        inline static T Round( const T& _Value )
        {
            return round( _Value );
        }


		/// <summary>
		/// Round upward a number to the nearest  integer. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Number to round upward.</param>
		/// <returns><paramref name="_Value"/> rounded upward to the nearest integer.</returns>
        template<typename T>
        inline static T Ceil( const T& _Value )
        {
            return ceil( _Value );
        }


		/// <summary>
		/// Round downward a number to the nearest  integer. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Number to round downward.</param>
		/// <returns><paramref name="_Value"/> rounded downward to the nearest integer.</returns>
        template<typename T>
        inline static T Floor( const T& _Value )
        {
            return floor( _Value );
        }


		/// <summary>
		/// Process the square root of a number. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Number to do the square root with.</param>
		/// <returns>Square root of <paramref name="_Value"/>.</returns>
        template<typename T>
        inline static T Sqrt( const T& _Value )
        {
            return sqrt( _Value );
        }


		/// <summary>
		/// Process the power of a number. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Base to raise to the power <paramref name="_Power"/> ( exponent ).</param>
		/// <param name="_Power">Exponent value.</param>
		/// <returns><paramref name="_Value"/> raised to the power <paramref name="_Power"/>.</returns>
        template<typename T>
        inline static T Pow( const T& _Value, const T& _Power )
        {
            return pow( _Value, _Power );
        }


		/// <summary>
		/// Power of 2 of a value. ( x^2 ). <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Base to raise to the power of 2.</param>
		/// <returns><paramref name="_Value"/> ^ 2.</returns>
        template<typename T>
        inline static T Pow2( const T& _Value )
        {
            return ( _Value * _Value );
        }

		/// <summary>
		/// Power of 3 of a value. ( x^3 ). <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Base to raise to the power of 3.</param>
		/// <returns><paramref name="_Value"/> ^ 3.</returns>
        template<typename T>
        inline static T Pow3( const T& _Value )
        {
            return ( _Value * _Value * _Value );
        }


		/// <summary>
		/// Process the modulo of a number. <para/>
		/// Division remainder of <paramref name="_Numerator"/> / <paramref name="_Denominator"/>. <para/>
		/// Equivalent : Integer % Integer, but this function support floating values. <para/>
		/// Do NOT check for division by 0. <para/>
		/// Template available but try to use it with algorithmic types. 
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Numerator">Numerator.</param>
		/// <param name="_Denominator">Denominator.</param>
		/// <returns>The remainder of the division <paramref name="_Numerator"/> / <paramref name="_Denominator"/>.</returns>
        template<typename T>
        inline static T Modulo( const T& _Numerator, const T& _Denominator )
        {
            return fmod( _Numerator, _Denominator );
        }


		/// <summary>
		/// Determine if a number is par. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Value to determine if it is par or not.</param>
		/// <returns>True if <paramref name="_Value"/> is par, false otherwise.</returns>
        template<typename T>
        inline static Bool IsPar( const T& _Value )
        {
            return ( ( Modulo( _Value, static_cast<T>( 2.0 ) ) == static_cast<T>( 0.0 ) ) ? True : False );
        }



		/// <summary>
		/// Extract integral and decimal part of a value. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Value to extract parts from.</param>
		/// <param name="_OutIntegralPart">(Output) Integral part if wanted.</param>
		/// <returns>The decimal part of <paramref name="_Value"/>.</returns>
        template<typename T>
        inline static T Modf( const T& _Value, T* _OutIntegralPart = nullptr )
        {
            T Integral;
            T Decimal = modf( _Value, &Integral );

            if( _OutIntegralPart != nullptr )
                *_OutIntegralPart = Integral;

            return Decimal;
        }


		/// <summary>
		/// Process the based <paramref name="_Base"/> logarithm of <paramref name="_Value"/>. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <remarks>Remainder : \f$\log_a{x} = \ln{x} / \ln{a}\f$</remarks>
		/// <param name="_Value">Value used to process the logarithm.</param>
		/// <param name="_Base">Base of the log.</param>
		/// <returns>Result of the based <paramref name="_Base"/> logarithm of <paramref name="_Value"/>.</returns>
		template<typename T>
		inline static T Log( const T& _Value, const T& _Base )
		{
			// log_a(x) = ln(x) / ln(a).
			return Cast( T, log( _Value ) / log( _Base ) );
		}

		/// <summary>
		/// Process the natural logarithm of <paramref name="_Value"/>. <para/>
		/// ( Equivalent to Ln ). <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Value used to process the logarithm.</param>
		/// <returns>Result of the natural logarithm of <paramref name="_Value"/>.</returns>
		template<typename T>
		inline static T Log( const T& _Value )
		{
			return Cast( T, log( _Value ) );
		}

		/// <summary>
		/// Process the natural logarithm of <paramref name="_Value"/>. <para/>
		/// ( Equivalent to Log overload without base parameter ). <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Value used to process the logarithm.</param>
		/// <returns>Result of the natural logarithm of <paramref name="_Value"/>.</returns>
		template<typename T>
		inline static T Ln( const T& _Value )
		{
			return Cast( T, Log( _Value ) );
		}

		/// <summary>
		/// Process the based 2 logarithm of <paramref name="_Value"/>. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Value used to process the logarithm.</param>
		/// <returns>Result of the based 2 logarithm of <paramref name="_Value"/>.</returns>
		template<typename T>
		inline static T Log2( const T& _Value )
		{
			return Cast( T, log2( _Value ) );
		}

		/// <summary>
		/// Process the based 10 logarithm of <paramref name="_Value"/>. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Value used to process the logarithm.</param>
		/// <returns>Result of the based 10 logarithm of <paramref name="_Value"/>.</returns>
		template<typename T>
		inline static T Log10( const T& _Value )
		{
			return Cast( T, log10( _Value ) );
		}

		/// <summary>
		/// Process the exponential of <paramref name="_Value"/>. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Value used to process the exponential.</param>
		/// <returns>Result of the exponential of <paramref name="_Value"/>.</returns>
		template<typename T>
		inline static T Exp( const T& _Value )
		{
			return Cast( T, exp( _Value ) );
		}

		/// <summary>
		/// Raise 2 to the specified <paramref name="_Exponent"/>. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Exponent">Exponent value.</param>
		/// <returns>2 ^ <paramref name="_Exponent"/>.</returns>
		template<typename T>
		inline static T PowOf2( const T& _Exponent )
		{
			return Cast( T, exp2( _Exponent ) );
		}


		/// <summary>
		/// Retrieve the maximum value of a numeric type. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <returns>The maximum value of the template type.</returns>
		template<typename T>
		inline static constexpr T Max()
		{
			return std::numeric_limits<T>::max();
		}

		/// <summary>
		/// Retrieve the smallest value of a numeric type. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <returns>The smallest value of the template type.</returns>
		template<typename T>
		inline static constexpr T Min()
		{
			return std::numeric_limits<T>::min();
		}

		/// <summary>
		/// Retrieve the lowest value of a numeric type. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <returns>The lowest value of the template type.</returns>
		template<typename T>
		inline static constexpr T Lowest()
		{
			return std::numeric_limits<T>::lowest();
		}

		/// <summary>
		/// Retrieve the infinity value of a numeric type. <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <returns>The infinity value of the template type.</returns>
		template<typename T>
		inline static constexpr T Infinity()
		{
			return std::numeric_limits<T>::infinity();
		}


		/// <summary>
		/// Process the Hermite interpolation between two points and their tangents at the given parameter.<para/>
		/// The PointType must have a compatible multiplication operator with TimeType (operator*).
		/// </summary>
		/// <param name="_P0">The first point.</param>
		/// <param name="_T0">The tangent at the first point.</param>
		/// <param name="_P1">The second point.</param>
		/// <param name="_T1">The tangent at the second point.</param>
		/// <param name="_Time">The interpolation parameter.</param>
		/// <returns>The interpolated point.</returns>
		template<typename PointType = Vector3, typename TimeType = float>
		inline static PointType HermiteInterpolation( const PointType& _P0, const PointType& _T0, const PointType& _P1, const PointType& _T1, TimeType _Time )
		{
			const TimeType Time_1_2 = _Time * _Time;
			const TimeType Time_1_3 = Time_1_2 * _Time;

			const TimeType Time_2_2 = Cast( TimeType, 2.0f ) * Time_1_2;
			const TimeType Time_3_2 = Cast( TimeType, 3.0f ) * Time_1_2;
			const TimeType Time_2_3 = Cast( TimeType, 2.0f ) * Time_1_3;

			const TimeType One = Cast( TimeType, 1.0f );


			const PointType HermiteP0 = _P0 * ( Time_2_3 - Time_3_2 + One );
			const PointType HermiteT0 = _T0 * ( Time_1_3 - Time_2_2 + _Time );

			const PointType HermiteP1 = _P1 * ( -Time_2_3 + Time_3_2 );
			const PointType HermiteT1 = _T1 * ( Time_1_3 - Time_1_2 );

			return HermiteP0 + HermiteT0 + HermiteT1 + HermiteP1;
		}


		/// <summary>
		/// Process the gaussian of the given <paramref name="_Value"/> with the given <paramref name="_StandardDeviation"/>.<para/>
		/// Gaussian = ( 1 / sqrt( 2 * PI * <paramref name="_StandardDeviation"/>² ) ) * exp( -<paramref name="_Value"/>² / ( 2 * <paramref name="_StandardDeviation"/>² ) ) <para/>
		/// Template available but try to use it with algorithmic types.
		/// ( float, double, long double, ... ).
		/// </summary>
		/// <param name="_Value">Value used to process the gaussian.</param>
		/// <param name="_StandardDeviation">Standard deviation of the gaussian function.</param>
		/// <returns>Result of the gaussian.</returns>
		template<typename T>
		inline static T Gaussian( const T& _Value, const T& _StandardDeviation )
		{
			// 1 / sqrt( 2 * PI )
			constexpr T PiCoef = Cast( T, 0.39894228040143267793994605993438 );

			return PiCoef * Exp( Cast( T, -0.5  ) * _Value * _Value / ( _StandardDeviation * _StandardDeviation ) ) / _StandardDeviation;
		}

		/// <summary>Process the position [0,1] of the given <paramref name="_Value"/> in its range [<paramref name="_ValueRangeMin"/>, <paramref name="_ValueRangeMax"/>].</summary>
		/// <param name="_Value">The value to remap.</param>
		/// <param name="_ValueRangeMin">Minimum value of the <paramref name="_Value"/>.</param>
		/// <param name="_ValueRangeMax">Maximum value of the <paramref name="_Value"/>.</param>
		/// <returns>The percent equivalent of the value in its range.</returns>
		template<typename T>
		inline static T Percent( const T& _Value, const T& _ValueRangeMin, const T& _ValueRangeMax )
		{
			return ( _Value - _ValueRangeMin ) / ( _ValueRangeMax - _ValueRangeMin );
		}


		/// <summary>
		/// Process the position [0,1] of the given <paramref name="_Value"/> in its range [<paramref name="_ValueRangeMin"/>, <paramref name="_ValueRangeMax"/>]
		/// and return the value in the new range [<paramref name="_NewRangeMin"/>, <paramref name="_NewRangeMax"/>] at this position.
		/// </summary>
		/// <param name="_Value">The value to remap.</param>
		/// <param name="_ValueRangeMin">Minimum value of the <paramref name="_Value"/>.</param>
		/// <param name="_ValueRangeMax">Maximum value of the <paramref name="_Value"/>.</param>
		/// <param name="_NewRangeMin">Minimum value of the new range.</param>
		/// <param name="_NewRangeMax">Maximum value of the new range.</param>
		/// <returns>The equivalent value in the new range.</returns>
		template<typename T>
		inline static T Remap( const T& _Value, const T& _ValueRangeMin, const T& _ValueRangeMax, const T& _NewRangeMin, const T& _NewRangeMax )
		{
			const T Position = ( _Value - _ValueRangeMin ) / ( _ValueRangeMax - _ValueRangeMin );
			return _NewRangeMin + Position * ( _NewRangeMax - _NewRangeMin );
		}
    };
} // ae

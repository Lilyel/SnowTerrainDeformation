#pragma once

#include "../../Toolbox/Toolbox.h"

namespace ae
{
	/// \ingroup time
    /// <summary>
    /// Time representation. <para/>
    /// Give possibility to retrieve tick and conversion functions.
    /// </summary>
	class AERO_CORE_EXPORT Time
	{
	public:
         /// <summary>Default constructor. (Time set to 0)</summary>
		Time();
  

        /// <summary>Copy constructor.</summary>
        /// <param name="_Time">Time value to copy.</param>
		Time( const Time& _Time );



        /// <summary>Set time value with value as seconds.</summary>
        /// <param name="_Seconds">New value for time as seconds.</param>
		void SetSeconds( float _Seconds );


        /// <summary>Add time ( as seconds )to the current time value.</summary>
        /// <param name="_Seconds">Value to add as seconds.</param>
		void AddSeconds( float _Seconds );


        /// <summary>Retrieve the time value as seconds.</summary>
        /// <returns>Time value as seconds.</returns>
		float AsSeconds() const;



        /// <summary>Set time value with value as milliseconds.</summary>
        /// <param name="_Milli">New value for time as milliseconds.</param>
		void SetMilliSeconds( Int32 _Milli );


        /// <summary>Add time ( as milliseconds )to the current time value.</summary>
        /// <param name="_Milli">Value to add as milliseconds.</param>
		void AddMilliSeconds( Int32 _Milli );


        /// <summary>Retrieve the time value as milliseconds.</summary>
        /// <returns>Time value as milliseconds.</returns>
		Int32 AsMilliSeconds() const;



        /// <summary>Set time value with value as microseconds.</summary>
        /// <param name="_Micro">New value for time as microseconds.</param>
		void SetMicroSeconds( Int64 _Micro );


        /// <summary>Add time ( as microseconds )to the current time value.</summary>
        /// <param name="_Micro">Value to add as microseconds.</param>
		void AddMicroSeconds( Int64 _Micro );


        /// <summary>Retrieve the time value as microseconds.</summary>
        /// <returns>Time value as microseconds.</returns>
		Int64 AsMicroSeconds() const;



        /// <summary>Create a time value from seconds.</summary>
        /// <param name="_Seconds">Value as seconds to create a time value from.</param>
        /// <returns>Time created from value as seconds.</returns>
		static Time Seconds( float _Seconds );


        /// <summary>Create a time value from milliseconds.</summary>
        /// <param name="_Milli">Value as milliseconds to create a time value from.</param>
        /// <returns>Time created from value as milliseconds.</returns>
		static Time MilliSeconds( Int32 _Milli );


        /// <summary>Create a time value from microseconds.</summary>
        /// <param name="_Micro">Value as microseconds to create a time value from.</param>
        /// <returns>Time created from value as microseconds.</returns>
		static Time MicroSeconds( Int64 _Micro );



        /// <summary>Create a time value from the current tick.</summary>
        /// <returns>Time value corresponding to the current tick.</returns>
		static Time GetTick();

	protected:
        /// <summary>Build a time value from microseconds.</summary>
        /// <param name="_MicroSeconds">Value to build the time value from.</param>
		Time( Int64 _MicroSeconds );


	protected:
        /// <summary>Time value stored as microseconds.</summary>
		Int64 m_MicroSeconds;
	};

} // ae

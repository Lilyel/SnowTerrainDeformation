#pragma once

#include "../../Toolbox/Toolbox.h"

namespace ae
{
	/// \ingroup idioms
	/// <summary>
	/// Class to inherit from to disable the possibility to copy the object.<para/>
	/// Only subclass of NotCopiable will be able to create it.
	/// </summary>
	class AERO_CORE_EXPORT NotCopiable
	{
	protected:
		/// <summary>
		/// Default constructor.<para/>
		/// Redefine it in protected visibility because the default constructor genereted is public.
		/// </summary>
		NotCopiable() = default;

		/// <summary>Destructor redefined for inheritance purpose.</summary>
        virtual ~NotCopiable() = default;

	private:
		/// <summary>
		/// Copy constructor.<para/>
		/// Disabled.
		/// </summary>
		/// <param name=""></param>
		NotCopiable( const NotCopiable& ) = delete;
		

		/// <summary>
		/// Copy operator.<para/>
		/// Disabled.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		NotCopiable& operator=( const NotCopiable& ) = delete;
	};

} // ae

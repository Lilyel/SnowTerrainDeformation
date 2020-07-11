#pragma once

#include "../Types.h"

namespace ae
{
	namespace BitOp
	{
		/// \ingroup toolbox
		/// <summary>
		/// Apply the '&' between <paramref name="_A"/> and <paramref name="_B"/>.<para/>
		/// The two parameters are casted to the integer type provided in template parameter before operator.
		/// </summary>
		/// <returns>True if the result is different from 0, False otherwise.</returns>
		template<typename UserType, typename IntegerType = Int64>
		inline Bool BitOpAnd( const UserType& _A, const UserType& _B )
		{
			return ( Cast( IntegerType, _A ) & Cast( IntegerType, _B ) ) != Cast( IntegerType, 0 );
		}

		/// \ingroup toolbox
		/// <summary>
		/// Apply the '|' between <paramref name="_A"/> and <paramref name="_B"/>.<para/>
		/// The two parameters are casted to the integer type provided in template parameter before operator.
		/// </summary>
		/// <returns>True if the result is different from 0, False otherwise.</returns>
		template<typename UserType, typename IntegerType = Int64>
		inline Bool BitOpOr( const UserType& _A, const UserType& _B )
		{
			return ( Cast( IntegerType, _A ) | Cast( IntegerType, _B ) ) != Cast( IntegerType, 0 );
		}
	}
}


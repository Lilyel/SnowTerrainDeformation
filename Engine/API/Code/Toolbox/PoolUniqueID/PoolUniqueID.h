#pragma once

#include "../Types.h"
#include "../../Debugging/Log/Log.h"

#include <limits>
#include <array>

namespace ae
{

	/// \ingroup toolbox
	/// <summary>
	/// Generator of unique ID. <para/>
	/// IDs are type of Uint16. There are UINT16_MAX -2 IDs available.
	/// </summary>
	class PoolUniqueID
	{
	public:
		/// <summary>Count of available IDs + the InvalidID.</summary>
		static constexpr Uint16 PoolSize = UINT16_MAX;

		/// <summary>Value that represent an invalid ID. Never given to user as usable ID.</summary>
		static constexpr Uint16 InvalidID = 0;

		/// <summary>Represents the last ID. Never given to user (used as max limit without overflowing the type).</summary>
		static constexpr Uint16 MaxID = PoolSize - 1;

		/// <summary>Available IDs, without invalid ID and max ID.</summary>
		static constexpr Uint16 CountAvailableIDs = PoolSize - 2;

	public:
		/// <summary>Initialize the generator.</summary>
		PoolUniqueID() :
			m_IDs{}
		{
			for( Uint16 Index = InvalidID; Index < MaxID; Index++ )
				m_IDs[Index] = Index;

			m_Current = InvalidID + 1;
		}

		/// <summary>Generate an ID.</summary>
		/// <returns>
		/// A new ID or InvalidObjectID if the generation failed 
		/// (ID already exists or the maximum count of IDs has been reached ).
		/// </returns>
		Uint16 GenerateID()
		{
			if( m_Current >= MaxID )
			{
				AE_LogError( "No more available ID in the pool." );
				return InvalidID;
			}

			Uint16 ID = m_IDs[m_Current];

			m_IDs[m_Current] = InvalidID;
			m_Current++;

			return ID;
		}

		/// <summary>Free an ID. Allow, later, this ID to be generated again.</summary>
		/// <param name="_ID">The ID to free.</param>
		void FreeID( Uint16 _ID )
		{
			if( m_Current <= InvalidID )
			{
				AE_LogError( "No ID to free." );
				return;
			}

			if( _ID >= MaxID || _ID <= InvalidID )
			{
				AE_LogError( "Invalid ID to free." );
				return;
			}

			m_Current--;
			m_IDs[m_Current] = _ID;
		}

	private:
		/// <summary>Pool of ID to manage.</summary>
		std::array<Uint16, PoolSize> m_IDs;

		/// <summary>Index of the next available ID to give.</summary>
		Uint16 m_Current;
	};

} // ae

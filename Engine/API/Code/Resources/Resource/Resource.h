#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../../Idioms/NotCopiable/NotCopiable.h"

#include "../ResourcesManager.h"

namespace ae
{

	namespace priv
	{

		template<typename ResourceType>
		void FreeResource( ResourceType& _Resource )
		{
			_Resource.FreeResource();
		}

	} // priv

	/// \ingroup resources
	/// <summary>
	/// Class that represent an object in the world. <para/>
	/// Identified by an unique ID.
	/// </summary>
	class AERO_CORE_EXPORT Resource : public NotCopiable
	{
	public:
		/// <summary>Initialize the object and add it to the world hierarchy.</summary>
		Resource();

		/// <summary>Destroy an object and remove it from the world.</summary>
		virtual ~Resource();

		/// <summary>Retrieve the ID that identify this object in the world.</summary>
		/// <returns>ID in the world of the object.</returns>
		const ResourcesManager::ResourceID& GetResourceID() const;

		/// <summary>Retrieve the name of the object.</summary>
		/// <returns>Name of the object.</returns>
		const std::string& GetName() const;
		
		/// <summary>Set the name of the object.</summary>
		/// <param name="_NewName">The new name to apply to the object.</param>
		virtual void SetName( const std::string& _NewName );

		/// <summary>Is the resource is free when the manager is asked to unload its resources</summary>
		/// <returns>True if manager handle the resource free, False otherwise.</returns>
		Bool IsManagedByManager() const;

		/// <summary>Determine if the manager must free this resource when asking to unload its resources.</summary>
		/// <param name="_IsManagedByManager">
		/// True : The manager will free the resource when asked to unload its resources.<para/>
		/// False : The user must manage himself the resource.
		/// </param>
		void SetIsManagedByManager( Bool _IsManagedByManager );

		/// <summary>
		/// Free internal representation of the resource (programs for shader for example).<para/>
		/// Mostyle used internally.
		/// </summary>
		virtual void FreeResource();

		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor();

	private:
		/// <summary>Unique ID of the resource in the manager.</summary>
		ResourcesManager::ResourceID m_ResourceID;
		
		/// <summary>Name of the object.</summary>
		std::string m_Name;

		/// <summary>Determine if the manager must free this resource when asking to unload its resources.</summary>
		Bool m_IsManagedByManager;
	};

} // ae


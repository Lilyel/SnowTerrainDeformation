#include "Resource.h"

#include "../../Aero/Aero.h"
#include "../../Debugging/Debugging.h"
#include "../../Editor/TypesToEditor/ResourceToEditor.h"

namespace ae
{

	Resource::Resource() : 
		m_IsManagedByManager( False )
	{
		ResourcesManager& ManagerRef = Aero.GetResourcesManager();

		m_ResourceID = ManagerRef.AddResource( this );
		if( m_ResourceID == ResourcesManager::InvalidResourceID )
		{
			AE_LogError( "Invalid resource ID returned by the resource manager." );
			return;
		}

		SetName( std::string( "Resource_" ) + std::to_string( m_ResourceID ) );
	}

	Resource::~Resource()
	{
		ResourcesManager& ManagerRef = Aero.GetResourcesManager();

		ManagerRef.RemoveResource( this );
	}

	const ResourcesManager::ResourceID& Resource::GetResourceID() const
	{
		return m_ResourceID;
	}

	const std::string& Resource::GetName() const
	{
		return m_Name;
	}

	void Resource::SetName( const std::string& _NewName )
	{
		m_Name = _NewName;
	}

	Bool Resource::IsManagedByManager() const
	{
		return m_IsManagedByManager;
	}

	void Resource::SetIsManagedByManager( Bool _IsManagedByManager )
	{
		m_IsManagedByManager = _IsManagedByManager;
	}

	void Resource::FreeResource()
	{
	}

	void Resource::ToEditor()
	{
		priv::ui::ResourceToEditor( *this );
	}


} // ae

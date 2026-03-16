#include "World.h"

#include "WorldObject/WorldObject.h"
#include "../Graphics/Light/Light.h"
#include "../Physics/PhysicObject/PhysicObject.h"
#include "../Debugging/Log/Log.h"
#include "../Editor/TypesToEditor/WorldToEditor.h"
#include "../Editor/TypesToEditor/PhysicsSettingsToEditor.h"

namespace ae
{

	///////////////////////////////////////////////////////
	////				 World						   ////
	///////////////////////////////////////////////////////

	World::World()
	{
	}

    const std::unordered_map<World::ObjectID, Light*>& World::GetLights() const
    {
        return m_Lights;
    }

    const std::unordered_map<World::ObjectID, WorldObject*>& World::GetObjects() const
    {
        return m_Objects;
    }

    std::unordered_map<World::ObjectID, WorldObject*>& World::GetObjects()
    {
        return m_Objects;
    }

    const WorldObject* World::GetObject( ObjectID _ID ) const
    {
        if( _ID == InvalidObjectID )
        {
            AE_LogError( "Invalid ID. Function will return nullptr." );
            return nullptr;
        }

        std::unordered_map<World::ObjectID, WorldObject*>::const_iterator It = m_Objects.find( _ID );

        if( It != m_Objects.cend() )
            return It->second;
        
        else
        {
            AE_LogError( std::string( "Object with the ID (" ) + std::to_string( _ID ) + ") not found." );
            return nullptr;
        }
    }

    WorldObject* World::GetObject( ObjectID _ID )
    {
        if( _ID == InvalidObjectID )
        {
            AE_LogError( "Invalid ID. Function will return nullptr." );
            return nullptr;
        }

        std::unordered_map<World::ObjectID, WorldObject*>::iterator It = m_Objects.find( _ID );

        if( It != m_Objects.end() )
            return It->second;

        else
        {
            AE_LogError( std::string( "Object with the ID (" ) + std::to_string( _ID ) + ") not found." );
            return nullptr;
        }
    }


    const PhysicsSettings& World::GetPhysicsSettings() const
    {
        return m_PhysicsSimulator.GetPhysicsSettings();
    }

    PhysicsSettings& World::GetPhysicsSettings()
    {
        return m_PhysicsSimulator.GetPhysicsSettings();
    }


    void World::ToEditor()
    {
        priv::ui::WorldToEditor( *this );
        priv::ui::PhysicsSettingsToEditor( GetPhysicsSettings() );
    }

    void World::Update()
    {
        for( std::pair<const ObjectID, PhysicObject*>& PhysicObjectItem : m_PhysicObjects )
        {
            PhysicObject* PhysicObject = PhysicObjectItem.second;
            if( PhysicObject == nullptr )
                continue;

            m_PhysicsSimulator.SimulateObject( *PhysicObject );
        }
    }


	World::ObjectID World::GenerateObjectID()
	{
		return m_IDPool.GenerateID();
	}

	void World::FreeObjectID( ObjectID _ID )
	{
		m_IDPool.FreeID( _ID );
	}

	World::ObjectID World::AddObjectToWorld( WorldObject* _ObjectToAdd )
	{
		if( _ObjectToAdd == nullptr )
		{
			AE_LogError( "Invalid object to add to the world." );
			return InvalidObjectID;
		}

		// Generate a new ID.
		const ObjectID NewID = GenerateObjectID();

		if( NewID == InvalidObjectID )
		{
			AE_LogError( "Invalid generated ID. Object will not be added to the world." );
			return InvalidObjectID;
		}

		if( m_Objects.find( NewID ) != m_Objects.cend() )
		{
			AE_LogError( std::string( "Object with the generated ID (" ) + std::to_string( NewID ) + ") already exists." );
			return InvalidObjectID;
		}

		// Add the object to the word with this ID.
		m_Objects.insert( { NewID , _ObjectToAdd } );

		return NewID;
	}

	void World::RemoveObjectFromWorld( WorldObject* _ObjectToRemove )
	{
		if( _ObjectToRemove == nullptr )
		{
			AE_LogError( "Invalid object to remove from the world." );
			return;
		}

		const ObjectID& ToDeleteID = _ObjectToRemove->GetObjectID();

		if( m_Objects.find( ToDeleteID ) == m_Objects.cend() )
		{
			AE_LogError( std::string( "Object with the ID (" ) + std::to_string( ToDeleteID ) + ") doesn't exist. Impossible to remove it from the world." );
			return;
		}

		// Remove the object from the world.
		m_Objects.erase( ToDeleteID );

		// Make its ID available again.
		FreeObjectID( ToDeleteID );
	}


    void World::AddLightToList( Light* _LightToAdd )
    {
        if( _LightToAdd == nullptr )
        {
            AE_LogError( "Invalid light to add to the world light list." );
            return;
        }

        const Uint16 LightID = _LightToAdd->GetObjectID();

        if( LightID == InvalidObjectID )
        {
            AE_LogError( "Invalid object ID for the light to add to the world light list." );
            return;
        }

        m_Lights[LightID] = _LightToAdd;
    }

    void World::RemoveLightFromList( Light* _LightToRemove )
    {
        if( _LightToRemove == nullptr )
        {
            AE_LogError( "Invalid light from remove to the world light list." );
            return;
        }

        const Uint16 LightID = _LightToRemove->GetObjectID();

        if( LightID == InvalidObjectID )
        {
            AE_LogError( "Invalid object ID for the light to remove from the world light list." );
            return;
        }

        m_Lights.erase( LightID );
    }


    void World::AddPhysicObjectToList( PhysicObject* _PhysicObjectToAdd )
    {
        if( _PhysicObjectToAdd == nullptr )
        {
            AE_LogError( "Invalid physic object to add to the world physic object list." );
            return;
        }

        const Uint16 ObjectID = _PhysicObjectToAdd->GetObjectID();

        if( ObjectID == InvalidObjectID )
        {
            AE_LogError( "Invalid object ID for the physic object to add to the world physic object list." );
            return;
        }

        m_PhysicObjects[ObjectID] = _PhysicObjectToAdd;
    }

    void World::RemoveLightFromList( PhysicObject* _PhysicObjectToRemove )
    {
        if( _PhysicObjectToRemove == nullptr )
        {
            AE_LogError( "Invalid physic object from remove to the world physic object list." );
            return;
        }

        const Uint16 ObjectID = _PhysicObjectToRemove->GetObjectID();

        if( ObjectID == InvalidObjectID )
        {
            AE_LogError( "Invalid object ID for the physic object to remove from the world physic object list." );
            return;
        }

        m_PhysicObjects.erase( ObjectID );
    }



} // ae
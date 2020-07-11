#ifndef _WORLD_AERO_H_
#define _WORLD_AERO_H_

#include "../Toolbox/Toolbox.h"

#include "../Graphics/Color/Color.h"
#include "../Physics/Simulator/PhysicsSimulator.h"
#include "../Toolbox/PoolUniqueID/PoolUniqueID.h"

#include <limits>
#include <array>
#include <unordered_map>

////////////////////////////////////////////////////////////
/// \defgroup scene Scene Management
///
/// Objects hierarchy management in the world.
///
////////////////////////////////////////////////////////////

namespace ae
{
    class WorldObject;
    class Light;
    class PhysicObject;
    class AeroCore;

    /// \ingroup scene
    /// <summary>
    /// World class that represent the scene. <para/>
    /// Hold the objects hierarchy.
    /// </summary>
    class AERO_CORE_EXPORT World
    {
        friend class WorldObject;
        friend class Light;
        friend class PhysicObject;
        friend class AeroCore;

    public:

        /// <summary>Type used to identify object in the world.</summary>
        using ObjectID = Uint16;

        /// <summary>Value that represent an invalid object ID.</summary>
        static constexpr ObjectID InvalidObjectID = PoolUniqueID::InvalidID;

        /// <summary>Represents the maximum amount of objects that the world can have at the same time.</summary>
        static constexpr ObjectID MaxObjectID = PoolUniqueID::MaxID;


    public:
        /// <summary>Initialiaze an empty world.</summary>
        World();


        /// <summary>Retrieve all the lights that are active in the world.</summary>
        /// <returns>World's lights.</returns>
        const std::unordered_map<ObjectID, Light*>& GetLights() const;

        /// <summary>Retrieve all the objects in the world.</summary>
        /// <returns>World's objects.</returns>
        const std::unordered_map<ObjectID, WorldObject*>& GetObjects() const;

        /// <summary>Retrieve all the objects in the world.</summary>
        /// <returns>World's objects.</returns>
        std::unordered_map<ObjectID, WorldObject*>& GetObjects();

        /// <summary>Get the object with the <paramref name="_ID"/> in the world.</summary>
        /// <param name="_ID">The ID of the object to retrieve from the world.</param>
        /// <returns>Object in the world with the corresponding ID.</returns>
        const WorldObject* GetObject( ObjectID _ID ) const;

        /// <summary>Get the object with the <paramref name="_ID"/> in the world.</summary>
        /// <param name="_ID">The ID of the object to retrieve from the world.</param>
        /// <returns>Object in the world with the corresponding ID.</returns>
        WorldObject* GetObject( ObjectID _ID );

        /// <summary>Retrieve the world physics settings.</summary>
        /// <returns>The world physics settings.</returns>
        const PhysicsSettings& GetPhysicsSettings() const;

        /// <summary>Retrieve the world physics settings.</summary>
        /// <returns>The world physics settings.</returns>
        PhysicsSettings& GetPhysicsSettings();


        /// <summary>
        /// Function called by the editor.
        /// It allows the class to expose some attributes for user editing.
        /// Think to call all inherited class function too when overloading.
        /// </summary>
        void ToEditor();

    private:
        /// <summary>Update the world objects.</summary>
        void Update();

        /// <summary>Take a new object ID from the pool.</summary>
        /// <returns>The new ID taken from the pool (can be InvalidObjectID).</returns>
        ObjectID GenerateObjectID();

        /// <summary>Make available again an ID in the pool.</summary>
        /// <param name="_ID">ID to make available in the pool.</param>
        void FreeObjectID( ObjectID _ID );

        /// <summary>
        /// Add a new object in the world. <para/>
        /// If the object is invalid or if there is not available ID
        /// <paramref name="_ObjectToAdd"/> will not be added to the world. <para/>
        /// If an object with the same ID already exists, <paramref name="_ObjectToAdd"/>
        /// will not be added to the world.
        /// </summary>
        /// <returns>The ID of the object added (can be InvalidObjectID).</returns>
        ObjectID AddObjectToWorld( WorldObject* _ObjectToAdd );

        /// <summary>
        /// Remove an object from the world. <para/>
        /// Its ID will be available again in the pool ID.
        /// </summary>
        void RemoveObjectFromWorld( WorldObject* _ObjectToRemove );


        /// <summary>
        /// Add a light (must be valid) to the lights list
        /// to improve lights access while rendering.
        /// </summary>
        void AddLightToList( Light* _LightToAdd );

        /// <summary>
        /// Remove a light from the lights list.
        /// </summary>
        void RemoveLightFromList( Light* _LightToRemove );

        /// <summary>
        /// Add a physic object (must be valid) to the physic object list
        /// to improve physic object access while doing the simumation.
        /// </summary>
        /// <returns>The ID of the object added (can be InvalidObjectID).</returns>
        void AddPhysicObjectToList( PhysicObject* _PhysicObjectToAdd );

        /// <summary>
        /// Remove a physic object from the physic object list.
        /// </summary>
        void RemoveLightFromList( PhysicObject* _PhysicObjectToRemove );

    private:
        /// <summary>Object ID generator.</summary>
        PoolUniqueID m_IDPool;

        /// <summary>World objects.</summary>
        std::unordered_map<ObjectID, WorldObject*> m_Objects;

        /// <summary>World lights, for quicker access in render.</summary>
        std::unordered_map<ObjectID, Light*> m_Lights;

        /// <summary>World physic objects, for quicker access for simulation.</summary>
        std::unordered_map<ObjectID, PhysicObject*> m_PhysicObjects;

        /// <summary>Physics simulator to update physic objects.</summary>
        priv::PhysicsSimulator m_PhysicsSimulator;
    };

} //ae

#endif // _WORLD_AERO_H_

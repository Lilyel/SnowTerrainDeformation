#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../../Maths/Transform/Transform.h"
#include "../../World/WorldObject/WorldObject.h"

namespace ae
{
    class World;

    /// \ingroup physics
    /// <summary>
    /// Basic class for physic object.
    /// Physic object are simulated when updating the world.
    /// </summary>
    class AERO_CORE_EXPORT PhysicObject : public Transform, public WorldObject
    {
        // Give access to the update function for the world.
        friend class World;

    public:
        /// <summary>Build a physic object and add it to the world.</summary>
        /// <param name="_Mass">The mass of the object.</param>
        PhysicObject( float _Mass = 1.0f );

        /// <summary>Physic object destructor (remove the object from the world).</summary>
        virtual ~PhysicObject();

        /// <summary>Set the mass of the object.</summary>
        /// <param name="_Mass">The new mass of the object.</param>
        void SetMass( float _Mass );

        /// <summary>Retrieve the mass of the object.</summary>
        /// <returns>The mass of the object.</returns>
        float GetMass() const;
        
        /// <summary>
        /// Set the air resistance of the object.<para/>
        /// Small value mean that the object is slippery and will not catch a lot of wind. <para/>
        /// Big value that the object is rough and will catch a lot of wind.
        /// </summary>
        /// <param name="_AirResistance">The new air resistance to apply to the object.</param>
        void SetAirResistance( float _AirResistance );

        /// <summary>
        /// Retrieve the air resistance of the object.<para/>
        /// Small value mean that the object is slippery and will not catch a lot of wind. <para/>
        /// Big value that the object is rough and will catch a lot of wind.
        /// </summary>
        /// <returns>The current air resistance of the object.</returns>
        float GetAirResistance() const;

        /// <summary>Retrieve the current forces that apply to the object.</summary>
        /// <returns>The current forces that apply to the object.</returns>
        const Vector3& GetForces() const;

        /// <summary>Set the forces that apply to the object.</summary>
        /// <param name="_NewForces">The new forces to apply to the object</param>
        void SetForces( const Vector3& _NewForces );

        /// <summary>Add a force to the current forces that apply to the object.</summary>
        /// <param name="_ForceToAdd">Force to add the current forces.</param>
        void AddForce( const Vector3& _ForceToAdd );


        /// <summary>Retrieve the current velocity of the object.</summary>
        /// <returns>The current velocity of the object.</returns>
        const Vector3& GetVelocity() const;

        /// <summary>Set the current velocity of the object.</summary>
        /// <param name="_Velocity">The new velocity to apply to the object.</param>
        void SetVelocity( const Vector3& _Velocity );

        /// <summary>Retrieve the current acceleration of the object.</summary>
        /// <returns>The current acceleration of the object.</returns>
        const Vector3& GetAcceleration() const;

        /// <summary>Set the current acceleration of the object.</summary>
        /// <param name="_Acceleration">The new acceleration to apply to the object.</param>
        void SetAcceleration( const Vector3& _Acceleration );


        /// <summary>Set whether the physics must be applied to this object or not.</summary>
        /// <param name="_ApplyPhysics">Apply the physics to this object ?</param>
        void SetApplyPhysics( Bool _ApplyPhysics );

        /// <summary>Is the physics must be applied to this object or not.</summary>
        /// <returns>True if the physics must be applied, false otherwise.</returns>
        Bool DoApplyPhysics() const;


        /// <summary>Set whether the gravity must be applied to this object or not.</summary>
        /// <param name="_ApplyGravity">Apply the gravity to this object ?</param>
        void SetApplyGravity( Bool _ApplyGravity );

        /// <summary>Is the gravity must be applied to this object or not.</summary>
        /// <returns>True if the gravity must be applied, false otherwise.</returns>
        Bool DoApplyGravity() const;

        /// <summary>Set whether the global world wind must be applied to this object or not.</summary>
        /// <param name="_ApplyGlobalWind">Apply the global world wind to this object ?</param>
        void SetApplyGlobalWind( Bool _ApplyGlobalWind );

        /// <summary>Is the global world wind must be applied to this object or not.</summary>
        /// <returns>True if the global world wind must be applied, false otherwise.</returns>
        Bool DoApplyGlobalWind() const;

        /// <summary>Set whether the air resistance must be applied to this object or not.</summary>
        /// <param name="_ApplyAirResistance">Apply the air resistance to this object ?</param>
        void SetApplyAirResistance( Bool _ApplyAirResistance );

        /// <summary>Is the air resistance must be applied to this object or not.</summary>
        /// <returns>True if the air resistance must be applied, false otherwise.</returns>
        Bool DoApplyAirResistance() const;

        /// <summary>
        /// Function called by the editor.
        /// It allows the class to expose some attributes for user editing.
        /// Think to call all inherited class function too when overloading.
        /// </summary>
        virtual void ToEditor() override;

    private:
        /// <summary>Apply or not the physics for this object.</summary>
        Bool m_ApplyPhysics;

        /// <summary>Apply or not the gravity for this object.</summary>
        Bool m_ApplyGravity;

        /// <summary>Apply or not the air resistant to this object.</summary>
        Bool m_ApplyAirResistance;

        /// <summary>Apply or not the global world wind to this object.</summary>
        Bool m_ApplyGlobalWind;

        /// <summary>Mass of the object.</summary>
        float m_Mass;

        /// <summary>
        /// Air resistance of the object.<para/>
        /// Small value mean that the object is slippery and will not catch a lot of wind. <para/>
        /// Big value that the object is rough and will catch a lot of wind.
        /// </summary>
        float m_AirResistance;

        /// <summary>Current forces that apply to the object.</summary>
        Vector3 m_Forces;

        /// <summary>Current velocity of the object.</summary>
        Vector3 m_Velocity;

        /// <summary>Current acceleration of the object.</summary>
        Vector3 m_Acceleration;
    };

} // ae

#include "PhysicObject.h"

#include "../../Aero/Aero.h"
#include "../../Editor/TypesToEditor/PhysicObjectToEditor.h"

namespace ae
{
    PhysicObject::PhysicObject( float _Mass ) :
        m_ApplyPhysics( True ),
        m_ApplyGravity( True ),
        m_ApplyAirResistance( True ),
        m_Mass( _Mass ),
        m_AirResistance( 0.0f ),
        m_Forces( Vector3::Zero ),
        m_Velocity( Vector3::Zero ),
        m_Acceleration( Vector3::Zero )
    {
        World& worldRef = Aero.GetWorld();
        worldRef.AddPhysicObjectToList( this );


        SetName( std::string( "PhysicObject_" ) + std::to_string( GetObjectID() ) );
    }

    PhysicObject::~PhysicObject()
    {
        World& worldRef = Aero.GetWorld();
        worldRef.RemoveLightFromList( this );
    }


    void PhysicObject::SetMass( float _Mass )
    {
        m_Mass = Math::Max( _Mass, Math::Epsilon() );
    }

    float PhysicObject::GetMass() const
    {
        return m_Mass;
    }

    void PhysicObject::SetAirResistance( float _AirResistance )
    {
        m_AirResistance = _AirResistance;
    }


    float PhysicObject::GetAirResistance() const
    {
        return m_AirResistance;
    }

    const Vector3& PhysicObject::GetForces() const
    {
        return m_Forces;
    }

    void PhysicObject::SetForces( const Vector3& _NewForces )
    {
        m_Forces = _NewForces;
    }

    void PhysicObject::AddForce( const Vector3& _ForceToAdd )
    {
        m_Forces += _ForceToAdd;
    }


    const Vector3& PhysicObject::GetVelocity() const
    {
        return m_Velocity;
    }

    void PhysicObject::SetVelocity( const Vector3& _Velocity )
    {
        m_Velocity = _Velocity;
    }

    const Vector3& PhysicObject::GetAcceleration() const
    {
        return m_Acceleration;
    }

    void PhysicObject::SetAcceleration( const Vector3& _Acceleration )
    {
        m_Acceleration = _Acceleration;
    }

    void PhysicObject::SetApplyPhysics( Bool _ApplyPhysics )
    {
        m_ApplyPhysics = _ApplyPhysics;
    }

    Bool PhysicObject::DoApplyPhysics() const
    {
        return m_ApplyPhysics;
    }

    void PhysicObject::SetApplyGravity( Bool _ApplyGravity )
    {
        m_ApplyGravity = _ApplyGravity;
    }

    Bool PhysicObject::DoApplyGravity() const
    {
        return m_ApplyGravity;
    }

    void PhysicObject::SetApplyGlobalWind( Bool _ApplyGlobalWind )
    {
        m_ApplyGlobalWind = _ApplyGlobalWind;
    }

    Bool PhysicObject::DoApplyGlobalWind() const
    {
        return m_ApplyGlobalWind;
    }

    void PhysicObject::SetApplyAirResistance( Bool _ApplyAirResistance )
    {
        m_ApplyAirResistance = _ApplyAirResistance;
    }

    Bool PhysicObject::DoApplyAirResistance() const
    {
        return m_ApplyAirResistance;
    }


    void PhysicObject::ToEditor()
    {
        WorldObject::ToEditor();
        Transform::ToEditor();
        priv::ui::PhysicObjectToEditor( *this );
    }


} // ae
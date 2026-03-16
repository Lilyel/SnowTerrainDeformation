#include "PhysicsSimulator.h"

#include "../PhysicObject/PhysicObject.h"
#include "../../Aero/Aero.h"


namespace ae
{
    namespace priv
    {
		PhysicsSimulator::PhysicsSimulator() : 
			m_TimeStep( 0.0f )
		{
		}

		const PhysicsSettings& PhysicsSimulator::GetPhysicsSettings() const
        {
            return m_Settings;
        }

        PhysicsSettings& PhysicsSimulator::GetPhysicsSettings()
        {
            return m_Settings;
        }


        void PhysicsSimulator::SimulateObject( PhysicObject& _Object )
        {
            if( !_Object.DoApplyPhysics() )
                return;

            // Retrieve object data.
            Vector3 Position = _Object.GetPosition();
            Vector3 Velocity = _Object.GetVelocity();                             
            Vector3 Forces = _Object.GetForces();

            // Gravity. (g*m)
            if( _Object.DoApplyGravity() )
                Forces += m_Settings.Gravity * _Object.GetMass();

            // Air resistance. (Damping against the velocity : -d*V)
            if( _Object.DoApplyAirResistance() )
                Forces += -Velocity * _Object.GetAirResistance();

            // Wind. (d*V_wind)
            if( _Object.DoApplyGlobalWind() )
                Forces += m_Settings.GlobalWind *  _Object.GetAirResistance();

            // TODO : Add other forces to acceleration...


            // Process the final acceleration.
            // F = ma -> a = F/m
            const Vector3 Acceleration = Forces / _Object.GetMass();

			// Process the timestep to use according the fixed framerate of the physics.
			// For stability, we do not take a value higher than the current framerate of the application.
            float Time = 0.0f;
            const float MaxTime = Aero.GetDeltaTime();
            m_TimeStep = Math::Min( 1.0f / Cast( float, m_Settings.FixedFrameRate ), MaxTime );

            IntegratorFunction Integrator = GetIntegrator();

            // Do the simulation with the asked count of iterations to reach the time of a frame.
            while( Time < MaxTime )
            {
                Integrator( *this, Position, Velocity, Acceleration );

                Time += m_TimeStep;
            }

            // Send the result to the object.

            _Object.SetPosition( Position );
            _Object.SetVelocity( Velocity );
            _Object.SetAcceleration( Acceleration );
        }


        void PhysicsSimulator::EulerIntegration( Vector3& _InOutPosition, Vector3& _InOutVelocity, const Vector3& _Acceleration )
        {
            // Euler classic : 

            // Update the position with the current velocity.
            _InOutPosition = _InOutPosition + _InOutVelocity * m_TimeStep;

            // Update the velocity after.
            _InOutVelocity = _InOutVelocity + _Acceleration * m_TimeStep;
        }

        void PhysicsSimulator::EulerEndingVelocityIntegration( Vector3& _InOutPosition, Vector3& _InOutVelocity, const Vector3& _Acceleration )
        {
            // Euler ending velocity :

            // Update the velocity first.
            _InOutVelocity = _InOutVelocity + _Acceleration * m_TimeStep;

            // Update the position with the updated velocity.
            _InOutPosition = _InOutPosition + _InOutVelocity * m_TimeStep;
        }

        void PhysicsSimulator::EulerAverageVelocityIntegration( Vector3& _InOutPosition, Vector3& _InOutVelocity, const Vector3& _Acceleration )
        {
            // Euler average velocity :

            // Store the current velocity then update it.
            const Vector3 currentVelocity = _InOutVelocity;
            _InOutVelocity = _InOutVelocity + _Acceleration * m_TimeStep;

            // Update the position with the average of the current velocity and the new.
            _InOutPosition = _InOutPosition + ( ( currentVelocity + _InOutVelocity ) * 0.5f ) * m_TimeStep;
        }

        PhysicsSimulator::IntegratorFunction PhysicsSimulator::GetIntegrator() const
        {
            // Chose the right integrator according to the settings.
            switch( m_Settings.Integrator )
            {
            case PhysicsSettings::IntegrationMethod::Euler:
            return &PhysicsSimulator::EulerIntegration;

            case PhysicsSettings::IntegrationMethod::EulerEndingVelocity:
            return &PhysicsSimulator::EulerEndingVelocityIntegration;

            case PhysicsSettings::IntegrationMethod::EulerAverageVelocity:
            default:
            return &PhysicsSimulator::EulerAverageVelocityIntegration;
            }
        }

    } // priv
} // ae

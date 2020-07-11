#pragma once

#include "../../Toolbox/Toolbox.h"

#include "../Settings/PhysicsSettings.h"

#include <functional>

namespace ae
{
    class PhysicObject;
    class Vector3;

    namespace priv
    {
        /// \ingroup physics
        /// <summary>
        /// This class stored the physics settings and update physics objects of the world.
        /// </summary>
        class AERO_CORE_EXPORT PhysicsSimulator
        {
            using IntegratorFunction = std::function<void( PhysicsSimulator&, Vector3&, Vector3&, const Vector3& )>;

        public:
			/// <summary>Default constructor.</summary>
			PhysicsSimulator();

            /// <summary>Retrieve the world physics settings.</summary>
            /// <returns>The world physics settings.</returns>
            const PhysicsSettings& GetPhysicsSettings() const;

            /// <summary>Retrieve the world physics settings.</summary>
            /// <returns>The world physics settings.</returns>
            PhysicsSettings& GetPhysicsSettings();

            /// <summary>Update the physics of an object.</summary>
            /// <param name="_Object"></param>
            void SimulateObject( PhysicObject& _Object );

        private:
            /// <summary>Process the next position using Euler integration.</summary>
            /// <param name="_InOutPosition">The position to process.</param>
            /// <param name="_Velocity">The velocity of the current step, will be updated.</param>
            /// <param name="_Acceleration">The acceleration of the current step.</param>
            void EulerIntegration( Vector3& _InOutPosition, Vector3& _InOutVelocity, const Vector3& _Acceleration );

            /// <summary>Process the next position using Euler ending velocity integration.</summary>
            /// <param name="_InOutPosition">The position to process.</param>
            /// <param name="_Velocity">The velocity of the current step, will be updated.</param>
            /// <param name="_Acceleration">The acceleration of the current step.</param>
            void EulerEndingVelocityIntegration( Vector3& _InOutPosition, Vector3& _InOutVelocity, const Vector3& _Acceleration );

            /// <summary>Process the next position using Euler average velocity integration.</summary>
            /// <param name="_InOutPosition">The position to process.</param>
            /// <param name="_Velocity">The velocity of the current step, will be updated.</param>
            /// <param name="_Acceleration">The acceleration of the current step.</param>
            void EulerAverageVelocityIntegration( Vector3& _InOutPosition, Vector3& _InOutVelocity, const Vector3& _Acceleration );

            /// <summary>Retrieve the integrator that the user wants to process the new position and the velocity.</summary>
            /// <returns>The integrator to use to update the positions and velocity.</returns>
            IntegratorFunction GetIntegrator() const;

        private:
            /// <summary>Current world physics settings.</summary>
            PhysicsSettings m_Settings;

            /// <summary>Current time step for this frame.</summary>
            float m_TimeStep;
            
        };
    } // priv
} // ae

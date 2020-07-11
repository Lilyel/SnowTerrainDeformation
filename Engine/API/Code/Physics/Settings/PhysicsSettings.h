#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../../Maths/Vector/Vector3.h"

namespace ae
{
    /// \ingroup physics
    /// <summary>
    /// Global settings for the physics sumlation.
    /// </summary>
    class AERO_CORE_EXPORT PhysicsSettings
    {
    public:

        /// <summary>
        /// Numerical integration method to use to process the physics simulation.
        /// </summary>
        enum class IntegrationMethod : Uint8
        {
            /// <summary>Classic euler methods.</summary>
            Euler,
            /// <summary>Euler methods using the updated velocity to process the position.</summary>
            EulerEndingVelocity,
            /// <summary>
            /// Euler methods using the average of the update velocity and the current one
            /// to process the position.
            /// </summary>
            EulerAverageVelocity
        };


    public:
        /// <summary>
        /// Initialize the defaults settings for the physics simulation. <para/>
        /// Integrator : EulerAverageVelocity <para/>
        /// Gravity : X = 0, Y = -10, Z = 0 <para/>
        /// Iteration : 1
        /// </summary>
        PhysicsSettings() :
            Integrator( IntegrationMethod::EulerAverageVelocity ),
            Gravity( 0.0f, -10.0f, 0.0f ),
            GlobalWind( 0.0f, 0.0f, 0.0f ),
			FixedFrameRate( 60 )
        {}

    public:
        /// <summary>Numerical integration method to use to simulate physics.</summary>
        IntegrationMethod Integrator;

        /// <summary>Value and direction of the gravity to apply.</summary>
        Vector3 Gravity;

        /// <summary>Wind applied to entire world.</summary>
        Vector3 GlobalWind;

        /// <summary>The framerate that the physics must used.</summary>
        Uint32 FixedFrameRate;
    };
} // ae

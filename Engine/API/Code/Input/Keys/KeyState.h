#pragma once
#include "../../Toolbox/Toolbox.h"

#include <string>

namespace ae
{
    namespace Input
    {
        /// \ingroup input
        /// <summary>Possible states of a key.</summary>
        enum class State : Int8
        {
            Pressed = 1,       ///< Pressed is if the key was up at the previous frame and down (at low level) for the current frame.
            Down = 1 << 1,     ///< Down is if the key was pressed the previous frame and down (at low level) for the current frame.
            Released = 1 << 2, ///< Released if the key was pressed or down the previous frame and up (at low level) for the current frame.
            Up = 1 << 3,       ///< Default state. Up if the key was pressed  the previous frame and up (at low level) for the current frame.

            Lock = 1 << 4,     ///< Used for capslock and locknum key. If set to 1 theses keys are active.

            StateCount = 5,    ///< Count of possible state.
            StateInvalid = -1  ///< Invalid state.
        };

        /// \ingroup input
        /// <summary>Convert a key state as string.</summary>
        /// <param name="_State">To convert as string.</param>
        /// <returns>State as string.</returns>
        AERO_CORE_EXPORT std::string StateToString( const State& _State );

    } // Input
} // ae


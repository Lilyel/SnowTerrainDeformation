#include "KeyState.h"

namespace ae
{
    namespace Input
    {
        std::string StateToString( const State& _State )
        {
            std::string AsString;

            if( ( Cast( Int8, _State ) & Cast( Int8, State::Up ) ) != 0 )
                AsString = "Up";

            else if( ( Cast( Int8, _State ) & Cast( Int8, State::Pressed ) ) != 0 )
                AsString = "Pressed";

            else if( ( Cast( Int8,_State ) & Cast( Int8, State::Down ) ) != 0 )
                AsString = "Down";

            else if( ( Cast( Int8, _State ) & Cast( Int8, State::Released ) ) != 0 )
                AsString = "Released";


            if( ( Cast( Int8, _State ) & Cast( Int8, State::Lock ) ) != 0 )
                AsString += " | Lock";

            return AsString;
        }

    } // Input
} // ae
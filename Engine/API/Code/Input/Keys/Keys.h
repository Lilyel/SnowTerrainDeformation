#pragma once

#include "../../Toolbox/Toolbox.h"

#include <string>

namespace ae
{
    namespace Input
    {
        // Keyboard and mouse list made with : https://msdn.microsoft.com/fr-fr/library/windows/desktop/dd375731(v=vs.85).aspx

        /// \ingroup input
        /// <summary>List of handled keys.<summary>
        enum class Key : Int16
        {
            Keyboard_Numpad0, ///< The '0' key of numpad.
            Keyboard_Numpad1, ///< The '1' key of numpad.
            Keyboard_Numpad2, ///< The '2' key of numpad.
            Keyboard_Numpad3, ///< The '3' key of numpad.
            Keyboard_Numpad4, ///< The '4' key of numpad.
            Keyboard_Numpad5, ///< The '5' key of numpad.
            Keyboard_Numpad6, ///< The '6' key of numpad.
            Keyboard_Numpad7, ///< The '7' key of numpad.
            Keyboard_Numpad8, ///< The '8' key of numpad.
            Keyboard_Numpad9, ///< The '9' key of numpad.

            Keyboard_0, ///< The '0' key.
            Keyboard_1, ///< The '1' key.
            Keyboard_2, ///< The '2' key.
            Keyboard_3, ///< The '3' key.
            Keyboard_4, ///< The '4' key.
            Keyboard_5, ///< The '5' key.
            Keyboard_6, ///< The '6' key.
            Keyboard_7, ///< The '7' key.
            Keyboard_8, ///< The '8' key.
            Keyboard_9, ///< The '9' key.

            Keyboard_A, ///< The 'A' key.
            Keyboard_B, ///< The 'B' key.
            Keyboard_C, ///< The 'C' key.
            Keyboard_D, ///< The 'D' key.
            Keyboard_E, ///< The 'E' key.
            Keyboard_F, ///< The 'F' key.
            Keyboard_G, ///< The 'G' key.
            Keyboard_H, ///< The 'H' key.
            Keyboard_I, ///< The 'I' key.
            Keyboard_J, ///< The 'J' key.
            Keyboard_K, ///< The 'K' key.
            Keyboard_L, ///< The 'L' key.
            Keyboard_M, ///< The 'M' key.
            Keyboard_N, ///< The 'N' key.
            Keyboard_O, ///< The 'O' key.
            Keyboard_P, ///< The 'P' key.
            Keyboard_Q, ///< The 'Q' key.
            Keyboard_R, ///< The 'R' key.
            Keyboard_S, ///< The 'S' key.
            Keyboard_T, ///< The 'T' key.
            Keyboard_U, ///< The 'U' key.
            Keyboard_V, ///< The 'V' key.
            Keyboard_W, ///< The 'W' key.
            Keyboard_X, ///< The 'X' key.
            Keyboard_Y, ///< The 'Y' key.
            Keyboard_Z, ///< The 'Z' key.

            Keyboard_F1, ///< The 'F1' key.
            Keyboard_F2, ///< The 'F2' key.
            Keyboard_F3, ///< The 'F3' key.
            Keyboard_F4, ///< The 'F4' key.
            Keyboard_F5, ///< The 'F5' key.
            Keyboard_F6, ///< The 'F6' key.
            Keyboard_F7, ///< The 'F7' key.
            Keyboard_F8, ///< The 'F8' key.
            Keyboard_F9, ///< The 'F9' key.
            Keyboard_F10, ///< The 'F10' key.
            Keyboard_F11, ///< The 'F11' key.
            Keyboard_F12, ///< The 'F12' key.
            Keyboard_F13, ///< The 'F13' key.
            Keyboard_F14, ///< The 'F14' key.
            Keyboard_F15, ///< The 'F15' key.
            Keyboard_F16, ///< The 'F16' key.
            Keyboard_F17, ///< The 'F17' key.
            Keyboard_F18, ///< The 'F18' key.
            Keyboard_F19, ///< The 'F19' key.
            Keyboard_F20, ///< The 'F20' key.
            Keyboard_F21, ///< The 'F21' key.
            Keyboard_F22, ///< The 'F22' key.
            Keyboard_F23, ///< The 'F23' key.
            Keyboard_F24, ///< The 'F24' key.
            Keyboard_F25, ///< The 'F25' key.

            Keyboard_Multiply, ///< The '*' key.
            Keyboard_Add, ///< The '+' key.
            Keyboard_Subtract, ///< The '-' key.
            Keyboard_Decimal, ///< The '.' key.
            Keyboard_Divide, ///< The '/' key.
            Keyboard_NumLock, ///< The Numpad lock key.

            Keyboard_PageUp, ///< The 'Page Up' key.
            Keyboard_PageDown, ///< The 'Page Down' key.
            Keyboard_Home, ///< The 'Home' key.
            Keyboard_End, ///< The 'End' key.
            Keyboard_Insert, ///< The 'Insert' key.
            Keyboard_Delete, ///< The 'Delete' key.

            Keyboard_Pause, ///< The 'Pause' key.
            Keyboard_ScrollLock, ///< The 'Scroll Lock' key.
            Keyboard_Snapshot, ///< The print screen key.

            Keyboard_LeftArrow, ///< The left arrow key.
            Keyboard_UpArrow, ///< The up arrow key.
            Keyboard_DownArrow, ///< The down arrow key.
            Keyboard_RightArrow, ///< The right arrow key.


            Keyboard_CapsLock, ///< The caps lock key.
            Keyboard_Backspace, ///< The backspace key.
            Keyboard_Tab, ///< The tabulation key.
            Keyboard_Return, ///< The return ('Enter') key.
            Keyboard_Space, ///< The space bar key.
            Keyboard_LeftSystem, ///< The left system key (Start Menu shortcut for Windows).
            Keyboard_RightSystem, ///< The right system key (Start Menu shortcut for Windows).
            Keyboard_LeftAlt, ///< The left alt key.
            Keyboard_RightAlt, ///< The right alt key.
            Keyboard_LeftShift, ///< The left shift key.
            Keyboard_RightShift, ///< The right shift key.
            Keyboard_LeftControl, ///< The left control ('ctrl') key.
            Keyboard_RightControl, ///< The right control ('ctrl') key.
            Keyboard_Menu, ///< The menu key.
            Keyboard_SemiColon, ///< The ';' key.
            Keyboard_Equal, ///< The '=' key.
            Keyboard_Comma, ///< The ',' key.
            Keyboard_Dash, ///< The '-' key.
            Keyboard_Period, ///< The '.' key.
            Keyboard_Slash, ///< The '/' key.
            Keyboard_Tilde, ///< The '~' key.
            Keyboard_LeftBracket, ///< The '[' key.
            Keyboard_RightBracket, ///< The ']' key.
            Keyboard_BackSlash, ///< The '\' key.
            Keyboard_Quote, ///< The ''' key.

            Keyboard_Clear, ///< The clear key.
            Keyboard_Escape, ///< The escape ('Esc') key.
            Keyboard_Select, ///< The select key.
            Keyboard_Print, ///< The print key.
            Keyboard_Execute, ///< The execute key.
            Keyboard_Help, ///< The help key.
            Keyboard_Applications, ///< The applications key.
            Keyboard_Sleep, ///< The sleep key.

            Keyboard_BrowserBack, ///< The back key (browser).
            Keyboard_BrowserForward, ///< The forward key (browser).
            Keyboard_BrowserRefresh, ///< The refresh key (browser).
            Keyboard_BrowserStop, ///< The stop key (browser).
            Keyboard_BrowserSearch, ///< The search key (browser).
            Keyboard_BrowserFavorites, ///< The favorites key (browser).
            Keyboard_BrowserStartHome, ///< The start/home key (browser).

            Keyboard_VolumeMute, ///< The mute key (Volume).
            Keyboard_VolumeDown, ///< The up key (Volume).
            Keyboard_VolumeUp, ///< The down key (Volume).

            Keyboard_PreviousTrack, ///< The previous key (media).
            Keyboard_NextTrack, ///< The next key (media).
            Keyboard_StopMedia, ///< The stop key (media).
            Keyboard_PlayPauseMedia, ///< The play/pause key (media).
            Keyboard_SelectMedia, ///< The select key (media).

            Keyboard_StartMail,  ///< The start key (mail).
            Keyboard_StartApp1, ///< The start application 1 key.
            Keyboard_StartApp2, ///< The start application 2 key.

            Keyboard_PrintScreen, ///< Print screen key.

            Keyboard_Unknown, ///< Undefined key.



            Mouse_LeftButton, ///< Left mouse button.
            Mouse_RightButton, ///< Right mouse button.
            Mouse_MiddleButton, ///< Middle mouse button.
            Mouse_X1Button, ///< X1 mouse button.
            Mouse_X2Button, ///< X2 mouse button.

            Mouse_Unknown, ///< Undefined mouse button.




            Gamepad_Unknown, ///< Undefined gamepad button.


            KeyCount, ///< Total count of key.
            KeyInvalid = -1 ///< Invalid key.
        };

        /// \ingroup input
        /// <summary>Convert a key as string.</summary>
        /// <param name="_Key">To convert as string.</param>
        /// <returns>Key as string.</returns>
        AERO_CORE_EXPORT std::string KeyToString( const Key& _Key );

    } // Input

} // ae

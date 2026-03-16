#include "Keys.h"

namespace ae
{
    namespace Input
    {

        std::string KeyToString( const Key& _Key )
        {
            switch( _Key )
            {
                /// Keyboard

                case ae::Input::Key::Keyboard_Numpad0:
                    return "0";
                case ae::Input::Key::Keyboard_Numpad1:
                    return "1";
                case ae::Input::Key::Keyboard_Numpad2:
                    return "2";
                case ae::Input::Key::Keyboard_Numpad3:
                    return "3";
                case ae::Input::Key::Keyboard_Numpad4:
                    return "4";
                case ae::Input::Key::Keyboard_Numpad5:
                    return "5";
                case ae::Input::Key::Keyboard_Numpad6:
                    return "6";
                case ae::Input::Key::Keyboard_Numpad7:
                    return "7";
                case ae::Input::Key::Keyboard_Numpad8:
                    return "8";
                case ae::Input::Key::Keyboard_Numpad9:
                    return "9";

                case ae::Input::Key::Keyboard_0:
                    return "0";
                case ae::Input::Key::Keyboard_1:
                    return "1";
                case ae::Input::Key::Keyboard_2:
                    return "2";
                case ae::Input::Key::Keyboard_3:
                    return "3";
                case ae::Input::Key::Keyboard_4:
                    return "4";
                case ae::Input::Key::Keyboard_5:
                    return "5";
                case ae::Input::Key::Keyboard_6:
                    return "6";
                case ae::Input::Key::Keyboard_7:
                    return "7";
                case ae::Input::Key::Keyboard_8:
                    return "8";
                case ae::Input::Key::Keyboard_9:
                    return "9";

                case ae::Input::Key::Keyboard_A:
                    return "A";
                case ae::Input::Key::Keyboard_B:
                    return "B";
                case ae::Input::Key::Keyboard_C:
                    return "C";
                case ae::Input::Key::Keyboard_D:
                    return "D";
                case ae::Input::Key::Keyboard_E:
                    return "E";
                case ae::Input::Key::Keyboard_F:
                    return "F";
                case ae::Input::Key::Keyboard_G:
                    return "G";
                case ae::Input::Key::Keyboard_H:
                    return "H";
                case ae::Input::Key::Keyboard_I:
                    return "I";
                case ae::Input::Key::Keyboard_J:
                    return "J";
                case ae::Input::Key::Keyboard_K:
                    return "K";
                case ae::Input::Key::Keyboard_L:
                    return "L";
                case ae::Input::Key::Keyboard_M:
                    return "M";
                case ae::Input::Key::Keyboard_N:
                    return "N";
                case ae::Input::Key::Keyboard_O:
                    return "O";
                case ae::Input::Key::Keyboard_P:
                    return "P";
                case ae::Input::Key::Keyboard_Q:
                    return "Q";
                case ae::Input::Key::Keyboard_R:
                    return "R";
                case ae::Input::Key::Keyboard_S:
                    return "S";
                case ae::Input::Key::Keyboard_T:
                    return "T";
                case ae::Input::Key::Keyboard_U:
                    return "U";
                case ae::Input::Key::Keyboard_V:
                    return "V";
                case ae::Input::Key::Keyboard_W:
                    return "W";
                case ae::Input::Key::Keyboard_X:
                    return "X";
                case ae::Input::Key::Keyboard_Y:
                    return "Y";
                case ae::Input::Key::Keyboard_Z:
                    return "Z";

                case ae::Input::Key::Keyboard_F1:
                    return "F1";
                case ae::Input::Key::Keyboard_F2:
                    return "F2";
                case ae::Input::Key::Keyboard_F3:
                    return "F3";
                case ae::Input::Key::Keyboard_F4:
                    return "F4";
                case ae::Input::Key::Keyboard_F5:
                    return "F5";
                case ae::Input::Key::Keyboard_F6:
                    return "F6";
                case ae::Input::Key::Keyboard_F7:
                    return "F7";
                case ae::Input::Key::Keyboard_F8:
                    return "F8";
                case ae::Input::Key::Keyboard_F9:
                    return "F9";
                case ae::Input::Key::Keyboard_F10:
                    return "F10";
                case ae::Input::Key::Keyboard_F11:
                    return "F11";
                case ae::Input::Key::Keyboard_F12:
                    return "F12";
                case ae::Input::Key::Keyboard_F13:
                    return "F13";
                case ae::Input::Key::Keyboard_F14:
                    return "F14";
                case ae::Input::Key::Keyboard_F15:
                    return "F15";
                case ae::Input::Key::Keyboard_F16:
                    return "F16";
                case ae::Input::Key::Keyboard_F17:
                    return "F17";
                case ae::Input::Key::Keyboard_F18:
                    return "F18";
                case ae::Input::Key::Keyboard_F19:
                    return "F19";
                case ae::Input::Key::Keyboard_F20:
                    return "F20";
                case ae::Input::Key::Keyboard_F21:
                    return "F21";
                case ae::Input::Key::Keyboard_F22:
                    return "F22";
                case ae::Input::Key::Keyboard_F23:
                    return "F23";
                case ae::Input::Key::Keyboard_F24:
                    return "F24";

                case ae::Input::Key::Keyboard_Multiply:
                    return "*";
                case ae::Input::Key::Keyboard_Add:
                    return "+";
                case ae::Input::Key::Keyboard_Subtract:
                    return "-";
                case ae::Input::Key::Keyboard_Decimal:
                    return "+";
                case ae::Input::Key::Keyboard_Divide:
                    return "/";
                case ae::Input::Key::Keyboard_NumLock:
                    return "NumLock";

                case ae::Input::Key::Keyboard_PageUp:
                    return "PageUp";
                case ae::Input::Key::Keyboard_PageDown:
                    return "PageDown";
                case ae::Input::Key::Keyboard_Home:
                    return "Home";
                case ae::Input::Key::Keyboard_End:
                    return "End";
                case ae::Input::Key::Keyboard_Insert:
                    return "Insert";
                case ae::Input::Key::Keyboard_Delete:
                    return "Delete";

                case ae::Input::Key::Keyboard_Pause:
                    return "Pause";
                case ae::Input::Key::Keyboard_ScrollLock:
                    return "ScrollLock";
                case ae::Input::Key::Keyboard_Snapshot:
                    return "Snapshot";

                case ae::Input::Key::Keyboard_LeftArrow:
                    return "Left";
                case ae::Input::Key::Keyboard_UpArrow:
                    return "Up";
                case ae::Input::Key::Keyboard_DownArrow:
                    return "Down";
                case ae::Input::Key::Keyboard_RightArrow:
                    return "Right";


                case ae::Input::Key::Keyboard_CapsLock:
                    return "CapsLock";
                case ae::Input::Key::Keyboard_Backspace:
                    return "Backspace";
                case ae::Input::Key::Keyboard_Tab:
                    return "Tabulation";
                case ae::Input::Key::Keyboard_Return:
                    return "Return";
                case ae::Input::Key::Keyboard_Space:
                    return "Space";
                case ae::Input::Key::Keyboard_LeftSystem:
                    return "LeftSystem";
                case ae::Input::Key::Keyboard_RightSystem:
                    return "RightSystem";
                case ae::Input::Key::Keyboard_LeftShift:
                    return "LeftShift";
                case ae::Input::Key::Keyboard_RightShift:
                    return "RightShift";
                case ae::Input::Key::Keyboard_LeftControl:
                    return "LeftControl";
                case ae::Input::Key::Keyboard_RightControl:
                    return "RightControl";
                case ae::Input::Key::Keyboard_Menu:
                    return "Menu";
                case ae::Input::Key::Keyboard_SemiColon:
                    return ";";
                case ae::Input::Key::Keyboard_Equal:
                    return "=";
                case ae::Input::Key::Keyboard_Comma:
                    return ",";
                case ae::Input::Key::Keyboard_Dash:
                    return "/";
                case ae::Input::Key::Keyboard_Period:
                    return ".";
                case ae::Input::Key::Keyboard_Slash:
                    return "-";
                case ae::Input::Key::Keyboard_Tilde:
                    return "~";
                case ae::Input::Key::Keyboard_LeftBracket:
                    return "[";
                case ae::Input::Key::Keyboard_RightBracket:
                    return "]";
                case ae::Input::Key::Keyboard_BackSlash:
                    return "\\";
                case ae::Input::Key::Keyboard_Quote:
                    return "\'";

                case ae::Input::Key::Keyboard_Clear:
                    return "Clear";
                case ae::Input::Key::Keyboard_Escape:
                    return "Escape";
                case ae::Input::Key::Keyboard_Select:
                    return "Select";
                case ae::Input::Key::Keyboard_Print:
                    return "Print";
                case ae::Input::Key::Keyboard_Execute:
                    return "Execute";
                case ae::Input::Key::Keyboard_Help:
                    return "Help";
                case ae::Input::Key::Keyboard_Applications:
                    return "Applications";
                case ae::Input::Key::Keyboard_Sleep:
                    return "Sleep";

                case ae::Input::Key::Keyboard_BrowserBack:
                    return "BrowserBack";
                case ae::Input::Key::Keyboard_BrowserForward:
                    return "BrowserForward";
                case ae::Input::Key::Keyboard_BrowserRefresh:
                    return "BrowserRefresh";
                case ae::Input::Key::Keyboard_BrowserStop:
                    return "BrowserStop";
                case ae::Input::Key::Keyboard_BrowserSearch:
                    return "BrowserSearch";
                case ae::Input::Key::Keyboard_BrowserFavorites:
                    return "BrowserFavorites";
                case ae::Input::Key::Keyboard_BrowserStartHome:
                    return "BrowserHome";

                case ae::Input::Key::Keyboard_VolumeMute:
                    return "VolumeMute";
                case ae::Input::Key::Keyboard_VolumeDown:
                    return "VolumeDown";
                case ae::Input::Key::Keyboard_VolumeUp:
                    return "VolumeUp";

                case ae::Input::Key::Keyboard_PreviousTrack:
                    return "PreviousTrack";
                case ae::Input::Key::Keyboard_NextTrack:
                    return "NextTrack";
                case ae::Input::Key::Keyboard_StopMedia:
                    return "Stop";
                case ae::Input::Key::Keyboard_PlayPauseMedia:
                    return "Play/Pause";
                case ae::Input::Key::Keyboard_SelectMedia:
                    return "Select";

                case ae::Input::Key::Keyboard_StartMail:
                    return "StartMail";
                case ae::Input::Key::Keyboard_StartApp1:
                    return "LaunchApp1";
                case ae::Input::Key::Keyboard_StartApp2:
                    return "LaunchApp2";

                    /// MOUSE
                case ae::Input::Key::Mouse_LeftButton:
                    return "LeftMouseButton";
                case ae::Input::Key::Mouse_RightButton:
                    return "RightMouseButton";
                case ae::Input::Key::Mouse_MiddleButton:
                    return "MiddleMouseButton";
                case ae::Input::Key::Mouse_X1Button:
                    return "X1MouseButton";
                case ae::Input::Key::Mouse_X2Button:
                    return "X2MouseButton";

                case ae::Input::Key::Keyboard_Unknown:
                case ae::Input::Key::Mouse_Unknown:
                case ae::Input::Key::Gamepad_Unknown:
                case ae::Input::Key::KeyInvalid:
                default:
                    return "Invalid";
            }
        }


    } // Input
} // ae
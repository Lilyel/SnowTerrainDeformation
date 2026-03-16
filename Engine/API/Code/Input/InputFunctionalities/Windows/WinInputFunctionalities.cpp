#include "WinInputFunctionalities.h"

#include "../../../Debugging/Debugging.h"
#include "../../../Graphics/Window/Window.h"
#include "../../../Maths/Primitives/TRect.h"
#include "../InputFunctionalities.h"

#include <windowsx.h>

#ifdef WINDOWS
#define AE_INCLUDE_GLFW_NATIVE
#endif
#include "../../../Graphics/Dependencies/GLFW.h"

namespace ae
{
    namespace priv
    {
        namespace Input
        {

            ae::Input::Key WinKeyToAeroKey( const Int32& _WinKey )
            {
                switch( _WinKey )
                {
                    /// Keyboard

                case VK_NUMPAD0:
                return ae::Input::Key::Keyboard_Numpad0;
                case VK_NUMPAD1:
                return ae::Input::Key::Keyboard_Numpad1;
                case VK_NUMPAD2:
                return ae::Input::Key::Keyboard_Numpad2;
                case VK_NUMPAD3:
                return ae::Input::Key::Keyboard_Numpad3;
                case VK_NUMPAD4:
                return ae::Input::Key::Keyboard_Numpad4;
                case VK_NUMPAD5:
                return ae::Input::Key::Keyboard_Numpad5;
                case VK_NUMPAD6:
                return ae::Input::Key::Keyboard_Numpad6;
                case VK_NUMPAD7:
                return ae::Input::Key::Keyboard_Numpad7;
                case VK_NUMPAD8:
                return ae::Input::Key::Keyboard_Numpad8;
                case VK_NUMPAD9:
                return ae::Input::Key::Keyboard_Numpad9;

                case 0x30:
                return ae::Input::Key::Keyboard_0;
                case 0x31:
                return ae::Input::Key::Keyboard_1;
                case 0x32:
                return ae::Input::Key::Keyboard_2;
                case 0x33:
                return ae::Input::Key::Keyboard_3;
                case 0x34:
                return ae::Input::Key::Keyboard_4;
                case 0x35:
                return ae::Input::Key::Keyboard_5;
                case 0x36:
                return ae::Input::Key::Keyboard_6;
                case 0x37:
                return ae::Input::Key::Keyboard_7;
                case 0x38:
                return ae::Input::Key::Keyboard_8;
                case 0x39:
                return ae::Input::Key::Keyboard_9;

                case 0x41:
                return ae::Input::Key::Keyboard_A;
                case 0x42:
                return ae::Input::Key::Keyboard_B;
                case 0x43:
                return ae::Input::Key::Keyboard_C;
                case 0x44:
                return ae::Input::Key::Keyboard_D;
                case 0x45:
                return ae::Input::Key::Keyboard_E;
                case 0x46:
                return ae::Input::Key::Keyboard_F;
                case 0x47:
                return ae::Input::Key::Keyboard_G;
                case 0x48:
                return ae::Input::Key::Keyboard_H;
                case 0x49:
                return ae::Input::Key::Keyboard_I;
                case 0x4A:
                return ae::Input::Key::Keyboard_J;
                case 0x4B:
                return ae::Input::Key::Keyboard_K;
                case 0x4C:
                return ae::Input::Key::Keyboard_L;
                case 0x4D:
                return ae::Input::Key::Keyboard_M;
                case 0x4E:
                return ae::Input::Key::Keyboard_N;
                case 0x4F:
                return ae::Input::Key::Keyboard_O;
                case 0x50:
                return ae::Input::Key::Keyboard_P;
                case 0x51:
                return ae::Input::Key::Keyboard_Q;
                case 0x52:
                return ae::Input::Key::Keyboard_R;
                case 0x53:
                return ae::Input::Key::Keyboard_S;
                case 0x54:
                return ae::Input::Key::Keyboard_T;
                case 0x55:
                return ae::Input::Key::Keyboard_U;
                case 0x56:
                return ae::Input::Key::Keyboard_V;
                case 0x57:
                return ae::Input::Key::Keyboard_W;
                case 0x58:
                return ae::Input::Key::Keyboard_X;
                case 0x59:
                return ae::Input::Key::Keyboard_Y;
                case 0x5A:
                return ae::Input::Key::Keyboard_Z;

                case VK_F1:
                return ae::Input::Key::Keyboard_F1;
                case VK_F2:
                return ae::Input::Key::Keyboard_F2;
                case VK_F3:
                return ae::Input::Key::Keyboard_F3;
                case VK_F4:
                return ae::Input::Key::Keyboard_F4;
                case VK_F5:
                return ae::Input::Key::Keyboard_F5;
                case VK_F6:
                return ae::Input::Key::Keyboard_F6;
                case VK_F7:
                return ae::Input::Key::Keyboard_F7;
                case VK_F8:
                return ae::Input::Key::Keyboard_F8;
                case VK_F9:
                return ae::Input::Key::Keyboard_F9;
                case VK_F10:
                return ae::Input::Key::Keyboard_F10;
                case VK_F11:
                return ae::Input::Key::Keyboard_F11;
                case VK_F12:
                return ae::Input::Key::Keyboard_F12;
                case VK_F13:
                return ae::Input::Key::Keyboard_F13;
                case VK_F14:
                return ae::Input::Key::Keyboard_F14;
                case VK_F15:
                return ae::Input::Key::Keyboard_F15;
                case VK_F16:
                return ae::Input::Key::Keyboard_F16;
                case VK_F17:
                return ae::Input::Key::Keyboard_F17;
                case VK_F18:
                return ae::Input::Key::Keyboard_F18;
                case VK_F19:
                return ae::Input::Key::Keyboard_F19;
                case VK_F20:
                return ae::Input::Key::Keyboard_F20;
                case VK_F21:
                return ae::Input::Key::Keyboard_F21;
                case VK_F22:
                return ae::Input::Key::Keyboard_F22;
                case VK_F23:
                return ae::Input::Key::Keyboard_F23;
                case VK_F24:
                return ae::Input::Key::Keyboard_F24;

                case VK_MULTIPLY:
                return ae::Input::Key::Keyboard_Multiply;
                case VK_ADD:
                return ae::Input::Key::Keyboard_Add;
                case VK_SUBTRACT:
                return ae::Input::Key::Keyboard_Subtract;
                case VK_DECIMAL:
                return ae::Input::Key::Keyboard_Decimal;
                case VK_DIVIDE:
                return ae::Input::Key::Keyboard_Divide;
                case VK_NUMLOCK:
                return ae::Input::Key::Keyboard_NumLock;

                case VK_PRIOR:
                return ae::Input::Key::Keyboard_PageUp;
                case VK_NEXT:
                return ae::Input::Key::Keyboard_PageDown;
                case VK_HOME:
                return ae::Input::Key::Keyboard_Home;
                case VK_END:
                return ae::Input::Key::Keyboard_End;
                case VK_INSERT:
                return ae::Input::Key::Keyboard_Insert;
                case VK_DELETE:
                return ae::Input::Key::Keyboard_Delete;

                case VK_PAUSE:
                return ae::Input::Key::Keyboard_Pause;
                case VK_SCROLL:
                return ae::Input::Key::Keyboard_ScrollLock;
                case VK_SNAPSHOT:
                return ae::Input::Key::Keyboard_Snapshot;

                case VK_LEFT:
                return ae::Input::Key::Keyboard_LeftArrow;
                case VK_UP:
                return ae::Input::Key::Keyboard_UpArrow;
                case VK_DOWN:
                return ae::Input::Key::Keyboard_DownArrow;
                case VK_RIGHT:
                return ae::Input::Key::Keyboard_RightArrow;

                case VK_SHIFT:
                return ae::Input::Key::Keyboard_RightShift;
                case VK_CONTROL:
                return ae::Input::Key::Keyboard_RightControl;
                case VK_MENU:
                return ae::Input::Key::Keyboard_RightAlt;
                case VK_CAPITAL:
                return ae::Input::Key::Keyboard_CapsLock;
                case VK_BACK:
                return ae::Input::Key::Keyboard_Backspace;
                case VK_TAB:
                return ae::Input::Key::Keyboard_Tab;
                case VK_RETURN:
                return ae::Input::Key::Keyboard_Return;
                case VK_SPACE:
                return ae::Input::Key::Keyboard_Space;
                case VK_LWIN:
                return ae::Input::Key::Keyboard_LeftSystem;
                case VK_RWIN:
                return ae::Input::Key::Keyboard_RightSystem;
                case VK_LSHIFT:
                return ae::Input::Key::Keyboard_LeftShift;
                case VK_RSHIFT:
                return ae::Input::Key::Keyboard_RightShift;
                case VK_LCONTROL:
                return ae::Input::Key::Keyboard_LeftControl;
                case VK_RCONTROL:
                return ae::Input::Key::Keyboard_RightControl;
                case VK_LMENU:
                return ae::Input::Key::Keyboard_LeftAlt;
                case VK_RMENU:
                return ae::Input::Key::Keyboard_RightAlt;
                case VK_OEM_1:
                return ae::Input::Key::Keyboard_SemiColon;
                case VK_OEM_PLUS:
                return ae::Input::Key::Keyboard_Equal;
                case VK_OEM_COMMA:
                return ae::Input::Key::Keyboard_Comma;
                case VK_OEM_MINUS:
                return ae::Input::Key::Keyboard_Dash;
                case VK_OEM_PERIOD:
                return ae::Input::Key::Keyboard_Period;
                case VK_OEM_2:
                return ae::Input::Key::Keyboard_Slash;
                case VK_OEM_3:
                return ae::Input::Key::Keyboard_Tilde;
                case VK_OEM_4:
                return ae::Input::Key::Keyboard_LeftBracket;
                case VK_OEM_6:
                return ae::Input::Key::Keyboard_RightBracket;
                case VK_OEM_5:
                return ae::Input::Key::Keyboard_BackSlash;
                case VK_OEM_7:
                return ae::Input::Key::Keyboard_Quote;

                case VK_CLEAR:
                return ae::Input::Key::Keyboard_Clear;
                case VK_ESCAPE:
                return ae::Input::Key::Keyboard_Escape;
                case VK_SELECT:
                return ae::Input::Key::Keyboard_Select;
                case VK_PRINT:
                return ae::Input::Key::Keyboard_Print;
                case VK_EXECUTE:
                return ae::Input::Key::Keyboard_Execute;
                case VK_HELP:
                return ae::Input::Key::Keyboard_Help;
                case VK_APPS:
                return ae::Input::Key::Keyboard_Applications;
                case VK_SLEEP:
                return ae::Input::Key::Keyboard_Sleep;

                case VK_BROWSER_BACK:
                return ae::Input::Key::Keyboard_BrowserBack;
                case VK_BROWSER_FORWARD:
                return ae::Input::Key::Keyboard_BrowserForward;
                case VK_BROWSER_REFRESH:
                return ae::Input::Key::Keyboard_BrowserRefresh;
                case VK_BROWSER_STOP:
                return ae::Input::Key::Keyboard_BrowserStop;
                case VK_BROWSER_SEARCH:
                return ae::Input::Key::Keyboard_BrowserSearch;
                case VK_BROWSER_FAVORITES:
                return ae::Input::Key::Keyboard_BrowserFavorites;
                case VK_BROWSER_HOME:
                return ae::Input::Key::Keyboard_BrowserStartHome;

                case VK_VOLUME_MUTE:
                return ae::Input::Key::Keyboard_VolumeMute;
                case VK_VOLUME_DOWN:
                return ae::Input::Key::Keyboard_VolumeDown;
                case VK_VOLUME_UP:
                return ae::Input::Key::Keyboard_VolumeUp;

                case VK_MEDIA_PREV_TRACK:
                return ae::Input::Key::Keyboard_PreviousTrack;
                case VK_MEDIA_NEXT_TRACK:
                return ae::Input::Key::Keyboard_NextTrack;
                case VK_MEDIA_STOP:
                return ae::Input::Key::Keyboard_StopMedia;
                case VK_MEDIA_PLAY_PAUSE:
                return ae::Input::Key::Keyboard_PlayPauseMedia;
                case VK_LAUNCH_MEDIA_SELECT:
                return ae::Input::Key::Keyboard_SelectMedia;

                case VK_LAUNCH_MAIL:
                return ae::Input::Key::Keyboard_StartMail;
                case VK_LAUNCH_APP1:
                return ae::Input::Key::Keyboard_StartApp1;
                case VK_LAUNCH_APP2:
                return ae::Input::Key::Keyboard_StartApp2;

                /// MOUSE
                case VK_LBUTTON:
                return ae::Input::Key::Mouse_LeftButton;
                case VK_RBUTTON:
                return ae::Input::Key::Mouse_RightButton;
                case VK_MBUTTON:
                return ae::Input::Key::Mouse_MiddleButton;
                case VK_XBUTTON1:
                return ae::Input::Key::Mouse_X1Button;
                case VK_XBUTTON2:
                return ae::Input::Key::Mouse_X2Button;


                default:
                return ae::Input::Key::KeyInvalid;
                }
            }

            Int32 AeroKeyToWinKey( const ae::Input::Key& _Key )
            {
                switch( _Key )
                {
                    /// Keyboard

                case ae::Input::Key::Keyboard_Numpad0:
                return VK_NUMPAD0;
                case ae::Input::Key::Keyboard_Numpad1:
                return VK_NUMPAD1;
                case ae::Input::Key::Keyboard_Numpad2:
                return VK_NUMPAD2;
                case ae::Input::Key::Keyboard_Numpad3:
                return VK_NUMPAD3;
                case ae::Input::Key::Keyboard_Numpad4:
                return VK_NUMPAD4;
                case ae::Input::Key::Keyboard_Numpad5:
                return VK_NUMPAD5;
                case ae::Input::Key::Keyboard_Numpad6:
                return VK_NUMPAD6;
                case ae::Input::Key::Keyboard_Numpad7:
                return VK_NUMPAD7;
                case ae::Input::Key::Keyboard_Numpad8:
                return VK_NUMPAD8;
                case ae::Input::Key::Keyboard_Numpad9:
                return VK_NUMPAD9;

                case ae::Input::Key::Keyboard_0:
                return 0x30;
                case ae::Input::Key::Keyboard_1:
                return 0x31;
                case ae::Input::Key::Keyboard_2:
                return 0x32;
                case ae::Input::Key::Keyboard_3:
                return 0x33;
                case ae::Input::Key::Keyboard_4:
                return 0x34;
                case ae::Input::Key::Keyboard_5:
                return 0x35;
                case ae::Input::Key::Keyboard_6:
                return 0x36;
                case ae::Input::Key::Keyboard_7:
                return 0x37;
                case ae::Input::Key::Keyboard_8:
                return 0x38;
                case ae::Input::Key::Keyboard_9:
                return 0x39;

                case ae::Input::Key::Keyboard_A:
                return 0x41;
                case ae::Input::Key::Keyboard_B:
                return 0x42;
                case ae::Input::Key::Keyboard_C:
                return 0x43;
                case ae::Input::Key::Keyboard_D:
                return 0x44;
                case ae::Input::Key::Keyboard_E:
                return 0x45;
                case ae::Input::Key::Keyboard_F:
                return 0x46;
                case ae::Input::Key::Keyboard_G:
                return 0x47;
                case ae::Input::Key::Keyboard_H:
                return 0x48;
                case ae::Input::Key::Keyboard_I:
                return 0x49;
                case ae::Input::Key::Keyboard_J:
                return 0x4A;
                case ae::Input::Key::Keyboard_K:
                return 0x4B;
                case ae::Input::Key::Keyboard_L:
                return 0x4C;
                case ae::Input::Key::Keyboard_M:
                return 0x4D;
                case ae::Input::Key::Keyboard_N:
                return 0x4E;
                case ae::Input::Key::Keyboard_O:
                return 0x4F;
                case ae::Input::Key::Keyboard_P:
                return 0x50;
                case ae::Input::Key::Keyboard_Q:
                return 0x51;
                case ae::Input::Key::Keyboard_R:
                return 0x52;
                case ae::Input::Key::Keyboard_S:
                return 0x53;
                case ae::Input::Key::Keyboard_T:
                return 0x54;
                case ae::Input::Key::Keyboard_U:
                return 0x55;
                case ae::Input::Key::Keyboard_V:
                return 0x56;
                case ae::Input::Key::Keyboard_W:
                return 0x57;
                case ae::Input::Key::Keyboard_X:
                return 0x58;
                case ae::Input::Key::Keyboard_Y:
                return 0x59;
                case ae::Input::Key::Keyboard_Z:
                return 0x5A;

                case ae::Input::Key::Keyboard_F1:
                return VK_F1;
                case ae::Input::Key::Keyboard_F2:
                return VK_F2;
                case ae::Input::Key::Keyboard_F3:
                return VK_F3;
                case ae::Input::Key::Keyboard_F4:
                return VK_F4;
                case ae::Input::Key::Keyboard_F5:
                return VK_F5;
                case ae::Input::Key::Keyboard_F6:
                return VK_F6;
                case ae::Input::Key::Keyboard_F7:
                return VK_F7;
                case ae::Input::Key::Keyboard_F8:
                return VK_F8;
                case ae::Input::Key::Keyboard_F9:
                return VK_F9;
                case ae::Input::Key::Keyboard_F10:
                return VK_F10;
                case ae::Input::Key::Keyboard_F11:
                return VK_F11;
                case ae::Input::Key::Keyboard_F12:
                return VK_F12;
                case ae::Input::Key::Keyboard_F13:
                return VK_F13;
                case ae::Input::Key::Keyboard_F14:
                return VK_F14;
                case ae::Input::Key::Keyboard_F15:
                return VK_F15;
                case ae::Input::Key::Keyboard_F16:
                return VK_F16;
                case ae::Input::Key::Keyboard_F17:
                return VK_F17;
                case ae::Input::Key::Keyboard_F18:
                return VK_F18;
                case ae::Input::Key::Keyboard_F19:
                return VK_F19;
                case ae::Input::Key::Keyboard_F20:
                return VK_F20;
                case ae::Input::Key::Keyboard_F21:
                return VK_F21;
                case ae::Input::Key::Keyboard_F22:
                return VK_F22;
                case ae::Input::Key::Keyboard_F23:
                return VK_F23;
                case ae::Input::Key::Keyboard_F24:
                return VK_F24;

                case ae::Input::Key::Keyboard_Multiply:
                return VK_MULTIPLY;
                case ae::Input::Key::Keyboard_Add:
                return VK_ADD;
                case ae::Input::Key::Keyboard_Subtract:
                return VK_SUBTRACT;
                case ae::Input::Key::Keyboard_Decimal:
                return VK_DECIMAL;
                case ae::Input::Key::Keyboard_Divide:
                return VK_DIVIDE;
                case ae::Input::Key::Keyboard_NumLock:
                return VK_NUMLOCK;

                case ae::Input::Key::Keyboard_PageUp:
                return VK_PRIOR;
                case ae::Input::Key::Keyboard_PageDown:
                return VK_NEXT;
                case ae::Input::Key::Keyboard_Home:
                return VK_HOME;
                case ae::Input::Key::Keyboard_End:
                return VK_END;
                case ae::Input::Key::Keyboard_Insert:
                return VK_INSERT;
                case ae::Input::Key::Keyboard_Delete:
                return VK_DELETE;

                case ae::Input::Key::Keyboard_Pause:
                return VK_PAUSE;
                case ae::Input::Key::Keyboard_ScrollLock:
                return VK_SCROLL;
                case ae::Input::Key::Keyboard_Snapshot:
                return VK_SNAPSHOT;

                case ae::Input::Key::Keyboard_LeftArrow:
                return VK_LEFT;
                case ae::Input::Key::Keyboard_UpArrow:
                return VK_UP;
                case ae::Input::Key::Keyboard_DownArrow:
                return VK_DOWN;
                case ae::Input::Key::Keyboard_RightArrow:
                return VK_RIGHT;

                case ae::Input::Key::Keyboard_RightShift:
                return VK_SHIFT;
                case ae::Input::Key::Keyboard_RightControl:
                return VK_CONTROL;
                case ae::Input::Key::Keyboard_RightAlt:
                return VK_MENU;
                case ae::Input::Key::Keyboard_CapsLock:
                return VK_CAPITAL;
                case ae::Input::Key::Keyboard_Backspace:
                return VK_BACK;
                case ae::Input::Key::Keyboard_Tab:
                return VK_TAB;
                case ae::Input::Key::Keyboard_Return:
                return VK_RETURN;
                case ae::Input::Key::Keyboard_Space:
                return VK_SPACE;
                case ae::Input::Key::Keyboard_LeftSystem:
                return VK_LWIN;
                case ae::Input::Key::Keyboard_RightSystem:
                return VK_RWIN;
                case ae::Input::Key::Keyboard_LeftShift:
                return VK_LSHIFT;
                case ae::Input::Key::Keyboard_LeftControl:
                return VK_LCONTROL;
                case ae::Input::Key::Keyboard_Menu:
                return VK_LMENU;
                case ae::Input::Key::Keyboard_SemiColon:
                return VK_OEM_1;
                case ae::Input::Key::Keyboard_Equal:
                return VK_OEM_PLUS;
                case ae::Input::Key::Keyboard_Comma:
                return VK_OEM_COMMA;
                case ae::Input::Key::Keyboard_Dash:
                return VK_OEM_MINUS;
                case ae::Input::Key::Keyboard_Period:
                return VK_OEM_PERIOD;
                case ae::Input::Key::Keyboard_Slash:
                return VK_OEM_2;
                case ae::Input::Key::Keyboard_Tilde:
                return VK_OEM_3;
                case ae::Input::Key::Keyboard_LeftBracket:
                return VK_OEM_4;
                case ae::Input::Key::Keyboard_RightBracket:
                return VK_OEM_6;
                case ae::Input::Key::Keyboard_BackSlash:
                return VK_OEM_5;
                case ae::Input::Key::Keyboard_Quote:
                return VK_OEM_7;

                case ae::Input::Key::Keyboard_Clear:
                return VK_CLEAR;
                case ae::Input::Key::Keyboard_Escape:
                return VK_ESCAPE;
                case ae::Input::Key::Keyboard_Select:
                return VK_SELECT;
                case ae::Input::Key::Keyboard_Print:
                return VK_PRINT;
                case ae::Input::Key::Keyboard_Execute:
                return VK_EXECUTE;
                case ae::Input::Key::Keyboard_Help:
                return VK_HELP;
                case ae::Input::Key::Keyboard_Applications:
                return VK_APPS;
                case ae::Input::Key::Keyboard_Sleep:
                return VK_SLEEP;

                case ae::Input::Key::Keyboard_BrowserBack:
                return VK_BROWSER_BACK;
                case ae::Input::Key::Keyboard_BrowserForward:
                return VK_BROWSER_FORWARD;
                case ae::Input::Key::Keyboard_BrowserRefresh:
                return VK_BROWSER_REFRESH;
                case ae::Input::Key::Keyboard_BrowserStop:
                return VK_BROWSER_STOP;
                case ae::Input::Key::Keyboard_BrowserSearch:
                return VK_BROWSER_SEARCH;
                case ae::Input::Key::Keyboard_BrowserFavorites:
                return VK_BROWSER_FAVORITES;
                case ae::Input::Key::Keyboard_BrowserStartHome:
                return VK_BROWSER_HOME;

                case ae::Input::Key::Keyboard_VolumeMute:
                return VK_VOLUME_MUTE;
                case ae::Input::Key::Keyboard_VolumeDown:
                return VK_VOLUME_DOWN;
                case ae::Input::Key::Keyboard_VolumeUp:
                return VK_VOLUME_UP;

                case ae::Input::Key::Keyboard_PreviousTrack:
                return VK_MEDIA_PREV_TRACK;
                case ae::Input::Key::Keyboard_NextTrack:
                return VK_MEDIA_NEXT_TRACK;
                case ae::Input::Key::Keyboard_StopMedia:
                return VK_MEDIA_STOP;
                case ae::Input::Key::Keyboard_PlayPauseMedia:
                return VK_MEDIA_PLAY_PAUSE;
                case ae::Input::Key::Keyboard_SelectMedia:
                return VK_LAUNCH_MEDIA_SELECT;

                case ae::Input::Key::Keyboard_StartMail:
                return VK_LAUNCH_MAIL;
                case ae::Input::Key::Keyboard_StartApp1:
                return VK_LAUNCH_APP1;
                case ae::Input::Key::Keyboard_StartApp2:
                return VK_LAUNCH_APP2;

                /// MOUSE
                case ae::Input::Key::Mouse_LeftButton:
                return VK_LBUTTON;
                case ae::Input::Key::Mouse_RightButton:
                return VK_RBUTTON;
                case ae::Input::Key::Mouse_MiddleButton:
                return VK_MBUTTON;
                case ae::Input::Key::Mouse_X1Button:
                return VK_XBUTTON1;
                case ae::Input::Key::Mouse_X2Button:
                return VK_XBUTTON2;

                case ae::Input::Key::Keyboard_Unknown:
                case ae::Input::Key::Mouse_Unknown:
                case ae::Input::Key::Gamepad_Unknown:
                case ae::Input::Key::KeyInvalid:
                default:
                return -1;
                }
            }

            void ClipMouse( const HWND& _WindowHandle, const FloatRect& _ClipArea )
            {
                // Client area is in client coordinates, ClipCursor need screen coordinates.
                // So we need to convert the coordinates.

                POINT LeftTop = { Cast( LONG, _ClipArea.Left ),  Cast( LONG, _ClipArea.Top ) };
                POINT RightBottom = { Cast( LONG, _ClipArea.Right ),  Cast( LONG, _ClipArea.Bottom ) };

                ClientToScreen( _WindowHandle, &LeftTop );
                ClientToScreen( _WindowHandle, &RightBottom );

                RECT WinClipArea;
                SetRect( &WinClipArea, LeftTop.x, LeftTop.y, RightBottom.x, RightBottom.y );

                if( !ClipCursor( &WinClipArea ) )
                {
                    errno_t Error = GetLastError();
                    AE_ErrorCheckErrno( Error );
                }
            }

            void ClipMouseStop()
            {
                if( !ClipCursor( NULL ) )
                {
                    errno_t Error = GetLastError();
                    AE_ErrorCheckErrno( Error );
                }
            }
            
            AERO_CORE_EXPORT Int32 ScanCodeToWinKey( const Int32& _ScanCode )
            {
                switch( _ScanCode )
                {
                case 328:
                return VK_UP;
                case 331:
                return VK_LEFT;
                case 333:
                return VK_RIGHT;
                case 336:
                return VK_DOWN;

                default:
                return MapVirtualKeyA( _ScanCode, MAPVK_VSC_TO_VK_EX );
                }
            }

            AERO_CORE_EXPORT HWND GetNativeWinHandleFromGLFW( GLFWwindow* _GLFWWindow )
            {
                return glfwGetWin32Window( _GLFWWindow );
            }

        } // Input
    } // priv 
} // ae

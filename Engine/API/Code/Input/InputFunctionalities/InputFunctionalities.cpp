#include "InputFunctionalities.h"

#include "../../Aero/Aero.h"
#include "../../Graphics/Window/Window.h"
#include "../../Maths/Primitives/TRect.h"
#include "../InputManager/InputManager.h"

#ifdef WINDOWS
#include "Windows/WinInputFunctionalities.h"
#endif
#include "../../Graphics/Dependencies/GLFW.h"

namespace ae
{
    namespace Input
    {

        Bool IsKeyboardKey( const Key& _Key )
        {
            return (_Key < Key::Keyboard_Unknown);
        }

        Bool IsMouseKey( const Key& _Key )
        {
            return ( _Key > Key::Keyboard_Unknown && _Key < Key::Mouse_Unknown );
        }

        Bool IsGamepadKey( const Key& _Key )
        {
            return ( _Key > Key::Mouse_Unknown );
        }

        State GetKeyState( const Key& _Key )
        {
            return Aero.GetInputManger().GetKeyState( _Key );
        }

        Bool IsKeyPressed( const Key& _Key )
        {
            return ( Aero.GetInputManger().GetKeyState( _Key ) == State::Pressed );
        }
        Bool IsKeyDown( const Key& _Key )
        {
            return ( Aero.GetInputManger().GetKeyState( _Key ) == State::Down );
        }
        Bool IsKeyReleased( const Key& _Key )
        {
            return ( Aero.GetInputManger().GetKeyState( _Key ) == State::Released );
        }
        Bool IsKeyUp( const Key& _Key )
        {
            return ( Aero.GetInputManger().GetKeyState( _Key ) == State::Up );
        }

        Bool IsKeyValid( const Key & _Key )
        {
            if( _Key >= Key::KeyCount )
                return False;

            if( IsKeyboardKey( _Key ) && _Key == Key::Keyboard_Unknown )
                return False;

            if( IsMouseKey( _Key ) && _Key == Key::Mouse_Unknown )
                return False;

            if( IsGamepadKey( _Key ) && _Key == Key::Gamepad_Unknown )
                return False;

            return True;
        }

        Bool IsCaps()
        {
            return Aero.GetInputManger().IsCaps();
        }

        Bool IsKeyboardHit()
        {
            return Aero.GetInputManger().IsKeyboardHit();
        }

        Bool IsMouseHit()
        {
            return Aero.GetInputManger().IsMouseHit();
        }

        Bool IsGamepadHit()
        {
            return Aero.GetInputManger().IsGamepadHit();
        }

        const Vector2& GetMousePosition()
        {
            return Aero.GetInputManger().GetMousePosition();
        }

        const Vector2& GetMouseDeltaMove()
        {
            return Aero.GetInputManger().GetMouseDeltaMove();
        }

		const Int16 GetMouseDeltaWheel()
		{
			return Aero.GetInputManger().GetMouseDeltaWheel();
		}

        void ClipMouse( Window& _Window, const FloatRect& _ClipArea )
        {
#ifdef WINDOWS
           ae::priv::Input::ClipMouse( ae::priv::Input::GetNativeWinHandleFromGLFW( &_Window.GetGLFWWindow() ), _ClipArea );
#else
#pragma message (": warning : ClipMouse not implemented on this platform.")
#endif
        }

        void ClipMouseToWindow( Window& _Window )
        {
#ifdef WINDOWS
            ae::priv::Input::ClipMouse( ae::priv::Input::GetNativeWinHandleFromGLFW( &_Window.GetGLFWWindow() ), _Window.GetWindowRect() );
#else
#pragma message (": warning : ClipMouseToWindow not implemented on this platform.")
#endif
        }

        void ClipMouseStop()
        {
#ifdef WINDOWS
            ae::priv::Input::ClipMouseStop();
#else
#pragma message (": warning : ClipMouseStop not implemented on this platform.")
#endif
        }

        void SetMousePosition( Window& _Window, const ae::Vector2& _Position )
        {
            ae::priv::Input::SetMousePosition( _Window, _Position );
        }

    } // Input


    namespace priv
    {
        namespace Input
        {
            ae::Input::Key GLFWKeyToAeroKey( const Int32& _GLFWKey )
            {
                switch( _GLFWKey )
                {
                case GLFW_KEY_SPACE: return ae::Input::Key::Keyboard_Space;

                case GLFW_KEY_APOSTROPHE: return ae::Input::Key::Keyboard_Quote;
                case GLFW_KEY_COMMA: return ae::Input::Key::Keyboard_Comma;
                case GLFW_KEY_MINUS: return ae::Input::Key::Keyboard_Subtract;
                case GLFW_KEY_PERIOD: return ae::Input::Key::Keyboard_Period;
                case GLFW_KEY_SLASH: return ae::Input::Key::Keyboard_Slash;
                case GLFW_KEY_SEMICOLON: return ae::Input::Key::Keyboard_SemiColon;
                case GLFW_KEY_EQUAL: return ae::Input::Key::Keyboard_Equal;

                case GLFW_KEY_0: return ae::Input::Key::Keyboard_0;
                case GLFW_KEY_1: return ae::Input::Key::Keyboard_1;
                case GLFW_KEY_2: return ae::Input::Key::Keyboard_2;
                case GLFW_KEY_3: return ae::Input::Key::Keyboard_3;
                case GLFW_KEY_4: return ae::Input::Key::Keyboard_4;
                case GLFW_KEY_5: return ae::Input::Key::Keyboard_5;
                case GLFW_KEY_6: return ae::Input::Key::Keyboard_6;
                case GLFW_KEY_7: return ae::Input::Key::Keyboard_7;
                case GLFW_KEY_8: return ae::Input::Key::Keyboard_8;
                case GLFW_KEY_9: return ae::Input::Key::Keyboard_9;

                case GLFW_KEY_A: return ae::Input::Key::Keyboard_A;
                case GLFW_KEY_B: return ae::Input::Key::Keyboard_B;
                case GLFW_KEY_C: return ae::Input::Key::Keyboard_C;
                case GLFW_KEY_D: return ae::Input::Key::Keyboard_D;
                case GLFW_KEY_E: return ae::Input::Key::Keyboard_E;
                case GLFW_KEY_F: return ae::Input::Key::Keyboard_F;
                case GLFW_KEY_G: return ae::Input::Key::Keyboard_G;
                case GLFW_KEY_H: return ae::Input::Key::Keyboard_H;
                case GLFW_KEY_I: return ae::Input::Key::Keyboard_I;
                case GLFW_KEY_J: return ae::Input::Key::Keyboard_J;
                case GLFW_KEY_K: return ae::Input::Key::Keyboard_K;
                case GLFW_KEY_L: return ae::Input::Key::Keyboard_L;
                case GLFW_KEY_M: return ae::Input::Key::Keyboard_M;
                case GLFW_KEY_N: return ae::Input::Key::Keyboard_N;
                case GLFW_KEY_O: return ae::Input::Key::Keyboard_O;
                case GLFW_KEY_P: return ae::Input::Key::Keyboard_P;
                case GLFW_KEY_Q: return ae::Input::Key::Keyboard_Q;
                case GLFW_KEY_R: return ae::Input::Key::Keyboard_R;
                case GLFW_KEY_S: return ae::Input::Key::Keyboard_S;
                case GLFW_KEY_T: return ae::Input::Key::Keyboard_T;
                case GLFW_KEY_U: return ae::Input::Key::Keyboard_U;
                case GLFW_KEY_V: return ae::Input::Key::Keyboard_V;
                case GLFW_KEY_W: return ae::Input::Key::Keyboard_W;
                case GLFW_KEY_X: return ae::Input::Key::Keyboard_X;
                case GLFW_KEY_Y: return ae::Input::Key::Keyboard_Y;
                case GLFW_KEY_Z: return ae::Input::Key::Keyboard_Z;

                case GLFW_KEY_LEFT_BRACKET: return ae::Input::Key::Keyboard_LeftBracket;
                case GLFW_KEY_RIGHT_BRACKET: return ae::Input::Key::Keyboard_RightBracket;

                case GLFW_KEY_BACKSLASH: return ae::Input::Key::Keyboard_BackSlash;
                case GLFW_KEY_ESCAPE: return ae::Input::Key::Keyboard_Escape;
                case GLFW_KEY_ENTER: return ae::Input::Key::Keyboard_Return;
                case GLFW_KEY_TAB: return ae::Input::Key::Keyboard_Tab;
                case GLFW_KEY_BACKSPACE: return ae::Input::Key::Keyboard_Backspace;

                case GLFW_KEY_INSERT: return ae::Input::Key::Keyboard_Insert;
                case GLFW_KEY_DELETE: return ae::Input::Key::Keyboard_Delete;

                case GLFW_KEY_RIGHT: return ae::Input::Key::Keyboard_RightArrow;
                case GLFW_KEY_LEFT: return ae::Input::Key::Keyboard_LeftArrow;
                case GLFW_KEY_DOWN: return ae::Input::Key::Keyboard_DownArrow;
                case GLFW_KEY_UP: return ae::Input::Key::Keyboard_UpArrow;

                case GLFW_KEY_PAGE_UP: return ae::Input::Key::Keyboard_PageUp;
                case GLFW_KEY_PAGE_DOWN: return ae::Input::Key::Keyboard_PageDown;
                case GLFW_KEY_HOME: return ae::Input::Key::Keyboard_Home;
                case GLFW_KEY_END: return ae::Input::Key::Keyboard_End;

                case GLFW_KEY_CAPS_LOCK: return ae::Input::Key::Keyboard_CapsLock;
                case GLFW_KEY_SCROLL_LOCK: return ae::Input::Key::Keyboard_ScrollLock;
                case GLFW_KEY_NUM_LOCK: return ae::Input::Key::Keyboard_NumLock;
                case GLFW_KEY_PRINT_SCREEN: return ae::Input::Key::Keyboard_PrintScreen;
                case GLFW_KEY_PAUSE: return ae::Input::Key::Keyboard_Pause;

                case GLFW_KEY_F1: return ae::Input::Key::Keyboard_F1;
                case GLFW_KEY_F2: return ae::Input::Key::Keyboard_F2;
                case GLFW_KEY_F3: return ae::Input::Key::Keyboard_F3;
                case GLFW_KEY_F4: return ae::Input::Key::Keyboard_F4;
                case GLFW_KEY_F5: return ae::Input::Key::Keyboard_F5;
                case GLFW_KEY_F6: return ae::Input::Key::Keyboard_F6;
                case GLFW_KEY_F7: return ae::Input::Key::Keyboard_F7;
                case GLFW_KEY_F8: return ae::Input::Key::Keyboard_F8;
                case GLFW_KEY_F9: return ae::Input::Key::Keyboard_F9;
                case GLFW_KEY_F10: return ae::Input::Key::Keyboard_F10;
                case GLFW_KEY_F11: return ae::Input::Key::Keyboard_F11;
                case GLFW_KEY_F12: return ae::Input::Key::Keyboard_F12;
                case GLFW_KEY_F13: return ae::Input::Key::Keyboard_F13;
                case GLFW_KEY_F14: return ae::Input::Key::Keyboard_F14;
                case GLFW_KEY_F15: return ae::Input::Key::Keyboard_F15;
                case GLFW_KEY_F16: return ae::Input::Key::Keyboard_F16;
                case GLFW_KEY_F17: return ae::Input::Key::Keyboard_F17;
                case GLFW_KEY_F18: return ae::Input::Key::Keyboard_F18;
                case GLFW_KEY_F19: return ae::Input::Key::Keyboard_F19;
                case GLFW_KEY_F20: return ae::Input::Key::Keyboard_F20;
                case GLFW_KEY_F21: return ae::Input::Key::Keyboard_F21;
                case GLFW_KEY_F22: return ae::Input::Key::Keyboard_F22;
                case GLFW_KEY_F23: return ae::Input::Key::Keyboard_F23;
                case GLFW_KEY_F24: return ae::Input::Key::Keyboard_F24;
                case GLFW_KEY_F25: return ae::Input::Key::Keyboard_F25;

                case GLFW_KEY_KP_0: return ae::Input::Key::Keyboard_Numpad0;
                case GLFW_KEY_KP_1: return ae::Input::Key::Keyboard_Numpad1;
                case GLFW_KEY_KP_2: return ae::Input::Key::Keyboard_Numpad2;
                case GLFW_KEY_KP_3: return ae::Input::Key::Keyboard_Numpad3;
                case GLFW_KEY_KP_4: return ae::Input::Key::Keyboard_Numpad4;
                case GLFW_KEY_KP_5: return ae::Input::Key::Keyboard_Numpad5;
                case GLFW_KEY_KP_6: return ae::Input::Key::Keyboard_Numpad6;
                case GLFW_KEY_KP_7: return ae::Input::Key::Keyboard_Numpad7;
                case GLFW_KEY_KP_8: return ae::Input::Key::Keyboard_Numpad8;
                case GLFW_KEY_KP_9: return ae::Input::Key::Keyboard_Numpad9;

                case GLFW_KEY_KP_DECIMAL: return ae::Input::Key::Keyboard_Decimal;
                case GLFW_KEY_KP_DIVIDE: return ae::Input::Key::Keyboard_Divide;
                case GLFW_KEY_KP_MULTIPLY: return ae::Input::Key::Keyboard_Multiply;
                case GLFW_KEY_KP_SUBTRACT: return ae::Input::Key::Keyboard_Subtract;
                case GLFW_KEY_KP_ADD: return ae::Input::Key::Keyboard_Add;
                case GLFW_KEY_KP_ENTER: return ae::Input::Key::Keyboard_Return;
                case GLFW_KEY_KP_EQUAL: return ae::Input::Key::Keyboard_Equal;

                case GLFW_KEY_LEFT_SHIFT: return ae::Input::Key::Keyboard_LeftShift;
                case GLFW_KEY_LEFT_CONTROL: return ae::Input::Key::Keyboard_LeftControl;
                case GLFW_KEY_LEFT_ALT: return ae::Input::Key::Keyboard_LeftAlt;
                case GLFW_KEY_LEFT_SUPER: return ae::Input::Key::Keyboard_LeftSystem;

                case GLFW_KEY_RIGHT_SHIFT: return ae::Input::Key::Keyboard_RightShift;
                case GLFW_KEY_RIGHT_CONTROL: return ae::Input::Key::Keyboard_RightControl;
                case GLFW_KEY_RIGHT_ALT: return ae::Input::Key::Keyboard_RightAlt;
                case GLFW_KEY_MENU: return ae::Input::Key::Keyboard_Menu;


                case GLFW_MOUSE_BUTTON_LEFT: return ae::Input::Key::Mouse_LeftButton;
                case GLFW_MOUSE_BUTTON_RIGHT: return ae::Input::Key::Mouse_RightButton;
                case GLFW_MOUSE_BUTTON_MIDDLE: return ae::Input::Key::Mouse_MiddleButton;

                case GLFW_MOUSE_BUTTON_4: return ae::Input::Key::Mouse_X1Button;
                case GLFW_MOUSE_BUTTON_5: return ae::Input::Key::Mouse_X2Button;

                case GLFW_KEY_UNKNOWN:
                default:
                return ae::Input::Key::KeyInvalid;
                }
            }

            Int32 AeroKeyToGLFWKey( const ae::Input::Key& _Key )
            {
                switch( _Key )
                {
                case ae::Input::Key::Keyboard_Space: return GLFW_KEY_SPACE;

                case ae::Input::Key::Keyboard_Quote: return GLFW_KEY_APOSTROPHE;
                case ae::Input::Key::Keyboard_Comma: return GLFW_KEY_COMMA;
                case ae::Input::Key::Keyboard_Subtract: return GLFW_KEY_MINUS;
                case ae::Input::Key::Keyboard_Period: return GLFW_KEY_PERIOD;
                case ae::Input::Key::Keyboard_Slash: return GLFW_KEY_SLASH;
                case ae::Input::Key::Keyboard_SemiColon: return GLFW_KEY_SEMICOLON;
                case ae::Input::Key::Keyboard_Equal: return GLFW_KEY_EQUAL;

                case ae::Input::Key::Keyboard_0: return GLFW_KEY_0;
                case ae::Input::Key::Keyboard_1: return GLFW_KEY_1;
                case ae::Input::Key::Keyboard_2: return GLFW_KEY_2;
                case ae::Input::Key::Keyboard_3: return GLFW_KEY_3;
                case ae::Input::Key::Keyboard_4: return GLFW_KEY_4;
                case ae::Input::Key::Keyboard_5: return GLFW_KEY_5;
                case ae::Input::Key::Keyboard_6: return GLFW_KEY_6;
                case ae::Input::Key::Keyboard_7: return GLFW_KEY_7;
                case ae::Input::Key::Keyboard_8: return GLFW_KEY_8;
                case ae::Input::Key::Keyboard_9: return GLFW_KEY_9;

                case ae::Input::Key::Keyboard_A: return GLFW_KEY_A;
                case ae::Input::Key::Keyboard_B: return GLFW_KEY_B;
                case ae::Input::Key::Keyboard_C: return GLFW_KEY_C;
                case ae::Input::Key::Keyboard_D: return GLFW_KEY_D;
                case ae::Input::Key::Keyboard_E: return GLFW_KEY_E;
                case ae::Input::Key::Keyboard_F: return GLFW_KEY_F;
                case ae::Input::Key::Keyboard_G: return GLFW_KEY_G;
                case ae::Input::Key::Keyboard_H: return GLFW_KEY_H;
                case ae::Input::Key::Keyboard_I: return GLFW_KEY_I;
                case ae::Input::Key::Keyboard_J: return GLFW_KEY_J;
                case ae::Input::Key::Keyboard_K: return GLFW_KEY_K;
                case ae::Input::Key::Keyboard_L: return GLFW_KEY_L;
                case ae::Input::Key::Keyboard_M: return GLFW_KEY_M;
                case ae::Input::Key::Keyboard_N: return GLFW_KEY_N;
                case ae::Input::Key::Keyboard_O: return GLFW_KEY_O;
                case ae::Input::Key::Keyboard_P: return GLFW_KEY_P;
                case ae::Input::Key::Keyboard_Q: return GLFW_KEY_Q;
                case ae::Input::Key::Keyboard_R: return GLFW_KEY_R;
                case ae::Input::Key::Keyboard_S: return GLFW_KEY_S;
                case ae::Input::Key::Keyboard_T: return GLFW_KEY_T;
                case ae::Input::Key::Keyboard_U: return GLFW_KEY_U;
                case ae::Input::Key::Keyboard_V: return GLFW_KEY_V;
                case ae::Input::Key::Keyboard_W: return GLFW_KEY_W;
                case ae::Input::Key::Keyboard_X: return GLFW_KEY_X;
                case ae::Input::Key::Keyboard_Y: return GLFW_KEY_Y;
                case ae::Input::Key::Keyboard_Z: return GLFW_KEY_Z;

                case ae::Input::Key::Keyboard_LeftBracket: return GLFW_KEY_LEFT_BRACKET;
                case ae::Input::Key::Keyboard_RightBracket: return GLFW_KEY_RIGHT_BRACKET;

                case ae::Input::Key::Keyboard_BackSlash: return GLFW_KEY_BACKSLASH;
                case ae::Input::Key::Keyboard_Escape: return GLFW_KEY_ESCAPE;
                case ae::Input::Key::Keyboard_Return: return GLFW_KEY_ENTER;
                case ae::Input::Key::Keyboard_Tab: return GLFW_KEY_TAB;
                case ae::Input::Key::Keyboard_Backspace: return GLFW_KEY_BACKSPACE;

                case ae::Input::Key::Keyboard_Insert: return GLFW_KEY_INSERT;
                case ae::Input::Key::Keyboard_Delete: return GLFW_KEY_DELETE;

                case ae::Input::Key::Keyboard_RightArrow: return GLFW_KEY_RIGHT;
                case ae::Input::Key::Keyboard_LeftArrow: return GLFW_KEY_LEFT;
                case ae::Input::Key::Keyboard_DownArrow: return GLFW_KEY_DOWN;
                case ae::Input::Key::Keyboard_UpArrow: return GLFW_KEY_UP;

                case ae::Input::Key::Keyboard_PageUp: return GLFW_KEY_PAGE_UP;
                case ae::Input::Key::Keyboard_PageDown: return GLFW_KEY_PAGE_DOWN;
                case ae::Input::Key::Keyboard_Home: return GLFW_KEY_HOME;
                case ae::Input::Key::Keyboard_End: return GLFW_KEY_END;

                case ae::Input::Key::Keyboard_CapsLock: return GLFW_KEY_CAPS_LOCK;
                case ae::Input::Key::Keyboard_ScrollLock: return GLFW_KEY_SCROLL_LOCK;
                case ae::Input::Key::Keyboard_NumLock: return GLFW_KEY_NUM_LOCK;
                case ae::Input::Key::Keyboard_PrintScreen: return GLFW_KEY_PRINT_SCREEN;
                case ae::Input::Key::Keyboard_Pause: return GLFW_KEY_PAUSE;

                case ae::Input::Key::Keyboard_F1: return GLFW_KEY_F1;
                case ae::Input::Key::Keyboard_F2: return GLFW_KEY_F2;
                case ae::Input::Key::Keyboard_F3: return GLFW_KEY_F3;
                case ae::Input::Key::Keyboard_F4: return GLFW_KEY_F4;
                case ae::Input::Key::Keyboard_F5: return GLFW_KEY_F5;
                case ae::Input::Key::Keyboard_F6: return GLFW_KEY_F6;
                case ae::Input::Key::Keyboard_F7: return GLFW_KEY_F7;
                case ae::Input::Key::Keyboard_F8: return GLFW_KEY_F8;
                case ae::Input::Key::Keyboard_F9: return GLFW_KEY_F9;
                case ae::Input::Key::Keyboard_F10: return GLFW_KEY_F10;
                case ae::Input::Key::Keyboard_F11: return GLFW_KEY_F11;
                case ae::Input::Key::Keyboard_F12: return GLFW_KEY_F12;
                case ae::Input::Key::Keyboard_F13: return GLFW_KEY_F13;
                case ae::Input::Key::Keyboard_F14: return GLFW_KEY_F14;
                case ae::Input::Key::Keyboard_F15: return GLFW_KEY_F15;
                case ae::Input::Key::Keyboard_F16: return GLFW_KEY_F16;
                case ae::Input::Key::Keyboard_F17: return GLFW_KEY_F17;
                case ae::Input::Key::Keyboard_F18: return GLFW_KEY_F18;
                case ae::Input::Key::Keyboard_F19: return GLFW_KEY_F19;
                case ae::Input::Key::Keyboard_F20: return GLFW_KEY_F20;
                case ae::Input::Key::Keyboard_F21: return GLFW_KEY_F21;
                case ae::Input::Key::Keyboard_F22: return GLFW_KEY_F22;
                case ae::Input::Key::Keyboard_F23: return GLFW_KEY_F23;
                case ae::Input::Key::Keyboard_F24: return GLFW_KEY_F24;
                case ae::Input::Key::Keyboard_F25: return GLFW_KEY_F25;

                case ae::Input::Key::Keyboard_Numpad0: return GLFW_KEY_KP_0;
                case ae::Input::Key::Keyboard_Numpad1: return GLFW_KEY_KP_1;
                case ae::Input::Key::Keyboard_Numpad2: return GLFW_KEY_KP_2;
                case ae::Input::Key::Keyboard_Numpad3: return GLFW_KEY_KP_3;
                case ae::Input::Key::Keyboard_Numpad4: return GLFW_KEY_KP_4;
                case ae::Input::Key::Keyboard_Numpad5: return GLFW_KEY_KP_5;
                case ae::Input::Key::Keyboard_Numpad6: return GLFW_KEY_KP_6;
                case ae::Input::Key::Keyboard_Numpad7: return GLFW_KEY_KP_7;
                case ae::Input::Key::Keyboard_Numpad8: return GLFW_KEY_KP_8;
                case ae::Input::Key::Keyboard_Numpad9: return GLFW_KEY_KP_9;

                case ae::Input::Key::Keyboard_Decimal: return GLFW_KEY_KP_DECIMAL;
                case ae::Input::Key::Keyboard_Divide: return GLFW_KEY_KP_DIVIDE;
                case ae::Input::Key::Keyboard_Multiply: return GLFW_KEY_KP_MULTIPLY;
                case ae::Input::Key::Keyboard_Add: return GLFW_KEY_KP_ADD;

                case ae::Input::Key::Keyboard_LeftShift: return GLFW_KEY_LEFT_SHIFT;
                case ae::Input::Key::Keyboard_LeftControl: return GLFW_KEY_LEFT_CONTROL;
                case ae::Input::Key::Keyboard_LeftAlt: return GLFW_KEY_LEFT_ALT;
                case ae::Input::Key::Keyboard_LeftSystem: return GLFW_KEY_LEFT_SUPER;

                case ae::Input::Key::Keyboard_RightShift: return GLFW_KEY_RIGHT_SHIFT;
                case ae::Input::Key::Keyboard_RightControl: return GLFW_KEY_RIGHT_CONTROL;
                case ae::Input::Key::Keyboard_RightAlt: return GLFW_KEY_RIGHT_ALT;
                case ae::Input::Key::Keyboard_Menu: return GLFW_KEY_MENU;


                case ae::Input::Key::Mouse_LeftButton: return GLFW_MOUSE_BUTTON_LEFT;
                case ae::Input::Key::Mouse_RightButton: return GLFW_MOUSE_BUTTON_RIGHT;
                case ae::Input::Key::Mouse_MiddleButton: return GLFW_MOUSE_BUTTON_MIDDLE;

                case ae::Input::Key::Mouse_X1Button: return GLFW_MOUSE_BUTTON_4;
                case ae::Input::Key::Mouse_X2Button: return GLFW_MOUSE_BUTTON_5;

                case ae::Input::Key::KeyInvalid:
                case ae::Input::Key::KeyCount:
                case ae::Input::Key::Mouse_Unknown:
                case ae::Input::Key::Keyboard_Unknown:
                case ae::Input::Key::Gamepad_Unknown:
                default:
                return GLFW_KEY_UNKNOWN;
                }
            }

            void SetMousePosition( Window& _WindowHandle, const ae::Vector2& _Position )
            {
                glfwSetCursorPos( &_WindowHandle.GetGLFWWindow(), Cast( double, _Position.X ), Cast( double, _Position.Y ) );
            }

            void HideMouse( Window& _WindowHandle )
            {
                glfwSetInputMode( &_WindowHandle.GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN );
            }
            void ShowMouse( Window& _WindowHandle )
            {
                glfwSetInputMode( &_WindowHandle.GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL );
            }
            void DisableMouse( Window& _WindowHandle )
            {
                glfwSetInputMode( &_WindowHandle.GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED );
            }
            void EnableMouse( Window& _WindowHandle )
            {
                glfwSetInputMode( &_WindowHandle.GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL );
            }

            ae::Input::Key PlatformKeyToAeroKey( const Int32& _Key )
            {
#ifdef WINDOWS
                return WinKeyToAeroKey( _Key );
#else
#pragma message (": warning : PlatformKeyToAeroKey not implemented on this platform.")
#endif
            }
            Int32 AeroKeyToPlatformKey( const ae::Input::Key& _Key )
            {
#ifdef WINDOWS
                return AeroKeyToWinKey( _Key );
#else
#pragma message (": warning : AeroKeyToPlatformKey not implemented on this platform.")
#endif
            }
            Int32 GLFWScanCodeToPlatformKey( const Int32& _ScanCode )
            {
#ifdef WINDOWS
                return ScanCodeToWinKey( _ScanCode );
#else
#pragma message (": warning : GLFWScanCodeToPlatformKey not implemented on this platform.")
#endif
            }
            void UpdatePlatformLockKeys( ae::Input::InputManager& _InputManager )
            {
#ifdef WINDOWS
                // Update caps lock state.
                SHORT LockState = GetKeyState( AeroKeyToWinKey( ae::Input::Key::Keyboard_CapsLock ) );
                _InputManager.UpdateLockKeys( ae::Input::Key::Keyboard_CapsLock, ( LockState & 0x0001 ) != 0 );

                // Update num lock state.
                LockState = GetKeyState( AeroKeyToWinKey( ae::Input::Key::Keyboard_NumLock ) );
                _InputManager.UpdateLockKeys( ae::Input::Key::Keyboard_NumLock, ( LockState & 0x0001 ) != 0 );

                // Update scroll lock state.
                LockState = GetKeyState( AeroKeyToWinKey( ae::Input::Key::Keyboard_ScrollLock ) );
                _InputManager.UpdateLockKeys( ae::Input::Key::Keyboard_ScrollLock, ( LockState & 0x0001 ) != 0 );
#else
#pragma message (": warning : UpdatePlatformLockKeys not implemented on this platform.")
#endif
            }
        } // Input

    } // priv

} // ae
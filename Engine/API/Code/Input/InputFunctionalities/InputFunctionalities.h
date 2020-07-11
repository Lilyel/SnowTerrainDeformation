#pragma once

#include "../../Toolbox/Toolbox.h"

#include "../Keys/Keys.h"
#include "../Keys/KeyState.h"

#include "../../Maths/Primitives/TRect.h"


namespace ae
{
    class Window;

    namespace Input
    {
		class InputManager;

        /// \ingroup input
		/// <summary>Determine if the given key is a keyboard key or not.</summary>
		/// <param name="_Key">Key to determine the nature.</param>
		/// <returns>True if the key is a keyboard key, False otherwise.</returns>
        AERO_CORE_EXPORT inline Bool IsKeyboardKey( const Key& _Key );

        /// \ingroup input
		/// <summary>Determine if the given key is a mouse button or not.</summary>
		/// <param name="_Key">Key to determine the nature.</param>
		/// <returns>True if the key is a mouse button, False otherwise.</returns>
        AERO_CORE_EXPORT inline Bool IsMouseKey( const Key& _Key );

        /// \ingroup input
		/// <summary>Determine if the given key is a gamepad input or not.</summary>
		/// <param name="_Key">Key to determine the nature.</param>
		/// <returns>True if the key is a gamepad input, False otherwise.</returns>
        AERO_CORE_EXPORT inline Bool IsGamepadKey( const Key& _Key );

        /// \ingroup input
		/// <summary>Retrieve the state of a key.</summary>
		/// <param name="_Key">Key to retrieve the state of.</param>
		/// <returns>State of the key.</returns>
        AERO_CORE_EXPORT inline State GetKeyState( const Key& _Key );

        /// \ingroup input
		/// <summary>Determine if the given key is pressed.</summary>
		/// <param name="_Key">Key to determine if it's pressed.</param>
		/// <returns>True if the key is in pressed state, False otherwise.</returns>
        AERO_CORE_EXPORT inline Bool IsKeyPressed( const Key& _Key );

        /// \ingroup input
		/// <summary>Determine if the given key is down.</summary>
		/// <param name="_Key">Key to determine if it's down.</param>
		/// <returns>True if the key is in down state, False otherwise.</returns>
        AERO_CORE_EXPORT inline Bool IsKeyDown( const Key& _Key );

        /// \ingroup input
		/// <summary>Determine if the given key is released.</summary>
		/// <param name="_Key">Key to determine if it's released.</param>
		/// <returns>True if the key is in released state, False otherwise.</returns>
        AERO_CORE_EXPORT inline Bool IsKeyReleased( const Key& _Key );

        /// \ingroup input
		/// <summary>Determine if the given key is up.</summary>
		/// <param name="_Key">Key to determine if it's up.</param>
		/// <returns>True if the key is in up state, False otherwise.</returns>
        AERO_CORE_EXPORT inline Bool IsKeyUp( const Key& _Key );

        /// \ingroup input
		/// <summary>Determine if the given key is valid. ( If it's known. )</summary>
		/// <param name="_Key">Key to determine if it's known.</param>
		/// <returns>True if the key is in known, False otherwise.</returns>
        AERO_CORE_EXPORT inline Bool IsKeyValid( const Key& _Key );

        /// \ingroup input
		/// <summary>Determine if the according to possible combinaison, caps are active.</summary>
		/// <returns>True if the caps are active, False otherwise.</returns>
        AERO_CORE_EXPORT inline Bool IsCaps();

        /// \ingroup input
		/// <summary>Determine if a keyboard key was hit this frame.</summary>
		/// <returns>True if the a key was hit, False otherwise.</returns>
        AERO_CORE_EXPORT inline Bool IsKeyboardHit();

        /// \ingroup input
		/// <summary>Determine if a mouse button was hit this frame.</summary>
		/// <returns>True if the a button was hit, False otherwise.</returns>
        AERO_CORE_EXPORT inline Bool IsMouseHit();

        /// \ingroup input
		/// <summary>Determine if a gamepad button was hit this frame.</summary>
		/// <returns>True if the a button was hit, False otherwise.</returns>
        AERO_CORE_EXPORT inline Bool IsGamepadHit();

        /// \ingroup input
		/// <summary>
		/// Position of the mouse cursor in application area.<para/>
		/// (0, 0) is the top left corner of the application.
		/// </summary>
		/// <returns>Mouse position in the application area.</returns>
        AERO_CORE_EXPORT inline const Vector2& GetMousePosition();

        /// \ingroup input
		/// <summary>
		/// The difference of position of the mouse between this frame and the current one.<para/>
		/// (0, 0) is the top left corner of the application.
		/// </summary>
		/// <returns>The movement of the mouse between the previous frame and the current one.</returns>
        AERO_CORE_EXPORT inline const Vector2& GetMouseDeltaMove();

		/// \ingroup input
		/// <summary>Get the delta scroll (wheel) from the last frame.</summary>
		/// <returns>The mouse delta scroll from the last frame.</returns>
		AERO_CORE_EXPORT inline const Int16 GetMouseDeltaWheel();

		/// \ingroup input
		/// <summary>Clip the cursor into an area in the application.</summary>
		/// <param name="_Window">Window to clip the mouse in.</param>
		/// <param name="_ClipArea">Area to clip the cursor (application coordinates).</param>
        AERO_CORE_EXPORT inline void ClipMouse( const Window& _Window, const FloatRect& _ClipArea );

		/// \ingroup input
		/// <summary>Clip the cursor into an area in the application.</summary>
		/// <param name="_Window">Window to clip the mouse in.</param>
        AERO_CORE_EXPORT inline void ClipMouseToWindow( const Window& _Window );

		/// \ingroup input
		/// <summary>Stop clipping the mouse.</summary>
        AERO_CORE_EXPORT inline void ClipMouseStop();

		/// \ingroup input
		/// <summary>Set the mouse position.</summary>
		/// <param name="_Window">Window to move the mouse in.</param>
		/// <param name="_Position">New position to move the cursor.</param>
        AERO_CORE_EXPORT inline void SetMousePosition( const Window& _Window, const ae::Vector2& _Position );

    } // Input


    namespace priv
    {
        namespace Input
        {
            /// <summary>Convert a windows key value (low level input) to Aero input (ae::Input::Key).</summary>
            /// <param name="_WinKey">Low level input value to convert.</param>
            /// <returns>Low level input value converted to Aero input.</returns>
            AERO_CORE_EXPORT ae::Input::Key GLFWKeyToAeroKey( const Int32& _GLFWKey );

            /// <summary>Convert Aero input value to windows input value (low level input).</summary>
            /// <param name="_Key">Aero input value to convert.</param>
            /// <returns>Aero input value convert as windows input value (low level input).</returns>
            AERO_CORE_EXPORT Int32 AeroKeyToGLFWKey( const ae::Input::Key& _Key );



            /// <summary>Set the mouse position.</summary>
            /// <param name="_WindowHandle">Low level handle on the window to move the cursor in.</param>
            /// <param name="_Position">New position to move the cursor.</param>
            AERO_CORE_EXPORT inline void SetMousePosition( Window& _WindowHandle, const ae::Vector2& _Position );

            /// <summary>Hide the mouse cursor when it is in the window area.</summary>
            /// <param name="_WindowHandle">Low level handle on the window to hide the cursor in.</param>
            AERO_CORE_EXPORT inline void HideMouse( Window& _WindowHandle );

            /// <summary>Show the mouse cursor when it is in the window area.</summary>
            /// <param name="_WindowHandle">Low level handle on the window to show the cursor in.</param>
            AERO_CORE_EXPORT inline void ShowMouse( Window& _WindowHandle );

            /// <summary>Disable the mouse cursor when it is in the window area.</summary>
            /// <param name="_WindowHandle">Low level handle on the window to disable the cursor in.</param>
            AERO_CORE_EXPORT inline void DisableMouse( Window& _WindowHandle );

            /// <summary>Enable the mouse cursor when it is in the window area.</summary>
            /// <param name="_WindowHandle">Low level handle on the window to enable the cursor in.</param>
            AERO_CORE_EXPORT inline void EnableMouse( Window& _WindowHandle );

            /// <summary>Convert a platform key value (low level input) to Aero input (ae::Input::Key).</summary>
            /// <param name="_Key">Low level input value to convert.</param>
            /// <returns>Low level input value converted to Aero input.</returns>
            AERO_CORE_EXPORT ae::Input::Key PlatformKeyToAeroKey( const Int32& _Key );

            /// <summary>Convert Aero input value to platform input value (low level input).</summary>
            /// <param name="_Key">Aero input value to convert.</param>
            /// <returns>Aero input value convert as windows input value (low level input).</returns>
            AERO_CORE_EXPORT Int32 AeroKeyToPlatformKey( const ae::Input::Key& _Key );

            /// <summary>Convert scan code (physical key code) to virtual key (layout aware code).</summary>
            /// <param name="_ScanCode">Scan code to convert</param>
            /// <returns>Converted key (PlatformKey)</returns>
            AERO_CORE_EXPORT Int32 GLFWScanCodeToPlatformKey( const Int32& _ScanCode );

            /// <summary>
            /// Update input manger lock bits for "Caps", "NumVerr" and "Scroll".
            /// </summary>
            /// <param name="_InputManager">Input manager to update.</param>
            AERO_CORE_EXPORT void UpdatePlatformLockKeys( ae::Input::InputManager& _InputManager );

        } // Input
    } // priv

} // ae


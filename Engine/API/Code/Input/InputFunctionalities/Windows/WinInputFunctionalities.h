#pragma once

// https://msdn.microsoft.com/fr-fr/library/windows/desktop/ms645530(v=vs.85).aspx

#include "../../../Toolbox/Toolbox.h"

#include "../../Keys/Keys.h"
#include "../../Keys/KeyState.h"

#include "../../../Maths/Vector/Vector2.h"
#include "../../../Maths/Primitives/TRect.h"

#include <Windows.h>

struct GLFWwindow;

namespace ae
{
    class Window;

    namespace priv
    {
        namespace Input
        {
			/// <summary>Convert a windows key value (low level input) to Aero input (ae::Input::Key).</summary>
			/// <param name="_WinKey">Low level input value to convert.</param>
			/// <returns>Low level input value converted to Aero input.</returns>
            AERO_CORE_EXPORT ae::Input::Key WinKeyToAeroKey( const Int32& _WinKey );

			/// <summary>Convert Aero input value to windows input value (low level input).</summary>
			/// <param name="_Key">Aero input value to convert.</param>
			/// <returns>Aero input value convert as windows input value (low level input).</returns>
            AERO_CORE_EXPORT Int32 AeroKeyToWinKey( const ae::Input::Key& _Key );

			/// <summary>Clip the cursor to an client space area.</summary>
			/// <param name="_WindowHandle">Low level handle on the window to clip the cursor in.</param>
			/// <param name="_ClipArea">Area to clip the cursor (application coordinates).</param>
            AERO_CORE_EXPORT inline void ClipMouse( const HWND& _WindowHandle, const FloatRect& _ClipArea );

			/// <summary>Stop clipping the mouse.</summary>
            AERO_CORE_EXPORT inline void ClipMouseStop();


            /// <summary>Convert scan code (physical key code) to virtual key (layout aware code).</summary>
            /// <param name="_ScanCode">Scan code to convert</param>
            /// <returns>Converted key (WinKey)</returns>
            AERO_CORE_EXPORT inline Int32 ScanCodeToWinKey( const Int32& _ScanCode );


            /// <summary>Retrieve the native window handle from GLFW window/</summary>
            /// <param name="_GLFWWindow">GLFW window to retrieve the native handle from.</param>
            /// <returns>Native window handle.</returns>
            AERO_CORE_EXPORT inline HWND GetNativeWinHandleFromGLFW( GLFWwindow* _GLFWWindow );

        } // Input
    } // priv 
} // ae


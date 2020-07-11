#pragma once

#include "../Toolbox/Toolbox.h"

#include <string>

////////////////////////////////////////////////////////////
/// \defgroup ui User Interface
///
/// User interface fonctionalities (link with ImGui).
/// 
////////////////////////////////////////////////////////////


namespace ae
{
    class Window;
    class Camera;

    /// \ingroup ui
    namespace UI
    {
        /// <summary>Retrieve the clipboard content from GLFW.</summary>
        /// <param name="_UserDara">User data to fill with clipboard data.</param>
        /// <returns>Clipboard content.</returns>
        AERO_CORE_EXPORT const char* GetClipboardData( void* _UserData );

        /// <summary>Set the clipboard content.</summary>
        /// <param name="_UserDara">New user data to put in the clipboard.</param>
        /// <param name="_Text">Text to put in the clipboard.</param>
        AERO_CORE_EXPORT void SetClipboardData( void* _UserData, const char* _Text );

        /// <summary>Initialize ImGUI.</summary>
        /// <param name="_Window">Window to initialize ImGui inside.</param>
        AERO_CORE_EXPORT void InitImGUI( Window& _Window );

        /// <summary>Deinitialize ImGUI.</summary>
        AERO_CORE_EXPORT void DeinitImGUI();

   

        /// <summary>Begin a ImGui frame.</summary>
        AERO_CORE_EXPORT void NewFrame();

        /// <summary>Render the current ImGui frame to the <paramref name="_Window"/>.</summary>
        /// <param name="_Window">The window to render the ImGui frame to.</param>
        AERO_CORE_EXPORT void RenderFrame();

        /// <summary>Begin a dockspace that fit the whole viewport.</summary>
        AERO_CORE_EXPORT void BeginEditorDock();

        /// <summary>Begin the dockspace beginned by <see cref="BeginEditorDock()"/>.</summary>
        AERO_CORE_EXPORT void EndEditorDock();


    } // UI
}

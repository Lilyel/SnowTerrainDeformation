#pragma once

#include "../../Toolbox/Toolbox.h"

#include "../Context/Context.h"
#include "../Renderer/Renderer.h"

#include "../../TimeManagement/Time/Time.h"

#include "../../Maths/Primitives/TRect.h"
#include "../../Maths/Vector/Vector2.h"


#include <string>
#include <memory>

struct GLFWwindow;

namespace ae
{
    /// \ingroup graphics
    /// <summary>
    /// Style applied to the window.
    /// Deternime which buttons it will have and if it will be resizable.
    /// </summary>
    enum class WindowStyle : Uint8
    {
        /// <summary>Window will be resizable.</summary>
        Resizable = 1,

        /// <summary>Window will have borders and close buttons.</summary>
        Decorated = 2,

        /// <summary>Window will be maximized at creation.</summary>
        Maximized = 4,

        /// <summary>Default window decorated and resizable.</summary>
        Default = Resizable | Decorated,

        /// <summary>Window will have nothing.</summary>
        None = 0,
    };


    /// \ingroup graphics
    /// <summary>
    /// Settings of a new window. <para/>
    /// It contains all informations required for window creation.
    /// </summary>
    class AERO_CORE_EXPORT WindowSettings
    {
    public:
        /// <summary>Default constructor.</summary>
        WindowSettings() :
            Width( 960 ),
            Height( 720 ),
            X( 50 ),
            Y( 50 ),
            Name( "DefaultWindowName" ),
            Options( WindowStyle::Default ),
            AntiAliasing( 0 ),
            FrameRate( 60 ),
            VSync( True ),
            IsDPIAware( True )
        {
        }


        /// <summary>Window width.</summary>
        Uint32 Width;

        /// <summary>Window height.</summary>
        Uint32 Height;

        /// <summary>Window position X.</summary>
        Int32 X;

        /// <summary>Window position Y.</summary>
        Int32 Y;

        /// <summary>Window name ( in toolbar and taskbar ).</summary>
        std::string Name;

        /// <summary>Window style and options ( close, resize, border, etc ).</summary>
        WindowStyle Options;

        /// <summary>Antialiasing level. 0 disable.</summary>
        Uint8 AntiAliasing;

        /// <summary>Window frame rate. 0 to ignore it.</summary>
        Uint32 FrameRate;

        /// <summary>Synchronize the framerate with the monitor refresh frequence ?</summary>
        Bool VSync;

        /// <summary>Window and UI must be scaled according to the monitor DPI ?</summary>
        Bool IsDPIAware;
    };

    /// \ingroup graphics
    /// <summary>
    /// Window management (size, style, ...)
    /// The OpenGL rendering will be show on it.
    /// Catch user interactions.
    /// </summary>
    class AERO_CORE_EXPORT Window : public Renderer
    {
    public:


        /// <summary>Default constructor.</summary>
        Window();
        /// <summary> Destructor.</summary>
        ~Window();
		   

        /// <summary>Create a window (render target).</summary>
        /// <param name="_Settings">Settings to apply to the window when creating it.</param>
        void Create( const WindowSettings& _Settings = WindowSettings() );
      

        /// <summary>Destroy created window.</summary>
        void Destroy();


        /// <summary>Return True if window is open, false otherwise.</summary>
        /// <returns>True if open, false if not.</returns>
        Bool IsOpen();


        /// <summary>
        /// Push the openGL buffer to the screen
        /// Then process frame rate.
        /// </summary>
        void Render() override;

        
        /// <summary>Change the title of the window.</summary>
        /// <param name="_Title">New window title.</param>
        void SetWindowTitle( const std::string& _Title );
        

        /// <summary>Retrieve the window title.</summary>
        /// <returns>Window title.</returns>
        const std::string& GetWindowTitle() const;

        
        /// <summary>Set frame rate limit.</summary>
        /// <param name="_FrameRate">Target frame rate.</param>
        void SetFrameRate( Int8 _FrameRate );
        

        /// <summary>Retrieve frame rate target. ( User setting ).</summary>
        /// <returns>Current target frame rate.</returns>
        Uint32 GetFrameRate() const;
        
        /// <summary>Get the real frame rate based on frame delta time.</summary>
        /// <returns>Frame rate based on delta time.</returns>
        Uint32 GetRealFrameRate() const;

        /// <summary>Get the last frame time.</summary>
        /// <returns>The last frame time.</returns>
        Time GetFrameTime() const;

        /// <summary>Get the last frame time (computation time without the sleep).</summary>
        /// <returns>The last frame time.</returns>
        const Time& GetFrameComputeTime() const;
        
        /// <summary>Retrieve window height.</summary>
        /// <returns>Window height.</returns>
        Uint32 GetHeight() const override;
        
        /// <summary>Retrieve window width.</summary>
        /// <returns>Window width.</returns>
        Uint32 GetWidth() const override;


        /// <summary>Get window rectangle area.</summary>
        /// <returns>Window area.</returns>
        FloatRect GetWindowRect() const;


        /// <summary>Convert a screen position to a position relative to the window.</summary>
        /// <param name="_Position">Position to convert.</param>
        /// <returns>Position converted.</returns>
        Vector2 ScreenToWindowCoordinates( const Vector2& _Position ) const;
        

        /// <summary>Convert a position in the window to screen coordinates.</summary>
        /// <param name="_Position">Position to convert.</param>
        /// <returns>Position converted.</returns>
        Vector2 WindowToScreenCoordinates( const Vector2& _Position ) const;


        /// <summary>Gets the rendering context of the window.</summary>
        /// <returns>The window context.</returns>
        const Context& GetContext() const;


        /// <summary>Determines whether this window has focus on messages and keyboard strokes.</summary>
        /// <returns>True if the window has the focus, False otherwise.</returns>
        Bool HasFocus() const;

        /// <summary>
        /// Retrieve the focus from operating system.
        /// The focus is not imediatly retrieved, you must check after witth HasFocus.
        /// </summary>
        void RequestFocus() const;

        /// <summary>Retrieve the GLFW window.</summary>
        /// <returns>GLFW window.</returns>
        const GLFWwindow& GetGLFWWindow() const;

        /// <summary>Retrieve the GLFW window.</summary>
        /// <returns>GLFW window.</returns>
        GLFWwindow& GetGLFWWindow();

        /// <summary>Process event received by the window, and update inputs.</summary>
        void WindowIteration();

        /// <summary>Get the scale to apply according the monitor DPI.</summary>
        /// <returns>The scale according to the monitor DPI.</returns>
        float GetDPIScale() const;

		/// <summary>Is the window is resizable ?</summary>
		/// <returns>True if resizable, False otherwise.</returns>
		Bool IsResizable() const;

		/// <summary>Is the window is decorated ?</summary>
		/// <returns>True if decorated, False otherwise.</returns>
		Bool IsDecorated() const;

		/// <summary>Is the window is maximized at its creation ?</summary>
		/// <returns>True if maximized at creation, False otherwise.</returns>
		Bool IsMaximizedAtCreation() const;

        /// <summary>Is the framerate is syncrhonized with the monitor refresh frequence ?</summary>
        /// <returns>True if the VSync is active, False otherwise.</returns>
        Bool IsVSyncActive() const;

        /// <summary>Should the framerate be syncrhonized with the monitor refresh frequence ? </summary>
        /// <param name="_ActivateVSync">True to activate the VSync, False to disable it.</param>
        void SetVSync( Bool _ActivateVSync );
        
        /// <summary>Is the application scale the window and the UI according the monitor DPI ?</summary>
        /// <returns>True if the scale is applied, false otherwise.</returns>
        Bool IsDPIAware() const;

    private:
        /// <summary> GLFW callback when a key is pressed or released.</summary>
        /// <param name="_Window">GLFW window receiving the input.</param>
        /// <param name="_Key">_Key concerned by the event.</param>
        /// <param name="_Scancode">Scan code of the key.</param>
        /// <param name="_Action">Action done to the key.</param>
        /// <param name="_Mods">Combined key (shift, alt, ...).</param>
        static void OnKeyEvent( GLFWwindow* _Window, Int32 _Key, Int32 _Scancode, Int32 _Action, Int32 _Mods );
        
        /// <summary>GLFW event when a character is entered.</summary>
        /// <param name="window">GLFW window receiving the input.</param>
        /// <param name="_Codepoint">Code of the character.</param>
        static void OnKeyCharEvent( GLFWwindow* window, Uint32 _Codepoint );

        /// <summary>GLFW callback when a mouse button is pressed or released.</summary>
        /// <param name="_Window">GLFW window receiving the input.</param>
        /// <param name="_Button">Mouse button concerned.</param>
        /// <param name="_Action">Action done to the key.</param>
        /// <param name="_Mods">Combined key (shift, alt, ...).</param>
        static void OnMouseButtonEvent( GLFWwindow* _Window, Int32 _Button, Int32 _Action, Int32 _Mods );

        /// <summary>GLFW callback when a mouse is moved.</summary>
        /// <param name="_Window">GLFW window receiving the input.</param>
        /// <param name="_PositionX">The new position X of the mouse.</param>
        /// <param name="_PositionY">The new position Y of the mouse.</param>
        static void OnMouseMoveEvent( GLFWwindow* _Window, double _PositionX, double _PositionY );

        /// <summary>GLFW callback when the mouse wheel is used.</summary>
        /// <param name="_Window">GLFW window receiving the input.</param>
        /// <param name="_DeltaX">The delta on X axis of the wheel since the last callback.</param>
        /// <param name="_DeltaY">The delta on Y axis of the wheel since the last callback.</param>
        static void OnMouseWheelEvent( GLFWwindow* _Window, double _DeltaX, double _DeltaY );

        /// <summary>GLFW callback when the window size is changed.</summary>
        /// <param name="_Window">GLFW window resized.</param>
        /// <param name="_Width">New width of the window.</param>
        /// <param name="_Height">New height of the window.</param>
        static void OnWindowSizeChangedEvent( GLFWwindow* _Window, Int32 _Width, Int32 _Height );

        /// <summary>GLFW callback when the window is moved.</summary>
        /// <param name="_Window">GLFW window moved.</param>
        /// <param name="_PositionX">The new position on X axis of the window.</param>
        /// <param name="_PositionY">The new position on Y axis of the window.</param>
        static void OnWindowMoveEvent( GLFWwindow* _Window, Int32 _PositionX, Int32 _PositionY );

        /// <summary>GLFW callback when the focus of the window changed.</summary>
        /// <param name="_Window">GLFW window losing or winning focus.</param>
        /// <param name="_IsFocus">True if <paramref name="_Window"/> is focus, false otherwise.</param>
        static void OnFocusChangedEvent( GLFWwindow* _Window, Int32 _IsFocus );

        /// <summary>GLFW callback when the window is closed.</summary>
        /// <param name="_Window">GLFW window closed.</param>
        static void OnCloseEvent( GLFWwindow* _Window );

        /// <summary>Process the scale according the monitor DPI.</summary>
        void ProcessDPIScale();

    protected:
        
        /// <summary>Init context for opengl rendering.</summary>
        void InitContext();

        /// <summary>
        /// Limit the framerate to the user setting.<para/>
        /// Also fill engine DeltaTime value.
        /// </summary>
        void ProcessFrameRate();

        /// <summary>Update the computation time of the frame (without VSync / Sleep ).</summary>
        void UpdateFrameTime();

    protected:

        /// <summary>Handle on GLFW window.</summary>
        GLFWwindow* m_GLFWWindow;

        /// <summary>If windows is in a valid state.</summary>
        Bool m_IsOpen;

        /// <summary>OpenGL context.</summary>
        Context m_Context;

        /// <summary>User info.</summary>
        WindowSettings m_WindowUserInfo;
        
        /// <summary>
        /// Time marker set a the end of each frame.
        /// Used for process framerate and delta time.
        /// </summary>
        Time m_EndLastFrameTime;

        /// <summary>Elapsed time between the end of the last frame and the current frame before the sleep.</summary>
        Time m_FrameComputeTime;

        /// <summary>Determine if the window has the focus on messages and keyboard strokes.</summary>
        Bool m_HasFocus;

        /// <summary>Scale to do according to the monitor DPI.</summary>
        float m_DPIScale;
    };
}


/// <summary>
/// '|' Operator for WindowStyle enum fields.<para/>
/// That allow to do ae::WindowStyle | ae::WindowStyle without casts.<para/>
/// The enum values will cast to Int64 to do the operation.
/// </summary>
/// <param name="_A">First WindowStyle.</param>
/// <param name="_B">Seoncd WindowStyle.</param>
/// <returns>The result of the operator '|' between the two parameter..</returns>
AERO_CORE_EXPORT ae::WindowStyle operator|( ae::WindowStyle _A, ae::WindowStyle _B );


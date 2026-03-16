#include "Window.h"

#include "../../Aero/Aero.h"

#include "../Context/Context.h"
#include "../../Maths/Vector/Vector2.h"
#include "../../Toolbox/BitOperations/BitOperations.h"

#include "../../Input/Input.h"

#include "../Image/Image.h"

#include "../../Debugging/Debugging.h"


#include "../Dependencies/OpenGL.h"
#include "../Dependencies/GLFW.h"

#include "../../Input/InputFunctionalities/InputFunctionalities.h"

#include <thread>
#include <chrono>

namespace ae
{
	Window::Window()
	{
		m_GLFWWindow = nullptr;
		m_IsOpen = False;
		m_HasFocus = False;
		m_DPIScale = 1.0f;
	}
	Window::~Window()
	{
	}

	void Window::Create( const WindowSettings& _Settings )
	{
		// Retrieve monitor DPI scaling.
		ProcessDPIScale();

		// Fill user info
		m_WindowUserInfo = _Settings;
		m_WindowUserInfo.Height = Cast( Uint32, Cast( float, _Settings.Height ) * GetDPIScale() );
		m_WindowUserInfo.Width = Cast( Uint32, Cast( float, _Settings.Width ) * GetDPIScale() );

		// Create window.

		glfwWindowHint( GLFW_SAMPLES, m_WindowUserInfo.AntiAliasing );
		glfwWindowHint( GLFW_DOUBLEBUFFER, GLFW_TRUE );
		glfwWindowHint( GLFW_RESIZABLE, IsResizable() ? GLFW_TRUE : GLFW_FALSE );
		glfwWindowHint( GLFW_MAXIMIZED, IsMaximizedAtCreation() ? GLFW_TRUE : GLFW_FALSE );
		glfwWindowHint( GLFW_DECORATED, IsDecorated() ? GLFW_TRUE : GLFW_FALSE );
		glfwWindowHint( GLFW_SCALE_TO_MONITOR, GLFW_TRUE );

		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 5 );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

		m_GLFWWindow = glfwCreateWindow( Cast( int, m_WindowUserInfo.Width ),
										 Cast( int, m_WindowUserInfo.Height ),
										 m_WindowUserInfo.Name.c_str(),
										 nullptr, nullptr );
		if( m_GLFWWindow == nullptr )
		{
			AE_LogError( "Failed to create GLFW Window." );
			return;
		}

		glfwSetWindowPos( m_GLFWWindow, m_WindowUserInfo.X, m_WindowUserInfo.Y );

		// Setup window events callbacks.
		glfwSetWindowUserPointer( m_GLFWWindow, this );
		glfwSetKeyCallback( m_GLFWWindow, Window::OnKeyEvent );
		glfwSetCharCallback( m_GLFWWindow, Window::OnKeyCharEvent );
		glfwSetMouseButtonCallback( m_GLFWWindow, Window::OnMouseButtonEvent );
		glfwSetScrollCallback( m_GLFWWindow, Window::OnMouseWheelEvent );
		glfwSetCursorPosCallback( m_GLFWWindow, Window::OnMouseMoveEvent );
		glfwSetWindowFocusCallback( m_GLFWWindow, Window::OnFocusChangedEvent );
		glfwSetFramebufferSizeCallback( m_GLFWWindow, Window::OnWindowSizeChangedEvent );
		glfwSetWindowPosCallback( m_GLFWWindow, Window::OnWindowMoveEvent );
		glfwSetWindowCloseCallback( m_GLFWWindow, Window::OnCloseEvent );

		InitContext();

		SetVSync( m_WindowUserInfo.VSync );

		Aero.SetWindow( this );
		m_IsOpen = True;

		// Init glew after created opengl context.
		glewExperimental = GL_TRUE;
		glewInit();

		// After opengl and glew init, create our rendering target.
		InitializeRendering();

		m_EndLastFrameTime = Time::GetTick();
	}
	void Window::Destroy()
	{
		FreeResource();

		m_IsOpen = False;

		m_WindowUserInfo.Height = 0;
		m_WindowUserInfo.Width = 0;
		m_WindowUserInfo.X = 0;
		m_WindowUserInfo.Y = 0;
		m_WindowUserInfo.Options = WindowStyle::Default;

		glfwDestroyWindow( m_GLFWWindow );
	}

	FloatRect Window::GetWindowRect() const
	{
		int WindowArea[4];

		glfwGetWindowFrameSize( m_GLFWWindow, &WindowArea[0], &WindowArea[1], &WindowArea[2], &WindowArea[3] );

		return FloatRect( Cast( float, WindowArea[0] ),
						  Cast( float, WindowArea[1] ),
						  Cast( float, WindowArea[2] ),
						  Cast( float, WindowArea[3] ) );
	}

	void Window::SetWindowIcon( const Image& _Icon )
	{
		if( _Icon.GetChannelsCount() != 4 )
		{
			AE_LogError( "Icon is not RGBA. It will not be applied" );
			return;
		}

		GLFWimage GLFWIcon;
		GLFWIcon.width = Cast( Int32, _Icon.GetWidth() );
		GLFWIcon.height = Cast( Int32, _Icon.GetHeight() );
		
		Uint32 MemorySize = _Icon.GetWidth() * _Icon.GetHeight() * _Icon.GetChannelsCount();
		GLFWIcon.pixels = new Uint8[MemorySize];
		std::memcpy( GLFWIcon.pixels, _Icon.GetData(), MemorySize * sizeof( Uint8 ) );

		glfwSetWindowIcon( m_GLFWWindow, 1, &GLFWIcon );

		delete[] GLFWIcon.pixels;
	}

	Vector2 Window::ScreenToWindowCoordinates( const Vector2& _Position ) const
	{
		int windowPosition[2];
		glfwGetWindowPos( m_GLFWWindow, &windowPosition[0], &windowPosition[1] );

		return Vector2( _Position.X + Cast( float, windowPosition[0] ), _Position.Y + Cast( float, windowPosition[1] ) );
	}

	Vector2 Window::WindowToScreenCoordinates( const Vector2& _Position ) const
	{
		int windowPosition[2];
		glfwGetWindowPos( m_GLFWWindow, &windowPosition[0], &windowPosition[1] );

		return Vector2( _Position.X - Cast( float, windowPosition[0] ), _Position.Y - Cast( float, windowPosition[1] ) );
	}

	const Context& Window::GetContext() const
	{
		if( m_GLFWWindow == nullptr )
			AE_LogError( "Invalid context. Context available only when a window is correctly created." );

		return m_Context;
	}

	Bool Window::HasFocus() const
	{
		return m_HasFocus;
	}

	void Window::RequestFocus() const
	{
		glfwRequestWindowAttention( m_GLFWWindow );
	}

	void Window::Iconify() const
	{
		glfwIconifyWindow( m_GLFWWindow );
	}

	void Window::Maximize() const
	{
		glfwMaximizeWindow( m_GLFWWindow );
	}

	void Window::Restore() const
	{
		glfwRestoreWindow( m_GLFWWindow );
	}

	const GLFWwindow& Window::GetGLFWWindow() const
	{
		return *m_GLFWWindow;
	}

	GLFWwindow& Window::GetGLFWWindow()
	{
		return *m_GLFWWindow;
	}



	float Window::GetDPIScale() const
	{
		return m_DPIScale;
	}

	Bool Window::IsResizable() const
	{
		return BitOp::BitOpAnd<WindowStyle, Uint8>( m_WindowUserInfo.Options, WindowStyle::Resizable );
	}

	Bool Window::IsDecorated() const
	{
		return BitOp::BitOpAnd<WindowStyle, Uint8>( m_WindowUserInfo.Options, WindowStyle::Decorated );
	}

	Bool Window::IsMaximizedAtCreation() const
	{
		return BitOp::BitOpAnd<WindowStyle, Uint8>( m_WindowUserInfo.Options, WindowStyle::Maximized );
	}

	Bool Window::IsVSyncActive() const
	{
		return m_WindowUserInfo.VSync;
	}

	void Window::SetVSync( Bool _ActivateVSync )
	{
		m_WindowUserInfo.VSync = _ActivateVSync;
		glfwSwapInterval( _ActivateVSync ? 1 : 0 );
	}

	void Window::OnKeyEvent( GLFWwindow*, Int32, Int32 _ScanCodes, Int32 _Action, Int32 )
	{
		Int32 WinKey = priv::Input::GLFWScanCodeToPlatformKey( _ScanCodes );
		const Input::Key KeyButton = priv::Input::PlatformKeyToAeroKey( WinKey );


		Input::State KeyState = Input::State::StateInvalid;
		if( _Action == GLFW_PRESS )
			KeyState = Input::State::Pressed;
		else if( _Action == GLFW_RELEASE )
			KeyState = Input::State::Released;
		else
			return;

		Input::InputManager& InputManagerInstance = Aero.GetInputManger();

		InputManagerInstance.HandleKeyEvent( KeyButton, KeyState );
	}

	void Window::OnKeyCharEvent( GLFWwindow*, Uint32 )
	{
#pragma message (": warning : OnKeyCharEvent not implemented.")
	}

	void Window::OnMouseButtonEvent( GLFWwindow*, Int32 _Button, Int32 _Action, Int32 )
	{
		const Input::Key MouseButton = priv::Input::GLFWKeyToAeroKey( _Button );


		Input::State MouseState = Input::State::StateInvalid;
		if( _Action == GLFW_PRESS )
			MouseState = Input::State::Pressed;
		else if( _Action == GLFW_RELEASE )
			MouseState = Input::State::Released;
		else
			return;

		Input::InputManager& InputManagerInstance = Aero.GetInputManger();

		InputManagerInstance.HandleKeyEvent( MouseButton, MouseState );
	}

	void Window::OnMouseMoveEvent( GLFWwindow*, double _PositionX, double _PositionY )
	{
		Input::InputManager& InputManagerInstance = Aero.GetInputManger();

		InputManagerInstance.UpdateMousePosition( ae::Vector2( Cast( float, _PositionX ), Cast( float, _PositionY ) ) );
	}

	void Window::OnMouseWheelEvent( GLFWwindow*, double, double _DeltaY )
	{
		Input::InputManager& InputManagerInstance = Aero.GetInputManger();

		InputManagerInstance.UpdateMouseDeltaWheel( Cast( Int16, _DeltaY ) );
	}

	void Window::OnWindowSizeChangedEvent( GLFWwindow* _Window, Int32 _Width, Int32 _Height )
	{
		Window* ThisWindow = Cast( Window*, glfwGetWindowUserPointer( _Window ) );

		// Prevent 0x0 framebuffers (happens when minimizing window).
		_Width = Math::Max( _Width, 1 );
		_Height = Math::Max( _Height, 1 );

		ThisWindow->m_WindowUserInfo.Height = Cast( Uint32, _Height );
		ThisWindow->m_WindowUserInfo.Width = Cast( Uint32, _Width );
	}

	void Window::OnWindowMoveEvent( GLFWwindow* _Window, Int32 _PositionX, Int32 _PositionY )
	{
		Window* ThisWindow = Cast( Window*, glfwGetWindowUserPointer( _Window ) );

		ThisWindow->m_WindowUserInfo.X = _PositionX;
		ThisWindow->m_WindowUserInfo.Y = _PositionY;
	}

	void Window::OnFocusChangedEvent( GLFWwindow* _Window, Int32 _IsFocus )
	{
		Window* ThisWindow = Cast( Window*, glfwGetWindowUserPointer( _Window ) );
		if( ThisWindow == nullptr )
			return;

		ThisWindow->m_HasFocus = _IsFocus != 0;
	}


	void Window::OnCloseEvent( GLFWwindow* _Window )
	{
		Window* ThisWindow = Cast( Window*, glfwGetWindowUserPointer( _Window ) );
		if( ThisWindow == nullptr )
			return;

		ThisWindow->m_IsOpen = False;
	}



	void Window::WindowIteration()
	{
		ProcessFrameRate();

		glfwPollEvents();
	}
	Bool Window::IsOpen()
	{
		return m_IsOpen;
	}


	/// RENDERING
	void Window::Render()
	{
		Renderer::Render();

		// Update frame time before swapping to avoid VSync.
		UpdateFrameTime();


		m_Context.SwapDeviceBuffers();
	}

	/// UTILITIES

	void Window::InitContext()
	{
		m_Context.Init( m_GLFWWindow );
	}

	void Window::ProcessFrameRate()
	{
		Time CurrentTime = Time::GetTick();
		Int64 DeltaMicro = CurrentTime.AsMicroSeconds() - m_EndLastFrameTime.AsMicroSeconds();
		float Delta = Cast( float, DeltaMicro ) / 1000000.0f;

		if( m_WindowUserInfo.FrameRate > 0 && !m_WindowUserInfo.VSync )
		{
			const float TargetDelta = 1.0f / Cast( float, m_WindowUserInfo.FrameRate );
			const float SleepTime = ( TargetDelta - Delta );

			// If loop is longer than a normal loop, we are late, so do not sleep.
			if( SleepTime > 0.0f )
			{
				const std::chrono::duration<float> stdSleepTime( SleepTime );
				std::this_thread::sleep_for( stdSleepTime );

				CurrentTime = Time::GetTick();
				DeltaMicro = CurrentTime.AsMicroSeconds() - m_EndLastFrameTime.AsMicroSeconds();
			}
		}

		Aero.m_DeltaTime = Cast( float, DeltaMicro ) / 1000000.0f;
		m_EndLastFrameTime = CurrentTime;
	}

	void Window::UpdateFrameTime()
	{
		Time Now = Time::GetTick();
		m_FrameComputeTime = Time::MicroSeconds( Now.AsMicroSeconds() - m_EndLastFrameTime.AsMicroSeconds() );
	}

	void Window::ProcessDPIScale()
	{
		if( !m_WindowUserInfo.IsDPIAware )
			return;

		GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor();
		if( PrimaryMonitor == nullptr )
			return;

		const GLFWvidmode* VideoMode = glfwGetVideoMode( PrimaryMonitor );
		if( VideoMode == nullptr )
			return;

		float ScaleX;
		float ScaleY;
		glfwGetMonitorContentScale( PrimaryMonitor, &ScaleX, &ScaleY );

		m_DPIScale = Math::Max( ScaleX, ScaleY );
	}

	void Window::SetWindowTitle( const std::string& _Title )
	{
		glfwSetWindowTitle( m_GLFWWindow, _Title.c_str() );

		m_WindowUserInfo.Name = _Title;
	}
	const std::string& Window::GetWindowTitle() const
	{
		return m_WindowUserInfo.Name;
	}


	void Window::SetWindowPosition( const Int32 _X, const Int32 _Y )
	{
		glfwSetWindowPos( m_GLFWWindow, _X, _Y );

		m_WindowUserInfo.X = _X;
		m_WindowUserInfo.Y = _Y;
	}

	void Window::SetWindowPosition( const Vector2& _Position )
	{
		m_WindowUserInfo.X = Cast( Int32, _Position.X );
		m_WindowUserInfo.Y = Cast( Int32, _Position.Y );

		glfwSetWindowPos( m_GLFWWindow, m_WindowUserInfo.X, m_WindowUserInfo.Y );
	}

	void Window::GetWindowPosition( AE_Out Int32& _X, AE_Out Int32& _Y ) const
	{
		_X = m_WindowUserInfo.X;
		_Y = m_WindowUserInfo.Y;
	}

	Vector2 Window::GetWindowPosition() const
	{
		return Vector2( Cast( float, m_WindowUserInfo.X ), Cast( float, m_WindowUserInfo.Y ) );
	}


	void Window::SetFrameRate( Int8 _FrameRate )
	{
		m_WindowUserInfo.FrameRate = _FrameRate;
	}
	Uint32 Window::GetFrameRate() const
	{
		return m_WindowUserInfo.FrameRate;
	}
	Uint32 Window::GetRealFrameRate() const
	{
		return Cast( Uint32, 1.0f / Aero.m_DeltaTime );
	}

	Time Window::GetFrameTime() const
	{
		return Time::Seconds( Aero.m_DeltaTime );
	}

	const Time& Window::GetFrameComputeTime() const
	{
		return m_FrameComputeTime;
	}

	Uint32 Window::GetHeight() const
	{
		return m_WindowUserInfo.Height;
	}
	Uint32 Window::GetWidth() const
	{
		return m_WindowUserInfo.Width;
	}

	Bool Window::IsDPIAware() const
	{
		return  m_WindowUserInfo.IsDPIAware;
	}

} // ae

ae::WindowStyle operator|( ae::WindowStyle _A, ae::WindowStyle _B )
{
	return static_cast<ae::WindowStyle>( static_cast<Int64>( _A ) | static_cast<Int64>( _B ) );
}

#include "Context.h"

#include "../../Debugging/Debugging.h"

#include <stdio.h>
#include "../Dependencies/GLFW.h"

namespace ae
{

	Context::Context()
	{
		//m_DeviceContextHandle = nullptr;
		//m_RenderingContextHande = nullptr;
	}
	Context::~Context()
	{
		//if( m_DeviceContextHandle && m_RenderingContextHande )
		//{
			Deinit();

			//m_DeviceContextHandle = nullptr;
			//m_RenderingContextHande = nullptr;
		//}
	}

	void Context::SetupPixelFormat()
	{
		/*Int32 PixelFormat = 0;

		m_PixelDescriptor.nSize = sizeof( PIXELFORMATDESCRIPTOR );								// Size of structure.
		m_PixelDescriptor.nVersion = 1;															// Default version.
		m_PixelDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; // Window drawing support and opengl support and double buffering support.
		m_PixelDescriptor.iPixelType = PFD_TYPE_RGBA;											// RGBA color mode.
		m_PixelDescriptor.cColorBits = 32;														// 32 bit color mode.
		m_PixelDescriptor.cRedBits = 0;
		m_PixelDescriptor.cRedShift = 0;
		m_PixelDescriptor.cGreenBits = 0;
		m_PixelDescriptor.cGreenShift = 0;
		m_PixelDescriptor.cBlueBits = 0;
		m_PixelDescriptor.cBlueShift = 0;
		m_PixelDescriptor.cAlphaBits = 0;
		m_PixelDescriptor.cAlphaShift = 0;
		m_PixelDescriptor.cAccumBits = 0;
		m_PixelDescriptor.cAccumRedBits = 0;
		m_PixelDescriptor.cAccumGreenBits = 0;
		m_PixelDescriptor.cAccumBlueBits = 0;
		m_PixelDescriptor.cAccumAlphaBits = 0;
		m_PixelDescriptor.cDepthBits = 16;														// 16 bit z - buffer size.
		m_PixelDescriptor.cStencilBits = 0;
		m_PixelDescriptor.cAuxBuffers = 0;
		m_PixelDescriptor.iLayerType = PFD_MAIN_PLANE;											// Main drawing plane.
		m_PixelDescriptor.bReserved = False;
		m_PixelDescriptor.dwLayerMask = NULL;
		m_PixelDescriptor.dwVisibleMask = NULL;
		m_PixelDescriptor.dwDamageMask = NULL;

		// Choose best matching format.
		PixelFormat = ChoosePixelFormat( m_DeviceContextHandle, &m_PixelDescriptor );

		// Set the pixel format to the device context.
		SetPixelFormat( m_DeviceContextHandle, PixelFormat, &m_PixelDescriptor );*/
	}

	void Context::Init( GLFWwindow* _WindowHandle )
	{
        m_GLFWWindow = _WindowHandle;
        MakeCurrent();
		/*m_DeviceContextHandle = GetDC( _WindowHandle );

		SetupPixelFormat();

		m_RenderingContextHande = wglCreateContext( m_DeviceContextHandle );

		wglMakeCurrent( m_DeviceContextHandle, m_RenderingContextHande );*/

	}
	void Context::Deinit()
	{
		/*if( m_DeviceContextHandle && m_RenderingContextHande )
		{
			wglMakeCurrent( m_DeviceContextHandle, NULL );
			wglDeleteContext( m_RenderingContextHande );
			m_DeviceContextHandle = nullptr;
			m_RenderingContextHande = nullptr;
		}*/
	}
	Bool Context::MakeCurrent( Bool ) const
	{
		/*if( m_DeviceContextHandle && m_RenderingContextHande )
		{
			const BOOL&& Result = wglMakeCurrent( m_DeviceContextHandle, m_RenderingContextHande );

			if( !Result && _LogErrorIfFail )
				AE_ErrorCheckHResult( GetLastError() );

			return Cast( Bool, Result );
		}*/
        if( m_GLFWWindow == nullptr )
            return False;

        glfwMakeContextCurrent( m_GLFWWindow );

		return True;
	}
	void Context::SwapDeviceBuffers()
	{
		//if( m_DeviceContextHandle )
		//	SwapBuffers( m_DeviceContextHandle );

        if( m_GLFWWindow == nullptr )
            return;

        glfwSwapBuffers( m_GLFWWindow );
	}

} // ae
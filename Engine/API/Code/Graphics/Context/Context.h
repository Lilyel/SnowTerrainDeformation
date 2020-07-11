#ifndef _CONTEXT_AERO_H_
#define _CONTEXT_AERO_H_

#include "../../Toolbox/Toolbox.h"

//#include <Windows.h>

struct GLFWwindow;

namespace ae
{
	/// \ingroup graphics
	/**
	 * Context for OpenGL rendering.
	 */
	class AERO_CORE_EXPORT Context
	{
	public:
		/** Default constructor. */
		Context();
		/** Destructor */
		~Context();

		/**
		 * Create device and rendering context then make to current the context.
		 */
		void Init( GLFWwindow* _WindowHandle );
		/** 
		 * Destroy the contexts.
		 */
		void Deinit();
		/**
		 * Make this context the current for the calling thread.
		 * Context must be init before this call.
		 */
		Bool MakeCurrent( Bool _LogErrorIfFail = True ) const;

		/**
		 * Swap buffers to draw the new rendered image.
		 */
		void SwapDeviceBuffers();

	protected:
		/**
		 * Choose and set the best pixel format for the device context.
		 */
		void SetupPixelFormat();

	protected:
		/** Rendering context handle of the window. */
		//HGLRC m_RenderingContextHande;
		/** Device context handle of the window. */
		//HDC m_DeviceContextHandle;

		/** Pixel descriptor for the device. */
		//PIXELFORMATDESCRIPTOR m_PixelDescriptor;
        GLFWwindow* m_GLFWWindow;
	};

} // ae

#endif

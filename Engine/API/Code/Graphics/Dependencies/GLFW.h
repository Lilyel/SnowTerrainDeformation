#ifndef _GLFW_DEPENDENCIES_AERO_H_
#define _GLFW_DEPENDENCIES_AERO_H_

#include "GLFW/glfw3.h"

#ifdef AE_INCLUDE_GLFW_NATIVE
#ifdef WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include "GLFW/glfw3native.h"
#endif

#endif // _OPENGL_DEPENDENCIES_AERO_H_
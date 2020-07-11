#pragma once

#include "Platform.h"

/** @file Export.h */

/**
* @addtogroup   toolbox
*
* @{
*/


/// <summary>Major number of Aero version.</summary>
#define AERO_VERSION_MAJOR 0

/// <summary>Minor number of Aero version.</summary>
#define AERO_VERSION_MINOR 0

/// <summary>Patch number of Aero version.</summary>
#define AERO_VERSION_PATCH 1


/// <summary>Aero version as string.</summary>
#define AERO_VERSION_STR L"0.0.1"

#ifdef WINDOWS

    #ifdef AERO_DLL_EXPORT
	/// <summary>DLL export/import instruction.</summary>
    #define AERO_CORE_EXPORT __declspec(dllexport)
    #else
    /// <summary>DLL export/import instruction.</summary>
    #define AERO_CORE_EXPORT __declspec(dllimport)
    #endif

#elif LINUX

    // GCC 4 has special attributs.
    #if __GNUC__ >= 4
	/// <summary>DLL export/import instruction.</summary>
    #define AERO_CORE_EXPORT __attribute__ ((__visibility__ ("default")))
    #define AERO_CORE_EXPORT __attribute__ ((__visibility__ ("default")))
    // Before, there was nothing specific.
    #else
	/// <summary>DLL export/import instruction.</summary>
    #define AERO_CORE_EXPORT
    #endif

#endif // OS

/** @} */

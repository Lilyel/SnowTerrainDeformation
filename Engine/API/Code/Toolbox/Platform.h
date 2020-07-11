#pragma once

/** @file Platform.h */

/**
* @addtogroup   toolbox
*
* @{
*/

#if defined(_WIN32) || defined(_WIN64)

/// <summary>Is defined if the running plateform is Windows.</summary>
#define WINDOWS

    #if defined(_WIN64)
	/// <summary>Is defined if the running plateform is 64 bits (x64).</summary>
    #define ENVIRONMENT64
    #else
	/// <summary>Is defined if the running plateform is 32 bits (x86).</summary>
    #define ENVIRONMENT32
    #endif

    #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
    #endif

    #ifndef VC_EXTRALEAN
    #define VC_EXTRALEAN
    #endif

#elif defined(linux) || defined(__linux)

	/// <summary>Is defined if the running plateform is Linux.</summary>
    #define LINUX

#endif

/** @} */


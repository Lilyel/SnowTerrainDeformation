#pragma once

#include "Platform.h"

/** @file Types.h */

/**
* @addtogroup   toolbox
*
* @{
*/

// Windows
#ifdef WINDOWS

/// <summary>8 bits integer.</summary>
typedef signed __int8 Int8;

/// <summary>8 bits unsigned integer.</summary>
typedef unsigned __int8 Uint8;


/// <summary>16 bits integer.</summary>
typedef signed __int16 Int16;

/// <summary>16 bits unsigned integer.</summary>
typedef unsigned __int16 Uint16;


/// <summary>32 bits integer.</summary>
typedef signed __int32 Int32;

/// <summary>32 bits unsigned integer.</summary>
typedef unsigned __int32 Uint32;


/// <summary>64 bits integer.</summary>
typedef signed __int64 Int64;

/// <summary>64 bits unsigned integer.</summary>
typedef unsigned __int64 Uint64;


/// <summary>Alias for boolean type.</summary>
typedef bool Bool;

// Other platform.
#else
/// <summary>8 bits integer.</summary>
typedef signed   char Int8;

/// <summary>8 bits unsigned integer.</summary>
typedef unsigned char Uint8;


/// <summary>16 bits integer.</summary>
typedef signed   short Int16;

/// <summary>16 bits unsigned integer.</summary>
typedef unsigned short Uint16;


/// <summary>32 bits integer.</summary>
typedef signed   int Int32;

/// <summary>32 bits unsigned integer.</summary>
typedef unsigned int Uint32;


/// <summary>64 bits integer.</summary>
typedef signed   long long Int64;

/// <summary>64 bits unsigned integer.</summary>
typedef unsigned long long Uint64;


/// <summary>Alias for boolean type.</summary>
typedef unsigned char Bool;
#endif


/// <summary>True value for boolean type.</summary>
#define True true

/// <summary>False value for boolean type.</summary>
#define False false


/// <summary>In Parameters type.</summary>
#define AE_In

/// <summary>Out Parameters type.</summary>
#define AE_Out

/// <summary>In and Out Parameters type.</summary>
#define AE_InOut

/// <summary>C++17 Feature : tag for parameters or variable to notify the compiler that can be unsed in order to not generate a warning for them.</summary>
#define AE_MaybeUnused [[maybe_unused]]

/// <summary>Compilation safe cast.</summary>
#define Cast(Type, Value) static_cast<Type>(Value)

/// <summary>Equivalent to "=0" to mark function as pure.</summary>
#define AE_IsVirtualPure = 0

/** @} */

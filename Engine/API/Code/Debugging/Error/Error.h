#ifndef _ERROR_AERO_H_
#define _ERROR_AERO_H_

#include "../../Toolbox/Toolbox.h"
#include "../Log/Log.h"

#include <assert.h>

namespace ae
{
    namespace priv
    {
        /// \ingroup debugging
        /// <summary>
        /// Set of function to check standard error
        /// (HResult, errno_t, OpenGL errors, ...) and
        /// log an error if the error retrieve is not ok.
        /// </summary>
        /// <param name="_Error">Value to check.</param>
        /// <returns>True if the value was ok, False otherwise.</returns>
        class AERO_CORE_EXPORT Error
        {
        public:

            /// <summary>Check an HResult value value to see if it is ok.</summary>
            /// <param name="_Result">Value to check.</param>
            /// <returns>True if the value was ok, False otherwise.</returns>
            static Bool CheckHResult( const Uint32 _Result );


            /// <summary>Check an errno_t value to see if it is ok.</summary>
            /// <param name="_Error">Value to check.</param>
            /// <returns>True if the value was ok, False otherwise.</returns>
            static Bool CheckErrno( const Uint32 _Error );


            /// <summary>Check an OpenGL error value to see if it is ok.</summary>
            /// <param name="_glError">Value to check.</param>
            /// <returns>True if the value was ok, False otherwise.</returns>
            static Bool CheckOpenGLError( const Uint32 _glError );


            /// <summary>Convert a HResult error value to a Win32 error value.</summary>
            /// <param name="_ErrorCode">HResult value to convert.</param>
            /// <returns>HResult error value converted.</returns>
            static Uint32 Win32FromHResult( Uint32 _ErrorCode );


            /// <summary>Reset "buffer" of the errno_t value.</summary>
            static void ResetErrno();
        };

    } // priv
} // ae



/** @file Error.h */

/**
* @addtogroup  debugging
*
* @{
*/


/// <summary>Check an HResult value to see if it is ok.</summary>
/// <param name="_Result">Value to check.</param>
/// <returns>True if the value was ok, False otherwise.</returns>
#define AE_ErrorCheckHResult(_Result) ( ae::priv::Error::CheckHResult( _Result ) )


/// <summary>Check an errno_t value to see if it is ok.</summary>
/// <param name="_Error">Value to check.</param>
/// <returns>True if the value was ok, False otherwise.</returns>
#define AE_ErrorCheckErrno(_Error) ( ae::priv::Error::CheckErrno( _Error ) )


/// <summary>Check an OpenGL error value to see if it is ok.</summary>
/// <returns>True if the value was ok, False otherwise.</returns>
#define AE_ErrorCheckOpenGLError() ( ae::priv::Error::CheckOpenGLError( glGetError() ) )


/// <summary>
/// Check a condition and if the condition fail, the message is log and an assert is rose.
/// </summary>
/// <param name="_ConditionToVerify">Condition to check. If this condition is not valid, the program will stop.</param>
/// <param name="_Message">The message to log.</param>
#define AE_Assert(_ConditionToVerify, _Message) \
    if(!(_ConditionToVerify)) \
    { \
        AE_LogError( _Message ); \
        assert( _ConditionToVerify ); \
    }

/** @} */


#endif // _ERROR_AERO_H_

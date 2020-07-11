#ifndef _LOG_AERO_H_
#define _LOG_AERO_H_

#include "../../Toolbox/Toolbox.h"
#include <string>

namespace ae
{
    /// \ingroup debugging
    /// <summary>
    /// Class that give the possibility to log messages into the console
    /// and to a file named "log.txt".
    /// Offer the possibility to get the stack trace. Pdb files are needed to retrieve all infos.
    /// </summary>
    class AERO_CORE_EXPORT Log
    {
    public:
        /// <summary>Possible type of message.</summary>
        enum MessageType
        {
            /// <summary>Log the message as a message.</summary>
            Message = 0,

            /// <summary>Log the message as a warning.</summary>
            Warning,

            /// <summary>Log the message as an error.</summary>
            Error
        };

    public:
        /// <summary>Initialize Log external library.</summary>
        /// <param name="_LogInFile">If true the log will also be written in a file next to the executable.</param>
        static void Initialize( Bool _LogInFile );

        /// <summary>Log a message to the console and to log.txt.</summary>
        /// <param name="_MessageType">Type of the message, can be Message, Warning or Error.</param>
        /// <param name="_Message">Message to log.</param>
        static void LogMessage( MessageType _MessageType, const std::string& _Message );

    };
} // ae

/** @file Log.h */

/**
* @addtogroup  debugging
*
* @{
*/

/// <summary>
/// A macro allow the user to log a error to the console and put it in the log file.
/// If it execute in visual, it log into the output window too.
/// </summary>
/// <param name="_Message">The message to log.</param>
#define AE_LogError(_Message) \
		{ \
			ae::Log::LogMessage(ae::Log::MessageType::Error, _Message );\
		} 

/// <summary>
/// A macro allow the user to log a warning to the console and put it in the log file.
/// If it execute in visual, it log into the output window too.
/// </summary>
/// <param name="_Message">The message to log.</param>
#define AE_LogWarning(_Message) \
		{ \
			ae::Log::LogMessage(ae::Log::MessageType::Warning, _Message );\
		} 

/// <summary>
/// A macro allow the user to log a message to the console and put it in the log file.
/// If it execute in visual, it log into the output window too.
/// </summary>
/// <param name="_Message">The message to log.</param>
#define AE_LogMessage(_Message) \
		{ \
			ae::Log::LogMessage(ae::Log::MessageType::Message, _Message );\
		} 

/** @} */

#endif
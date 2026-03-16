#include "Log.h"


#include "../Error/Error.h"

#include "../Dependencies/loguru.hpp"

namespace ae
{
    void Log::Initialize( Bool _LogInFile )
    {
        //loguru::init( argc, argv );

        if( _LogInFile )
            loguru::add_file( "Log/Log.txt", loguru::Truncate, loguru::Verbosity_INFO );
    }

    void Log::LogMessage( MessageType _MessageType, const std::string& _Message )
	{
        loguru::Text StackTrace = loguru::stacktrace( 1 );

        std::string Message = StackTrace.c_str();
        Message += std::string( "\n\t " ) + _Message;

        int logLevel[3] = { loguru::Verbosity_INFO, loguru::Verbosity_WARNING, loguru::Verbosity_ERROR };

        VLOG_F( logLevel[_MessageType], Message.c_str() );
	}

} // ae
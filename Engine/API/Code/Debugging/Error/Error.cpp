#include "Error.h"
#include "../Log/Log.h"

#ifdef WINDOWS
#include <Windows.h>
#include <winbase.h>
#include <winerror.h>
#endif
#include "../../Graphics/Dependencies/OpenGL.h"

#include <string>

namespace ae
{
    namespace priv
    {
        Bool IsThereHResultError( const Uint32 _Result )
        {
#ifdef WINDOWS
            return _Result != S_OK;
#else
            return False;
#endif
        }

        void HResultToString( std::string& _Out, const Uint32 _Result )
        {
#ifdef WINDOWS
            char ErrorBuffer[256] = "\0";
            FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, NULL, _Result, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), ErrorBuffer, 255, NULL );
            _Out = ErrorBuffer;
#endif
        }

        Bool IsThereErrnoError( const Uint32 _Error )
        {
            return _Error != 0;
        }

        void ErrnoToString( std::string& _Out, const Uint32 _Error )
        {
            _Out = "";

            // winerror.h
            // https://msdn.microsoft.com/en-us/library/t3ayayh1.aspx
            switch( _Error )
            {
            case 0:				_Out = "No Error."; break;

            case EPERM:			_Out = "Operation not permitted."; break;
            case ENOENT:		_Out = "No such file or directory."; break;
            case ESRCH:			_Out = "No such process."; break;
            case EINTR:			_Out = "Interrupted function."; break;
            case EIO:			_Out = "I/O error."; break;
            case ENXIO:			_Out = "No such device or address."; break;
            case E2BIG:			_Out = "Argument list too long."; break;
            case ENOEXEC:		_Out = "Exec format error."; break;
            case EBADF:			_Out = "Bad file number."; break;
            case ECHILD:		_Out = "No spawned processes."; break;
            case EAGAIN:		_Out = "No more processes or not enough memory or maximum nesting level reached."; break;
            case ENOMEM:		_Out = "Not enough memory."; break;
            case EACCES:		_Out = "Permission denied."; break;
            case EFAULT:		_Out = "Bad address."; break;
            case EBUSY:			_Out = "Device or resource busy."; break;
            case EEXIST:		_Out = "File exists."; break;
            case EXDEV:			_Out = "Cross-device link."; break;
            case ENODEV:		_Out = "No such device."; break;
            case ENOTDIR:		_Out = "Not a directory."; break;
            case EISDIR:		_Out = "Is a directory."; break;
            case EINVAL:		_Out = "Invalid argument."; break;
            case ENFILE:		_Out = "Too many files open in system."; break;
            case EMFILE:		_Out = "Too many open files."; break;
            case ENOTTY:		_Out = "Inappropriate I/O control operation."; break;
            case EFBIG:			_Out = "File too large."; break;
            case ENOSPC:		_Out = "No space left on device."; break;
            case ESPIPE:		_Out = "Invalid seek."; break;
            case EROFS:			_Out = "Read-only file system."; break;
            case EMLINK:		_Out = "Too many links."; break;
            case EPIPE:			_Out = "Broken pipe."; break;
            case EDOM:			_Out = "Math argument."; break;
            case ERANGE:		_Out = "Result too large."; break;
            case EDEADLK:		_Out = "Resource deadlock would occur."; break;
            case ENAMETOOLONG:	_Out = "Filename too long."; break;
            case ENOLCK:		_Out = "No locks available."; break;
            case ENOSYS:		_Out = "Function not supported."; break;
            case ENOTEMPTY:		_Out = "Directory not empty."; break;
            case EILSEQ:		_Out = "Illegal byte sequence."; break;
            case STRUNCATE:		_Out = "String was truncated."; break;

            case ERROR_MOD_NOT_FOUND: _Out = "The specified module could not be found."; break;

            case ERROR_INVALID_ADDRESS: _Out = "Attempt to access invalid address."; break;

            default:			_Out = "Unkown error."; break;
            }
        }

        Bool IsThereOpenGLError( const Uint32 _glError )
        {
            return _glError != GL_NO_ERROR;
        }

        void OpenGLToString( std::string& _Out, const Uint32 _glError )
        {
            switch( _glError )
            {
            case GL_NO_ERROR:			_Out = "OpenGL : No error."; break;

            case GL_INVALID_ENUM:		_Out = "OpenGL (GL_INVALID_ENUM) : Unacceptable value."; break;
            case GL_INVALID_VALUE:		_Out = "OpenGL (GL_INVALID_VALUE) : Argument out of range."; break;
            case GL_INVALID_OPERATION:	_Out = "OpenGL (GL_INVALID_OPERATION) : Operation is not allowed in the current state"; break;
            case GL_STACK_OVERFLOW:		_Out = "OpenGL (GL_INVALID_OPERATION) : Operation cannot be done because it would overflow the limit of that stack's size."; break;
            case GL_STACK_UNDERFLOW:	_Out = "OpenGL (GL_STACK_UNDERFLOW) : Operation cannot be done because the stack is already at its lowest point."; break;
            case GL_OUT_OF_MEMORY:		_Out = "OpenGL (GL_OUT_OF_MEMORY) : Not enough memory to continue operation."; break;

            default:					_Out = "OpenGL : Unknow error."; break;
            }

        }

        Bool Error::CheckHResult( const Uint32 _Result )
        {
            if( !IsThereHResultError( _Result ) )
                return True;

            std::string ErrorString;
            HResultToString( ErrorString, _Result );

            return False;
        }
        Bool Error::CheckErrno( const Uint32 _Error )
        {
            if( !IsThereErrnoError( _Error ) )
                return True;

            std::string ErrorString;
            ErrnoToString( ErrorString, _Error );

            return False;
        }
        Bool Error::CheckOpenGLError( const Uint32 _glError )
        {
            if( !IsThereOpenGLError( _glError ) )
                return True;

            std::string ErrorString;
            ErrnoToString( ErrorString, _glError );

            return False;
        }


        Uint32 Error::Win32FromHResult( Uint32 _ErrorCode )
        {
#ifdef WINDOWS
            if( ( _ErrorCode & 0xFFFF0000 ) == MAKE_HRESULT( SEVERITY_ERROR, FACILITY_WIN32, 0 ) )
            {
                return HRESULT_CODE( _ErrorCode );
            }

            if( _ErrorCode == S_OK )
            {
                return ERROR_SUCCESS;
            }

            // Not a Win32 HRESULT so return a generic error code.
            return ERROR_CAN_NOT_COMPLETE;
#else
            return 0;
#endif
        }

        void Error::ResetErrno()
        {
            _set_errno( 0 );
        }

    } // priv
} // ae
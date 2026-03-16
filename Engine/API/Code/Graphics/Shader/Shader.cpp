#include "Shader.h"

#include "../../Debugging/Debugging.h"

#include "../../Maths/Matrix/Matrix3x3.h"
#include "../../Maths/Matrix/Matrix4x4.h"
#include "../../Maths/Vector/Vector2.h"
#include "../../Maths/Vector/Vector3.h"
#include "../Color/Color.h"

#include "../../Editor/TypesToEditor/ShaderToEditor.h"

#include "../Dependencies/OpenGL.h"

#include "../../Aero/Aero.h"

#include <fstream>
#include <string>

namespace ae
{
	Shader::Shader( const std::string& _VertexPath, const std::string& _FragmentPath, const std::string& _GeometryPath,
					const std::string& _TesselationControlPath, const std::string& _TesselationEvaluationPath ) :
		m_ProgramID( 0 ),
		m_VertexID( 0 ),
		m_GeometryID( 0 ),
		m_TesselationControlID( 0 ),
		m_TesselationEvaluationID( 0 ),
		m_FragmentID( 0 ),
		m_ComputeID( 0 ),

		m_VertexFile( _VertexPath ),
		m_GeometryFile( _GeometryPath ),
		m_TesselationControlFile( _TesselationControlPath ),
		m_TesselationEvaluationFile( _TesselationEvaluationPath ),
		m_FragmentFile( _FragmentPath ),
		m_ComputeFile( "" )
	{
		if( !Aero.CheckContext() )
			AE_LogError( "Invalid context. Cannot create shader." );

		CreateShader();

		Compile();

		SetName( std::string( "Shader_" ) + std::to_string( GetResourceID() ) );
	}

	Shader::Shader( const std::string& _ComputePath ) :
		m_ProgramID( 0 ),
		m_VertexID( 0 ),
		m_GeometryID( 0 ),
		m_TesselationControlID( 0 ),
		m_TesselationEvaluationID( 0 ),
		m_FragmentID( 0 ),
		m_ComputeID( 0 ),

		m_VertexFile( "" ),
		m_GeometryFile( "" ),
		m_TesselationControlFile( "" ),
		m_TesselationEvaluationFile( "" ),
		m_FragmentFile( "" ),
		m_ComputeFile( _ComputePath )
	{
		if( !Aero.CheckContext() )
			AE_LogError( "Invalid context. Cannot create shader." );

		CreateShader();

		Compile();

		SetName( std::string( "ComputeShader_" ) + std::to_string( GetResourceID() ) );
	}

	Shader::~Shader()
	{
		FreeResource();
	}

	void Shader::Bind() const
	{
		glUseProgram( m_ProgramID );
		AE_ErrorCheckOpenGLError();
	}
	void Shader::Unbind() const
	{
		glUseProgram( 0 );
		AE_ErrorCheckOpenGLError();
	}

	void Shader::SetBool( Int32 _Location, Bool _Value )
	{
		if( _Location < 0 )
			return;

		glUniform1i( _Location, Cast( GLint, _Value ) );
		AE_ErrorCheckOpenGLError();
	}

	void Shader::SetInt( Int32 _Location, Int32 _Value )
	{
		if( _Location < 0 )
			return;

		glUniform1i( _Location, Cast( GLint, _Value ) );
		AE_ErrorCheckOpenGLError();
	}

	void Shader::SetFloat( Int32 _Location, float _Value )
	{
		if( _Location < 0 )
			return;

		glUniform1f( _Location, _Value );
		AE_ErrorCheckOpenGLError();
	}

	void Shader::SetMatrix4x4( Int32 _Location, const Matrix4x4& _Value, Bool _Tranpose )
	{
		if( _Location < 0 )
			return;

		glUniformMatrix4fv( _Location, 1, _Tranpose, _Value.GetData() );
		AE_ErrorCheckOpenGLError();
	}

	void Shader::SetMatrix3x3( Int32 _Location, const Matrix3x3& _Value, Bool _Tranpose )
	{
		if( _Location < 0 )
			return;

		glUniformMatrix3fv( _Location, 1, _Tranpose, _Value.GetData() );
		AE_ErrorCheckOpenGLError();
	}

	void Shader::SetVector3( Int32 _Location, const Vector3& _Value )
	{
		if( _Location < 0 )
			return;

		glUniform3f( _Location, _Value.X, _Value.Y, _Value.Z );
		AE_ErrorCheckOpenGLError();
	}

	void Shader::SetVector2( Int32 _Location, const Vector2& _Value )
	{
		if( _Location < 0 )
			return;

		glUniform2f( _Location, _Value.X, _Value.Y );
		AE_ErrorCheckOpenGLError();
	}

	void Shader::SetColor( Int32 _Location, const Color& _Value )
	{
		if( _Location < 0 )
			return;

		glUniform4f( _Location, _Value.R(), _Value.G(), _Value.B(), _Value.A() );
		AE_ErrorCheckOpenGLError();
	}

	Int32 Shader::GetUniformLocation( const std::string& _Name ) const
	{
		LocationsMap::const_iterator itExisting = m_CachedLocations.find( _Name );
		if( itExisting == m_CachedLocations.cend() )
		{
			const Int32 Location = glGetUniformLocation( m_ProgramID, _Name.c_str() );
			AE_ErrorCheckOpenGLError();

			m_CachedLocations.insert( std::make_pair( _Name, Location ) );
			return Location;
		}
        
		return itExisting->second;
	}

	Uint32 Shader::GetProgramID() const
	{
		return m_ProgramID;
	}

	void Shader::SetName( const std::string& _NewName )
	{
		Resource::SetName( _NewName );

		const std::string& Name = GetName();

		glObjectLabel( GL_PROGRAM, m_ProgramID, Cast( GLsizei, Name.size() ), Name.c_str() );
	}

	void Shader::Compile() const
	{
		DetachShaders();
		ClearLocationsCached();

		if( !m_ComputeFile.empty() )
		{
			m_ComputeID = CompileShader( m_ComputeFile, GL_COMPUTE_SHADER );
		}
		else
		{
			m_VertexID = m_VertexFile.empty() ? 0 : CompileShader( m_VertexFile, GL_VERTEX_SHADER );
			m_FragmentID = m_FragmentFile.empty() ? 0 : CompileShader( m_FragmentFile, GL_FRAGMENT_SHADER );
			m_GeometryID = m_GeometryFile.empty() ? 0 : CompileShader( m_GeometryFile, GL_GEOMETRY_SHADER );
			m_TesselationControlID = m_TesselationControlFile.empty() ? 0 : CompileShader( m_TesselationControlFile, GL_TESS_CONTROL_SHADER );
			m_TesselationEvaluationID = m_TesselationEvaluationFile.empty() ? 0 : CompileShader( m_TesselationEvaluationFile, GL_TESS_EVALUATION_SHADER );
		}

		LinkShaders();

		DeleteShaders();
	}

	const std::string& Shader::GetVertexFile() const
	{
		return m_VertexFile;
	}

	const std::string& Shader::GetFragmentFile() const
	{
		return m_FragmentFile;
	}

	const std::string& Shader::GetGeometryFile() const
	{
		return m_GeometryFile;
	}

	const std::string& Shader::GetTesselationControlFile() const
	{
		return m_TesselationControlFile;
	}

	const std::string& Shader::GetTesselationEvaluationFile() const
	{
		return m_TesselationEvaluationFile;
	}

	const std::string& Shader::GetComputeFile() const
	{
		return m_ComputeFile;
	}

	void Shader::ClearLocationsCached() const
	{
		m_CachedLocations.clear();
	}

	const Shader::LocationsMap& Shader::GetCachedLocations()
	{
		return m_CachedLocations;
	}

	void Shader::Dispatch( Uint32 _CountGroupsX, Uint32 _CountGroupsY, Uint32 _CountGroupsZ ) const
	{
		if( m_ComputeID == 0 )
			return;

		glDispatchCompute( Math::Max( _CountGroupsX, 1u ), Math::Max( _CountGroupsY, 1u ), Math::Max(  _CountGroupsZ, 1u ) );
		AE_ErrorCheckOpenGLError();
	}

	void Shader::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::ShaderToEditor( *this );
	}

	Uint32 Shader::CompileShader( const std::string& _ShaderPath, Uint32 _ShaderType ) const
	{   
		// Retrieve shader file content.
		std::string ShaderContent;

		if( !ReadEntireFile( ShaderContent, _ShaderPath ) )
			return 0;

		std::vector<std::string> IncludeHistory;
		if( !ProcessIncludes( ShaderContent, _ShaderPath, IncludeHistory ) )
			return 0;

		Uint32 ShaderID = glCreateShader( _ShaderType );
		AE_ErrorCheckOpenGLError();

		// Link source.
		const char* ShaderSourceCode = ShaderContent.data();
		glShaderSource( ShaderID, 1, &ShaderSourceCode, NULL );
		AE_ErrorCheckOpenGLError();

		// Compile the shader.
		glCompileShader( ShaderID );
		AE_ErrorCheckOpenGLError();

		// Check for compilation error.
		Int32 Success;
		glGetShaderiv( ShaderID, GL_COMPILE_STATUS, &Success );
		AE_ErrorCheckOpenGLError();

		if( !Success )
		{
			std::string InfoLog( 1024, ' ' );
			glGetShaderInfoLog( ShaderID, 1024, NULL, &InfoLog[0] );
			AE_LogError( std::string( "Failed to compile shader : \n" ) + _ShaderPath + "\n" + InfoLog + "\n" );
		}		

		return ShaderID;
	}

	void Shader::LinkShaders() const
	{
		if( m_ComputeID != 0 )
		{
			glAttachShader( m_ProgramID, m_ComputeID );
			AE_ErrorCheckOpenGLError();
		}

		if( m_VertexID != 0 )
		{
			glAttachShader( m_ProgramID, m_VertexID );
			AE_ErrorCheckOpenGLError();
		}

		if( m_FragmentID != 0 )
		{
			glAttachShader( m_ProgramID, m_FragmentID );
			AE_ErrorCheckOpenGLError();
		}

		if( m_GeometryID != 0 )
		{
			glAttachShader( m_ProgramID, m_GeometryID );
			AE_ErrorCheckOpenGLError();
		}

		if( m_TesselationControlID != 0 )
		{
			glAttachShader( m_ProgramID, m_TesselationControlID );
			AE_ErrorCheckOpenGLError();
		}

		if( m_TesselationEvaluationID != 0 )
		{
			glAttachShader( m_ProgramID, m_TesselationEvaluationID );
			AE_ErrorCheckOpenGLError();
		}

		glLinkProgram( m_ProgramID ); AE_ErrorCheckOpenGLError();

		// Check for link errors.
		Int32 Success;
		glGetProgramiv( m_ProgramID, GL_LINK_STATUS, &Success ); AE_ErrorCheckOpenGLError();

		if( !Success )
		{
			Int32 LogLength = 1024;
			glGetProgramiv( m_ProgramID, GL_INFO_LOG_LENGTH, &LogLength );

			std::string InfoLog( Cast( size_t, LogLength ), ' ' );

			glGetProgramInfoLog( m_ProgramID, LogLength, NULL, &InfoLog[0] );
			AE_LogError( std::string( "Failed to link shader : \n" ) + InfoLog + "\n" );
		}
	}

	void Shader::DeleteShaders() const
	{
		if( m_ComputeID != 0 )
		{
			glDeleteShader( m_ComputeID );
			AE_ErrorCheckOpenGLError();
		}

		if( m_VertexID != 0 )
		{
			glDeleteShader( m_VertexID );
			AE_ErrorCheckOpenGLError();
		}

		if( m_FragmentID != 0 )
		{
			glDeleteShader( m_FragmentID );
			AE_ErrorCheckOpenGLError();
		}

		if( m_GeometryID != 0 )
		{
			glDeleteShader( m_GeometryID );
			AE_ErrorCheckOpenGLError();
		}

		if( m_TesselationControlID != 0 )
		{
			glDeleteShader( m_TesselationControlID );
			AE_ErrorCheckOpenGLError();
		}

		if( m_TesselationEvaluationID != 0 )
		{
			glDeleteShader( m_TesselationEvaluationID );
			AE_ErrorCheckOpenGLError();
		}
	}

	void Shader::CreateShader()
	{
		FreeResource();

		m_ProgramID = glCreateProgram();
		AE_ErrorCheckOpenGLError();
	}

	void Shader::FreeResource()
	{
		if( m_ProgramID && Aero.CheckContext() )
		{
			glDeleteProgram( m_ProgramID );
			AE_ErrorCheckOpenGLError();
			m_ProgramID = 0;
		}
	}

	void Shader::DetachShaders() const
	{
		if( m_ComputeID != 0 )
		{
			glDetachShader( m_ProgramID, m_ComputeID );
			AE_ErrorCheckOpenGLError();
		}

		if( m_VertexID != 0 )
		{
			glDetachShader( m_ProgramID, m_VertexID );
			AE_ErrorCheckOpenGLError();
		}

		if( m_FragmentID != 0 )
		{
			glDetachShader( m_ProgramID, m_FragmentID );
			AE_ErrorCheckOpenGLError();
		}

		if( m_GeometryID != 0 )
		{
			glDetachShader( m_ProgramID, m_GeometryID );
			AE_ErrorCheckOpenGLError();
		}

		if( m_TesselationControlID != 0 )
		{
			glDetachShader( m_ProgramID, m_TesselationControlID );
			AE_ErrorCheckOpenGLError();
		}

		if( m_TesselationEvaluationID != 0 )
		{
			glDetachShader( m_ProgramID, m_TesselationEvaluationID );
			AE_ErrorCheckOpenGLError();
		}
	}

	

	Bool Shader::ProcessIncludes( AE_InOut std::string& _ShaderContent, const std::string& _ShaderPath, std::vector<std::string>& _IncludeHistory ) const
	{
		constexpr const char* IncludeToken = "#include";

		// Continue only if there is at least one include.
		if( _ShaderContent.find( IncludeToken, 0 ) == std::string::npos )
			return True;

		std::string Path = _ShaderPath;
		RemoveFileFromPath( Path );

		size_t FinalContentSize = 0;
		std::vector<std::string> ShaderParts;

		size_t OriginPosition = 0;
		size_t Position = 0;		

		std::string PathToInclude;
		std::string IncludedContent;

		constexpr size_t QuoteSize = 1;

		while( ( Position = _ShaderContent.find( IncludeToken, OriginPosition ) ) != std::string::npos )
		{
			// Save what was before the include directive (that wasn't an include).
			if( Position - OriginPosition > 0 )
			{
				ShaderParts.push_back( _ShaderContent.substr( OriginPosition, Position - OriginPosition ) );
				FinalContentSize += ShaderParts.back().size();
			}
						
			const size_t FirstQuotePosition = _ShaderContent.find( '\"', Position );
			const size_t SecondQuotePosition = _ShaderContent.find( '\"', FirstQuotePosition + QuoteSize );
			const size_t LengthInclude = SecondQuotePosition - FirstQuotePosition - QuoteSize;

			if( FirstQuotePosition == std::string::npos || SecondQuotePosition == std::string::npos || LengthInclude == 0 )
			{
				AE_LogError( std::string( "Invalid include directive in " ) + _ShaderPath );
				return False;
			}

			// Update the origin position to continue seeking include after this one.
			OriginPosition = SecondQuotePosition + QuoteSize;

			// Check if the include is commented.
			if( Position >= 2 )
			{
				if( _ShaderContent.substr( Position - 2, 2 ) == "//" )
					continue;
			}

			PathToInclude = Path + "/" + _ShaderContent.substr( FirstQuotePosition + QuoteSize, LengthInclude );

			// Skip if it already has been included.
			if( CheckIncludeHistory( PathToInclude, _IncludeHistory ) )
				continue;
			
			// Load the include file.
			if( !ReadEntireFile( IncludedContent, PathToInclude ) )
				return False;

			// Check if the incuded file has include directive.
			if( !ProcessIncludes( IncludedContent, PathToInclude, _IncludeHistory ) )
				return False;

			ShaderParts.push_back( IncludedContent );
			FinalContentSize += ShaderParts.back().size();

			_IncludeHistory.push_back( PathToInclude );
		}

		// Concatenate all the part and the last part.
		if( !ShaderParts.empty() )
		{
			std::string LastPart = _ShaderContent.substr( OriginPosition, _ShaderContent.size() - OriginPosition );

			_ShaderContent.clear();
			_ShaderContent.reserve( FinalContentSize );

			for( const std::string& Part : ShaderParts )
				_ShaderContent += Part;
			
			// Must include the rest of the file since we save only what is before the includes directives, not what is after the last one.
			_ShaderContent += LastPart;
		}

		return True;
	}


	Bool Shader::ReadEntireFile( AE_Out std::string& _Content, const std::string& _Path ) const
	{
		std::ifstream File( _Path, std::ios::binary );
		if( !File.is_open() )
		{
			AE_LogError( std::string( "Can not open file : " ) + _Path );
			return False;
		}

		// Retrieve length of the content.
		File.seekg( 0, std::ios::end );
		std::streampos FileLength = File.tellg();
		File.seekg( 0 );

		if( FileLength == 0 )
		{
			AE_LogError( std::string( "File is empty : " ) + _Path );
			return False;
		}

		// Retrieve shader file content.
		_Content.resize( Cast( Uint32, FileLength ), ' ' );
		File.read( &_Content[0], FileLength );

		return True;
	}

	void Shader::RemoveFileFromPath( AE_InOut std::string& _Path ) const
	{
		size_t Position = _Path.find_last_of( '/' );
		if( Position != std::string::npos )
			_Path.erase( _Path.begin() + Position, _Path.end() );
	}

	Bool Shader::CheckIncludeHistory( const std::string& _Path, const std::vector<std::string>& _IncludeHistory ) const
	{
		for( const std::string& PreviousInclude : _IncludeHistory )
		{
			if( _Path == PreviousInclude )
				return True;
		}

		return False;
	}

} // ae
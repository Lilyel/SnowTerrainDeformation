#include "SnowParametersBuffer.h"
#include "SnowDisplacement.h"

#include <API/Code/Aero/Aero.h>
#include <API/Code/Graphics/Dependencies/OpenGL.h>
#include <API/Code/Debugging/Error/Error.h>

#include <API/Code/Maths/Functions/MathsFunctions.h>
#include <API/Code/UI/Dependencies/IncludeImGui.h>


SnowParametersBuffer::SnowParametersBuffer() :
	m_BufferID( 0 ),
	m_MustUpdate( True )
{
	CreateBuffer();
	UpdateBuffer();
}

SnowParametersBuffer::~SnowParametersBuffer()
{
	DeleteBuffer();
}

void SnowParametersBuffer::Bind()
{
	glBindBuffer( GL_UNIFORM_BUFFER, m_BufferID ); 
	AE_ErrorCheckOpenGLError();
}

void SnowParametersBuffer::Unbind()
{
	glBindBuffer( GL_UNIFORM_BUFFER, 0 ); 
	AE_ErrorCheckOpenGLError();
}

void SnowParametersBuffer::BindToPoint( Uint32 _BindingPoint )
{
	glBindBufferBase( GL_UNIFORM_BUFFER, _BindingPoint, m_BufferID );
	AE_ErrorCheckOpenGLError();
}

void SnowParametersBuffer::UnbindFromPoint( Uint32 _BindingPoint )
{
	glBindBufferBase( GL_UNIFORM_BUFFER, _BindingPoint, 0 );
	AE_ErrorCheckOpenGLError();
}

void SnowParametersBuffer::SetCameraNear( float _Near )
{
	m_MustUpdate = m_Parameters.CameraNear != _Near;

	m_Parameters.CameraNear = _Near;
}

float SnowParametersBuffer::GetCameraNear() const
{
	return m_Parameters.CameraNear;
}

void SnowParametersBuffer::SetCameraFar( float _Far )
{
	m_MustUpdate = m_Parameters.CameraFar != _Far;

	m_Parameters.CameraFar = _Far;
}

float SnowParametersBuffer::GetCameraFar() const
{
	return m_Parameters.CameraFar;
}

void SnowParametersBuffer::SetTextureSize( Uint32 _TextureSize )
{
	m_MustUpdate = m_Parameters.TextureSize != _TextureSize;

	m_Parameters.TextureSize = _TextureSize;
}

Uint32 SnowParametersBuffer::GetTextureSize() const
{
	return m_Parameters.TextureSize;
}

void SnowParametersBuffer::SetHeightMapScale( float _Scale )
{
	m_MustUpdate = m_Parameters.HeightMapScale != _Scale;

	m_Parameters.HeightMapScale = _Scale;
}

float SnowParametersBuffer::GetHeightMapScale() const
{
	return m_Parameters.HeightMapScale;
}

void SnowParametersBuffer::SetPixelSize( float _Size )
{
	m_MustUpdate = m_Parameters.PixelSize != _Size;

	m_Parameters.PixelSize = _Size;
}

float SnowParametersBuffer::GetPixelSize() const
{
	return m_Parameters.PixelSize;
}

void SnowParametersBuffer::UpdateTimeFromLifeTime()
{
	m_Parameters.Time = Aero.GetLifeTime();

	m_MustUpdate = True;
}

void SnowParametersBuffer::CreateBuffer()
{
	if( m_BufferID != 0 )
		DeleteBuffer();

	glGenBuffers( 1, &m_BufferID ); 
	AE_ErrorCheckOpenGLError();

	const std::string Name = "Snow Parameters Buffers";
	glObjectLabel( GL_BUFFER, m_BufferID, Cast( GLsizei, Name.length() ), Name.c_str() );
}

void SnowParametersBuffer::UpdateBuffer()
{
	if( !m_MustUpdate )
		return;

	Bind();

	glBufferData( GL_UNIFORM_BUFFER, m_Parameters.GetStructAlignedSize(), &m_Parameters, GL_STATIC_DRAW ); 
	AE_ErrorCheckOpenGLError();
	
	Unbind();

	m_MustUpdate = False;
}

void SnowParametersBuffer::Update( float _CameraFar, float _CameraNear, float _PixelSize )
{
	SetCameraFar( _CameraFar );
	SetCameraNear( _CameraNear );
	SetPixelSize( _PixelSize );
	UpdateTimeFromLifeTime();
	UpdateBuffer();
}

void SnowParametersBuffer::DeleteBuffer()
{
	if( m_BufferID != 0 )
	{
		glDeleteBuffers( 1, &m_BufferID );
		AE_ErrorCheckOpenGLError();
	}
}



void SnowParametersBuffer::ToEditor( SnowDisplacement& _Displacement )
{
	ImGui::Text( "Auto Datas" );

	ImGui::InputFloat( "Camera Near", &m_Parameters.CameraNear, 0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_ReadOnly );
	ImGui::InputFloat( "Camera Far", &m_Parameters.CameraFar, 0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_ReadOnly );

	ImGui::InputFloat( "Height Map Scale", &m_Parameters.HeightMapScale, 0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_ReadOnly );

	ImGui::InputFloat( "Pixel Size", &m_Parameters.PixelSize, 0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_ReadOnly );

	ImGui::InputFloat( "Time", &m_Parameters.Time, 0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_ReadOnly );



	ImGui::Separator();
	ImGui::Text( "Initalization" );

	if( ImGui::DragFloat( "Initial Min Height", &m_Parameters.InitialMinHeight, 0.01f, m_Parameters.CameraNear, m_Parameters.InitialMaxHeight ) )
		m_MustUpdate = True;

	if( ImGui::DragFloat( "Initial Max Height", &m_Parameters.InitialMaxHeight, 0.01f, m_Parameters.InitialMinHeight, m_Parameters.CameraFar ) )
		m_MustUpdate = True;

	if( ImGui::DragFloat( "Initial Dune Frequency", &m_Parameters.InitialDuneFrequency, 0.1f, 0.0f, ae::Math::Max<float>() ) )
		m_MustUpdate = True;

	if( ImGui::DragFloat( "Intial Seed", &m_Parameters.InitialSeed, 1.0f ) )
		m_MustUpdate = True;


	ImGui::Separator();
	ImGui::Text( "Snow Displacement" );

	if( ImGui::DragFloat( "Compression", &m_Parameters.Compression, 0.01f, 0.0f, 1.0f ) )
		m_MustUpdate = True;

	if( ImGui::DragFloat( "Roughness", &m_Parameters.Roughness, 0.01f, 0.0f, 0.8f ) )
		m_MustUpdate = True;

	float SlopeThresholdDeg = ae::Math::RadToDeg( m_Parameters.SlopeThreshold );
	if( ImGui::DragFloat( "Slope Threshold", &SlopeThresholdDeg, 1.0f, 20.0f, 90.0f, "%.3f deg" ) )
	{
		m_MustUpdate = True;
		m_Parameters.SlopeThreshold = ae::Math::DegToRad( SlopeThresholdDeg );
	}

	float SlopeMaxBetweenFrameDeg = ae::Math::RadToDeg( m_Parameters.SlopeMaxBetweenFrame );
	if( ImGui::DragFloat( "Slope Max Between Frame", &SlopeMaxBetweenFrameDeg, 1.0f, 20.0f, 90.0f, "%.3f deg" ) )
	{
		m_MustUpdate = True;
		m_Parameters.SlopeMaxBetweenFrame = ae::Math::DegToRad( SlopeMaxBetweenFrameDeg );
	}

	_Displacement.ToEditor();




	ImGui::Separator();
	ImGui::Text( "Normal Noise" );

	if( ImGui::DragFloat( "Chunk Amount", &m_Parameters.ChunkAmount, 0.1f, 0.0f, 1.0f ) )
		m_MustUpdate = True;

	if( ImGui::DragFloat( "Chunk Frequency", &m_Parameters.ChunkFrequency, 1.0f, 0.0f, ae::Math::Max<float>() ) )
		m_MustUpdate = True;

	if( ImGui::DragFloat( "Grain Amount", &m_Parameters.GrainAmount, 0.1f, 0.0f, 1.0f ) )
		m_MustUpdate = True;

	if( ImGui::DragFloat( "Grain Frequency", &m_Parameters.GrainFrequency, 1.0f, 0.0f, ae::Math::Max<float>() ) )
		m_MustUpdate = True;

	if( ImGui::DragFloat( "Noise Seed", &m_Parameters.NoiseSeed, 1.0f ) )
		m_MustUpdate = True;



	ImGui::Separator();
	ImGui::Text( "Tesselation" );

	if( ImGui::DragFloat( "Tess Min", &m_Parameters.TessMin, 1.0f, 1.0f, m_Parameters.TessMax ) )
		m_MustUpdate = True;

	if( ImGui::DragFloat( "Tess Max", &m_Parameters.TessMax, 1.0f, m_Parameters.TessMin, 10.0f ) )
		m_MustUpdate = True;

	if( ImGui::DragFloat( "Tess Camera Distance Min", &m_Parameters.TessCameraDistanceMin, 0.1f, 0.0001f, m_Parameters.TessCameraDistanceMax ) )
		m_MustUpdate = True;

	if( ImGui::DragFloat( "Tess Camera Distance Max", &m_Parameters.TessCameraDistanceMax, 0.1f, m_Parameters.TessCameraDistanceMin, 2.0f ) )
		m_MustUpdate = True;

	ImGui::Separator();
}

#include "Aero.h"

#include "../Graphics/Graphics.h"
#include "../Input/Input.h"
#include "../Maths/Primitives/TRect.h"
#include "../World/World.h"
#include "../Graphics/Window/Window.h"
#include "../Application/Application.h"
#include "../Editor/Editor.h"


#include "../Graphics/Dependencies/GLFW.h"
#include "../UI/UI.h"
#include "../UI/Dependencies/IncludeImGui.h"

#include "../Input/InputFunctionalities/InputFunctionalities.h"

#include "../Debugging/Log/Log.h"

#include <memory>

namespace ae
{
	AeroCore& AeroCore::GetInstance()
	{
		static AeroCore Instance;
		return Instance;
	}

	Bool AeroCore::Update()
	{
		// Update inputs before processing events (needed to update mouse position).
		UpdateInputs();

		// Update the world (physics, ...).
		m_World.Update();

		if( m_Window != nullptr && m_Window->IsOpen() )
		{
			m_Window->WindowIteration();
			return True;
		}

		return False;
	}


	AeroCore::AeroCore()
	{
		m_Window = nullptr;
		m_CurrentCamera = nullptr;

		m_DeltaTime = 0.0f;
		m_StartUpTime = Time::GetTick();


		// Initialize GLFW library (used to create and manage window).
		if( !glfwInit() )
			AE_LogError( "Failed to initialize GLFW library." );
	}
	AeroCore::~AeroCore()
	{
		m_Window = nullptr;
		m_CurrentCamera = nullptr;

		// Deinitialize GLFW library.
		glfwTerminate();
	}

	void AeroCore::SetWindow( Window* _Window )
	{
		m_Window = _Window;

		if( _Window == nullptr )
			return;

		if( m_CurrentCamera == nullptr )
			return;
	}
	Window* AeroCore::GetWindow()
	{
		return m_Window;
	}
	Bool AeroCore::CheckContext() const
	{
		if( m_Window == nullptr )
			return False;

		if( !m_Window->IsOpen() )
			return False;

		const Context& WindowContext = m_Window->GetContext();

		const Bool&& IsCurrent = WindowContext.MakeCurrent( False );

		return IsCurrent;
	}
	void AeroCore::SetCamera( Camera& _Camera )
	{
		m_CurrentCamera = &_Camera;
	}

	Camera& AeroCore::GetCamera()
	{
		return *m_CurrentCamera;
	}

	Bool AeroCore::HasCamera() const
	{
		return m_CurrentCamera != nullptr;
	}


	float AeroCore::GetDeltaTime() const
	{
		return m_DeltaTime;
	}

	float AeroCore::GetLifeTime() const
	{
		return Time::GetTick().AsSeconds() - m_StartUpTime.AsSeconds();
	}

	const Input::InputManager& AeroCore::GetInputManger() const
	{
		return m_InputManager;
	}

	Input::InputManager& AeroCore::GetInputManger()
	{
		return m_InputManager;
	}

	void AeroCore::UpdateInputs()
	{
		// Update inputs.
		m_InputManager.Update();
		m_InputManager.CheckCaps();
	}

	World& AeroCore::GetWorld()
	{
		return m_World;
	}

	const World& AeroCore::GetWorld() const
	{
		return m_World;
	}

	ResourcesManager& AeroCore::GetResourcesManager()
	{
		return m_Resources;
	}

	const ResourcesManager& AeroCore::GetResourcesManager() const
	{
		return m_Resources;
	}

	const std::string& AeroCore::GetPathToEngineData() const
	{
		return m_PathToEngineData;
	}

	void AeroCore::SetPathToEngineData( const std::string& _NewPath )
	{
		m_PathToEngineData = _NewPath;
	}





	void AeroCore::Run( Application& _Application, Bool _InEditor )
	{
		// Called from engine instance so the engine is initialized.


		// Application start.
		std::string PathToEngineData = "../../../Data/Engine/";
		_Application.OnApplicationStart( PathToEngineData );

		SetPathToEngineData( PathToEngineData );


		// Window creation.
		WindowSettings WindowSettings;
		_Application.OnWindowCreation( WindowSettings );

		Window MyWindow;
		MyWindow.Create( WindowSettings );


		// Setup a default camera.
		CameraPerspective Camera;
		Camera.SetControlToFPS();
		Aero.SetCamera( Camera );


		// Editor setup.
		std::string ImGuiFile = "imgui.ini";
		_Application.OnEditorCreation( ImGuiFile );


		Renderer* RendererToSend = &MyWindow;


		std::unique_ptr<Editor> EditorPtr;
		if( _InEditor )
		{
			UI::InitImGUI( MyWindow );
			ImGui::GetIO().IniFilename = ImGuiFile.c_str();

			EditorPtr = std::make_unique<Editor>();
			RendererToSend = &EditorPtr->GetViewport();
		}


		// User app initialization phase.
		_Application.OnInitialize();


		Bool MustClear = True;
		Color ClearColor = Color::Black;
		Bool DrawEditor = True;

		while( MyWindow.IsOpen() )
		{
			// Update logic.

			if( !_InEditor )
				Camera.UpdateFromRenderer( MyWindow );

			_Application.OnPreUpdate();
			Update();
			_Application.OnUpdate();


			// Rendering logic.

			_Application.OnPreRender( MustClear, ClearColor );

			if( _InEditor )
				EditorPtr->BindViewport( MustClear, ClearColor );

			else if( MustClear )
				MyWindow.Clear( ClearColor );


			_Application.OnRender( *RendererToSend );


			if( _InEditor )
				EditorPtr->UnbindViewport();

			_Application.OnPostRender();


			// Editor logic.

			if( _InEditor )
			{
				MyWindow.Clear( ae::Color::Black );
				ae::UI::NewFrame();

				_Application.OnPreEditorUpdate();
				EditorPtr->Update();
				_Application.OnEditorUpdate();

				_Application.OnEditorPreRender( DrawEditor );
				if( DrawEditor )
				{
					EditorPtr->Show();
					_Application.OnEditorRender();
				}

				ae::UI::RenderFrame();
			}

			MyWindow.Render();
		}


		// Exit logic.

		_Application.OnDeinitialize();

		MyWindow.Destroy();

	}



} // ae
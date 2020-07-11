#ifndef _AERO_H_
#define _AERO_H_


#include "../Toolbox/Toolbox.h"

#include "../TimeManagement/Time/Time.h"

#include "../World/World.h"

#include "../Resources/ResourcesManager.h"

#include "../Input/InputManager/InputManager.h"




/// <summary>Static access to the engine.</summary>
#define Aero ae::AeroCore::GetInstance()

namespace ae
{
	class Camera;
	class Window;
    class Application;


    /// <summary>
    /// Main class of the engine. <para/>
    /// Keep reference of all modules of the engine. <para/>
    /// Process and dispatch all events and request to the right modules.
    /// </summary>
	class AERO_CORE_EXPORT AeroCore
	{
		friend class Window;


	public :
        /// <summary>Retrieve the unique instance of the Aero engine.</summary>
        static AeroCore& GetInstance();
        
        /// <summary>Update the engine and its components.</summary>
        /// <returns>True if the current window is open, false otherwise.</returns>
        Bool Update();

        /// <summary>Set the current window of the application.</summary>
        /// <param name="_Window">The new window to use for the application.</param>
		void SetWindow( Window* _Window );

        /// <summary>Retrieve the current window used for the application.</summary>
        /// <returns>The current window used for the application.</returns>
		Window* GetWindow();

		/// <summary>Try to make current the context if there any.</summary>
		/// <returns>True if the context is current, False otherwise.</returns>
		Bool CheckContext() const;

        /// <summary>Set the camera used for the rendering.</summary>
        /// <param name="_Camera">The new camera to use for rendering.</param>
		void SetCamera( Camera& _Camera );

        /// <summary>Get the current camera used for the rendering.</summary>
        /// <returns>The current camera used for the rendering.</returns>
		Camera& GetCamera();
        
        /// <summary>Is there a camera set for the rendering ?</summary>
        /// <returns>True if there is a camera, False otherwise.</returns>
        Bool HasCamera() const;


        /// <summary>Get the time elapsed between the two last frames in seconds.</summary>
        /// <returns>The time elapsed between the two last frames.</returns>
		float GetDeltaTime() const;

        /// <summary>Get the time elapsed since the start of the application.</summary>
        /// <returns>Time elapsed since the start of the application.</returns>
		float GetLifeTime() const;

        /// <summary>Retrieve the input manager object.</summary>
        /// <returns>The input manager object.</returns>
        const Input::InputManager& GetInputManger() const;

        /// <summary>Retrieve the input manger object.</summary>
        /// /// <returns>The input manager object.</returns>
		Input::InputManager& GetInputManger();

		/// <summary>
		/// Update inputs.
		/// Mainly use internally.
		/// </summary>
		void UpdateInputs();

        /// <summary>Retrieve the world (it stores created objects references).</summary>
        /// <returns>The world.</returns>
		World& GetWorld();

        /// <summary>Retrieve the world (it stores created objects references).</summary>
        /// <returns>The world.</returns>
		const World& GetWorld() const;

		/// <summary>Retrieve resources manager (it stores textures, shaders, ... references).</summary>
		/// <returns>The resources manager.</returns>
		ResourcesManager& GetResourcesManager();

		/// <summary>Retrieve resources manager (it stores textures, shaders, ... references).</summary>
		/// <returns>The resources manager.</returns>
		const ResourcesManager& GetResourcesManager() const;

        /// <summary>Get the current path to the engine datas (shaders, images, ...)</summary>
        /// <returns>Path the engine datas.</returns>
        const std::string& GetPathToEngineData() const;
        /// <summary>
        /// Set the path to th engine data.<para/>
        /// The path need to lead to shaders and other stuff required by the engine.
        /// </summary>
        /// <param name="_NewPath">The new path to the engine datas.</param>
        void SetPathToEngineData( const std::string& _NewPath );

        /// <summary>
        /// Handle an application : <para/>
        /// Create a render loop and call the application events.
        /// </summary>
        /// <param name="_Application">The application to run.</param>
        /// <param name="_InEditor">True to run the application with the editor, False to not setup and draw the editor.</param>
        void Run( Application& _Application, Bool _InEditor = True );

	private:
        /// <summary>Default constructor.</summary>
		AeroCore();
        /// <summary>Destructor.</summary>
		~AeroCore();

        /// <summary>
        /// Copy constructor. <para/>
        /// Deleted for the singleton.
        /// </summary>
        /// <param name="">Other instance of AeroCore to copy.</param>
        AeroCore( const AeroCore& ) = delete;

        /// <summary>
        /// Copy operator. <para/>
        /// Deleted for the singleton.
        /// </summary>
        /// <param name="">Other instance of AeroCore to copy.</param>
        AeroCore& operator=( const AeroCore& ) = delete;


	private:
        /// <summary>Current window of the application.</summary>
		Window* m_Window;
        /// <summary>Current camera used for th rendering.</summary>
		Camera* m_CurrentCamera;

        /// <summary>Time elapsed between the two lasts frames in seconds..</summary>
		float m_DeltaTime;
        /// <summary>Time elapsed since the start of the application.</summary>
		Time m_StartUpTime;
        
        /// <summary>Input manager object : handle all keyboard/mouse/gamepad events.</summary>
		Input::InputManager m_InputManager;

        /// <summary>World : store objects and manage them.</summary>
		World m_World;

		/// <summary>Resources Manager : store the pointers to resources (textures, shaders, ...).</summary>
		ResourcesManager m_Resources;

        /// <summary>Path to folder containing shaders and Aero stuffs.</summary>
        std::string m_PathToEngineData;
	};
}

#endif
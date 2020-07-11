#pragma once

#include "../Toolbox/Toolbox.h"
#include "../Idioms/NotCopiable/NotCopiable.h"
#include "../Graphics/Color/Color.h"

#include <string>

namespace ae
{
	class WindowSettings;
	class Renderer;

	/// <summary>
	/// Utility class that can be used to create application runned by the engine.<para/>
	/// It can be sent to the engine that will handle all the initialization, updates and rendering
	/// and call the events of the application.<para/>
	/// Usage of this class require C++17 or above compiler.
	/// </summary>
	class AERO_CORE_EXPORT Application : public NotCopiable
	{
	public:

		/// <summary>First event called, just before the window creation.</summary>
		/// <param name="_PathToEngineData">Path to the engine data to setup if the folders architecture is not the default one.</param>
		virtual void OnApplicationStart( AE_InOut std::string& _PathToEngineData );

		/// <summary>Event called just before the creation of the window.</summary>
		/// <param name="_Settings">Setting prefilled, can be changed by the user.</param>
		virtual void OnWindowCreation( AE_InOut WindowSettings& _Settings );

		/// <summary>Event called just before the creation of the editor.</summary>
		/// <param name="_InitFileName">Name of the file of the UI configuration that can be changed.</param>
		virtual void OnEditorCreation( AE_InOut std::string& _InitFileName );

		/// <summary>Event called before the first update.</summary>
		virtual void OnInitialize();

		/// <summary>Event called just before the update of the engine (inputs, physics, ...).</summary>
		virtual void OnPreUpdate();

		/// <summary>Event called just after the update of the engine (inputs, physics, ...)</summary>
		virtual void OnUpdate();

		/// <summary>Event called before starting rendering.</summary>
		/// <param name="_MustClear">The rendering target must be clear ?</param>
		/// <param name="_ClearColor">The color the clear the target with.</param>
		virtual void OnPreRender( AE_InOut Bool& _MustClear, AE_InOut Color& _ClearColor );

		/// <summary>Envet called during the rendering.</summary>
		/// <param name="_Renderer">The current bound renderer (can be the viewport or the final render target).</param>
		virtual void OnRender( Renderer& _Renderer );

		/// <summary>Event called after the rendering.</summary>
		virtual void OnPostRender();

		/// <summary>
		/// Event called just before the editor is updated.<para/>
		/// Not called if the editor is not asked when sending the application to the engine.
		/// </summary>
		virtual void OnPreEditorUpdate();

		/// <summary>
		/// Event called just after the editor is updated.<para/>
		/// Not called if the editor is not asked when sending the application to the engine.
		/// </summary>
		virtual void OnEditorUpdate();

		/// <summary>Event called just before the editor is drawn.</summary>
		/// <param name="_ShowEditor">Must the editor be drawn ?</param>
		virtual void OnEditorPreRender( AE_InOut Bool& _ShowEditor );

		/// <summary>
		/// Event called juste after the editor is drawn.<para/>
		/// Not called if the editor is not drawn.
		/// </summary>
		virtual void OnEditorRender();

		/// <summary>Called if the window is closing, just before its destruction.</summary>
		virtual void OnDeinitialize();
	};
}

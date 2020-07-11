#pragma once


#include "../Toolbox/Toolbox.h"
#include "../World/World.h"
#include "../Resources/ResourcesManager.h"
#include "../Graphics/Framebuffer/Framebuffer.h"
#include "../Maths/Vector/Vector2.h"

#include <string>
#include <array>

////////////////////////////////////////////////////////////
/// \defgroup editor Editor
///
/// Editor related functionalities.
/// User interface that show the created objects 
/// and give the possibility to edit them.
/// 
////////////////////////////////////////////////////////////


namespace ae
{
	class Texture2D;

    /// \ingroup editor
    /// <summary>
    /// Editor. <para/>
    /// Can show an interface to see objects world hiearchy and edit these objects.<para/>
    /// Also give the possibility to control a camera to explore the world.
    /// </summary>
    class AERO_CORE_EXPORT Editor
    {
	private:
		/// <summary>Determine the nature of the object to show in details panel.</summary>
		enum class DetailToShow : Uint8
		{
			None,
			World,
			WorldObject,
			Resource
		};

		/// <summary>Determine which windows to show.</summary>
		enum class Windows : Uint8
		{
			Stats,
			Outliner,
			Details,
			Resources,
			Viewport,

			Count
		};

    public:
        /// <summary>Initialize the editor.</summary>
        /// <param name="_HDR">Use float texture for the viewport textures ?</param>
        Editor( Bool _HDR = False );

        /// <summary>
        /// Show the user interface part of the editor.<para/>
        /// (Outliner, details, stats, ...)
        /// </summary>
        void Show();

        /// <summary>
        /// Update editor.<para/>
        /// Process input to move camera.<para/>
        /// Process shortcuts.
        /// </summary>
        void Update();

		/// <summary>Bind and (optionaly) clear the viewport framebuffer.</summary>
		/// <param name="_ClearViewport">If set to true, the viewport will be cleared after bound.</param>
		/// <param name="_ClearColor">Clear color for the viewport.</param>
		void BindViewport( Bool _ClearViewport = True, const Color& _ClearColor = Color::Black );

		/// <summary>
		/// Unbind the viewport framebuffer.
		/// </summary>
		void UnbindViewport();

		/// <summary>Update the viewport framebuffer size according to the current camera.</summary>
		void UpdateViewportSize();

		/// <summary>Retrieve the viewport framebuffer.</summary>
		/// <returns>The viewport framebuffer.</returns>
		Framebuffer& GetViewport();

		/// <summary>Retrieve the viewport framebuffer.</summary>
		/// <returns>The viewport framebuffer.</returns>
		const Framebuffer& GetViewport() const;


		/// <summary>Retrieve the final render framebuffer.</summary>
		/// <returns>The final render framebuffer.</returns>
		Framebuffer& GetFinalRender();

		/// <summary>Retrieve the final render framebuffer.</summary>
		/// <returns>The final render framebuffer.</returns>
		const Framebuffer& GetFinalRender() const;


		/// <summary>Retrieve the final render framebuffer texture.</summary>
		/// <returns>The final render framebuffer texture.</returns>
		Texture2D& GetFinalRenderTexture();

		/// <summary>Retrieve the final render framebuffer texture.</summary>
		/// <returns>The final render framebuffer texture.</returns>
		const Texture2D& GetFinalRenderTexture() const;


		/// <summary>Retrieve the number of samples for multi-sample rendering framebuffer.</summary>
		/// <returns>The current number of samples.</returns>
		Uint32 GetSamplesCount() const;

		/// <summary>Draw an object to the viewport.</summary>
		/// <param name="_Object">The object to draw.</param>
		/// <param name="_Camera">Optionnal camera. If null, the current active camera will be taken.</param>
		void DrawOnViewport( const Drawable& _Object, Camera* _Camera = nullptr );


		/// <summary>Set the number of samples for anti-aliasing.</summary>
		/// <param name="_SamplesCount">The number of samples to use for anti-aliasing.</param>
		void SetMSAASamplesCount( Uint32 _SamplesCount );

		/// <summary>Capture the final viewport image and save it to a file.</summary>
		/// <param name="_FolderPath">The folder path to use for the screenshots.</param>
		void ScreenshotViewport( const std::string& _FolderPath = "Screenshots/" );

    private:
        /// <summary>Show the interface for the outliner (objects hiearchy).</summary>
        void ShowOutliner();

        /// <summary>Show the interface to see and edit the current selected object.</summary>
        void ShowDetails();
        
        /// <summary>Show the world settings interface.</summary>
        void ShowWorldSettings();

        /// <summary>Show an interface that show fps and other perfomance/stats stuff.</summary>
        void ShowStats();

        /// <summary>Show the gizimos to edit easily an object's transform.</summary>
        void ManipulateSelection();

		/// <summary>Show resources stored in the manager.</summary>
		void ShowResources();

		/// <summary>Show details of the current selected world object.</summary>
		void ShowWorldObjectDetails();

		/// <summary>Show details of the current selected resource.</summary>
		void ShowResourceDetails();

		/// <summary>Show window with the viewport framebuffer texture.</summary>
		void ShowViewport();

		/// <summary>Update internal values of width, height and rect.</summary>
		void UpdateViewportData();

		/// <summary>Global menu bar of the editor.</summary>
		void ShowMainMenuBar();

		/// <summary>
		/// Is the given editor window open ?<para/>
		/// Meant to be given to ImGui functions.
		/// </summary>
		/// <param name="_Window">Nature of the editor window.</param>
		/// <returns>True if it is open, False otherwise.</returns>
		bool* IsWindowOpen( Windows _Window );

    private:
        /// <summary>Current selected object.</summary>
        World::ObjectID m_SelectedObject;

		/// <summary>Current selected resource.</summary>
		ResourcesManager::ResourceID m_SelectedResource;

		/// <summary>Determine which details function to call.</summary>
		DetailToShow m_DetailToShow;

		/// <summary> Render target that is drawn in viewport window.</summary>
		Framebuffer m_Viewport;

		/// <summary>Image to blit the viewport on and send to the UI.</summary>
		Framebuffer m_FinalImage;

		/// <summary>Top Left corner of the viewport.</summary>
		Vector2 m_ViewportTopLeft;

		/// <summary>Bottom right corner of the viewport.</summary>
		Vector2 m_ViewportBottomRight;

		/// <summary>Width of the viewport at the end of the previous frame.</summary>
		Uint32 m_ViewportWidth;

		/// <summary>Height of the viewport at the end of the previous frame.</summary>
		Uint32 m_ViewportHeight;

		/// <summary>Is the viewport the current window in focus ?</summary>
		Bool m_IsViewportFocused;

		/// <summary>Determine which manipulation show to user.</summary>
		Int32 m_ManipTool;

		/// <summary>Determine which attachement of the viewport framebuffer to show.</summary>
		FramebufferAttachement::Type m_ViewportAttachement;

		/// <summary>Samples count for MSAA anti aliasing.</summary>
		Uint32 m_MSAASamples;
		/// <summary>Used to apply antialiasing to the viewport.</summary>
		Uint32 m_AntiAliasingChanged;

		/// <summary>Number of currently drawn to viewport.</summary>
		Uint64 m_VerticesDrawn;

		/// <summary>Number of primitives drawn to viewport.</summary>
		Uint64 m_PrimitivesDrawn;

		/// <summary>Keep track of which window must be shown or not.</summary>
		std::array<bool, Cast( size_t, Windows::Count )> m_IsWindowOpen;
    };

} // ae
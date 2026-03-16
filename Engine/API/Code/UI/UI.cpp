#include "UI.h"

#include "../Graphics/Window/Window.h"
#include "../Graphics/Camera/Camera.h"

#define AE_INCLUDE_GLFW_NATIVE
#include "../Graphics/Dependencies/GLFW.h"

#include "Dependencies/IncludeImGui.h"



namespace ae
{
        namespace UI
        {
            const char* GetClipboardData( void* _UserData )
            {
                return glfwGetClipboardString( (GLFWwindow*)_UserData );
            }
            void SetClipboardData( void* _UserData, const char* _Text )
            {
                glfwSetClipboardString( (GLFWwindow*)_UserData, _Text );
            }

            void InitImGUI( Window& _Window )
            {
                IMGUI_CHECKVERSION();
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO();
                io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
                io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
                io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
				io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;		// Make the UI DPI aware.
				io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;

                // Setup Dear ImGui style
                ImGui::StyleColorsDark();

                // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
                ImGuiStyle& style = ImGui::GetStyle();
                if( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
                {
                    style.WindowRounding = 0.0f;
                    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
                }

                // Setup Platform/Renderer bindings
                ImGui_ImplGlfw_InitForOpenGL( &_Window.GetGLFWWindow(), true );
                ImGui_ImplOpenGL3_Init();
            }

            void DeinitImGUI()
            {
                ImGui_ImplOpenGL3_Shutdown();
                ImGui_ImplGlfw_Shutdown();
                ImGui::DestroyContext();
            }


            void NewFrame()
            {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();
            }

            void RenderFrame()
            {
                ImGui::EndFrame();
                

                ImGuiIO& io = ImGui::GetIO(); (void)io;

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

                // Update and Render additional Platform Windows
                // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
                //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
                if( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
                {
                    GLFWwindow* backup_current_context = glfwGetCurrentContext();
                    ImGui::UpdatePlatformWindows();
                    ImGui::RenderPlatformWindowsDefault();
                    glfwMakeContextCurrent( backup_current_context );
                }
            }

            void BeginEditorDock()
            {
                ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos( viewport->Pos );
                ImGui::SetNextWindowSize( viewport->Size );
                ImGui::SetNextWindowViewport( viewport->ID );
                ImGui::SetNextWindowBgAlpha( 0.0f );

                ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
                window_flags |= ImGuiWindowFlags_NoBackground;

                ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.0f );
                ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );
                ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0.0f, 0.0f ) );
                ImGui::Begin( "Editor", nullptr, window_flags );
                ImGui::PopStyleVar( 3 );

                ImGuiID dockspace_id = ImGui::GetID( "Editor_Space" );
                ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
                ImGui::DockSpace( dockspace_id, ImVec2( 0.0f, 0.0f ), dockspace_flags );

            }

            void EndEditorDock()
            {
                ImGui::End();
            }

        } // UI


} // ae

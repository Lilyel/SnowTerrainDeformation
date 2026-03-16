#include "Editor.h"

#include "../UI/UI.h"
#include "../UI/Dependencies/IncludeImGui.h"
#include "../UI/Dependencies/ImGuizmo.h"
#include "TypesToEditor/WorldObjectToEditor.h"
#include "../Aero/Aero.h"
#include "../World/WorldObject/WorldObject.h"
#include "../Maths/Transform/Transform.h"
#include "../Graphics/Camera/Camera.h"
#include "../Graphics/Window/Window.h"
#include "../Graphics/Drawable/Drawable.h"
#include "../Input/Input.h"
#include "../Graphics/Image/Image.h"
#include "../Graphics/Texture/Texture2D.h"
#include "../TimeManagement/Date/Date.h"

#include <array>
#include <string>
#include <inttypes.h>

namespace ae
{
	Editor::Editor( Bool _HDR ) :
		m_SelectedObject( World::InvalidObjectID ),
		m_SelectedResource( ResourcesManager::InvalidResourceID ),
		m_DetailToShow( DetailToShow::None ),
		m_Viewport( 512, 512, _HDR ? Framebuffer::AttachementPreset::RGBA_F16_DepthStencil_U_24_8_MS : Framebuffer::AttachementPreset::RGBA_U8_DepthStencil_U_24_8_MS ),
		m_FinalImage( 512, 512, _HDR ? Framebuffer::AttachementPreset::RGBA_F16 : Framebuffer::AttachementPreset::RGBA_U8 ),
		m_ViewportTopLeft( 0.0f, 0.0f ),
		m_ViewportBottomRight( 512.0f, 512.0f ),
		m_ViewportWidth( 512 ),
		m_ViewportHeight( 512 ),
		m_IsViewportFocused( False ),
		m_ManipTool( ImGuizmo::OPERATION::BOUNDS ),
		m_ViewportAttachement( FramebufferAttachement::Type::Color_0 ),
		m_MSAASamples( 16 ),
		m_AntiAliasingChanged( False ),
		m_VerticesDrawn( 0 ),
		m_PrimitivesDrawn( 0 )
	{
		m_IsWindowOpen.fill( true );

		Texture* ViewportColor = m_Viewport.GetAttachementTexture( FramebufferAttachement::Type::Color_0 );
		if( ViewportColor != nullptr )
			ViewportColor->SetName( "Viewport Multisample Color Attachement" );


		Texture* ViewportDepthStencil = m_Viewport.GetAttachementTexture( FramebufferAttachement::Type::DepthStencil );
		if( ViewportDepthStencil != nullptr )
			ViewportDepthStencil->SetName( "Viewport Multisample Depth/Stencil Attachement" );


		Texture* ViewportFinal = m_FinalImage.GetAttachementTexture( FramebufferAttachement::Type::Color_0 );
		if( ViewportFinal != nullptr )
			ViewportFinal->SetName( "Viewport Final Color Attachement" );
	}


	void Editor::Show()
	{
		UI::BeginEditorDock();
		ShowMainMenuBar();
		ShowOutliner();
		ShowDetails();
		ShowStats();
		ShowResources();
		ShowViewport();
		UI::EndEditorDock();
	}

	void Editor::Update()
	{
		Camera& CurrentCamera = Aero.GetCamera();

		if( m_IsViewportFocused )
		{
			const float WheelDelta = Cast( float, Input::GetMouseDeltaWheel() );
			const Bool WheelhHasMoved = WheelDelta != 0.0f;

			const Vector3 CameraLook = -CurrentCamera.GetForward();

			if( Input::IsKeyDown( Input::Key::Keyboard_LeftShift ) || Input::IsKeyDown( Input::Key::Keyboard_RightShift ) )
			{
				const ae::Vector2 DeltaMove = ae::Input::GetMouseDeltaMove();
				const float RotationFactor = Aero.GetDeltaTime() / 10.0f;
				const float TranslationFactor = Aero.GetDeltaTime() / 2.0f;

				const Vector3 CameraRight = -CurrentCamera.GetLeft();
				const Vector3 CameraUp = CurrentCamera.GetUp();

				if( Input::IsKeyDown( Input::Key::Mouse_LeftButton ) )
				{
					if( CurrentCamera.GetControlType() == Camera::ControlType::Orbit )
						CurrentCamera.Rotate( DeltaMove.Y * RotationFactor, DeltaMove.X * -RotationFactor, 0.0f );
					else
						CurrentCamera.Rotate( DeltaMove.Y * RotationFactor, DeltaMove.X * RotationFactor, 0.0f );
				}

				else if( Input::IsKeyDown( Input::Key::Mouse_RightButton ) || WheelhHasMoved )
				{
					if( CurrentCamera.GetControlType() == Camera::ControlType::Orbit )
						CurrentCamera.SetOrbitDistance( CurrentCamera.GetOrbitDistance() + ( DeltaMove.Y * TranslationFactor ) );
					else
					{
						CurrentCamera.Translate( CameraRight * ( DeltaMove.X * TranslationFactor ) );
						CurrentCamera.Translate( CameraUp * ( DeltaMove.Y * TranslationFactor ) );
					}
				}

				else if( Input::IsKeyDown( Input::Key::Mouse_MiddleButton ) )
				{
					if( CurrentCamera.GetControlType() == Camera::ControlType::Orbit )
						CurrentCamera.SetOrbitDistance( CurrentCamera.GetOrbitDistance() + ( DeltaMove.Y * TranslationFactor ) );
					else
						CurrentCamera.Translate( CameraLook * ( DeltaMove.Y * TranslationFactor ) );
				}
			}
			else if( WheelhHasMoved && !Input::IsKeyboardHit() )
			{
				float ZoomFactor = -Math::Clamp( -0.1f, 0.1f, WheelDelta );

				if( CurrentCamera.GetControlType() == Camera::ControlType::Orbit )
					CurrentCamera.SetOrbitDistance( CurrentCamera.GetOrbitDistance() + ZoomFactor );
				else
					CurrentCamera.Translate( CameraLook * ZoomFactor );
			}

			if( Input::IsKeyPressed( Input::Key::Keyboard_W ) )
				m_ManipTool = ImGuizmo::OPERATION::TRANSLATE;

			else if( Input::IsKeyPressed( Input::Key::Keyboard_E ) )
				m_ManipTool = ImGuizmo::OPERATION::ROTATE;

			else if( Input::IsKeyPressed( Input::Key::Keyboard_R ) )
				m_ManipTool = ImGuizmo::OPERATION::SCALE;

			else if( Input::IsKeyPressed( Input::Key::Keyboard_Q ) )
				m_ManipTool = ImGuizmo::OPERATION::BOUNDS;
		}


		if( Input::IsKeyPressed( Input::Key::Keyboard_F ) )
		{
			if( Input::IsKeyDown( Input::Key::Keyboard_LeftShift ) )
				CurrentCamera.SetControlToFPS();

			else if( m_SelectedObject != World::InvalidObjectID )
			{
				World& WorldRef = Aero.GetWorld();

				Transform* ObjectTransform = dynamic_cast<Transform*>( WorldRef.GetObject( m_SelectedObject ) );

				if( ObjectTransform != nullptr )
					CurrentCamera.SetControlToOrbit( ObjectTransform->GetPosition() );
			}
		}
	}

	void Editor::BindViewport( Bool _ClearViewport, const Color& _ClearColor )
	{
		UpdateViewportSize();

		m_Viewport.Bind();
		glEnable( GL_MULTISAMPLE );


		if( _ClearViewport )
		{
			m_Viewport.Clear( _ClearColor );
			m_VerticesDrawn = 0;
			m_PrimitivesDrawn = 0;
		}
	}

	void Editor::UnbindViewport()
	{
		m_Viewport.Unbind();
	}

	void Editor::UpdateViewportSize()
	{
		if( m_ViewportWidth != m_Viewport.GetWidth() || m_ViewportHeight != m_Viewport.GetHeight() || m_AntiAliasingChanged )
		{
			m_Viewport.SetSamplesCount( m_MSAASamples );
			m_Viewport.Resize( m_ViewportWidth, m_ViewportHeight );

			m_FinalImage.Resize( m_ViewportWidth, m_ViewportHeight );


			if( Aero.HasCamera() )
				Aero.GetCamera().UpdateFromRenderer( m_Viewport );

			else
				AE_LogError( "The editor need a valid camera set." );


			m_AntiAliasingChanged = False;
		}
	}

	Framebuffer& Editor::GetViewport()
	{
		return m_Viewport;
	}

	const Framebuffer& Editor::GetViewport() const
	{
		return m_Viewport;
	}

	Framebuffer& Editor::GetFinalRender()
	{
		return m_FinalImage;
	}

	const Framebuffer& Editor::GetFinalRender() const
	{
		return m_FinalImage;
	}

	Texture2D& Editor::GetFinalRenderTexture()
	{
		return *(Texture2D*)m_FinalImage.GetAttachementTexture();
	}

	const Texture2D& Editor::GetFinalRenderTexture() const
	{
		return *(Texture2D*)m_FinalImage.GetAttachementTexture();
	}

	Uint32 Editor::GetSamplesCount() const
	{
		return m_MSAASamples;
	}

	void Editor::DrawOnViewport( const Drawable& _Object, Camera* _Camera )
	{
		m_VerticesDrawn += _Object.GetVerticesCount();
		m_PrimitivesDrawn += _Object.GetPrimitivesCount();

		m_Viewport.Draw( _Object, _Camera );
	}

	void Editor::SetMSAASamplesCount( Uint32 _SamplesCount )
	{
		if( _SamplesCount != m_MSAASamples )
		{
			m_MSAASamples = Math::Clamp( 1u, 32u, _SamplesCount );
			m_AntiAliasingChanged = True;
		}
	}

	void Editor::ScreenshotViewport( const std::string& _FolderPath )
	{
		Texture2D* FinalTexture = (Texture2D*)m_FinalImage.GetAttachementTexture();
		if( FinalTexture == nullptr )
		{
			AE_LogError( "Invalid viewport texture attachement. Can't save it to a file." );
			return;
		}

		Image&& Capture = std::move( FinalTexture->ToImage() );

		Date Now = Date::Now();
		std::string FileName = _FolderPath + "/Capture_" + std::to_string( Now.GetYear() )
			+ "." + std::to_string( Now.GetMonth() )
			+ "." + std::to_string( Now.GetDay() )
			+ "." + std::to_string( Now.GetHours() )
			+ "." + std::to_string( Now.GetMinutes() )
			+ "." + std::to_string( Now.GetSeconds() )
			+ ".png";

		if( !Capture.SaveToFile( FileName ) )
			AE_LogError( std::string( "Failed to save viewport screenshot to file " ) + FileName );
	}

	void Editor::ShowOutliner()
	{
		if( !*IsWindowOpen( Windows::Outliner ) )
			return;

		ImGui::Begin( "Outliner", IsWindowOpen( Windows::Outliner ) );

		World& WorldRef = Aero.GetWorld();

		const std::unordered_map<World::ObjectID, WorldObject*>& Objects = WorldRef.GetObjects();

		ImGuiTreeNodeFlags Flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen;

		if( ImGui::TreeNodeEx( (void*)(intptr_t)0, Flags, "World" ) )
		{
			if( ImGui::IsItemClicked() )
				m_DetailToShow = DetailToShow::World;


			for( const std::pair<World::ObjectID, WorldObject*>& Object : Objects )
			{
				if( Object.second->HasParent() )
					continue;

				ShowOutlinerObject( Object.second, Flags );
			}

			ImGui::TreePop();
		}

		ImGui::End();
	}


	void Editor::ShowOutlinerObject( WorldObject* _Object, Int32 _UIFlags )
	{
		World::ObjectID ObjectID = _Object->GetObjectID();

		ImGuiTreeNodeFlags FlagsWithSelection = _UIFlags | ( ( m_SelectedObject == ObjectID ) ? ImGuiTreeNodeFlags_Selected : 0 );

		bool IsOpen = ImGui::TreeNodeEx( (void*)(intptr_t)ObjectID, FlagsWithSelection, _Object->GetName().c_str() );
		if( ImGui::IsItemClicked() )
		{
			m_SelectedObject = ObjectID;
			m_DetailToShow = DetailToShow::WorldObject;
			m_SelectedResource = ResourcesManager::InvalidResourceID;
		}
		if( IsOpen )
		{
			// Show children.
			for( WorldObject* Child : _Object->GetChildren() )
				ShowOutlinerObject( Child, _UIFlags );

			ImGui::TreePop();
		}
	}

	void Editor::ShowDetails()
	{
		if( !*IsWindowOpen( Windows::Details ) )
			return;

		ImGui::Begin( "Details", IsWindowOpen( Windows::Details ) );

		switch( m_DetailToShow )
		{
		case DetailToShow::World:
			ShowWorldSettings();
			break;

		case DetailToShow::WorldObject:
			ShowWorldObjectDetails();
			break;

		case DetailToShow::Resource:
			ShowResourceDetails();
			break;

		case DetailToShow::None:
		default:
			break;
		}

		ImGui::End();
	}

	void Editor::ShowWorldSettings()
	{
		World& WorldRef = Aero.GetWorld();
		WorldRef.ToEditor();
	}

	void Editor::ShowStats()
	{
		if( !*IsWindowOpen( Windows::Stats ) )
			return;

		ImGui::Begin( "Stats", IsWindowOpen( Windows::Stats ) );

		ae::Window* CurrentWindow = Aero.GetWindow();

		if( CurrentWindow != nullptr )
		{
			ImGui::Text( "FPS %d / %d", CurrentWindow->GetRealFrameRate(), CurrentWindow->GetFrameRate() );
			ImGui::Text( "Frame Time (s) %f", CurrentWindow->GetFrameTime().AsSeconds() );
			ImGui::Text( "Frame Compute Time (s) %f", CurrentWindow->GetFrameComputeTime().AsSeconds() );

			if( Aero.HasCamera() )
			{
				Uint32 ViewportWidth = m_Viewport.GetWidth();
				Uint32 ViewportHeight = m_Viewport.GetHeight();
				ImGui::Text( "Viewport %d x %d", ViewportWidth, ViewportHeight );
			}

			ImGui::Text( "Vertices Drawn On Viewport %" PRIu64, m_VerticesDrawn );
			ImGui::Text( "Primitives Drawn On Viewport %" PRIu64, m_PrimitivesDrawn );
		}

		ImGui::End();
	}

	void Editor::ManipulateSelection()
	{
		if( m_ManipTool >= ImGuizmo::OPERATION::BOUNDS )
			return;

		if( m_SelectedObject == World::InvalidObjectID )
			return;

		World& WorldRef = Aero.GetWorld();

		WorldObject* Object = WorldRef.GetObject( m_SelectedObject );

		if( Object == nullptr )
			return;

		// Try to retrieve the transform component of the object.
		Transform* ObjectTr = dynamic_cast<Transform*>( Object );
		if( ObjectTr == nullptr )
			return;

		ImGuizmo::SetDrawlist();


		Vector3 Position = ObjectTr->GetPosition();
		float GuizmoPos[3] = { Position.X, Position.Y, Position.Z };
		Vector3 Rotation = ObjectTr->GetRotationAngles();
		float GuizmoRot[3] = { Math::RadToDeg( Rotation.X ), Math::RadToDeg( Rotation.Y ), Math::RadToDeg( Rotation.Z ) };
		Vector3 Scale = ObjectTr->GetScale();
		float GuizmoScale[3] = { Scale.X, Scale.Y, Scale.Z };

		float GuizmoTr[16];
		ImGuizmo::RecomposeMatrixFromComponents( GuizmoPos, GuizmoRot, GuizmoScale, GuizmoTr );

		Camera& CurrentCamera = Aero.GetCamera();
		const Matrix4x4& ProjectionMatrix = CurrentCamera.GetProjectionMatrix();
		const Matrix4x4& LookAtMatrix = CurrentCamera.GetLookAtMatrix();

		ImGuizmo::SetRect( m_ViewportTopLeft.X, m_ViewportTopLeft.Y, Cast( float, m_ViewportWidth ), Cast( float, m_ViewportHeight ) );

		ImGuizmo::Manipulate( LookAtMatrix.GetTranspose().GetData(),
							  ProjectionMatrix.GetTranspose().GetData(),
							  Cast( ImGuizmo::OPERATION, m_ManipTool ),
							  ImGuizmo::MODE::LOCAL,
							  GuizmoTr );

		ImGuizmo::DecomposeMatrixToComponents( GuizmoTr, GuizmoPos, GuizmoRot, GuizmoScale );
		ObjectTr->SetPosition( GuizmoPos[0], GuizmoPos[1], GuizmoPos[2] );
		ObjectTr->SetRotation( Math::DegToRad( GuizmoRot[0] ), Math::DegToRad( GuizmoRot[1] ), Math::DegToRad( GuizmoRot[2] ) );
		ObjectTr->SetScale( GuizmoScale[0], GuizmoScale[1], GuizmoScale[2] );
	}

	void Editor::ShowResources()
	{
		if( !*IsWindowOpen( Windows::Resources ) )
			return;

		ImGui::Begin( "Resources", IsWindowOpen( Windows::Resources ) );

		ResourcesManager& ResourcesRef = Aero.GetResourcesManager();

		const std::unordered_map<ResourcesManager::ResourceID, Resource*>& ResourcesPairs = ResourcesRef.GetResources();

		ImGuiTreeNodeFlags Flags = ImGuiTreeNodeFlags_Leaf;

		for( const std::pair<ResourcesManager::ResourceID, Resource*>& ResourcePair : ResourcesPairs )
		{
			ImGuiTreeNodeFlags FlagsWithSelection = Flags | ( ( m_SelectedResource == ResourcePair.first ) ? ImGuiTreeNodeFlags_Selected : 0 );

			if( ImGui::TreeNodeEx( (void*)(intptr_t)0, FlagsWithSelection, ResourcePair.second->GetName().c_str() ) )
			{
				if( ImGui::IsItemClicked() )
				{
					m_SelectedResource = ResourcePair.first;
					m_DetailToShow = DetailToShow::Resource;
					m_SelectedObject = World::InvalidObjectID;
				}

				ImGui::TreePop();
			}
		}

		ImGui::End();
	}

	void Editor::ShowWorldObjectDetails()
	{
		if( m_SelectedObject == World::InvalidObjectID )
			return;

		World& WorldRef = Aero.GetWorld();

		WorldObject* Object = WorldRef.GetObject( m_SelectedObject );

		if( Object != nullptr )
			Object->ToEditor();
	}

	void Editor::ShowResourceDetails()
	{
		if( m_SelectedResource == ResourcesManager::InvalidResourceID )
			return;

		ResourcesManager& ResourcesRef = Aero.GetResourcesManager();

		Resource* ResourceRef = ResourcesRef.GetResource( m_SelectedResource );

		if( ResourceRef != nullptr )
			ResourceRef->ToEditor();
	}

	void Editor::ShowViewport()
	{
		if( !*IsWindowOpen( Windows::Viewport ) )
			return;

		// Finilize viewport rendering.
		m_FinalImage.Blit( m_Viewport );

		ImGui::Begin( "Viewport", IsWindowOpen( Windows::Viewport ), ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_MenuBar );

		m_IsViewportFocused = ImGui::IsWindowFocused();

		if( ImGui::BeginMenuBar() )
		{
			// Manip settings.

			ImGui::RadioButton( "Translation", &m_ManipTool, 0 ); ImGui::SameLine();
			ImGui::RadioButton( "Rotation", &m_ManipTool, 1 ); ImGui::SameLine();
			ImGui::RadioButton( "Scale", &m_ManipTool, 2 ); ImGui::SameLine();
			ImGui::RadioButton( "Cursor", &m_ManipTool, 3 ); ImGui::SameLine();


			ImGui::Separator();

			if( ImGui::BeginMenu( "Viewport Settings" ) )
			{

				if( ImGui::BeginMenu( "Draw Mode" ) )
				{
					DrawMode CurrentDrawMode = m_Viewport.GetDrawMode();
					std::array<DrawMode, 3> DrawModes = { DrawMode::Filled, DrawMode::Wireframe, DrawMode::Points };
					std::string PossibleDrawModeName;

					for( DrawMode PossibleDrawMode : DrawModes )
					{
						Bool IsSelected = CurrentDrawMode == PossibleDrawMode;
						PossibleDrawModeName = ToString( PossibleDrawMode );

						if( ImGui::MenuItem( PossibleDrawModeName.c_str(), 0, IsSelected ) )
							m_Viewport.SetDrawMode( PossibleDrawMode );
					}

					ImGui::EndMenu();
				}

				if( ImGui::BeginMenu( "Anti-Aliasing" ) )
				{
					int SamplesCount = Cast( int, m_MSAASamples );
					if( ImGui::SliderInt( "MSAA", &SamplesCount, 1, 32 ) )
					{
						m_MSAASamples = Cast( Uint32, SamplesCount );
						m_AntiAliasingChanged = True;
					}

					ImGui::EndMenu();
				}


				if( ImGui::BeginMenu( "Culling Mode" ) )
				{
					CullingMode CurrentCullingMode = m_Viewport.GetCullingMode();
					std::array<CullingMode, 4> CullingModes = { CullingMode::NoCulling, CullingMode::BackFaces, CullingMode::FrontFaces, CullingMode::BackAndFrontFaces };
					std::string PossibleCullingModeName;

					for( CullingMode PossibleCullingMode : CullingModes )
					{
						Bool IsSelected = CurrentCullingMode == PossibleCullingMode;
						PossibleCullingModeName = ToString( PossibleCullingMode );

						if( ImGui::MenuItem( PossibleCullingModeName.c_str(), 0, IsSelected ) )
							m_Viewport.SetCullingMode( PossibleCullingMode );
					}

					ImGui::EndMenu();
				}



				ImGui::EndMenu();
			}



			ImGui::Separator();


			//if( ImGui::Button( "Screenshot Viewport" ) )
			//	ScreenshotViewport();

			ImGui::EndMenuBar();
		}

		// Update width and height of viewport available space.
		UpdateViewportData();

		// Draw framebuffer texture.
		ImGui::Image( (void*)(intptr_t)m_FinalImage.GetAttachementTextureID(),
					  ImVec2( Cast( float, m_ViewportWidth ), Cast( float, m_ViewportHeight ) ), ImVec2( 0.0f, 1.0f ), ImVec2( 1.0f, 0.0f ) );

		ManipulateSelection();

		ImGui::End();
	}

	void Editor::UpdateViewportData()
	{
		ImVec2 RegionMin = ImGui::GetWindowContentRegionMin();
		ImVec2 RegionMax = ImGui::GetWindowContentRegionMax();

		const ImVec2 WindowPosition = ImGui::GetWindowPos();

		RegionMin.x += WindowPosition.x;
		RegionMin.y += WindowPosition.y;
		RegionMax.x += WindowPosition.x;
		RegionMax.y += WindowPosition.y;

		m_ViewportTopLeft.Set( RegionMin.x, RegionMin.y );
		m_ViewportBottomRight.Set( RegionMax.x, RegionMax.y );

		m_ViewportWidth = Cast( Uint32, ae::Math::Max( RegionMax.x - RegionMin.x, 64.0f ) );
		m_ViewportHeight = Cast( Uint32, ae::Math::Max( RegionMax.y - RegionMin.y, 64.0f ) );
	}

	void Editor::ShowMainMenuBar()
	{
		if( ImGui::BeginMenuBar() )
		{
			if( ImGui::BeginMenu( "Windows" ) )
			{
				ImGui::Checkbox( "Stats", IsWindowOpen( Windows::Stats ) );
				ImGui::Checkbox( "Outliner", IsWindowOpen( Windows::Outliner ) );
				ImGui::Checkbox( "Details", IsWindowOpen( Windows::Details ) );
				ImGui::Checkbox( "Resources", IsWindowOpen( Windows::Resources ) );
				ImGui::Checkbox( "Viewport", IsWindowOpen( Windows::Viewport ) );

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}


	}

	bool* Editor::IsWindowOpen( Windows _Window )
	{
		return &( m_IsWindowOpen[Cast( size_t, _Window )] );
	}

} // ae

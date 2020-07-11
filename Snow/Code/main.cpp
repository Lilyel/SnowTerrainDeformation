
#include "HeightMap.h"
#include "DepthPass.h"
#include "PenetrationPass.h"
#include "JumpFlooding.h"
#include "SnowDisplacement.h"
#include "NormalGeneration.h"
#include "SnowParametersBuffer.h"
#include "Scene.h"
#include "SnowPlane.h"

#include <API/Code/Includes.h>
#include <API/Code/UI/Dependencies/IncludeImGui.h>


float GetPixelSize( Uint32 _TextureSize, const SnowPlane& _Ground );
void EditorTextureSize( SnowParametersBuffer& _Parameter, HeightMap& _Height, DepthPass& _Depth, PenetrationPass& _Penetration, JumpFlooding& _Flooding, NormalGeneration& _Normal, SnowDisplacement& _Displacement, const SnowPlane& _Ground );

int main()
{
	// Call once to initialize everything.
	Aero;
	Aero.SetPathToEngineData( "../../../Data/Engine/" );

	ae::Window MyWindow;
	MyWindow.Create();

	ae::CameraPerspective Camera;
	Camera.SetName( "Camera" );
	Camera.SetPosition( 0.0f, 2.0, 2.5f );
	Camera.SetRotation( ae::Math::DegToRad_Const( 30.0f ), 0.0f, 0.0f );
	Camera.SetControlToOrbit( ae::Vector3( 0.0f, 0.5f, 0.0f ) );
	Camera.SetOrbitDistance( 3.0f );
	Camera.SetNear( 0.001f );
	Camera.SetFar( 30.0f );
	Camera.SetToActiveCamera();

	


	SnowParametersBuffer Parameters;
	

	HeightMap Height( Parameters.GetTextureSize() );

	NormalGeneration Normal( Parameters.GetTextureSize() );

	SnowPlane Ground( Height.GetFloatHeightMap(), Normal.GetNormalMap() );
	

	DepthPass DepthPassFromBelow( Parameters.GetTextureSize(), Ground );

	PenetrationPass Penetration( Parameters.GetTextureSize(), Height.GetIntegerHeightMap(), DepthPassFromBelow.GetDepthTexture() );

	JumpFlooding Flooding( Parameters.GetTextureSize(), Penetration.GetPenetrationTexture() );

	SnowDisplacement Displacement( Parameters.GetTextureSize(), Height.GetIntegerHeightMap(), Penetration.GetPenetrationTexture(), Flooding.GetDistanceTexture() );

	
	
	float PixelSize = GetPixelSize( Parameters.GetTextureSize(), Ground );
	Parameters.Update( DepthPassFromBelow.GetCameraFar(), DepthPassFromBelow.GetCameraNear(), PixelSize );
	Parameters.BindToPoint( 4 );

	

	Height.Initialize();
	

	Scene SceneObjects;

	ae::UI::InitImGUI( MyWindow );
	ae::Editor Editor( True );
	ImGui::GetIO().IniFilename = "Snow.ini";

	ae::Bloom BloomPostProcess;
	BloomPostProcess.SetIterationsCount( 5u );
	BloomPostProcess.SetStandardDeviation( 1.2f );
	BloomPostProcess.NormalizeGaussian( True );

	ae::GammaCorrection GammaPostProcess;

	while( Aero.Update() )
	{
		SceneObjects.UpdateBootsAnim();

		DepthPassFromBelow.UpdateCamera( Ground );
		PixelSize = GetPixelSize( Parameters.GetTextureSize(), Ground );
		Parameters.Update( DepthPassFromBelow.GetCameraFar(), DepthPassFromBelow.GetCameraNear(), PixelSize );


		// Draw the objects that can collide with the terrain.
		DepthPassFromBelow.Run( SceneObjects );

		// Process the penetration.
		Penetration.Run();

		// Find closest available points to transfert penetrating snow.
		Flooding.Run();

		// Move penetrating snow onto free spots.
		Displacement.Run( Height.GetIntegerHeightMap(), Penetration.GetPenetrationTexture(), Flooding.GetDistanceTexture() );

		// Generate ground normal map from height map.
		Normal.Run( Height.GetIntegerHeightMap() );


		// Convert height to float to take advantage of linear filtering during ground rendering.
		Height.ToFloat();


		// Draw objects and ground.
		Editor.BindViewport( True, ae::Color( 0.1f, 0.1f, 0.1f ) );

		SceneObjects.RenderColorPass( Editor.GetViewport() );
		Editor.DrawOnViewport( Ground );

		Editor.UnbindViewport();


		// Finalize viewport rendering.

		MyWindow.Clear( ae::Color::Black );
		ae::UI::NewFrame();
		Editor.Update();
		Editor.Show();

		BloomPostProcess.Apply( Editor.GetFinalRenderTexture() );
		GammaPostProcess.Apply( Editor.GetFinalRenderTexture() );

		if( ImGui::Begin( "Snow" ) )
		{
			Parameters.ToEditor( Displacement );

			Flooding.ToEditor();

			EditorTextureSize( Parameters, Height, DepthPassFromBelow, Penetration, Flooding, Normal, Displacement, Ground );

			ImGui::Separator();

			if( ImGui::Button( "Reset Height Map" ) )
				Height.Initialize();

			ImGui::End();
		}

		ae::UI::RenderFrame();
		MyWindow.Render();
	}

	MyWindow.Destroy();

}


float GetPixelSize( Uint32 _TextureSize, const SnowPlane& _Ground )
{
	return _Ground.GetSize() / Cast( float, _TextureSize );
}

void EditorTextureSize( SnowParametersBuffer& _Parameter, HeightMap& _Height, DepthPass& _Depth, PenetrationPass& _Penetration, JumpFlooding& _Flooding, NormalGeneration& _Normal, SnowDisplacement& _Displacement, const SnowPlane& _Ground )
{	
	Uint32 CurrentSize = _Parameter.GetTextureSize();

	if( ImGui::BeginCombo( "Texture Size", std::to_string( CurrentSize ).c_str() ) )
	{
		Uint32 Sizes[6] = { 128, 256, 512, 1024, 2048, 4096 };

		Bool HasChanged = False;

		for( Uint32 s = 0u; s < 6u; s++ )
		{
			Bool IsSelected = Sizes[s] == CurrentSize;

			if( ImGui::Selectable( std::to_string( Sizes[s] ).c_str(), &IsSelected ) )
			{
				if( IsSelected )
				{
					HasChanged = True;
					CurrentSize = Sizes[s];
					ImGui::SetItemDefaultFocus();
				}
			}
		}

		ImGui::EndCombo();

		if( HasChanged )
		{
			_Parameter.SetTextureSize( CurrentSize );
			_Parameter.SetPixelSize( GetPixelSize( CurrentSize, _Ground ) );
			_Parameter.UpdateBuffer();

			_Height.Resize( CurrentSize );
			_Height.Initialize();

			_Depth.Resize( CurrentSize );
			_Penetration.Resize( CurrentSize );
			_Flooding.Resize( CurrentSize );
			_Normal.Resize( CurrentSize );
			_Displacement.Resize( CurrentSize );
		}
	}
}
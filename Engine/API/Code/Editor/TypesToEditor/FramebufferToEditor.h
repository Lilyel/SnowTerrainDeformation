#pragma once

#include "../../Graphics/Framebuffer/Framebuffer.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void FramebufferToEditor( Framebuffer& _Framebuffer )
			{
				ImGui::Text( "Framebuffer" );

				ImGui::Spacing();

				ImGui::Text( "Draw Mode" );

				DrawMode CurrentDrawMode = _Framebuffer.GetDrawMode();

				if( ImGui::RadioButton( ToString( DrawMode::Filled ).c_str(), CurrentDrawMode == DrawMode::Filled ) )
					CurrentDrawMode = DrawMode::Filled;

				ImGui::SameLine();

				if( ImGui::RadioButton( ToString( DrawMode::Wireframe ).c_str(), CurrentDrawMode == DrawMode::Wireframe ) )
					CurrentDrawMode = DrawMode::Wireframe;

				ImGui::SameLine();

				if( ImGui::RadioButton( ToString( DrawMode::Points ).c_str(), CurrentDrawMode == DrawMode::Points ) )
					CurrentDrawMode = DrawMode::Points;

				_Framebuffer.SetDrawMode( CurrentDrawMode );


				ImGui::Spacing();

				ImGui::Text( "Culling Mode" );

				CullingMode CurrentCullingMode = _Framebuffer.GetCullingMode();

				if( ImGui::RadioButton( ToString( CullingMode::NoCulling ).c_str(), CurrentCullingMode == CullingMode::NoCulling ) )
					CurrentCullingMode = CullingMode::NoCulling;

				if( ImGui::RadioButton( ToString( CullingMode::BackFaces ).c_str(), CurrentCullingMode == CullingMode::BackFaces ) )
					CurrentCullingMode = CullingMode::BackFaces;

				if( ImGui::RadioButton( ToString( CullingMode::FrontFaces ).c_str(), CurrentCullingMode == CullingMode::FrontFaces ) )
					CurrentCullingMode = CullingMode::FrontFaces;

				if( ImGui::RadioButton( ToString( CullingMode::BackAndFrontFaces ).c_str(), CurrentCullingMode == CullingMode::BackAndFrontFaces ) )
					CurrentCullingMode = CullingMode::BackAndFrontFaces;

				_Framebuffer.SetCullingMode( CurrentCullingMode );

				ImGui::Separator();
			}
		}

	} // priv

} // ae

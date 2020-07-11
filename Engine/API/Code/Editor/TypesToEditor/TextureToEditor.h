#pragma once

#include "../../Graphics/Texture/Texture.h"
#include "../../Graphics/Texture/Texture1D.h"
#include "../../Graphics/Texture/Texture2D.h"
#include "../../Graphics/Texture/Texture3D.h"
#include "../../Graphics/Texture/TextureMultisample.h"
#include "../../Graphics/Texture/TextureImage.h"
#include "../../Graphics/Texture/Texture2DRect.h"
#include "../../Graphics/Texture/Texture2DArray.h"
#include "../../Graphics/Texture/Texture1DArray.h"
#include "../../UI/Dependencies/IncludeImGui.h"
#include "ColorToEditor.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline int GetFilterModeIndex( Texture& _Texture )
			{
				switch( _Texture.GetFilterMode() )
				{
				case TextureFilterMode::Linear:
					return 1;

				case TextureFilterMode::Nearest_MipMap_Nearest:
					return 2;

				case TextureFilterMode::Nearest_MipMap_Linear:
					return 3;

				case TextureFilterMode::Linear_MipMap_Nearest:
					return 4;

				case TextureFilterMode::Linear_MipMap_Linear:
					return 5;

				case TextureFilterMode::Nearest :
				default:
					return 0;
				}
			}

			inline int GetWrapModeIndex( Texture& _Texture )
			{
				switch( _Texture.GetWrapMode() )
				{
				case TextureWrapMode::ClampToEdge:
					return 1;

				case TextureWrapMode::ClampToBorder:
					return 2;

				case TextureWrapMode::MirroredRepeat:
					return 3;

				case TextureWrapMode::MirroredClampToEdge:
					return 4;
					
				case TextureWrapMode::Repeat:
				default:
					return 0;
				}
			}

			inline int GeDimensionIndex( Texture& _Texture )
			{
				switch( _Texture.GetDimension() )
				{
				case TextureDimension::Texture1D:
					return 0;

				case TextureDimension::Texture2D:
					return 1;

				case TextureDimension::Texture2DMultiSample:
					return 2;

				case TextureDimension::Texture3D:
					return 3;

				case TextureDimension::CubeMap:
					return 4;

				default:
					return 0;
				}
			}

			inline void TextureToEditorBegin()
			{
				ImGui::Text( "Texture" );
			}

			inline void TextureToEditorEnd()
			{
				ImGui::Separator();
			}

			inline void Texture2DToEditorPreview( const Texture2D& _Texture )
			{
				float Width = Cast( float, _Texture.GetWidth() );
				float Height = Cast( float, _Texture.GetHeight() );

				const float Ratio = Height / Width;
				const float PreviewWidth = ImGui::GetWindowWidth();
				const float PreviewHeight = Ratio * PreviewWidth;

				ImGui::Image( (void*)(intptr_t)_Texture.GetTextureID(), ImVec2( PreviewWidth, PreviewHeight ) );
			}

			inline void TextureToEditor( Texture& _Texture )
			{		
				if( _Texture.GetTextureID() == 0 )
					ImGui::Text( "Error : Invalid texture" );


				// Filter mode.
				const char* FilterModesNames[6] = { "Nearest", "Linear", "Nearest MipMip Nearest", "Nearest MipMap Linear", "Lienar MipMap Nearest", "Linear MipMap Linear" };
				const TextureFilterMode FilterModes[6] = { TextureFilterMode::Nearest, TextureFilterMode::Linear, TextureFilterMode::Nearest_MipMap_Nearest, TextureFilterMode::Nearest_MipMap_Linear, TextureFilterMode::Linear_MipMap_Nearest, TextureFilterMode::Linear_MipMap_Linear };

				int CurrentFilterModeIndex = GetFilterModeIndex( _Texture );

				if( ImGui::Combo( "Filter Mode", &CurrentFilterModeIndex, FilterModesNames, IM_ARRAYSIZE( FilterModesNames ) ) )
					_Texture.SetFilterMode( FilterModes[CurrentFilterModeIndex] );



				// Wrap mode.
				const char* WrapModesNames[5] = { "Repeat", "Clamp To Edge", "Clamp To Border", "Mirrored Repeat", "Mirrored Clamp To Edge" };
				const TextureWrapMode WrapModes[5] = { TextureWrapMode::Repeat, TextureWrapMode::ClampToEdge, TextureWrapMode::ClampToBorder, TextureWrapMode::MirroredRepeat, TextureWrapMode::MirroredClampToEdge };

				int CurrentWrapModeIndex = GetWrapModeIndex( _Texture );

				if( ImGui::Combo( "Wrap Mode", &CurrentWrapModeIndex, WrapModesNames, IM_ARRAYSIZE( WrapModesNames ) ) )
					_Texture.SetWrapMode( WrapModes[CurrentWrapModeIndex] );

				if( _Texture.GetWrapMode() == TextureWrapMode::ClampToBorder )
				{
					
					Color Color = _Texture.GetBorderColor();
					if( ColorToEditor( "Wrap Border Color", Color ) )
						_Texture.SetBorderColor( Color );
				}


				// Pixel format.
				std::string PixelFormatName = ToString( _Texture.GetFormat() );
				ImGui::InputText( "Format", &PixelFormatName, ImGuiInputTextFlags_ReadOnly );


				// Dimension.
				std::string DimensionsNames[8] = { "Texture 1D", "Texture 2D", "Texture 2D Multisample", "Texture 2D Rectangle", "Texture 2D Array", "Texture 3D", "CubeMap" };
				int CurrentDimensionIndex = GeDimensionIndex( _Texture );
				ImGui::InputText( "Dimension", &DimensionsNames[CurrentDimensionIndex], ImGuiInputTextFlags_ReadOnly );


				// Mip Map generation.
				if( ImGui::Button( "Generate MipMap" ) )
					_Texture.GenerateMipMap();

			}

			inline void Texture1DToEditor( Texture1D& _Texture )
			{
				TextureToEditor( _Texture );

				// Size
				float Width = Cast( float, _Texture.GetWidth() );				
				ImGui::InputFloat( "Width", &Width, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );
			}

			inline void Texture1DArrayToEditor( Texture1DArray& _Texture )
			{
				TextureToEditor( _Texture );

				// Size
				float Width = Cast( float, _Texture.GetWidth() );
				ImGui::InputFloat( "Width", &Width, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );

				float Depth = Cast( float, _Texture.GetDepth() );
				ImGui::InputFloat( "Depth", &Depth, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );
			}

			inline void Texture2DToEditor( Texture2D& _Texture )
			{
				TextureToEditor( _Texture );

				// Size
				float Width = Cast( float, _Texture.GetWidth() );
				ImGui::InputFloat( "Width", &Width, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );

				float Height = Cast( float, _Texture.GetHeight() );
				ImGui::InputFloat( "Height", &Height, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );
			}

			inline void TextureMultisampleToEditor( TextureMultisample& _Texture )
			{
				Texture2DToEditor( _Texture );

				// Multi sampling.
				int SamplesCount = Cast( int, _Texture.GetSamplesCount() );
				if( ImGui::SliderInt( "Samples Count", &SamplesCount, 1, 32 ) )
					_Texture.SetSamplesCount( Cast( Uint32, SamplesCount ) );
			}

			inline void TextureImageToEditor( TextureImage& _Texture )
			{
				Texture2DToEditor( _Texture );

				std::string Path = _Texture.GetFilePath();
				ImGui::InputText( "Path", &Path, ImGuiInputTextFlags_ReadOnly );
			}

			inline void Texture2DRectToEditor( Texture2DRect& _Texture )
			{
				TextureToEditor( _Texture );

				// Size
				float Width = Cast( float, _Texture.GetWidth() );
				ImGui::InputFloat( "Width", &Width, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );

				float Height = Cast( float, _Texture.GetHeight() );
				ImGui::InputFloat( "Height", &Height, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );
			}

			inline void Texture2DArrayToEditor( Texture2DArray& _Texture )
			{
				TextureToEditor( _Texture );

				// Size
				float Width = Cast( float, _Texture.GetWidth() );
				ImGui::InputFloat( "Width", &Width, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );

				float Height = Cast( float, _Texture.GetHeight() );
				ImGui::InputFloat( "Height", &Height, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );

				float Depth = Cast( float, _Texture.GetDepth() );
				ImGui::InputFloat( "Depth", &Depth, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );
			}

			inline void Texture3DToEditor( Texture3D& _Texture )
			{
				TextureToEditor( _Texture );

				// Size
				float Width = Cast( float, _Texture.GetWidth() );
				ImGui::InputFloat( "Width", &Width, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );

				float Height = Cast( float, _Texture.GetHeight() );
				ImGui::InputFloat( "Height", &Height, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );

				float Depth = Cast( float, _Texture.GetDepth() );
				ImGui::InputFloat( "Depth", &Depth, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_ReadOnly );
			}
		}

	} // priv

} // ae

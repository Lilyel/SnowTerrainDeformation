#pragma once

#include "../../Graphics/Image/Image.h"
#include "../../Graphics/Image/ImageHDR.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void ImageToEditor( Image& )
			{
				ImGui::Text( "Image" );

				
				ImGui::Separator();
			}

			inline void ImageToEditor( ImageHDR& )
			{
				ImGui::Text( "Image HDR" );


				ImGui::Separator();
			}
		}

	} // priv

} // ae

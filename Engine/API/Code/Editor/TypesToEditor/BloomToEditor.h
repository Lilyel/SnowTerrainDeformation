#pragma once


#include "../../Graphics/PostProcess/Bloom.h"
#include "../../Maths/Functions/MathsFunctions.h"
#include "../../UI/Dependencies/IncludeImGui.h"


namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void BloomToEditorBegin()
			{
				ImGui::Text( "Bloom" );
			}
			inline void BloomToEditorEnd()
			{
				ImGui::Separator();
			}
			
			inline void BloomToEditor( Bloom& _Bloom )
			{
				Vector3 Threshold = _Bloom.GetBrightnessThreshold();
				if( ImGui::DragFloat3( "Brightness Threshold", &Threshold.X, 0.1f, 0.0f, Math::Max<float>() ) )
					_Bloom.SetBrightnessThreshold( Threshold );
			}
		}

	} // priv

} // ae

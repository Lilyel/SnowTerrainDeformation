#pragma once

#pragma once

#include "../../UI/Dependencies/IncludeImGui.h"
#include "../../Maths/Curve/Curve.h"
#include "../../Maths/Functions/MathsFunctions.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline Bool CurveEditorVector( AE_InOut Vector3& _Value, const std::string& _Label )
			{
				return ImGui::DragFloat3( _Label.c_str(), &_Value.X );
			}

			inline Bool CurveEditorFloat( AE_InOut float& _Value, const std::string& _Label, float _Min = Math::Lowest<float>(), float _Max = Math::Max<float>() )
			{
				return ImGui::DragFloat( _Label.c_str(), &_Value, 1.0, _Min, _Max );
			}

			inline void CurveEditorFloatReadOnly( float _Value, const std::string& _Label )
			{
				ImGui::InputFloat( _Label.c_str(), &_Value, 0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_ReadOnly );
			}
		}
	}
}
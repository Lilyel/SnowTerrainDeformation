#pragma once

#include "../../Graphics/PostProcess/GaussianBlur.h"
#include "../../Maths/Functions/MathsFunctions.h"
#include "../../UI/Dependencies/IncludeImGui.h"


namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void GaussianBlurToEditorBegin()
			{
				ImGui::Text( "Gaussian Blur" );
			}
			inline void GaussianBlurToEditorEnd()
			{
				ImGui::Separator();
			}

			inline void GaussianBlurToEditor( GaussianBlur& _GaussianBlur )
			{
				int Iterations = Cast( int, _GaussianBlur.GetIterationsCount() );
				if( ImGui::DragInt( "Iterations", &Iterations, 1.0f, 0, 10 ) )
					_GaussianBlur.SetIterationsCount( Cast( Uint32, Iterations ) );

				float StandardDeviation = _GaussianBlur.GetStandardDeviation();
				if( ImGui::DragFloat( "Standard Deviation", &StandardDeviation, 0.1f, 0.01f, Math::Max<float>() ) )
					_GaussianBlur.SetStandardDeviation( StandardDeviation );

				Bool IsNormalized = _GaussianBlur.IsGaussianNormalized();
				if( ImGui::Checkbox( "Is Normalized", &IsNormalized ) )
					_GaussianBlur.NormalizeGaussian( IsNormalized );


				int CurrentRadius = Cast( int, _GaussianBlur.GetRadius() );

				ImGui::RadioButton( "5x5", &CurrentRadius, Cast( int, GaussianBlur::Radius::_5x5 ) ); ImGui::SameLine();
				ImGui::RadioButton( "11x11", &CurrentRadius, Cast( int, GaussianBlur::Radius::_11x11 ) ); ImGui::SameLine();
				ImGui::RadioButton( "21x21", &CurrentRadius, Cast( int, GaussianBlur::Radius::_21x21 ) ); ImGui::SameLine();
				ImGui::RadioButton( "41x41", &CurrentRadius, Cast( int, GaussianBlur::Radius::_41x41 ) ); ImGui::SameLine();
				ImGui::Text( "Radius" ); 

				_GaussianBlur.SetRadius( Cast( GaussianBlur::Radius, CurrentRadius ) );

				float Coefs[5];
				_GaussianBlur.GetCoefs( Coefs );

				ImGui::Columns( 9, "Coeficients" );
				for( int i = 0; i < 9; i++ )
				{
					std::string ColumnName = "##" + std::to_string( i );
					ImGui::InputFloat( ColumnName.c_str(), &Coefs[Math::Abs( i - 4 )], 0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_ReadOnly ); ImGui::NextColumn();
				}

				ImGui::Columns( 1 );
			}
		}

	} // priv

} // ae

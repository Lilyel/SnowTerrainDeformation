#include "CurveKochanekBartels.h"

#include "../Functions/MathsFunctions.h"
#include "../../Editor/CurveEditor/CurveEditorHelper.h"
#include "../../Debugging/Error/Error.h"

namespace ae
{

	CurveKochanekBartels::CurveKochanekBartels( const std::vector<Vector3>& _ControlPoints ) :
		Curve( _ControlPoints )
	{
		m_Settings.resize( _ControlPoints.size() );
		AutoProcessTangents();
	}

	CurveKochanekBartels::CurveKochanekBartels( const std::vector<Vector3>& _ControlPoints, const std::vector<ControlPointSettings>& _Settings ) :
		Curve( _ControlPoints )
	{
		if( _ControlPoints.size() != _Settings.size() )
			throw std::exception( "The number control points is different from the number of settings." );

		m_Settings = _Settings;
		AutoProcessTangents();
	}



	void CurveKochanekBartels::Rebuild( const std::vector<Vector3>& _ControlPoints )
	{
		Curve::Rebuild( _ControlPoints );

		m_Settings.clear();
		m_Settings.resize( _ControlPoints.size() );
		AutoProcessTangents();
	}

	void CurveKochanekBartels::Rebuild( const std::vector<Vector3>& _ControlPoints, const std::vector<ControlPointSettings>& _Settings )
	{
		if( _ControlPoints.size() != _Settings.size() )
			throw std::exception( "The number control points is different from the number of settings." );

		Curve::Rebuild( _ControlPoints );

		m_Settings = _Settings;
		AutoProcessTangents();
	}



	Vector3 CurveKochanekBartels::GetPointAtParam( float _Param ) const
	{
		return HermiteInterpolationPoint( _Param );
	}


	Curve::Type CurveKochanekBartels::GetType() const
	{
		return Type::KochanekBartels;
	}



	const CurveKochanekBartels::ControlPointSettings& CurveKochanekBartels::GetControlPointSetting( Uint32 _Index ) const
	{
		if( _Index >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );

		return m_Settings[_Index];
	}

	void CurveKochanekBartels::SetControlPointSetting( Uint32 _Index, const ControlPointSettings& _Settings )
	{
		if( _Index >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );

		m_Settings[_Index] = _Settings;
	}


	float CurveKochanekBartels::GetControlPointBias( Uint32 _Index ) const
	{
		if( _Index >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );

		return m_Settings[_Index].Bias;
	}

	void CurveKochanekBartels::SetControlPointBias( Uint32 _Index, float _Bias )
	{
		if( _Index >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );

		m_Settings[_Index].Bias = _Bias;
		UpdateTangent( _Index );
	}


	float CurveKochanekBartels::GetControlPointTension( Uint32 _Index ) const
	{
		if( _Index >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );

		return m_Settings[_Index].Tension;
	}

	void CurveKochanekBartels::SetControlPointTension( Uint32 _Index, float _Tension )
	{
		if( _Index >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );

		m_Settings[_Index].Tension = _Tension;
		UpdateTangent( _Index );
	}



	const Vector3& CurveKochanekBartels::GetPreviousTangent( Uint32 _Index ) const
	{
		if( _Index >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );

		return m_PreviousTangents[_Index];
	}

	void CurveKochanekBartels::SetPreviousTangent( Uint32 _Index, const Vector3& _Tangent )
	{
		if( _Index >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );

		m_PreviousTangents[_Index] = _Tangent;
		UpdateTangent( _Index );
	}

	const Vector3& CurveKochanekBartels::GetNextTangent( Uint32 _Index ) const
	{
		if( _Index >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );

		return m_NextTangents[_Index];
	}

	void CurveKochanekBartels::SetNextTangent( Uint32 _Index, const Vector3& _Tangent )
	{
		if( _Index >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );

		m_NextTangents[_Index] = _Tangent;
		UpdateTangent( _Index );
	}



	Uint32 CurveKochanekBartels::EditorGetPropertiesCount() const
	{
		return 6;
	}

	const std::string& CurveKochanekBartels::EditorGetPropertyName( Uint32 _Index ) const
	{
		static std::string Names[6] = { "Position", "Previous Tangent", "Next Tangent", "Bias", "Tension", "Time" };

		return Names[_Index];
	}

	Bool CurveKochanekBartels::EditorEditProperty( const std::string& _Label, Uint32 _ControlPoint, Uint32 _Property )
	{
		switch( _Property )
		{
		case 0:
		{
			Vector3 Position = GetControlPoint( _ControlPoint );
			if( priv::ui::CurveEditorVector( Position, _Label ) )
			{
				SetControlPoint( _ControlPoint, Position );
				return True;
			}
		}
		break;

		case 1:
		{
			Vector3 PreviousTangent = GetPreviousTangent( _ControlPoint );
			if( priv::ui::CurveEditorVector( PreviousTangent, _Label ) )
			{
				SetPreviousTangent( _ControlPoint, PreviousTangent );
				return True;
			}
		}
		break;

		case 2:
		{
			Vector3 NextTangent = GetNextTangent( _ControlPoint );
			if( priv::ui::CurveEditorVector( NextTangent, _Label ) )
			{
				SetNextTangent( _ControlPoint, NextTangent );
				return True;
			}
		}
		break;

		case 3:
		{
			float Bias = GetControlPointBias( _ControlPoint );
			if( priv::ui::CurveEditorFloat( Bias, _Label ) )
			{
				SetControlPointBias( _ControlPoint, Bias );
				return True;
			}
		}
		break;

		case 4:
		{
			float Tension = GetControlPointTension( _ControlPoint );
			if( priv::ui::CurveEditorFloat( Tension, _Label ) )
			{
				SetControlPointTension( _ControlPoint, Tension );
				return True;
			}
		}
		break;

		case 5:
			priv::ui::CurveEditorFloatReadOnly( m_Times[_ControlPoint], _Label );
			break;

		default:
			AE_LogWarning( "Invalid curve editor property." );
			break;
		}

		return False;
	}



	Vector3 CurveKochanekBartels::HermiteInterpolationPoint( float _Param ) const
	{
		if( GetControlPointsCount() < 1 )
			throw std::exception( "Can't retrieve point at parameter : the curve has less than 2 points." );

		float Parameter = Math::Clamp( GetTimeMin(), GetTimeMax(), _Param );

		const size_t Index0 = Cast( size_t, Math::Floor( Parameter ) );

		// In case the index is the last point.
		if( Index0 == GetControlPointsCount() - 1 )
			return m_ControlPoints.back();


		const size_t Index1 = Index0 + 1;

		// Bring back the parameter between 0 and 1.
		const float Time = ( Parameter - m_Times[Index0] ) / ( m_Times[Index1] - m_Times[Index0] );

		return Math::HermiteInterpolation( m_ControlPoints[Index0], m_ModifiedTangents[Index0], m_ControlPoints[Index1], m_ModifiedTangents[Index1], Time );
	}


	void CurveKochanekBartels::AutoProcessTangents()
	{
		const Uint32 Count = GetControlPointsCount();

		m_PreviousTangents.resize( Count );
		m_NextTangents.resize( Count );
		m_ModifiedTangents.resize( Count );

		for( Uint32 CP = 0; CP < Count; CP++ )
		{
			const Vector3& Current = m_ControlPoints[CP];
			const Vector3& Previous = CP > 0 ? m_ControlPoints[Cast( size_t, CP ) - 1] : Current;
			const Vector3& Next = CP < Count - 1 ? m_ControlPoints[Cast( size_t, CP ) + 1] : Current;

			m_PreviousTangents[CP] = Vector3( Previous, Current );
			m_NextTangents[CP] = Vector3( Current, Next );

			UpdateTangent( CP );
		}
	}


	void CurveKochanekBartels::UpdateTangent( Uint32 _Index )
	{
		if( _Index >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );


		const ControlPointSettings& Setting = GetControlPointSetting( _Index );

		// * 0.5f -> to average the two tangents.
		const float Tension = ( 1.0f - Setting.Tension ) * 0.5f;
		const float CoefPrevious = Tension * ( 1.0f + Setting.Bias );
		const float CoefNext = Tension * ( 1.0f - Setting.Bias );

		m_ModifiedTangents[_Index] = m_PreviousTangents[_Index] * CoefPrevious + m_NextTangents[_Index] * CoefNext;
	}

}

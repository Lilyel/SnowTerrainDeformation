#include "Curve.h"

#include "../../Editor/CurveEditor/CurveEditorHelper.h"

#include "../../Debugging/Error/Error.h"

#include <algorithm>

namespace ae
{

	Curve::Curve( const std::vector<Vector3>& _ControlPoints ) :
		m_ControlPoints( _ControlPoints )
	{
		AutoProcessTimes();
	}

	void Curve::Rebuild( const std::vector<Vector3>& _ControlPoints )
	{
		m_ControlPoints = _ControlPoints;
		AutoProcessTimes();
	}


	float Curve::GetTimeMin() const
	{
		if( GetControlPointsCount() == 0 )
			throw std::exception( "Can't retrieve time of the first control point : the curve is empty." );

		return m_Times.front();
	}

	float Curve::GetTimeMax() const
	{
		if( GetControlPointsCount() == 0 )
			throw std::exception( "Can't retrieve time of the last control point : the curve is empty." );

		return m_Times.back();
	}

	float Curve::GetTime( Uint32 _ControlPointIndex ) const
	{
		if( _ControlPointIndex >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );

		return m_Times[_ControlPointIndex];
	}



	const Vector3& Curve::GetControlPoint( Uint32 _Index ) const
	{
		if( _Index >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );

		return m_ControlPoints[_Index];
	}

	void Curve::SetControlPoint( Uint32 _Index, const Vector3& _Position )
	{
		if( _Index >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );

		m_ControlPoints[_Index] = _Position;
	}


	Uint32 Curve::GetControlPointsCount() const
	{
		return Cast( Uint32, m_ControlPoints.size() );
	}




	Curve::Type Curve::GetType() const
	{
		return Type::Unknown;
	}

	Uint32 Curve::EditorGetPropertiesCount() const
	{
		return 2;
	}

	const std::string& Curve::EditorGetPropertyName( Uint32 _Index ) const
	{
		static std::string Names[2] = { "Position", "Time" };

		return Names[_Index];
	}

	Bool Curve::EditorEditProperty( const std::string& _Label, Uint32 _ControlPoint, Uint32 _Property )
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
			priv::ui::CurveEditorFloatReadOnly( m_Times[_ControlPoint], _Label );
			break;

		default:
			AE_LogWarning( "Invalid curve editor property." );
			break;
		}

		return False;
	}


	void Curve::AutoProcessTimes()
	{
		m_Times.resize( m_ControlPoints.size() );

		if( !m_Times.empty() )
		{
			float IncTime = 0.0f;

			for( float& Time : m_Times )
			{
				Time = IncTime;
				IncTime += 1.0f;
			}
		}
	}

	std::string ToString( const Curve::Type& _Type )
	{
		std::string TypeNames[4] =
		{
			"Linear", 
			"Hermite",
			"Kochanek-Bartels",
			"Unknown"
		};

		return TypeNames[Cast( Uint8, _Type )];
	}

} // ae

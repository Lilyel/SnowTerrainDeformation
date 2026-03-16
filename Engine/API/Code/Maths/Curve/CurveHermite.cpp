#include "CurveHermite.h"

#include "../Functions/MathsFunctions.h"
#include "../../Editor/CurveEditor/CurveEditorHelper.h"
#include "../../Debugging/Error/Error.h"

namespace ae
{

	CurveHermite::CurveHermite( const std::vector<Vector3>& _ControlPoints ) :
		Curve( _ControlPoints )
	{
		AutoProcessTangents();
	}

	CurveHermite::CurveHermite( const std::vector<Vector3>& _ControlPoints, const std::vector<Vector3>& _ControlTangents ) :
		Curve( _ControlPoints )
	{
		if( _ControlPoints.size() != _ControlTangents.size() )
			throw std::exception( "The number control points is different from the number of control tangents." );

		m_ControlTangents = _ControlTangents;
	}


	void CurveHermite::Rebuild( const std::vector<Vector3>& _ControlPoints )
	{
		Curve::Rebuild( _ControlPoints );

		AutoProcessTangents();
	}


	void CurveHermite::Rebuild( const std::vector<Vector3>& _ControlPoints, const std::vector<Vector3>& _ControlTangents )
	{
		if( _ControlPoints.size() != _ControlTangents.size() )
			throw std::exception( "The number control points is different from the number of control tangents." );

		Curve::Rebuild( _ControlPoints );

		m_ControlTangents = _ControlTangents;
	}


	const Vector3& CurveHermite::GetControlTangent( Uint32 _Index ) const
	{
		if( _Index >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );

		return m_ControlTangents[_Index];
	}

	void CurveHermite::SetControlTangent( Uint32 _Index, const Vector3& _Tangent )
	{
		if( _Index >= GetControlPointsCount() )
			throw std::out_of_range( "Invalid control point index." );

		m_ControlTangents[_Index] = _Tangent;
	}



	Vector3 CurveHermite::GetPointAtParam( float _Param ) const
	{
		return HermiteInterpolationPoint( _Param );
	}

	Curve::Type CurveHermite::GetType() const
	{
		return Type::Hermite;
	}



	Uint32 CurveHermite::EditorGetPropertiesCount() const
	{
		return 3;
	}

	const std::string& CurveHermite::EditorGetPropertyName( Uint32 _Index ) const
	{
		static std::string Names[3] = { "Position", "Tangent", "Time" };

		return Names[_Index];
	}

	Bool CurveHermite::EditorEditProperty( const std::string& _Label, Uint32 _ControlPoint, Uint32 _Property )
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
			Vector3 Tangent = GetControlTangent( _ControlPoint );
			if( priv::ui::CurveEditorVector( Tangent, _Label ) )
			{
				SetControlTangent( _ControlPoint, Tangent );
				return True;
			}
		}
		break;

		case 2:
			priv::ui::CurveEditorFloatReadOnly( m_Times[_ControlPoint], _Label );
			break;

		default:
			AE_LogWarning( "Invalid curve editor property." );
			break;
		}

		return False;
	}
	



	Vector3 CurveHermite::HermiteInterpolationPoint( float _Param ) const
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

		return Math::HermiteInterpolation( m_ControlPoints[Index0], m_ControlTangents[Index0], m_ControlPoints[Index1], m_ControlTangents[Index1], Time );
	}



	void CurveHermite::AutoProcessTangents()
	{
		const size_t Count = m_ControlPoints.size();

		m_ControlTangents.resize( Count );

		for( size_t CP = 0; CP < Count; CP++ )
		{
			const Vector3& Current = m_ControlPoints[CP];
			const Vector3& Previous = CP > 0 ? m_ControlPoints[CP - 1] : Current;
			const Vector3& Next = CP < Count - 1 ? m_ControlPoints[CP + 1] : Current;

			const float TangentSize = Vector3( Previous, Next ).Length() / 2.0f;

			const Vector3&& Tangent = Vector3( Previous, Current ) + Vector3( Current, Next );

			m_ControlTangents[CP] = Tangent.GetNormalized() * TangentSize;
		}
	}
}

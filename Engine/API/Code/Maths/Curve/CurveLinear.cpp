#include "CurveLinear.h"

#include "../Functions/MathsFunctions.h"

namespace ae
{

	CurveLinear::CurveLinear( const std::vector<Vector3>& _ControlPoints ) : 
		Curve( _ControlPoints )
	{
	}


	Vector3 CurveLinear::GetPointAtParam( float _Param ) const
	{
		return LinearInterpolation( _Param, m_ControlPoints );
	}

	Curve::Type CurveLinear::GetType() const
	{
		return Type::Linear;
	}



	Vector3 CurveLinear::LinearInterpolation( float _Param, const std::vector<Vector3>& _ToInterpolate ) const
	{
		if( GetControlPointsCount() < 1 )
			throw std::exception( "Can't retrieve point at parameter : the curve has less than 2 points." );

		float Parameter = Math::Clamp( GetTimeMin(), GetTimeMax(), _Param );

		const size_t Index0 = Cast( size_t, Math::Floor( Parameter ) );

		// In case the index is the last point.
		if( Index0 == GetControlPointsCount() - 1 )
			return _ToInterpolate.back();


		const size_t Index1 = Index0 + 1;

		// Bring back the parameter between 0 and 1.
		const float Time = ( Parameter - m_Times[Index0] ) / ( m_Times[Index1] - m_Times[Index0] );

		return Math::Lerp( _ToInterpolate[Index0], _ToInterpolate[Index1], Time );
	}

} // ae

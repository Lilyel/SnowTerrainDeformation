#include "Time.h"

#include <chrono>

namespace ae
{
	Time::Time() :
		m_MicroSeconds( 0 )
	{
	}
	Time::Time( const Time& _Time )
	{
		m_MicroSeconds = _Time.m_MicroSeconds;
	}
	Time::Time( Int64 _MicroSeconds )
	{
		m_MicroSeconds = _MicroSeconds;
	}

	void Time::SetSeconds( float _Seconds )
	{
		m_MicroSeconds = (Int64)( Cast( double, _Seconds ) * 1000000.0 );
	}
	void Time::AddSeconds( float _Seconds )
	{
		m_MicroSeconds += (Int64)( Cast( double, _Seconds ) * 1000000.0 );
	}
	float Time::AsSeconds() const
	{
		return m_MicroSeconds / 1000000.0f;
	}
	Time Time::Seconds( float _Seconds )
	{
		return Time( (Int64)( Cast( double, _Seconds ) * 1000000.0 ) );
	}

	void Time::SetMilliSeconds( Int32 _Milli )
	{
		m_MicroSeconds = Cast( Int64, _Milli ) * 1000;
	}
	void Time::AddMilliSeconds( Int32 _Milli )
	{
		m_MicroSeconds += Cast( Int64, _Milli ) * 1000;
	}
	Int32 Time::AsMilliSeconds() const
	{
		return (Int32)( m_MicroSeconds / 1000 );
	}
	Time Time::MilliSeconds( Int32 _Milli )
	{
		return Time( Cast( Int64, _Milli ) * 1000 );
	}

	void Time::SetMicroSeconds( Int64 _Micro )
	{
		m_MicroSeconds = _Micro;
	}
	void Time::AddMicroSeconds( Int64 _Micro )
	{
		m_MicroSeconds = _Micro;
	}
	Int64 Time::AsMicroSeconds() const
	{
		return m_MicroSeconds;
	}
	Time Time::MicroSeconds( Int64 _Micro )
	{
		return Time( _Micro );
	}
	
	Time Time::GetTick()
	{
        const std::chrono::high_resolution_clock::time_point Now = std::chrono::high_resolution_clock::now();
        const std::chrono::high_resolution_clock::time_point NowMs = std::chrono::time_point_cast<std::chrono::microseconds>( Now );
        const std::chrono::microseconds NowEpoch = std::chrono::duration_cast<std::chrono::microseconds>( NowMs.time_since_epoch() );

        return Time( NowEpoch.count() );
	}
    
} // ae
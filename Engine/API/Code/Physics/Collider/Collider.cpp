#include "Collider.h"


namespace ae
{
	Collider::Collider() : 
		m_Type( Type::None )
	{
	}
	Bool Collider::Intersects( const Collider& ) const
	{
		return False;
	}
	Bool Collider::Intersects( HitResult&, const Collider& ) const
	{
		return False;
	}
} // ae

#include "Vertex3D.h"

namespace ae
{

	Vertex3D::Vertex3D()
	{
	}
	Vertex3D::Vertex3D( const Vector3& _Position ) :
		Position( _Position )
	{
	}
	Vertex3D::Vertex3D( const Vector3& _Position, const ae::Color& _Color ) :
		Position( _Position ),
		Color( _Color )
	{
	}
	Vertex3D::Vertex3D( const Vector3& _Position, const ae::Color& _Color, const Vector2& _UV ) :
		Position( _Position ),
		Color( _Color ),
		UV( _UV )
	{
	}

	Vertex3D::Vertex3D( const Vector3& _Position, const ae::Color& _Color, const Vector2& _UV, const Vector3& _Normal ) :
		Position( _Position ),
		Color( _Color ),
		UV( _UV ),
		Normal( _Normal )
	{
	}

	inline Bool Vertex3D::operator==( const Vertex3D& _VertexB ) const
	{
		return ( Position == _VertexB.Position && Color == _VertexB.Color && UV == _VertexB.UV );
	}

	inline Bool Vertex3D::operator!=( const Vertex3D& _VertexB ) const
	{
		return ( Position != _VertexB.Position || Color != _VertexB.Color || UV != _VertexB.UV );
	}



    std::string ToString( const Vertex3D& _Vertex )
    {
        return std::string( "Position(" ) + ae::ToString( _Vertex.Position )
            + std::string( ") Color(" ) + ae::ToString( _Vertex.Color )
            + std::string( ") Normal(" ) + ae::ToString( _Vertex.Normal )
            + std::string( ") UV(" ) + ae::ToString( _Vertex.UV ) + ")";
    }

} // ae


std::ostream& operator<<( std::ostream& os, const ae::Vertex3D& _Vertex )
{
    os << ae::ToString( _Vertex );

    return os;
}

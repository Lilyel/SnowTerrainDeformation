#include "Vertex2D.h"

namespace ae
{
	Vertex2D::Vertex2D()
	{
	}
	Vertex2D::Vertex2D( const Vector2& _Position ) :
		Position( _Position )
	{
	}
	Vertex2D::Vertex2D( const Vector2& _Position, const ae::Color& _Color ) :
		Position( _Position ),
		Color( _Color )
	{
	}
	Vertex2D::Vertex2D( const Vector2& _Position, const ae::Color& _Color, const Vector2& _UV ) :
		Position( _Position ),
		Color( _Color ),
		UV( _UV )
	{
	}


	inline Bool Vertex2D::operator==( const Vertex2D& _VertexB ) const
	{
		return ( Position == _VertexB.Position && Color == _VertexB.Color && UV == _VertexB.UV );
	}

	inline Bool Vertex2D::operator!=( const Vertex2D& _VertexB ) const
	{
		return ( Position != _VertexB.Position || Color != _VertexB.Color || UV != _VertexB.UV );
	}



    std::string ToString( const Vertex2D& _Vertex )
    {
        return std::string( "Position(" ) + ae::ToString( _Vertex.Position )
            + std::string( ") Color(" ) + ae::ToString( _Vertex.Color )
            + std::string( ") UV(" ) + ae::ToString( _Vertex.UV ) + ")";
    }

} // ae


std::ostream& operator<<( std::ostream& os, const ae::Vertex2D& _Vertex )
{
    os << ae::ToString( _Vertex );

    return os;
}

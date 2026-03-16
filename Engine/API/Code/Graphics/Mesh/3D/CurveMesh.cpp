#include "CurveMesh.h"

#include "../../../Maths/Curve/Curve.h"

#include "../../Material/CurveMaterial.h"
#include "../../../Toolbox/BitOperations/BitOperations.h"
#include "../../../Editor/TypesToEditor/CurveMeshToEditor.h"

#include "../../../Aero/Aero.h"

namespace ae
{

	CurveMesh::CurveMesh( const Curve& _Curve, Uint32 _PointCount ) :
		Mesh3D( _PointCount, _PointCount ),
		m_DrawControlCurve( False ),
		m_DrawCurve( True ),
		m_PointCounts( _PointCount )
	{
		SetPrimitiveType( PrimitiveType::LineStrip );
		SetAttributePointerTags( AttributePointer::Position | AttributePointer::TexCoords );
		SetCurve( _Curve, _PointCount );

		SetMaterial( *Aero.GetResourcesManager().GetDefaultCurveMaterial() );

		SetName( std::string( "CurveMesh_" ) + std::to_string( GetObjectID() ) );
	}

	void CurveMesh::SetCurve( const Curve& _Curve, Uint32 _PointCount )
	{		
		m_Curve = &_Curve;
		m_PointCounts = _PointCount;

		const Uint32 ControlPointCount = m_Curve->GetControlPointsCount();
		const Uint32 FinalPointCount = ( m_DrawCurve ? m_PointCounts : 0 ) + ( m_DrawControlCurve ? ControlPointCount : 0 );

		m_Vertices.resize( Cast( size_t, FinalPointCount ) );
		m_Indices.resize( Cast( size_t, FinalPointCount ) );

		Uint32 VertexIndex = 0;

		if( m_DrawCurve )
		{
			const float MinTime = m_Curve->GetTimeMin();
			const float Domain = m_Curve->GetTimeMax() - MinTime;

			float Step = ( 1.0f / Cast( float, m_PointCounts - 1 ) ) * Domain;

			// Send interpolated points.
			for( Uint32 p = 0; p < m_PointCounts; p++, VertexIndex++ )
			{
				float Time = MinTime + Cast( float, p ) * Step;

				SetVertex( VertexIndex, Vertex3D( m_Curve->GetPointAtParam( Time ) ) );
				SetIndice( VertexIndex, VertexIndex );
			}
		}

		if( m_DrawControlCurve )
		{
			// Send control curve and tag UV to 1 to recognize it in the shader.
			for( Uint32 cp = 0; cp < ControlPointCount; cp++, VertexIndex++ )
			{
				SetVertex( VertexIndex, Vertex3D( m_Curve->GetControlPoint( cp ), Color::White, Vector2::One ) );
				SetIndice( VertexIndex, VertexIndex );
			}
		}

		ApplyChanges();
	}

	Uint32 CurveMesh::GetPointCount() const
	{
		return m_PointCounts;
	}

	void CurveMesh::SetPointCount( Uint32 _PointCount )
	{
		m_PointCounts = _PointCount;
		Update();
	}

	Bool CurveMesh::IsControlCurveDrawn() const
	{
		return m_DrawControlCurve;
	}

	void CurveMesh::SetDrawControlCurve( Bool _Draw )
	{
		m_DrawControlCurve = _Draw;
		Update();
	}

	Bool CurveMesh::IsCurveDrawn() const
	{
		return m_DrawCurve;
	}

	void CurveMesh::SetDrawCurve( Bool _Draw )
	{
		m_DrawCurve = _Draw;
		Update();
	}


	const Curve& CurveMesh::GetCurve() const
	{
		return *m_Curve;
	}


	void CurveMesh::Update()
	{
		SetCurve( *m_Curve, m_PointCounts );
	}

	void CurveMesh::ToEditor()
	{
		Mesh3D::ToEditor();
		priv::ui::CurveMeshToEditor( *this );
	}

} // ae

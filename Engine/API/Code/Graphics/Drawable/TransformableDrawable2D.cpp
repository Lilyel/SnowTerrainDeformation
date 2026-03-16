#include "TransformableDrawable2D.h"

#include "../Shader/Shader.h"

namespace ae
{
	void ae::TransformableDrawable2D::SendTransformToShader( const Shader& _Shader ) const
	{
		const std::string ModelParameterName = Material::GetDefaultParameterName( Material::DefaultParameters::Model2DMatrix );
		_Shader.SetMatrix3x3( _Shader.GetUniformLocation( ModelParameterName ), const_cast<TransformableDrawable2D*>(this)->GetMatrix() );
	}
}

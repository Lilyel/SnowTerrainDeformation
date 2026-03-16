#include "TransformableDrawable3D.h"

#include "../Shader/Shader.h"

namespace ae
{
	void TransformableDrawable3D::SendTransformToShader( const Shader& _Shader ) const
	{
		const std::string ModelParameterName = Material::GetDefaultParameterName( Material::DefaultParameters::Model3DMatrix );
		_Shader.SetMatrix4x4( _Shader.GetUniformLocation( ModelParameterName ), const_cast<TransformableDrawable3D*>( this )->GetMatrix() );
	}

} // ae
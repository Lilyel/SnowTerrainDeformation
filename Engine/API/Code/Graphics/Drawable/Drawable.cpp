#include "Drawable.h"

#include "../../Aero/Aero.h"

#include "../../Debugging/Debugging.h"
#include "../Material/Material.h"
#include "../Renderer/Renderer.h"
#include "../../Toolbox/BitOperations/BitOperations.h"

#include <exception>

namespace ae
{
	Drawable::Drawable( BufferType _BufferType, AttributePointer _AttributePointerTags ) :
		m_IndicesCount( 0 ),
		m_VerticesCount( 0 ),
		m_MaterialRef( nullptr ),
		m_BufferType( _BufferType ),
		m_AttributePointerTags( _AttributePointerTags ),
		m_PrimitiveType( PrimitiveType::Triangles ),
		m_BlendMode( BlendMode::BlendAlpha )
	{
        if( !Aero.CheckContext() )
            return;

		// Create OpenGL buffers for vertices and indices link with a VertexArrayBuffer.
		glGenVertexArrays( 1, &m_VertexArrayObject );
		AE_ErrorCheckOpenGLError();

		glGenBuffers( 1, &m_VertexBufferObject );
		AE_ErrorCheckOpenGLError();

		glGenBuffers( 1, &m_ElementsArrayObject );
		AE_ErrorCheckOpenGLError();
	}

	Drawable::Drawable( const Vertex3DArray& _Vertices, BufferType _BufferType, AttributePointer _AttributePointerTags ) :
		Drawable( _BufferType, _AttributePointerTags )
	{
		UpdateVerticesBuffer( _Vertices );
	}

	Drawable::Drawable( const Vertex3DArray& _Vertices, const IndexArray& _Indices, BufferType _BufferType, AttributePointer _AttributePointerTags ) :
		Drawable( _BufferType, _AttributePointerTags )
	{
		UpdateBuffers( _Vertices, _Indices );
	}

	Drawable::Drawable( const Vertex2DArray& _Vertices, BufferType _BufferType, AttributePointer _AttributePointerTags ) :
		Drawable( _BufferType, _AttributePointerTags )
	{
		UpdateVerticesBuffer( _Vertices );
	}

	Drawable::Drawable( const Vertex2DArray& _Vertices, const IndexArray& _Indices, BufferType _BufferType, AttributePointer _AttributePointerTags ) :
		Drawable( _BufferType, _AttributePointerTags )
	{
		UpdateBuffers( _Vertices, _Indices );
	}

	Drawable::~Drawable()
	{
		DeleteInstanceMaterial();

        if( !Aero.CheckContext() )
            return;

		if( m_ElementsArrayObject )
		{
			glDeleteBuffers( 1, &m_ElementsArrayObject );
			AE_ErrorCheckOpenGLError();
			m_ElementsArrayObject = 0;
		}

		if( m_VertexBufferObject )
		{
			glDeleteBuffers( 1, &m_VertexBufferObject );
			AE_ErrorCheckOpenGLError();
			m_VertexBufferObject = 0;
		}

		if( m_VertexArrayObject )
		{
			glDeleteVertexArrays( 1, &m_VertexArrayObject );
			AE_ErrorCheckOpenGLError();
			m_VertexArrayObject = 0;
		}
	}


	void Drawable::UpdateBuffers( const Vertex3DArray& _Vertices, const IndexArray& _Indices, Bool _BindArrayBuffer )
	{
        if( !Aero.CheckContext() )
            return;

		// If not alrady done, bind the vertex array buffer to apply the next settings to it.
		if( _BindArrayBuffer )
		{
			glBindVertexArray( m_VertexArrayObject );
			AE_ErrorCheckOpenGLError();
		}

		UpdateVerticesBuffer( _Vertices, False );
		UpdateIndicesBuffer( _Indices, False );

		// Once we have finished, unbind the vertex array object.
		if( _BindArrayBuffer )
		{
			glBindVertexArray( 0 );
			AE_ErrorCheckOpenGLError();
		}
	}

	void Drawable::UpdateBuffers( const Vertex2DArray& _Vertices, const IndexArray& _Indices, Bool _BindArrayBuffer )
	{
        if( !Aero.CheckContext() )
            return;

		// If not alrady done, bind the vertex array buffer to apply the next settings to it.
		if( _BindArrayBuffer )
		{
			glBindVertexArray( m_VertexArrayObject );
			AE_ErrorCheckOpenGLError();
		}

		UpdateVerticesBuffer( _Vertices, False );
		UpdateIndicesBuffer( _Indices, False );

		// Once we have finished, unbind the vertex array object.
		if( _BindArrayBuffer )
		{
			glBindVertexArray( 0 );
			AE_ErrorCheckOpenGLError();
		}
	}

	void Drawable::UpdateVerticesBuffer( const Vertex3DArray& _Vertices, Bool _BindArrayBuffer )
	{
        if( !Aero.CheckContext() )
            return;

		m_VerticesCount = Cast( Uint32, _Vertices.size() );

		// If not alrady done, bind the vertex array buffer to apply the next settings to it.
		if( _BindArrayBuffer )
		{
			glBindVertexArray( m_VertexArrayObject );
			AE_ErrorCheckOpenGLError();
		}

		// Bind the vertex buffer to apply the changes to it.
		glBindBuffer( GL_ARRAY_BUFFER, m_VertexBufferObject );
		AE_ErrorCheckOpenGLError();

		// Bind the new data.
		glBufferData( GL_ARRAY_BUFFER, _Vertices.size() * sizeof( Vertex3D ), _Vertices.data(), Cast( GLenum, m_BufferType ) );
		AE_ErrorCheckOpenGLError();


		// Update attributes for 3D object.

		// Positions.
		if( BitOp::BitOpAnd( m_AttributePointerTags, AttributePointer::Position ) )
		{
			glEnableVertexAttribArray( 0 ); AE_ErrorCheckOpenGLError();
			glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex3D ), 0 ); AE_ErrorCheckOpenGLError();
		}

		// Colors.
		if( BitOp::BitOpAnd( m_AttributePointerTags, AttributePointer::Color ) )
		{
			glEnableVertexAttribArray( 1 ); AE_ErrorCheckOpenGLError();
			glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof( Vertex3D ), (GLvoid*)sizeof( Vector3 ) ); AE_ErrorCheckOpenGLError();
		}

		// Tex coords.
		if( BitOp::BitOpAnd( m_AttributePointerTags, AttributePointer::TexCoords ) )
		{
			glEnableVertexAttribArray( 2 ); AE_ErrorCheckOpenGLError();
			glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex3D ), (GLvoid*)( sizeof( Vector3 ) + sizeof( Color ) ) ); AE_ErrorCheckOpenGLError();
		}

		// Normals.
		if( BitOp::BitOpAnd( m_AttributePointerTags, AttributePointer::Normals ) )
		{
			glEnableVertexAttribArray( 3 ); AE_ErrorCheckOpenGLError();
			glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex3D ), (GLvoid*)( sizeof( Vector3 ) + sizeof( Color ) + sizeof( Vector2 ) ) ); AE_ErrorCheckOpenGLError();
		}

		// Once we have finished, unbind the vertex array object.
		if( _BindArrayBuffer )
		{
			glBindVertexArray( 0 );
			AE_ErrorCheckOpenGLError();
		}
	}

	void Drawable::UpdateVerticesBuffer( const Vertex2DArray& _Vertices, Bool _BindArrayBuffer )
	{
        if( !Aero.CheckContext() )
            return;

		m_VerticesCount = Cast( Uint32, _Vertices.size() );

		// If not alrady done, bind the vertex array buffer to apply the next settings to it.
		if( _BindArrayBuffer )
		{
			glBindVertexArray( m_VertexArrayObject );
			AE_ErrorCheckOpenGLError();
		}

		// Bind the vertex buffer to apply the changes to it.
		glBindBuffer( GL_ARRAY_BUFFER, m_VertexBufferObject );
		AE_ErrorCheckOpenGLError();

		// Bind the new data.
		glBufferData( GL_ARRAY_BUFFER, _Vertices.size() * sizeof( Vertex2D ), _Vertices.data(), Cast( GLenum, m_BufferType ) );
		AE_ErrorCheckOpenGLError();


		// Update attributes for 2D object.

		// Positions.
		if( BitOp::BitOpAnd( m_AttributePointerTags, AttributePointer::Position ) )
		{
			glEnableVertexAttribArray( 0 ); AE_ErrorCheckOpenGLError();
			glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex2D ), (GLvoid*)0 ); AE_ErrorCheckOpenGLError();
		}

		// Colors.
		if( BitOp::BitOpAnd( m_AttributePointerTags, AttributePointer::Color ) )
		{
			glEnableVertexAttribArray( 1 ); AE_ErrorCheckOpenGLError();
			glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof( Vertex2D ), (GLvoid*)sizeof( Vector2 ) ); AE_ErrorCheckOpenGLError();
		}

		// Tex coords.
		if( BitOp::BitOpAnd( m_AttributePointerTags, AttributePointer::TexCoords ) )
		{
			glEnableVertexAttribArray( 2 ); AE_ErrorCheckOpenGLError();
			glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex2D ), (GLvoid*)( sizeof( Vector2 ) + sizeof( Color ) ) );  AE_ErrorCheckOpenGLError();
		}


		// Once we have finished, unbind the vertex array object.
		if( _BindArrayBuffer )
		{
			glBindVertexArray( 0 );
			AE_ErrorCheckOpenGLError();
		}
	}

	void Drawable::UpdateIndicesBuffer( const IndexArray& _Indices, Bool _BindArrayBuffer )
	{
        if( !Aero.CheckContext() )
            return;

		m_IndicesCount = Cast( Uint32, _Indices.size() );

		// If not alrady done, bind the vertex array buffer to apply the next settings to it.
		if( _BindArrayBuffer )
		{
			glBindVertexArray( m_VertexArrayObject );
			AE_ErrorCheckOpenGLError();
		}

		// Bind the element buffer to apply changes to it.
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ElementsArrayObject );
		AE_ErrorCheckOpenGLError();

		// Bind the new data.
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_IndicesCount * sizeof( Uint32 ), _Indices.data(), Cast( GLenum, m_BufferType ) );
		AE_ErrorCheckOpenGLError();

		// Once we have finished, unbind the vertex array object.
		if( _BindArrayBuffer )
		{
			glBindVertexArray( 0 );
			AE_ErrorCheckOpenGLError();
		}
	}


	Uint32 Drawable::GetVertexBufferObject() const
	{
		return m_VertexBufferObject;
	}
	Uint32 Drawable::GetVertexArrayObject() const
	{
		return m_VertexArrayObject;
	}
	Uint32 Drawable::GetElementsArrayObject() const
	{
		return m_ElementsArrayObject;
	}
	
	Uint32 Drawable::GetVerticesCount() const
	{
		return m_VerticesCount;
	}

	Uint32 Drawable::GetIndicesCount() const
	{
		return m_IndicesCount;
	}

	Uint32 Drawable::GetPrimitivesCount() const
	{
		switch( GetPrimitiveType() )
		{
		case PrimitiveType::Points:
			return GetIndicesCount();
					
		case PrimitiveType::Lines:
			return GetIndicesCount() / 2;

		case PrimitiveType::LineStrip:
			return GetIndicesCount() - 1;

		case PrimitiveType::LineLoop:
			return GetIndicesCount();

		case PrimitiveType::Triangles:
			return GetIndicesCount() / 3;

		case PrimitiveType::TriangleStrip:
		case PrimitiveType::TriangleFan:
			return GetIndicesCount() - 2;

		case PrimitiveType::Quads:
			return GetIndicesCount() / 4;

		case PrimitiveType::QuadStip:
			return GetIndicesCount() / 2 - 1;

		case PrimitiveType::Polygon:
			return 1;

		case PrimitiveType::Patches:
			return 1;

		default:
			return 0;
		}
	}

	Drawable::BufferType Drawable::GetBufferType() const
	{
		return m_BufferType;
	}


	void Drawable::SetBufferType( BufferType _BufferType )
	{
		m_BufferType = _BufferType;
	}

	const BlendMode& Drawable::GetBlendMode() const
	{
		return m_BlendMode;
	}

	Drawable::AttributePointer Drawable::GetAttributePointerTags() const
	{
		return m_AttributePointerTags;
	}

	void Drawable::SetAttributePointerTags( AttributePointer _AttributePointerTags )
	{
		m_AttributePointerTags = _AttributePointerTags;
	}

	void Drawable::SetBlendMode( const BlendMode& _BlendMode )
	{
		m_BlendMode = _BlendMode;
	}

	PrimitiveType Drawable::GetPrimitiveType() const
	{
		return m_PrimitiveType;
	}

	void Drawable::SetPrimitiveType( PrimitiveType _PrimitiveType )
	{
		m_PrimitiveType = _PrimitiveType;
	}


	const Material& Drawable::GetMaterial() const
	{
		if( m_MaterialRef == nullptr )
			throw std::exception( "The drawable doesn't have a material" );

		return *m_MaterialRef;
	}

	Material& Drawable::GetMaterial()
	{
		if( m_MaterialRef == nullptr )
			throw std::exception( "The drawable doesn't have a material" );

		return *m_MaterialRef;
	}

	void Drawable::SetMaterial( Material& _Material )
	{
		DeleteInstanceMaterial();

		m_MaterialRef = &_Material;
	}

	void Drawable::SendMaterialToShader( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& _ImageUnit ) const
	{
		if( m_MaterialRef != nullptr )
			m_MaterialRef->SendParametersToShader( _Shader, _TextureUnit, _ImageUnit );
	}

	void Drawable::SendTransformToShader( const Shader& ) const
	{
	}

	void Drawable::OnDrawBegin( Renderer& ) const
	{
	}

	void Drawable::OnDrawEnd( Renderer& ) const
	{
	}

	void Drawable::DeleteInstanceMaterial()
	{
		if( m_MaterialRef != nullptr && m_MaterialRef->IsInstance() )
		{
			delete m_MaterialRef;
			m_MaterialRef = nullptr;
		}
	}

} // ae
#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Vertex/VertexArray.h"
#include "../Primitives/PrimitivesType.h"
#include "../Material/Material.h"
#include "../BlendMode/BlendMode.h"

#include "../../World/WorldObject/WorldObject.h"

#include "../Dependencies/OpenGL.h"

#include <vector>

namespace ae
{
	class Renderer;

	/// \ingroup graphics
	/// <summary>
	/// Basic class to draw elements with OpenGL.
	/// Contains the OpenGL informations for vertex and index buffers.
	/// </summary>
	class AERO_CORE_EXPORT Drawable : public WorldObject
	{
	public:
		/// <summary>Alias for array of Uint32 for better readability.</summary>
		using IndexArray = std::vector<Uint32>;

		/// <summary>Determine the frequency of the modifications of the buffers.</summary>
		enum class BufferType : GLenum
		{
			/// <summary>Buffers modified once and drawn many times.</summary>
			Static = GL_STATIC_DRAW,

			/// <summary>Buffers modified often and drawn many times.</summary>
			Dynamic = GL_DYNAMIC_DRAW,

			/// <summary>Buffers modified once and drawn a few times.</summary>
			Stream = GL_STREAM_DRAW,

			/// <summary>Default Buffer type for drawable.</summary>
			Default = Static
		};

		/// <summary>Enum used to specify which attribute pointer must be activated.</summary>
		enum class AttributePointer : Uint8
		{
			/// <summary>No attribute to activate.</summary>
			None,

			/// <summary>Correspond to the vertex position attribute.</summary>
			Position = 1,

			/// <summary>Correspond to the vertex color attribute.</summary>
			Color = Position << 1,

			/// <summary>Correspond to the vertex UV coordinates attribute.</summary>
			TexCoords = Color << 1,

			/// <summary>Correspond to the vertex normals attribute.</summary>
			Normals = TexCoords << 1,

			/// <summary>Default attributes for 3D drawables.</summary>
			Default3D = Position | Color | TexCoords | Normals,

			/// <summary>Default attributes for 2D drawables.</summary>
			Default2D = Position | Color | TexCoords,

			/// <summary>Default attributes for framebuffer drawables.</summary>
			DefaultFramebuffer = Position | TexCoords,
		};

	public:
		/// <summary>Build an empty drawable.</summary>
		explicit Drawable( BufferType _BufferType = BufferType::Default, AttributePointer _AttributePointerTags = AttributePointer::None );

		/// <summary>Build a mesh with vertices.</summary>
		/// <param name="_Vertices">Vertices to draw.</param>
		/// <param name="_BufferType">Type of buffer for vertex and indice buffer.</param>
		/// <param name="_AttributePointerTags">Which data pointer must be active for this drawable.</param>
		explicit Drawable( const Vertex3DArray& _Vertices, BufferType _BufferType = BufferType::Default, AttributePointer _AttributePointerTags = AttributePointer::Default3D );

		/// <summary>Build a mesh with vertices and indices.</summary>
		/// <param name="_Vertices">Vertices to draw.</param>
		/// <param name="_Indices">Indices of vertices of each triangles.</param>
		/// <param name="_BufferType">Type of buffer for vertex and indice buffer.</param>
		/// <param name="_AttributePointerTags">Which data pointer must be active for this drawable.</param>
		explicit Drawable( const Vertex3DArray& _Vertices, const IndexArray& _Indices, BufferType _BufferType = BufferType::Default, AttributePointer _AttributePointerTags = AttributePointer::Default3D );

		/// <summary>Build a mesh with vertices.</summary>
		/// <param name="_Vertices">Vertices to draw.</param>
		/// <param name="_BufferType">Type of buffer for vertex and indice buffer.</param>
		/// <param name="_AttributePointerTags">Which data pointer must be active for this drawable.</param>
		explicit Drawable( const Vertex2DArray& _Vertices, BufferType _BufferType = BufferType::Default, AttributePointer _AttributePointerTags = AttributePointer::Default2D );

		/// <summary>Build a mesh with vertices and indices.</summary>
		/// <param name="_Vertices">Vertices to draw.</param>
		/// <param name="_Indices">Indices of vertices of each triangles.</param>
		/// <param name="_BufferType">Type of buffer for vertex and indice buffer.</param>
		/// <param name="_AttributePointerTags">Which data pointer must be active for this drawable.</param>
		explicit Drawable( const Vertex2DArray& _Vertices, const IndexArray& _Indices, BufferType _BufferType = BufferType::Default, AttributePointer _AttributePointerTags = AttributePointer::Default2D );

		/// <summary>Destructor </summary>
		virtual ~Drawable();

		/// <summary>Update OpenGL vertices and indices buffers.</summary>
		/// <param name="_Vertices">The new vertices for the vertex buffer.</param>
		/// <param name="_Indices">The new indices for the indices buffer.</param>
		/// <param name="_BindArrayBuffer">Need to bind the vertex array buffer ?</param>
		void UpdateBuffers( const Vertex3DArray& _Vertices, const IndexArray& _Indices, Bool _BindArrayBuffer = True );

		/// <summary>Update OpenGL vertices and indices buffers.</summary>
		/// <param name="_Vertices">The new vertices for the vertex buffer.</param>
		/// <param name="_Indices">The new indices for the indices buffer.</param>
		/// <param name="_BindArrayBuffer">Need to bind the vertex array buffer ?</param>
		void UpdateBuffers( const Vertex2DArray& _Vertices, const IndexArray& _Indices, Bool _BindArrayBuffer = True );

		/// <summary>Update OpenGL vertices buffer.</summary>
		/// <param name="_Vertices">The new vertices for the vertex buffer.</param>
		/// <param name="_BindArrayBuffer">Need to bind the vertex array buffer ?</param>
		void UpdateVerticesBuffer( const Vertex3DArray& _Vertices, Bool _BindArrayBuffer = True );

		/// <summary>Update OpenGL vertices buffer.</summary>
		/// <param name="_Vertices">The new vertices for the vertex buffer.</param>
		/// <param name="_BindArrayBuffer">Need to bind the vertex array buffer ?</param>
		void UpdateVerticesBuffer( const Vertex2DArray& _Vertices, Bool _BindArrayBuffer = True );

		/// <summary>Update OpenGL indices.</summary>
		/// <param name="_Indices">The new indices for the indices buffer.</param>
		/// <param name="_BindArrayBuffer">Need to bind the vertex array buffer ?</param>
		void UpdateIndicesBuffer( const IndexArray& _Indices, Bool _BindArrayBuffer = True );

		/// <summary>Get the OpenGL vertex buffer ID.</summary>
		/// <returns>ID of OpenGL vertex buffer of the mesh.</returns>
		Uint32 GetVertexBufferObject() const;

		/// <summary>ID of OpenGL vertex array of the mesh.</summary>
		/// <returns></returns>
		Uint32 GetVertexArrayObject() const;

		/// <summary>Get the OpenGL elements array ID.</summary>
		/// <returns>ID of OpenGL elements array of the mesh.</returns>
		Uint32 GetElementsArrayObject() const;


		/// <summary>Get the vertices count.</summary>
		/// <returns>Count of vertices in the current vertex buffer.</returns>
		Uint32 GetVerticesCount() const;

		/// <summary>Get the indices count.</summary>
		/// <returns>Count of indices in the current indices buffer.</returns>
		Uint32 GetIndicesCount() const;

		/// <summary>Get the number of primitives (triangles, quads or lines) of the drawable.</summary>
		/// <returns>The current primitives count.</returns>
		Uint32 GetPrimitivesCount() const;


		/// <summary>Retrieve the current buffer type of vertex and indice buffer.</summary>
		/// <returns>Current type of buffer.</returns>
		BufferType GetBufferType() const;

		/// <summary>
		/// Set the current buffer type of vertex and indice buffer.<para/>
		/// Note that it will take effect only from the next update of the buffer.
		/// </summary>
		/// <param name="_BufferType">The new indices for the indices buffer.</param>
		void SetBufferType( BufferType _BufferType );


		/// <summary>Retrieve the current blend mode.</summary>
		/// <returns>The current blend mode.</returns>
		const BlendMode& GetBlendMode() const;

		/// <summary>Bit packed tags to know which attribute pointer is active.</summary>
		/// <returns>The tags of the active attribute pointers, packed.</returns>
		AttributePointer GetAttributePointerTags() const;

		/// <summary>
		/// Set the packed tags to know which attribute pointer must be active.<para/>
		/// Note that it will take effect only from the next update of the buffer.
		/// </summary>
		/// <param name="_AttributePointerTags">The new packed tags to toggle the attribute pointers.</param>
		void SetAttributePointerTags( AttributePointer _AttributePointerTags );


		/// <summary>Set the blend mode when rendering this drawable.</summary>
		/// <param name="_BlendMode">The new blend mode to apply.</param>
		void SetBlendMode( const BlendMode& _BlendMode );


		/// <summary>
		/// Retrieve the current primitive type of this drawable.<para/>
		/// The primitive type determine how to process the vertices and indices of the drawable.
		/// </summary>
		/// <returns>The current primitive type.</returns>
		PrimitiveType GetPrimitiveType() const;

		/// <summary>
		/// Set the primitive type of this drawable.<para/>
		/// The primitive type determine how to process the vertices and indices of the drawable.
		/// </summary>
		/// <param name="_PrimitiveType">The new primitive type to apply.</param>
		void SetPrimitiveType( PrimitiveType _PrimitiveType );


		/// <summary>Retrieve the current material of the drawable.</summary>
		/// <returns>The current material of the drawable.</returns>
		const Material& GetMaterial() const;

		/// <summary>Retrieve the current material of the drawable.</summary>
		/// <returns>The current material of the drawable.</returns>
		Material& GetMaterial();

		/// <summary>Set the current material for the drawable.</summary>
		/// <param name="_Material">The new material to apply to the drawable.</param>
		virtual void SetMaterial( Material& _Material );

		/// <summary>
		/// Send all the parameters stored in the material to the shader.
		/// The shader must be bound before calling this function.<para/>
		/// The texture unit is used with parameter that correspond to sampler uniforms.<para/>
		/// For texture parameters, the texture unit is activated, incremented then the texture is bound.
		/// </summary>
		/// <param name="_Shader">Shader to send the parameters to.</param>
		/// <param name="_TextureUnit">Texture unit to use with texture parameters bound as texture. Incremented for each texture sent.</param>
		/// <param name="_ImageUnit">Image unit to use with texture parameters bound as image. Incremented for each image sent.</param>
		void SendMaterialToShader( const Shader& _Shader, AE_InOut Uint32& _TextureUnit, AE_InOut Uint32& _ImageUnit ) const;

		/// <summary>
		/// Send the transform (3x3 matrix for TransformableDrawable2D, 4x4 matrix for TransformableDrawable3D) to the shader.
		/// The shader must be bound before calling this function.
		/// </summary>
		/// <param name="_Shader">Shader to send the parameters to.</param>
		virtual void SendTransformToShader( const Shader& _Shader ) const;

		/// <summary>Event call at the beggining of the draw function of the renderer.</summary>
		/// <param name="_Renderer">The renderer used to draw this object.</param>
		virtual void OnDrawBegin( Renderer& _Renderer ) const;

		/// <summary>Event call at the end of the draw function of the renderer.</summary>
		/// <param name="_Renderer">The renderer used to draw this object.</param>
		virtual void OnDrawEnd( Renderer& _Renderer ) const;

	protected:
		/// <summary>Free the memory of the material hold if it is an instance.</summary>
		void DeleteInstanceMaterial();

	protected:

		/// <summary>OpenGL vertex buffer. Hold data of vertex and elements buffers.</summary>
		Uint32 m_VertexBufferObject;

		/// <summary>OpenGL vertex array. Hold data of vertices.</summary>
		Uint32 m_VertexArrayObject;

		/// <summary>OpenGL elements array. Hold data of triangles.</summary>
		Uint32 m_ElementsArrayObject;

		/// <summary>Save of the vertices count for rendering purpose.</summary>
		Uint32 m_VerticesCount;

		/// <summary>Save of the indices count for rendering purpose.</summary>
		Uint32 m_IndicesCount;

		/// <summary>The drawable material.</summary>
		Material* m_MaterialRef;

		/// <summary>Type of the drawable's buffers, static, dynamic, ...</summary>
		BufferType m_BufferType;

		/// <summary>Bit packed tag to activate attribute pointers.</summary>
		AttributePointer m_AttributePointerTags;

		/// <summary>The method for drawing the vertices.</summary>
		PrimitiveType m_PrimitiveType;

		/// <summary>Blend setting for rendering.</summary>
		BlendMode m_BlendMode;
	};

} // ae

/// <summary>
/// Apply the '&' between <paramref name="_A"/> and <paramref name="_B"/>.<para/>
/// The two parameters are casted to the integer type provided in template parameter before operator.
/// </summary>
/// <returns>True if the result is different from 0, False otherwise.</returns>
inline ae::Drawable::AttributePointer operator&( const ae::Drawable::AttributePointer& _A, const ae::Drawable::AttributePointer& _B )
{
	return Cast( ae::Drawable::AttributePointer, static_cast<Uint8>( _A ) & static_cast<Uint8>( _B ) );
}


/// <summary>
/// Apply the '|' between <paramref name="_A"/> and <paramref name="_B"/>.<para/>
/// The two parameters are casted to the integer type provided in template parameter before operator.
/// </summary>
/// <returns>True if the result is different from 0, False otherwise.</returns>
inline ae::Drawable::AttributePointer operator|( const ae::Drawable::AttributePointer& _A, const ae::Drawable::AttributePointer& _B )
{
	return Cast( ae::Drawable::AttributePointer, static_cast<Uint8>( _A ) | static_cast<Uint8>( _B ) );
}
#ifndef _RENDERER_AERO_H_
#define _RENDERER_AERO_H_

#include "../../Toolbox/Toolbox.h"
#include "../Primitives/PrimitivesType.h"
#include "../Vertex/VertexArray.h"
#include "../Shader/Shader.h"
#include "../BlendMode/BlendMode.h"
#include "../DrawMode/DrawMode.h"
#include "../CullingMode/CullingMode.h"
#include "../DepthMode/DepthMode.h"
#include "../../Idioms/NotCopiable/NotCopiable.h"

namespace ae
{
	class Material;
	class Camera;
	class Drawable;

	/// \ingroup graphics
	/// <summary>
	///  Base class for every rendering.
	///  Implement basic OpenGl for render primitive.
	/// </summary>
	class AERO_CORE_EXPORT Renderer : public NotCopiable
	{
	public:
		
		/// <summary>Create a OpenGL rendering target.</summary>
		Renderer();

		/// <summary>Destroy OpenGL rendering target.</summary>
		virtual ~Renderer();
        
		/// <summary>Clear the current OpenGL buffer.</summary>
		/// <param name="_ClearColor">The color to apply after the clear.</param>
		virtual void Clear( const class Color& _ClearColor = ae::Color::Black );

		/// <summary>Draw an object to the render target.</summary>
		/// <param name="_Object">The object to draw.</param>
		/// <param name="_Camera">Optionnal camera. If null, the current active camera will be taken.</param>
		virtual void Draw( const Drawable& _Object, Camera* _Camera = nullptr );


		/// <summary>Draw an object to the render target.</summary>
		/// <param name="_Object">The object to draw.</param>
		/// <param name="_Material">Material to use instead of the object material.</param>
		/// <param name="_Camera">Optionnal camera. If null, the current active camera will be taken.</param>
		virtual void Draw( const Drawable& _Object, const Material& _Material, Camera* _Camera = nullptr );


		 /// <summary>Flush the current OpenGL buffer.</summary>
		virtual void Render();

		/// <summary>Send the vertex array of the object (vertex buffer + indices buffer) to OpenGL.</summary>
		/// <remarks>It is up to the user to bind a shader and set up its uniforms.</remarks>
		/// <param name="_Object">The object to draw.</param>
		/// <param name="_PrimitiveType">Type of the primitive.</param>
		void DrawVertexArray( const class Drawable& _Object, PrimitiveType _PrimitiveType = PrimitiveType::Triangles );


		/// <summary>
		/// Change the blending mode for the next draw calls.<para/>
		/// In case of framebuffer, the framebuffer must be bound to get affected.<para/>
		/// For the window, no framebuffer must be bound to get affected.
		/// </summary>
		/// <param name="_BlendMode">The new blend mode.</param>
		void SetBlendingMode( const BlendMode& _BlendMode );

		/// <summary>Change the draw mode for the next draw calls.</summary>
		/// <param name="_DrawMode">The new draw mode.</param>
		void SetDrawMode( const DrawMode& _DrawMode );

		/// <summary>Retrieve the draw mode of the renderer.</summary>
	    /// <returns>The current draw mode.</returns>
		DrawMode GetDrawMode() const;

		/// <summary>
		/// Set the draw mode to the default mode (DrawMode::Filled).<para/>
		/// Immediatly applied.
		/// </summary>
		void ResetDrawMode();

		/// <summary>
		/// Change the culling mode for the next draw calls.<para/>
		/// In case of framebuffer, the framebuffer must be bound to get affected.<para/>
		/// For the window, no framebuffer must be bound to get affected.
		/// </summary>
		/// <param name="_CullingMode">The new culling mode.</param>
		void SetCullingMode( const CullingMode& _CullingMode );

		/// <summary>Retrieve the culling mode of the renderer.</summary>
		/// <returns>The current culling mode.</returns>
		CullingMode GetCullingMode() const;

		/// <summary>
		/// Set the culling mode to the default mode (CullingMode::BackFaces).<para/>
		/// Immediatly applied.
		/// </summary>
		void ResetCullingMode();


		/// <summary>
		/// Change the depth mode for the next draw calls.<para/>
		/// In case of framebuffer, the framebuffer must be bound to get affected.<para/>
		/// For the window, no framebuffer must be bound to get affected.
		/// </summary>
		/// <param name="_DepthMode">The new depth mode.</param>
		void SetDepthMode( const DepthMode& _DepthMode );

		/// <summary>Retrieve the depth mode of the renderer.</summary>
		/// <returns>The current depth mode.</returns>
		DepthMode GetDepthMode() const;

		/// <summary>Set the depth mode to the default mode (DepthMode::Less).</summary>
		void ResetDepthMode();

		/// <summary>Get the width of the render target surface.</summary>
		virtual Uint32 GetWidth() const AE_IsVirtualPure;

		/// <summary>Get the width of the render target surface.</summary>
		virtual Uint32 GetHeight() const AE_IsVirtualPure;

	private:
		/// <summary>Send the world lights to the shader.</summary>
		/// <param name="_Shader">The shader to send the lights to.</param>
		void SendLightsToShader( const Shader& _Shader );

	protected:

		 /// <summary>Check if the count of vertex is compatible with the primitive chosen.</summary>
		 /// <param name="_Count">Count of vertices.</param>
		 /// <param name="_PrimitiveType">Type of the primitive.</param>
		 /// <returns>If the count of vertices match with the primitive.</returns>
		Bool CheckCountPrimitive( const Uint32 _Count, const PrimitiveType& _PrimitiveType ) const;


		/// <summary>Initialize OpenGL rendering.</summary>
		void InitializeRendering();


        /// <summary>Free the defaults shaders resources.</summary>
		void FreeResource();

		/// <summary>Apply the draw mode set for this renderer.</summary>
		void ApplyDrawMode() const;

		/// <summary>Apply the culling mode set for this renderer.</summary>
		void ApplyCullingMode() const;

		/// <summary>Apply the depth mode set for this renderer.</summary>
		void ApplyDepthMode() const;

		/// <summary>Apply every modes set for this render (culling, draw, depth, ...).</summary>
		void ApplyAllModes() const;

		/// <summary>Reset all modes to their default values (culling, draw, depth, ...).</summary>
		void ResetAllModes();

		/// <summary>Push OpenGL attributes of the settable modes.</summary>
		void SaveModes() const;

		/// <summary>Pop OpenGlattributes of the settables modes.</summary>
		void RestoreSavedModes() const;


	protected:		

		/// <summary>Draw mode of the renderer (wireframe, filled, ...).</summary>
		DrawMode m_DrawMode;

		/// <summary>Culling mode of the renderer (cull back faces, front faces, ...).</summary>
		CullingMode m_CullingMode;

		/// <summary>Depth mode for the renderer (disabled, less, less equal ...).</summary>
		DepthMode m_DepthMode;
	};

} // ae

#endif
#pragma once

#include "../../Toolbox/Toolbox.h"

#include "../Drawable/Drawable.h"
#include "../CubeMap/CubeMap.h"
#include "../Shader/ShaderParameter/ShaderParameterCubeMap.h"
#include "../Vertex/VertexArray.h"
#include "../DepthMode/DepthMode.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Draw support for cube map.<para/>
	/// The Skybox default shader is done in a way to draw the skybox the last.
	/// </summary>
	/// <seealso cref="CubeMap" />
	/// <seealso cref="Drawable" />
	class AERO_CORE_EXPORT Skybox : public Drawable
	{
	public:
		/// <summary>
		/// Setup a empty skybox.<para/>
		/// The cube map resource can be provided later.
		/// </summary>
		/// <param name="_NewMaterialInstance">
		/// Must create a new material instance for this sprite ?<para/>
		/// If set to False, the default 2D material is taken and will be shared with all others sprite and 2D shapes with the default material.
		/// </param>
		Skybox( Bool _NewMaterialInstance = True );

		/// <summary>Setup a skybox with the given <paramref name="_CubeMap"/></summary>
		/// <param name="_CubeMap">Cube map to use for the skybox.</param>
		/// <param name="_NewMaterialInstance">
		/// Must create a new material instance for this sprite ?<para/>
		/// If set to False, the default 2D material is taken and will be shared with all others sprite and 2D shapes with the default material.
		/// </param>
		Skybox( const CubeMap& _CubeMap, Bool _NewMaterialInstance = True );

		/// <summary>Set the cube map to use for the skybox.</summary>
		/// <param name="_CubeMap">New cube map to use.</param>
		void SetCubeMap( const CubeMap& _CubeMap );

		/// <summary>Set the current material for the drawable.</summary>
		/// <param name="_Material">The new material to apply to the drawable.</param>
		void SetMaterial( Material& _Material ) override;

		/// <summary>Retrieve the current cube map used for the skybox.</summary>
		/// <returns>The current cube map used for the skybox.</returns>
		const CubeMap* GetCubeMap() const;

		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor();

		/// <summary>Event call at the beggining of the draw function of the renderer.</summary>
		/// <param name="_Renderer">The renderer used to draw this object.</param>
		void OnDrawBegin( Renderer& _Renderer ) const override;

		/// <summary>Event call at the end of the draw function of the renderer.</summary>
		/// <param name="_Renderer">The renderer used to draw this object.</param>
		void OnDrawEnd( Renderer& _Renderer ) const override;

	private:
		/// <summary>Create the vertices and indices of the mesh that will hold the cube map.</summary>
		void SetupCubeMesh();

		/// <summary>Setup the material to default skybox material.</summary>
		void SetupMaterial( Bool _NewMaterialInstance );

		/// <summary>Update the material shader parameter that hold the cube map texture.</summary>
		void UpdateMaterialCubeMap();

		/// <summary>Setup a triangle.</summary>
		/// <param name="_TriangleIndex">Triangle index to modify.</param>
		/// <param name="_Values">New indices for the triangle.</param>
		void SetTriangleIndices( const Uint32 _TriangleIndex, const Uint32 _Values[3] );

	private:
		/// <summary>Reference to a cube map resource to use.</summary>
		const CubeMap* m_CubeMap;

		/// <summary>Vertices to render that hold the cube map.</summary>
		Vertex3DArray m_Vertices;
		/// <summary>Indices of the triangles made with the vertices.</summary>
		IndexArray m_Indices;

		/// <summary>Material shader parameter that hold the cube map texture.</summary>
		ShaderParameterCubeMap* m_CubeMapParameter;

		/// <summary>Save of the renderer depth mode to restore it after the draw.</summary>
		mutable DepthMode m_SavedRendererDepthMode;
	};
} // ae

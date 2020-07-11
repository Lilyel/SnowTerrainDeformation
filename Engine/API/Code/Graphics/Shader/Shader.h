#ifndef _SHADER_AERO_H_
#define _SHADER_AERO_H_

#include "../../Toolbox/Toolbox.h"

#include "../../Resources/Resource/Resource.h"

#include <string>
#include <unordered_map>

namespace ae
{
	class Matrix4x4;
	class Matrix3x3;
	class Vector3;
	class Vector2;
	class Color;

	/// \ingroup graphics
	/// <summary>
	/// Interface for the shader OpenGL system.<para/>
	/// Allow to create a shader and set its parameters.
	/// </summary>
	/// <seealso cref="Material"/>
	class AERO_CORE_EXPORT Shader : public Resource
	{
		friend void priv::FreeResource<Shader>( Shader& _Shader );

	public:
		/// <summary>Alias for map string/int of uniform locations (name/location).</summary>
		using LocationsMap = std::unordered_map<std::string, Int32>;

	public:
		/// <summary>Create an OpenGL shader from shader files. </summary>
		/// <param name="_VertexPath">The vertex file path.</param>
		/// <param name="_FragmentPath">The fragment file path.</param>
		/// <param name="_GeometryPath">The geometry file shader (optional).</param>
		/// <param name="_TesselationControlPath">The tesselation control file shader (optional).</param>
		/// <param name="_TesselationEvaluationPath">The tesselation evaluation file shader (optional).</param>
		Shader( const std::string& _VertexPath, const std::string& _FragmentPath, const std::string& _GeometryPath = "", 
				const std::string& _TesselationControlPath = "", const std::string& _TesselationEvaluationPath = "" );

		/// <summary>Create an OpenGL compute shader from shader file. </summary>
		/// <param name="_VertexPath">The compute file path.</param>
		Shader( const std::string& _ComputePath );

		/// <summary>Destroy the OpenGL shader</summary>
		~Shader();

		/// <summary>
		/// Bind the shader to the rendering system.
		/// Draw call after this call will use this shader.
		/// </summary>
		void Bind() const;
		/// <summary>
		/// Unbinds the shader from the rendering system.
		/// </summary>
		void Unbind() const;


		/// <summary>Set a Bool uniform variable in the shader</summary>
		/// <param name="_Location">The location in the shader of the uniform variable.</param>
		/// <param name="_Value">The value to set the variable with.</param>
		static void SetBool( Int32 _Location, Bool _Value );

		/// <summary>Set a Int32 uniform variable in the shader</summary>
		/// <param name="_Location">The location in the shader of the uniform variable.</param>
		/// <param name="_Value">The value to set the variable with.</param>
		static void SetInt( Int32 _Location, Int32 _Value );

		/// <summary>Set a float uniform variable in the shader</summary>
		/// <param name="_Location">The location in the shader of the uniform variable.</param>
		/// <param name="_Value">The value to set the variable with.</param>
		static void SetFloat( Int32 _Location, float _Value );

		/// <summary>Set a Matrix4x4 uniform variable in the shader</summary>
		/// <remarks>
		/// Note that the Aero matrices are row-major and OpenGL is column-major.
		/// If you want to use matrices in shader like an OpenGL classic matrix you
		/// need to set <paramref name="_Tranpose"/> to True.
		/// </remarks>
		/// <param name="_Location">The location in the shader of the uniform variable.</param>
		/// <param name="_Value">The value to set the variable with.</param>
		/// <param name="_Tranpose">True if its needed to transpose the matrix when sending to OpenGL.</param>
		static void SetMatrix4x4( Int32 _Location, const Matrix4x4& _Value, Bool _Tranpose = False );

		/// <summary>Set a Matrix3x3 uniform variable in the shader.</summary>
		/// <remarks>
		/// Note that the Aero matrices are row-major and OpenGL is column-major.<para/>
		/// If you want to use matrices in shader like an OpenGL classic matrix you
		/// need to set <paramref name="_Tranpose"/> to True.
		/// </remarks>
		/// <param name="_Location">The location in the shader of the uniform variable.</param>
		/// <param name="_Value">The value to set the variable with.</param>
		/// <param name="_Tranpose">True if its needed to transpose the matrix when sending to OpenGL.</param>
		static void SetMatrix3x3( Int32 _Location, const Matrix3x3& _Value, Bool _Tranpose = False );

		/// <summary>Set a Vector3 uniform variable in the shader</summary>
		/// <param name="_Location">The location in the shader of the uniform variable.</param>
		/// <param name="_Value">The value to set the variable with.</param>
		static void SetVector3( Int32 _Location, const Vector3& _Value );

		/// <summary>Set a Vector2 uniform variable in the shader</summary>
		/// <param name="_Location">The location in the shader of the uniform variable.</param>
		/// <param name="_Value">The value to set the variable with.</param>
		static void SetVector2( Int32 _Location, const Vector2& _Value );

		/// <summary>Set a Color uniform variable in the shader</summary>
		/// <param name="_Location">The location in the shader of the uniform variable.</param>
		/// <param name="_Value">The value to set the variable with.</param>
		static void SetColor( Int32 _Location, const Color& _Value );


		/// <summary>Retrieve the location of a uniform variable from its name.</summary>
		/// <param name="_Name">The name of the uniform variable.</param>
		/// <returns>The location of the variable in the shader.</returns>
		Int32 GetUniformLocation( const std::string& _Name ) const;

		/// <summary>Get the OpenGL program ID of the shader.</summary>
		/// <returns>Program ID of the shader.</returns>
		Uint32 GetProgramID() const;

		/// <summary>Set the name of the object.</summary>
		/// <param name="_NewName">The new name to apply to the object.</param>
		void SetName( const std::string& _NewName ) final;

		/// <summary>
		/// Recompile shaders file provided in constructor.<para/>
		/// Allow to update modified shader at runtime.
		/// </summary>
		void Compile() const;

		/// <summary>Retrieve the path to the vertex file shader.</summary>
		/// <returns>Path to the vertex file shader.</returns>
		const std::string& GetVertexFile() const;

		/// <summary>Retrieve the path to the fragment file shader.</summary>
		/// <returns>Path to the fragment file shader.</returns>
		const std::string& GetFragmentFile() const;

		/// <summary>Retrieve the path to the geometry file shader.</summary>
		/// <returns>Path to the geometry file shader.</returns>
		const std::string& GetGeometryFile() const;

		/// <summary>Retrieve the path to the tesselation control file shader.</summary>
		/// <returns>Path to the tesselation control file shader.</returns>
		const std::string& GetTesselationControlFile() const;

		/// <summary>Retrieve the path to the tesselation evaluation file shader.</summary>
		/// <returns>Path to the tesselation evaluation file shader.</returns>
		const std::string& GetTesselationEvaluationFile() const;

		/// <summary>Retrieve the path to the compute file shader.</summary>
		/// <returns>Path to the compute file shader.</returns>
		const std::string& GetComputeFile() const;

		/// <summary>Remove all save uniforms location.</summary>
		void ClearLocationsCached() const;

		/// <summary>Retrieve the saved uniforms location.</summary>
		/// <returns>Saved uniforms location.</returns>
		const LocationsMap& GetCachedLocations();

		/// <summary>
		/// Execute the compute shader.<para/>
		/// Must be bound with the Bind() method before.<para/>
		/// Effective only if the shader is a compute shader.
		/// </summary>
		/// <param name="_CountGroupsX">Number of work groups to launch in the X dimension.</param>
		/// <param name="_CountGroupsY">Number of work groups to launch in the Y dimension</param>
		/// <param name="_CountGroupsZ">Number of work groups to launch in the Z dimension</param>
		void Dispatch( Uint32 _CountGroupsX, Uint32 _CountGroupsY = 1, Uint32 _CountGroupsZ = 1 ) const;


		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		void ToEditor() override;

	private:
		/// <summary>A shader from a file and retrieve an OpenGL ID for the shader. </summary>
		/// <param name="_ShaderPath">The shader file path.</param>
		/// <param name="_ShaderType">Type of the shader.</param>
		/// <returns>OpenGL ID of the compiled shader.</returns>
		Uint32 CompileShader( const std::string& _ShaderPath, Uint32 _ShaderType ) const;

		/// <summary>Attach and link the compiled shaders with the currently bound program.</summary>
		void LinkShaders() const;

		/// <summary>Destroy compiled shaders.</summary>
		void DeleteShaders() const;

		/// <summary>Create OpenGL shader object.</summary>
		void CreateShader();

		/// <summary>
		/// Free OpenGL shader program.
		/// </summary>
		void FreeResource();

		/// <summary>Detach the compiled shaders from the program if there are valid.</summary>
		void DetachShaders() const;

		/// <summary>
		/// Parse shader code to replace #include directive with the file content the aim to.<para/>
		/// Can fail if the files don't exists or if the #include directive is not well written.<para/>
		/// Origin path for includes is the original file path.
		/// </summary>
		/// <param name="_ShaderContent">The shader to parse.</param>
		/// <param name="_ShaderPath">The path to the shader to parse.</param>
		/// <param name="_RemoveFileFromPath">Must remove last part of the path ? (Everything after the last '/').</param>
		/// <param name="_IncludeHistory">Keep track of the included file to avoid duplications.</param>
		/// <returns>True if the parsing was sucessfull, False otherwise.</returns>
		Bool ProcessIncludes( AE_InOut std::string& _ShaderContent, const std::string& _ShaderPath, std::vector<std::string>& _IncludeHistory ) const;

		/// <summary>Retrieve the entire content of a file.</summary>
		/// <param name="_Content">The content of the file.</param>
		/// <param name="_Path">Path to the file to read.</param>
		/// <returns>True if the reading was sucessfull, False otherwise.</returns>
		Bool ReadEntireFile( AE_Out std::string& _Content, const std::string& _Path ) const;

		/// <summary>Remove the part after the last '/'.</summary>
		/// <param name="_Path">The path to process.</param>
		void RemoveFileFromPath( AE_InOut std::string& _Path ) const;

		/// <summary>Check if the file is not already included.</summary>
		/// <param name="_Path">The path to check?</param>
		/// <param name="_IncludeHistory">The history of the includes.</param>
		/// <returns>True if the path has already been included, False otherwise.</returns>
		Bool CheckIncludeHistory( const std::string& _Path, const std::vector<std::string>& _IncludeHistory ) const;

	private:
		/// <summary>OpenGL shader program ID.</summary>
		Uint32 m_ProgramID;

		/// <summary>ID of the vertex shader.</summary>
		mutable Uint32 m_VertexID;

		/// <summary>ID of the geometry shader.</summary>
		mutable Uint32 m_GeometryID;

		/// <summary>ID of the tesselation control shader.</summary>
		mutable Uint32 m_TesselationControlID;

		/// <summary>ID of the tesselation evaluation shader.</summary>
		mutable Uint32 m_TesselationEvaluationID;

		/// <summary>ID of the geometry shader.</summary>
		mutable Uint32 m_FragmentID;

		/// <summary>ID of the compute shader.</summary>
		mutable Uint32 m_ComputeID;


		/// <summary>Path to vertex shader file.</summary>
		std::string m_VertexFile;

		/// <summary>Path to geometry shader file.</summary>
		std::string m_GeometryFile;

		/// <summary>Path to tesselation control shader file.</summary>
		std::string m_TesselationControlFile;

		/// <summary>Path to tesselation evaluation shader file.</summary>
		std::string m_TesselationEvaluationFile;

		/// <summary>Path to fragment shader file.</summary>
		std::string m_FragmentFile;		

		/// <summary>Path to compute shader file.</summary>
		std::string m_ComputeFile;

		/// <summary>
		/// Locations saved when user call GetUniformLocation the first time for a parameter. <para/>
		/// The purpose is to use this map instead of fetching the location with OpenGL each time GetUniformLocation is called.
		/// </summary>
		mutable LocationsMap m_CachedLocations;
	};

} // ae

#endif // _SHADER_AERO_H_
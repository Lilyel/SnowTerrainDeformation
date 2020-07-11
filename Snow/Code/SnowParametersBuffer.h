#pragma once

#include "SnowParameters.h"

#include <API/Code/Toolbox/Toolbox.h>

/// <summary>Utility class to send the snow parameters to the shaders and expose them in the editor.</summary>
class SnowParametersBuffer
{
public:
	/// <summary>Initialize the buffer.</summary>
	SnowParametersBuffer();

	/// <summary>Free the buffer.</summary>
	~SnowParametersBuffer();

	/// <summary>Bind the buffer for data update.</summary>
	void Bind();
	/// <summary>Unbidng the buffer for data update.</summary>
	void Unbind();

	/// <summary>Bind the buffer for shader usage.</summary>
	/// <param name="_BindingPoint">The binding point in the shader.</param>
	void BindToPoint( Uint32 _BindingPoint );

	/// <summary>Unbind the buffer for shader usage.</summary>
	/// <param name="_BindingPoint">The binding point in the shader.</param>
	void UnbindFromPoint( Uint32 _BindingPoint );

	/// <summary>Set the near distance of the camera bellow the ground.</summary>
	/// <param name="_Near">The near distance of the camera bellow the ground.</param>
	void SetCameraNear( float _Near );

	/// <summary>Get the near distance of the camera bellow the ground.</summary>
	/// <returns>The near distance of the camera bellow the ground.</returns>
	float GetCameraNear() const;


	/// <summary>Set the far distance of the camera bellow the ground.</summary>
	/// <returns>The far distance of the camera bellow the ground.</returns>
	void SetCameraFar( float _Far );

	/// <summary>Get the far distance of the camera bellow the ground.</summary>
	/// <returns>GThe far distance of the camera bellow the ground.</returns>
	float GetCameraFar() const;

	/// <summary>Set the size of the texture used of the snow ( height map, depth map, ...)</summary>
	/// <param name="_TextureSize">The size to apply.</param>
	void SetTextureSize( Uint32 _TextureSize );

	/// <summary>Retrieve the size of the textures.</summary>
	/// <returns>The size of the textures.</returns>
	Uint32 GetTextureSize() const;

	/// <summary>Set the scale applied to the height values when converting them to integer.</summary>
	/// <param name="_Scale">The scale to apply.</param>
	void SetHeightMapScale( float _Scale );

	/// <summary>Retrieve the scale applied to the height values when converting them to integer.</summary>
	/// <returns>The scale applied to the height values.</returns>
	float GetHeightMapScale() const;

	/// <summary>Set the conversion value from texture distance to world distance.</summary>
	/// <param name="_Size">The size of a texel as world distance.</param>
	void SetPixelSize( float _Size );

	/// <summary>Get the conversion value from texture distance to world distance.</summary>
	/// <returns>The size of a texel as world distance.</returns>
	float GetPixelSize() const;

	/// <summary>Update the tim value from the application life time.</summary>
	void UpdateTimeFromLifeTime();

	/// <summary>Update the buffer data.</summary>
	void UpdateBuffer();

	/// <summary>Update camera, texture and time parameters.</summary>
	/// <param name="_CameraFar">The far distance of the camera bellow the ground.</param>
	/// <param name="_CameraNear">The near distance of the camera bellow the ground.</param>
	/// <param name="_PixelSize">The conversion value from texture distance to world distance.</param>
	void Update( float _CameraFar, float _CameraNear, float _PixelSize );

	/// <summary>Expose properties in the editor panel.</summary>
	/// <param name="_Displacement">Displacement pass to expose to the editor.</param>
	void ToEditor( class SnowDisplacement& _Displacement );

private:
	/// <summary>Create the OpenGL buffer.</summary>
	void CreateBuffer();

	/// <summary>Free the OpenGL buffer.</summary>
	void DeleteBuffer();

private:
	/// <summary>OpenGL buffer ID.</summary>
	Uint32 m_BufferID;
	/// <summary>Should the buffer must be update before the next BindToPoint() ?</summary>
	Bool m_MustUpdate;

	/// <summary>Snow parameters to put in the buffer.</summary>
	SnowParameters m_Parameters;
};
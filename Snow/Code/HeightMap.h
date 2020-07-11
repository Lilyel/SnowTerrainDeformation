#pragma once


#include <API/Code/Graphics/Texture/Texture2D.h>
#include <API/Code/Graphics/Shader/Shader.h>

/// <summary>Height texture representing the snow level.</summary>
class HeightMap
{
public:
	/// <summary>Create the height textures/</summary>
	/// <param name="_TextureSize">The size to apply to the textures.</param>
	HeightMap( Uint32 _TextureSize );

	/// <summary>Initialization pass of the height map (makes dunes).</summary>
	void Initialize();

	/// <summary>Convert the integer height map to floating value and store the result in the float texture.</summary>
	void ToFloat();

	/// <summary>Retrieve the integer height map.</summary>
	/// <returns>The integer height map.</returns>
	ae::Texture2D& GetIntegerHeightMap();

	/// <summary>Retrieve the floating value height map.</summary>
	/// <returns>The floating value height map.</returns>
	ae::Texture2D& GetFloatHeightMap();

	/// <summary>Resize the height maps</summary>
	/// <param name="_TextureSize"></param>
	void Resize( Uint32 _TextureSize );

private:
	/// <summary>Initialization shader : makes soft dunes.</summary>
	ae::Shader m_InitializationShader;

	/// <summary>Shader that convert integer height value to floating values.</summary>
	ae::Shader m_ToFloatShader;

	/// <summary>Integer and scaled height texture.</summary>
	ae::Texture2D m_IntegerHeightMap;

	/// <summary>Floating value (not scaled) height texture.</summary>
	ae::Texture2D m_FloatHeightMap;
};
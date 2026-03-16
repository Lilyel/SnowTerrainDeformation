#include "TexturePixelFormat.h"

#include <array>

namespace ae
{
	GLint ae::ToGLInternalFormat( TexturePixelFormat _Format )
	{
		static const std::array<GLint, static_cast<size_t>( TexturePixelFormat::Count )> InternalFormats =
		{
			GL_R8,
			GL_R8I,
			GL_R16,
			GL_R16I,
			GL_R32UI,
			GL_R32I,
			GL_R16F,
			GL_R32F,

			GL_R8,
			GL_R8I,
			GL_R16,
			GL_R16I,

			GL_RG8,
			GL_RG8I,
			GL_RG16,
			GL_RG16I,
			GL_RG32UI,
			GL_RG32I,
			GL_RG16F,
			GL_RG32F,

			GL_RGB8,
			GL_RGB8I,
			GL_RGB16,
			GL_RGB16I,
			GL_RGB32UI,
			GL_RGB32I,
			GL_RGB16F,
			GL_RGB32F,

			GL_RGB8,

			GL_RGBA8,
			GL_RGBA8I,
			GL_RGBA16,
			GL_RGBA16I,
			GL_RGBA32UI,
			GL_RGBA32I,
			GL_RGBA16F,
			GL_RGBA32F,

			GL_RGBA8,

			GL_SRGB8,
			GL_SRGB8_ALPHA8, 

			GL_DEPTH_COMPONENT,

			GL_DEPTH24_STENCIL8
		};

		return InternalFormats[Cast(size_t, _Format )];
	}

	GLint ae::ToGLImageFormat( TexturePixelFormat _Format )
	{
		static const std::array<GLint, static_cast<size_t>( TexturePixelFormat::Count )> InternalFormats =
		{
			GL_R8UI,
			GL_R8I,
			GL_R16UI,
			GL_R16I,
			GL_R32UI,
			GL_R32I,
			GL_R16F,
			GL_R32F,

			GL_R8UI,
			GL_R8I,
			GL_R16UI,
			GL_R16I,

			GL_RG8UI,
			GL_RG8I,
			GL_RG16UI,
			GL_RG16I,
			GL_RG32UI,
			GL_RG32I,
			GL_RG16F,
			GL_RG32F,

			GL_RGB8UI,
			GL_RGB8I,
			GL_RGB16UI,
			GL_RGB16I,
			GL_RGB32UI,
			GL_RGB32I,
			GL_RGB16F,
			GL_RGB32F,

			GL_RGB8,

			GL_RGBA8UI,
			GL_RGBA8I,
			GL_RGBA16UI,
			GL_RGBA16I,
			GL_RGBA32UI,
			GL_RGBA32I,
			GL_RGBA16F,
			GL_RGBA32F,

			GL_RGBA8,

			GL_RGB8UI,
			GL_RGBA8UI,

			GL_R32F,

			GL_R32UI
		};

		return InternalFormats[Cast( size_t, _Format )];
	}

	GLint ToGLFormat( TexturePixelFormat _Format )
	{
		static const std::array<GLenum, static_cast<size_t>( TexturePixelFormat::Count )> Formats =
		{
			GL_RED,
			GL_RED,
			GL_RED,
			GL_RED,
			GL_RED_INTEGER,
			GL_RED_INTEGER,
			GL_RED,
			GL_RED,

			GL_RED_INTEGER,
			GL_RED_INTEGER,
			GL_RED_INTEGER,
			GL_RED_INTEGER,

			GL_RG,
			GL_RG,
			GL_RG,
			GL_RG,
			GL_RG,
			GL_RG,
			GL_RG_INTEGER,
			GL_RG_INTEGER,

			GL_RGB,
			GL_RGB,
			GL_RGB,
			GL_RGB,
			GL_RGB_INTEGER,
			GL_RGB_INTEGER,
			GL_RGB,
			GL_RGB,

			GL_RGB,

			GL_RGBA,
			GL_RGBA,
			GL_RGBA,
			GL_RGBA,
			GL_RGBA_INTEGER,
			GL_RGBA_INTEGER,
			GL_RGBA,
			GL_RGBA,

			GL_RGBA,

			GL_RGB,
			GL_RGBA,

			GL_DEPTH_COMPONENT,

			GL_DEPTH_STENCIL
		};

		return Formats[Cast( size_t, _Format )];
	}
	GLint ToGLType( TexturePixelFormat _Format )
	{
		static const std::array<GLenum, static_cast<size_t>( TexturePixelFormat::Count )> Types =
		{
			GL_UNSIGNED_BYTE,
			GL_BYTE,
			GL_UNSIGNED_SHORT,
			GL_SHORT,
			GL_UNSIGNED_INT,
			GL_INT,
			GL_HALF_FLOAT,
			GL_FLOAT,

			GL_UNSIGNED_INT,
			GL_INT,
			GL_UNSIGNED_INT,
			GL_INT,

			GL_UNSIGNED_BYTE,
			GL_BYTE,
			GL_UNSIGNED_SHORT,
			GL_SHORT,
			GL_UNSIGNED_INT,
			GL_INT,
			GL_HALF_FLOAT,
			GL_FLOAT,

			GL_UNSIGNED_BYTE,
			GL_BYTE,
			GL_UNSIGNED_SHORT,
			GL_SHORT,
			GL_UNSIGNED_INT,
			GL_INT,
			GL_HALF_FLOAT,
			GL_FLOAT,

			GL_UNSIGNED_BYTE,

			GL_UNSIGNED_BYTE,
			GL_BYTE,
			GL_UNSIGNED_SHORT,
			GL_SHORT,
			GL_UNSIGNED_INT,
			GL_INT,
			GL_HALF_FLOAT,
			GL_FLOAT,

			GL_UNSIGNED_BYTE,

			GL_UNSIGNED_BYTE,
			GL_UNSIGNED_BYTE,

			GL_FLOAT,

			GL_UNSIGNED_INT_24_8
		};

		return Types[Cast( size_t, _Format )];
	}

	Uint8 GetChannelsCount( TexturePixelFormat _Format )
	{
		static const std::array<Uint8, static_cast<size_t>( TexturePixelFormat::Count )> Types =
		{
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			1,

			1,
			1,
			1,
			1,

			2,
			2,
			2,
			2,
			2,
			2,
			2,
			2,

			3,
			3,
			3,
			3,
			3,
			3,
			3,
			3,

			3,

			4,
			4,
			4,
			4,
			4,
			4,
			4,
			4,

			4,

			3,
			4,

			1,

			1
		};

		return Types[Cast( size_t, _Format )];
	}

	std::string ToString( TexturePixelFormat _Format )
	{
		static const std::array<std::string, static_cast<size_t>( TexturePixelFormat::Count )> Names =
		{
			"Red (unsigned byte)",
			"Red (signed byte)",
			"Red (unsigned short)",
			"Red (signed short)",
			"Red (unsigned int, not normalized)",
			"Red (signed int, not normalized)",
			"Red (half-float)",
			"Red (float)",

			"Red (unsigned byte, not normalized)",
			"Red (signed byte, not normalized)",
			"Red (unsigned short, not normalized)",
			"Red (signed short, not normalized)",

			"Red, Green (unsigned byte)",
			"Red, Green (signed byte)",
			"Red, Green (unsigned short)",
			"Red, Green (signed short)",
			"Red, Green (unsigned int, not normalized)",
			"Red, Green (signed int, not normalized)",
			"Red, Green (half-float)",
			"Red, Green (float)",

			"RGB (unsigned byte)",
			"RGB (signed byte)",
			"RGB (unsigned short)",
			"RGB (signed short)",
			"RGB (unsigned int, not normalized)",
			"RGB (signed int, not normalized)",
			"RGB (half-float)",
			"RGB (float)",

			"RGB (unsigned byte)",

			"RGBA (unsigned byte)",
			"RGBA (signed byte)",
			"RGBA (unsigned short)",
			"RGBA (signed short)",
			"RGBA (unsigned int, not normalized)",
			"RGBA (signed int, not normalized)",
			"RGBA (half-float)",
			"RGBA (float)",

			"RGBA (unsigned byte)",

			"sRGB (unsigned byte)",
			"sRGBA (unsigned byte)",

			"Depth (float)",

			"Depth-Stencil (unsigned int 24/8)"
		};


		return Names[Cast( size_t, _Format )];
	}
}

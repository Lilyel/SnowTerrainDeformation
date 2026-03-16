#include "CubeMapImage.h"

#include "../../Debugging/Debugging.h"
#include "../Image/Image.h"
#include "../../Aero/Aero.h"

#include "../../Editor/TypesToEditor/CubeMapToEditor.h"

#include "../Dependencies/OpenGL.h"

namespace ae
{
	CubeMapImage::CubeMapImage( const std::array<const std::string*, 6>& _FilePaths, Bool _AreHDR )
	{
		if( _AreHDR )
		{
			ImageHDR ImageSources[6] =
			{
				ImageHDR( *( _FilePaths[0] ) ),
				ImageHDR( *( _FilePaths[1] ) ),
				ImageHDR( *( _FilePaths[2] ) ),
				ImageHDR( *( _FilePaths[3] ) ),
				ImageHDR( *( _FilePaths[4] ) ),
				ImageHDR( *( _FilePaths[5] ) )
			};

			std::reference_wrapper<const ImageHDR> Images[6] =
			{
				std::cref( ImageSources[0] ),
				std::cref( ImageSources[1] ),
				std::cref( ImageSources[2] ),
				std::cref( ImageSources[3] ),
				std::cref( ImageSources[4] ),
				std::cref( ImageSources[5] )
			};

			UpdateDataFromImages( Images );
		}
		else
		{
			Image ImageSources[6] =
			{
				Image( *( _FilePaths[0] ) ),
				Image( *( _FilePaths[1] ) ),
				Image( *( _FilePaths[2] ) ),
				Image( *( _FilePaths[3] ) ),
				Image( *( _FilePaths[4] ) ),
				Image( *( _FilePaths[5] ) )
			};

			std::reference_wrapper<const Image> Images[6] =
			{
				std::cref( ImageSources[0] ),
				std::cref( ImageSources[1] ),
				std::cref( ImageSources[2] ),
				std::cref( ImageSources[3] ),
				std::cref( ImageSources[4] ),
				std::cref( ImageSources[5] )
			};

			UpdateDataFromImages( Images );
		}
	}

	CubeMapImage::CubeMapImage( const std::array<const std::string, 6>& _FilePaths, Bool _AreHDR )
	{
		if( _AreHDR )
		{
			ImageHDR ImageSources[6] =
			{
				ImageHDR( _FilePaths[0] ),
				ImageHDR( _FilePaths[1] ),
				ImageHDR( _FilePaths[2] ),
				ImageHDR( _FilePaths[3] ),
				ImageHDR( _FilePaths[4] ),
				ImageHDR( _FilePaths[5] )
			};

			std::reference_wrapper<const ImageHDR> Images[6] =
			{
				std::cref( ImageSources[0] ),
				std::cref( ImageSources[1] ),
				std::cref( ImageSources[2] ),
				std::cref( ImageSources[3] ),
				std::cref( ImageSources[4] ),
				std::cref( ImageSources[5] )
			};

			UpdateDataFromImages( Images );
		}
		else
		{
			Image ImageSources[6] =
			{
				Image( _FilePaths[0] ),
				Image( _FilePaths[1] ),
				Image( _FilePaths[2] ),
				Image( _FilePaths[3] ),
				Image( _FilePaths[4] ),
				Image( _FilePaths[5] )
			};

			std::reference_wrapper<const Image> Images[6] =
			{
				std::cref( ImageSources[0] ),
				std::cref( ImageSources[1] ),
				std::cref( ImageSources[2] ),
				std::cref( ImageSources[3] ),
				std::cref( ImageSources[4] ),
				std::cref( ImageSources[5] )
			};

			UpdateDataFromImages( Images );
		}
	}

	CubeMapImage::CubeMapImage( const std::string& _FilePath, Bool _AreHDR )
	{
		if( _AreHDR )
		{
			const ImageHDR ImageSource( _FilePath );

			std::reference_wrapper<const ImageHDR> Images[6] =
			{
				ImageSource, ImageSource, ImageSource, ImageSource, ImageSource, ImageSource
			};

			UpdateDataFromImages( Images );
		}
		else
		{
			const Image ImageSource( _FilePath );

			std::reference_wrapper<const Image> Images[6] =
			{
				ImageSource, ImageSource, ImageSource, ImageSource, ImageSource, ImageSource
			};

			UpdateDataFromImages( Images );
		}
	}


	CubeMapImage::CubeMapImage( const std::array<const Image*, 6>& _ImageSources )
	{
		std::reference_wrapper<const Image> Images[6] =
		{
			std::cref( *( _ImageSources[0] ) ),
			std::cref( *( _ImageSources[1] ) ),
			std::cref( *( _ImageSources[2] ) ),
			std::cref( *( _ImageSources[3] ) ),
			std::cref( *( _ImageSources[4] ) ),
			std::cref( *( _ImageSources[5] ) )
		};

		UpdateDataFromImages( Images );
	}

	CubeMapImage::CubeMapImage( const std::array<const Image, 6>& _ImageSources )
	{
		std::reference_wrapper<const Image> Images[6] =
		{
			std::cref( _ImageSources[0] ),
			std::cref( _ImageSources[1] ),
			std::cref( _ImageSources[2] ),
			std::cref( _ImageSources[3] ),
			std::cref( _ImageSources[4] ),
			std::cref( _ImageSources[5] )
		};

		UpdateDataFromImages( Images );
	}

	CubeMapImage::CubeMapImage( const Image& _ImageSource )
	{
		std::reference_wrapper<const Image> Images[6] =
		{
			_ImageSource, _ImageSource, _ImageSource, _ImageSource, _ImageSource, _ImageSource
		};

		UpdateDataFromImages( Images );
	}


	CubeMapImage::CubeMapImage( const std::array<const ImageHDR*, 6>& _ImageSources )
	{
		std::reference_wrapper<const ImageHDR> Images[6] =
		{
			std::cref( *( _ImageSources[0] ) ),
			std::cref( *( _ImageSources[1] ) ),
			std::cref( *( _ImageSources[2] ) ),
			std::cref( *( _ImageSources[3] ) ),
			std::cref( *( _ImageSources[4] ) ),
			std::cref( *( _ImageSources[5] ) )
		};

		UpdateDataFromImages( Images );
	}

	CubeMapImage::CubeMapImage( const std::array<const ImageHDR, 6>& _ImageSources )
	{
		std::reference_wrapper<const ImageHDR> Images[6] =
		{
			std::cref( _ImageSources[0] ),
			std::cref( _ImageSources[1] ),
			std::cref( _ImageSources[2] ),
			std::cref( _ImageSources[3] ),
			std::cref( _ImageSources[4] ),
			std::cref( _ImageSources[5] )
		};

		UpdateDataFromImages( Images );
	}

	CubeMapImage::CubeMapImage( const ImageHDR& _ImageSource )
	{
		std::reference_wrapper<const ImageHDR> Images[6] =
		{
			_ImageSource, _ImageSource, _ImageSource, _ImageSource, _ImageSource, _ImageSource
		};

		UpdateDataFromImages( Images );
	}


	const std::string& CubeMapImage::GetFilePath( Uint32 _Index ) const
	{
		if( _Index >= 6 )
		{
			AE_LogError( "Try to access to a cube map's texture superior to 5, returing the first one. (Cube map textures indexes must be in [0-5])" );
			return m_FilePath[0];
		}

		return m_FilePath[_Index];
	}

	void CubeMapImage::ToEditor()
	{
		Resource::ToEditor();
		priv::ui::CubeMapToEditorBegin();
		priv::ui::CubeMapImageToEditor( *this );
		priv::ui::TextureToEditorEnd();
	}

	


	void CubeMapImage::UpdateDataFromImages( std::reference_wrapper<const Image> _ImageSources[6] )
	{
		m_Dimension = TextureDimension::CubeMap;

		// Bind the newly created OpenGL texture to apply the next changes.
		Bind();

		// Texture settings :  repeat ? - pixel interpolation ( smoothing ) ?.
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();

		for( size_t i = 0; i < 6; i++ )
		{
			const Image& SideImage = _ImageSources[i].get();

			m_FilePath[i] = SideImage.GetFilePath();

			m_Format = SideImage.GetTexturePixelFormat();

			m_Widths[i] = SideImage.GetWidth();
			m_Heights[i] = SideImage.GetHeight();

			// Atatch each given image to a side of the cube.
			glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + Cast( GLenum, i ), 
						  0, 
						  ToGLInternalFormat( m_Format ),
						  m_Widths[i],
						  m_Heights[i],
						  0,
						  ToGLFormat( m_Format ),
						  ToGLType( m_Format ),
						  SideImage.GetData() );
			AE_ErrorCheckOpenGLError();
		}

		Unbind();

		SetName( std::string( "CubeMapImage_" ) + std::to_string( GetResourceID() ) );
	}

	void CubeMapImage::UpdateDataFromImages( std::reference_wrapper<const ImageHDR> _ImageSources[6] )
	{
		m_Dimension = TextureDimension::CubeMap;

		// Bind the newly created OpenGL texture to apply the next changes.
		Bind();

		// Texture settings :  repeat ? - pixel interpolation ( smoothing ) ?.
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, Cast( GLint, m_Wrap ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, Cast( GLint, m_Filter ) ); AE_ErrorCheckOpenGLError();

		for( size_t i = 0; i < 6; i++ )
		{
			const ImageHDR& SideImage = _ImageSources[i].get();

			m_FilePath[i] = SideImage.GetFilePath();

			m_Format = SideImage.GetTexturePixelFormat();

			m_Widths[i] = SideImage.GetWidth();
			m_Heights[i] = SideImage.GetHeight();

			// Atatch each given image to a side of the cube.
			glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + Cast( GLenum, i ),
						  0,
						  ToGLInternalFormat( m_Format ),
						  m_Widths[i],
						  m_Heights[i],
						  0,
						  ToGLFormat( m_Format ),
						  ToGLType( m_Format ),
						  SideImage.GetData() );
			AE_ErrorCheckOpenGLError();
		}

		Unbind();

		SetName( std::string( "CubeMapImage_" ) + std::to_string( GetResourceID() ) );
	}

} // ae

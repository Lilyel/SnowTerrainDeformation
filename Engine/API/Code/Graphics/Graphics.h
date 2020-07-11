#pragma once

////////////////////////////////////////////////////////////
/// \defgroup graphics Graphics
///
/// All tools that help to create a window a draw thing on it.
/// ( Window, shapes, OpenGL rendering, ... )
/// 
////////////////////////////////////////////////////////////

#include "Camera/Camera.h"
#include "Camera/CameraOrthographic.h"
#include "Camera/CameraPerspective.h"
#include "Renderer/Renderer.h"
#include "Context/Context.h"
#include "Window/Window.h"

#include "Framebuffer/Framebuffer.h"
#include "Framebuffer/FramebufferSprite.h"

#include "ShadowMap/ShadowMap.h"

#include "BlendMode/BlendMode.h"

#include "Shader/Shader.h"
#include "Shader/ShaderParameter/ShaderParameter.h"
#include "Shader/ShaderParameter/ShaderParameterInt.h"
#include "Shader/ShaderParameter/ShaderParameterBool.h"
#include "Shader/ShaderParameter/ShaderParameterFloat.h"
#include "Shader/ShaderParameter/ShaderParameterVector2.h"
#include "Shader/ShaderParameter/ShaderParameterVector3.h"
#include "Shader/ShaderParameter/ShaderParameterColor.h"
#include "Shader/ShaderParameter/ShaderParameterMatrix3x3.h"
#include "Shader/ShaderParameter/ShaderParameterMatrix4x4.h"
#include "Shader/ShaderParameter/ShaderParameterTexture.h"
#include "Shader/ShaderParameter/ShaderParameterCubeMap.h"
#include "Shader/ShaderParameter/ShaderParameterTextureBool.h"

#include "Material/Material.h"
#include "Material/BlinnPhongMaterial.h"
#include "Material/SpriteMaterial.h"
#include "Material/FramebufferMaterial.h"
#include "Material/SkyboxMaterial.h"
#include "Material/CookTorranceMaterial.h"
#include "Material/ToonMaterial.h"

#include "Color/Color.h"

#include "Vertex/Vertex3D.h"
#include "Vertex/Vertex2D.h"

#include "Drawable/Drawable.h"
#include "Drawable/TransformableDrawable2D.h"
#include "Drawable/TransformableDrawable3D.h"

#include "Image/Image.h"
#include "Texture/Texture.h"
#include "Texture/Texture1D.h"
#include "Texture/Texture2D.h"
#include "Texture/Texture3D.h"
#include "Texture/Texture1DArray.h"
#include "Texture/TextureImage.h"
#include "Texture/TextureMultisample.h"
#include "Texture/Texture2DRect.h"
#include "Texture/Texture2DArray.h"
#include "CubeMap/CubeMap.h"
#include "CubeMap/CubeMapImage.h"
#include "Skybox/Skybox.h"

#include "Mesh/3D/Mesh3D.h"
#include "Mesh/3D/CubeMesh.h"
#include "Mesh/3D/SphereMesh.h"
#include "Mesh/3D/PlaneMesh.h"
#include "Mesh/3D/CurveMesh.h"

#include "Mesh/2D/Mesh2D.h"
#include "Mesh/2D/QuadMesh.h"
#include "Mesh/2D/FullscreenQuadMesh.h"

#include "Sprite/Sprite.h"


#include "Light/Lights.h"

#include "ImageBasedLighting/ImageBasedLighting.h"

#include "PostProcess/GaussianBlur.h"
#include "PostProcess/GammaCorrection.h"
#include "PostProcess/Bloom.h"

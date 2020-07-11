#pragma once

#include "../../Toolbox/Toolbox.h"

#include <string>

struct aiMaterial;

namespace ae
{
	class Texture;
	class Material;
	class BlinnPhongMaterial;
	class CookTorranceMaterial;
	class ToonMaterial;

	namespace priv
	{
		/// <summary>Load the Blinn-Phong supported parameters from model file.</summary>
		/// <param name="_OurMaterial">The engine model material to fill.</param>
		/// <param name="_AssimpMaterial">The Assimp model material extracted from the file.</param>
		/// <param name="_Directory">Directory of the model file.</param>
		void AssimpLoadBlinnPhongMaterial( BlinnPhongMaterial& _OurMaterial, const aiMaterial* _AssimpMaterial, const std::string& _Directory );

		/// <summary>Load the Cook-Torrance supported parameters from model file.</summary>
		/// <param name="_OurMaterial">The engine model material to fill.</param>
		/// <param name="_AssimpMaterial">The Assimp model material extracted from the file.</param>
		/// <param name="_Directory">Directory of the model file.</param>
		void AssimpLoadCookTorranceMaterial( CookTorranceMaterial& _OurMaterial, const aiMaterial* _AssimpMaterial, const std::string& _Directory );

		/// <summary>Load the Toon supported parameters from model file.</summary>
		/// <param name="_OurMaterial">The engine model material to fill.</param>
		/// <param name="_AssimpMaterial">The Assimp model material extracted from the file.</param>
		/// <param name="_Directory">Directory of the model file.</param>
		void AssimpLoadToonMaterial( ToonMaterial& _OurMaterial, const aiMaterial* _AssimpMaterial, const std::string& _Directory );

		/// <summary>Load material from the model file.</summary>
		/// <param name="_OurMaterial">The engine model material to fill.</param>
		/// <param name="_AssimpMaterial">The Assimp model material extracted from the file.</param>
		/// <param name="_Directory">Directory of the model file.</param>
		/// <param name="_UseTextureBool">Use simple texture parameter or texture/bool pair to handle invalid texture ?</param>
		void AssimpLoadMaterial( Material& _OurMaterial, const aiMaterial* _AssimpMaterial, const std::string& _Directory, Bool _UseTextureBool );


		/// <summary>Retrieve file texture from the material and create a texture from it.</summary>
		/// <param name="_Material">The material containing the file texture path.</param>
		/// <param name="_Directory">The path to the model file directory.</param>
		/// <param name="TextureType">Type of the texture to retrieve.</param>
		/// <returns>Pointer on the new texture, nullptr if failed.</returns>
		Texture* AssimpGetMaterialTexture( const aiMaterial* _Material, const std::string& _Directory, Uint32 _TextureType );

	} // priv

} // ae

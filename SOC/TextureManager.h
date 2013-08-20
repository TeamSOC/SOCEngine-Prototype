#pragma once

#include "SOCHashMap.h"
#include "SingleTon.h"
#include "Texture.h"

namespace Rendering
{
	class TextureManager
	{
#define RESOURCE_DIR "../Resources/"

	private:
		SOCHashMap<std::string, Texture::TextureForm*> hash;
		int resourceDirLen;

	private:
		TextureManager();
		~TextureManager();

	public:
		Texture::TextureForm* AddTexture(std::string path, bool inResourceFolder = true);
		Texture::TextureForm* FindTexture(std::string path, bool inResourceFolder = true);

	public:
		void Delete(std::string path, bool inResourceFolder = true);
		void DeleteAll();
	};

}
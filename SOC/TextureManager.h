#pragma once

#include "SOCHashMap.h"
#include "Texture.h"

namespace Rendering
{
	namespace Texture
	{
		class TextureManager
		{
#define RESOURCE_DIR "../Resources/"

		private:
			SOCHashMap<std::string, Texture*> hash;
			int resourceDirLen;

		public:
			TextureManager();
			~TextureManager();

		public:
			Texture* AddTexture(std::string path, bool inResourceFolder = true);
			Texture* FindTexture(std::string path, bool inResourceFolder = true);

		public:
			void Delete(std::string path, bool inResourceFolder = true);
			void Delete(Texture* texture, bool dealloc);

			void DeleteAll();
		};
	}
}
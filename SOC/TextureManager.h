#pragma once

#include "SOCHashMap.h"
#include "Texture.h"

namespace Rendering
{
	namespace Texture
	{
		class TextureManager
		{
		private:
			SOCHashMap<std::string, Texture*> hash;

		public:
			TextureManager();
			~TextureManager();

		public:
			Texture* AddTexture(std::string path, bool inResourceFolder = true);
			Texture* FindTexture(std::string path);

		public:
			void Delete(std::string path);
			void Delete(Texture* texture, bool dealloc);

			void DeleteAll();
		};
	}
}
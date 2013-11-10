#include "TextureManager.h"
#include <string>
#include "ResourcesFolder.h"

using namespace std;

namespace Rendering
{
	using namespace Utility;

	namespace Texture
	{

		TextureManager::TextureManager()
		{
		}

		TextureManager::~TextureManager()
		{
			DeleteAll();
		}

		Texture* TextureManager::AddTexture(std::string path, bool inResourceFolder)
		{
			SOCHashMap<std::string, Texture*>::iterator iter = hash.find(path);

			if(iter != hash.end())
				return iter->second;

			Texture *tex = NULL;
			bool success;

			tex = new Texture();

			std::string &str = ResourcesFolder::GetPath(path.data());
			success = tex->Create(str.data());

			if(success == false)
				return NULL;

			hash.insert(SOCHashMap<string, Texture*>::value_type(path, tex));

			return tex;
		}

		Texture* TextureManager::FindTexture(std::string path)
		{
			return hash.find(path)->second;
		}

		void TextureManager::Delete(std::string path)
		{
			SOCHashMap<string, Texture*>::iterator iter = hash.find(path);

			if( iter == hash.end() )
				return;

			Utility::SAFE_DELETE(iter->second);

			hash.erase(iter);
		}

		void TextureManager::Delete(Texture* texture, bool remove)
		{
			SOCHashMap<string, Texture*>::iterator iter;
			for(iter = hash.begin(); iter != hash.end(); ++iter)
			{
				if( (*iter).second == texture )
				{
					if(remove)
						delete texture;

					hash.erase(iter);
					return;
				}
			}
		}

		void TextureManager::DeleteAll()
		{
			for(SOCHashMap<string, Texture*>::iterator iter = hash.begin();iter != hash.end(); ++iter)
				Utility::SAFE_DELETE(iter->second);

			hash.clear();
		}
	}
}
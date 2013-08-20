#include "TextureManager.h"
#include <string>

using namespace std;

namespace Rendering
{
	TextureManager::TextureManager()
	{
		resourceDirLen = strlen(RESOURCE_DIR);
	}

	TextureManager::~TextureManager()
	{
		DeleteAll();
	}

	Texture::TextureForm* TextureManager::AddTexture(std::string path, bool inResourceFolder)
	{
		if(inResourceFolder)
			path.erase(0, resourceDirLen);

		hash_map<string, Texture::TextureForm*>::iterator iter = hash.find(path);

		if(iter != hash.end())
			return iter->second;

		wchar_t wcharPath[260];
		//		const char *charPath = path.c_str();

		MultiByteToWideChar(CP_ACP, NULL, string( inResourceFolder ? RESOURCE_DIR  : "" + path ).c_str(), -1, wcharPath, path.length()+1 );

		Texture::TextureForm *tex = NULL;
		bool success;

#if defined(WIN32) && !defined(_USE_GL_DEFINES)
		tex = new Texture::TextureDX();
		success = tex->Create(wcharPath);
#endif

		if(success == false)
			return NULL;

		hash.insert(hash_map<string, Texture::TextureForm*>::value_type(path, tex));

		return tex;
	}

	Texture::TextureForm* TextureManager::FindTexture(std::string path, bool inResourceFolder)
	{
		if(inResourceFolder)
			path.erase(0, resourceDirLen);
		return hash.find(path)->second;
	}

	void TextureManager::Delete(std::string path, bool inResourceFolder/* = true*/)
	{
		if(inResourceFolder)
			path.erase(0, resourceDirLen);

		hash_map<string, Texture::TextureForm*>::iterator iter = hash.find(path);

		if( iter == hash.end() )
			return;

		Utility::SAFE_DELETE(iter->second);

		hash.erase(iter);
	}

	void TextureManager::DeleteAll()
	{
		for(hash_map<string, Texture::TextureForm*>::iterator iter = hash.begin();
			iter != hash.end(); ++iter)
			Utility::SAFE_DELETE(iter->second);

		hash.clear();
	}
}
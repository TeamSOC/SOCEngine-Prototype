#include "TextureManager.h"

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

	LPDIRECT3DTEXTURE9 TextureManager::AddTexture(std::string path, bool inResourceFolder)
	{
		if(inResourceFolder)
			path.erase(0, resourceDirLen);

		hash_map<string, LPDIRECT3DTEXTURE9>::iterator iter = hash.find(path);

		if(iter != hash.end())
			return iter->second;

		LPDIRECT3DTEXTURE9 tex = NULL;

		wchar_t wcharPath[MAX_PATH];
		//		const char *charPath = path.c_str();

		MultiByteToWideChar(CP_ACP, NULL, string( inResourceFolder ? RESOURCE_DIR  : "" + path ).c_str(), -1, wcharPath, path.length()+1 );

		if( FAILED( D3DXCreateTextureFromFile(device, wcharPath, &tex) ) )
			return NULL;

		hash.insert(hash_map<string, LPDIRECT3DTEXTURE9>::value_type(path, tex));

		return tex;
	}

	LPDIRECT3DTEXTURE9 TextureManager::FindTexture(std::string path, bool inResourceFolder)
	{
		if(inResourceFolder)
			path.erase(0, resourceDirLen);
		return hash.find(path)->second;
	}

	void TextureManager::Delete(std::string path, bool inResourceFolder/* = true*/)
	{
		if(inResourceFolder)
			path.erase(0, resourceDirLen);

		hash_map<string, LPDIRECT3DTEXTURE9>::iterator iter = hash.find(path);

		if( iter == hash.end() )
			return;

		Utility::SAFE_RELEASE(iter->second);

		hash.erase(iter);
	}

	void TextureManager::DeleteAll()
	{
		for(hash_map<string, LPDIRECT3DTEXTURE9>::iterator iter = hash.begin();
			iter != hash.end(); ++iter)
			Utility::SAFE_RELEASE(iter->second);

		hash.clear();
	}
}
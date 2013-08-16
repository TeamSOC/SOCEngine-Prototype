#pragma once

#include <hash_map>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>

#include "SingleTon.h"

namespace Rendering
{
	class TextureManager
	{
#define RESOURCE_DIR "../Resources/"

	private:
		std::hash_map<std::string, LPDIRECT3DTEXTURE9> hash;
		int resourceDirLen;

	public:
		LPDIRECT3DDEVICE9 device;

	private:
		TextureManager();
		~TextureManager();

	public:
		LPDIRECT3DTEXTURE9 AddTexture(std::string path, bool inResourceFolder = true);
		LPDIRECT3DTEXTURE9 FindTexture(std::string path, bool inResourceFolder = true);

	public:
		void Delete(std::string path, bool inResourceFolder = true);
		void DeleteAll();

	public:
		void SetDevice(LPDIRECT3DDEVICE9 device)
		{ this->device = device; }
	};

}
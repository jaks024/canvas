#pragma once
#include <SDL.h>
#include <string>
#include "ResourceObject.h"
using std::string;

namespace Framework::Resource
{
	class ResourceLoader
	{
		static const string ASSET_FOLDER_PATH;
	public:
		static ResourceObject* LoadTextureAsResourceObject(SDL_Renderer* renderer, string filename, string id, string name);
	};
}
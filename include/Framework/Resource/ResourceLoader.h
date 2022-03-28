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
		static int resourceCreatedCount;
		static ResourceObject* LoadTextureAsResourceObject(SDL_Renderer* renderer, const string filename, const string name);
		static ResourceObject* LoadTextAsResourceObject(SDL_Renderer* renderer, const string fontPath, const int fontSize,
			const SDL_Color textColor, const string message, const string name);
	};
}
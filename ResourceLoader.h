#pragma once
#include <SDL.h>
#include <string>
#include "ResourceObject.h"
using std::string;
class ResourceLoader
{
	public: 
		 static ResourceObject* LoadTextureAsResourceObject(SDL_Renderer* renderer, string filename, string id, string name);
};


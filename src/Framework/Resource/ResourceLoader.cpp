#include "../../../include/Framework/Resource/ResourceLoader.h"
#include <SDL_image.h>

namespace Framework::Resource 
{
	const string ResourceLoader::ASSET_FOLDER_PATH = "Assets/";

	ResourceObject* ResourceLoader::LoadTextureAsResourceObject(SDL_Renderer* renderer, string filename, string id, string name)
	{
		SDL_Texture* newTexture = NULL;
		string fullPath = ASSET_FOLDER_PATH + filename;
		printf("Loading %s\n", fullPath.c_str());

		newTexture = IMG_LoadTexture(renderer, fullPath.c_str());
		ResourceObject* newResourceObj = new ResourceObject(id, name, newTexture, fullPath);

		return newResourceObj;
	}
}
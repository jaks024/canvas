#include "ResourceLoader.h"
#include <SDL_image.h>

ResourceObject* ResourceLoader::LoadTextureAsResourceObject(SDL_Renderer* renderer, string path, string id, string name)
{
	SDL_Texture* newTexture = NULL;
	printf("Loading %s\n", path.c_str());

	newTexture = IMG_LoadTexture(renderer, path.c_str());

	ResourceObject* newResourceObj = new ResourceObject(id, name, newTexture, path);

	return newResourceObj;
}

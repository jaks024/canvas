#include "../../../include/Framework/Resource/ResourceLoader.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace Framework::Resource 
{
	int ResourceLoader::resourceCreatedCount = 0;
	const string ResourceLoader::ASSET_FOLDER_PATH = "Assets/";

	ResourceObject* ResourceLoader::LoadTextureAsResourceObject(SDL_Renderer* renderer, const string filename, const string name)
	{
		SDL_Texture* newTexture = NULL;
		string fullPath = ASSET_FOLDER_PATH + filename;
		printf("Loading %s\n", fullPath.c_str());

		newTexture = IMG_LoadTexture(renderer, fullPath.c_str());
		ResourceObject* newResourceObj = new ResourceObject(resourceCreatedCount, name, newTexture, fullPath);
		++resourceCreatedCount;

		return newResourceObj;
	}

	ResourceObject* ResourceLoader::LoadTextAsResourceObject(SDL_Renderer* renderer, const string fontPath, const int fontSize,
		const SDL_Color textColor, const string message, const string name) {
		string fullPath = ASSET_FOLDER_PATH + fontPath;
		if (TTF_Init() == 0)
		{
			TTF_Font* font = TTF_OpenFont(fullPath.c_str(), fontSize);

			SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, message.c_str(), textColor);
			SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

			ResourceObject* newResourceObj = new ResourceObject(0, name, messageTexture, fontPath);

			TTF_CloseFont(font);
			SDL_FreeSurface(surfaceMessage);
			return newResourceObj;
		}
		return nullptr;
	}
}
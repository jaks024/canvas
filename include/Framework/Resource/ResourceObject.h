#pragma once
#include <SDL.h>
#include <string>

namespace Framework::Resource
{
	struct ResourceObject
	{
		std::string id;
		std::string name;
		SDL_Texture* texture;
		std::string path;

		ResourceObject(std::string id, std::string name, SDL_Texture* texture, std::string path);
		~ResourceObject();
	};
}
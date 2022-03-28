#pragma once
#include <SDL.h>
#include <string>

namespace Framework::Resource
{
	struct ResourceObject
	{
		int id;
		std::string name;
		SDL_Texture* texture;
		std::string path;

		ResourceObject(int id, std::string name, SDL_Texture* texture, std::string path);
		~ResourceObject();
	};
}
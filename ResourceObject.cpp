#include "ResourceObject.h"

ResourceObject::ResourceObject(std::string id, std::string name, SDL_Texture* texture, std::string path)
{
	this->id = id;
	this->name = name;
	this->texture = texture;
	this->path = path;
}

ResourceObject::~ResourceObject()
{
	SDL_DestroyTexture(texture);
}

#include "../../../include/Framework/UI/Background.h"

namespace Framework::UI {
	Background::Background(unsigned int id, string name, SDL_Color tintColor, ResourceObject* textureObj, int width, int height)
		: Component(id, name, width, height)
	{
		this->tintColor = tintColor;
		Component::textureObj = textureObj;
	}

	void Background::SetTintColor(SDL_Color color)
	{
		this->tintColor = color;
	}

	void Background::Draw(SDL_Renderer* renderer)
	{
		Component::DrawChild(renderer);

		if (textureObj == nullptr) {
			return;
		}

		SDL_Rect bgRect;
		bgRect.x = GetRelativePositionX();
		bgRect.y = GetRelativePositionY();

		if (width == 0 && height == 0)
		{
			SDL_QueryTexture(Component::textureObj->texture, NULL, NULL, &bgRect.w, &bgRect.h);
		}
		else
		{
			bgRect.w = width;
			bgRect.h = height;
		}
		SDL_SetTextureColorMod(textureObj->texture, tintColor.r, tintColor.g, tintColor.b);
		SDL_RenderCopy(renderer, Component::textureObj->texture, NULL, &bgRect);
	}

}
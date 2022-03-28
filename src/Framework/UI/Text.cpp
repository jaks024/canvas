#include "../../../include/Framework/UI/Text.h"
#include "../../../include//Framework/Resource/ResourceLoader.h"
using Framework::Resource::ResourceLoader;

namespace Framework::UI {
	
	void Text::UpdateTextResourceObj(SDL_Renderer* renderer)
	{
		textureObj = ResourceLoader::LoadTextAsResourceObject(renderer, fontPath, 20, color, text, text);
	}

	Text::Text(unsigned int id, string name, string fontPath, int fontSize, int width, int height)
		: Component(id, name, width, height)
	{
		this->text = text;
		this->fontPath = fontPath;
		this->fontSize = fontSize;
	}

	void Text::SetFontSize(int fontSize)
	{
		this->fontSize = fontSize;
	}

	void Text::SetText(string text)
	{
		if (this->text.compare(text) == 0) {
			return;
		}

		this->text = text;
		updatedText = true;
		if (textureObj != nullptr) {
			delete(textureObj);
		}
	}

	void Text::SetColor(SDL_Color color)
	{
		this->color = color;
	}

	void Text::SetFont(string fontPath)
	{
		this->fontPath = fontPath;
	}

	void Text::Draw(SDL_Renderer* renderer)
	{
		Component::DrawChild(renderer);

		if (updatedText) {
			UpdateTextResourceObj(renderer);
			updatedText = false;
		}

		if (textureObj == nullptr) {
			return;
		}

		SDL_Rect messageRect; 
		messageRect.x = GetRelativePositionX();
		messageRect.y = GetRelativePositionY();

		if (width == 0 && height == 0)
		{
			SDL_QueryTexture(Component::textureObj->texture, NULL, NULL, &messageRect.w, &messageRect.h);
		}
		else
		{
			messageRect.w = width;
			messageRect.h = height;
		}

		SDL_RenderCopy(renderer, Component::textureObj->texture, NULL, &messageRect);
	}

}
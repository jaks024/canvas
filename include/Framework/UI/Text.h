#pragma once
#include "Component.h"
#include "../Resource/ResourceObject.h"
using Framework::Resource::ResourceObject;

namespace Framework::UI {

	class Text : public Component
	{
	protected:
		string text = "";
		string fontPath = "";
		int fontSize = 24;
		SDL_Color color = { 255, 255, 255 };
		bool updatedText = false;

		void UpdateTextResourceObj(SDL_Renderer* renderer);

	public:
		Text(unsigned int id, string name, string fontPath, int fontSize = 24, int width = 0, int height = 0);

		void SetFontSize(int fontSize);
		void SetText(string text);
		void SetColor(SDL_Color color);
		void SetFont(string fontPath);
		virtual void Draw(SDL_Renderer* renderer) override;
	};
}

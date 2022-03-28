#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>
#include "../Resource/ResourceObject.h"
using Framework::Resource::ResourceObject;
using std::string;
using std::unordered_map;

namespace Framework::UI {

	class Component
	{
	protected:
		unsigned int id = 0;
		string name;
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
		float xScale = 1;
		float yScale = 1;
		Component* parent;
		ResourceObject* textureObj;
		unordered_map<unsigned int, Component*> children;
		int GetRelativePositionX();
		int GetRelativePositionY();
		void DrawChild(SDL_Renderer* renderer);

	public:

		Component(unsigned int id, string name, int width, int height);
		~Component(void);

		unsigned int GetId(void);
		void SetName(string name);
		void SetPosition(int x, int y);
		void SetSize(int width, int height);
		void SetScale(float x, float y);
		void AddChild(Component* child);
		void SetTexture(ResourceObject* texutreObj);
		Component* RemoveChild(unsigned int id);

		virtual void Draw(SDL_Renderer* renderer) = 0;


	};
}

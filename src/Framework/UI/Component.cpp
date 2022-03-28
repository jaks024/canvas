#include "../../../include/Framework/UI/Component.h"

namespace Framework::UI {
	int Component::GetRelativePositionX()
	{
		return x + (parent == nullptr ? 0 : parent->x);
	}
	int Component::GetRelativePositionY()
	{
		return y + (parent == nullptr ? 0 : parent->y);
	}
	void Component::DrawChild(SDL_Renderer* renderer)
	{
		for (auto& child : children)
		{
			child.second->Draw(renderer);
		}
	}
	Component::Component(unsigned int id, string name, int width, int height)
	{
		this->id = id;
		SetName(name);
		SetSize(width, height);
	}

	Component::~Component(void)
	{
		if (textureObj != nullptr) {
			delete(textureObj);
		}
	}

	unsigned int Component::GetId(void)
	{
		return id;
	}

	void Component::SetName(string name)
	{
		this->name = name;
	}

	void Component::SetPosition(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void Component::SetSize(int width, int height)
	{
		this->width = width;
		this->height = height;
	}

	void Component::SetScale(float x, float y)
	{
		this->xScale = x;
		this->yScale = y;
	}

	void Component::AddChild(Component* child)
	{
		child->parent = this;
		children.emplace(child->id, child);
	}

	void Component::SetTexture(ResourceObject* texutreObj)
	{
		printf("texture ? %s\n", textureObj == nullptr ? "null" : "not null");
		this->textureObj = textureObj;
	}

	Component* Component::RemoveChild(unsigned int id)
	{
		auto result = children.find(id);
		if (result != children.end())
		{
			result->second->parent = nullptr;
			children.erase(id);
			return result->second;
		}
		return nullptr;
	}
}

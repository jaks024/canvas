#include "InputEventManager.h"


InputEventManager::InputEventManager(InputKeybindManager* keybindManager, function<void()> quitBehavior)
{
	this->keybindManager = keybindManager;
	this->QuitBehavior = quitBehavior;
}

void InputEventManager::InvokeBehavior(vector<function<void()>>* behaviors)
{
	if (behaviors == nullptr) 
	{
		return;
	}

	for (auto& behavior : *behaviors)
	{
		behavior();
	}
}

vector<function<void()>>* InputEventManager::GetBehaviors(SDL_Keycode key)
{
	auto result = keycodeBehaviorMap.find(key);
	if (result != keycodeBehaviorMap.end())
	{
		return &(result->second);
	}
	return nullptr;
}

void InputEventManager::ProcessInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				QuitBehavior();
				break;
			case SDL_KEYDOWN:	
				InvokeBehavior(GetBehaviors(keybindManager->GetBinding(event.key.keysym.sym)));
				break;
			default:
				break;
		}
	}
}

void InputEventManager::BindBehaviorToKey(SDL_Keycode key, function<void()> behavior)
{
	auto result = keycodeBehaviorMap.find(key);
	if (result != keycodeBehaviorMap.end()) 
	{
		result->second.push_back(behavior);
	} 
	else 
	{
		vector<function<void()>> keyBehaviors;
		keyBehaviors.push_back(behavior);
		keycodeBehaviorMap.insert(std::map<SDL_Keycode, vector<function<void()>>>::value_type(key, keyBehaviors));
	}
}

void InputEventManager::RemoveBehaviorFromKey(SDL_Keycode key, function<void()> behavior)
{
	auto result = keycodeBehaviorMap.find(key);
	if (result != keycodeBehaviorMap.end())
	{
		for (auto it = result->second.begin(); it != result->second.end(); ++it)
		{
			if (&(* it) == &behavior) {
				result->second.erase(it);
			}
		}
	}
}

void InputEventManager::RemoveKey(SDL_Keycode key)
{
	keycodeBehaviorMap.erase(key);
}

void InputEventManager::Clear(void)
{
	keycodeBehaviorMap.clear();
}

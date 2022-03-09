#include "InputKeybindManager.h"

void InputKeybindManager::Add(SDL_Keycode original, SDL_Keycode binding)
{
	keybindMap.insert(keybindMap.begin(), { original, binding });
}

void InputKeybindManager::Remove(SDL_Keycode original)
{
	keybindMap.erase(original);
}

SDL_Keycode InputKeybindManager::GetBinding(SDL_Keycode original)
{
	auto result = keybindMap.find(original);
	if (result != keybindMap.end()) {
		return result->second;
	}
	return NULL;
}

void InputKeybindManager::LoadBindingsFromJSON(std::string json)
{
}

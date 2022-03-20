#pragma once
#include <map>
#include <SDL.h>
#include <string>
using std::map;
using std::pair;

namespace Framework::Input 
{
	class InputKeybindManager
	{
	private:
		map<SDL_Keycode, SDL_Keycode> keybindMap;

	public:
		void Add(SDL_Keycode original, SDL_Keycode binding);
		void Remove(SDL_Keycode original);
		SDL_Keycode GetBinding(SDL_Keycode original);
		void LoadBindingsFromJSON(std::string json);
	};
}
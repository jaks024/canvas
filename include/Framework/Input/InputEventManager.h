#pragma once
#include <SDL.h>
#include <map>
#include <vector>
#include <functional>
#include "InputKeybindManager.h"
using std::function;
using std::map;
using std::vector;

namespace Framework::Input
{
	class InputEventManager
	{
	private:
		InputKeybindManager* keybindManager;
		map<SDL_Keycode, vector<function<void()>>> keycodeBehaviorMap;
		function<void()> QuitBehavior;
		void InvokeBehavior(vector<function<void()>>* behaviors);
		vector<function<void()>>* GetBehaviors(SDL_Keycode key);

	public:
		InputEventManager(InputKeybindManager* keybindManager, function<void()> quitBehavior);
		void ProcessInput(void);
		void BindBehaviorToKey(SDL_Keycode key, function<void()> behavior);
		void RemoveBehaviorFromKey(SDL_Keycode key, function<void()> behavior);
		void RemoveKey(SDL_Keycode key);
		void Clear(void);
	};
}
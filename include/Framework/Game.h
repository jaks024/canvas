#pragma once

#include <SDL.h>
#include <string>
#include "Resource/ResourceLibrary.h"
#include "Input/InputEventManager.h"
using Framework::Resource::ResourceLibrary;
using Framework::Input::InputKeybindManager;
using Framework::Input::InputEventManager;

namespace Framework 
{
	class Game
	{
	protected:
		// SDL
		SDL_Window* window;
		SDL_Renderer* renderer;

		// assets
		ResourceLibrary* resourceLibrary;

		// inputs
		InputKeybindManager* inputKeybindManager;
		InputEventManager* inputEventManager;

		virtual void PrepareScene(void);
		virtual void Update(void);
		virtual void ProcessInput(void);
		void PresentScene(void);
		void Draw(void);
		void OnQuitEvent(void);

	public:
		bool quit = false;
		bool InitializeSDL(const std::string name, int screenWidth, int screenHeight);
		virtual bool InitializeResources(void);
		virtual bool InitializeGame(void);
		virtual void Destroy(void);
		void Run(int framerate);
		void Quit(void);

	};
}

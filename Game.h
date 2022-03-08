#pragma once

#include <SDL.h>
#include <string>
#include "ResourceLibrary.h"

class Game
{
	protected:
		SDL_Window* window;
		SDL_Renderer* renderer;
		ResourceLibrary* resourceLibrary;
		
		virtual void PrepareScene(void);
		virtual void Update(void);
		void PresentScene(void);
		void ProcessInput(void);
		void Draw(void);

	public:
		bool quit = false;
		bool InitializeSDL(const std::string name, int screenWidth, int screenHeight);
		virtual bool InitializeResources(void);
		virtual bool InitializeGame(void);
		virtual void Destroy(void);
		void Run(int framerate);
		void Quit(void);
};


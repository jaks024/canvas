#pragma once

#include <SDL.h>
#include <string>
#include "ResourceLibrary.h"

class Game
{
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		ResourceLibrary* resourceLibrary;
		

		void PrepareScene(void);
		void PresentScene(void);
		void ProcessInput(void);
		void Update(void);
		void Draw(void);

	public:
		bool quit = false;
		bool Initialize(const std::string name, int screenWidth, int screenHeight);
		void Run(int framerate);
		void Destroy(void);
		void Quit(void);
};


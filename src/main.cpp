#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "RenderWindow.hpp"


int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL_Init FAILED. SDL_ERROR:" << SDL_GetError() << std::endl;
	}

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	RenderWindow window("GAME v1.0", 1280, 720);

	bool gameIsRunning = true;

	SDL_Event event;

	while(gameIsRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				gameIsRunning = false;
		}
	}

	window.cleanUP();
	SDL_Quit();


	std::cout << "YEY" << std::endl;
	std::cin.get();
	return 0;
}
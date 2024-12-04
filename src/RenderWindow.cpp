
#include "RenderWindow.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	
    if (renderer == nullptr)
    {
        std::cerr << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
    }
}


RenderWindow::~RenderWindow()
{
	cleanUp();
}


SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == nullptr)
	{
		std::cout << "Failed to load texture! Error: " << SDL_GetError() << std::endl;
	}

	return texture;

}	



void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* p_tex)
{
	
	SDL_RenderCopy(renderer, p_tex, NULL, NULL);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}





void RenderWindow::cleanUp()
{
	 if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}
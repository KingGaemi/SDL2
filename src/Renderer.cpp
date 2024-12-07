
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>



Renderer::Renderer(SDL_Window* window)
{

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr)
    {
        std::cerr << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
    }
}


Renderer::~Renderer()
{
	 if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
}

SDL_Texture* Renderer::loadTexture(std::string_view p_filePath){
	return IMG_LoadTexture(renderer, std::string(p_filePath).c_str());
}

void Renderer::render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect) {
    SDL_RenderCopy(renderer, texture, srcRect, dstRect);
}

void Renderer::clear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Renderer::display()
{
	SDL_RenderPresent(renderer);
}


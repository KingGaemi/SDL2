
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


SDL_Texture* Renderer::loadTexture(const std::string& p_filePath){
    std::cout << "Renderer loadTexture : " << p_filePath << std::endl;
    
    SDL_Texture* texture = IMG_LoadTexture(renderer, p_filePath.c_str());
    std::cout << "Renderer loadTexture Complete " << std::endl;

    if (!texture) {
        std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
    }

	return texture;
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

void Renderer::draw(std::string textureID, SDL_Rect* srcRect, SDL_Rect* dstRect){

    TextureManager* textureManager =  TextureManager::getInstance();

    SDL_Texture* texture =  textureManager->get(textureID);

    if(texture == nullptr){

        std::cerr << "texture load failed" << std::endl;
    }

    // std::cout << "Render -> " << textureID << std::endl;
    SDL_RenderCopy(renderer, texture, srcRect, dstRect);

}

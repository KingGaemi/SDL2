
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Sdl2/SDL_ttf.h>
#include <iostream>
#include "myMath.h"



Renderer::Renderer(SDL_Window* window)
{
	SDL_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (SDL_renderer == nullptr)
    {
        std::cerr << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
    }
}

    
Renderer::~Renderer()
{
	 if (SDL_renderer != nullptr)
    {
        SDL_DestroyRenderer(SDL_renderer);
        SDL_renderer = nullptr;
    }
}


SDL_Texture* Renderer::loadTexture(const std::string& p_filePath){

    SDL_Texture* texture = IMG_LoadTexture(SDL_renderer, p_filePath.c_str());
    if (!texture) {
        std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
    }else{
        std::cout << "Renderer loadTexture Complete!" << std::endl;
    }
	return texture;
}

SDL_Texture* Renderer::loadText(const char * textString){

    auto myFont =TTF_OpenFont("res/fonts/ARCADECLASSIC.TTF", 18);
   
    SDL_Color myColor;
    myColor.r = 255;
    myColor.g = 255;
    myColor.b = 255;


    SDL_Surface* textSurface = TTF_RenderText_Blended(myFont, textString, myColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(SDL_renderer, textSurface);
    SDL_FreeSurface(textSurface);

    if(!textTexture){
        std::cerr << "Failed to load textTexture: " << SDL_GetError() << std::endl;
    }else{
        std::cout << "Renderer loadText Complete!" << std::endl;
    }

    return textTexture;

}


void Renderer::render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_FRect* dstRect, double angle, SDL_FPoint* center, SDL_RendererFlip flip) {

    SDL_RenderCopyExF(SDL_renderer, texture, srcRect, dstRect, angle, center, flip);

}

void Renderer::clear()
{
	SDL_SetRenderDrawColor(SDL_renderer, 0, 0, 0, 255);
	SDL_RenderClear(SDL_renderer);
}

void Renderer::display()
{
	SDL_RenderPresent(SDL_renderer);
}

void Renderer::SetRenderDrawColor(int r, int g, int b, int a){
    SDL_SetRenderDrawColor(SDL_renderer, r, g, b, a);
}

void Renderer::RenderDrawRect(SDL_FRect &debugRect, float theta){

    float x1, y1, x2, y2, cx, cy;

    // upside
    x1 = debugRect.x - debugRect.w/2;
    y1 = debugRect.y - debugRect.h/2;
    x2 = debugRect.x + debugRect.w/2;
    y2 = y1;
    cx = debugRect.x;
    cy = debugRect.y;

    rotateLineSegment(x1, y1, x2, y2,
                       cx, cy, theta,
                       x1, y1, x2, y2);

    SDL_RenderDrawLineF(SDL_renderer, x1, y1,
                                      x2, y2);


    // downside
    x1 = debugRect.x - debugRect.w/2;
    y1 = debugRect.y + debugRect.h/2;
    x2 = debugRect.x + debugRect.w/2;
    y2 = y1;
    cx = debugRect.x;
    cy = debugRect.y;

    rotateLineSegment(x1, y1, x2, y2,
                       cx, cy, theta,
                       x1, y1, x2, y2);


    SDL_RenderDrawLineF(SDL_renderer, x1, y1,
                                      x2, y2);


    // leftside
    x1 = debugRect.x - debugRect.w/2;
    y1 = debugRect.y - debugRect.h/2;
    x2 = x1;
    y2 = debugRect.y + debugRect.h/2;
    cx = debugRect.x;
    cy = debugRect.y;


    rotateLineSegment(x1, y1, x2, y2,
                       cx, cy, theta,
                       x1, y1, x2, y2);


    SDL_RenderDrawLineF(SDL_renderer, x1, y1,
                                      x2, y2);

    // rightside
    x1 = debugRect.x + debugRect.w/2;
    y1 = debugRect.y - debugRect.h/2;
    x2 = x1;
    y2 = debugRect.y + debugRect.h/2;
    cx = debugRect.x;
    cy = debugRect.y;

    rotateLineSegment(x1, y1, x2, y2,
                       cx, cy, theta,
                       x1, y1, x2, y2);


    SDL_RenderDrawLineF(SDL_renderer, x1, y1,
                                      x2, y2);


}
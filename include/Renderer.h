#pragma once
#include <string>
#include <string_view>
#include "IRenderer.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class SDL_Rect;


class Renderer {
public:
    Renderer(SDL_Window* window);
    ~Renderer();
    
    SDL_Texture* loadTexture(const std::string& filePath);
    void render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, double angle, SDL_Point* center, SDL_RendererFlip flip);
    void clear();
    void display();

    SDL_Renderer* getSDLRenderer() const { return renderer; }

private:
    SDL_Renderer* renderer = nullptr;
};


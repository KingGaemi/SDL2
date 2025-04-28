#pragma once
#include <string>
#include <string_view>
#include "IRenderer.h"
#include <Sdl2/SDL_ttf.h>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class SDL_Rect;



class Renderer {
public:
    Renderer(SDL_Window* window);
    ~Renderer();
    
    SDL_Texture* loadTexture(const std::string& filePath);
    SDL_Texture* loadText(const char * textString);
    void render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_FRect* dstRect, double angle, SDL_FPoint* center, SDL_RendererFlip flip);
    void clear();
    void display();

    SDL_Renderer* getSDLRenderer() const { return SDL_renderer; }
    void setRenderDrawColor(int r, int g, int b, int a);
    void renderDrawLineF(float x1, float y1, float x2, float y2);
    void renderFillRectF(SDL_FRect *rect);
    void renderDrawRect(SDL_FRect &debugRect, float rot);
    void addDarkOverlay();
    void setFont(const std::string& font, int size);

private:
    TTF_Font* myFont;
    SDL_Renderer* SDL_renderer = nullptr;
};


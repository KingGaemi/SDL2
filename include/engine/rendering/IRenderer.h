#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual SDL_Texture* loadTexture(const std::string& p_filePath) = 0;
};

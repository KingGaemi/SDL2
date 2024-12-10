#pragma once
#include <string>
#include <string_view>
#include "TextureManager.h"
#include "IRenderer.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class SDL_Rect;



class Renderer : public IRenderer {
public:
	Renderer(SDL_Window* window);
	~Renderer();
	

	SDL_Texture* loadTexture(const std::string& p_filePath) override;
	void render(SDL_Texture* p_tex, SDL_Rect* srcRect, SDL_Rect* dstRect);
	void draw(std::string textureID, SDL_Rect* srcRect, SDL_Rect* dstRect);
	void display();
	void clear();

	


private:
	
	SDL_Renderer* renderer;

};



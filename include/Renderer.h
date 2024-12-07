#pragma once
#include <string>
#include <string_view>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class SDL_Rect;


class Renderer
{
public:
	Renderer(SDL_Window* window);
	~Renderer();
	

	void clear();
	void render(SDL_Texture* p_tex, SDL_Rect* srcRect, SDL_Rect* dstRect);
	SDL_Texture* loadTexture(std::string_view p_filePath);
	void display();

	


private:
	
	SDL_Renderer* renderer;

};



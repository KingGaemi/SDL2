#pragma once

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;


class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	~RenderWindow();
	SDL_Texture* loadTexture(const char* p_filePath);

	void clear();
	void render(SDL_Texture* p_tex);
	void display();
	

	void cleanUp();



private:
	SDL_Window* window;
	SDL_Renderer* renderer;

};



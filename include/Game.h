#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include "Renderer.h"
#include "TextureManager.h"
#include "Scene.h"
#include "MenuScene.h"
#include "EventQueue.h"



class Game{
public:
	Game();
	~Game();
	void init(const char* title, int width, int height, bool fullscreen);
	bool running() const;
	Event convertSDLEventToGameEvent(const SDL_Event& sdlEvent);
	void processGameEvents();
	void pushEvent(const Event& event);
	void changeScene(std::shared_ptr<Scene> newScene);
	void run();
	void handleEvents();
	void update();
	void render();
	void clean();
	

private:
	SDL_Window* window;
	Renderer* renderer;
	bool isRunning;
	Uint32 lastFrameTime;
	Uint32 frameStart;
	int frameTime;
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
    std::shared_ptr<Scene> currentScene;

    EventQueue gameEventQueue;

};




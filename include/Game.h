#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include "Renderer.h"
#include "TextureManager.h"
#include "Scene.h"
#include "MenuScene.h"
#include "GameplayScene.h"
#include "ECS/ECSManager.h"
#include "ECS/System.h"
#include "Systems/Systems.h"
#include "Input/InputManager.h"
#include "Events/EventSystem.h"
#include "Events/EventManager.h"





class Game{
public:
	Game();
	~Game();
	void init(const char* title, int width, int height, bool fullscreen);
	void textureLoading();
	void run();
	bool running() const;
	void render();
	Event convertSDLEventToGameEvent(const SDL_Event& sdlEvent);
	void changeScene(std::string newScene);
	void handleEvents();
	void clean();
	

private:
	SDL_Window* window;
	bool isRunning;
	Uint32 lastFrameTime;
	Uint32 frameStart;
	int frameTime;
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	std::unique_ptr<Renderer> renderer;
    std::shared_ptr<Scene> currentScene;
    std::shared_ptr<ECSManager> ecsManager;
    std::unique_ptr<TextureManager> textureManager;
    std::unique_ptr<InputManager> inputManager;
    std::unique_ptr<EventManager> eventManager;
 
    EventQueue gameEventQueue;

};




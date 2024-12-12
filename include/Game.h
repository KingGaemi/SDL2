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
#include "InputManager.h"




class Game{
public:
	Game();
	~Game();
	void init(const char* title, int width, int height, bool fullscreen);
	void textureLoading();
	void run();
	bool running() const;
	void update();
	void render();
	Event convertSDLEventToGameEvent(const SDL_Event& sdlEvent);
	void processGameEvents();
	void pushEvent(const Event& event);
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
    // std::shared_ptr<RenderSystem> renderSystem;
    // std::shared_ptr<MovementSystem> movementSystem;
    EventQueue gameEventQueue;

};




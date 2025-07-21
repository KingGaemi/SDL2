#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <memory>
#include "nlohmann/json.hpp"
#include "Renderer.h"
#include "TextureManager.h"
#include "MapManager.h"
#include "EffectManager.h"
#include "Manager/SoundManager.h"
#include "Manager/CursorManager.h"
#include "Manager/GameManager.h"
#include "Manager/SpawnManager.h"
#include "Scene.h"
#include "MenuScene.h"
#include "GameplayScene.h"
#include "CharacterSelectScene.h"
#include "ecs/ECSManager.h"
#include "ecs/System.h"
#include "ecs/EntityFactory.h"
#include "Systems/Systems.h"
#include "Input/InputManager.h"
#include "Events/EventSystem.h"
#include "Events/EventManager.h"
#include "Events/MiddleEventSystem.h"




class Game{
public:
	Game();
	~Game();
	void init(const char* title, int width, int height, bool fullscreen);
	void textureLoading();
	void soundLoading();
	void run();
	bool running() const;
	Event convertSDLEventToGameEvent(const SDL_Event& sdlEvent);
	void changeScene(std::string newScene);
	void clean();
	
private:
	SDL_Window* window;
	bool isRunning, pause, gameOver;
	Uint32 lastFrameTime;
	Uint32 frameStart;
	int frameTime;
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	std::unique_ptr<Renderer> renderer;
    std::shared_ptr<Scene> currentScene;
    std::shared_ptr<ECSManager> ecsManager;
    std::shared_ptr<GameManager> gameManager;
    std::shared_ptr<EntityFactory> entityFactory;
    std::shared_ptr<EventManager> eventManager;
    std::shared_ptr<MapManager> mapManager;
    std::shared_ptr<EffectManager> effectManager;
 	std::shared_ptr<SoundManager> soundManager;
 	std::shared_ptr<CursorManager> cursorManager;
	std::shared_ptr<SpawnManager> spawnManager;
    std::unique_ptr<TextureManager> mapTextureManager;
    std::unique_ptr<TextureManager> textureManager;
    std::unique_ptr<TextureManager> uiTextureManager;
    std::unique_ptr<InputManager> inputManager;

};




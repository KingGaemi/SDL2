#include "Game.h"




Game::Game() : window(nullptr),  isRunning(false), lastFrameTime(0) {}


Game::~Game() {
    clean();
}


void Game::init(const char* title, int width, int height, bool fullscreen){


	// Init Video
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init FAILED. SDL_ERROR:" << SDL_GetError() << std::endl;
		return;
	}
	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "IMG_Init Failed: " << IMG_GetError() << std::endl;
        return;
    }
    

	// Create Window
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return;
    }

    // Create renderer
    renderer = std::make_unique<Renderer>(window);

    // Create manager
    ecsManager = std::make_shared<ECSManager>();
    eventManager = std::make_unique<EventManager>();
    inputManager = std::make_unique<InputManager>(eventManager->get());


    // Add Systems
    ecsManager->addSystem<RenderSystem>(*renderer);
    ecsManager->addSystem<MovementSystem>();
    ecsManager->addSystem<EventSystem>(eventManager->get());
    ecsManager->addSystem<AnimationSystem>();
    ecsManager->addSystem<InputSystem>();
    ecsManager->addSystem<TimerSystem>();
    ecsManager->addSystem<ExpireSystem>(ecsManager);
    ecsManager->addSystem<AttackSystem>(ecsManager);

    textureLoading();
    
    currentScene = std::make_shared<MenuScene>(ecsManager);
    currentScene->onEnter();

	isRunning = true;
}



void Game::textureLoading(){

    textureManager = std::make_unique<TextureManager>(*renderer);
    textureManager->loadTexture("background_main", "res/gfx/SunnyLand/Environment/back.png");
    textureManager->loadTexture("player_eri", "res/gfx/eri_copy2.png");
    textureManager->loadTexture("streetlamp", "res/gfx/streetlamp3.png");
    textureManager->loadTexture("farmer", "res/gfx/1/player_sprite_sheet.png");
    textureManager->loadTexture("water_tile", "res/gfx/water_tile.png");
    textureManager->loadTexture("orc3", "res/gfx/SpriteSheet/Orc/orc3_sprite_sheet.png");


    auto rendersys = ecsManager->getSystem<RenderSystem>();
    rendersys->setTextureManager(std::move(textureManager));

}

void Game::run() {

    
    while (isRunning) {
        frameStart = SDL_GetTicks();

        // 1. 입력 처리 → InputManager가 SDL 이벤트를 EventManager에 푸시
        inputManager->handleEvents();

        // deltaTime 구하기
        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f; // 초 단위 시간
        lastFrameTime = currentFrameTime;

        // 2. ECS 시스템 업데이트 → EventSystem이 SCENE_CHANGE 이벤트 발생 가능
        ecsManager->updateSystems(deltaTime); 

        // 3. EventManager에서 이벤트 폴링 → SCENE_CHANGE나 QUIT 처리
        Event evt;
        while (eventManager->pollBigEvent(evt)) {
            // std::cout << "polling Big Event" << std::endl;
            if (evt.type == EventType::SCENE_CHANGE && evt.sceneChangeData.has_value()) {

                changeScene(evt.sceneChangeData->nextSceneName);
            }
            if (evt.type == EventType::QUIT) {
                isRunning = false;
            }
        }

        // 4. 씬의 update, render 호출 (씬이 직접 이벤트 처리 안함)
        if (currentScene) {
            currentScene->update(deltaTime);
            currentScene->render();
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
          SDL_Delay(frameDelay - frameTime);
        }
    }

}

bool Game::running() const {
    return isRunning;
}

void Game::render() {

}

void Game::handleEvents() {
    inputManager->handleEvents();
}

void Game::changeScene(std::string sceneName) {

    if (sceneName == "GameplayScene") {
        std::cout << "Switching to Gameplay Scene..." << std::endl;
        currentScene->onExit();
        currentScene = std::make_shared<GameplayScene>(ecsManager);
        currentScene->onEnter();
    }
} 

void Game::clean() {
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
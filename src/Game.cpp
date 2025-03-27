
#include "Game.h"


Game::Game() : window(nullptr),  isRunning(false), lastFrameTime(0) {}


Game::~Game() {
    clean();
}


void Game::init(const char* title, int width, int height, bool fullscreen){


	// Init Video
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
		std::cout << "SDL_Init FAILED. SDL_ERROR:" << SDL_GetError() << std::endl;
		return;
	}

	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    // SDL_mixer 초기화 (44100 Hz, 스테레오, 2048 샘플 버퍼 크기)
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer : " << Mix_GetError() << std::endl;
        return;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "IMG_Init Failed: " << IMG_GetError() << std::endl;
        return;
    }

    if (TTF_Init() == -1){
        std::cerr << "TTF_Init Failed: " << TTF_GetError() << std::endl;
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
    ecsManager = std::make_shared<ECSManager>();
    ecsManager->entityFactory = std::make_shared<EntityFactory>(ecsManager);
    eventManager = std::make_shared<EventManager>();
    soundManager = std::make_shared<SoundManager>();
    ecsManager->eventManager = eventManager;
    inputManager = std::make_unique<InputManager>(eventManager);
    mapManager = std::make_shared<MapManager>(ecsManager);
    effectManager = std::make_shared<EffectManager>();
    cursorManager = std::make_shared<CursorManager>();
    // Add Systems
    // Render
    ecsManager->addSystem<WorldRenderSystem>(SystemGroup::Render, 100, *renderer, ecsManager, effectManager);
    ecsManager->addSystem<UIRenderSystem>(SystemGroup::Render, 200, *renderer, ecsManager, effectManager);
    // Logic
    ecsManager->addSystem<EventSystem>(SystemGroup::Logic, 10, eventManager, cursorManager);
    ecsManager->addSystem<TimerSystem>(SystemGroup::Logic, 30);
    ecsManager->addSystem<CommandSystem>(SystemGroup::Logic, 40, eventManager);
    ecsManager->addSystem<PhysicsSystem>(SystemGroup::Logic, 50, ecsManager, eventManager, mapManager);
    // ecsManager->addSystem<CollisionSystem>(SystemGroup::Logic, 60, ecsManager);
    ecsManager->addSystem<CameraSystem>(SystemGroup::Logic, 70, ecsManager);
    ecsManager->addSystem<ExpireSystem>(SystemGroup::Logic, 90);
    // ecsManager->addSystem<MovementSystem>(SystemGroup::Logic, 100);
    ecsManager->addSystem<DamageSystem>(SystemGroup::Logic, 100, ecsManager, eventManager, soundManager);
    ecsManager->addSystem<EffectSystem>(SystemGroup::Logic, 110, effectManager);
    ecsManager->addSystem<AnimationSystem>(SystemGroup::Logic, 150);
    ecsManager->addSystem<SyncSystem>(SystemGroup::Logic, 160);
    ecsManager->addSystem<AttackSystem>(SystemGroup::Logic, 200, ecsManager, eventManager, soundManager);
    ecsManager->addSystem<CooldownSystem>(SystemGroup::Logic, 250);
    ecsManager->addSystem<AISystem>(SystemGroup::Logic, 300);
    ecsManager->addSystem<KillSystem>(SystemGroup::Logic, 400);
    ecsManager->addSystem<SpawnSystem>(SystemGroup::Logic, 500, ecsManager);
    // Event
    ecsManager->addSystem<CollisionEventHandlerSystem>(SystemGroup::Event, 180, ecsManager);
    ecsManager->addSystem<MiddleEventSystem>(SystemGroup::Event, 200, eventManager);

    // auto physSys = ecsManager->getSystem<PhysicsSystem>();
    // ecsManager->setPhysicsSystem(physSys);
    cursorManager->init();

    textureLoading();
    soundLoading();

    currentScene = std::make_shared<MenuScene>(ecsManager);
    currentScene->onEnter();


	isRunning = true;
}



void Game::textureLoading(){

    textureManager = std::make_unique<TextureManager>(*renderer);



    json j = json::parse(std::ifstream("json/texturePath/texturePathes.json"));

    for (const auto& texture : j["textures"]) {
        std::string textureId = texture["textureId"];
        std::string path = texture["path"];
        
        textureManager->loadTexture(textureId, path);
    }

    // textureManager->loadText("12345");
    // textureManager->loadTexture("shadow6", "res/gfx/sprite_sheets/map/shadow6.png");
    // textureManager->loadText("Hello World!");
    // textureManager->loadTexture("farm_map",);

    auto worldRenderSys = ecsManager->getSystem<WorldRenderSystem>();
    worldRenderSys->setTextureManager(*textureManager.get());

    auto uiRenderSys = ecsManager->getSystem<UIRenderSystem>();
    uiRenderSys->setTextureManager(*textureManager.get());

    mapManager->setTextureManager(*textureManager.get());
    mapManager->init();
    // auto mapSys = ecsManager->getSystem<MapSystem>();
    // mapSys->setTextureManager(*textureManager.get());
    
}


void Game::soundLoading(){

    // 효과음 로드 (WAV)
    std::string path = "res/sounds/effect/impale_flesh.mp3";
    soundManager->loadEffect("metal_hit_flesh", path);
    path = "res/sounds/bgm/bgsound.mp3";
    soundManager->loadMusic("bgmWind", path);
    path = "res/sounds/effect/orc_death.mp3";
    soundManager->loadEffect("orc_death", path);
    path = "res/sounds/effect/orc_swing.mp3";
    soundManager->loadEffect("orc_swing", path);
    path = "res/sounds/effect/hit-swing-sword-small-2-95566.mp3";
    soundManager->loadEffect("metal_slash_flesh", path);

    path = "res/sounds/effect/hit-rock-02-266304.mp3";
    soundManager->loadEffect("metal_slash_rock", path);

    soundManager->registerEffects();
    soundManager->setEffectVolume(20);
    

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
        ecsManager->processTerminatedEntities();
        ecsManager->updateSystems(deltaTime);
        ecsManager->renderSystems(deltaTime);
        ecsManager->processSpawnRequests();
        ecsManager->processCollisionEvents();
        

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
        
        ecsManager->cleanUpEntities();

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
        currentScene = std::make_shared<GameplayScene>(ecsManager, mapManager);
        currentScene->onEnter();
    }
} 

void Game::clean() {
    SDL_DestroyWindow(window);
    soundManager->cleanup();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
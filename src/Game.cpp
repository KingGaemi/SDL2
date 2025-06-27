
#include "Game.h"


Game::Game() : window(nullptr),  isRunning(false), lastFrameTime(0) {}


Game::~Game() {
    clean();
}


void Game::init(const char* title, int width, int height, bool fullscreen){

    // SDL 관련 라이브러리 초기화 -> 구현한 매니저들 생성 -> ecsManager에 시스템 추가 -> 필요한 텍스처처 로드 -> 게임 가동
    // (텍스처 로드는 현재 프로젝트가 작아 Game::init 내에서 모두 로드중)

	// SDL_video 초기화
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
		std::cout << "SDL_Init FAILED. SDL_ERROR:" << SDL_GetError() << std::endl;
		return;
	}

    // 0 = 창모드 , 1 = 전체화면
	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    // SDL_mixer 초기화  (44100 Hz, 스테레오, 2048 샘플 버퍼 크기)
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer : " << Mix_GetError() << std::endl;
        return;
    }

    // SDL_image 초기화
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "IMG_Init Failed: " << IMG_GetError() << std::endl;
        return;
    }

    // SDL_font 초기화
    if (TTF_Init() == -1){
        std::cerr << "TTF_Init Failed: " << TTF_GetError() << std::endl;
        return;
    }
    
	// 창 생성성
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return;
    }

    // 매니저 생성
    renderer = std::make_unique<Renderer>(window);
    ecsManager = std::make_shared<ECSManager>();
    gameManager = std::make_shared<GameManager>(ecsManager);
    eventManager = std::make_shared<EventManager>();
    spawnManager = std::make_shared<SpawnManager>(ecsManager);
    gameManager->setEventManager(eventManager);
    ecsManager->entityFactory = std::make_shared<EntityFactory>(ecsManager, gameManager);
    soundManager = std::make_shared<SoundManager>();
    ecsManager->eventManager = eventManager;
    inputManager = std::make_unique<InputManager>(eventManager);
    mapManager = std::make_shared<MapManager>(ecsManager);
    effectManager = std::make_shared<EffectManager>();
    cursorManager = std::make_shared<CursorManager>();
    // 시스템 추가
    // 랜더링 시스템군
    ecsManager->addSystem<WorldRenderSystem>(SystemGroup::Render, 100, *renderer, ecsManager, effectManager);
    ecsManager->addSystem<UIRenderSystem>(SystemGroup::UI, 200, *renderer, ecsManager, effectManager);
    // 논리 시스템군
    ecsManager->addSystem<EventSystem>(SystemGroup::Logic, 10, eventManager, cursorManager);
    ecsManager->addSystem<TimerSystem>(SystemGroup::Logic, 30);
    ecsManager->addSystem<CommandSystem>(SystemGroup::Logic, 40, eventManager);
    ecsManager->addSystem<PhysicsSystem>(SystemGroup::Logic, 50, ecsManager, eventManager, mapManager);
    ecsManager->addSystem<CameraSystem>(SystemGroup::Logic, 70, ecsManager);
    ecsManager->addSystem<ExpireSystem>(SystemGroup::Logic, 90);
    ecsManager->addSystem<DamageSystem>(SystemGroup::Logic, 100, ecsManager, eventManager, soundManager);
    ecsManager->addSystem<EffectSystem>(SystemGroup::Logic, 110, effectManager);
    ecsManager->addSystem<AnimationSystem>(SystemGroup::Logic, 150);
    ecsManager->addSystem<SyncSystem>(SystemGroup::Logic, 160);
    ecsManager->addSystem<AttackSystem>(SystemGroup::Logic, 200, ecsManager, eventManager, soundManager);
    ecsManager->addSystem<CooldownSystem>(SystemGroup::Logic, 250);
    ecsManager->addSystem<AISystem>(SystemGroup::Logic, 300);
    ecsManager->addSystem<KillSystem>(SystemGroup::Logic, 400, gameManager);
    ecsManager->addSystem<SpawnSystem>(SystemGroup::Logic, 500, ecsManager);
    // 이벤트 시스템군
    ecsManager->addSystem<CollisionEventHandlerSystem>(SystemGroup::Event, 180, ecsManager);
    ecsManager->addSystem<MiddleEventSystem>(SystemGroup::Event, 200, eventManager);


    // Json 파일 형식의 텍스쳐 & 음향의 경로 로드
    textureLoading();
    soundLoading();

    // 현재 씬을 메뉴 씬으로 결정
    currentScene = std::make_shared<MenuScene>(ecsManager);
    currentScene->onEnter();

    // 게임 가동
	isRunning = true;
}



void Game::textureLoading(){

    // 텍스처 매니저 생성
    textureManager = std::make_unique<TextureManager>(*renderer);

    // json 형식의 파일 로드 'nlohmann/json' 이용중
    json j = json::parse(std::ifstream("json/texturePath/texturePathes.json"));

    for (const auto& texture : j["textures"]) {
        std::string textureId = texture["textureId"];
        std::string path = texture["path"];
        
        textureManager->loadTexture(textureId, path);
    }


    // 랜더링 관련 시스템, 매니저와 텍스처 매니저 연결
    auto worldRenderSys = ecsManager->getSystem<WorldRenderSystem>();
    worldRenderSys->setTextureManager(*textureManager.get());

    auto uiRenderSys = ecsManager->getSystem<UIRenderSystem>();
    uiRenderSys->setTextureManager(*textureManager.get());

    mapManager->setTextureManager(*textureManager.get());
    mapManager->init();

}


void Game::soundLoading(){

    // 효과음 로드 (WAV)
    // 현재는 파일 경로 직접 지정중 (텍스처 로딩과 동일하게 업그레이드 예정정)
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

    // initialize before loop
    lastFrameTime = SDL_GetTicks();
    while (isRunning) {
        frameStart = SDL_GetTicks();

        // 1. 입력 처리 → InputManager가 SDL 이벤트를 EventManager에 푸시
        inputManager->handleEvents();

        // 프레임 시간 계산 (단위 : 초)
        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f; // 초 단위 시간
        lastFrameTime = currentFrameTime;

        // 2. ECS 시스템 처리 (Entity 삭제, 시스템 업데이트 및 렌더링, 새로운 Entity 스폰, 충돌 이벤트 처리) 
        ecsManager->processTerminatedEntities();
        ecsManager->updateSystems(deltaTime);
        ecsManager->renderSystems(deltaTime);
        if(pause||gameOver) renderer->addDarkOverlay();
        ecsManager->renderUI(deltaTime);
        ecsManager->processSpawnRequests();
        // ecsManager->processCollisionEvents();
        

        // 3. 주요 이벤트 처리 (SCENE_CHANGE, QUIT 등..)
        Event evt;
        while (eventManager->pollBigEvent(evt)) {
            if (evt.type == EventType::SCENE_CHANGE && evt.sceneChangeData.has_value()) {
                changeScene(evt.sceneChangeData->nextSceneName);
            }
            if (evt.type == EventType::QUIT) {
                isRunning = false;
            }
            if (evt.type == EventType::PAUSE) {
                ecsManager->removeSystem<AnimationSystem>();
                ecsManager->removeSystem<PhysicsSystem>();
                ecsManager->removeSystem<CommandSystem>();
                ecsManager->removeSystem<TimerSystem>();
                ecsManager->removeSystem<EffectSystem>();
                ecsManager->removeSystem<SpawnSystem>();
                // ecsManager->removeSystem<AISystem>();
                pause = true;
            }
            if (evt.type == EventType::RESUME) {
                ecsManager->addSystem<AnimationSystem>(SystemGroup::Logic, 150);
            }
            if (evt.type == EventType::GAMEOVER) {
                ecsManager->removeSystem<KillSystem>();
                ecsManager->removeSystem<EffectSystem>();
                ecsManager->removeSystem<CommandSystem>();
                ecsManager->removeSystem<EventSystem>();
                gameOver = true;
            }
        }

        // 제거해야할 엔티티 정리
        ecsManager->cleanUpEntities();

        
        // 프레임 조절
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
          SDL_Delay(frameDelay - frameTime);
        }
    }
}

bool Game::running() const {
    return isRunning;
}

void Game::changeScene(std::string sceneName) {

    // 씬 전환 이벤트는 가끔 일어나므로 string 데이터 비교 사용중
    if (sceneName == "GameplayScene") {
        std::cout << "Switching to Gameplay Scene..." << std::endl;
        currentScene->onExit();
        currentScene = std::make_shared<GameplayScene>(ecsManager, mapManager);
        currentScene->onEnter();
    }
    if (sceneName == "CharacterSelectScene") {
        std::cout << "Switching to Character Select Scene..." << std::endl;
        currentScene->onExit();
        currentScene = std::make_shared<CharacterSelectScene>(ecsManager, gameManager);
        currentScene->onEnter();
    }
} 

void Game::clean() {
    // 종료 시 SDL 관련 모두 정리
    SDL_DestroyWindow(window);
    soundManager->cleanup();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
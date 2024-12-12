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
    // renderSystem = std::make_shared<RenderSystem>(*renderer);
    // movementSystem = std::make_shared<MovementSystem>();
    ecsManager->addSystem<RenderSystem>(*renderer);
    ecsManager->addSystem<MovementSystem>();

    textureLoading();
    

    inputManager = std::make_unique<InputManager>();
    inputManager->setQuitCallback([this]() {
        this->isRunning = false;
    });

    currentScene = std::make_shared<MenuScene>(
        ecsManager,
        [this](const std::string& newSceneName){
        this->changeScene(newSceneName); // 콜백 함수 등록
        }
        
    );
    std::cout << "NewScene " << std::endl;
    currentScene->onEnter();

	isRunning = true;
}



void Game::textureLoading(){

    textureManager = std::make_unique<TextureManager>(*renderer);
    textureManager->loadTexture("background_main", "res/gfx/SunnyLand/Environment/back.png");
    textureManager->loadTexture("player_eri", "res/gfx/eri_copy2.png");
    textureManager->loadTexture("streetlamp", "res/gfx/streetlamp3.png");

    auto rendersys = ecsManager->getSystem<RenderSystem>();
    rendersys->setTextureManager(std::move(textureManager));

}




// Run ========


void Game::run() {

    
    while(isRunning)
    {
        frameStart = SDL_GetTicks();

        handleEvents();
        update();
        render();


        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay> frameTime){
            SDL_Delay(frameDelay- frameTime);
        }
    }

}

bool Game::running() const {
    return isRunning;
}

// Update =======


void Game::update() {
    Uint32 currentFrameTime = SDL_GetTicks();
    float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f; // 초 단위 시간
    lastFrameTime = currentFrameTime;

    if (currentScene) {
        currentScene->update(deltaTime);
    }
}


void Game::render() {

    // if (currentScene) {
    //     currentScene->render();
    // }

}




// Events =======


// Event Game::convertSDLEventToGameEvent(const SDL_Event& sdlEvent) {
//     Event gameEvent;

//     switch (sdlEvent.type) {
//     case SDL_QUIT:
//         gameEvent.type = "QUIT";
//         break;
//     case SDL_KEYDOWN:
//         gameEvent.type = "KEYDOWN";
//         gameEvent.key = sdlEvent.key.keysym.sym;
//         break;
//     case SDL_KEYUP:
//         gameEvent.type = "KEYUP";
//         gameEvent.key = sdlEvent.key.keysym.sym;
//         break;
//     default:
//         gameEvent.type = "UNKNOWN";
//         break;
//     }

//     return gameEvent;
// }





void Game::handleEvents() {
    inputManager->pollEvents();
    if (currentScene) {
        currentScene->handleEvents(inputManager->getEvents());
    }
    
}


void Game::changeScene(std::string sceneName) {

    if (sceneName == "GameplayScene") {
        std::cout << "Switching to Gameplay Scene..." << std::endl;
        currentScene = std::make_shared<GameplayScene>(
            ecsManager,
            [this](const std::string& newSceneName) {
                this->changeScene(newSceneName); // 새로운 씬의 콜백 설정
            }
        );
        std::cout << "callbackFunction ready" << std::endl;
        currentScene->onEnter();
    }
} 


void Game::pushEvent(const Event& event){
    gameEventQueue.push(event);
}


void Game::processGameEvents() {

    while (!gameEventQueue.isEmpty()) {
        Event event = gameEventQueue.pop();
        if (event.type == "GAME_OVER") {
            //endGame();
        }
    }
}










void Game::clean() {
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
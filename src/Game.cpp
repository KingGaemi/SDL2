#include "Game.h"




Game::Game() : window(nullptr), renderer(nullptr), isRunning(false), lastFrameTime(0) {}


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



	// Create Window
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return;
    }

    // Create renderer
    renderer = new Renderer(window);

    // Create manager
    manager = std::make_shared<ECSManager>();


    currentScene = std::make_shared<MenuScene>(
        [this](const std::shared_ptr<Scene> newScene){
        this->changeScene(newScene->getName()); // 콜백 함수 등록
        },
        manager
    );

    currentScene->init(renderer);

	isRunning = true;
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


// Events =======


Event Game::convertSDLEventToGameEvent(const SDL_Event& sdlEvent) {
    Event gameEvent;

    switch (sdlEvent.type) {
    case SDL_QUIT:
        gameEvent.type = "QUIT";
        break;
    case SDL_KEYDOWN:
        gameEvent.type = "KEYDOWN";
        gameEvent.key = sdlEvent.key.keysym.sym;
        break;
    case SDL_KEYUP:
        gameEvent.type = "KEYUP";
        gameEvent.key = sdlEvent.key.keysym.sym;
        break;
    default:
        gameEvent.type = "UNKNOWN";
        break;
    }

    return gameEvent;
}





void Game::handleEvents() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            isRunning = false;
        }

        Event gameEvent = convertSDLEventToGameEvent(sdlEvent);

        if (currentScene) {
            currentScene->handleEvents(gameEvent);
        }
    }
}

void Game::changeScene(std::string sceneName) {

    if (sceneName == "GameplayScene") {
        std::cout << "Switching to Gameplay Scene..." << std::endl;
        currentScene = std::make_shared<GameplayScene>(
            [this](const std::shared_ptr<Scene> newScene) {
                this->changeScene(newScene->getName()); // 새로운 씬의 콜백 설정
            },
            manager
        );
        std::cout << "callbackFunction ready" << std::endl;
        currentScene->init(renderer);
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
    if (currentScene) {
        currentScene->render(renderer);
    }
    renderer->display();
}







void Game::clean() {
    delete renderer;
    SDL_DestroyWindow(window);
    SDL_Quit();
}
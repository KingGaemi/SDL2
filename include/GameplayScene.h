#pragma once
#include <memory>
#include "Scene.h"
#include "Requests.h"

class Entity;




class GameplayScene: public Scene{
public:
	GameplayScene(std::shared_ptr<ECSManager> ecsManager) : Scene("GameplayScene", ecsManager){}
	// ~GameplayScene() override;
	void onEnter() override;
	void handleEvents(const std::vector<Event>& events) override;
	void render() override;
	void onExit() override;
	void update(float deltaTime) override;

	void pushEvent(const Event& event);
private:
	std::shared_ptr<Entity> player;
	std::shared_ptr<Entity> farmer;
	// std::vector<SpawnRequest> gamePlaySceneSpawnRequests;
	// std::unique_ptr<KeyboardController> keyboardController;

};
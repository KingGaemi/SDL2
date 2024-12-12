#pragma once
#include <memory>
#include "Scene.h"

class Entity;



class GameplayScene: public Scene{
public:
	GameplayScene(std::shared_ptr<ECSManager> ecsManager, ChangeSceneCallback callback) : Scene("GameplayScene", ecsManager , callback){}
	// ~GameplayScene() override;
	void onEnter() override;
	void handleEvents(const std::vector<Event>& events) override;
	void render() override;
	void onExit() override;
	void update(float deltaTime) override;

	void pushEvent(const Event& event);
private:
	std::shared_ptr<Entity> player;

	// std::unique_ptr<KeyboardController> keyboardController;

};
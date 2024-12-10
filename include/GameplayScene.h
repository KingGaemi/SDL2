#pragma once
#include <memory>
#include "Scene.h"
#include "ECS/ECSManager.h"
#include "ECS/Entity.h"
#include "Components/Components.h"



class GameplayScene: public Scene{
public:
	GameplayScene(ChangeSceneCallback callback, std::shared_ptr<ECSManager> manager) : Scene("GameplayScene", callback), manager(manager) {}
	void init(Renderer* renderer) override;
	void handleEvents(Event& event) override;
	void handleInput();
	void render(Renderer* renderer) override;
	void clean();
	void update(float deltaTime) override;

	void pushEvent(const Event& event);
private:
	EventQueue sceneEventQueue;
	std::shared_ptr<ECSManager> manager;
	std::shared_ptr<Entity> player;
	TransformComponent* playerTransform;

};
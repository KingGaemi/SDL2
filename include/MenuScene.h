#pragma once
#include "Scene.h"
#include "ECS/ECSManager.h"




class MenuScene : public Scene{
public:
	MenuScene(ChangeSceneCallback callback, std::shared_ptr<ECSManager> manager) : Scene("MenuScene", callback), manager(manager) {}
	void init(Renderer* renderer) override;
	void handleEvents(Event& event) override;
	void render(Renderer* renderer) override;
	void clean();
	void update(float deltaTime) override;

	void pushEvent(const Event& event);
private:
	EventQueue sceneEventQueue;
	std::shared_ptr<ECSManager> manager;
};
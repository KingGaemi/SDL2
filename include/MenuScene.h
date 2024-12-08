#pragma once

#include "Scene.h"




class MenuScene : public Scene{
public:
	MenuScene(ChangeSceneCallback callback) : Scene(callback) {}
	void init(Renderer* renderer) override;
	void handleEvents(Event& event) override;
	void render(Renderer* renderer) override;
	void clean();
	void update(float deltaTime) override;

	void pushEvent(const Event& event);
private:
	EventQueue sceneEventQueue;
};
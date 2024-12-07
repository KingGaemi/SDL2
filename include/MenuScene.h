#pragma once

#include "EventQueue.h"
#include "Scene.h"
#include "TextureManager.h"
#include "Renderer.h"
#include <iostream>



class MenuScene : public Scene{
public:
	void init(Renderer* renderer) override;
	void handleEvents(Event& event) override;
	void render(Renderer* renderer) override;
	void clean();
	void update(float deltaTime) override;

	void pushEvent(const Event& event);
private:
	EventQueue sceneEventQueue;
};
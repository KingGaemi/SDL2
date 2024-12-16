#pragma once
#include "Scene.h"




class Entity;



class MenuScene : public Scene{
public:
	MenuScene(std::shared_ptr<ECSManager> ecsManager) : Scene("MenuScene", ecsManager){}
	// ~MenuScene() override;	
	void onEnter() override;
	void onExit() override;
	void handleEvents(const std::vector<Event>& events) override;
	void update(float deltaTime) override;
	void render() override;

private:

	std::shared_ptr<Entity> background;

};
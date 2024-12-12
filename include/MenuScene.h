#pragma once
#include "Scene.h"




class Entity;



class MenuScene : public Scene{
public:
	MenuScene(std::shared_ptr<ECSManager> ecsManager, ChangeSceneCallback callback) : Scene("MenuScene", ecsManager, callback){}
	// ~MenuScene() override;	
	void onEnter() override;
	void onExit() override;
	void handleEvents(const std::vector<Event>& events) override;
	void update(float deltaTime) override;
	void render() override;

private:

};
#pragma once
#include "Manager/GameManager.h"
#include "Scene.h"
#include "Requests.h"
#include "Groups.h"



class Entity;
class CharacterSelectScene : public Scene{
public:
	CharacterSelectScene(std::shared_ptr<ECSManager> ecsManager, std::shared_ptr<GameManager> gameManager) : Scene("CharacterSelectScene", ecsManager), gameManager(gameManager){}
	// ~MenuScene() override;	
	void onEnter() override;
	void onExit() override;
	void handleEvents(const std::vector<Event>& events) override;
	void update(float deltaTime) override;
	void render() override;

private:
	 std::shared_ptr<GameManager> gameManager;
	

};
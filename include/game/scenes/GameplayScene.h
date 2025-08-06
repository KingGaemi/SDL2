#pragma once
#include <memory>
#include "Scene.h"
#include "engine/event/Requests.h"
#include "MapManager.h"

class Entity;




class GameplayScene: public Scene{
public:
	GameplayScene(std::shared_ptr<ECSManager> ecsManager, std::shared_ptr<MapManager> p_mapManager) : Scene("GameplayScene", ecsManager){
		mapManager = p_mapManager;
	}
	// ~GameplayScene() override;
	void onEnter() override;
	void handleEvents(const std::vector<Event>& events) override;
	void render() override;
	void onExit() override;
	void update(float deltaTime) override;

	void pushEvent(const Event& event);
private:
	std::shared_ptr<MapManager> mapManager;

};
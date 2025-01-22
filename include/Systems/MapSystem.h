#pragma once

#include "nlohmann/json.hpp"
#include "ECS/System.h"
#include "ECS/Entity.h"
#include "ECS/ECSManager.h"
#include "Components/MapComponent.h"
#include "RenderSystem.h"


using json = nlohmann::json;


class MapSystem : public RenderSystem{

public:
	using RenderSystem::RenderSystem;
	MapSystem(Renderer& renderer, std::shared_ptr<ECSManager>& ecsManager)
			: RenderSystem(renderer, ecsManager), ecsManager(ecsManager) {}

	
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;
	void init();
	void parseTileLayer(const json& layerJson);
	void parseObjectLayer(const json& layerJson);
	std::shared_ptr<Entity> getMapEntity(){return mapEntity;}

private:
	int mapWidth, mapHeight, tileWidth, tileHeight;
	std::shared_ptr<ECSManager> ecsManager;
	std::shared_ptr<Entity> mapEntity;
	std::shared_ptr<Entity> cameraEntity;
	std::shared_ptr<MapComponent> mapComp;
	json mapJson;
	json tileJson;
};
#pragma once
#include "RenderSystem.h"

#include <iostream>

class WorldRenderSystem : public RenderSystem {
public:
	using RenderSystem::RenderSystem;


    void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override {

        for (auto& entity : entities) {
            if (!entity->isActive) continue;
            if (entity->hasComponent<UITag>()) continue;
            if (entity->hasComponent<PositionComponent>() && entity->hasComponent<SpriteComponent>()) drawEntity(entity);
        }    
    }

};
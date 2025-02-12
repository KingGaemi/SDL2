#pragma once
#include "RenderSystem.h"
#include "Components/HitboxComponent.h"
#include <iostream>

class WorldRenderSystem : public RenderSystem {
public:
	using RenderSystem::RenderSystem;
    WorldRenderSystem(Renderer& renderer, std::shared_ptr<ECSManager>& ecsManager)
            : RenderSystem(renderer, ecsManager){}

    void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;
private:    
    
};
#pragma once
#include "engine/ecs/systems/rendering/RenderSystem.h"
#include <iostream>

class WorldRenderSystem : public RenderSystem {
public:
	using RenderSystem::RenderSystem;
    // WorldRenderSystem(Renderer& renderer, std::shared_ptr<ECSManager>& ecsManager)
    //         : RenderSystem(renderer, ecsManager){}

    void update(float deltaTime) override;
    void renderMap(std::shared_ptr<Entity>& entity);
private:    
    
};
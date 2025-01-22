#pragma once
#include "RenderSystem.h"

#include <iostream>

class WorldRenderSystem : public RenderSystem {
public:
	using RenderSystem::RenderSystem;
    WorldRenderSystem(Renderer& renderer, std::shared_ptr<ECSManager>& ecsManager)
            : RenderSystem(renderer, ecsManager), ecsManager(ecsManager) {}


    void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override {

        for(auto& entity : entities){
            if(entity->hasComponent<CameraComponent>()) cameraEntity = entity;
        }

        std::vector<std::shared_ptr <Entity>> renderables;
        for (auto& e : entities) {
            if (e->hasComponent<PositionComponent>() && e->hasComponent<SpriteComponent>()) {
                renderables.push_back(e);
            }
        }

        // 2) 정렬 (y 좌표 기준 오름차순)
        std::sort(renderables.begin(), renderables.end(), 
            [](std::shared_ptr <Entity> a, std::shared_ptr <Entity> b){
                auto pa = a->getComponent<PositionComponent>();
                auto pb = b->getComponent<PositionComponent>();
                auto sa = a->getComponent<SpriteComponent>();
                auto sb = b->getComponent<SpriteComponent>();

                // 혹은 pa->y + pa->height 등, 원하는 기준
                return pa->y - sa->dstRect.h/2 < pb->y - sb->dstRect.h/2; 
            }
        );

        for (auto& entity : renderables) {
            if (entity->hasComponent<UITag>()) continue;
            drawEntity(entity);
        }


    }
private:
    // std::shared_ptr<Entity> cameraEntity;
    std::shared_ptr<ECSManager> ecsManager;
};
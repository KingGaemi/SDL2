#pragma once
#include "RenderSystem.h"


class UIRenderSystem : public RenderSystem {
	using RenderSystem::RenderSystem;

    void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override {
        // UI는 굳이 clear()하지 않고, 이미 월드가 그려진 위에 덧그릴 수 있음
        // renderer->clear(); // 대부분 생략
        cameraEntity = ecsManager->getCamera();
        for (auto& entity : entities) {
            if (!entity->isActive) continue;
            // UI 태그가 있어야만 그린다거나...
            if (!entity->hasComponent<UITag>()) continue;
            drawEntity(entity);
            
        }
        drawEffects();
        for (auto& entity : entities) {
            if (!entity->isActive) continue;
            // UI 태그가 있어야만 그린다거나...
            if (!entity->hasComponent<TextLabelComponent>()) continue;
            drawText(entity);
            
        }

        // 여기서 최종 display()
        renderer->display();
    }
	
};
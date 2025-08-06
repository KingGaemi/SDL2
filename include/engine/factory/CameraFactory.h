#pragma once
#include "engine/ecs/core/ECSCoordinator.h"
#include "game/ecs/components/tags/Groups.h"
#include "engine/ecs/components/status/TransformComponent.h"
#include "engine/ecs/components/status/PositionComponent.h"
#include "engine/ecs/components/rendering/CameraComponent.h"





class CameraFactory {
    ECSCoordinator& ecs;

public:
    CameraFactory(ECSCoordinator& coordinator) : ecs(coordinator) {}

    EntityID createMainCamera(float x, float y, int w, int h) {
        auto cam = ecs.createEntity();
        auto id = cam->getId();
        ecs.addComponent<SceneTag>(id, cam, SceneCode::Game);
        ecs.addComponent<TransformComponent>(id, cam);
        ecs.addComponent<PositionComponent>(id, cam, x, y);
        ecs.addComponent<CameraComponent>(id, cam, w, h);
        return id;
    }

};
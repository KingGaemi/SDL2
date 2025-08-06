#pragma once
#include <algorithm>
#include "engine/ecs/core/EntityManager.h"

std::shared_ptr<Entity> EntityManager::create() {
    auto entity = std::make_shared<Entity>(nextID++);
    entities.push_back(entity);
    return entity;
}

void EntityManager::destroy(const std::shared_ptr<Entity>& entity) {
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());

}

std::shared_ptr<Entity> EntityManager::getById(std::size_t id) const{
    for (auto& e : entities) {
        if (e->getId() == id) return e;
    }
    return nullptr;
}



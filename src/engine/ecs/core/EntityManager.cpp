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
    // 이름 관리도 필요하면 여기서 정리
    for (auto it = entityNames.begin(); it != entityNames.end();) {
        if (it->first == entity) {
            entityByName.erase(it->second);
            it = entityNames.erase(it);
        } else {
            ++it;
        }
    }
}

std::shared_ptr<Entity> EntityManager::getById(std::size_t id) const{
    for (auto& e : entities) {
        if (e->getId() == id) return e;
    }
    return nullptr;
}

std::shared_ptr<Entity> EntityManager::getByName(const std::string& name) const{
    auto it = entityByName.find(name);
    if (it != entityByName.end()) {
        return it->second;
    }
    return nullptr;
}

void EntityManager::setName(const std::shared_ptr<Entity>& entity, const std::string& name) {
    if (entityByName.find(name) != entityByName.end()) {
        // 이름 중복 경고
        // name duplicated warning
        return;
    }
    entityNames[entity] = name;
    entityByName[name] = entity;
}
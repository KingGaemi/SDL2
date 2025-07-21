#include "ecs/ECSManager.h"
#include "Systems/AttackSystem.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

ECSManager::ECSManager() {
    makeCamera();
}



std::shared_ptr<Entity> ECSManager::createEntity() {
    auto entity = std::make_shared<Entity>(nextID++);
    entities.push_back(entity);
    return entity;
}


void ECSManager::destroyEntity(std::shared_ptr<Entity> entity) {
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

std::shared_ptr<Entity> ECSManager::getEntityById(std::size_t id) {
    for (auto& e : entities) {
        if (e->getId() == id) return e;
    }
    return nullptr;
}

void ECSManager::updateSystems(float deltaTime) {

        // if(mapEntity) mapEntity->isActive = activeMap; // temp

        std::sort(registeredSystems.begin(), registeredSystems.end(),
            [](const SystemRegistration& a, const SystemRegistration& b) {
                return a.priority < b.priority;
            }
        );

        for (auto& reg : registeredSystems) {
            if (reg.group == SystemGroup::Logic) {
                reg.system->update(entities, deltaTime);
            }
        }

        for (auto& reg : registeredSystems) {
            if (reg.group == SystemGroup::Event) {
                reg.system->update(entities, deltaTime);
            }
        }
}

void ECSManager::renderSystems(float deltaTime) {

    std::sort(registeredSystems.begin(), registeredSystems.end(),
        [](const SystemRegistration& a, const SystemRegistration& b) {
            return a.priority < b.priority;
        }
    );

    for (auto& reg : registeredSystems) {
        if (reg.group == SystemGroup::Render) {
            reg.system->update(entities, deltaTime);
        }
    }


  
}

void ECSManager::renderUI(float deltaTime) {
    std::sort(registeredSystems.begin(), registeredSystems.end(),
        [](const SystemRegistration& a, const SystemRegistration& b) {
            return a.priority < b.priority;
        }
    );

    for (auto& reg : registeredSystems) {
        if (reg.group == SystemGroup::UI) {
            reg.system->update(entities, deltaTime);
        }
    }     
}



void ECSManager::processSpawnRequests() {

    for(auto& req : pendingSpawns){
        auto entity = createEntity();
        entityFactory->configureEntity(req, entity);
    }
    pendingSpawns.clear();
    
    for(auto& req : pendingProjectiles){
        auto entity = createEntity();
        entityFactory->configureEntity(req, entity);
    }
    pendingProjectiles.clear();   
}

// void ECSManager::processCollisionEvents(){

//     for(auto& evt : collisionEvents){

//         if(evt.type == CollisionType::Crash){
            

//         }else if(evt.type == CollisionType::Hit){

//             // std::cout << evt.entityA->getId() << " hits " << evt.entityB->getId() << std::endl;

//         }

//     }
//     collisionEvents.clear();
// }


std::shared_ptr<EntityFactory> ECSManager::shareFactory() {
    return entityFactory;
}

void ECSManager::setFactory(std::shared_ptr<EntityFactory>& factory){
    entityFactory = factory;
}

void ECSManager::setEntityName(std::shared_ptr<Entity> entity, const std::string& name) {
    if (entityByName.find(name) != entityByName.end()) {
        // 이름 중복 경고
        return;
    }
    entityNames[entity] = name;
    entityByName[name] = entity;
}

std::shared_ptr<Entity> ECSManager::getEntityByName(const std::string& name) {
    auto it = entityByName.find(name);
    if (it != entityByName.end()) {
        return it->second;
    }
    return nullptr;
}

void ECSManager::processTerminatedEntities(){
    for (auto& entity : entities){
        if(entity&&entity->terminate) {
            DestroyEvent destroyEvent = {entity->getId()};
            eventManager->pushDestroyEvent(destroyEvent);
        }
    }
}

void ECSManager::cleanUpEntities(){
    auto events = eventManager->getDestroyEvents();
    for(auto evt : events){
        auto entity = getEntityById(evt.entityId);
        
        destroyEntity(entity);
    }
    eventManager->clearDestroyEvents();
}

void ECSManager::cleanUpAllEntities(){
    std::cout << "Cleanup all entities!!! " << std::endl;
    for (auto& entity : entities){
        destroyEntity(entity);
    }

}

void ECSManager::cleanUpEntitiesByScene(SceneCode sceneCode){
    for (auto& entity : entities){
        if(entity&&entity->hasComponent<SceneTag>()){
            auto sceneTag = entity->getComponent<SceneTag>();
            // std::cout << "entity " << entity->getId() << "terminate \n"; 
            if(sceneTag && sceneTag->sceneCode == sceneCode) entity->terminate = true;
        }
    }
}

void ECSManager::takeSingleRequest(const SpawnRequest& req){



}
void ECSManager::activeMapEntity(){
    // activeMap = true;
}

void ECSManager::makeCamera(){
    cameraEntity = createEntity();
    setEntityName(cameraEntity, "camera");
    cameraEntity->addComponent<SceneTag>(SceneCode::Game);
    cameraEntity->addComponent<TransformComponent>();
    cameraEntity->addComponent<PositionComponent>(1.0f, 1.0f);
    cameraEntity->addComponent<CameraComponent>(1280, 800);
}



std::shared_ptr<Entity> ECSManager::getCamera(){
    return cameraEntity;
}
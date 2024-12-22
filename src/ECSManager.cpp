#include "ECS/ECSManager.h"
#include "Systems/AttackSystem.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

std::shared_ptr<Entity> ECSManager::createEntity() {
    auto entity = std::make_shared<Entity>(nextID++);
    entities.push_back(entity);
    std::cout << "createEntity "<< std::endl; 
    return entity;
}


void ECSManager::destroyEntity(std::shared_ptr<Entity> entity) {

    std::cout << "destroyEntity : " << entityNames[entity] << std::endl; 
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
    for (std::size_t i = 0; i < MAX_SYSTEMS; ++i) {

        if (systemBitset[i]) {
            auto& system = systemArray[i];
            system->update(entities, deltaTime);
        }
    }

}

 
void ECSManager::processSpawnRequests() {


    for(auto& req : pendingSpawns){
        if(req.type == "player"){
            entityFactory->createPlayerEntity(req);
        }
        if(req.type == "farmer"){
            entityFactory->createFarmerEntity(req);
        }



    }
    pendingSpawns.clear();
    


    auto attackSys = getSystem<AttackSystem>();

    if(attackSys){
        for(auto& req : attackSys->requests)
        {
            if(req.type == "slash"){
                entityFactory->createSlashEntity(req);
            }
        }



        attackSys->requests.clear();
    }


    


}

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


void ECSManager::cleanUpEntities(){

    for (auto& entity : entities){
        

        if(entity&&!entity->isActive) destroyEntity(entity);
    }

}







void ECSManager::takeSingleRequest(const SpawnRequest& req){



}
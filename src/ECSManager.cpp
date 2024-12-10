#include "ECS/ECSManager.h"
#include <iostream>





std::shared_ptr<Entity> ECSManager::createEntity(){

	auto id = nextID++;

	// std::cout << "Entity create start" << std::endl;
	auto entity = std::make_shared<Entity>(*this, id);

	// std::cout << "Entity creating" << std::endl;
	entities.push_back(entity);
	return entity;


}

std::shared_ptr<Entity> ECSManager::getEntityByName(const std::string& name){

	auto it = entityByName.find(name);
	if (it != entityByName.end()) {
        return it->second;
    } else {
        throw std::runtime_error("There is no Entity with this name!");
    }

    return nullptr;

}

void ECSManager::setEntityName(std::shared_ptr<Entity> sharedEntity, const std::string& name) {
   	


    std::cout << "ECSManager setEntityName :"<< name << std::endl;
    entityNames[sharedEntity] = name;
    entityByName[name] = sharedEntity;
    std::cout << "ECSManager setEntityName Complete"<< name << std::endl;

}



std::optional<std::string> ECSManager::getEntityName(std::shared_ptr<Entity> sharedEntity) const {
    // entityNames에서 키 검색
    auto it = entityNames.find(sharedEntity);
    if (it != entityNames.end()) {
        return it->second; // 이름 반환
    }
    return std::nullopt; // 이름 없음
}

void ECSManager::update(){
	// std::cout << "ECSManager: update " << std::endl;

	for(auto& entity : entities){
		if(entity->isActive()){

			entity->update();
		}
	}

}


void ECSManager::draw() {
	// std::cout << "ECSManager: draw " << std::endl;
        for (auto& entity : entities) {
            if (entity->isActive()) {
                for (auto& component : entity->getAllComponents()) {
                	if (auto drawable = dynamic_cast<DrawableComponent*>(component.get())) {
                    	drawable->draw();
                	}
            	}
            }
        }
}





#include "ECS/EntityFactory.h"
#include "ECS/ECSManager.h"
#include "Components/Components.h"
#include "Systems/Systems.h"
#include <iostream>


std::shared_ptr<Entity> EntityFactory::createBackgroundEntity(std::shared_ptr<ECSManager> ecsManager, const std::string& textureName){

	auto entity = ecsManager->createEntity();
	entity->addComponent<TransformComponent>();
	entity->addComponent<SpriteComponent>(textureName, 1280, 800);

	return entity;
}



std::shared_ptr<Entity> EntityFactory::createPlayerEntity(std::shared_ptr<ECSManager> ecsManager){

	auto player = ecsManager->createEntity();
	player->addComponent<TransformComponent>();
	std::pair<int, int> size = ecsManager->getSystem<RenderSystem>()->getTextureSize("player_eri");
	player->addComponent<SpriteComponent>("player_eri", size.first , size.second, 3.0f);
	// player->addComponent<KeyboardController>(player->getComponent<TransformComponent>());

	return player;	

}
    // ... 필요한 팩토리 메서드를 추가




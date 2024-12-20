#include "Systems/AttackSystem.h"








void AttackSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){



	for(auto& entity : entities){

		
		auto statusComp = entity->getComponent<StatusComponent>();
		auto stateComp = entity->getComponent<StateComponent>();
		auto transComp = entity->getComponent<TransformComponent>();
		auto spriteComp = entity->getComponent<SpriteComponent>();


		if(stateComp && transComp && statusComp && spriteComp){
			if(stateComp->stateTimer <= 0){
				stateComp->currentState = States::Idle;
				stateComp->callAttack = false;
			}
			
			if(stateComp->callAttack){
				
				Vector2D attackPosition;

				attackPosition.x = transComp->position.x + (spriteComp->dstRect.w / 3) + transComp->direction.x * 80;
				attackPosition.y = transComp->position.y + (spriteComp->dstRect.h / 3) + transComp->direction.y * 80;
				
				auto attack = ecsManager->createEntity();

				attack->addComponent<AttackComponent>(statusComp->physicalDamage);
				attack->addComponent<TransformComponent>(attackPosition);
				attack->addComponent<ColliderComponent>(attackPosition, "slash", 100, 200);
				attack->addComponent<SpriteComponent>("water_tile", 100, 200);
				attack->addComponent<LifeTimeComponent>(0.1f);

				stateComp->callAttack = false;

				
			}

		}

	}



}

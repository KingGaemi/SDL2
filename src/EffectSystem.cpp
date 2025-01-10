# define M_PI           3.14159265358979323846
#include "Systems/EffectSystem.h"
#include "Components/SpriteComponent.h"
#include "Components/FloatingEffectComponent.h"
#include <math.h>



void EffectSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){
	for(auto& entity: entities){


		if(entity->hasComponent<FloatingEffectComponent>()){
			floatingEffect(entity, deltaTime);
		}
	}
}



void EffectSystem::floatingEffect(std::shared_ptr<Entity>& entity, float deltaTime){

	auto floatComp = entity->getComponent<FloatingEffectComponent>();
	floatComp->timeElapsed += deltaTime;
	floatComp->timeElapsed = fmod(floatComp->timeElapsed, 2 * M_PI);
    floatComp->renderOffsetY = floatComp->amplitude 
                            * sin(floatComp->speed 
                            * floatComp->timeElapsed
                            + floatComp->phaseOffset);


       
}
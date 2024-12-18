#include <SDL2/SDL.h>
#include "Systems/InputSystem.h"
#include "Components/PlayableComponent.h"
#include "Components/TransformComponent.h"
#include "Components/StateComponent.h"
#include <iostream>








void InputSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){
	const Uint8* state = SDL_GetKeyboardState(NULL);

	Vector2D velo;


	if (state[SDL_SCANCODE_LEFT]) velo.x += -1;
    if (state[SDL_SCANCODE_RIGHT]) velo.x += 1;
    if (state[SDL_SCANCODE_UP]) velo.y += -1;
    if (state[SDL_SCANCODE_DOWN]) velo.y += 1;


    // 키 상태에 따른 방향 결정
    if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN]){
		for (auto& entity : entities) {
	        if (entity->hasComponent<PlayableComponent>()) {
	        	auto trans = entity->getComponent<TransformComponent>();
	        	if(trans){
	        		trans->velocity = velo;
	        	}
	            auto stateComp = entity->getComponent<StateComponent>();
	            if (stateComp) {
	                if(stateComp->currentState != States::Walk) stateComp->currentState = States::Walk;
	            }
	        }
    	}
    }else{
    	for (auto& entity : entities) {
    		if (entity->hasComponent<PlayableComponent>()) {
	        	auto trans = entity->getComponent<TransformComponent>();
	        	if(trans){
	        		trans->velocity = velo;
	        	}
		        auto stateComp = entity->getComponent<StateComponent>();
		        if (stateComp) {
		        	if(stateComp->currentState != States::Idle) stateComp->currentState = States::Idle;
		        }
		    }
		}
    }

    // if(!state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT]){
	// 	for (auto& entity : entities) {
	//         if (entity->hasComponent<PlayableComponent>()) {
	//         	auto trans = entity->getComponent<TransformComponent>();
	//         	if(trans){
	//         		trans->direction.x = 0;
	//         	}
	//         }
    // 	}
    // }

    // if(!state[SDL_SCANCODE_UP] && !state[SDL_SCANCODE_DOWN]){
    // 	for (auto& entity : entities) {
	//         if (entity->hasComponent<PlayableComponent>()) {
	//         	auto trans = entity->getComponent<TransformComponent>();
	//         	if(trans){
	//         		trans->direction.y = 0;
	//         	}
	//         }
    // 	}
    
 

}
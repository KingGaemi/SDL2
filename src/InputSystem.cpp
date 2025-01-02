#include <SDL2/SDL.h>
#include "Systems/InputSystem.h"
#include "Components/PlayableComponent.h"
#include "Components/StateComponent.h"
#include <iostream>








void InputSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){
	const Uint8* state = SDL_GetKeyboardState(NULL);

	// Vector2D velo;


	// for (auto& entity : entities){
	// 	if(entity->hasComponent<PlayableComponent>()&& entity->hasComponent<StateComponent>() ){

	// 		auto playComp = entity->getComponent<PlayableComponent>();
	// 		auto stateComp = entity->getComponent<StateComponent>();

	// 		if(playComp && stateComp){
	// 			if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN]){

	// 				stateComp->changeState(States::Walk);

	// 			}else{
	// 				stateComp->changeState(States::Idle);

	// 			}


	// 		}

	// 	}
	// }


   

}
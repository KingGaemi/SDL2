#include "ECS/Entity.h"
#include "ECS/Component.h"





void Entity::update(){

	for(auto& component : components){
		component -> update();
	}

}





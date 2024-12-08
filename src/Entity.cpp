#include "ECS/Entity.h"
#include "ECS/Component.h"





void Entity::update(){

	for(auto& component : components){
		component -> update();
	}

}


void Entity::draw(){

	for(auto& component : components){
		component -> draw();
	}

}

template <typename T, typename... Args>
T& Entity::addComponent(Args&&... args){

	static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

	T* comp = new T(std::forward<Args>(args)...);
	comp->entity = this;
	components.emplace_back(comp);
	componentArray[getComponentTypeID<T>()] = comp;
	componentBitset[getComponentTypeID<T>()] = true;

	comp->init();

	return *comp;	


}



template <typename T>
bool Entity::hasComponent() const{

	return componentBitset[getComponentTypeID<T>()];

}

template <typename T>
T& Entity::getComponent() const{

	auto ptr = componentArray[getComponentTypeID<T>()];
	return *static_cast<T*>(ptr);
}
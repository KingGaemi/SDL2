#pragma once
#include "ECS/Component.h"
#include "Components/TransformComponent.h"





class KeyboardController : public Component {

public:

	TransformComponent* transform; 
	KeyboardController(TransformComponent* p_transform);
	void init() override;
	void update() override;


private:






};
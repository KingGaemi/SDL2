#pragma once
#include <SDL2/SDL.h>
#include "Components/TransformComponent.h"





class KeyboardController : public Component {

public:

	
	KeyboardController(std::shared_ptr<TransformComponent> p_transform);
	void update();


private:


	std::shared_ptr<TransformComponent> transform; 



};
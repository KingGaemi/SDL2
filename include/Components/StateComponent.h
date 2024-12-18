#pragma once

#include "ECS/Component.h"


enum class States{
	Idle,
	Walk,	
	Run,
	Attack,
	Hit,
	Death
};



class StateComponent : public Component {


public:
	States currentState;

	

private:


};
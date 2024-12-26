#pragma once

#include "ECS/Component.h"
#include <iostream>


enum class States{
	Idle,
	Walk,	
	Run,
	Attack,
	Hurt,
	Death
};



class StateComponent : public Component {


public:
	States currentState;
	float stateTimer;
	bool callAttack = false;
	bool inMotion = false;

	
	void changeState(States newState){
		if(currentState != newState){
			currentState = newState;
			inMotion = false;
			// if(currentState == States::Idle) std::cout << "Idle";
			// if(currentState == States::Walk) std::cout << "Walk";

			// std::cout << std::endl;
		}
	}
	
	void changeState(States newState, float timer){
		if(currentState != newState){
			currentState = newState;
			stateTimer = timer;
			inMotion = true;
			if(newState == States::Attack) callAttack = true;
			// if(currentState == States::Attack) std::cout << "Attack";

			// std::cout << std::endl;
		}
	}

	void setTimer(float timer){stateTimer = timer;}
	

private:


};
#pragma once

#include "ECS/Component.h"
#include <iostream>


enum class ActionStates{
	Idle,
	Attack,
	SpecialAttack,
	Hurt,
	Death
};

enum class MovementStates{
	Stop,
	Walk,
	Run
};



class StateComponent : public Component {


public:
	ActionStates actionState = ActionStates::Idle;
	MovementStates movementState = MovementStates::Stop;
	float stateTimer;
	bool callAttack = false;
	bool inMotion = false;
	
	void changeMovementState(MovementStates newState){
		if(movementState != newState) movementState = newState;
	}
	
	void changeActionState(ActionStates newState, float timer){
		if(actionState == ActionStates::Death) return;
		actionState = newState;
		stateTimer = timer;
		inMotion = true;
		if(newState == ActionStates::Attack) callAttack = true;
		// if(currentState == States::Attack) std::cout << "Attack";

			// std::cout << std::endl;

	}

	void setTimer(float timer){stateTimer = timer;}
	

private:


};
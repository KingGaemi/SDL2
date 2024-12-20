#pragma once

#include "ECS/Component.h"


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

	
	void changeState(States newState){
		if(currentState != newState){
			currentState = newState;
		}
	}
	
	void changeState(States newState, float timer){
		if(currentState != newState){
			currentState = newState;
			stateTimer = timer;
			if(newState == States::Attack) callAttack = true;
		}
	}

	void setTimer(float timer){stateTimer = timer;}
	

private:


};
#pragma once

#include "ECS/Component.h"




enum Actions{ HOLD, MOVE, ATTACK, CAST};



class ActionComponent : public Component {

public:


	void doAction(enum Actions type);


private:
	enum Actions type = HOLD;


};
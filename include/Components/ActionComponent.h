#pragma once

#include "ECS/Component.h"




enum Actions{ HOLD, MOVE, ATTACK, CAST};



class ActionComponent : public Component {

public:


	void init() override;
	void update() override;

	void doAction(enum Actions type);


private:
	enum Actions type = HOLD;


}